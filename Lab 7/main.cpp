#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_ITEM = 4;             // maximum number of items to be bid
const int MAX_NAME = 30;            // 1 + maximum length of player's name
const int INITIAL_MONEY = 200;      // the initial amount of money each player gets

// TODO: create Item struct here
struct Item {
    int id;
    int value;
};

// TODO: create Buyer struct here
struct Buyer {
    char name[MAX_NAME];
    int money_left;
    int n_items_bought;
    Item items_bought[MAX_ITEM];
};

// TODO: implement generate items function
void generate_items (Item items[])
{
    for (int i = 0; i < MAX_ITEM; i++) {
        // TODO: generate 4 items
        // with id from 1 to 4
        // and value random from 10 to 100 (inclusively)
        items[i].id = i + 1;
        items[i].value = rand() % 91 + 10;


        cout << "item " << items[i].id << " has value $" << items[i].value << endl;
    }
    cout << endl;
}

// TODO: implement the bought function
// this function used to manipulate/edit the buyer struct
// step 1: add the item to the items_bought array of that buyer
// step 2: deduce the bid money from money_left
void bought(Buyer &buyer, const Item &item, int bid)
{
    buyer.money_left -= bid;
    buyer.n_items_bought += 1;
    buyer.items_bought[buyer.n_items_bought - 1] = item;
}

// TODO: implement the calculate buyer score function
// this function calculate the game score of a player
// sum of the 'value of the items bought + money_left * 0.5
float cal_buyer_score (const Buyer &player)
{
    float score = 0;
    for (int i = 0; i < player.n_items_bought; i++) {
        score += player.items_bought[i].value;
    }
    score += player.money_left * 0.5;
    return score;
}

void print_results (const Buyer players[]) {
    float score1 = cal_buyer_score(players[0]);
    float score2 = cal_buyer_score(players[1]);
    cout << players[0].name << " has score: " << score1 << endl;
    cout << players[1].name << " has score: " << score2 << endl;

    // who win?
    if (score1 == score2) {
        cout << "draw!";
    } else if (score1 > score2) {
        cout << players[0].name << " won!";
    } else {
        cout << players[1].name << " won!";
    }
}

int main()
{
    Item items[MAX_ITEM]; // Items for bidding

    // initialize players
    Buyer players[] = {
        {
            "Player 1",     // name
            INITIAL_MONEY,  // money_left
            0               // n_items_bought
        },
        {
            "Player 2",     // name
            INITIAL_MONEY,  // money_left
            0               // n_items_bought
        }
    };

    srand(time(NULL));      // set random seed
    generate_items(items);  // generate items


    // iterate and sell all the items
    for (int current_item = 0; current_item < MAX_ITEM; current_item++) {
        int player_turn = rand() % 2;             // index indicate it is which player's turn (To be fair, randomize who is bidding on each item first)
        int current_bid = 0;                      // the current bid amount

        // TODO: write you logic here for players to bid, you will need to call the function "bought" when a player successfully bid the item
        // feel free to add more variables
        int bid;
        do {
            cout << "Bid for item " << items[current_item].id << ": (current bid: " << current_bid << ")\n";
            do {
                cout << players[player_turn].name << "'s turn ($" << players[player_turn].money_left << " remains) : (enter -1 to give up making a bid)\n";
                cin >> bid;
                if ((bid <= current_bid || bid > players[player_turn].money_left) && bid != -1) {
                    cout << "invalid amount\n";
                }
            } while ((bid <= current_bid || bid > players[player_turn].money_left) && bid != -1);
            if (bid == -1) {
                bought(players[(player_turn + 1) % 2], items[current_item], current_bid);
                cout << players[player_turn].name << " gives up\n" << players[(player_turn + 1) % 2].name << " bought item " << items[current_item].id << " with $" << current_bid << ". " << players[(player_turn + 1) % 2].name << " has $" << players[(player_turn + 1) % 2].money_left << " left. \n\n";
            } else {
                current_bid = bid;
                player_turn = (player_turn + 1) % 2;
            }
        } while(bid != -1);
    }

    print_results(players);
    return 0;
}
