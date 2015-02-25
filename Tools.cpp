#include <string>
#include "tools.h"
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