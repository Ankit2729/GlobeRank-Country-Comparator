#include "CountryStore.h"
#include "Country.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

string capitalize(const string &s)
{
    string res = s;
    if (!res.empty())
        res[0] = toupper(res[0]);
    return res;
}

void CountryStore::addCountry(const Country &country)
{
    countries[country.getName()] = country;
    allMetrices.insert("population");
    allMetrices.insert("gdp");
    allMetrices.insert("literacy rate");
}
string CountryStore::getValidatedCountryName(const string &countryName) const
{
    string query = trim(countryName);
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    // bool found = false;

    // exact || partial macth
    for (const auto &pair : countries)
    {
        string storedName = trim(pair.first);
        string lowerStoredName = storedName;
        transform(lowerStoredName.begin(), lowerStoredName.end(), lowerStoredName.begin(), ::tolower);

        if (lowerStoredName.find(query) != string::npos)
            return storedName;
    }

    // Fuzzy match
    string closestMatch;
    int min_dist = 3;
    for (const auto &pair : countries)
    {
        string storedName = trim(pair.first);
        string lowerStoredName = storedName;
        transform(lowerStoredName.begin(), lowerStoredName.end(), lowerStoredName.begin(), ::tolower);

        int dist = levenshteinDistance(query, lowerStoredName);
        if (dist < min_dist)
        {
            min_dist = dist;
            closestMatch = storedName;
        }
    }

    if (!closestMatch.empty())
    {
        cout << "\n⚠️ Country \"" << countryName << "\" not found. Did you mean \"" << closestMatch << "\"? (y/n): \n";

        char ch;
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ch == 'y' || ch == 'Y')
        {
            return closestMatch;
        }
    }
    return ""; // No match
}

void CountryStore::displayAllCountries() const
{
    if (countries.empty())
    {
        cout << "\033[31mNo countries to display!\033[0m\n";
        return;
    }

    cout << "\n\033[36m============================================================\n";
    cout << "              🌏 GlobeRank Country List\n";
    cout << "============================================================\033[0m\n";

    cout << left << setw(20) << "Country";
    for (const auto &m : allMetrices)
        cout << right << setw(15) << capitalize(m);
    cout << endl;
    cout << string(20 + 15 * allMetrices.size(), '-') << endl;

    for (const auto &val : countries)
    {
        const auto &c = val.second;
        cout << left << setw(20) << val.first;
        for (const auto &m : allMetrices)
        {
            double metricVal = val.second.hasMetric(m) ? val.second.getMetric(m) : 0.0;
            cout << right << setw(15) << fixed << setprecision(2) << metricVal;
        }
        cout << endl;
    }
    cout << string(20 + 15 * allMetrices.size(), '=') << "\n";
}

void CountryStore::compareByMetric(const string &metric)
{
    string normMetric = normalizeKey(metric);
    vector<pair<string, double>> list;

    for (auto &pair : countries)
    {
        double val = pair.second.getMetric(normMetric);
        list.push_back({pair.first, val});
    }

    sort(list.begin(), list.end(), [](auto &a, auto &b)
         { return a.second > b.second; });

    cout << "Countries ranked by " << metric << endl;

    for (auto &pair : list)
    {
        if (pair.second != -1)
            cout << pair.first << ": " << pair.second << endl;
    }
}

void CountryStore::computeByMultipleMetrices(const vector<string> &metrices, bool descending)
{
    vector<pair<string, double>> scores;

    for (const auto &entry : countries)
    {
        const Country &c = entry.second;
        double totalScore = 0;

        for (const string &metric : metrices)
        {
            totalScore += c.getMetric(normalizeKey(metric));
        }

        scores.push_back({c.getName(), totalScore});
    }

    sort(scores.begin(), scores.end(), [&](auto &a, auto &b)
         { return descending ? a.second > b.second : a.second < b.second; });

    cout << "\n🌏 Countries ranked by combined metrices.\n";

    for (auto it = scores.begin(); it != scores.end(); ++it)
    {
        cout << it->first << ": " << it->second << endl;
    }
}

void CountryStore::topCountriesByMetric(const string &metric, int n) const
{
    if (countries.empty())
    {
        cout << " No countries available.\n";
        return;
    }

    vector<pair<string, double>> ranking;

    for (const auto &e : countries)
    {
        const Country &country = e.second;
        string m = normalizeKey(metric);
        double val = country.getMetric(m);
        ranking.push_back({country.getName(), val});
    }

    sort(ranking.begin(), ranking.end(), [](const auto &a, const auto &b)
         { return a.second > b.second; });
    cout << "\n Top " << n << " Countries by " << metric << ":\n";

    cout << string(45, '-') << endl;

    int lt = min(n, (int)ranking.size());

    for (int i = 0; i < lt; i++)
    {
        cout << left << setw(5) << (i + 1)
             << setw(20) << ranking[i].first
             << setw(15) << ranking[i].second
             << endl;
    }

    cout << string(45, '-') << endl;
}

Country *CountryStore::getCountry(const string &name)
{
    auto it = countries.find(name);
    if (it != countries.end())
        return &it->second;
    return nullptr;
}

const Country *CountryStore::getCountry(const string &name) const
{
    auto it = countries.find(name);
    if (it != countries.end())
        return &it->second;
    return nullptr;
}

