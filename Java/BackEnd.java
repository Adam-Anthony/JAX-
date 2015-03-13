//Input: TransactionFile.txt, UsersFile.txt, EventsFile.txt
//Output: TransactionFile.txt(Empty), UsersFile.txt(Updated), EventsFile.txt(Updated)
//Purpose: This program will take the log from the transaction file and then update
//		   the Users and Events file with any change from the transaction. The 
//		   transaction file will be blanked afterward for next day.

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileNotFoundException;

public class BackEnd{
	static final String UsersFile = "UsersFile.txt";
	static final String EventsFile = "EventsFile.txt";
	static final String TransactionFile = "TransactionFile.txt";

	public static void main(String[] Argv){
		BufferedReader Users = readFile(UsersFile);
		BufferedReader Events = readFile(EventsFile);
		BufferedReader Transaction = readFile(TransactionFile);
	}
	
	public static BufferedReader readFile(String fileName){
		try{
			BufferedReader br = new BufferedReader(new FileReader(fileName));
			return br;
		} catch (FileNotFoundException e){
			System.out.println("ERROR: File " + fileName + " not found!");
			return null;
		}
	}
}