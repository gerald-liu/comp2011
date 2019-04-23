#ifndef USER_H_
#define USER_H_

#include "utils.h"
#include "point.h"

const int MAXUSERNUM  = 100;
const int MAXNAMESIZE = 100;

struct User{
	int id;
	char name[MAXNAMESIZE];
};

void loadUser(User[], int*, string); // given
void addUser(User[], int*, int, const char[]); // TODO 3
void printUser(const User*);  // TODO 3
User* searchUserById(User[], int, int);  // TODO 3

#endif /* USER_H_ */
