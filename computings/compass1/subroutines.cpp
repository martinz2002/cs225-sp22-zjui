#include "headers/subroutines.h"
#include "id_hash.cpp"
#include "profile.cpp"
#include "fiboheap.cpp"
using namespace std;

// static int32_t date = 0;
static CDate *date = new CDate(time(NULL));       // Current date being processed by the system
static CDate *first_date = new CDate(time(NULL)); // Date of the first run of the program
static int64_t num_reg = 0;                       // Number of registration points
static int64_t num_ino = 0;                       // Number of inoculation points
static int64_t max_num_reg = 20;                  // Maximum Number of registration points
static int64_t max_num_ino = 20;                  // Maximum Number of inoculation points

static int64_t daily_total = 0; // the capacity of treatment from all registration points, initialized by 0

static int64_t total_reg_person = 0; // number of people that have registered
static int64_t queue_waiting = 0;    // number of people who haven't been inoculated but did not send the priority letter
static int64_t assign_waiting = 0;   // number of people who haven't been inoculated but have already sent the priority letter
static int64_t total_treatment = 0;  // the number of processed people
static double_t aver_waiting = 0;    // the average time of waiting

static int64_t *daily; // the array that contains the inoculation capacity of each inoculation point

static registration_profile **reg_pro = new registration_profile *[max_num_reg]; // pointing to a list of registration pts profile
static inoculate_profile **ino_pro = new inoculate_profile *[max_num_ino];       // pointing to a list of inoculation pts profile
// initialization for registration_profile and inoculate_profile

static vector<personal_profile *> queueing_personal_file; // the queue of the waiting people

static vector<personal_profile *> delay_personal_file; // the queue of the patient

static vector<personal_profile *> inoculated_personal_file; // the queue of the inoculated people

static vector<personal_profile *> withdraw_personal_file; // the queue of the inoculated people

static vector<personal_profile *> assigned_personal_file; // the queue of the people who have written priority letter

static int64_t *dist; // the temporary distance sequence

static hashmap<int64_t, int64_t> priority2ID = hashmap<int64_t, int64_t>(20); // hashmap from priority to ID

static hashmap<int64_t, personal_profile *> ID2ptr = hashmap<int64_t, personal_profile *>(20); // hashmap from ID to personal profile

static FibHeap *Queueing_heap = fib_heap_make(); // queuing heap; containing risk level 0, 1, and 2
                                                 // when popping risk 2 patients will be pushed back to delay_personal_file
static FibHeap *hrisk_heap = fib_heap_make();    // high risk (3) heap

/**
 * @brief a subroutine for comparation between distance for num1 and num2, return 1 if distance for num1 is the smaller one
 * 
 * @param num1 id of the first location index
 * @param num2 id of the second location index
 * @return true dist[num1] < dist[num2]
 * @return false dist[num1] >= dist[num2]
 */
bool compare_by_dist(int64_t num1, int64_t num2)
{
    return dist[num1] < dist[num2];
}

/**
 * @brief a subroutine for comparation by email address
 * 
 * @param file1 
 * @param file2 
 * @return true 
 * @return false 
 */
bool cmp_by_name(personal_profile *file1, personal_profile *file2)
{
    return file1->name < file2->name;
}


/**
 * @brief a subroutine for comparation by profession
 * 
 * @param file1 
 * @param file2 
 * @return true 
 * @return false 
 */
bool cmp_by_pof(personal_profile *file1, personal_profile *file2)
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
    return (file1->inoculate_date - file2->inoculate_date) < 0;
}

void alloc_for_reg()
// reallocate for larger memory space to contain registration profile
{
    max_num_reg *= 2;// double the size of the array
    registration_profile **new_reg = new registration_profile *[max_num_reg];
    for (int _ = 0; _ < num_reg; _++)// copy the old array to the new array
    {
        new_reg[_] = reg_pro[_];
    }
    reg_pro = new_reg;// update the pointer
}

