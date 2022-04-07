#include "headers/subroutines.h"
#include "id_hash.cpp"
#include "profile.cpp"
#include "fiboheap.cpp"
#include "headers/date.h"
using namespace std;

static int32_t date = 0;
static int64_t num_reg = 0;
static int64_t num_ino = 0;
static int64_t max_num_reg = 20;
static int64_t max_num_ino = 20;

static int64_t daily_total = 0; // the capacity of treatment from all registration points, initialized by 0

static int64_t total_reg_person = 0; // number of people that have registered
static int64_t queue_waiting = 0;    // number of people who haven't been inoculated but did not send the priority letter
static int64_t assign_waiting = 0;   // number of people who haven't been inoculated but have already sent the priority letter
static int64_t total_treatment = 0;  // the number of processed people
static double_t aver_waiting = 0;    // the average time of waiting

static int64_t *daily; // the array that contains the inoculation capacity of each inoculation point

static registration_profile **reg_pro = new registration_profile *[20];
static inoculate_profile **ino_pro = new inoculate_profile *[20];
// initialization for registration_profile and inoculate_profile

static vector<personal_profile *> queueing_personal_file; // the quene of the waiting people

static vector<personal_profile *> delay_personal_file;

static vector<personal_profile *> inoculated_personal_file; // the quene of the inoculated people

static vector<personal_profile *> withdraw_personal_file; // the quene of the inoculated people

static vector<personal_profile *> assigned_personal_file; // the quene of the people who have written priority letter

static int64_t *dist; // the temporary distance sequence

static hashmap<int64_t, int64_t> priority2ID = hashmap<int64_t, int64_t>(20); // hashmap from priority to ID

static hashmap<int64_t, personal_profile *> ID2ptr = hashmap<int64_t, personal_profile *>(20); // hashmap from ID to personal profile

static FibHeap *Queueing_heap = fib_heap_make(); // quene heap
static FibHeap *hrisk_heap = fib_heap_make();    // high risk heap

bool compare_by_dist(int64_t num1, int64_t num2)
// a subroutine for comparation between distance for num1 and num2, return 1 if distance for num1 is the smaller one
{
    return dist[num1] < dist[num2];
}

bool cmp_by_name(personal_profile *file1, personal_profile *file2)
// a subroutine for comparation by email address
{
    return file1->name < file2->name;
}

bool cmp_by_pof(personal_profile *file1, personal_profile *file2)
// a subroutine for comparation by profession
{
    return file1->profession < file2->profession;
}

bool cmp_by_agegp(personal_profile *file1, personal_profile *file2)
// a subroutine for comparation by agegroup
{
    return file1->agegroup < file2->agegroup;
}

bool cmp_by_ddl(personal_profile *file1, personal_profile *file2)
// a subroutine for comparation by inoculation date
{
    return file1->inoculate_date < file2->inoculate_date;
}

void alloc_for_reg()
// reallocate for larger memory space to contain registration profile
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
/// reallocate for larger memory space to contain inoculation profile
{
    max_num_ino *= 2;
    inoculate_profile **new_ino = new inoculate_profile *[max_num_ino];
    for (int _ = 0; _ < num_ino; _++)
    {
        new_ino[_] = ino_pro[_];
    }
    ino_pro = new_ino;
}

static void reg_reg(int64_t x, int64_t y)   // register a new registration point to the registration profile list
{
    reg_pro[num_reg] = new registration_profile;
    reg_pro[num_reg]->x_coordinate = x;
    reg_pro[num_reg]->y_coordinate = y;
    reg_pro[num_reg]->ID = num_reg;
    num_reg++;
    if (num_reg >= max_num_reg) // reallocate if running out of allocated memory
        alloc_for_reg();
}

static void reg_ino(int64_t x, int64_t y, int cap)  // register a new inoculation point to the inoculation profile list
{
    ino_pro[num_ino] = new inoculate_profile;
    ino_pro[num_ino]->x_coordinate = x;
    ino_pro[num_ino]->y_coordinate = y;
    ino_pro[num_ino]->ID = num_ino;
    ino_pro[num_ino]->daily_processnum = cap;
    num_ino++;
    daily_total += cap;
    if (num_ino >= max_num_ino)
        alloc_for_ino(); // reallocate if more memory space is required
}

