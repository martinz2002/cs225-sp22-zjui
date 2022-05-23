/**
 * @file runsys.cpp
 * @author Zhong Tiantian, Li Rong
 * @brief
 * @version 0.2
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022 Zhejiang University
 *
 */
#include "subroutines.cpp"

using namespace std;

int main()
{
    cout << "Welcome to the Silly Medical Treatment System (SMTS). Current date:\n";
    (*date).print();

    int report_op;
    cout << "Please choose the type of ordering scheme for weekly report: ";
    cout << endl;
    cout << "0. order of name\n";
    cout << "1. order of agegroup\n";
    cout << "2. order of profession\n";
    cin >> report_op;
    while (report_op < 0 || report_op > 2) // check if the input is valid
    {
        cout << "Please enter a value between 0 and 2\n";
        cin >> report_op;
    }

    freopen("result.out", "w", stdout);
    cout << endl
         << "****************************************\n The system starts on ";
    (*date).print();
    cout << "****************************************" << endl
         << endl;
    // import registration points
    ifstream reg_pts_file;
    reg_pts_file.open("data/reg_pts.loc"); // open file for locations of registration points
    int x, y;                              // coordination components
    while (EOF != reg_pts_file.peek())
    {
        reg_pts_file >> x >> y;
        reg_reg(x, y);
    }

    // import inoculation points
    ifstream inoc_pts_file;
    inoc_pts_file.open("data/ino_pts.loc"); // open file for locations of inoculation points
    int x_, y_, c_;
    while (EOF != inoc_pts_file.peek())
    {
        inoc_pts_file >> x_ >> y_ >> c_;
        reg_ino(x_, y_, c_);
    }
    calc_reg_dist(); // Calculate the distance between registration points and inoculation points

    // import profiles
    static CDate *next_profile_date = new CDate;         // date of next profile
    static CDate *next_withdraw_date = new CDate;        // date of next withdrawal
    static CDate *next_modify_profiles_date = new CDate; // date of next modification of profiles
    static CDate *next_priority_date = new CDate;        // date of importing next priority letter

    string name, address, phone, WeChat, email, birthdate;
    string temp_date;                 // Input temp when reading profile date
    string temp_date_for_withdraw;    // input temp when reading withdrawal/cancellation date
    string temp_date_priority_letter; // input temp when reading priority letter date
    string temp_date_modification;    // input temp when reading profile modification date
    int risk, profession;
    int64_t ID, RegID;
    int op_withdraw, op_change_profile; // 0 = cancel withdraw; 1 = withdraw; 0 = change risk; 1 = change profession

    ifstream profile_stream, withdraw_stream, priority_letter_stream, modify_profile_stream;
    profile_stream.open("data/profiles.entries", ios::in);
    withdraw_stream.open("data/withdraw.entries", ios::in);
    priority_letter_stream.open("data/priority_letters.entries", ios::in);
    modify_profile_stream.open("data/modify_profiles.entries", ios::in);

    // Get the first date of entry of profiles and withdrawals
    profile_stream >> temp_date;
    next_profile_date->set(temp_date);
    withdraw_stream >> temp_date_for_withdraw;
    next_withdraw_date->set(temp_date_for_withdraw);
    priority_letter_stream >> temp_date_priority_letter;
    next_priority_date->set(temp_date_priority_letter);
    modify_profile_stream >> temp_date_modification;
    next_modify_profiles_date->set(temp_date_modification);
    // Iterate through profile entries and withdrawals and record them
    while (temp_date != "EOF" || temp_date_for_withdraw != "EOF")
    // "EOF" is a random string to help checking if the file is ended
    // If the file ends, temp_data will read nothing and thus should be an empty stirng
    {
        while ((*next_profile_date) <= (*date) && temp_date != "EOF") // if the today we have to add a profile
        {
            profile_stream >> name >> address >> phone >> WeChat >> email >> birthdate >> risk >> profession >> ID >> RegID;
            add_profile(name, address, phone, WeChat, email, risk, ID, profession, birthdate, RegID);
            profile_stream >> temp_date;
            next_profile_date->set(temp_date);
        }
        while ((*next_withdraw_date) <= (*date) && temp_date_for_withdraw != "EOF") // if today we have to perform a withdrawal/cancellation
        {
            withdraw_stream >> op_withdraw;
            withdraw_stream >> ID;
            if (op_withdraw == 0)
            {
                // cancel withdraw
                cancel_withdraw(ID);
            }
            else if (op_withdraw == 1)
            {
                // withdraw
                withdraw(ID);
            }
            else
            {
                // illegal withdraw operation code
                cout << "[Error] Illegal entry at date:";
                (*date).print();
                cout << "    ID: " << ID << endl;
            }
            withdraw_stream >> temp_date_for_withdraw;
            next_withdraw_date->set(temp_date_for_withdraw);
        }
        while ((*next_priority_date) <= (*date) && temp_date_priority_letter != "EOF") // if today we have to import a priority letter
        {
            priority_letter_stream >> ID;
            priority_letter_stream >> temp_date_priority_letter;
            DDL_letter(ID, temp_date_priority_letter);
            priority_letter_stream >> temp_date_priority_letter;
            next_priority_date->set(temp_date_priority_letter);
        }
        while ((*next_modify_profiles_date) <= (*date) && temp_date_modification != "EOF") // if today we have to modify profiles
        {
            modify_profile_stream >> op_change_profile;
            if (op_change_profile == 0)
            {
                // change risk
                modify_profile_stream >> ID;
                modify_profile_stream >> risk;
                change_risks(ID, risk);
            }
            else if (op_change_profile == 1)
            {
                // change profession
                modify_profile_stream >> ID;
                modify_profile_stream >> profession;
                change_pro(ID, profession);
            }
            else
            {
                // illegal modify profile operation code
                cout << "[Error] Illegal entry at date:";
                (*date).print();
                cout << "    ID: " << ID << endl;
            }
            modify_profile_stream >> temp_date_modification;
            next_modify_profiles_date->set(temp_date_modification);
        }
        next_day_for_auto(report_op); // go to next day
    }
    while (assign_waiting > 0 || queue_waiting > 0)
    {
        next_day_for_auto(report_op); // go to next day
    }
    // Print the final report
    cout << "*****************************************" << endl;
    cout << "              FINAL REPORT"<< endl;
    cout << "*****************************************" << endl;
    monthly_report();
    cout << "\nSystem quites normally on ";
    (*date).print();
    cout << "*****************************************" << endl;
    cout << "           END OF FINAL REPORT"<< endl;
    cout << "*****************************************" << endl;
}