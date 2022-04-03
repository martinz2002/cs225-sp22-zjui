#include <bits/stdc++.h>
template <>
class profile
{
public:
    profile();
    ~profile();

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
    profile *next_node;
    profile *previous_node;
}