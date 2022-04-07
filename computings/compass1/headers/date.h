/**
 * @file date.h
 * @author Li Rong, Zhong Tiantian
 * @brief Providing Class CDate for dates.
 * @version 0.1
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022 Zhejiang University
 * 
 */

#include <bits/stdc++.h>
using namespace std;
#ifndef CDate_hh
#define CDate_hh
class CDate
{
public:
    int year;
    int month;
    int day;
    CDate()
    {
        year = 0;
        month = 0;
        day = 0;
    }
    CDate(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    CDate(time_t current_time)
    {
        struct tm *local_time = localtime(&current_time);
        year = local_time->tm_year + 1900;
        month = local_time->tm_mon + 1;
        day = local_time->tm_mday;
    }
    void print()
    {
        cout << year << "-" << month << "-" << day << " " << endl;
    }
    bool set(int y, int m, int d)
    {
        if (m < 1 || m > 12 || d < 0 || d > 30)
        // Assuming we only have 30 days a month in Computing Assignment World
        // Thus we have 360 days a year
        {
            return false;
        }
        year = y;
        month = m;
        day = d;
        return true;
    }
    void set(CDate d)
    {
        year = d.year;
        month = d.month;
        day = d.day;
    }
    bool set(string s)
    {
        int y, m, d, h, mi, sec;
        if (sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
        {
            return false;
        }
        if (m < 1 || m > 12 || d < 0 || d > 30)
        // Assuming we only have 30 days a month in Computing Assignment World
        // Thus we have 360 days a year
        {
            return false;
        }
        year = y;
        month = m;
        day = d;
        return true;
    }
    int operator-(CDate d)
    {
        int y, m, days;
        y = year - d.year;
        m = month - d.month;
        days = day - d.day;
        if (days < 0)
        {
            m--;
            days += 30;
        }
        if (m < 0)
        {
            y--;
            m += 12;
        }
        return y * 360 + m * 30 + days;
    }
    void nextday()
    {
        day++;
        if (day > 30)
        {
            day = 1;
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
        }
    }
    void operator++(int)
    {
        nextday();
    }
    CDate operator+= (int n)
    {
        for (int i = 0; i < n; i++)
        {
            nextday();
        }
        return *this;
    }
    CDate operator+ (CDate datesss)
    {
        CDate d;
        d.year = year + datesss.year;
        d.month = month + datesss.month;
        d.day = day + datesss.day;
        if (d.day > 30)
        {
            d.day -= 30;
            d.month++;
        }
        if (d.month > 12)
        {
            d.month -= 12;
            d.year++;
        }
        return d;
    }
};
#endif