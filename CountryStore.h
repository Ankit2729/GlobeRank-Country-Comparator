#pragma once
#include "Country.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

class CountryStore
{
    unordered_map<string, Country> countries;

public:
    unordered_set<string> allMetrices;
    void addCountry(const Country &country);
    bool removeCountry(const string &name);
    bool clearAllCountries();
    void displayAllCountries() const;
    void showCountryProfile(const string &countryName) const;
    void editCountry(const string &resolved);
    string getValidatedCountryName(const string &countryName) const;
    Country *getCountry(const string &name);
    const Country *getCountry(const string &name) const;

    void compareByMetric(const string &metric);
    void topCountriesByMetric(const string &metric, int n = 3) const;
    void filterByMetricRange(const string &metric, double minValue, double maxValue) const;
    void computeByMultipleMetrices(const vector<string> &metrices, bool descending = true);

    bool hasCountry(const string &name) const;
    void updateCountry(const string &name, const Country &updated);
    string normalizeMetric(const string &metric) const;

    bool saveToFile(const string &filename) const;
    bool loadFromFile(const string &filename);
};

string formatNumber(double num);