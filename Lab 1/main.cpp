#include <iostream>
#include <string>
using namespace std;

int main() {
	while (true) {
		int year;
		cout << "Which year were you born in?" << endl;
		cin >> year;
		if (year < 1900) {
			cout << "Take care! Bye!" << endl;
			break;
		} else if (year > 2018) {
			cout << "You come from the future! I'm scared! Bye!" << endl;
			break;
		}
		const string list[12] = {"Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Roaster", "Dog", "Pig"};
		cout << "You were born in the year of " << list[(year - 1900) % 12] << "!\n\n";
	}
	return 0;
}
