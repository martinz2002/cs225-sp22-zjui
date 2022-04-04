#include <bits/stdc++.h>
using namespace std;
struct personal_profile
{
public:
    personal_profile();
    ~personal_profile();

public:
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

public:
    personal_profile *next_node;
    personal_profile *previous_node;
};

struct registration_profile
{
public:
    registration_profile();
    ~registration_profile();

public:
    int64_t ID;
    int64_t *vaccination_sequence;
    int x_coordinate;
    int y_coordinate;
};

struct inoculate_profile
{
public:
    inoculate_profile();
    ~inoculate_profile();

public:
    int64_t ID;
    int x_coordinate;
    int y_coordinate;
    int daily_processnum;
};

static void newprofile(personal_profile *lastnode, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID);
static void change_risk(personal_profile *profile, int risk);
static void change_profession(personal_profile *profile, int new_profession);
static void registration_sequence_calculation(personal_profile *p_profile, registration_profile *r_profile);