/* Benjamin Reichert 
CS162 @ Portland State University
3/18/13 
Assignment #5
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
		void display_posting(char type); //display a single posting
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


struct node
{
	posting post; //create a post of type posting to hold all of the data
	node * next; //pointer to hold the memory address of the next node

};


class list
{
    public:
        list(); //default constructor that initializes data 
        ~list(); //default destructor that deallocates all dynamic memory
        void add(); //adds and entry to the LLL with input from the user for the posting
        void display_all(); //displays all of the postings of the LLL
    private:
        node * head; //pointer to the first entry of the LLL
};

