/*
    0 - 13 Spades
    14 - 26 Clubs
    27 - 39 Diamonds
    40 - 52 Hearts
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

const int DECK_SIZE = 52;

struct Player{
    string name;
    int totalValue = 0;
};

struct Card{
    string flower;
    string name;
    int value = 0;

};


void menu();
void initDeck(vector<int> &deck);
void determineCard(int number, Card& newCard);
int drawRandomCard(vector<int> &deck);
void initHintFile(vector<string> &hintString);

void newHand(Player& human, Player& dealer, vector<int> &deck, Card& newCard, Card& dealerCard);
void hitMe(Player& human, vector<int> &deck, Card& newCard);
void stand(Player& dealer, vector<int> &deck, Card& newCard);
void hint(Player& dealer,Player& human, vector<string> &hintString, Card& dealerCard);
void hintSuggestion(Player& dealer,Player& human, Card& dealerCard);

void printGameValues(Player& dealer, Player& human);

int main()
{
    srand (time (0));
    Card newCard, dealerCard;
    Player human, dealer;
    vector<int> deck;
    vector<string> hintString;


    int choice;
    menu();
    cin >> choice;

    if(choice == 1){
        //start game
        bool gameOn = true;

        //Load the hint file
        initHintFile(hintString);


        //create deck
        initDeck(deck);
        newHand(human, dealer, deck, newCard, dealerCard);
        printGameValues(dealer, human);



        do{
            menu();
            cin >> choice;

            if(choice == 1){
                cout << "Finish the current session first" << endl;
            }
            else if (choice == 2){
                hitMe(human, deck, newCard);

                if(human.totalValue > 21){
                        gameOn = false;

                        cout << "You loose" << endl;
                    }

                printGameValues(dealer, human);

            }
            else if (choice == 3){

                bool houseBusts = false;
                do{
                    stand(dealer, deck, newCard);

                    if(dealer.totalValue > 21){
                        houseBusts = true;
                        gameOn = false;

                        cout << "House busts! You win!" << endl;
                    }

                }
                while (houseBusts == false);

                printGameValues(dealer, human);

            }
            else if (choice == 4){
                hint(dealer, human, hintString, dealerCard);

            }
            else if (choice == 5){
                gameOn = false;

            }
            else{
                gameOn = false;
            }




        }
        while(gameOn == true);


        //
    }
    else if(choice == 5){
        //Exit program
    }
    else{

        cout << "You need to start the game first" << endl;
    }






    return 0;
}

void menu(){

    cout << "*********************************** MENU ************************* \n 1) New Hand \n 2) Hit Me \n 3) Stand \n 4) Hint \n 5) Exit \n*******************************************************************" << endl;
}

void initDeck(vector<int> &deck){
    for(int i = 0; i < 52; i++){
        deck.push_back(i);
    }
}

void initHintFile(vector<string> &hintString){
    string fileLine;

    ifstream hintFile ("blackJack_play_suggestion.txt");

    if (hintFile.is_open()){

        while (getline (hintFile, fileLine)){
            hintString.push_back(fileLine);
        }

        hintFile.close();

    }
    else cout << "Unable to open Hint file";

}

int drawRandomCard(vector<int> &deck){
    //Draws a card from the vector and deletes it from the vector

    int size = deck.size();
    int index = (int) (rand () % size);
    int cardNumber = deck[index];

    deck.erase(deck.begin() + index);

    return cardNumber;
}

void determineCard(int number, Card& newCard){

    int val = 0;

    if( number >= 0 && number <= 12){
        //Spades

        newCard.flower = "Spades";

        if (number == 0){

            newCard.name = "A";
            newCard.value = 11;
        }
        else if (number == 10){

            newCard.name = "J";
            newCard.value = 10;

        }
        else if (number == 11){

            newCard.name = "Q";
            newCard.value = 10;
        }
        else if (number == 12){
            newCard.name = "K";
            newCard.value = 10;

        }
        else{

            val = number + 1;
            newCard.name = to_string(val);
            newCard.value = val;
        }


    }
    else if( number >= 13 && number <= 25){
        //Clubs

        newCard.flower = "Clubs";

        if (number == 13){

            newCard.name = "A";
            newCard.value = 11;

        }
        else if (number == 23){

            newCard.name = "J";
            newCard.value = 10;

        }
        else if (number == 24){

            newCard.name = "Q";
            newCard.value = 10;

        }
        else if (number == 25){

            newCard.name = "K";
            newCard.value = 10;

        }
        else{

            val =  number - 12;
            newCard.name = to_string(val);
            newCard.value = val;
        }



    }
    else if( number >= 26 && number <= 38){
        //Diamonds

        newCard.flower = "Diamonds";

        if (number == 26){

            newCard.name = "A";
            newCard.value = 11;
        }
        else if (number == 36){

            newCard.name = "J";
            newCard.value = 10;
        }
        else if (number == 37){

            newCard.name = "Q";
            newCard.value = 10;

        }
        else if (number == 38){
            newCard.name = "K";
            newCard.value = 10;

        }
        else{

            val =  number - 25;
            newCard.name = to_string(val);
            newCard.value = val;
        }



    }
    else if( number >= 39 && number <= 51){
        //Hearts

        newCard.flower = "Hearts";

        if (number == 39){

            newCard.name = "A";
            newCard.value = 11;

        }
        else if (number == 49){

            newCard.name = "J";
            newCard.value = 10;

        }
        else if (number == 50){

            newCard.name = "Q";
            newCard.value = 10;

        }
        else if (number == 51){

            newCard.name = "K";
            newCard.value = 10;

        }
        else{

            val =  number - 38;
            newCard.name = to_string(val);
            newCard.value = val;
        }





    }
    else{
        // Do Nothing
    }

}

void newHand(Player& human, Player& dealer, vector<int> &deck, Card& newCard, Card& dealerCard){


    //Dealer
    int cardNumber = drawRandomCard(deck);

    determineCard(cardNumber, newCard);

    dealer.totalValue += newCard.value;
    
    dealerCard = newCard;

    cout << "Dealer picked the " << newCard.name << " of " << newCard.flower << endl;

    //player
    cardNumber = drawRandomCard(deck);

    determineCard(cardNumber, newCard);

    human.totalValue += newCard.value;

    cout << "You picked the " << newCard.name << " of " << newCard.flower << endl;




}

void hitMe(Player& human, vector<int> &deck, Card& newCard){

    int cardNumber = drawRandomCard(deck);
    cout << cardNumber << endl;

    determineCard(cardNumber, newCard);

    human.totalValue += newCard.value;

    //The Ace == 11 or
    // Ace == 1 if on adding the hand becomes greater than 21
    if(newCard.name == "A"){
        if(human.totalValue > 21){
            human.totalValue -= 10;
        }

    }

    cout << "You picked the " << newCard.name << " of " << newCard.flower << endl;

}

void stand(Player& dealer, vector<int> &deck, Card& newCard){

    int cardNumber = drawRandomCard(deck);

    determineCard(cardNumber, newCard);

    dealer.totalValue += newCard.value;

    //The Ace == 11 or
    // Ace == 1 if on adding the hand becomes greater than 21

    if(newCard.name == "A"){
        if(dealer.totalValue > 21){

            dealer.totalValue -= 10;
        }

    }


    cout << "Dealer picked the " << newCard.name << " of " << newCard.flower << endl;

}

void hint(Player& dealer,Player& human, vector<string> &hintString, Card& dealerCard){

    int playerVal = 7;

    cout << "^^^^^^^^^^^^^^^^^DEALER CARD^^^^^^^^^^^^^^^^^^^^" <<endl;
    cout << "PLAYER VALUE \t2345678_10A" << endl;

    for(int i = 0; i < hintString.size(); i++){

        cout << "\t" << playerVal << "\t" << hintString[i] << endl;
        playerVal++;
    }
    
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
    
    cout << "Suggestion: ";
    hintSuggestion(dealer, human, dealerCard);
    
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;



}

void hintSuggestion(Player& dealer,Player& human, Card& dealerCard){ 
    
    int player = human.totalValue;
    string dealer_card = dealerCard.name;
    
    switch(player) {
        case 5 :
            cout << "Hit Me" << endl;
            break;
            
        case 6 :
            cout << "Hit Me" << endl;
            break;
            
        case 7 :
            cout << "Hit Me" << endl;
            break;
         
        case 8 :
            cout << "Hit Me" << endl;
            break;
            
        case 9 :
            cout << "Hit Me" << endl;
            break;
      
        case 10 :
            cout << "Hit Me" << endl;
            break;
         
        case 11 :
            cout << "Hit Me" << endl;
            break;
            
        case 12 : 
            {
                if(dealer_card == "2"){
                    
                    cout << "Hit Me" << endl;
                }
                else if(dealer_card == "3"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "4"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "5"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "6"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "7"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "8"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "9"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "10"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "A"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else{
                    // No hint
                }
            }
            break;
            
        case 13 :
            {
                if(dealer_card == "2"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "3"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "4"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "5"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "6"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "7"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "8"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "9"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "10"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "A"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else{
                    // No hint
                }
            }
            break;
            
        case 14:
            {
                if(dealer_card == "2"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "3"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "4"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "5"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "6"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "7"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "8"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "9"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "10"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "A"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else{
                    // No hint
                }
            }
            break;
        
        case 15 :
            {
                if(dealer_card == "2"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "3"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "4"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "5"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "6"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "7"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "8"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "9"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "10"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "A"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else{
                    // No hint
                }
            }
            break;
         
        case 16 :
            {
                if(dealer_card == "2"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "3"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "4"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "5"){
                    
                    cout << "Stand" << endl;
                }
                else if(dealer_card == "6"){
                    
                    cout << "Stand" << endl;
                    
                }
                else if(dealer_card == "7"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "8"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "9"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "10"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else if(dealer_card == "A"){
                    
                    cout << "Hit Me" << endl;
                    
                }
                else{
                    // No hint
                }
            }
            break;
        
        case 17 :
            cout << "Stand" << endl;
            break;
            
        default :
            //No hint
            cout << "No hint" << endl;
}
}

void printGameValues(Player& dealer, Player& human){


    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;

    cout << "Dealer Value: " << dealer.totalValue << endl;
    cout << "Player Value: "<< human.totalValue << endl;


    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;


}







