#include <iostream>
#include <cstring>

using namespace std;

const char NULL_CHAR = '\0';

/*
 * Function: digits_to_barcode
 * To convert the given digit string to a barcode string
 * Return nothing (void)
 */

/* ADD YOUR CODE HERE */
void digits_to_barcode(const char barcode_ref[][6], const char* digits_str, char* out_barcodes) {
	int j = 0, checksum = 0;
	for (int i = 0; digits_str[i] != NULL_CHAR; i++, j+=5) {
		for (int k = 0; k < 5; k++)
			out_barcodes[j + k] = barcode_ref[digits_str[i] - '0'][k];
		checksum += digits_str[i] - '0';
	}
	int check_digit = 10 - (checksum % 10);
	if (check_digit == 10)
		check_digit = 0;
	for (int k = 0; k < 5; k++)
		out_barcodes[j + k] = barcode_ref[check_digit][k];
	out_barcodes[j + 5] = NULL_CHAR;
}

/*
 * Function: barcode_to_digits
 * Return true and store the digits in digit_string if barcode is valid;
 * Return false otherwise
 */

/* ADD YOUR CODE HERE */
bool barcode_to_digits(const char barcode_ref[][6], const char* barcode_str, char* out_digits) {
	int digits[101];
	char curr_digit[5];
	int j = 0, k = 0;
	for (int i = 0; barcode_str[i] != NULL_CHAR; i++) {
		curr_digit[k++] = barcode_str[i];
		if (k == 5) {
			bool found = false;
			for (int d = 0; d < 10; d++) {
				int b = 0;
				for (; b < 5; b++)
					if (barcode_ref[d][b] != curr_digit[b])
						break;
				if (b == 5) {
					found = true;
					digits[j] = d;
					j++;
					break;
				}
			}
			if (!found)
				return false;
			k = 0;
		}
	}
	int checksum = 0;
	for (int m = 0; m < j; m++)
		checksum += digits[m];
	if (checksum % 10 != 0)
		return false;
	out_digits[--j] = NULL_CHAR;
	for (j--; j >= 0; j--)
		out_digits[j] = '0' + digits[j];
	return true;
}

/*
 * Function: main
 * You are NOT ALLOWED to change ANY CODE in this function
 */
int main()
{
	const char barcodes[][6]=
		{
			"'''||",
			"||'''",
			"|'|''",
			"|''|'",
			"|'''|",
			"'||''",
			"'|'|'",
			"'|''|",
			"''||'",
			"''|'|"
		};
	
	int option;
	char input_string[501];		// a barcode or digit string
	
	do {
		cout << endl;
		cout << "Welcome to the barcode program!" << endl;
		cout << "Please select an option to proceed:" << endl;
		cout << "1. Convert digits to barcode" << endl;
		cout << "2. Revert digits from barcode" << endl;
		cout << "3. Exit" << endl << endl;
		
		cout << "Your option: ";
		cin >> option;
		
		switch(option)
		{
			case 1:
				cout << "Please enter the digit sequence: ";
				cin >> input_string;
			
				char output_barcode[2506];		// barcode string
				digits_to_barcode(barcodes, input_string, output_barcode);
				cout << "The barcode is: " << output_barcode << endl;
				break;
				
			case 2:
				cout << "Please enter the barcode: ";
				cin >> input_string;
			
				char digit_string[101];
				if (barcode_to_digits(barcodes, input_string, digit_string)) 
					cout << "The digit sequence is: " << digit_string << endl;
				else
					cout << "Invalid barcode." << endl;
				break;
			
			case 3:
				break;
			
			default:
				cout << "Invalid option. Please try again." << endl;
				break;
		}
		
	} while (option != 3);
	
	return 0;
}
