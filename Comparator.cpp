#include "Comparator.h"
#include "Utils.h"

#include <iostream>

void Comparator::compare(Country &c1, Country &c2, const string &metric)
{
    string normMetric = toLower(metric); // normalize metric name

    double val1 = c1.getMetric(normMetric);
    double val2 = c2.getMetric(normMetric);

    cout << "Comparing by " << metric << ":\n";
    cout << c1.getName() << ": " << val1 << endl;
    cout << c2.getName() << ": " << val2 << endl;

    if (val1 == -1 || val2 == -1)
    {
        cout << "One of the countries does not have the metric '" << metric << "'\n";
        cout << "---------------------\n";
        return;
    }

    if (val1 > val2)
        cout << c1.getName() << " ranks higher in " << metric << endl;
    else if (val2 > val1)
        cout << c2.getName() << " ranks higher in " << metric << endl;
    else
        cout << "Both countries have equal " << metric << endl;

    cout << "---------------------\n";
}
