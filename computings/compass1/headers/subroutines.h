#ifndef SUB_R
#define SUB_R
#include<bits/stdc++.h>

using std::string;

static void reg_reg(int64_t x, int64_t y);

static void reg_ino(int64_t x, int64_t y, int cap);

static void add_profile(string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t RegID);

static void calc_reg_dist();

static void report();

static void DDL_letter(int64_t ID, int64_t DDL);

static void next_day();

static void change_pro(int64_t ID, int64_t prof);

static void change_risks(int64_t ID, int64_t Risks);
#endif