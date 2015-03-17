//Input: TransactionFile.txt, UsersFile.txt, EventsFile.txt
//Output: TransactionFile.txt(Empty), UsersFile.txt(Updated), EventsFile.txt(Updated)
//Purpose: This program will take the log from the transaction file and then update
//		   the Users and Events file with any change from the transaction. The 
//		   transaction file will be blanked afterward for next day.

import java.lang.NullPointerException;
import java.io.FileNotFoundException;
import java.io.IOException;
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
		BufferedReader Users = readFromFile(UsersFile);
		BufferedReader Events = readFromFile(EventsFile);
		BufferedReader Transaction = readFromFile(TransactionFile);
		HashMap<String, User> userData = new HashMap<String, User>();
		HashMap<String, Event> eventData = new HashMap<String, Event>();
		String line, name;
		User u;
		Event e;
		int amount;
		int transType;
		float value;
		
		try{
			//Gets all the user data from the file and put it in the hash map one line at a time
			line = Users.readLine();
			while(line != null){
				name = line.substring(0, 15).trim();
				value = Float.parseFloat(line.substring(19,28));
				u = new User(name, line.substring(16, 18), value);
				
				userData.put(name, u);
				line = Users.readLine();
			}
			
			//Gets all the event data from the file and put it in a hash map
			line = Events.readLine();
			while(line != null){
				name = line.substring(0, 19).trim();
				amount = Integer.parseInt(line.substring(34, 37));
				value = Float.parseFloat(line.substring(38,44));
				e = new Event(name, line.substring(20, 33).trim(), amount, value);
				
				eventData.put(name, e);
				line = Events.readLine();
			}
			
			//Gets each transaction one at a time and apply the change to the user or event database
			line = Transaction.readLine();
			while(line != null){
				transType = Integer.parseInt(line.substring(0, 3));
				
				if(transType == 1){ //Creating an account
					name = line.substring(3, 18).trim();
					
					if(userData.get(name) != null){
						System.out.println("ERROR: The user " + name + " already exist in the database.");
					} else {
						value = Float.parseFloat(line.substring(22, 31));
						u = new User(name, line.substring(19,21), value);						
						userData.put(name, u);
					}
				} else if(transType == 2){	//Deleting an account
					name = line.substring(3, 18).trim();
					u = userData.remove(name);
					
					if(u == null){
						System.out.println("ERROR: The user " + name + " cannot be removed because it no longer exist.");
					}
				} else if(transType == 3){	//Selling tickets for new event
				
				} else if(transType == 4){	//Buying from an event
				
				} else if(transType == 5){	//Refund from seller to buyer
					value = Float.parseFloat(line.substring(35, 44));
					
					name = line.substring(3, 18).trim();
					u = userData.remove(name);
					
					if(u == null){
						System.out.println("ERROR: The user " + name + " cannot be refunded because it no longer exist.");
						//No point in subtracting the fund from seller if the buyer no longer exist
					} else {
						u.setCredit(u.getCredit() + value);
						userData.put(name, u);
						
						name = line.substring(19, 34).trim();
						u = userData.remove(name);
						
						if(u == null){
							System.out.println("ERROR: The user " + name + " cannot be initiate the refund because it no longer exist.");
							
							//If the seller is gone, we can't just give buyer free money
							name = line.substring(3, 18).trim();
							u = userData.remove(name);
							u.setCredit(u.getCredit() - value);
							userData.put(name, u);
						} else {
							u.setCredit(u.getCredit() - value);
							userData.put(name, u);
						}
					}
				} else if(transType == 6){	//Add credit to an account
					name = line.substring(3, 18).trim();
					value = Float.parseFloat(line.substring(22, 31));
					u = userData.remove(name);
					
					if(u == null){
						System.out.println("ERROR: Credit cannot be added to the user " + name + " because it no longer exist.");
					} else {
						u.setCredit(u.getCredit() + value);
						userData.put(name, u);
					}
				}
				
				line = Transaction.readLine();
			}
		} catch (IOException ex){
			System.out.println("ERROR: IO Exception???? Should never occur!");
			System.exit(1);
		} catch (NullPointerException exp){
			System.out.println("ERROR: Null pointer?????Should never occur!");
			System.exit(1);
		}
	}
	
	//Read a file name and provided a buffered reader for the file
	//Also handle error relating to file not being found
	public static BufferedReader readFromFile(String name){
		try{
			BufferedReader br = new BufferedReader(new FileReader(name));
			return br;
		} catch (FileNotFoundException e){
			System.out.println("ERROR: File " + name + " not found!");
			return null;
		}
	}
	
	//Write all the data inside the user and event map to the given file
	public static int writeToFile(String name, HashMap<String, User> u, HashMap<String, Event> e){
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