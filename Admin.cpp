#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Event.h"
#include "Admin.h"
#include "Tools.h"
using namespace std;

//Function: Admin
//Input: String n, float c
//Called By: Main
Admin::Admin(string n, float c){
	name = n;
	credit = c;
	buyMax = 9999999;
	type = 01;
}

//Function: Admin
//Input: User u
//Called By: Transaction
Admin::Admin(User u){
	name = u.getName();
	credit = u.getCredit();
	buyMax = 9999999;
	type = 1;
}

//Function: create
//Creates a new user.
//Output: int < 0 for error
//Called By: Transaction
int Admin::create(vector<User> UsersList){
	string user, type;
	int typeVal;
	//String typeToFile; //Only used when we actually are going to write to file
	cout << "What is the new username?\n";
	cout << "Name: ";
	cin >> user;

	cout << "What type of account does this user have?\n";
	cout << "Type(admin,buy,sell,full): ";
	cin >> type;
	if (type == "admin"){
		typeVal = 1;
		//typeToFile = "AA";
	}
	else if (type == "buy"){
		typeVal = 2;
		//typeToFile = "BS";
	}
	else if (type == "sell"){
		typeVal = 3;
		//typeToFile = "SS";
	}
	else if (type == "full"){
		typeVal = 4;
		//typeToFile = "FS";
	}

	UsersList.push_back(User(user, typeVal, 000000000));

	//Write to TransactionFile
	return 0;
	
	//Are we supposed to add the user to the User Array?
	//Doesn't check if user already exists.
	//Can't handle different answers for types (strings or ints)
	//Doesn't pad the name
}

//Function: del
//Deletes a user from the list
//Output: x<0 if an error occurs
//Called By: Transaction
//Calls: Tools
int Admin::del(vector<User> UsersList, vector<Event> EventsList){
	string user; //The variable space where we will store the name of the targeted user
	bool matchFound = false; //We don't know if the target exists yet.
	User deleteTarget;

	cout << "Which user are you going to delete?\n";
	cout << "User: ";
	cin >> user;
	//Can't delete self
	if (user == name){
		cout << "You cannot delete yourself.\n";
		return -1;
	}

	//Finding the user.
	for (vector<User>::iterator it = UsersList.begin(); it != UsersList.end(); ++it){
		if (name == trimName(it->getName())){
			matchFound = true;
			deleteTarget = (*it);
		}
	}
	if (matchFound == false){ //Bailing if the user does not exist.
		cout << "User does not exist";
		return -1;
	}

	//Delete all instances of the users tickets from Events.
	//Delete user from local storage

	//TransactionFile << '02 ' << user << ' ' << deleteTarget.getType() << ' ' << deleteTarget.getCredit();
	//Write to file

	//Doesn't delete from local storage, delete their tickets from the events, or write to file
	return 0;
}

//Function: Refund
//Takes credit from a seller and gives it to a user
//Output: int < 0 if there is an error
//Called By: Transactions
//Calls: User
int Admin::refund(vector<User> UsersList){
	User BuyUser;  //User recieving credit
	User SellUser; //User losing credit
	string input; 
	float amount; 

	bool matchFound = false;

	cout << "Which user will be recieving the refund?\n";
	cout << "User:";
	cin >> input;
	//Find the user that is getting the refund
	for (vector<User>::iterator it = UsersList.begin(); it != UsersList.end(); ++it){
		if (input == trimName(it->getName())){
			BuyUser = (*it);
			matchFound = true;
		}
	}
	if (matchFound == false){ //Bails if user doesn't exist
		cout << "That user doesn't exist\n";
		return -1;
	}
	if (BuyUser.getType() == 3){ //Bails if that user couldn't buy in the first place
		cout << "That user doesn't have buy privledges. \n";
		return -1;
}

	cout << "Which user will be refunding the money?\n";
	cout << "User:";
	cin >> input;
	//Find the user that is giving the refund
	for (vector<User>::iterator it = UsersList.begin(); it != UsersList.end(); ++it){
		if (input == trimName(it->getName())){
			SellUser = (*it);
			matchFound = true;
		}
	}
	if (matchFound == false){ //Bails if user doesn't exist
		cout << "That user doesn't exist\n";
		return -1;
	}
	if (SellUser.getType() == 2){ //Bails if user doesn't have privilege to sell in the first place
		cout << "That user doesn't have sell privledges. \n";
		return -1;
	}
	cout << "How much money is being refunded? \n"; 
	cout << "Amount: ";
	cin >> amount;

	if (amount > SellUser.getCredit()){ //Prevents someone from refunding more money then they have
		cout << "The seller does not have enough money.";
		return - 1;
	}

	BuyUser.addCredit(amount); //Adds money to user
	SellUser.addCredit(-1*amount); //Subtracts money from other user
	//Write to file
	return 0;
}

//Function: addCredit
//The admin version of add credit, allows an admin to add credit to any user account
//Output: returns int < 0 if there is an error
//Called By: Transaction
//Calls: User, Tools
int Admin::addCredit(vector<User> UsersList){
	string input;
	float amount;
	User userTarget;

	bool matchFound = false;

	cout << "Please enter the name of the User to add credit to. \n";
	cout << "User: ";
		cin >> input;
	//Checking to find the user
	for (vector<User>::iterator it = UsersList.begin(); it != UsersList.end(); ++it){
		if (input == it->getName()){
			userTarget = (*it);
			matchFound = true;
		}
	}
	if (matchFound == false){ //Bails if user doesn't exist
		cout << "That user doesn't exist\n";
		return -1;
	}

	//Askes for ammount
	cout << "Please enter the amount. \n";
	cout << "$:";
	cin >> amount;

	//If (user)AddCredit checks for inconsistencies, we delete this code=========================
	if (amount > 1000.00){ //Prevents adding more then the maximum add
		cout << "Cannot add more than $1000.00/n";
			return -1;
	}
	else if ((userTarget.getCredit() + amount) > 999999.00){
		cout << "This would exced credit limit of $999,999.00 on this account";
		return -1;
	}

	//==========================================================================================
	else{
		//Runs the (user)addCredit
		userTarget.addCredit(amount);
		
		//Write to transaction file
		return 0;
	}
}