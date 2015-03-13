//Input: TransactionFile.txt, UsersFile.txt, EventsFile.txt
//Output: TransactionFile.txt(Empty), UsersFile.txt(Updated), EventsFile.txt(Updated)
//Purpose: This program will take the log from the transaction file and then update
//		   the Users and Events file with any change from the transaction. The 
//		   transaction file will be blanked afterward for next day.

import java.io.FileNotFoundException;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.HashMap;

public class BackEnd{
	static final String UsersFile = "UsersFile.txt";
	static final String EventsFile = "EventsFile.txt";
	static final String TransactionFile = "TransactionFile.txt";

	public static void main(String[] Argv){
		BufferedReader Users = readFile(UsersFile);
		BufferedReader Events = readFile(EventsFile);
		BufferedReader Transaction = readFile(TransactionFile);
	}
	
	//Read a file name and provided a buffered reader for the file
	//Also handle error relating to file not being found
	public static BufferedReader readFile(String fileName){
		try{
			BufferedReader br = new BufferedReader(new FileReader(fileName));
			return br;
		} catch (FileNotFoundException e){
			System.out.println("ERROR: File " + fileName + " not found!");
			return null;
		}
	}
	
	//Write all the data inside the user and event map to the given file
	public static int writeFile(String fileName, HashMap<String, User> userData, HashMap<String, Event> eventData){
		return 1;
	}
}

//This class is responsible for holding the data for each user
//The data it contains are:
//User's name, User's type and User's Credit
class User{
	String name;
	String type;
	float credit;
	
	public User(String n, String t, float c){
		name = n;
		type = t;
		credit = c;
	}
	
	//Various access function for the class
	public String getName(){
		return name;
	}
	
	public String getType(){
		return type;
	}
	
	public float getCredit(){
		return credit;
	}
	
	//Mutation method for credit only, other data do not ever needs to be changed
	public void setCredit(float c){
		credit = c;
	}
}

//This class is responsible for holding the data for each event
//The data it contains are:
//Event Name, Seller's Name, Available Tickets and Ticket Price
class Event{
	String title;
	String seller;
	float price;
	int amount;
	
	public Event(String t, String s, int a, float p){
		title = t;
		seller = s;
		amount = a;
		price = p;
	}
	
	//Various access function for the class
	public String getTitle(){
		return title;
	}
	
	public String getSeller(){
		return seller;
	}
	
	public int getAmount(){
		return amount;
	}
	
	public float getPrice(){
		return price;
	}
	
	//Mutation method for price and tickets amount only
	//The other data do not ever needs to be changed
	void setAmount(int a){
		amount = a;
	}
	
	void setPrice(float p){
		price = p;
	}
}