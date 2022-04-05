
#ifndef PROF_H
#define PROF_H
#include <bits/stdc++.h>

using std::string;
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
    int64_t birthdate;
    int64_t registrationdate;
    int64_t regID;
    int64_t inoculate_date = -1;
    int64_t priority_num;
    bool is_inoculated = false;
    bool once_withdraw = false;
    bool is_delay = false;
    bool withdraw = false;
    bool is_assigned = false;

    personal_profile *next_node = NULL;
    personal_profile *previous_node = NULL;
} personal_profile;

typedef struct registration_profile
{

    int64_t ID;
    int64_t *vaccination_sequence;
    int x_coordinate;
    int y_coordinate;
} registration_profile;

typedef struct inoculate_profile
{
    int64_t ID;
    int x_coordinate;
    int y_coordinate;
    int daily_processnum;

} inoculate_profile;

extern personal_profile *newprofile(personal_profile *lastnode, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID);
extern void change_risk(personal_profile *profile, int risk);
extern void change_profession(personal_profile *profile, int new_profession);
extern void registration_sequence_calculation(personal_profile *p_profile, registration_profile *r_profile);

#endif