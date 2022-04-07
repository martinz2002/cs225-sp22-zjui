#include "subroutines.cpp"

using namespace std;

int main()
{
    freopen("result.txt", "w", stdout);

    cout << "Welcome to the Silly Medical Treatment System (SMTS). Current date: ";
    (*date).print();

    // import registration points
    ifstream reg_pts_file;
    reg_pts_file.open("reg_pts.loc"); // open file for locations of registration points
    int x, y;                         // coordination components
    while (EOF != reg_pts_file.peek())
    {
        reg_pts_file >> x >> y;
    }

    // import inoculation points
    ifstream inoc_pts_file;
    inoc_pts_file.open("inoc_pts.loc"); // open file for locations of inoculation points
    int x_, y_, c_;
    while (EOF != inoc_pts_file.peek())
    {
        inoc_pts_file >> x_ >> y_ >> c_;
    }
    calc_reg_dist(); // Calculate the distance between registration points and inoculation points

    // import profiles
    static CDate *next_profile_date = new CDate;  // date of next profile
    static CDate *next_withdraw_date = new CDate; // date of next withdrawal

    string name, address, phone, WeChat, email, birthdate, temp_date;
    int risk, profession;
    int64_t ID, RegID;

    ifstream profile_stream, withdraw_stream;
    profile_stream.open("data/profiles.entries", ios::in);
    withdraw_stream.open("data/withdraw.entries", ios::in);

    // Get the first date of entry of profiles and withdrawals
    profile_stream >> temp_date;
    next_profile_date->set(temp_date);
    string temp_date_for_withdraw;
    withdraw_stream >> temp_date_for_withdraw;
    next_withdraw_date->set(temp_date_for_withdraw);
    // Iterate through profile entries and withdrawals and record them
    while (temp_date != "EOF" || temp_date_for_withdraw != "EOF")
    // "EOF" is a random string to help checking if the file is ended
    // If the file ends, temp_data will read nothing and thus should be an empty stirng
    {
        while ((*next_profile_date) <= (*date) && temp_date != "EOF") // if the today we have to add a profile
        {
            profile_stream >> name >> address >> phone >> WeChat >> email >> birthdate >> risk >> profession >> ID >> RegID;
            add_profile(name, address, phone, WeChat, email, risk, ID, profession, birthdate, RegID);
            // print the added profile
            //  cout << "Added profile: " << endl;
            //  cout << "Name: " << name << endl;
            //  cout << "Address: " << address << endl;
            //  cout << "Phone: " << phone << endl;
            //  cout << "WeChat: " << WeChat << endl;
            //  cout << "Email: " << email << endl;
            profile_stream >> temp_date;
            next_profile_date->set(temp_date);
        }
        while (next_withdraw_date <= date && temp_date_for_withdraw != "EOF") // if today we have to perform a withdrawal
        {
            withdraw_stream >> ID;
            withdraw(ID);
            withdraw_stream >> temp_date_for_withdraw;
            next_withdraw_date->set(temp_date_for_withdraw);
        }
        next_day(); // go to next day
    }
}