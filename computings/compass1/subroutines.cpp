#include "headers/subroutines.h"

int64_t num_reg = 0;
int64_t num_ino = 0;
int64_t max_num_reg = 20;
int64_t max_num_ino = 20;
registration_profile *reg_pro = new registration_profile[20];
inoculate_profile *ino_pro = new inoculate_profile[20];

void alloc_for_reg()
{
    max_num_reg *= 2;
    registration_profile *new_reg = new registration_profile[max_num_reg];
    for (int _ = 0; _ < num_reg; _++)
    {
        new_reg[_] = reg_pro[_];
    }
    reg_pro = new_reg;
}

void alloc_for_ino()
{
    
}

static void reg_reg(int64_t x, int64_t y)
{
}

static void reg_ino(int64_t x, int64_t y, int cap) {}

static void add_profile(string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID) {}

static void calc_reg_dist() {}

static void report() {}

static void DDL_letter(int64_t ID, int64_t DDL) {}

static void next_day() {}

static void change_pro(int64_t ID, int64_t prof) {}

static void change_risks(int64_t ID, int64_t Risks) {}