#pragma once
#include <string>
#include <unordered_map>
#include <map>
using namespace std;

class Country
{
    string name;
    long long pop;
    double gdp;
    double literacy;
    unordered_map<string, double> metrices;

public:
    Country();
    Country(string name, long long pop, double gdp, double literacy);

    void addMetric(const string &key, double value);
    double getMetric(const string &key) const;
    bool hasMetric(const string &key) const;
    void setMetric(const string &key, double value);

    string getName() const;
    void displayMetrics() const;

    unordered_map<string, double> getAllMetrics() const;
};