static void calc_reg_dist() // calculate the distance between each registration point and inoculation points
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
    pri_num = profession;
    pri_num <<= 5;
    pri_num += agegroup;
    pri_num <<= 25;
    pri_num += date;
    pri_num <<= 20;
    pri_num += total_reg_person;
    if (ID2ptr.retrieve(ID) != NULL)
    {
        cout << "Already Registered!\n";
        return;
    }
    total_reg_person++;
    queue_waiting++;
    personal_profile *my_personal_file;
    my_personal_file = newprofile(name, address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, date, RegID);
    my_personal_file->priority_num = pri_num;
    registration_sequence_calculation(my_personal_file, reg_pro[RegID]);
    priority2ID.add(pri_num, ID);
    ID2ptr.add(ID, my_personal_file);
    queueing_personal_file.push_back(my_personal_file);
    if (risk <= 2)
    {
        fib_heap_insert_key(Queueing_heap, pri_num);
    }
    else
    {
        fib_heap_insert_key(hrisk_heap, pri_num);
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
    cout << "Queue Waiting: \n";
    for (int _ = 0; _ < queue_waiting; _++)
    {
        cout << "\nName:" << queueing_personal_file[_]->name << "\n";
        cout << "Age group:" << queueing_personal_file[_]->agegroup << "\n";
        cout << "Profession:" << queueing_personal_file[_]->profession << "\n";
        cout << "Risk:" << queueing_personal_file[_]->risk << "\n";
        cout << "Waiting time until now:" << date - queueing_personal_file[_]->registrationdate << "\n";
    }
    cout << "\nAssigned Waiting: \n";
    for (int _ = 0; _ < assign_waiting; _++)
    {
        cout << "\nName:" << assigned_personal_file[_]->name << "\n";
        cout << "Age group:" << assigned_personal_file[_]->agegroup << "\n";
        cout << "Profession:" << assigned_personal_file[_]->profession << "\n";
        cout << "Risk:" << assigned_personal_file[_]->risk << "\n";
        cout << "Waiting time until now:" << date - assigned_personal_file[_]->registrationdate << "\n";
    }
    cout << "\nTreatment: \n";
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
    else if (ptr->is_assigned)
    {
        return;
    }
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
    else if (ptr->withdraw)
    {
        for (vector<personal_profile *>::iterator i = withdraw_personal_file.begin(); i != withdraw_personal_file.end(); i++)
        {
            if (*i == ptr)
            {
                withdraw_personal_file.erase(i);
                break;
            }
        }
    }
    else
    {
        int64_t prio_num = ptr->priority_num;
        if (ptr->risk != 3)
            fib_heap_delete(Queueing_heap, prio_num);
        else
            fib_heap_delete(hrisk_heap, ptr->priority_num);

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
    assigned_personal_file.push_back(ptr);
    sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_ddl);
    assign_waiting++;
    ptr->is_assigned = true;
    ptr->is_inoculated = false;
    ptr->once_withdraw = false;
    ptr->is_delay = false;
    ptr->withdraw = false;
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
    int64_t pre_prio_num = ptr->priority_num, now_prio_num = prof << 50 + ptr->agegroup << 45 + ptr->registrationdate << 20 + total_reg_person;
    ptr->priority_num = now_prio_num;
    ptr->profession = prof;
    priority2ID.remove(pre_prio_num);
    priority2ID.add(now_prio_num, ID);
    if (ptr->is_delay || ptr->withdraw || ptr->is_inoculated || ptr->is_assigned)
        return;
    if (ptr->risk != 3)
        fib_heap_update(Queueing_heap, pre_prio_num, now_prio_num);
    else
        fib_heap_update(hrisk_heap, pre_prio_num, now_prio_num);
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

    if (ptr->is_assigned || ptr->withdraw || ptr->is_inoculated)
    {
        ptr->risk = Risks;
        return;
    }

    if (Risks <= 2 && ptr->risk <= 2)
    {
        ptr->risk = Risks;
        return;
    }
    if (Risks <= 2)
    {
        fib_heap_delete(hrisk_heap, ptr->priority_num);
        fib_heap_insert_key(Queueing_heap, ptr->priority_num);
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
            for (vector<personal_profile *>::iterator i = delay_personal_file.begin(); i != delay_personal_file.end(); i++)
            {
                if (*i == ptr)
                {
                    delay_personal_file.erase(i);
                    break;
                }
            }
            ptr->is_delay = false;
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
    if (ptr->is_inoculated || ptr->withdraw)
    {
        return;
    }
    if (ptr->is_assigned)
    {
        for (vector<personal_profile *>::iterator i = assigned_personal_file.begin(); i != assigned_personal_file.end(); i++)
        {
            if (*i == ptr)
            {
                assigned_personal_file.erase(i);
                break;
            }
        }
        assign_waiting--;
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
        }
        else if (ptr->risk == 3)
        {
            fib_heap_delete(hrisk_heap, ptr->priority_num);
        }
        else
        {
            fib_heap_delete(Queueing_heap, ptr->priority_num);
        }
        queue_waiting--;
    }
    withdraw_personal_file.push_back(ptr);
    ptr->is_assigned = false;
    ptr->once_withdraw = false;
    ptr->is_delay = false;
    ptr->withdraw = true;
}

