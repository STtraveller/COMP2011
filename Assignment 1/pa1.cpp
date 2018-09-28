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


/*
 * Function: barcode_to_digits
 * Return true and store the digits in digit_string if barcode is valid;
 * Return false otherwise
 */

/* ADD YOUR CODE HERE */




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
