#include <bits/stdc++.h>
using namespace std;
class date
{
public:
    int year;
    int month;
    int day;
    date()
    {
        year = 0;
        month = 0;
        day = 0;
    }
    date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    void print()
    {
        cout << year << "-" << month << "-" << day << " " << endl;
    }
    void set(int y, int m, int d, int h, int mi, int s)
    {
        year = y;
        month = m;
        day = d;
    }
    void set(date d)
    {
        year = d.year;
        month = d.month;
        day = d.day;
    }
    void set(string s)
    {
        int y, m, d, h, mi, sec;
        sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d);
        year = y;
        month = m;
        day = d;
    }
};