void alloc_for_ino()
/// reallocate for larger memory space to contain inoculation profile
{
    max_num_ino *= 2;// double the size of the array
    inoculate_profile **new_ino = new inoculate_profile *[max_num_ino];// allocate new memory space
    for (int _ = 0; _ < num_ino; _++)// copy the old array to the new array
    {
        new_ino[_] = ino_pro[_];
    }
    ino_pro = new_ino;// update the pointer
}

static void reg_reg(int64_t x, int64_t y) // register a new registration point to the registration profile list
{
    reg_pro[num_reg] = new registration_profile;// allocate new memory space
    reg_pro[num_reg]->x_coordinate = x;// update the x coordinate
    reg_pro[num_reg]->y_coordinate = y;// update the y coordinate
    reg_pro[num_reg]->ID = num_reg;// update the ID
    num_reg++;// update the number of registration points
    if (num_reg >= max_num_reg) // reallocate if running out of allocated memory
        alloc_for_reg();
}

static void reg_ino(int64_t x, int64_t y, int cap) // register a new inoculation point to the inoculation profile list
{
    ino_pro[num_ino] = new inoculate_profile;// allocate new memory space
    ino_pro[num_ino]->x_coordinate = x;// update the x coordinate
    ino_pro[num_ino]->y_coordinate = y;// update the y coordinate
    ino_pro[num_ino]->ID = num_ino;// update the ID
    ino_pro[num_ino]->daily_processnum = cap;// update the daily process number
    num_ino++;// update the number of inoculation points
    daily_total += cap;// update the total number of capacity
    if (num_ino >= max_num_ino)
        alloc_for_ino(); // reallocate if more memory space is required
}

static void calc_reg_dist() // calculate the distance between each registration point and inoculation points
{
    dist = new int64_t[num_ino];// allocate new memory space
    daily = new int64_t[num_ino];// allocate new memory space
    for (int _ = 0; _ < num_reg; _++)// calculate the distance between each registration point and inoculation points
    {
        reg_pro[_]->vaccination_sequence = new int64_t[num_ino];// allocate new memory space
        for (int i = 0; i < num_ino; i++)// calculate the distance between each registration point and inoculation points
        {
            dist[i] = sqrt(pow(ino_pro[i]->x_coordinate - reg_pro[_]->x_coordinate, 2) + pow(ino_pro[i]->y_coordinate - reg_pro[_]->y_coordinate, 2));// calculate the distance
            reg_pro[_]->vaccination_sequence[i] = ino_pro[i]->ID;// update the vaccination sequence
            if (_ == 0)// update the daily process number
                daily[i] = ino_pro[i]->daily_processnum;
        }
        sort(reg_pro[_]->vaccination_sequence, reg_pro[_]->vaccination_sequence + num_ino, compare_by_dist);// sort the vaccination sequence by distance between registration point and inoculation point
    }
}
static int calc_agegroup(CDate *birthdate)
{
    int64_t dateDiff = date->year - birthdate->year;
    if ((*date) - (*birthdate) < 0)// if the current date is earlier than the birthdate
    {
        return -1; // Exit
    }
    else if (dateDiff <= 12) // Age Group I
    {
        return 1;
    }
    else if (dateDiff <= 18) // Age Group II
    {
        return 2;
    }
    else if (dateDiff <= 35) // Age Group III
    {
        return 3;
    }
    else if (dateDiff <= 50) // Age Group IV
    {
        return 4;
    }
    else if (dateDiff <= 65) // Age Group V
    {
        return 5;
    }
    else if (dateDiff <= 75) // Age Group VI
    {
        return 6;
    }
    else // Age Group VII
    {
        return 7;
    }
}
static void add_profile(string name, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, string birthdate, int64_t RegID)
{
    CDate *dateBirthdate = new CDate();// allocate new memory space
    if (!dateBirthdate->set(birthdate))// if the birthdate is invalid
    {
        cout << "Invalid birthday format. Use \'yyyy-mm-dd\'." << endl;// print error message
        return;
    }
    int agegroup = calc_agegroup(dateBirthdate);// calculate the agegroup
    if (agegroup == -1) // Invalid birthdate
    {
        cout << "Invalid birthday. (Not born yet) Today is ";// print error message
        (*date).print();// print the current date
        delete dateBirthdate;// free the memory space
        return;
    }
    int64_t pri_num;
    pri_num = profession;
    pri_num <<= 5;
    pri_num += agegroup;
    pri_num <<= 25;
    pri_num += (*date) - (*first_date);
    pri_num <<= 20;
    pri_num += total_reg_person;
    if (ID2ptr.retrieve(ID) != NULL)// if the ID is already in the database
    {
        cout << "The ID is already in the database." << endl;// print error message
        delete dateBirthdate;// free the memory space
        return;
    }
    total_reg_person++;// update the total number of registered people
    queue_waiting++;// update the number of people waiting for registration
    personal_profile *my_personal_file;
    my_personal_file = newprofile(name, address, phone, WeChat, email, risk, ID, profession, agegroup, dateBirthdate, *date, RegID);
    my_personal_file->priority_num = pri_num;// update the priority number
    registration_sequence_calculation(my_personal_file, reg_pro[RegID]);
    priority2ID.add(pri_num, ID);// update the priority number to ID mapping
    ID2ptr.add(ID, my_personal_file);// update the ID to pointer mapping
    queueing_personal_file.push_back(my_personal_file);// update the queueing list
    if (risk <= 2)
    {
        fib_heap_insert_key(Queueing_heap, pri_num);// update the queueing heap
    }
    else
    {
        fib_heap_insert_key(hrisk_heap, pri_num);// update the high risk queueing heap
    }
}

