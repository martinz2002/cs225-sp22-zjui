/**
 * @file subroutines.h
 * @author Li Rong
 * @brief Providing the function models for misc functions.
 * @version 0.1
 * @date 2022-04-04
 *
 * @copyright Copyright (c) 2022 Zhejiang University
 *
 */

#ifndef SUB_R
#define SUB_R
#include <bits/stdc++.h>
#include "date.h"
#include "fiboheap.h"
#include "profile.h"
#include "id_hash.h"

using std::string;

class treatment
{
public:
    treatment(int32_t risk_type = 0);
    CDate *date = new CDate(time(NULL)); // Current date being processed by the system
    int64_t assign_waiting = 0;          // number of people who haven't been inoculated but have already sent the priority letter
    int64_t queue_waiting = 0;           // number of people who haven't been inoculated but did not send the priority letter
    /**
     * @brief a subroutine for comparation between distance for num1 and num2, return 1 if distance for num1 is the smaller one
     *
     * @param num1 id of the first location index
     * @param num2 id of the second location index
     * @return true dist[num1] < dist[num2]
     * @return false dist[num1] >= dist[num2]
     */
    bool compare_by_dist(int64_t num1, int64_t num2);

    /**
     * @brief a subroutine for comparation by email address
     *
     * @param file1
     * @param file2 Profiles to compare
     * @return true String of the first person's name is smaller than the second
     * @return false vice versa
     */
    bool cmp_by_name(personal_profile *file1, personal_profile *file2);

    /**
     * @brief a subroutine for comparation by profession
     *
     * @param file1
     * @param file2
     * @return true
     * @return false
     */
    bool cmp_by_pof(personal_profile *file1, personal_profile *file2);

    /**
     * @brief a subroutine for comparation by agegroup
     *
     * @param file1
     * @param file2
     * @return true
     * @return false
     */
    bool cmp_by_agegp(personal_profile *file1, personal_profile *file2);

    /**
     * @brief a subroutine for comparation by inoculation date
     *
     * @param file1
     * @param file2
     * @return true
     * @return false
     */
    bool cmp_by_ddl(personal_profile *file1, personal_profile *file2);

    /**
     * @brief reallocate for larger memory space to contain registration profile
     *
     */
    void alloc_for_reg();

    /**
     * @brief reallocate for larger memory space to contain inoculation profile
     *
     */
    void alloc_for_ino();

    /**
     * @brief register a new registration point to the registration profile list
     *
     * @param x X coordination of the point
     * @param y Y coordination of the point
     */
    void reg_reg(int64_t x, int64_t y);

    /**
     * @brief register a new inoculation point to the inoculation profile list
     *
     * @param x X coordinate of the point
     * @param y Y coordinate of the point
     * @param cap capacity of the point, i.e. maximum number of people receiving inoculation on the same day
     */
    void reg_ino(int64_t x, int64_t y, int cap);

    /**
     * @brief calculate the distance between each registration point and inoculation points
     *
     */
    void calc_reg_dist();

    /**
     * @brief Calculate a person's age group by its birthdate
     *
     * @param birthdate
     * @return int The index of the age group
     */
    int calc_agegroup(CDate *birthdate);

    /**
     * @brief Add a person's profile giving his/her basic information
     *
     * @param name name string of the patient
     * @param address address string of the patient
     * @param phone
     * @param WeChat
     * @param email
     * @param risk
     * @param ID
     * @param profession
     * @param birthdate
     * @param RegID
     */
    void add_profile(string name, string address, string phone, string WeChat, string email, int risk, int64_t ID, int profession, string birthdate, int64_t RegID);

    /**
     * @brief Generate weekly report giving certain operation code.
     *
     * @param op
     */
    void weekly_report(int op);

    /**
     * @brief Generate a monthly report
     *
     */
    void monthly_report();

    /**
     * @brief Change a profile's profession giving its ID and new profession number
     *
     * @param ID
     * @param prof
     */
    void change_pro(int64_t ID, int64_t prof);

    /**
     * @brief Change the risk level of a profile giving profile ID and new risk number
     *
     * @param ID
     * @param Risks
     */
    void change_risks(int64_t ID, int64_t Risks);

    /**
     * @brief withdraw the profile giving its ID
     *
     * @param ID
     */
    void withdraw(int64_t ID);

    /**
     * @brief cancel_withdraw: Cancel the withdrawal of profile ID
     *
     * @param ID
     */
    void cancel_withdraw(int64_t ID);

    /**
     * @brief treat_assigned: Treat the patients.
     *
     * @param copy_daily
     * @param copy_total
     */
    void treat_assigned(int64_t *copy_daily, int64_t *copy_total);

    /**
     * @brief treat_queue: Generate the queue for treatment order of the patients
     *
     * @param copy_daily
     * @param copy_total
     */
    void treat_queue(int64_t *copy_daily, int64_t *copy_total);

    /**
     * @brief Submit a letter to claim the deadline
     *
     * @param ID
     * @param sDDL
     */
    void DDL_letter(int64_t ID, string sDDL);

    /**
     * @brief
     *
     * @param copy_daily
     * @param copy_total
     */
    void treat_delay(int64_t *copy_daily, int64_t *copy_total);

    /**
     * @brief Treat the patients with high risk level.
     *
     * @param copy_daily
     * @param copy_total
     */
    void treat_hrisk(int64_t *copy_daily, int64_t *copy_total);

    /**
     * @brief Go to the next day; for use in manual version
     *
     */
    void next_day();

    /**
     * @brief Go to the next day; for use in auto version
     *
     * @param op
     */
    void next_day_for_auto(int op);

private:
    //  int32_t date = 0;
    int32_t risk_type = 0;
    CDate *first_date = new CDate(time(NULL)); // Date of the first run of the program
    int64_t num_reg = 0;                       // Number of registration points
    int64_t num_ino = 0;                       // Number of inoculation points
    int64_t max_num_reg = 20;                  // Maximum Number of registration points
    int64_t max_num_ino = 20;                  // Maximum Number of inoculation points

    int64_t daily_total = 0; // the capacity of treatment from all registration points, initialized by 0

    int64_t total_reg_person = 0; // number of people that have registered
    int64_t total_treatment = 0;  // the number of processed people
    double_t aver_waiting = 0;    // the average time of waiting

    int64_t *daily; // the array that contains the inoculation capacity of each inoculation point

    registration_profile **reg_pro = new registration_profile *[max_num_reg]; // pointing to a list of registration pts profile
    inoculate_profile **ino_pro = new inoculate_profile *[max_num_ino];       // pointing to a list of inoculation pts profile
                                                                              // initialization for registration_profile and inoculate_profile

    vector<personal_profile *> queueing_personal_file; // the queue of the waiting people

    vector<personal_profile *> delay_personal_file; // the queue of the patient

    vector<personal_profile *> inoculated_personal_file; // the queue of the inoculated people

    vector<personal_profile *> withdraw_personal_file; // the queue of the inoculated people

    vector<personal_profile *> assigned_personal_file; // the queue of the people who have written priority letter

    int64_t *dist; // the temporary distance sequence

    hashmap<int64_t, int64_t> priority2ID = hashmap<int64_t, int64_t>(20); // hashmap from priority to ID

    hashmap<int64_t, personal_profile *> ID2ptr = hashmap<int64_t, personal_profile *>(20); // hashmap from ID to personal profile

    FibHeap *Queueing_heap = fib_heap_make(); // queuing heap; containing risk level 0, 1, and 2
                                              // when popping risk 2 patients will be pushed back to delay_personal_file
    FibHeap *hrisk_heap = fib_heap_make();    // high risk (3) heap
};
#endif