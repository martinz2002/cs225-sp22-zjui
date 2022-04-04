#include "headers/subroutines.h"
using namespace std;


int main()
{
    int type;
    do
    {
        cout << "1. Add registration point\n" ;
        cout << "2. Add inoculation point\n" ;
        cout << "3. Start program\n" ;
        cin >> type;
        if (type != 1 && type != 2 && type != 3)
        {
            cout << "You must choose 1 or 2 or 3\n\n" ;
        }

        switch (type)
        {
        case 1:
        {
            int x, y;
            cout << "plz provide the x-coordinate of registration point\n" ;
            cin >> x;
            cout << "plz provide the y-coordinate of registration point\n\n" ;
            cin >> y;
            reg_reg(x, y);
            break;
        }
        case 2:
        {
            int x, y, c;
            cout << "plz provide the x-coordinate of inoculation point\n" ;
            cin >> x;
            cout << "plz provide the y-coordinate of inoculation point\n" ;
            cin >> y;
            cout << "plz provide the daily capacity of inoculation of the very point\n\n" ;
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
        cout << "1. Register a new profile\n" ;
        cout << "2. Print report\n" ;
        cout << "3. Change one's profile\n" ;
        cout << "4. Add one's priority letter\n" ;
        cout << "5. Start next day\n" ;
        cin >> op;

        if (op != 1 && op != 2 && op != 3 && op != 4 && op != 5)
        {
            cout << "You must choose 1 or 2 or 3 or 4 or 5\n\n" ;
        }

        switch (op)
        {
        case 1:
        {
            cout;

        }
        }
    } while (op != 5);

    return 0;
}
