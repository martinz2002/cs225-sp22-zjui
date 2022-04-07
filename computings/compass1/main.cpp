/**
 * @file main.cpp
 * @author Li Rong
 * @brief Computing Assignment 1 -- Medical Treatment System.
 * @date 2022-04-05
 *
 * @copyright Copyright (c) 2022 Zhejiang University
 *
 */

#include "subroutines.cpp"
using namespace std;

int main()
{
    int type;
    int registration_point_order = 0;
    do
    {
        cout << "1. Add registration point:\n";
        cout << "2. Add inoculation point:\n";
        cout << "3. Start program\n";
        cin >> type;
        while (type != 1 && type != 2 && type != 3) // invalid input
        {
            cout << "You must choose 1 or 2 or 3\n";
            cin >> type;
        }

        switch (type)
        {
        case 1: // Add registration point
        {
            int x, y;
            cout << "plz provide the x-coordinate of registration point:\n";
            cin >> x;
            cout << "plz provide the y-coordinate of registration point:\n";
            cin >> y;
            registration_point_order++;
            reg_reg(x, y);
            break;
        }
        case 2: // Add inoculation point
        {
            int x, y, c;
            cout << "plz provide the x-coordinate of inoculation point:\n";
            cin >> x;
            cout << "plz provide the y-coordinate of inoculation point:\n";
            cin >> y;
            cout << "plz provide the daily capacity of inoculation of the very point:\n";
            cin >> c;
            reg_ino(x, y, c);
            break;
        }
        }
    } while (type != 3);

    calc_reg_dist();

    int op;
    do
    {
        cout << "1. Register a new profile\n";
        cout << "2. Withdraw\n";
        cout << "3. Change one's profile\n";
        cout << "4. Add one's priority letter\n";
        cout << "5. Start next day\n";
        cout << "6. Cancel withdraw\n";
        cout << "7. Quit\n";
        cin >> op;

        if (op != 1 && op != 2 && op != 3 && op != 4 && op != 5 && op != 6 && op != 7)
        {
            cout << "You must choose 1 or 2 or 3 or 4 or 5 or 6 or 7\n";
            continue;
        }
        switch (op)
        {
        case 1: // Register a new profile
        {
            string name, address, phone, WeChat, email, birthdate;
            int64_t ID, regID;
            int risk, profession;
            // int agegroup;
            cout << "ID\n";
            cin >> ID;
            cout << "birthdate (yyyy-mm-dd)\n";
            cin >> birthdate;
            cout << "regID\n";
            cout << "it should be larger than 0 and smaller and equal than " << registration_point_order << "\n";
            cin >> regID;
            while (regID <= 0 || regID > registration_point_order)
            {
                cout << "plz enter a value in the range of registration point order\n";
                cin >> regID;
            }
            cout << "address\n";
            cin >> address;
            cout << "name\n";
            cin >> name;
            cout << "phone\n";
            cin >> phone;
            cout << "WeChat\n";
            cin >> WeChat;
            cout << "email\n";
            cin >> email;
            cout << "profession\n";
            cin >> profession;
            while (profession <= 0 || profession > 8)
            {
                cout << "plz enter a value between 1 and 8\n";
                cin >> profession;
            }
            // cout << "agegroup\n";
            // cin >> agegroup;
            // while (agegroup <= 0 || agegroup > 7)
            // {
            //     cout << "plz enter a value between 1 and 7\n";
            //     cin >> agegroup;
            // }
            cout << "risk\n";
            cin >> risk;
            while (risk < 0 || risk > 3)
            {
                cout << "plz enter a value between 0 and 3\n";
                cin >> risk;
            }
            add_profile(name, address, phone, WeChat, email, risk, ID, profession, birthdate, regID - 1);
            break;
        }
        case 2: // Withdrawl a profile with index ID
        {
            int64_t ID;
            cout << "plz enter the ID:\n";
            cin >> ID;
            withdraw(ID);
            break;
        }
        case 3: // Modify (change) a profile with ID
        {
            int64_t ID;
            int risk, profession, choice;
            cout << "plz provide the ID:\n";
            cin >> ID;
            cout << "choose the value type to change:\n";
            cout << "1. profession\n";
            cout << "2. risk\n";
            cin >> choice;

            while (choice != 1 && choice != 2)
            {
                cout << "You must choose 1 or 2\n\n";
                cin >> choice;
            }

            switch (choice)
            {
            case 1: // Change the profession
            {
                cout << "plz enter the changed profession value:\n";
                cin >> profession;
                while (profession <= 0 || profession > 8)
                {
                    cout << "plz enter a value between 1 and 8\n";
                    cin >> profession;
                }
                change_pro(ID, profession);
                break;
            }
            case 2: // Change the risk
            {
                cout << "plz enter the changed risk value:\n";
                cin >> risk;
                while (risk < 0 || risk > 3)
                {
                    cout << "plz enter a value between 0 and 3\n";
                    cin >> risk;
                }
                change_risks(ID, risk);
                break;
            }
            }

            break;
        }
        case 4: // Add one's priority letter
        {
            int64_t ID, DDL;
            cout << "plz enter the ID:\n";
            cin >> ID;
            cout << "plz enter the corresponding requested due date:\n";
            cin >> DDL;
            DDL_letter(ID, DDL);
            break;
        }
        case 5: // Start the next day
        {
            next_day();
            break;
        }
        case 6:
        {
            int64_t ID;
            cout << "plz enter the ID:\n";
            cin >> ID;
            cancel_withdraw(ID);
            break;
        }
        }
    } while (op != 7);

    // op == 6: the program automatically quits

    return 0;
}
