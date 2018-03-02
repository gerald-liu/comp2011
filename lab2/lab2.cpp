/*
 * Lab2.cpp
 *
 *  Created on: Sep 15, 2017
 *      Author: Weiyang Liu
 */

#include <iostream>
#include <math.h>
using namespace std;

int income, married, kid, oth, chargeable, tax;
char contd;

int main(int argc, char ** argv){
    while(true) {
        cout << "===========================" << endl;
        cout << "An imaginary tax calculator" << endl;
        cout << "===========================\n" << endl;
    
        cout << "1. Total income?" << endl;
        while(true) {
            cin >> income;
            if (income>=0) {break;}
            cout << "Invalid input, please enter again." << endl;
        }

        cout << "2. Marital Status?" << endl;
        cout << "Input 0 for single/widowed, 1 for married." << endl;
        while(true) {
            cin >> married;
            if (married==0 || married==1) {break;}
            cout << "Invalid input, please enter again." << endl;
        }

        cout << "3. Number of dependent kids?" << endl;        
        while(true) {
            cin >> kid;
            if (kid>=0) {break;}
            cout << "Invalid input, please enter again." << endl;
        }

        cout << "4. Amount of other tax deduction to be claimed?" << endl;        
        while(true) {
            cin >> oth;
            if (oth>=0) {break;}
            cout << "Invalid input, please enter again." << endl;
        }
    
        chargeable = income - kid*(4000-married*1000) - oth;
        if (chargeable<0){tax=0;}
        else if (chargeable<=45000){
            tax = (int)floor(chargeable*0.02);
        }
        else if (chargeable<=90000){
            tax = (int)floor(45000*0.02 + (chargeable-45000)*0.07);
        }
        else {
            tax = (int)floor(45000*0.02 + 45000*0.07 + (chargeable-90000)*0.12);
        }
    
        cout << "You need to pay $" << tax << " tax." << endl;
        
        cout << "Do you want to calculate another tax?" << endl;
        cout << "y for YES, n for no." << endl;
        do {
            cin >> contd;
            if (contd!='n' && contd!='y'){
                cout << "Invalid input, please enter again." << endl;}
        } while (contd!='n' && contd!='y'); 
        
        if (contd=='n') {break;}
        else {continue;}

    }
    
    return 0;
}