// cancel_withdraw(ID)
static void cancel_withdraw(int64_t ID)
{
    personal_profile *ptr = ID2ptr.retrieve(ID);
    if (ptr == NULL)
    {
        cout << "Fake ID!\n";
        return;
    }
    if (ptr->is_inoculated || !ptr->withdraw)
    {
        return;
    }
    queue_waiting++;
    for(vector<personal_profile *>::iterator i = withdraw_personal_file.begin(); i != withdraw_personal_file.end(); i++)
    {
        if (*i == ptr)
        {
            withdraw_personal_file.erase(i);
            break;
        }
    }
    ptr->is_assigned = false;
    ptr->once_withdraw = true;
    ptr->is_delay = false;
    ptr->withdraw = false;
    queueing_personal_file.push_back(ptr);
    if (ptr->risk <= 2)
    {
        fib_heap_insert_key(Queueing_heap, ptr->priority_num);
    }
    else
    {
        fib_heap_insert_key(hrisk_heap, ptr->priority_num);
    }
}

void treat_assigned(int64_t *copy_daily, int64_t *copy_total)
{
    vector<personal_profile *>::iterator i = assigned_personal_file.begin();
    personal_profile *ptr;
    int64_t ino_id = 0;
    while ((*copy_total) > 0 && !assigned_personal_file.empty())
    {
        ptr = *i;
        ptr->is_inoculated = true;
        ptr->is_assigned = false;
        ptr->once_withdraw = false;
        ptr->is_delay = false;
        ptr->withdraw = false;
        ptr->inoculate_date = date;
        while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
        {
            ino_id++;
        }
        copy_daily[ptr->vaccination_sequence[ino_id]]--;
        ptr->inoID = ptr->vaccination_sequence[ino_id];
        (*copy_total)--;
        assign_waiting--;
        aver_waiting = (aver_waiting * total_treatment + date - ptr->registrationdate) / (total_treatment + 1);
        total_treatment++;
        i = assigned_personal_file.erase(i);
        inoculated_personal_file.push_back(ptr);
    }
}

