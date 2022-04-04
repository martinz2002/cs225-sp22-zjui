#include "headers/profile.h"
using std::string;
static personal_profile* newprofile(personal_profile *lastnode, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID)
{
    personal_profile *new_profile = new personal_profile;
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
    new_profile->risk = risk;
    new_profile->regID = RegID;
    new_profile->previous_node = lastnode;
    if (lastnode != NULL)
        lastnode->next_node = new_profile;
    return new_profile;
}



static void change_profession(personal_profile *profile, int new_profession)
{
    profile->profession = new_profession;
}

static void change_risk(personal_profile *profile, int risk)
{
    profile->risk = risk;
}

static void registration_sequence_calculation(personal_profile *p_profile, registration_profile *r_profile)
{
    p_profile->vaccination_sequence = r_profile->vaccination_sequence;
}