#pragma once
#include "Country.h"

using namespace std;

class Comparator
{
public:
    static void compare(Country &c1, Country &c2, const string &metric);
};
