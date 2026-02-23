#include "Country.h"
#include <iostream>
#include <limits>
#include "CountryStore.h"
#include "Comparator.h"

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define PURPLE "\033[34m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

int main()
{
    CountryStore store;
    store.loadFromFile("abc.txt");

    Country india("India", 1400000000, 3.73, 74.04);
    // india.addMetric("Happiness", 4.2);
    // india.addMetric("Health", 6.5);

    Country japan("Japan", 125000000, 4.9, 99.0);
    // japan.addMetric("Happiness", 5.9);
    // japan.addMetric("Health", 8.1);

    Country norway("Norway", 5400000, 5.1, 100.0);
    // norway.addMetric("Happiness", 7.6);
    store.allMetrices.insert({"population", "gdp", "literacy rate"});
    store.addCountry(india);
    store.addCountry(japan);
    store.addCountry(norway);

    int choice;
    do
    {
        cout << CYAN << "==================================================================\n"
             << RESET;
        cout << CYAN << "\t Welcome to GlobeRank Menu:\t\n"
             << RESET;
        cout << CYAN << "==================================================================\n"
             << RESET;

        cout << BOLD << CYAN << "[1]  Compare countries by metric\n"
             << RESET;
        cout << BOLD << GREEN << "[2]  Top N countries by metric\n"
             << RESET;
        cout << BOLD << GREEN << "[3]  Filter countries by metric range\n"
             << RESET;
        cout << BOLD << PURPLE << "[4]  Display all countries\n"
             << RESET;
        cout << BOLD << PURPLE << "[5]  Add a new country\n"
             << RESET;
        cout << BOLD << YELLOW << "[6]  Show a country's profile\n"
             << RESET;
        cout << BOLD << YELLOW << "[7]  Edit a country's details\n"
             << RESET;
        cout << BOLD << RED << "[8]  Delete a country\n"
             << RESET;
        cout << BOLD << RED << "[9]  Delete all countries\n"
             << RESET;
        cout << BOLD << GREEN << "[10]  Save countries to file\n"
             << RESET;
        cout << BOLD << GREEN << "[11]  Load countries from file\n"
             << RESET;
        cout << BOLD << CYAN << "[12] Compare Two Countries directly.\n"
             << RESET;
        cout << BOLD << CYAN << "[0] Exit\n\n"
             << RESET;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string metric;
            cout << "Enter metric to compare: ";
            cin.ignore();
            getline(cin, metric);
            store.compareByMetric(metric);
        }
        else if (choice == 2)
        {
            string metric;
            int n;
            cout << "Enter metric: ";
            cin.ignore();
            getline(cin, metric);
            cout << "Enter number of top countries to show: ";
            cin >> n;
            store.topCountriesByMetric(metric, n);
        }
        else if (choice == 3)
        {
            string metric;
            double minVal, maxVal;
            cout << "Enter metric: ";
            cin.ignore();
            getline(cin, metric);
            cout << "Enter minimum value: ";
            cin >> minVal;
            cout << "Enter maximum value: ";
            cin >> maxVal;
            store.filterByMetricRange(metric, minVal, maxVal);
        }
        else if (choice == 4)
        {
            store.displayAllCountries();
        }
        else if (choice == 5)
        {
            string name;
            long long pop;
            double gdp, literacy;

            cin.ignore();
            cout << "Enter Country name: ";
            getline(cin, name);
            cout << "Enter population: ";
            cin >> pop;

            cout << "Enter GDP (in trillions): ";
            cin >> gdp;
            cout << "Enter Literacy rate(%): ";
            cin >> literacy;

            Country newCountry(name, pop, gdp, literacy);
            int extraCount;
            cout << "How many additional metrices to add?";
            cin >> extraCount;

            cin.ignore();

            for (int i = 0; i < extraCount; i++)
            {
                string metricName;
                double val;
                cout << "Metric: " << (i + 1) << " name: ";
                getline(cin, metricName);
                cin >> val;
                cin.ignore();
                newCountry.addMetric(metricName, val);
            }

            store.addCountry(newCountry);
            cout << " Country added successfully!\n";
        }
        else if (choice == 6)
        {
            string name;
            cin.ignore();
            cout << "Enter country name to view profile: ";
            getline(cin, name);
            store.showCountryProfile(name);
        }
        else if (choice == 7)
        {
            string countryName;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter country name to edit: ";
            getline(cin, countryName);

            string resolved = store.getValidatedCountryName(countryName);
            if (resolved.empty())
            {
                cout << " ❌Country not found!\n";
                continue;
            }
            store.showCountryProfile(resolved);

            cout << "\n Editing details for: " << resolved << endl;
            store.editCountry(resolved);
        }

        else if (choice == 8)
        {
            string name;
            cin.ignore();
            getline(cin, name);

            if (store.removeCountry(name))
            {
                cout << "✅ Country \"" << name << "\" deleted successfully!\n";
            }
            else
            {
                cout << "❌ Country \"" << name << "\" not found!\n";
            }
        }

        else if (choice == 9)
        {
            store.clearAllCountries();
            cout << "🧹 All Countries have been removed!\n";
        }
        else if (choice == 10)
        {
            string fileName;
            cout << "Enter file name to save data: ";
            cin.ignore();
            getline(cin, fileName);
            store.saveToFile(fileName);
            cout << "Data saved successfully!\n";
        }
        else if (choice == 11)
        {
            string fileName;
            cout << "Enter file name to load data: ";
            cin.ignore();
            getline(cin, fileName);
            store.loadFromFile(fileName);
            cout << "Data loaded successfully!\n";
        }
        else if (choice == 12)
        {
            cout << "Enter first country: ";
            string c1;
            getline(cin >> ws, c1);
            c1 = store.getValidatedCountryName(c1);

            cout << "Enter second country: ";
            string c2;
            getline(cin >> ws, c2);
            c2 = store.getValidatedCountryName(c2);

            Country *country1 = store.getCountry(c1);
            Country *country2 = store.getCountry(c2);

            if (country1 && country2)
            {
                cout << "Enter metric to compare: ";
                string metric;
                getline(cin >> ws, metric);
                Comparator::compare(*country1, *country2, metric);
            }
            else
            {
                cout << "One or both countries not found.\n";
            }
        }

        else if (choice == 0)
        {
            cout << "Exiting.. Thank you!\n";
        }
        else
        {
            cout << " Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    store.saveToFile("abc.txt");
    return 0;
}
