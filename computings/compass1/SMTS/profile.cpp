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


/**
 * @brief newprofile: Create a profile for a patient
 * 
 * @param name 
 * @param address 
 * @param phone 
 * @param WeChat 
 * @param email 
 * @param risk 
 * @param ID 
 * @param profession 
 * @param agegroup 
 * @param birthdate 
 * @param registrationdate 
 * @param RegID 
 * @return personal_profile* 
 */
extern personal_profile *newprofile(string name, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, CDate *birthdate, CDate registrationdate, int64_t RegID)
{
    personal_profile *new_profile = new personal_profile;
    new_profile->name = name;
    new_profile->ID = ID;
    new_profile->address = address;
    new_profile->agegroup = agegroup;
    new_profile->birthday = birthdate;
    new_profile->profession = profession;
    new_profile->registrationdate = registrationdate;
    new_profile->email = email;
    new_profile->phone = phone;
    new_profile->WeChat = WeChat;
    new_profile->risk = risk;
    new_profile->regID = RegID;
    return new_profile;
}


/**
 * @brief change_profession: Change the profession of a patient
 * 
 * @param profile 
 * @param new_profession 
 */
extern void change_profession(personal_profile *profile, int new_profession)
{
    profile->profession = new_profession;
}


/**
 * @brief change_risk: Change the risk level of a patient
 * 
 * @param profile 
 * @param risk 
 */
extern void change_risk(personal_profile *profile, int risk)
{
    profile->risk = risk;
}


/**
 * @brief registration_sequence_calculation: calculate the registration sequence
 * 
 * @param p_profile 
 * @param r_profile 
 */
extern void registration_sequence_calculation(personal_profile *p_profile, registration_profile *r_profile)
{
    p_profile->vaccination_sequence = r_profile->vaccination_sequence;
}

