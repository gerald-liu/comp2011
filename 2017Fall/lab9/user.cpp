#include "user.h"

// load user's information from a given file
void loadUser(User users[], int *numUsers, string filename) {
	*numUsers = 0;
	int id;
	char userName[MAXNAMESIZE];
	ifstream ifs(filename);
	while (!ifs.eof()){
		ifs >> id >> userName;
		addUser(users, numUsers, id, userName);
	}
	ifs.close();
}

// Add a User object to the User array, users, by the parameters, id, userName.
// Moreover, increment the numUsers accordingly.
void addUser(User users[], int* numUsers, int id, const char userName[]) {
	//TODO 3 Add Your Code Here
	users[*numUsers].id = id;
	strcpy(users[*numUsers].name, userName);
	(*numUsers)++;
}

// This function returns the address of the User object in the User array, users, with the id member of the value, id.
// If not found, returns nullptr.
// Input for this function: users -- the array of User objects; 
//                          numUsers -- the number of User objects in users array;
//                          id -- the id of the User object to be found. 
User* searchUserById(User users[], int numUsers, int id) {
	//TODO 3 Add Your Code Here
	for (int i = 0; i < numUsers; i++) if (users[i].id == id) return &users[i];
	return nullptr;
}

// This function will print user information including its ID and name
void printUser(const User *user) {
	//TODO 3 Add Your Code Here
	cout << "< ID: " << user->id << " Name: " << user->name << " >" << endl;
}