static void weekly_report(int op)
{

    switch (op)
    {
    case 0:
        sort(queueing_personal_file.begin(), queueing_personal_file.end(), cmp_by_name);// sort the queueing list by name
        sort(inoculated_personal_file.begin(), inoculated_personal_file.end(), cmp_by_name);// sort the inoculated list by name
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_name);// sort the assigned list by name
        break;
    case 1:
        sort(queueing_personal_file.begin(), queueing_personal_file.end(), cmp_by_agegp);// sort the queueing list by age group
        sort(inoculated_personal_file.begin(), inoculated_personal_file.end(), cmp_by_agegp);// sort the inoculated list by age group
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_agegp);// sort the assigned list by age group
        break;
    case 2:
        sort(queueing_personal_file.begin(), queueing_personal_file.end(), cmp_by_pof);// sort the queueing list by profession
        sort(inoculated_personal_file.begin(), inoculated_personal_file.end(), cmp_by_pof);// sort the inoculated list by profession
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_pof);// sort the assigned list by profession
        break;
    default:
        return;
    }
    cout << "Queue Waiting: \n";
    for (int _ = 0; _ < queue_waiting; _++)// print the queueing list
    {
        cout << "\nName:" << queueing_personal_file[_]->name << "\n";
        cout << "Age group:" << queueing_personal_file[_]->agegroup << "\n";
        cout << "Profession:" << queueing_personal_file[_]->profession << "\n";
        cout << "Risk:" << queueing_personal_file[_]->risk << "\n";
        cout << "Waiting time until now:" << (*date) - queueing_personal_file[_]->registrationdate << "\n";
    }
    cout << "\nAssigned Waiting: \n";
    for (int _ = 0; _ < assign_waiting; _++)// print the assigned list
    {
        cout << "\nName:" << assigned_personal_file[_]->name << "\n";
        cout << "Age group:" << assigned_personal_file[_]->agegroup << "\n";
        cout << "Profession:" << assigned_personal_file[_]->profession << "\n";
        cout << "Risk:" << assigned_personal_file[_]->risk << "\n";
        cout << "Waiting time until now:" << (*date) - assigned_personal_file[_]->registrationdate << "\n";
    }
    cout << "\nTreatment: \n";
    for (int _ = 0; _ < total_treatment; _++)// print the treatment list
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
{// print the monthly report
    cout << "\nTotal Registered: " << total_reg_person << "\n";
    cout << "Waiting in queue: " << queue_waiting << "\n";
    cout << "Waiting in total: " << assign_waiting + queue_waiting << "\n";
    cout << "Treatment appointments: " << assign_waiting << "\n";
    cout << "Withdraw: " << total_reg_person - queue_waiting - assign_waiting - total_treatment << "\n";
}

