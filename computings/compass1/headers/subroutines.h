#include "fiboheap.h"
#include "id_hash.h"
#include "profile.h"

static void reg_reg(int64_t x,int64_t y);

static void reg_ino(int64_t x,int64_t y,int cap);

static void add_profile(char *address, char *phone, char *WeChat, char *email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID);