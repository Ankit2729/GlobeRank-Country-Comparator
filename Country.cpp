#include "Country.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <map>

Country::Country()
{
    name = "Unnamed";
}

Country::Country(string name, long long pop, double gdp, double literacy) : name(name), pop(pop), gdp(gdp), literacy(literacy)
{
    this->name = name;

    metrices[normalizeKey("gdp")] = gdp;
    metrices[normalizeKey("literacy rate")] = literacy;
    metrices[normalizeKey("population")] = static_cast<double>(pop);
}

void Country::addMetric(const string &key, double value)
{
    metrices[normalizeKey(key)] = value;
}

double Country::getMetric(const string &key) const
{
    string lowered = normalizeKey(key);
    if (metrices.count(lowered))
        return metrices.at(lowered);
    return -1.0;
}
bool Country::hasMetric(const string &key) const
{
    return metrices.find(normalizeKey(key)) != metrices.end();
}

void Country::setMetric(const string &key, double value)
{
    metrices[normalizeKey(key)] = value;
}

string Country::getName() const
{
    return name;
}

void Country::displayMetrics() const
{
    cout << "\nCountry: " << name << endl;
    if (metrices.count("population") && metrices.at("population") > 0)
        cout << "Population: " << formatWithCommas(metrices.at("population")) << endl;
    else
        cout << "Population: N/A" << endl;

    if (metrices.count("gdp") && metrices.at("gdp") >= 0)
        cout << "GDP: " << fixed << setprecision(2) << metrices.at("gdp") << endl;
    else
        cout << "GDP: N/A" << endl;

    if (metrices.count("literacy rate") && metrices.at("literacy rate") >= 0)
        cout << "Literacy rate: " << fixed << setprecision(2) << metrices.at("literacy rate") << "%" << endl;
    else
        cout << "Literacy rate: N/A" << endl;

    cout << "================================================================\n";
}

unordered_map<string, double> Country::getAllMetrics() const
{
    return metrices;
}