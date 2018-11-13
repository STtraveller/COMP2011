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
void digits_to_barcode(const char barcodes[][6], const char input_string[], char output_barcode[]) {
  strcpy(output_barcode, "");
  int sum = 0;
  int temp;
  for (int i = 0; input_string[i] != NULL_CHAR && input_string[i] != '\n'; i++) {
    temp = static_cast <int> (input_string[i] - '0');
    sum += temp;
    strcat(output_barcode, barcodes[temp]);
  }
  temp = (10 - sum % 10) % 10;
  strcat(output_barcode, barcodes[temp]);
}

/*
 * Function: barcode_to_digits
 * Return true and store the digits in digit_string if barcode is valid;
 * Return false otherwise
 */

/* ADD YOUR CODE HERE */
bool barcode_to_digits(const char barcodes[][6], const char input_string[], char digit_string[]) {
  if (strlen(input_string) % 5 != 0) {
    return false;
  }
  char temp[6];
  int sum = 0, i = 0;
  strcpy(digit_string, "");
  for (; i < strlen(input_string) / 5; i++) {
    for (int j = 0; j < 5; j++) {
      temp[j] = input_string[i*5 + j];
    }
    temp[5] = NULL_CHAR;
    for (int j = 0; j < 11; j++) {
      if (strcmp(barcodes[j],temp) == 0) {
        digit_string[i] = static_cast <char> (j + '0');
        sum += j;
        break;
      }
      if (j == 10) {
        return false;
      }
    }
  }
  if (sum % 10 == 0) {
    digit_string[i - 1] = NULL_CHAR;
    return true;
  } else {
    return false;
  }
}

void add_leading_zeros(const char input_string[], char string_with_zeros[], int length) {
    strcpy(string_with_zeros, input_string);
    char temp[501];
    for (int i = strlen(input_string); i < length; i++) {
        strcpy(temp, "0");
        strcat(temp, string_with_zeros);
        strcpy(string_with_zeros, temp);
    }
}

bool generate_UPC_A_barcode(const char barcodes[][6], const char input_string[], char output_barcode[]) {
    if (strlen(input_string) > 11) {
        return false;
    }
    char string_with_zeros[12];
    add_leading_zeros(input_string, string_with_zeros, 11);
    const char startAndEndMarker[4] = "|'|";
    const char middleMarker[6] = "'|'|'";
    int sum = 0, temp;
    strcpy(output_barcode, startAndEndMarker);
    for (int i = 0; i < 11; i++) {
        temp = static_cast <int> (string_with_zeros[i] - '0');
        sum += (i % 2)? temp: temp * 3;
        strcat(output_barcode, barcodes[temp]);
        if (i == 5) {
            strcat(output_barcode, middleMarker);
        }
    }
    temp = (10 - sum % 10) % 10;
    strcat(output_barcode, barcodes[temp]);
    strcat(output_barcode, startAndEndMarker);
    return true;
}

bool decode_UPC_A_barcode(const char barcodes[][6], const char input_string[], char digit_string[]) {
    if (strlen(input_string) != 71) {
        return false;
    }
    char temp[6];
    const char startAndEndMarker[4] = "|'|";
    const char middleMarker[6] = "'|'|'";
    int j = 0, counter = 0;
    strcpy(digit_string, "");
    for (int i = 0; i < 71; i++) {
        if (i < 3) {
            temp[j] = input_string[i];
            j++;
            if (j == 3) {
                temp[j] = NULL_CHAR;
                if (strcmp(startAndEndMarker,temp) != 0) {
                    return false;
                }
                j = 0;
            }
        } else if (i < 33) {
            temp[j] = input_string[i];
            j++;
            if (j == 5) {
                temp[j] = NULL_CHAR;
                for (int k = 0; k < 10; k++) {
                    if (strcmp(barcodes[k],temp) == 0) {
                        digit_string[counter] = static_cast <char> (k + '0');
                        counter++;
                        break;
                    }
                }
                j = 0;
            }
        } else if (i < 38) {
            temp[j] = input_string[i];
            j++;
            if (j == 5) {
                temp[j] = NULL_CHAR;
                if (strcmp(middleMarker,temp) != 0) {
                    return false;
                }
                j = 0;
            }
        } else if (i < 68) {
            temp[j] = input_string[i];
            j++;
            if (j == 5) {
                temp[j] = NULL_CHAR;
                for (int k = 0; k < 10; k++) {
                    if (strcmp(barcodes[k],temp) == 0) {
                        digit_string[counter] = static_cast <char> (k + '0');
                        counter++;
                        break;
                    }
                }
                j = 0;
            }
        } else {
            temp[j] = input_string[i];
            j++;
            if (j == 3) {
                temp[j] = NULL_CHAR;
                if (strcmp(startAndEndMarker,temp) != 0) {
                    return false;
                }
                j = 0;
            }
        }
    }
    digit_string[counter] = NULL_CHAR;
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        if ((i % 2 == 1) || (i == 11)) {
            sum += static_cast <int> (digit_string[i] - '0');
        } else {
            sum += (static_cast <int> (digit_string[i] - '0')) * 3;
        }
    }
    if (sum % 10 != 0) {
        return false;
    }
    digit_string[counter - 1] = NULL_CHAR;
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
    const int exitcode = 6;

	do {
		cout << endl;
		cout << "Welcome to the barcode program!" << endl;
		cout << "Please select an option to proceed:" << endl;
		cout << "1. Convert digits to barcode" << endl;
		cout << "2. Revert digits from barcode" << endl;
        cout << "3. Add leading zeros" << endl;
        cout << "4. Generate pseudo UPC-A barcode" << endl;
        cout << "5. Decode pseudo UPC-A barcode" << endl;
		cout << exitcode << ". Exit" << endl << endl;
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
                cout << "Please enter the digit sequence: ";
                cin >> input_string;
                int input_length;
                cout << "Please enter the desired length: ";
                cin >> input_length;

                char string_with_zeros[501];
                add_leading_zeros(input_string, string_with_zeros, input_length);
                digits_to_barcode(barcodes, string_with_zeros, output_barcode);
                cout << "The barcode is: " << output_barcode << endl;
				break;

            case 4:
                cout << "Please enter the digit sequence: ";
                cin >> input_string;

                if (generate_UPC_A_barcode(barcodes, input_string, output_barcode)) {
                    cout << "The pseudo UPC-A barcode is: " << output_barcode << endl;
                } else {
                    cout << "Invalid digit sequence" << endl;
                }
                break;

            case 5:
                cout << "Please enter the pseudo UPC-A barcode: ";
                cin >> input_string;

                if (decode_UPC_A_barcode(barcodes, input_string, digit_string))
                    cout << "The digit sequence is: " << digit_string << endl;
                else
                    cout << "Invalid barcode." << endl;
                break;

            case exitcode:
                break;

			default:
				cout << "Invalid option. Please try again." << endl;
				break;
		}

	} while (option != exitcode);

	return 0;
}
