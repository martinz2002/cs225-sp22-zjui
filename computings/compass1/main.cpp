#include "headers/subroutines.h"
using namespace std;

int main()
{
    static int date = 0;
    int type;
    do
    {
        cout << "1. Add registration point:\n";
        cout << "2. Add inoculation point:\n";
        cout << "3. Start program\n";
        cin >> type;
        if (type != 1 && type != 2 && type != 3)
        {
            cout << "You must choose 1 or 2 or 3\n";
        }

        switch (type)
        {
        case 1:
        {
            int x, y;
            cout << "plz provide the x-coordinate of registration point:\n";
            cin >> x;
            cout << "plz provide the y-coordinate of registration point:\n";
            cin >> y;
            // reg_reg(x, y);
            break;
        }
        case 2:
        {
            int x, y, c;
            cout << "plz provide the x-coordinate of inoculation point:\n";
            cin >> x;
            cout << "plz provide the y-coordinate of inoculation point:\n";
            cin >> y;
            cout << "plz provide the daily capacity of inoculation of the very point:\n";
            cin >> c;
            // reg_ino(x, y, c);
            break;
        }
        }
    } while (type != 3);

    // calc_reg_dist();

    int op;
    do
    {
        cout << "1. Register a new profile\n";
        cout << "2. Print report\n";
        cout << "3. Change one's profile\n";
        cout << "4. Add one's priority letter\n";
        cout << "5. Start next day\n";
        cout << "6. Quit\n";
        cin >> op;

        if (op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6)
        {
            cout << "You must choose 1 or 2 or 3 or 4 or 5 or 6\n";
        }

        switch (op)
        {
        case 1:
        {
            string address, phone, WeChat, email;
            int64_t ID, birthdate, registrationdate, regID;
            int risk, profession, agegroup;
            cout << "ID\n";
            cin >> ID;
            cout << "birthdate";
            cin >> birthdate;
            cout << "registrationdate\n";
            cin >> registrationdate;
            cout << "regID\n";
            cin >> regID;
            cout << "address\n";
            cin >> address;
            cout << "phone\n";
            cin >> phone;
            cout << "WeChat\n";
            cin >> WeChat;
            cout << "email\n";
            cin >> email;
            cout << "profession\n";
            cin >> profession;
            if (profession <= 0 || profession > 8)
            {
                cout << ("plz enter a value between 1 and 8");
                break;
            }
            cout << "agegroup\n";
            cin >> agegroup;
            if (agegroup <= 0 || agegroup > 7)
            {
                cout << ("plz enter a value between 1 and 7");
                break;
            }
            cout << "risk\n";
            cin >> risk;
            if (risk <0 || risk > 3)
            {
                cout << ("plz enter a value between 0 and 3");
                break;
            }
            // add_profile(address, phone, WeChat, email, risk, ID, profession, agegroup, birthdate, registrationdate, regID);
            break;
        }
        case 2:
        {
            // report();
            break;
        }
        case 3:
        {
            int64_t ID;
            int risk, profession, choice;
            cout << "plz provide the ID:\n";
            cin >> ID;
            cout << "choose the value type to change:\n";
            cout << "1. profession\n";
            cout << "2. risk\n";
            cin >> choice;

            if (op != 1 && op != 2)
            {
                cout << "You must choose 1 or 2\n\n";
            }

            switch (choice)
            {
            case 1:
            {
                cout << "plz enter the changed profession value:\n";
                cin >> profession;
                // change_pro(ID, profession);
                break;
            }
            case 2:
            {
                cout << "plz enter the changed risk value:\n";
                cin >> risk;
                // change_risks(ID, risk);
                break;
            }
            }

            break;
        }
        case 4:
        {
            int64_t ID, DDL;
            cout << "plz enter the ID:\n";
            cin >> ID;
            cout << "plz enter the corresponding requested due date:\n";
            cin >> DDL;
            // DDL_letter(ID, DDL);
            break;
        }
        case 5:
        {
            // next_day();
        }
        }
    } while (op != 6);

    return 0;
}
