/*
 * @ Author     : 
 * 
 * @ File       : 
 * 
 * @ Purpose    : 
 * 
 * @ Usage      : 
 * 
 * @ Description: 
 * 
 * @ Input      : 
 * 
 * @ Output     : 
 * 
 */
#include "hw2ex2.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;
int main(){
    vector<booking> b1({booking(1,2), booking(2,3), booking(2,4), booking(3,4)});

    // =========== Test 1 ===========
    Bookings test1 = Bookings(b1, 8);
    cout << "Test 1: " << endl;
    test1.test();
    cout << "Gold Result: Success" << endl;

    // =========== Test 2 ===========
    Bookings test2 = Bookings(b1, 1);
    cout << "\nTest 2: " << endl;
    test2.test();
    cout << "Gold Result: Fail" << endl;

    // =========== Hidden Test =========
    // =========== Test 3 ===========
    vector<booking> b2({booking(1,2), booking(2,3), booking(2,4), booking(3,4), booking(1,6), booking(2, 7)});
    Bookings test3 = Bookings(b2, 3);
    cout << "\nTest 3: " << endl;
    test3.test();
    cout << "Gold Result: Fail" << endl;

    // =========== Test 4 ===========
    Bookings test4 = Bookings(b2, 4);
    cout << "\nTest 4: " << endl;
    test4.test();
    cout << "Gold Result: Succuss" << endl;




    return 0;
}