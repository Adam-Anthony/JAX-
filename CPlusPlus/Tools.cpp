#include <iostream>
#include <iomanip>
#include <fstream>
#include <strstream>
#include <string>
#include <vector>
#include "Event.h"
#include "User.h"
#include "Admin.h"
#include "Tools.h"
using namespace std;


//trimName
//Takes in a string that has extra white space at the end and removes it all so that we can better compare.
string trimName(string addedSpace){
	string formattedString;
	formattedString = addedSpace.substr(0, addedSpace.find_last_not_of(' ') + 1);
	return formattedString;
}

//Possibly writing to the transaction file will go here too?
//Possibly make finding if a user exists or not into a tool?

//Function:
//Description
//Input:
//Output:
//Called By: 
//Calls:

//Things and such.

//Initilizing the User database
vector<User> UpdateUsers(){
	vector<User> UsersList;
	string fileData;
	ifstream AccountsFile("UsersFile.txt");
	while (getline(AccountsFile, fileData)){
		if (trimName(fileData.substr(0, 14)) == "END"){
			break;
		}
		if (stoi(fileData.substr(15, 2)) == 1){
			UsersList.push_back(Admin(fileData.substr(0, 14), stof(fileData.substr(18, 11))));
		}
		else{
			UsersList.push_back(User(fileData.substr(0, 14), stoi(fileData.substr(15, 2)), stof(fileData.substr(18, 11))));
		}
		//0-12 is username
		//14-15 is the type
		//17-27 is the credit
		//Check if END to break;

		//The document mentions appending .00 to credit values if there is none, that is not implemented.
	}
	AccountsFile.close();
	return UsersList;
}
//Initilizing the Tickets Database

vector<Event> UpdateEvents(){
	vector<Event> EventsList;
	string fileData;
	ifstream EventsFile("EventsFile.txt");
	while (getline(EventsFile, fileData)){
		if (trimName(fileData.substr(0, 19)) == "END"){
			break;
		}
		EventsList.push_back(Event(fileData.substr(0, 19), fileData.substr(20, 12), stoi(fileData.substr(34, 3)), stof(fileData.substr(38, 6))
			));
		//0-19	Events Name
		//21-33	Sellers Name
		//35-37	Amount of tickets available
		//39-44	Price
	}

	EventsFile.close();
	return EventsList;
}

void WriteUsers(vector<User> u){
	ofstream userFile;
	userFile.open("UsersFile.txt");
	for (vector<User>::iterator it = u.begin(); it != u.end(); ++it){
		string type = to_string(it->getType());
		string cred = to_string(it->getCredit());
		type.insert(0, 1, '0');
		cred = cred.substr(0, cred.size() - 4);
		cred.insert(0, 11 - cred.size(), '0');
		userFile << it->getName() << " " << type << " " << cred << "\n";
	}
	userFile << "END                            ";
	userFile.close();
}

void WriteEvent(vector<Event> e){
	ofstream eventFile;
	eventFile.open("EventsFile.txt");
	for (vector<Event>::iterator it = e.begin(); it != e.end(); ++it){
		string amountOf = to_string(it->getTicket());
		amountOf.insert(0, 3 - amountOf.size(), '0');
		string price = to_string(it->getPrice());
		price = price.substr(0, price.size() - 4);
		price.insert(0, 6 - price.size(), '0');

		eventFile << it->getTitle() << " " << it->getSeller() << " " << amountOf << " " << price << "\n";
	}
	eventFile << "END                                             ";
	eventFile.close();
}

static string trans = "";

void addToTrans(string s){
	trans += s;
	trans += "\n";
}

string getTrans(){
	return trans;
}