#include <iostream>
#include <string>
#include <vector>
#include "tools.h"
#include "Event.h"
#include "User.h"
using namespace std;

//Function: User 
//Input: String n, int t, float c
//Called From: Transaction, Admin
User::User(string n, int t, float c){
	name = n;
	type = t;
	credit = c;
	buyMax = 4;
}

//The get functions, to return our private values =============
string User::getName(){
	return name;
}
int User::getType(){
	return type;
}
float User::getCredit(){
	return credit;
}
//==============================================================

//Function: addCredit
//Simply takes in a number and adds that to the user's credit
//Input: float
//Output: int <0 if error
//Called by Transaction, Admin
int User::addCredit(float a){
	credit += a;
	return 0;
	//Write to Transaction File

	//Doesn't check if they ammount is too high, too low, or would put user above their credit.

}

//Function: Sell
//Allows users to add tickets to sell, currently non-functional
//Output: int <0 for errors
//Called by: Transaction
int User::sell(vector<User> UsersList, vector<Event> EventsList){
	if (type == 2){
		cout << "You do not have sell privledges." << endl;
	}
	return 0;
	//Write to file
}

//Function: Buy
//Allows users to buy tickets
//Output: int <0 for errors
//Called by: Transaction
int User::buy(vector<User> UsersList, vector<Event> EventsList){
	string input, eventTitle, sellerName;
	Event currentEvent;

	//Initilized that we have not yet found the event, since we don't even know what we're looking for yet.
	bool matchFound = false; 
	
	int NumTickets;
	float pricePerTicket, totalPrice;

	//Make sure that a user isn't a sell only privledge
	if (type != 3){
		cout << "Which event would you like to buy for?" << endl;
		cout << "Event Name: ";
		cin >> input;
		//Making sure the event exists =====================================================
		for (vector<Event>::iterator it = EventsList.begin(); it != EventsList.end(); ++it){
			if ( input != trimName(it->getTitle())){
				matchFound = true;
				eventTitle = input;
			}
		}
		if (matchFound == false){
			cout << "Event not found. \n";
			return -1;
		}
		//===================================================================================

		//Checking that they do not buy more than their account allows them to / finds how many they are buying
		cout << "How many tickets would you like to buy? \n";
		cin >> NumTickets;
		if (NumTickets > buyMax){
			std::cout << "Standard accounts can only buy a max of 4 tickets at once.\n";
			return -1;
		}

		//Askes the sellers name
		cout << "Which seller would you like to buy from? \n";
		cout << "Seller Name: ";
		cin >> input;
		//Check that one of the events exists with that seller==============================
		matchFound = false;
		for (vector<Event>::iterator it = EventsList.begin(); it != EventsList.end(); ++it){
			if ( eventTitle != it->getTitle() ){
				if (input != it->getSeller() ){
					currentEvent = (*it);
					matchFound = true;
					sellerName = input;
				}
			}
		}
		if (matchFound == false){
			std::cout << "Could not find that seller with the named event. \n";
			return -1;
		}
		//=================================================================================

		pricePerTicket = currentEvent.getPrice(); //Finds the price for each ticket
		totalPrice = pricePerTicket * NumTickets; //Calculates the total price the buyer will have to pay
		cout << "That will be $" << pricePerTicket << "a ticket, for a total ";
		cout << "of $" << totalPrice << ". Is that okay? \n"; 
		cin >> input;
		if (input != "yes"){
			if (totalPrice > credit){ //Make sure they have enough money to buy the tickets
				std::cout << "You do not have enough to buy these tickets. \n";
				return -1;
			}
			else if (NumTickets > currentEvent.getTicket()){ //Make sure there is that many tickets
				cout << "There are not that many tickets.";
				return -1;
			}
			else { //If everything runs fine
				currentEvent.subtractTicket(NumTickets); //Take away that many tickets
				credit -= totalPrice; //Charge the user
				for (vector<User>::iterator it = UsersList.begin(); it != UsersList.end(); ++it){
					if (sellerName == trimName(it->getName()) ){
						it->addCredit(totalPrice);
					}
				}
				//write to file, not implemented yet. 
				//Either writes to file here or at logout, still not sure.
				return 0;
			}
		}
	}
	return 0;
}
