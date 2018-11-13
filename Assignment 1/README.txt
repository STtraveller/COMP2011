Compile:                    g++ -o pa1.out pa1.cpp
Mark it as executable:      chmod +x pa1.out
Run:                        ./pa1.out


Functionalities:

Mode 1,2:   As the original assignment


Mode 3:     Add Leading Zeros
Input:  input_string:   a random digit sequence
        input_length:   the desired length of the digit sequence
Output: output_barcode: a barcode with length (input_length + 1) * 5
This function will add leading zeros to the digit sequence to make the sequence to a specific length
This function will return the original sequence if the length of input_string is longer than input_length

Example (console i/o):
Please enter the digit sequence: 1024
Please enter the desired length of the digit sequence: 10
The barcode is: '''||'''||'''||'''||'''||'''||||''''''|||'|''|'''||''|' (which is representing 0000001024(3))

Idea:       As some records require a fixed length of the digit sequence (for example: staff number 00001), this function is coded to ease this process and reduce the possibility of typing wrong amount of leading zeros to the sequence


Mode 4:     Generate pseudo UPC-A barcode
(pseudo UPC-A barcode as i am using the barcode coding scheme of the assignment instead of the real one)
(assignment: 5 modules for one digit / real: 7 modules for one digit)
(assignment pseudo UPC-A barcode length: 12*5+3*2+5 = 71 / real pseudo UPC-A barcode length: 95)
composition of UPC-A barcode: a digit sequence of length 12, last digit is the check digit
for details of the calculation of check digit: http://www.makebarcode.com/specs/upc_a.html

Input:  input_string:    a random digit sequence shorter or equal to 11 (check digit will be added by the function)
Output: output_barcode:  a barcode with length 71 (formatting with the UPC-A barcode Start/Middle/End patterns and assignment given barcode scheme)
This function receives a digit sequence (input_string), add leading zeros to make it length of 11, add the check digit to make it length of 12, and generate the barcode in the form of UPC-A barcode with the Start (|'|), Middle ('|'|'), End (|'|) patterns added

Example (console i/o):
Please enter the digit sequence: 1024
The pseudo UPC-A barcode is: |'|'''||'''||'''||'''||'''||'''||'|'|''''||||''''''|||'|''|'''|'||''|'|


Mode 5: Decode pseudo UPC-A barcode
(reverse of Mode 4)

Input:  input_string:    a barcode with length 71 (formatting with the UPC-A barcode Start/Middle/End patterns and assignment given barcode scheme)
Output: output_barcode:  a digit string of length 11 (check digit is not displayed)

Example (console i/o):
Please enter the pseudo UPC-A barcode: |'|'''||'''||'''||'''||'''||'''||'|'|''''||||''''''|||'|''|'''|'||''|'|
The digit sequence is: 00000001024