void treat_queue(int64_t *copy_daily, int64_t *copy_total)
{
    vector<personal_profile *>::iterator i = queueing_personal_file.begin();
    int64_t ino_id = 0;
    personal_profile *ptr;
    int64_t *prio_num = new int64_t, id;
    while (*copy_total >= 0 && fib_heap_get_min(Queueing_heap, prio_num))
    {
        fib_heap_extract_min(Queueing_heap);
        id = priority2ID.retrieve(*prio_num);
        ptr = ID2ptr.retrieve(id);
        if (ptr->risk <= 1 && ptr->once_withdraw == false)
        {
            ptr->is_inoculated = true;
            ptr->is_assigned = false;
            ptr->once_withdraw = false;
            ptr->is_delay = false;
            ptr->withdraw = false;
            ptr->inoculate_date = date;
            while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
            {
                ino_id++;
            }
            copy_daily[ptr->vaccination_sequence[ino_id]]--;
            ptr->inoID = ptr->vaccination_sequence[ino_id];
            (*copy_total)--;
            queue_waiting--;
            aver_waiting = (aver_waiting * total_treatment + date - ptr->registrationdate) / (total_treatment + 1);
            total_treatment++;
            while (*i != ptr)
            {
                i++;
            }
            queueing_personal_file.erase(i);
            i = queueing_personal_file.begin();
            inoculated_personal_file.push_back(ptr);
        }
        else
        {
            ptr->is_inoculated = false;
            ptr->is_assigned = false;
            ptr->is_delay = true;
            ptr->withdraw = false;
            int64_t delay = date;
            if (ptr->risk == 2)
            {
                delay += 30;
            }
            else
            {
                delay += 14;
            }
            ptr->inoculate_date = delay;
            delay_personal_file.push_back(ptr);
            sort(delay_personal_file.begin(), delay_personal_file.end(), cmp_by_ddl);
        }
    }
}
void treat_delay(int64_t *copy_daily, int64_t *copy_total)
{
    vector<personal_profile *>::iterator i = queueing_personal_file.begin();
    vector<personal_profile *>::iterator i_d = delay_personal_file.begin();
    personal_profile *ptr;
    int64_t ino_id = 0;
    while ((*copy_total) > 0 && !delay_personal_file.empty() && (*i_d)->inoculate_date <= date)
    {
        ptr = *i_d;
        ptr->is_inoculated = true;
        ptr->is_assigned = false;
        ptr->once_withdraw = false;
        ptr->is_delay = false;
        ptr->withdraw = false;
        ptr->inoculate_date = date;
        while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
        {
            ino_id++;
        }
        copy_daily[ptr->vaccination_sequence[ino_id]]--;
        ptr->inoID = ptr->vaccination_sequence[ino_id];
        (*copy_total)--;
        queue_waiting--;
        aver_waiting = (aver_waiting * total_treatment + date - ptr->registrationdate) / (total_treatment + 1);
        total_treatment++;
        i_d = delay_personal_file.erase(i_d);
        while (*i != ptr)
        {
            i++;
        }
        queueing_personal_file.erase(i);
        i = queueing_personal_file.begin();
        inoculated_personal_file.push_back(ptr);
    }
}

void treat_hrisk(int64_t *copy_daily, int64_t *copy_total)
{
    if (!delay_personal_file.empty())
    {
        return;
    }
    vector<personal_profile *>::iterator i = queueing_personal_file.begin();
    int64_t ino_id = 0;
    personal_profile *ptr;
    int64_t *prio_num = new int64_t, id;
    while ((*copy_total) >= 0 && fib_heap_get_min(hrisk_heap, prio_num))
    {
        fib_heap_extract_min(hrisk_heap);
        id = priority2ID.retrieve(*prio_num);
        ptr = ID2ptr.retrieve(id);

        ptr->is_inoculated = true;
        ptr->is_assigned = false;
        ptr->once_withdraw = false;
        ptr->is_delay = false;
        ptr->withdraw = false;
        ptr->inoculate_date = date;
        while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
        {
            ino_id++;
        }
        copy_daily[ptr->vaccination_sequence[ino_id]]--;
        ptr->inoID = ptr->vaccination_sequence[ino_id];
        (*copy_total)--;
        queue_waiting--;
        aver_waiting = (aver_waiting * total_treatment + date - ptr->registrationdate) / (total_treatment + 1);
        total_treatment++;
        while (*i != ptr)
        {
            i++;
        }
        queueing_personal_file.erase(i);
        i = queueing_personal_file.begin();
        inoculated_personal_file.push_back(ptr);
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
        while (op < 0 || op > 2)
        {
            cout << "plz enter a value between 0 and 2\n";
            cin >> op;
        }
        cout << "The following is the weekly report\n\n";
        weekly_report(op);
    }
    if (date % 30 == 29)
    {
        cout << "The following is the monthly report\n\n";
        monthly_report();
    }
    int64_t copy_daily[num_ino];
    int64_t *copy_total = new int64_t;
    *copy_total = daily_total;
    memcpy(copy_daily, daily, num_ino * sizeof(int64_t));
    treat_assigned(copy_daily, copy_total);
    treat_queue(copy_daily, copy_total);
    treat_delay(copy_daily, copy_total);
    treat_hrisk(copy_daily, copy_total);
    date++;
}
