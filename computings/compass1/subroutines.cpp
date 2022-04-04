#include "headers/subroutines.h"

int64_t num_reg = 0;
int64_t num_ino = 0;
int64_t max_num_reg = 20;
int64_t max_num_ino = 20;
registration_profile **reg_pro = new registration_profile *[20];
inoculate_profile **ino_pro = new inoculate_profile *[20];

void alloc_for_reg()
{
    max_num_reg *= 2;
    registration_profile **new_reg = new registration_profile *[max_num_reg];
    for (int _ = 0; _ < num_reg; _++)
    {
        new_reg[_] = reg_pro[_];
    }
    reg_pro = new_reg;
}

void alloc_for_ino()
{
    max_num_ino *= 2;
    inoculate_profile **new_ino = new inoculate_profile *[max_num_ino];
    for (int _ = 0; _ < num_ino; _++)
    {
        new_ino[_] = ino_pro[_];
    }
    ino_pro = new_ino;
}

static void reg_reg(int64_t x, int64_t y)
{
    reg_pro[num_reg] = new registration_profile;
    reg_pro[num_reg]->x_coordinate = x;
    reg_pro[num_reg]->y_coordinate = y;
    num_reg++;
    if (num_reg >= max_num_reg)
        alloc_for_reg();
}

static void reg_ino(int64_t x, int64_t y, int cap)
{
    ino_pro[num_ino] = new inoculate_profile;
    ino_pro[num_ino]->x_coordinate = x;
    ino_pro[num_ino]->y_coordinate = y;
    num_ino++;
    if (num_ino >= max_num_ino)
        alloc_for_ino();
}

static void add_profile(string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID) {}

static void calc_reg_dist() {}

static void report() {}

static void DDL_letter(int64_t ID, int64_t DDL) {}

static void next_day() {}

static void change_pro(int64_t ID, int64_t prof) {}

static void change_risks(int64_t ID, int64_t Risks) {}