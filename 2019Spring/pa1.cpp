/*
 * COMP2011 (Spring 2019) Assignment 1: The hailstone sequence
 *
 * Student name: Gerald Liu
 * Student ID: 36258909
 * Student email: 36258909+gerald-liu@users.noreply.github.com
 * Student lab section: LA0
 */

#include <iostream>
using namespace std;

const int HISTOGRAM_SIZE = 5;
const int HISTOGRAM_STEP = 10;

/* std::min from <algorithm>
 * (defined in bits/stl_algobase.h already)
 */
// template <typename T>
// const T& min(const T& a, const T& b) {
// 	return (a < b) ? a : b;
// }

/* std::clamp from <algorithm> (since c++17) */
template <typename T>
const T& clamp(const T& v, const T& lo, const T& hi) {
	return (v < lo) ? lo : (hi < v) ? hi : v;
}

int getHailstoneNum(int n) {
	if (n % 2) // odd
		return 3 * n + 3;
	else // even
		return n / 2;
}

int getHailstoneSequence(int n, bool print = false) {
	int counter = 0;
	while (true) {
		counter++;
		if (print) {
			cout << n;
			if (counter % 8)
				cout << '\t';
			else
				cout << '\n';
		}
		if (n == 3) {
			if (print)
				cout << '\n';
			break;
		}
		n = getHailstoneNum(n);
	}
	return counter;
}

/* prints the hailstone sequence for n. */
void printHailstoneSequence(int n) {
	//Finish this function. Type your code below.
	getHailstoneSequence(n, true);
}

/* returns the length of the shortest hailstone sequence in the range [start, end]. */
int shortestHailstoneSequenceLength(int start, int end) {
	//Finish this function. Type your code below.
	int minLen = 100; // arbitrary large number
	for (int i = start; i <= end; i++)
		minLen = min(minLen, getHailstoneSequence(i));
	return minLen;
}

/* prints the histogram of the distribution of hailstone sequence lengths for the sequences in [start, end]. */
void printHistogram(int start, int end) {
	//Finish this function. Type your code below.
	int groups[HISTOGRAM_SIZE] = {0};
	for (int i = start; i <= end; i++)
		groups[clamp((getHailstoneSequence(i) - 1) / HISTOGRAM_STEP, 0, HISTOGRAM_SIZE - 1)]++;
	for (int i = 0; i < HISTOGRAM_SIZE; i++) {
		if (!groups[i])
			cout << 0;
		for (int j = 0; j < groups[i]; j++)
			cout << '*';
		cout << '\n';
	}
}

/*
 * main() is the entry point of the program.
 * Do NOT modify it in any way.
 */
int main() {
	//Define the variable for getting the user's choice.
	int choice;

	//Print the menu.
	cout << "Assignment 1: The hailstone sequence" << endl;
	cout << "1. Print a hailstone sequence" << endl;
	cout << "2. Find the shortest hailstone sequence length" << endl;
	cout << "3. Print a hailstone histogram" << endl;
	cout << endl;
	cout << "Enter your choice: ";

	//Get the choice.
	cin >> choice;

	//Perform a basic input validation.
	while(choice<1 || choice>3)
	{
		cout << "Please enter a valid choice: ";
		cin >> choice;
	}

	cout << endl;

	if(choice==1) //Print a hailstone sequence.
	{
		//Get n.
		int n;
		cout << "Enter an integer n: ";
		cin >> n;

		//Perform a basic input validation.
		while(n<1 || n>10000)
		{
			cout << "Please enter a valid n: ";
			cin >> n;
		}

		//Output the result.
		cout << endl;
		cout << "The hailstone sequence for " << n << " is:" << endl;
		printHailstoneSequence(n);
	}
	else if(choice==2) //Find the shortest hailstone sequence.
	{
		//Get start and end.
		int start, end;
		cout << "Enter the start and the end of the range: ";
		cin >> start >> end;

		//Perform a basic input validation.
		while(start>end || start<1 || end<1 || start>10000 || end>10000)
		{
			cout << "Please enter a valid range: ";
			cin >> start >> end;
		}

		//Output the result.
		cout << endl;
		cout <<  "The shortest hailstone sequence within the range [" << start << ", " << end << "] has a length of " << shortestHailstoneSequenceLength(start, end) << "." << endl;
	}
	else if(choice==3) // Print a hailstone histogram.
	{
		//Get start and end.
		int start, end;
		cout << "Enter the start and the end of the range: ";
		cin >> start >> end;

		//Perform a basic input validation.
		while(start>end || end-start>=100 || start<1 || end<1 || start>10000 || end>10000)
		{
			cout << "Please enter a valid range: ";
			cin >> start >> end;
		}

		//Output the result.
		cout << endl;
		cout << "The histogram of the hailstone sequence length distribution:" << endl;
		printHistogram(start, end);
	}

	//Exit the program.
	return 0;
}
