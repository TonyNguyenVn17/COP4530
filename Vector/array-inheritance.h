#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
using namespace std;

class IntArray
{
    friend ostream& operator<<(ostream&, const IntArray&);
protected:
    int* arr;
    int size;
public:
    IntArray(int initSize, int value = 0);
    IntArray(const IntArray& copy);
}tr

#endif