static void DDL_letter(int64_t ID, string sbDDL)
{
    CDate *DDL = new CDate;
    if (!DDL->set(sbDDL))// if the DDL is not valid
    {
        cout << "Invalid date format. Use \'yyyy-mm-dd\'." << endl;
        delete DDL;// free the memory space
        return;
    }
    personal_profile *ptr = ID2ptr.retrieve(ID);// get the pointer of the person
    if (ptr == NULL)// if the person is not in the database
    {
        cout << "The ID is not in the database." << endl;// print error message
        delete DDL;// free the memory space
        return;
    }
    if (ptr->is_inoculated)// if the person is already inoculated
    {
        cout << "The person is already inoculated." << endl;// print error message
        delete DDL;// free the memory space
        return;
    }
    if (ptr->is_assigned && (*DDL) - ptr->inoculate_date < 0)// if the person is assigned and the DDL is before the inoculation date
    {
        ptr->inoculate_date = (*DDL);
        sort(assigned_personal_file.begin(), assigned_personal_file.end(), cmp_by_ddl);// sort the assigned list by DDL
        return;
    }
    else if (ptr->is_assigned)
    {
        cout << "The person is assigned and the DDL is before the inoculation date." << endl;// print error message
        delete DDL;// free the memory space
        return;
    }
    if (ptr->is_delay)
    {
        for (vector<personal_profile *>::iterator i = delay_personal_file.begin(); i != delay_personal_file.end(); i++)// find the person in the delay list
        {
            if ((*i)->ID == ID)
            {
                delay_personal_file.erase(i);// remove the person from the delay list
                break;
            }
        }
        for (vector<personal_profile *>::iterator i = queueing_personal_file.begin(); i != queueing_personal_file.end(); i++)// find the person in the queueing list
        {
            if ((*i)->ID == ID)
            {
                queueing_personal_file.erase(i);// remove the person from the queueing list
                break;
            }
        }

        queue_waiting--;// decrease the number of person waiting in the queue
    }
    else if (ptr->withdraw)// if the person is withdrawn
    {
        for (vector<personal_profile *>::iterator i = withdraw_personal_file.begin(); i != withdraw_personal_file.end(); i++)// find the person in the withdraw list
        {
            if ((*i)->ID == ID)
            {
                withdraw_personal_file.erase(i);// remove the person from the withdraw list
                break;
            }
        }
    }
    else
    {
        int64_t prio_num = ptr->priority_num;// get the priority number of the person
        if (ptr->risk != 3)// if the person is not a high risk
            fib_heap_delete(Queueing_heap, prio_num);// delete the person from the queueing heap
        else
            fib_heap_delete(hrisk_heap, ptr->priority_num);// delete the person from the high risk heap

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
    int64_t pre_prio_num = ptr->priority_num;
    int64_t now_prio_num = prof;
    now_prio_num <<= 5;
    now_prio_num += ptr->agegroup;
    now_prio_num <<= 25;
    now_prio_num += ptr->registrationdate - (*first_date);
    now_prio_num <<= 20;
    now_prio_num += total_reg_person;
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

/**
 * @brief withdraw: withdraw the profile giving its ID
 *
 * @param ID
 */
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

/**
 * @brief cancel_withdraw: Cancel the withdrawal of profile ID
 *
 * @param ID
 */
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
    for (vector<personal_profile *>::iterator i = withdraw_personal_file.begin(); i != withdraw_personal_file.end(); i++)
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
    ptr->registrationdate = *date;
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

/**
 * @brief treat_assigned: Treat the patients.
 *
 * @param copy_daily
 * @param copy_total
 */
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
        ptr->inoculate_date = *date;
        while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
        {
            ino_id++;
        }
        copy_daily[ptr->vaccination_sequence[ino_id]]--;
        ptr->inoID = ptr->vaccination_sequence[ino_id];
        (*copy_total)--;
        assign_waiting--;
        aver_waiting = (aver_waiting * total_treatment + ((*date) - ptr->registrationdate)) / (total_treatment + 1);
        total_treatment++;
        i = assigned_personal_file.erase(i);
        inoculated_personal_file.push_back(ptr);
    }
}

