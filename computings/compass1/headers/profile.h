#include <bits/stdc++.h>
struct personal_profile
{
public:
    personal_profile();
    ~personal_profile();

public:
    char *address = new char[256];
    char *phone = new char[256];
    char *WeChat = new char[256];
    char *email = new char[256];
    int64_t ID;
    int64_t *vaccination_sequence;
    int profession; // I to VIII
    int risk;
    int agegroup; // 1-7
    int64_t birthdate;
    int64_t registrationdate;

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

public:
    inoculate_profile *next_node;
    inoculate_profile *previous_node;
};
