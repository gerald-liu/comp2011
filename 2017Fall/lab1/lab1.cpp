/*
 * Lab1.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: Weiyang Liu
 */

#include <iostream>
#include <string>
using namespace std;

//void usingSwitch();

int main(int argc, char** argv){
    std::string month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int m;
    cout << "Which month were you born in?" << endl;
    while (true) {
        cin >> m;
        if (m<1 || m>12){
            cout << "Oh. You must be... crazy!" << endl;
            cout << "Press enter to exit..." << endl;
            cin.ignore();
            cin.ignore();
            break;
        }
        else {
            cout << "I see! You were born in " << month[m-1] << endl;
        }
    }
    return 0;
}


/*
void usingSwitch(){
    int m;
    while (true) {
        cout << "Which month were you born in?" << endl;
        cin >> m;
        if (m<1 || m>12){
            cout << "Oh. You must be... crazy! Bye!" << endl;
            cout << "Press enter to exit..." << endl;
            cin.ignore();
            cin.ignore();
            break;
        }
        else{
            switch (m){
                case 1: cout << "I see! You were born in Jan" << endl; break;
                case 2: cout << "I see! You were born in Feb" << endl; break;
                case 3: cout << "I see! You were born in Mar" << endl; break;
                case 4: cout << "I see! You were born in Apr" << endl; break;
                case 5: cout << "I see! You were born in May" << endl; break;                
                case 6: cout << "I see! You were born in Jun" << endl; break;
                case 7: cout << "I see! You were born in Jul" << endl; break;
                case 8: cout << "I see! You were born in Aug" << endl; break;
                case 9: cout << "I see! You were born in Sep" << endl; break;
                case 10: cout << "I see! You were born in Oct" << endl; break;
                case 11: cout << "I see! You were born in Nov" << endl; break;
                case 12: cout << "I see! You were born in Dec" << endl; break;
            }
        }
    }
    return;
}
*/
