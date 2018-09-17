#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void printBoard(int Heap[3]) {
  cout << "\nHeap\t0\t1\t2\nNumber\t" << Heap[0] << "\t" << Heap[1] << "\t" << Heap[2] << endl << endl;
}

int main() {
  int Heap[3], inputHeap, inputNumber, mode;
  bool empty = false;
  cout << "Please select mode:\n1. Player vs Player\n2. Player vs Computer\n";
  do {
    cin >> mode;
    if (!((mode == 1) || (mode == 2))) {
      cout << "Invalid input\nPlease input again\n";
    }
  } while (!((mode == 1) || (mode == 2)));
  srand(time(0));
  for (int i = 0; i < 3; i++) {
    Heap[i] = (rand() % 9) + 1;
  }
  switch (mode) {
    case 1: {
        bool player1 = false;
        do {
          player1 = !player1;
          printBoard(Heap);
          do {
            if (player1) {
              cout << "Player1's turn (input format: \"Heap Number\"): ";
            } else {
              cout << "Player2's turn (input format: \"Heap Number\"): ";
            }
            cin >> inputHeap >> inputNumber;
            if ((inputNumber > Heap[inputHeap]) || (inputNumber < 1)) {
              cout << "Invalid input\nPlease input again\n";
            }
          } while ((inputNumber > Heap[inputHeap]) || (inputNumber < 1));
          if (player1) {
            cout << "Player1 takes " << inputNumber << " from heap " << inputHeap << endl;
          } else {
            cout << "Player2 takes " << inputNumber << " from heap " << inputHeap << endl;
          }
          Heap[inputHeap] -= inputNumber;
          if ((Heap[0] == 0) && (Heap[1] == 0) && (Heap[2] == 0)) {
            empty = true;
          }
        } while (!empty);
        if (player1) {
          cout << "Player1 wins\n";
        } else {
          cout << "Player2 wins\n";
        }
        break;
      }
    case 2: {
        bool player = false;
        int numberOfNonEmptyHeaps;
        do {
          player = !player;
          printBoard(Heap);
          if (player) {
            do {
              cout << "Player's turn (input format: \"Heap Number\"): ";
              cin >> inputHeap >> inputNumber;
              if ((inputNumber > Heap[inputHeap]) || (inputNumber < 1)) {
                cout << "Invalid input\nPlease input again\n";
              }
            } while ((inputNumber > Heap[inputHeap]) || (inputNumber < 1));
            cout << "Player takes " << inputNumber << " from heap " << inputHeap << endl;
          } else {
            numberOfNonEmptyHeaps = 0;
            for (int i = 0; i < 3; i++) {
              if (Heap[i] != 0) {
                numberOfNonEmptyHeaps ++;
              }
            }
            switch (numberOfNonEmptyHeaps) {
              case 1: {
                  for (int i = 0; i < 3; i++) {
                    if (Heap[i] != 0) {
                      inputHeap = i;
                      inputNumber = Heap[i];
                    }
                  }
                  break;
                }
              case 2: {
                  int x = -1;
                  int y = -1;
                  for (int i = 0; i < 3; i++) {
                    if (Heap[i] != 0) {
                      if (x == -1) {
                        x = i;
                      } else {
                        y = i;
                      }
                    }
                  }
                  if (Heap[x] == Heap[y]) {
                    inputHeap = x;
                    inputNumber = Heap[x];
                  } else if (Heap[x] > Heap[y]) {
                    inputHeap = x;
                    inputNumber = Heap[x] - Heap[y];
                  } else {
                    inputHeap = y;
                    inputNumber = Heap[y] - Heap[x];
                  }
                  break;
                }
              case 3: {
                  if (Heap[0] == Heap[1]) {
                    inputHeap = 2;
                    inputNumber = Heap[inputHeap];
                  } else if (Heap[0] == Heap[2]) {
                    inputHeap = 1;
                    inputNumber = Heap[inputHeap];
                  } else if (Heap[1] == Heap[2]) {
                    inputHeap = 0;
                    inputNumber = Heap[inputHeap];
                  } else {
                    int max = 0;
                    int index;
                    for (int i = 0; i < 3; i++) {
                      if (Heap[i] > max) {
                        max = Heap[i];
                        index = i;
                      }
                    }
                    if (max == 3) {
                      inputHeap = 1;
                      inputNumber = Heap[inputHeap];
                    } else {
                      for (int i = 1; i <= Heap[index]; i++) {
                        if ((i != Heap[(index + 1) % 3]) && (i != Heap[(index + 2) % 3])) {
                          inputHeap = index;
                          inputNumber = Heap[inputHeap] - i;
                          break;
                        }
                      }
                    }
                  }
                  break;
                }
              }
              cout << "Computer takes " << inputNumber << " from heap " << inputHeap << endl;
            }
          Heap[inputHeap] -= inputNumber;
          if ((Heap[0] == 0) && (Heap[1] == 0) && (Heap[2] == 0)) {
            empty = true;
          }
        } while (!empty);
        if (player) {
          cout << "Player1 wins\n\n";
        } else {
          cout << "Computer wins\n\n";
        }
        break;
      }
  }
  return 0;
}
