/* Benjamin Reichert 
CS162 @ Portland State University
3/2/13 
Assignment #4 
Part of the Command Line Awesome Posting System, or CLAPS 
*/

#include <iostream> 
#include <cstring> 
using namespace std;

class posting
{
	public:
		posting(); //default constructor
		~posting(); //default deconstructor
		void create_posting(char input_title[]); // create a new posting of this title. The rest of the information should be read from the user
		void display_posting(); //display a single posting
		bool is_type(char asking_type); //is the posting a job, housing, item for sales or free stuff (you can modify the argument list)
	private:
		//put details here
		char * title; //hold title
		char * description; //holds desc
		char * location; //holds location
		char * email; //holds email
		char * compensation; //holds compensation
		char type; //holds type of listing
		int  rent; //holds rent
		int  bedrooms; //holds bedrooms
		int  squarefeet; //holds sq feet
		int  cost; //holds cost
};

class list
{
	public:
		list(); //default constructor
		~list(); //default deconstructor
		void add(char title[]); //adds a posting to the list
		void display_all(); //display all the postings
		void display_type(char type); //only display those postings that match a type
	private:
		//put the information about an array of postings
		//and an integer count of the number of postings available
		int numpostings; //holds number of entered postings
		posting postings[10]; //create an array of postings
	
};

