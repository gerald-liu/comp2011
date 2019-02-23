// Based on the skeleton code

#include <iostream>

using namespace std;

// Check whether the given num is a three-digit number
// return true if it is, false otherwise
bool isThreeDigits(int num) {
	return (num / 1000 == 0 && num / 100 > 0);
}

// Check whether the digits of the given num are in decreasing order
// return true if it is, false otherwise
bool isDecreasingOrder(int num) {
	int next_digit = -1;
	while (num > 0) {
		if (num % 10 <= next_digit) return false;
		next_digit = num % 10;
		num /= 10;
	}
	return true;

	// or, for 3-digit numbers only:
	// return (num / 100 > num % 100 / 10) && (num % 100 / 10 > num % 10);
}

// Reverse the order of the digits of the given 3-digit num
// The reversed number is returned
// For example, reverseDigit(789) returns 987
int reverseDigit(int num) {
	int reversed = 0;
	while (num > 0) {
		reversed *= 10;
		reversed += num % 10;
		num /= 10;
	}
	return reversed;
}

// Check whether a given 3-digit decreasing order num follows 1089 magic
// return true if it is, false otherwise
// The function should also print out the calculation of 1089
// refer to the sample outputs
bool isMagic(int num) {
	int tmp = num - reverseDigit(num);
	return (tmp + reverseDigit(tmp) == 1089);
}

int main() {
	cout << "=================================================" << endl;
	cout << "Magic 1089" << endl;
	cout << "=================================================" << endl;

	cout << "Please input an arbitrary range:" << endl;
	int min, max;
	cin >> min >> max;

	while (min > max) {
		cout << "Invalid range!" << endl;
		cout << "Please input an arbitrary range:" << endl;
		cin >> min >> max;
	}

	int count_decreasing = 0;
	int count_magic = 0;

	for (int i = min; i <= max; i++)
		if (isThreeDigits(i))
			if (isDecreasingOrder(i)){
				count_decreasing++;
				if (isMagic(i))
					count_magic++;
			}

	cout << "There\'re " << count_decreasing << " 3-digit decreasing order number in the range." << endl;
	if (count_decreasing == count_magic)
		cout << "ALL follow magic 1089 rule!" << endl;
	else
		cout << "Only " << count_magic << " follow magic 1089 rule." << endl;
	return 0;
}
