#include <bits/stdc++.h>

using std::string;
typedef struct personal_profile

{


    string address;
    string phone;
    string WeChat;
    string email;
    int64_t ID;
    int64_t *vaccination_sequence;
    int profession; // I to VIII
    int risk;
    int agegroup; // 1-7
    int64_t birthdate;
    int64_t registrationdate;
    int64_t regID;

    personal_profile *next_node;
    personal_profile *previous_node;
}personal_profile;

typedef struct registration_profile
{


    int64_t ID;
    int64_t *vaccination_sequence;
    int x_coordinate;
    int y_coordinate;
}registration_profile;

typedef struct inoculate_profile
{
    int64_t ID;
    int x_coordinate;
    int y_coordinate;
    int daily_processnum;

}inoculate_profile;


static void newprofile(personal_profile *lastnode, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID);
static void change_risk(personal_profile *profile, int risk);
static void change_profession(personal_profile *profile, int new_profession);
static void registration_sequence_calculation(personal_profile *p_profile, registration_profile *r_profile);