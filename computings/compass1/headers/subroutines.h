#include "fiboheap.h"
#include "id_hash.h"
#include "profile.h"

using std::string;

static void reg_reg(int64_t x,int64_t y);

static void reg_ino(int64_t x,int64_t y,int cap);

static void add_profile(string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t registrationdate, int64_t RegID);