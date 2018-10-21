//
//  skeleton.cpp
//  Magic Square
//
//  Created by Yishuo ZHANG on 2018/10/11.
//  Copyright @ 2018 Yishuo ZHANG. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

//print the 2D view of magic square of size N
void print_square(int arr[], int N) {
    // insert your code here
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i * N + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//check whether the given array forms a magic square
bool check(int arr[], int N, int magic_const) {
    // insert your code here
	int sum;
	// col
	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += arr[j * N + i];
		}
		if (sum != magic_const) {
			return false;
		}
	}


	// col
	for (int i = 0; i < N; i++) {
		sum = 0;
		for (int j = 0; j < N; j++) {
			sum += arr[i * N + j];
		}
		if (sum != magic_const) {
			return false;
		}
	}

	// forward diagonal
	sum = 0;
	for (int i = 0; i < N; i++) {
		sum += arr[i * N + i];
	}
	if (sum != magic_const) {
		return false;
	}

	// backward diagonal
	sum = 0;
	for (int i = 0; i < N; i++) {
		sum += arr[i * N + N - i - 1];
	}
	if (sum != magic_const) {
		return false;
	}

	// passed all test
	return true;
}

//generate all the permutations recursively
void permute(int arr[], int i, int N, int magic_const) {
    // insert your code here
	if (i == N * N) {
		/*
		print_square(arr, N);
		cout << check(arr, N, magic_const) << endl;
		*/
		if (check(arr, N, magic_const)) {
			print_square(arr, N);
		}
	} else {
		for (int j = i; j < N * N; j++) {
			swap(arr[i], arr[j]);
			permute(arr, i + 1, N, magic_const);
			swap(arr[i], arr[j]);
		}
	}
}

int main() {
	int N = 0;
	int magic_const = 0;

	cout << "Please enter the value of N: ";
	cin >> N;

	//define a 1D array to save the permutation.
	int array[5 * 5];
	for (int i = 0; i < N * N; i++) {
		array[i] = i + 1;
	}

	//compute the magic constant
	magic_const = (N * N * N + N) / 2;

	//call resursive function
	permute(array, 0, N, magic_const);

	return 0;
}
