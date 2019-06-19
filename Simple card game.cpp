/*
Programmer: Bintao Wang
Program: bwangP8.cpp
Purpose: For each time you hit Enter, the computer will automatically play the war with itself.
Initially, there are two decks, and the computer will take the top of the deck and compare them,
the bigger number wins, and the winner gets the cards. If there is a draw, computer will take
the next card on the deck and do it again. When a player is out of card he will lose.

Input: name of two players. And hit enter for each round. That's all.
Output: The program will show the result of each turn, and print out who wins the game at last.
*/

#include<iostream>
#include<cstdlib>
#include<assert.h>
#include<time.h>
#include<string>
#include<queue>
#include<iomanip>
using namespace std;

struct card {
    int value;	// point value of card (2-14; Ace is high)
    string suit;	// Hearts, Diamonds, Clubs, Spades
    string face;	// Jack, Queen, King, or Ace (or none)
    bool dealt;	// if this card has been dealt
    int size;
};

class deckOfCards {
    card deck [52];   	// note: no constant here because things are hardcoded for a standard 52 card deck


    int numberDealt; 	// number of cards dealt so far

public:
    deckOfCards ();
    card dealCard ();
    void Match (card, card,int,string,string);
    queue<card> play1;
    queue<card> play2;
    queue<card> computer;
};

deckOfCards :: deckOfCards () {
/*
 *  Constructor.
 *  Set up a standard set of 52 cards.
 */
    int i;

    numberDealt = 0;

    for (i = 0; i < 52; i++) {
      deck[i].dealt = false;
      if (i < 13) {
         deck[i].value = i+2;
         deck[i].suit = "Hearts";
      } else if (i < 26) {
         deck[i].value = i-11;
         deck[i].suit = "Diamonds";
      } else if (i < 39) {
         deck[i].value = i-24;
         deck[i].suit = "Clubs";
      } else {
         deck[i].value = i-37;
         deck[i].suit = "Spades";
      }

      if (deck[i].value == 11)
         deck[i].face = "Jack";
      else if (deck[i].value == 12)
         deck[i].face = "Queen";
      else if (deck[i].value == 13)
         deck[i].face = "King";
      else if (deck[i].value == 14)
         deck[i].face = "Ace";
      else
         deck[i].face = "";
    }
}

card deckOfCards :: dealCard () {
/*
 * Deal one card from deck.
 * Precondition: Deck has been created
 * Postcondition: Returns a random card from the deck
 */

    int index;

    assert (numberDealt < 52);
    srand(time(NULL));
    index = rand () % 52;	// random number in range 0-51
    while (deck[index].dealt) {
      index = rand () % 52;
    }
    deck[index].dealt = true;
    numberDealt++;
    return deck[index];
}


/*
 * sample main() showing use of the deckOfCards class;
 * it is not sophisticated!
 */
void deckOfCards::Match(card One, card Two,int Hand,string P1, string P2)
{
    cout << "Hand: " << Hand << endl << endl;
    cout << P1 << "                            " << P2 << endl;
    cout << "------------------------------------------------" << endl;
    if(One.value>Two.value){
        play1.push(One);
        play1.push(Two);
        while(!computer.empty()){
            play1.push(computer.front());
            computer.pop();
        }
        if(One.value>10){
            cout << One.face << " of " << One.suit;
        }
        else{
            cout << One.value << " of " << One.suit;
        }
        cout << setw(25);
        if(Two.value>10){
            cout << Two.face << " of " << Two.suit <<endl;
        }
        else{
            cout << Two.value << " of " << Two.suit <<endl;
        }
        cout << "Wins hand!                                " << endl;
        cout << "Press <enter> to continue..." << endl << endl << endl;
    }
    else if(Two.value>One.value){
        play2.push(One);
        play2.push(Two);
        while(!computer.empty()){
            play2.push(computer.front());
            computer.pop();
        }
        if(One.value>10){
            cout << One.face << " of " << One.suit;
        }
        else{
            cout << One.value << " of " << One.suit;
        }
        cout << setw(25);
        if(Two.value>10){
            cout << Two.face << " of " << Two.suit <<endl;
        }
        else{
            cout << Two.value << " of " << Two.suit <<endl;
        }
        cout << "                                Wins hand!" << endl;
        cout << "Press <enter> to continue..." << endl << endl << endl;
    }
    else{
        computer.push(play1.front());
        computer.push(One);
        computer.push(play2.front());
        computer.push(Two);
        play1.pop();
        play2.pop();
        card temp1, temp2;
        temp1 = play1.front();
        temp2 = play2.front();
        play1.pop();
        play2.pop();
        Match(temp1,temp2,Hand,P1,P2);
        cout << "Hand: " << Hand << endl << endl;
        cout << P1 << "                            " << P2 << endl;
        cout << "------------------------------------------------" << endl;
        if(One.value>10){
            cout << One.face << " of " << One.suit;
        }
        else{
            cout << One.value << " of " << One.suit;
        }
        cout << setw(25);
        if(Two.value>10){
            cout << Two.face << " of " << Two.suit <<endl;
        }
        else{
            cout << Two.value << " of " << Two.suit <<endl;
        }
        cout << "                   -WAR-                        " << endl;
        cout << "secret card                     secret card     " << endl;
    }
}

int main () {
    deckOfCards game;
    string P1,P2;
    int one,two;
    int hand=1;
    int i;
    cout << "Name of player1: ";
    cin >> P1;
    cout << "Name of player2: ";
    cin >> P2;
    for (i = 0; i < 26; i++) {
        game.play1.push(game.dealCard());
        //cout << game.play1.front().value << " " << game.play1.front().face << " of " << game.play1.front().suit << endl;
    }
    cout << endl << endl << endl;
        for (i = 0; i < 26; i++) {
        game.play2.push(game.dealCard());
        //cout << game.play2.front().value << " " << game.play2.front().face << " of " << game.play2.front().suit << endl;
    }


    while(game.play1.size()!=0 && game.play2.size()!=0){
        cin.get();
        card temp1, temp2;
        temp1 = game.play1.front();
        temp2 = game.play2.front();
        game.play1.pop();
        game.play2.pop();
        game.Match(temp1,temp2,hand,P1,P2);
        hand++;

    }
    if(game.play1.empty()){
        cout << "================================================" << endl << endl;
        cout << "                           " << P1 << "     wins" << endl;
    }
    else{
        cout << "================================================" << endl << endl;
        cout << "                           " << P2 << "     wins" << endl;
    }
    return 0;
}
