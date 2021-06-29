#ifndef TRUECONF_H
#define TRUECONF_H

// библиотеки std
#include <vector>
#include <map>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

class TrueConf
{
public:
    TrueConf();
private:
    template<typename T>
    void randomFilling(T &emptyContainer, const size_t &size, const int &seed);
    template<typename T>
    void randomDelete(T &container, const int &seed);
    int randomNumber(const int &bottom, const int &top, const int &seed = 0);
    template<typename T, typename T1>
    void syncing(T &Vector, T1 &Map);
    void printMap(const map <int, int>& Map);
    void printVector(const vector <int>& vec);
};

#endif // TRUECONF_H
