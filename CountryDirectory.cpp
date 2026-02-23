#include <iostream>
#include <unordered_map>
#include "Country.h"
using namespace std;

int main()
{
    unordered_map<string, Country *> countries;
    countries["India"] = new Country("India", 1400000000, 3.91, 77.7);
    countries["USA"] = new Country("USA", 331000000, 23.32, 99.0);

    string query;
    cout << "Enter country name to search: ";
    cin >> query;

    if (countries.find(query) != countries.end())
        countries[query]->displayMetrics();
    else
        cout << "Country not found.\n";

    return 0;
}