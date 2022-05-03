/**
 * @file profile.h
 * @author Li Rong
 * @brief Provides declearations of structure personal_profile and its properties.
 * @version 0.1
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PROF_H
#define PROF_H
#include <bits/stdc++.h>
#include "date.h"

using std::string;

/**
 * @brief Structure for personal profiles
 * 
 */
typedef struct personal_profile

{
    string name;
    string address;
    string phone;
    string WeChat;
    string email;
    int64_t ID; 
    int64_t *vaccination_sequence;
    int profession; // I to VIII
    int risk;       // 0-3
    int agegroup;   // 1-7
    // int64_t birthdate;
    CDate *birthday;
    // int64_t registrationdate;
    CDate registrationdate;
    int64_t regID;
    int64_t inoID;
    // int64_t inoculate_date = -1;
    CDate inoculate_date;
    int64_t priority_num;
    bool is_inoculated = false;
    bool once_withdraw = false;
    bool is_delay = false;
    bool withdraw = false;
    bool is_assigned = false;
} personal_profile;

/**
 * @brief Structure for registration point information
 * 
 */
typedef struct registration_profile
{

    int64_t ID;
    int64_t *vaccination_sequence;

    // Location of the registration point
    int x_coordinate;
    int y_coordinate;
} registration_profile;


/**
 * @brief Structure for inoculation point information
 * 
 */
typedef struct inoculate_profile
{
    int64_t ID;

    // Location of the inoculation point
    int x_coordinate;
    int y_coordinate;
    int daily_processnum;

} inoculate_profile;

#endif