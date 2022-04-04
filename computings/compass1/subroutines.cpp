#include "headers/subroutines.h"
#include "id_hash.cpp"
#include "profile.cpp"
#include "fiboheap.cpp"
using namespace std;

static int32_t date = 0;
static int64_t num_reg = 0;
static int64_t num_ino = 0;
static int64_t max_num_reg = 20;
static int64_t max_num_ino = 20;

static int64_t daily_total = 0; //the capacity of treatment from all registration points, initialized by 0

static int64_t total_reg_person = 0; //number of people that have registered
static int64_t queue_waiting = 0; //number of people who haven't been inoculated but did not send the priority letter
static int64_t assign_waiting = 0; //number of people who haven't been inoculated but have already sent the priority letter
static int64_t total_treatment = 0; //the number of processed people
static double_t aver_waiting = 0; //the average time of waiting

static int64_t *daily; //the array that contains the inoculation capacity of each inoculation point

static registration_profile **reg_pro = new registration_profile *[20];
static inoculate_profile **ino_pro = new inoculate_profile *[20];
//initialization for registration_profile and inoculate_profile

static vector<personal_profile *> queueing_personal_file; //the quene of the waiting people
static personal_profile *first_queueing_personal_file; //the beginning of the quene
static personal_profile *last_queueing_personal_file; //the end of the quene


static vector<personal_profile *> delay_personal_file;

static personal_profile *first_hrisk_personal_file; //the beginning of the high risk quene
static personal_profile *last_hrisk_personal_file; //the end of the high risk quene


static vector<personal_profile *> inoculated_personal_file; //the quene of the inoculated people
static personal_profile *first_inoculated_personal_file; //the beginning of the quene
static personal_profile *last_inoculated_personal_file; //the end of the quene



static personal_profile *first_delay_personal_file; //the beginning of thr delay list
static personal_profile *last_delay_personal_file; //the end of the delay list

static personal_profile *first_withdraw_personal_file; //the beginning of the withdrawal list
static personal_profile *last_withdraw_personal_file; //the end of withdrawal list

static vector<personal_profile *> assigned_personal_file; //the quene of the people who have written priority letter
static personal_profile *first_assigned_personal_file; //the beginning of ~
static personal_profile *last_assigned_personal_file; //the end of ~

static int64_t *dist; //the temporary distance sequence 



static hashmap<int64_t, int64_t> priority2ID = hashmap<int64_t, int64_t>(20); //hashmap from priority to ID


static hashmap<int64_t, personal_profile *> ID2ptr = hashmap<int64_t, personal_profile *>(20); //hashmap from ID to personal profile

static FibHeap *Queueing_heap = new FibHeap; //quene heap
static FibHeap *hrisk_heap = new FibHeap; //high risk heap

bool compare_by_dist(int64_t num1, int64_t num2)
{
    return dist[num1] < dist[num2];
}

bool cmp_by_name(personal_profile *file1, personal_profile *file2)
{
    return file1->email < file2->email;
}

bool cmp_by_pof(personal_profile *file1, personal_profile *file2)
{
    return file1->profession < file2->profession;
}

bool cmp_by_agegp(personal_profile *file1, personal_profile *file2)
{
    return file1->agegroup < file2->agegroup;
}
bool cmp_by_ddl(personal_profile *file1, personal_profile *file2)
{
    return file1->inoculate_date < file2->inoculate_date;
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
    ino_pro[num_ino]->daily_processnum = cap;
    daily_total += cap;
    if (num_ino >= max_num_ino)
        alloc_for_ino();
}

static void calc_reg_dist()
{
    dist = new int64_t[num_ino];
    daily = new int64_t[num_ino];
    for (int _ = 0; _ < num_reg; _++)
    {
        reg_pro[_]->vaccination_sequence = new int64_t[num_ino];
        for (int i = 0; i < num_ino; i++)
        {
            dist[i] = sqrt(pow(ino_pro[i]->x_coordinate - reg_pro[_]->x_coordinate, 2) + pow(ino_pro[i]->y_coordinate - reg_pro[_]->y_coordinate, 2));
            reg_pro[_]->vaccination_sequence[i] = ino_pro[i]->ID;
            if (_ == 0)
                daily[i] = ino_pro[i]->daily_processnum;
        }
        sort(reg_pro[_]->vaccination_sequence, reg_pro[_]->vaccination_sequence + num_ino, compare_by_dist);
    }
}
static void add_profile(string name, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, int agegroup, int64_t birthdate, int64_t RegID)
{
    int64_t pri_num;
    pri_num = profession << 40 + agegroup << 33 + date;
    if (ID2ptr.retrieve(ID) != NULL)
    {
        cout << "Already Registered!\n";
        return;
    }
    total_reg_person++;
    queue_waiting++;
    if (risk <= 2)
    {

        if (first_queueing_personal_file == NULL)
        {
            first_queueing_personal_file = newprofile(first_queueing_personal_file, name, address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, date, RegID);
            last_queueing_personal_file = first_queueing_personal_file;
        }
        else
        {
            last_queueing_personal_file = newprofile(first_queueing_personal_file, name, address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, date, RegID);
        }
        last_queueing_personal_file->priority_num = pri_num;
        registration_sequence_calculation(last_queueing_personal_file, reg_pro[RegID]);
        fib_heap_insert_key(Queueing_heap, pri_num);
        priority2ID.add(pri_num, ID);
        ID2ptr.add(ID, last_queueing_personal_file);
        queueing_personal_file.push_back(last_queueing_personal_file);
    }
    else
    {
        if (first_hrisk_personal_file == NULL)
        {
            first_hrisk_personal_file = newprofile(first_hrisk_personal_file, name, address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, date, RegID);
            last_hrisk_personal_file = first_hrisk_personal_file;
        }
        else
        {
            last_hrisk_personal_file = newprofile(first_hrisk_personal_file, name, address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, date, RegID);
        }
        last_hrisk_personal_file->priority_num = pri_num;
        registration_sequence_calculation(last_hrisk_personal_file, reg_pro[RegID]);
        fib_heap_insert_key(hrisk_heap, pri_num);
        priority2ID.add(pri_num, ID);
        ID2ptr.add(ID, last_hrisk_personal_file);
        queueing_personal_file.push_back(last_hrisk_personal_file);
    }
}

