#ifndef EVENT_H
#define EVENT_H

#include <string>
using namespace std;

class Event
{
private:
	string seller;
	string name;
	int tickets;
	float price;

public:
	Event() { }
	Event(string n, float p, int t);
	Event(string n, string s, float p, int t);

	void setSeller(string s);
	string getTitle();
	float getPrice();
	int getTicket();
	string getSeller();
	void subtractTicket(int s);
};

#endif