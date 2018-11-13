/*
 * Lab 8 Skeleton
 *
 *  Created on: Oct 4, 2018
 *      Author: kevinw
 */


#include "header.h"


//You need to validate the filename by the following rules:
//1) It does not contain any of these three characters \ $ *
//2) It ends with the extension .lab8
//Note: In fact there are some other naming restrictions but to keep it simple we impose only these two rules.
bool check_filename(string filename) {
    
    // Add your code here.
    if (filename.length() <= 5) {
        return false;
    }
    for (char s: {'\\','$','*'}) {
        if (filename.find(s, 0) < filename.length()) {
            return false;
        }
    }
    if (filename.substr(filename.length() - 5, 5).compare(".lab8") != 0) {
        return false;
    }
    return true;
}


//Given the filename, save the current map and fire_count to the file.
//If the file already exists, erase the content inside and overwrite the content.
//We assume the filename entered is valid and does not contain directory symbols, such as, \ (in windows) or / (in mac/linux)
void save(string filename, const char map[][WIDTH], int fire_count) {
    
    // Add your code here.
    ofstream outfile(filename);
    outfile << fire_count << endl;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            outfile << map[row][col];
        }
        outfile << endl;
    }
    outfile.close();
}


//Given the filename, load the map into the map array and the variable fire_count.
//If the file is missing, output "No such file exist" and return false.
//If the file can be found, return true after the data is loaded.
bool load(string filename, char map[][WIDTH], int& fire_count) {
    
    // Add your code here.
    ifstream infile(filename);
    if (!infile) {
        return false;
    }
    infile >> fire_count;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            infile >> map[row][col];
        }
    }
    infile.close();
    return true;
}


int main() {
    srand(time(NULL));
    
    char map[HEIGHT][WIDTH];
    
    int fire_count = 0;
    
    char input;
    bool load_success = false;
    do {
        cout << "Choose from below: " << endl
        << "1) Load a Game" << endl
        << "2) Start a new Game" << endl;
        
        cin >> input;
        if (input == '1') {
            // New for Lab 8
            cout << "Enter your filename: " << endl;
            string filename;
            cin >> filename;
            load_success = load(filename, map, fire_count);
            
            if (!load_success) {
                cout << "Load file failed, please choose again. " << endl;
                continue;
            }
        } else if (input == '2') {
            for (int row = 0; row < HEIGHT; row++)
                for (int col = 0; col < WIDTH; col++)
                    map[row][col] = EMPTY;
            
            placeShip(map, 5);
            placeShip(map, 4);
            placeShip(map, 3);
            placeShip(map, 3);
            placeShip(map, 2);
            
        } else {
            cout << "Wrong option. Please choose again" << endl;
        }
    } while (!(input == '2' || (input == '1' && load_success)));
    
    
    cout << "Are you playing in the debug/demo mode? (Y for yes; no Otherwise)" << endl;
    cin >> input;
    bool debug = (input == 'Y');
    
    // New for Lab 8
    if (debug) {
        cout << "check_filename 1: " << boolalpha << check_filename("abc.lab8") << endl;
        cout << "check filename 2: " << boolalpha << !check_filename("def") << endl;
        cout << "check filename 3: " << boolalpha << !check_filename("de$f.lab8") << endl;
        cout << "check filename 4: " << boolalpha << !check_filename("def.lab8.w") << endl;
        cout << "check filename 5: " << boolalpha << !check_filename("de*f,lab8") << endl;
    }
    
    
    while (!isGameOver(map)) {
        printMap(map, debug);
        
        int col, row;
        cout << "\nFire count: " << fire_count << endl;
        cout << "\nPlease enter your col and row separated by a space: ";
        cout << "\nYou can also enter an invalid coordinate to save your game. " << endl;
        cin >> col >> row;
        
        // New for Lab 8
        if (col < 0 || col >= WIDTH || row < 0 || row >= HEIGHT) {
            //cout << "Invalid coordinate, please enter again." << endl;
            bool filename_ok;
            string filename;
            do {
                cout << "Please enter your filename" << endl;
                cin >> filename;
                filename_ok = check_filename(filename);
            } while (!filename_ok);
            save(filename, map, fire_count);
            continue;
        }
        
        if (isHit(map, col, row))
            cout << "It is a hit! " << endl << endl;
        else
            cout << "It is a miss :( " << endl << endl;
        
        fire_count++;
        
        
        
    }
    
    cout << "Game over. You have fire " << fire_count
    << " cannons to destroy your enemy battleships." << endl;
    
    if (fire_count == 17)
        cout << "Super! You make the impossible possible!" << endl;
    else if (fire_count < 40)
        cout << "Brilliant!" << endl;
    else if (fire_count < 70)
        cout << "Good shot!" << endl;
    else
        cout << "Improve your skill next time!" << endl;
    
    printMap(map);
}