static void weekly_report(int op)
{

    switch (op)
    {
    case 0:
        sort(queueing_personal_file.begin(), queueing_personal_file.end(), cmp_by_name);
        sort(inoculated_personal_file.begin(), inoculated_personal_file.end(), cmp_by_name);
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_name);
        break;
    case 1:
        sort(queueing_personal_file.begin(), queueing_personal_file.end(), cmp_by_agegp);
        sort(inoculated_personal_file.begin(), inoculated_personal_file.end(), cmp_by_agegp);
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_agegp);
        break;
    case 2:
        sort(queueing_personal_file.begin(), queueing_personal_file.end(), cmp_by_pof);
        sort(inoculated_personal_file.begin(), inoculated_personal_file.end(), cmp_by_pof);
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_pof);
        break;
    default:
        return;
    }
    for (int _ = 0; _ < queue_waiting; _++)
    {
        cout << "\nName:" << queueing_personal_file[_]->name << "\n";
        cout << "Age group:" << queueing_personal_file[_]->agegroup << "\n";
        cout << "Profession:" << queueing_personal_file[_]->profession << "\n";
        cout << "Risk:" << queueing_personal_file[_]->risk << "\n";
        cout << "Waiting time until now:" << date - queueing_personal_file[_]->registrationdate << "\n";
    }
    for (int _ = 0; _ < assign_waiting; _++)
    {
        cout << "\nName:" << assigned_personal_file[_]->name << "\n";
        cout << "Age group:" << assigned_personal_file[_]->agegroup << "\n";
        cout << "Profession:" << assigned_personal_file[_]->profession << "\n";
        cout << "Risk:" << assigned_personal_file[_]->risk << "\n";
        cout << "Waiting time until now:" << date - assigned_personal_file[_]->registrationdate << "\n";
    }
    for (int _ = 0; _ < total_treatment; _++)
    {
        cout << "\nName: " << inoculated_personal_file[_]->name << "\n";
        cout << "Age group: " << inoculated_personal_file[_]->agegroup << "\n";
        cout << "Profession: " << inoculated_personal_file[_]->profession << "\n";
        cout << "Risk: " << inoculated_personal_file[_]->risk << "\n";
        cout << "Waiting time: " << inoculated_personal_file[_]->inoculate_date - inoculated_personal_file[_]->registrationdate << "\n";
    }
    sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_ddl);
}

static void monthly_report()
{
    cout << "\nTotal Registered: " << total_reg_person << "\n";
    cout << "Waiting in queue: " << queue_waiting << "\n";
    cout << "Waiting in total: " << assign_waiting + queue_waiting << "\n";
    cout << "Treatment appointments: " << assign_waiting << "\n";
    cout << "Withdraw: " << total_reg_person - queue_waiting - assign_waiting - total_treatment << "\n";
}

