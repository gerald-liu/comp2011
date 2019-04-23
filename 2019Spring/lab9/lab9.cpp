#include <iostream>
#include "Customer.h"
using namespace std;

int main() {
	Customer* head = NULL;
	Customer* p1 = new_customer("Adam", Customer::customer_types[2]);
	Customer* p2 = new_customer("Betty", Customer::customer_types[1]);
	Customer* p3 = new_customer("Chris", Customer::customer_types[1]);
	Customer* p4 = new_customer("Doris", Customer::customer_types[0]);
	Customer* p5 = new_customer("Eric", Customer::customer_types[2]);
	insert_customer(head, p1);
	insert_customer(head, p2);
	insert_customer(head, p3);
	insert_customer(head, p4);
	insert_customer(head, p5);

	int reply, pos;
//	char target_customer_name[MAX_NAME_LENGTH+1];
	char membership[MAX_NAME_LENGTH+1];
	char customer_name[MAX_NAME_LENGTH+1];
	Customer* p;

	do {
		view_customers(head);

		cout << endl << "Choose an operation:" << endl;
		cout << "1: Insert a new customer to the queue." << endl;
		cout << "2: Dispatch a customer from the club." << endl;
		cout << "3: Change the membership of a customer." << endl;
		cout << "4: Quit" << endl;
		cin >> reply;

		switch(reply) {
		case 1:
			cout << "Please enter the name of the customer:" ;
			cin >> customer_name;
			cout << "Please enter the membership [\"VIP\", \"Regular-member\", \"Non-member\"] of the customer:";
			cin >> membership;

			p = new_customer(customer_name, membership);
			insert_customer(head, p);
			break;
		case 2:
			p = dispatch_customer(head);
			if (p != NULL)
				cout << p->name << " is dispatched from the club." << endl;
			else
				cout << "No customers to dispatch!" << endl;
			break;
		case 3:
			if(head != NULL) {
				cout << "Please choose a customer:" << endl;
				list_customers(head);
				cin >> pos;
				cout << "Change his/her membership to:" ;
				cin >> membership;
				modify_customer_type(head, pos, membership);
			} else {
				cout << "No customers available!" << endl;
			}
			break;
		default:
			break;
		}

	} while (reply != 4);


	return 0;
}




