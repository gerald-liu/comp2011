#include <iostream>
#include <cstring>
#include "Customer.h"
using namespace std;

const char* Customer::customer_types[] = { "VIP", "Regular-member", "Non-member" };

Customer* new_customer(const char c_name[MAX_NAME_LENGTH+1], const char c_type[MAX_NAME_LENGTH+1]){
	// TODO1: Create new customer and set his/her name and membership accordingly, input validation is not needed.
	Customer* c = new Customer;
	strcpy(c->name, c_name);
	strcpy(c->type, c_type);
	// c->next = nullptr; // default initialization
	return c;
}

// assume each customer's type is valid
// return true if c1 ranks higher than c2 (i.e. index in queue is smaller)
bool operator<(const Customer& c1, const Customer& c2) {
	int num_types = sizeof(Customer::customer_types)/sizeof(char*);
	for (int i = 0; i < num_types; ++i) {
		if (!strcmp(c2.type, Customer::customer_types[i]))
			return false;
		else if (!strcmp(c1.type, Customer::customer_types[i]))
			return true;
	}
	return false; // dummy
}

void insert_customer(Customer*& head, Customer* c){
	// TODO2: Insert the customer c into the queue according to his/her priority (VIP > Regular-member > Non-member)
	if (!head) {
		head = c;
		return;
	}

	if (*c < *head) {
		c->next = head;
		head = c;
		return;
	}

	Customer* curr = head;
	while (curr->next) {
		if (*c < *curr->next) {
			c->next = curr->next;
			curr->next = c;
			return;
		}
		curr = curr->next;
	}

	curr->next = c;
}

void view_customers(const Customer* const head){
	// TODO3: View all customers in the queue, the output format should be:
	// name: name of the customer (tab or spaces) membership: membership of the customer
	// Note: display message like "Empty queue" if the queue is empty
	// Please refer to the output example in the lab manual page.
	if (!head) {
		cout << "Current queue is empty.\n";
		return;
	}

	cout << "Current queue in club.\n";
	const Customer* curr = head;
	while (curr) {
		cout << "Name: " << curr->name << "\tMembership: " << curr->type << '\n';
		curr = curr->next;
	}
}

Customer* dispatch_customer(Customer*& head){
	// TODO4: Dispatch the customer who has the highest priority
	// i.e. Remove the customer who are at the first place of the queue
	// Note that you need to return the pointer reference to the dispatched customer as well.
	if (!head)
		return nullptr;
	Customer* temp = head;
	head = head->next;
	return temp;
}

void modify_customer_type(Customer*& head, int pos, const char c_type[MAX_NAME_LENGTH+1]){
	// TODO5: Update the membership (c_type: [VIP|Regular-member|Non-member]) of the customer who is at the (pos)th place in the queue, then re-arrange the customer to a correct position
	// Note1: pos starts from 1
	// Note2: You don't need to do input validation for pos and c_type
	// Hint: The insert_customer function can be helpful
	if (!head)
		return;
	Customer* temp = nullptr;
	if (pos == 1) {
		temp = head;
		head = head->next;
	}
	else {
		Customer* curr = head;
		for (int i = 0; i < pos - 2; curr = curr->next, ++i);
		temp = curr->next;
		curr->next = temp->next;
	}
	strcpy(temp->type, c_type);
	insert_customer(head, temp);
}

void list_customers(const Customer* const head){
	const Customer* current = head;
	int i = 1;
	while(current != nullptr) {
		cout << i << ": " << current->name << endl;
		current = current->next;
		i++;
	}
}
