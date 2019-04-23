#ifndef CUSTOMER_H_
#define CUSTOMER_H_

const int MAX_NAME_LENGTH = 20;

struct Customer {
	char name[MAX_NAME_LENGTH]; // name of the customer
	char type[MAX_NAME_LENGTH]; // membership of the customer
	Customer* next; // pointer to the next customer in the queue

	static const char* customer_types[];
};

Customer* new_customer(const char c_name[MAX_NAME_LENGTH+1], const char c_type[MAX_NAME_LENGTH+1]);

void insert_customer(Customer*& head, Customer* c);

void view_customers(const Customer* const head);

Customer* dispatch_customer(Customer*& head);

void modify_customer_type(Customer*& head, int pos, const char c_type[MAX_NAME_LENGTH+1]);

void list_customers(const Customer* const head);

#endif /* CUSTOMER_H_ */