static void DDL_letter(int64_t ID, int64_t DDL)
{
    personal_profile *ptr = ID2ptr.retrieve(ID);
    if (ptr == NULL)
    {
        cout << "Fake ID!\n";
        return;
    }
    if (ptr->is_inoculated)
        return;
    if (ptr->is_assigned && DDL < ptr->inoculate_date)
    {
        ptr->inoculate_date = DDL;
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_ddl);
        return;
    }
    if (ptr->inoculate_date != -1 && !ptr->is_delay)
        return;

    if (ptr->is_delay)
    {
        for (vector<personal_profile *>::iterator i = delay_personal_file.begin(); i != delay_personal_file.end(); i++)
        {
            if (*i == ptr)
            {
                delay_personal_file.erase(i);
                break;
            }
        }
        ptr->is_delay = false;
    }
    else
    {
        int64_t prio_num = ptr->priority_num;
        fib_heap_delete(Queueing_heap, prio_num);
        if (ptr->previous_node != NULL && ptr->next_node != NULL)
        {
            ptr->inoculate_date = DDL;
            ptr->previous_node->next_node = ptr->next_node;
            ptr->next_node->previous_node = ptr->previous_node;
            ptr->previous_node = last_assigned_personal_file;
        }
        ptr->next_node = NULL;
        if (first_assigned_personal_file == NULL)
            first_assigned_personal_file = ptr;
        last_assigned_personal_file = ptr;
    }
    assigned_personal_file.push_back(ptr);
    for (vector<personal_profile *>::iterator i = queueing_personal_file.begin(); i != queueing_personal_file.end(); i++)
    {
        if (*i == ptr)
        {
            queueing_personal_file.erase(i);
            break;
        }
    }
    sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_ddl);
    queue_waiting--;
    assign_waiting++;
    ptr->is_assigned = true;
}

static void change_pro(int64_t ID, int64_t prof)
{
    personal_profile *ptr = ID2ptr.retrieve(ID);
    if (ptr == NULL)
    {
        cout << "Fake ID!\n";
        return;
    }
    if (prof == ptr->profession)
        return;
    int64_t pre_prio_num = ptr->priority_num, now_prio_num = prof << 40 + ptr->agegroup << 33 + ptr->registrationdate;
    ptr->priority_num = now_prio_num;
    ptr->profession = prof;
    priority2ID.remove(pre_prio_num);
    priority2ID.add(now_prio_num, ID);
    if (ptr->inoculate_date != -1)
        return;
    fib_heap_update(Queueing_heap, pre_prio_num, now_prio_num);
}

static void change_risks(int64_t ID, int64_t Risks)
{
    personal_profile *ptr = ID2ptr.retrieve(ID);
    if (ptr == NULL)
    {
        cout << "Fake ID!\n";
        return;
    }
    if (Risks == ptr->risk)
        return;

    if (ptr->inoculate_date != -1 && !ptr->is_delay)
    {
        ptr->risk = Risks;
        return;
    }

    if (Risks <= 2 && ptr->risk <= 2)
    {
        ptr->risk = Risks;
        return;
    }
    ptr->previous_node->next_node = ptr->next_node;
    ptr->next_node->previous_node = ptr->previous_node;
    if (Risks <= 2)
    {
        if (first_hrisk_personal_file == last_hrisk_personal_file)
        {
            first_hrisk_personal_file = NULL;
            last_hrisk_personal_file = NULL;
        }
        fib_heap_delete(hrisk_heap, ptr->priority_num);
        fib_heap_insert_key(Queueing_heap, ptr->priority_num);
        if (first_queueing_personal_file == NULL)
            first_queueing_personal_file = ptr;
        ptr->previous_node = last_queueing_personal_file;
        last_queueing_personal_file = ptr;
        ptr->next_node = NULL;
    }
    else
    {
        if (!ptr->is_delay)
        {
            fib_heap_delete(Queueing_heap, ptr->priority_num);
            fib_heap_insert_key(hrisk_heap, ptr->priority_num);
        }
        else
        {
            for (vector<personal_profile *>::iterator i = queueing_personal_file.begin(); i != queueing_personal_file.end(); i++)
            {
                if (*i == ptr)
                {
                    queueing_personal_file.erase(i);
                    break;
                }
            }
            fib_heap_insert_key(hrisk_heap, ptr->priority_num);
        }
    }
}

static void withdraw(int64_t ID)
{
    personal_profile *ptr = ID2ptr.retrieve(ID);
    if (ptr == NULL)
    {
        cout << "Fake ID!\n";
        return;
    }
    if (ptr->is_inoculated || ptr->once_withdraw)
    {
        return;
    }
    ptr->once_withdraw = true;

    if (ptr->is_delay)
    {
        for (vector<personal_profile *>::iterator i = queueing_personal_file.begin(); i != queueing_personal_file.end(); i++)
        {
            if (*i == ptr)
            {
                queueing_personal_file.erase(i);
                break;
            }
        }
        queue_waiting--;
    }
    if (ptr->risk == 3)
    {
        fib_heap_delete(hrisk_heap, ptr->priority_num);
        queue_waiting--;
    }
}

static void next_day()
{
    if (date % 7 == 6)
    {
        int op;
        cout << "plz choose the type of ordering scheme:\n";
        cout << "0. order of name\n ";
        cout << "1. order of agegroup\n";
        cout << "2. order of profession\n";
        cin >> op;
        if (op < 0 || op > 8)
        {
            cout << "plz enter a value between 0 and 2\n";
        }
        else
        {
            cout << "The following is the weekly report\n\n";
            weekly_report(op);
        }
    }
    if (date % 30 == 29)
    {
        cout << "The following is the monthly report\n\n";
        monthly_report();
    }

    date++;
}
