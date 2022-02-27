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

#include <vector>
#include <iostream>
using namespace std;

class booking{
    public:
        booking(int a, int d){
            arrival = a;
            departure = d;
        };
        int arrival; 
        int departure; 
};

// Solution add
class transbook{
    public:
        int _day;
        int _ad; // represent arrival or departure, 1 means arrival, 0 means departure
        transbook(){};
        transbook(int day, int ad){
            _day = day;
            _ad = ad;
        }
        bool operator<(transbook& other){
            if(_day < other._day || (_day == other._day && _ad < other._ad)) return true;
            return false;
        }
};

class Bookings{
    public:
        Bookings(vector<booking> bookings, int K){
            bks = bookings;
            k = K;
        };
        vector <booking> bks;
        int k;
        void bookings_print();
        void test();
        // Modify the following to solve the exercise
        bool checkdemands();


    private:
        // Solution Add
        vector<transbook> bktransfer;
        
        void transferbooking();
        void transbooksort();
};

void Bookings::bookings_print(){
    cout << "Bookings as follow:" << endl;
    for(booking i: this->bks){
        cout << "A: " << i.arrival << "  | D: " << i.departure << endl;
    }
    cout << "Max available room:" << this->k << endl;
    return ;
}

void Bookings::test(){
    bookings_print();
    cout << "Check whether satisfy the demands: " << (checkdemands()? "Success":"Fail") << endl;
}

// You should right the following to finish the exercise
// You may also add your own help function
bool Bookings::checkdemands(){
    transferbooking();
    transbooksort();
    int cur_cus = 0, max_cus = 0;

    for (transbook i: this->bktransfer){
        if (i._ad == 0){
            cur_cus--;
        }
        else{
            cur_cus++;
            max_cus = (max_cus < cur_cus)?cur_cus:max_cus;
            if (max_cus > this->k) return false;
        }
    }
    return true;
};


// Solution add
// Transfer the given input to a sortable tuple set
// Given (1, 2) a booking, transfer to (1, 0)
void Bookings::transferbooking(){
    for (auto b: bks){
        bktransfer.push_back(transbook(b.arrival, 1));
        bktransfer.push_back(transbook(b.departure, 0));
    }
};

// Solution add
void Bookings::transbooksort(){
    transbook temp = transbook();
    for (int i = 0; i < bktransfer.size(); i++){
        for (int j = i; j > 0 && bktransfer[j] < bktransfer[j-1]; j--){
            temp = bktransfer[j];
            bktransfer[j] = bktransfer[j-1];
            bktransfer[j-1] = temp;
        }
    }
};