/**
 * @brief treat_queue: Generate the queue for treatment order of the patients
 *
 * @param copy_daily
 * @param copy_total
 */
void treat_queue(int64_t *copy_daily, int64_t *copy_total)
{
    vector<personal_profile *>::iterator i = queueing_personal_file.begin();
    int64_t ino_id = 0;
    personal_profile *ptr;
    int64_t *prio_num = new int64_t, id;
    while (*copy_total > 0 && fib_heap_get_min(Queueing_heap, prio_num))
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
            ptr->inoculate_date = *date;
            while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
            {
                ino_id++;
            }
            copy_daily[ptr->vaccination_sequence[ino_id]]--;
            ptr->inoID = ptr->vaccination_sequence[ino_id];
            (*copy_total)--;
            queue_waiting--;
            aver_waiting = (aver_waiting * total_treatment + ((*date) - ptr->registrationdate)) / (total_treatment + 1);
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
            CDate delay = *date;
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

/**
 * @brief
 *
 * @param copy_daily
 * @param copy_total
 */
void treat_delay(int64_t *copy_daily, int64_t *copy_total)
{
    vector<personal_profile *>::iterator i = queueing_personal_file.begin();
    vector<personal_profile *>::iterator i_d = delay_personal_file.begin();
    personal_profile *ptr;
    int64_t ino_id = 0;
    while ((*copy_total) > 0 && !delay_personal_file.empty() && (*i_d)->inoculate_date - (*date) <= 0)
    {
        ptr = *i_d;
        ptr->is_inoculated = true;
        ptr->is_assigned = false;
        ptr->once_withdraw = false;
        ptr->is_delay = false;
        ptr->withdraw = false;
        ptr->inoculate_date = *date;
        while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
        {
            ino_id++;
        }
        copy_daily[ptr->vaccination_sequence[ino_id]]--;
        ptr->inoID = ptr->vaccination_sequence[ino_id];
        (*copy_total)--;
        queue_waiting--;
        aver_waiting = (aver_waiting * total_treatment + ((*date) - ptr->registrationdate)) / (total_treatment + 1);
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

/**
 * @brief Treat the patients with high risk level.
 *
 * @param copy_daily
 * @param copy_total
 */
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
    while ((*copy_total) > 0 && fib_heap_get_min(hrisk_heap, prio_num))
    {
        fib_heap_extract_min(hrisk_heap);
        id = priority2ID.retrieve(*prio_num);
        ptr = ID2ptr.retrieve(id);

        ptr->is_inoculated = true;
        ptr->is_assigned = false;
        ptr->once_withdraw = false;
        ptr->is_delay = false;
        ptr->withdraw = false;
        ptr->inoculate_date = *date;
        while (copy_daily[ptr->vaccination_sequence[ino_id]] <= 0)
        {
            ino_id++;
        }
        copy_daily[ptr->vaccination_sequence[ino_id]]--;
        ptr->inoID = ptr->vaccination_sequence[ino_id];
        (*copy_total)--;
        queue_waiting--;
        aver_waiting = (aver_waiting * total_treatment + ((*date) - ptr->registrationdate)) / (total_treatment + 1);
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

/**
 * @brief Go to the next day.
 *
 */
static void next_day()
{
    if (((*date) - (*first_date)) % 7 == 6)
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
    if (((*date) - (*first_date)) % 30 == 29)
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
    (*date)++;
    cout << endl
         << "********************\n Today is ";
    (*date).print();
    cout << "********************" << endl
         << endl;
}