void CountryStore::filterByMetricRange(const string &metric, double minValue, double maxValue) const
{
    cout << "\n Countries with " << metric << " between " << minValue << " and " << maxValue << ":\n";
    bool found = false;
    for (const auto &pair : countries)
    {
        const Country &c = pair.second;
        string m = normalizeKey(metric);
        double val = c.getMetric(m);
        // cout << c.getName();
        if (val >= minValue && val <= maxValue)
        {
            cout << " - " << c.getName() << ": " << val << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No countries found in the given range.\n";
    }
}
void CountryStore::showCountryProfile(const string &countryName) const
{

    string name = getValidatedCountryName(countryName);
    if (!name.empty())
    {

        cout << "=====================================================================\n";
        cout << "\n Country Profile: " << name << endl;
        cout << "=====================================================================\n";
        countries.at(name).displayMetrics();
    }
    else
    {
        cout << "❌ Country\"" << countryName << "\" not found.\n";
    }
}

bool CountryStore::hasCountry(const string &name) const
{
    return countries.find(name) != countries.end();
}

void CountryStore::updateCountry(const string &name, const Country &updated)
{
    countries[name] = updated;
}

bool CountryStore::removeCountry(const string &name)
{
    if (countries.erase(name) > 0)
    {
        cout << "Country '" << name << "' deleted successfully!\n";
        return true;
    }
    else
    {
        cout << "Country '" << name << "' not found.\n";
        return false;
    }
}

bool CountryStore::clearAllCountries()
{
    if (countries.empty())
    {
        cout << "No countries to delete.\n";
        return false;
    }
    countries.clear();
    cout << "All countries deleted successfully!\n";
    return true;
}

void CountryStore::editCountry(const string &resolved)
{
    Country &updated = countries.at(resolved);
    while (true)
    {
        cout << "\n---Editing " << resolved << " ---\n";
        cout << "\nWhich field would you like to update?\n";
        cout << "1. Population\n";
        cout << "2. GDP\n";
        cout << "3. Literacy Rate\n";
        cout << "4. Custom Metric\n";
        cout << "5. Done Editing\n";
        cout << "Enter your choice: ";

        int ch;
        cin >> ch;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 5.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ch == 1 || ch == 2 || ch == 3 || ch == 4)
        {
            string metricName;
            double value;

            if (ch == 1)
            {
                metricName = "population";
                cout << "Enter new population: ";
            }
            else if (ch == 2)
            {
                metricName = "gdp";
                cout << "Enter new GDP: ";
            }
            else if (ch == 3)
            {
                metricName = "literacy rate";
                cout << "Enter new Literacy Rate: ";
            }
            else
            {
                cout << "Enter metric name: ";
                getline(cin, metricName);
                metricName = normalizeKey(metricName);
                cout << "Enter new value: ";
            }

            cin >> value;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (value < 0)
            {
                cout << "❌ Invalid value! Metric cannot be negative.\n";
                continue;
            }

            updated.setMetric(metricName, value);
            allMetrices.insert(normalizeKey(metricName));
            cout << "✅ Metric \"" << metricName << "\" updated.\n";

            if (ch == 4)
            {
                char choice;
                cout << "Do you want to add this metric for other countries too? (y/n): ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (choice == 'y' || choice == 'Y')
                {
                    for (auto &pair : countries)
                    {
                        if (pair.first != resolved)
                        {
                            double val;
                            cout << "Enter value of " << metricName << " for " << pair.first << ": ";
                            cin >> val;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            pair.second.setMetric(metricName, val);
                        }
                    }
                }
            }
        }
        else if (ch == 5)
        {
            cout << "✅ Editing Completed.\n";
            return;
        }
        else
        {
            cout << "❌ Invalid choice. Try again.\n";
        }
    }
}

bool CountryStore::saveToFile(const string &filename) const
{
    ofstream out(filename);
    if (!out.is_open())
    {
        cout << "Failed to open file for saving.\n";
        return false;
    }
    out << "Country";
    for (const auto &m : allMetrices)
    {
        out << "," << m;
    }
    out << "\n";

    for (const auto &e : countries)
    {
        const Country &c = e.second;
        out << c.getName();

        for (const auto &m : allMetrices)
        {
            double val = c.hasMetric(m) ? c.getMetric(m) : 0.0;
            out << "," << val;
        }
        out << "\n";
    }
    cout << "Data saved to " << filename << " successfully.\n";
    return true;
}
bool CountryStore::loadFromFile(const string &filename)
{
    ifstream in(filename);
    if (!in.is_open())
    {
        cout << "Failed to open file for loading.\n";
        return false;
    }

    countries.clear();
    allMetrices.clear();

    string line;
    vector<string> headers;
    // read headers
    if (getline(in, line))
    {
        stringstream ss(line);
        string header;
        while (getline(ss, header, ','))
        {
            headers.push_back(normalizeKey(header));
        }
    }

    // add metrices(except "Country")
    for (size_t i = 1; i < headers.size(); ++i)
    {
        allMetrices.insert(headers[i]);
    }

    // read country data
    while (getline(in, line))
    {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');
        name = trim(name);

        Country c(name, 0, 0.0, 0.0);

        for (size_t i = 1; i < headers.size(); ++i)
        {
            string valStr;
            if (getline(ss, valStr, ','))
            {
                double val = 0.0;
                try
                {
                    val = stod(trim(valStr));
                }
                catch (...)
                {
                }
                c.setMetric(headers[i], val);
            }
        }
        countries[name] = c;
    }
    cout << "Data loaded from " << filename << " successfully.\n";
    return true;
}
