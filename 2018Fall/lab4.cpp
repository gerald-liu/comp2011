#include <iostream>
#include <cstring>
using namespace std;

const int DECRYPT = 0;
const int ENCRYPT = 1;

// shift a single character
// Ex1: inputChar is 'H', key is 'd', op is ENCRYPT, returns 'K'
// Ex2: inputChar is 'H', key is 'p', op is DECRYPT, returns 'S'
// Ex3: inputChar is ' ' returns ' '
// Ex4: inputChar is 'z' (ASCII code 122), key is 'o' (shift amount 14), op is ENCRYPT, returns 'n'
// Hint: since 122 + 14 = 136, the value can't be properly saved in a char variable, use of unsigned int is recommended.

char shiftAChar(char inputChar, char key, int op) {
	// add your code here
	if (inputChar == ' ') return ' ';
	else if (op) {
		if (inputChar > 'Z') return 'a' + ((inputChar - 'a' + key - 'a') % 26);
		else return 'A' + ((inputChar - 'A' + key - 'a') % 26);
	}
	else {
		if (inputChar > 'Z') return 'z' - (('z' - inputChar + key - 'a') % 26);
		else return 'Z' - (('Z' - inputChar + key - 'a') % 26);
	}
}

// encrypt or decrypt a message
void endecrypt(const char input[], int inputSize, const char key[], int keySize, char output[], int op) {
	// add your code here
	int j = 0;
	for (int i = 0; i < inputSize; i++) {
		output[i] = shiftAChar(input[i], key[j % keySize], op);
		if (output[i] != ' ') j++;
	}
	output[inputSize] = '\0';
}

int main() {

	// set up the array
	const int SIZE = 101; //the size of the input message is at most 100 characters

	char input[SIZE] = {};
	char key[SIZE] = {};
	char output[SIZE] = {};

	int option = 0;
	do {
		//initialize the three arrays
		cout << "This is a Vigenere cipher machine." << endl;
		cout << "You can input at most 100 characters." << endl;
		cout << "1. Encrypt a plaintext" << endl;
		cout << "2. Decrypt a ciphertext" << endl;
		cout << "3. Exit" << endl;
		do {
			cout << "Please select an option (1 - 3): ";
			cin >> option;
			cin.ignore(); //ignore the enter
		} while (option < 1 || option > 3);

		if (option == 1) {
			cout << "Your plaintext is: ";
			// get the input including the whitespace but terminate when it is over the size or reach the newline character
			cin.getline(input, SIZE, '\n');
			cout << "The keyword is: ";
			cin >> key;
			// en/decrpyt the input text
			// function strlen(input) from cstring library is used to get the string length of input, same for strlen(key)
			endecrypt(input, strlen(input), key, strlen(key), output, ENCRYPT);
			cout << "The ciphertext is: " << output << endl << endl;
		} else if (option == 2) {
			cout << "Your ciphertext is: ";
			cin.getline(input, SIZE, '\n');
			cout << "The keyword is: ";
			cin >> key;
			endecrypt(input, strlen(input), key, strlen(key), output, DECRYPT);
			cout << "The plaintext is: " << output << endl << endl;
		}
	} while (option != 3);

	return 0;
}

