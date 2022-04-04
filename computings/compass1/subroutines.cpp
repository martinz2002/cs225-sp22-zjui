#include "headers/subroutines.h"

static int64_t date = 0;
int64_t num_reg = 0;
int64_t num_ino = 0;
int64_t max_num_reg = 20;
int64_t max_num_ino = 20;
registration_profile **reg_pro = new registration_profile *[20];
inoculate_profile **ino_pro = new inoculate_profile *[20];

personal_profile *first_personal_file;
personal_profile *last_personal_file;

int64_t *dist;

using std::pow;
using std::sort;
using std::sqrt;

bool compare(int64_t num1, int64_t num2)
{
    return dist[num1] > dist[num2];
}

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
    reg_pro[num_reg]->ID = num_reg;
    if (num_reg >= max_num_reg)
        alloc_for_reg();
}

static void reg_ino(int64_t x, int64_t y, int cap)
{
    ino_pro[num_ino] = new inoculate_profile;
    ino_pro[num_ino]->x_coordinate = x;
    ino_pro[num_ino]->y_coordinate = y;
    num_ino++;
    ino_pro[num_ino]->ID = num_ino;
    if (num_ino >= max_num_ino)
        alloc_for_ino();
}

static void calc_reg_dist()
{
    dist = new int64_t[num_ino];
    for (int _ = 0; _ < num_reg; _++)
    {
        reg_pro[_]->vaccination_sequence = new int64_t[num_ino];
        for (int i = 0; i < num_ino; i++)
        {
            dist[i] = sqrt(pow(ino_pro[i]->x_coordinate - reg_pro[_]->x_coordinate, 2) + pow(ino_pro[i]->y_coordinate - reg_pro[_]->y_coordinate, 2));
            reg_pro[_]->vaccination_sequence[i] = ino_pro[i]->ID;
        }
        sort(reg_pro[_]->vaccination_sequence, reg_pro[_]->vaccination_sequence + num_ino, compare);
    }
}
static void add_profile(string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t RegID)
{
    if (first_personal_file == NULL)
    {
        first_personal_file = newprofile(first_personal_file, address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, date, RegID);
        last_personal_file = first_personal_file;
    }
    else
    {
        last_personal_file = newprofile(first_personal_file, address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, date, RegID);
    }
    registration_sequence_calculation(last_personal_file, reg_pro[RegID]);
}

static void report() {}

static void DDL_letter(int64_t ID, int64_t DDL) {}

static void next_day() {}

static void change_pro(int64_t ID, int64_t prof) {}

static void change_risks(int64_t ID, int64_t Risks) {}