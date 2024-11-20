#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <windows.h> // cho Windows

using namespace std;

class Card {
public:
    string suit;
    string rank;
    int value;

    Card(string r, string s, int v) : rank(r), suit(s), value(v) {}
};

class Deck {
private:
    vector<Card> cards;
public:
    Deck() {
        string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11}; // Ace will be handled separately

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cards.push_back(Card(ranks[j], suits[i], values[j]));
            }
        }
        shuffle();
    }

    void shuffle() {
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < cards.size(); i++) {
            int r = rand() % cards.size();
            swap(cards[i], cards[r]);
        }
    }

    Card deal() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
};

class Hand {
private:
    vector<Card> cards;
public:
    void addCard(Card card) {
        cards.push_back(card);
    }

    int getValue() {
        int value = 0;
        int aces = 0;
        for (Card card : cards) {
            value += card.value;
            if (card.rank == "Ace") {
                aces++;
            }
        }
        while (value > 21 && aces > 0) {
            value -= 10; // count Ace as 1 instead of 11
            aces--;
        }
        return value;
    }

    void display() {
        for (Card card : cards) {
            cout << card.rank << " of " << card.suit << endl;
        }
    }
};

void delay(int milliseconds) {
    Sleep(milliseconds);
}

int main() {
    char playAgain;
    do {
        system("cls");
        Deck deck;
        Hand playerHand, dealerHand;

        cout << "Dealing cards...\n";
        delay(1000);

        // Deal two cards to player and dealer
        playerHand.addCard(deck.deal());
        delay(500);
        playerHand.addCard(deck.deal());
        delay(500);
        dealerHand.addCard(deck.deal());
        delay(500);
        dealerHand.addCard(deck.deal());

        cout << "\nYour hand:" << endl;
        playerHand.display();
        cout << "Value: " << playerHand.getValue() << endl;

        cout << "\nDealer's hand:" << endl;
        cout << dealerHand.getValue() << " (One card hidden)" << endl;

        // Player's turn
        char choice;
        do {
            cout << "\nDo you want to (h)it or (s)tand? ";
            cin >> choice;

            if (choice == 'h') {
                cout << "\nDealing card...\n";
                delay(1000);
                
                playerHand.addCard(deck.deal());
                cout << "Your hand:" << endl;
                playerHand.display();
                cout << "Value: " << playerHand.getValue() << endl;
            }

            if (playerHand.getValue() > 21) {
                cout << "\nYou bust! Dealer wins." << endl;
                break;
            }
        } while (choice != 's');

        // Nếu người chơi chưa bust thì mới tới lượt dealer
        if (playerHand.getValue() <= 21) {
            cout << "\nDealer's turn...\n";
            delay(1000);
            
            cout << "Dealer's hand:" << endl;
            dealerHand.display();
            
            while (dealerHand.getValue() < 17) {
                cout << "\nDealer draws a card...\n";
                delay(1000);
                
                dealerHand.addCard(deck.deal());
                dealerHand.display();
            }

            // Determine the winner
            cout << "\nFinal hands:" << endl;
            cout << "Your hand value: " << playerHand.getValue() << endl;
            cout << "Dealer's hand value: " << dealerHand.getValue() << endl;

            delay(1000);

            if (dealerHand.getValue() > 21) {
                cout << "Dealer busts! You win!" << endl;
            } else if (playerHand.getValue() > dealerHand.getValue()) {
                cout << "You win!" << endl;
            } else if (playerHand.getValue() < dealerHand.getValue()) {
                cout << "Dealer wins!" << endl;
            } else {
                cout << "It's a tie!" << endl;
            }
        }

        // Hỏi người chơi có muốn chơi tiếp không
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing! Goodbye!\n";
    return 0;
}