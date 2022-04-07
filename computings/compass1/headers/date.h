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
    date(time_t current_time){
        struct tm *local_time = localtime(&current_time);
        year = local_time->tm_year + 1900;
        month = local_time->tm_mon + 1;
        day = local_time->tm_mday;
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
    int operator-(date d)
    {
        int y, m, day;
        y = year - d.year;
        m = month - d.month;
        day = day - d.day;
        if (day < 0)
        {
            m--;
            day += 30;
        }
        if (m < 0)
        {
            y--;
            m += 12;
        }
        return y * 365 + m * 30 + day;
    }
};