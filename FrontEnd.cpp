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

//Function: Transaction
//Main loop where user is asked to do transactions
//Called By: Main
//Calls To: User, Admin
void transaction(vector<User> UsersList, vector<Event> EventsList){
	bool loggedIn = false;
	User CurrentUser;
	bool isAdmin = false;
	Admin CurrentAdmin; //Incase the user is an admin and they have admin privledges
	string UserName;

	bool loopCondition = true;	//a condition initilized to true for the while loop to indefinitely repeat

	string input;	//Input from users will be stored in this variable
	float amount;	//Float amounts in inputs will be stored here

	//File io for the transaction file, writting to transaction file not yet implemented.
	ofstream TransactionFile("TransactionFile.txt");

	//The loop where the user is asked about performing a transaction
	while (loopCondition){
		cout << "Which kind of transaction would you like to perform?\n";
		cout << "Transaction: ";
		cin >> input;
		
		//QUIT
		if (input == "quit"){
			loopCondition = false;
		}
		else if (loggedIn == false && (input != ("login"))){
			cout << "You must login first. \n";
		}
		else{
			//Login
			if (input == "login"){
				cout << "Enter your user name: \n Name:";
				cin >> input;
				for (vector<User>::iterator it = UsersList.begin(); it != UsersList.end(); ++it){ //Searches through Users list
					UserName = trimName(it->getName()); //Sends the string of the name to get endspaces trimmed off to better compare.
					if (input == UserName){
						CurrentUser = (*it); //Setting current user
						loggedIn = true;	//Confirming that user can now use other transactions
						cout << "You are now logged in." << endl;
						if (CurrentUser.getType() == 01){	//Checks if user is an Admin
							isAdmin = true;
							CurrentAdmin = Admin(*it);
						}
					}
				}
			}
			//Logout
			else if (input == "logout"){
				loggedIn = false;	//Makes the user have to log back in to access other transactions
				isAdmin = false;	//Prevents accidental admin
				
				//Writes to file. Really broken.
				//Doesn't put enough spacing for some credit, Doesn't store proper types for users privliges. Doesn't append.
				TransactionFile << "00 " << CurrentUser.getName() << " " << CurrentUser.getType() << ' ' << CurrentUser.getCredit() << endl;
				TransactionFile.close(); 
				cout << "You have successfully logged out. \n";
			}
			//Create
			else if (input == "create" && isAdmin){
				CurrentAdmin.create(UsersList); //Admin only, Calls Admin.create
			}
			//Delete
			else if (input == "delete" && isAdmin){
				CurrentAdmin.del(UsersList, EventsList);	//Admin only, Calls Admin.del
			}
			//Sell
			else if (input == "sell"){
				CurrentUser.sell(UsersList, EventsList);	//Calls User.sell
			}
			//Buy
			else if (input == "buy"){
				CurrentUser.buy(UsersList, EventsList);		//Calls User.Buy
			}
			//Refund
			else if (input == "refund" && isAdmin){			//Admin only, calls Admin.refund
				CurrentAdmin.refund(UsersList);
			}
			//Add Credit
			else if (input == "addCredit" || input == "add"){	//Works for two cases.
				if (isAdmin){									//Checks if user is admin to run the admin version or not
					CurrentAdmin.addCredit(UsersList);			//Admin only, calls Admin.addCredit
				}
				else{
					cout << "Enter how much you wish to add.\n $:";
					cin >> amount;
					CurrentUser.addCredit(amount);	//Calls the basic user one, User.addCredit
					//Then alerts user to how much money they have.
					//Doesn't currently check if they hit maximum, Doesn't check if they try to add more then allowed
					//Doesn't currently check if they enter negative
					cout << "You now have $" << fixed << setprecision(2) << CurrentUser.getCredit() << endl; 
				}
			}
			else{
				cout << "Please enter a valid transaction.\n";
			}
		}
	}
}

//Function: Main
//Main function to initilize the user base and event base, and then call the transactions
//Called by: User
//Calls: Transaction

int main()
{
	//Iniitilizing important vectors used for our userbase and tickets base
	vector<User> UsersList;	
	vector<Event> EventsList;

	string fileData;

	//Initilizing the User database
	ifstream AccountsFile ("UsersFile.txt");
	while (getline (AccountsFile, fileData)){
		UsersList.push_back(User(fileData.substr(0,13), stoi(fileData.substr(14,2)), stof (fileData.substr(17,9))
		));
		//0-12 is username
		//14-15 is the type
		//17-27 is the credit
		//Check if END and nothing else then break;

		//The document mentions appending .00 to credit values if there is none, that is not implemented.
		//Should nornally end at htting the END signifiying value in the file, but doesn't do that yet.
	}
	AccountsFile.close();

	//Initilizing the Tickets Database
	ifstream EventsFile ("EventsFile.txt");
	while (getline (AccountsFile, fileData)){
		EventsList.push_back(Event(fileData.substr(0,20),fileData.substr(21,13),stoi(fileData.substr(35,3)),stof(fileData.substr(39,6))
		));
		//0-19	Events Name
		//21-33	Sellers Name
		//35-37	Amount of tickets available
		//39-44	Price

		//Supposed to end on hitting the END event, but doesn't yet.
	}

	EventsFile.close();
	transaction(UsersList, EventsList);

	return 0;
}


// Data for when implemnting writing to the transaction file: 

//XX_UUUUUUUUUUUUU_TT_CCCCCCCCC
//Create, Delete, addCredit, End of Session
//01,02,06,00
//TransactionFile << '0' << type << ' ' << name << " " << usertype << ' ' << credit;  



//XX_UUUUUUUUUUUUU_UUUUUUUUUUUUU_CCCCCCCCC
//Refund
//05
//TransactionFile << '0' << type << ' ' << name << " " << name << ' ' << credit;  


//XX_EEEEEEEEEEEEEEEEEEEE_SSSSSSSSSSSSS_TTT_PPPPPP
//Buy, Sell
//03,04

//TransactionFile << '0' << type << ' ' << event << ' ' << name << " " << tickets << ' ' << price;  
