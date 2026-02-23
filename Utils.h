#pragma once
#include <string>
#include <cctype>
#include <climits>
#include <vector>
#include <algorithm>
#include <initializer_list>

#include <unordered_map>
using namespace std;

inline int levenshteinDistance(const string &a, const string &b)
{
    int m = a.size(), n = b.size();
    // Dynamic Programming....
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (tolower(a[i - 1]) == tolower(b[j - 1]))
                dp[i][j] = dp[i - 1][j - 1]; // tabulation
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});

    return dp[m][n];
}

inline string toLower(const string &str)
{
    string res = str;
    for (char &ch : res)
        ch = tolower(ch);
    return res;
}
template <typename T>
inline string formatWithCommas(T val)
{
    static_assert(is_arithmetic<T>::value, "formatWithCommas requires a numeric type");
    long long number = static_cast<long long>(val);

    string num = to_string(number);
    int com = num.length() - 3;
    while (com > 0)
    {
        num.insert(com, ",");
        com -= 3;
    }
    return num;
}
inline string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

inline string normalizeKey(const string &key)
{
    string lowered = key;
    for (auto &ch : lowered)
        ch = tolower(ch);

    vector<string> valid = {"population", "gdp", "literacy"};
    string best = lowered;
    int bestDist = INT_MAX;

    for (auto &cand : valid)
    {
        int d = levenshteinDistance(lowered, cand);
        if (d < bestDist)
        {
            bestDist = d;
            best = cand;
        }
    }
    if (bestDist <= 2)
        return best;
    return lowered;
}
