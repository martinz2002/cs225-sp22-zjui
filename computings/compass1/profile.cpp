/**
 * @file profile.cpp
 * @author Jiang Wenhan
 * @brief The data structure for patients' profiles.
 * @date 2022-04-05
 *
 * @copyright Copyright (c) 2022 Zhejiang University
 *
 */

#include "headers/profile.h"
using std::string;
extern personal_profile *newprofile(string name, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID)
{
    personal_profile *new_profile = new personal_profile;
    new_profile->name = name;
    new_profile->ID = ID;
    new_profile->address = address;
    new_profile->agegroup = agegroup;
    new_profile->birthdate = birthdate;
    new_profile->profession = profession;
    new_profile->registrationdate = registrationdate;
    new_profile->email = email;
    new_profile->phone = phone;
    new_profile->WeChat = WeChat;
    new_profile->risk = risk;
    new_profile->regID = RegID;
    return new_profile;
}

extern void change_profession(personal_profile *profile, int new_profession)
{
    profile->profession = new_profession;
}

extern void change_risk(personal_profile *profile, int risk)
{
    profile->risk = risk;
}

extern void registration_sequence_calculation(personal_profile *p_profile, registration_profile *r_profile)
{
    p_profile->vaccination_sequence = r_profile->vaccination_sequence;
}

