#include "headers/profile.h"
void add_profile(profile *lastnode, char *address, char *phone, char *WeChat, char *email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate)
{
    profile *new_profile = new profile;
    new_profile->ID = ID;
    new_profile->address = address;
    new_profile->agegroup = agegroup;
    new_profile->birthdate = birthdate;
    new_profile->profession = profession;
    new_profile->registrationdate = registrationdate;
    new_profile->email = email;
    new_profile->next_node = NULL;
    new_profile->phone = phone;
    new_profile->WeChat = WeChat;
    new_profile->previous_node = lastnode;
    lastnode->next_node = newprofile;
    new_profile->risk = risk;
}

void change_profession(profile *profile, int new_profession)
{
    profile->profession = new_profession;
}

void change_risk(profile *profile, int risk)
{
    profile->risk = risk;
}

void registration_sequence_calculation(profile *profile)
{
}