/* Benjamin Reichert 
CS162 @ Portland State University
3/2/13 
Assignment #4 
Part of the Command Line Awesome Posting System, or CLAPS 
*/

#include "class.h"

//************ PROTOTYPES ****************//
void welcome();
bool menu(list alist);


//calls the main manager function, menu and welcome to greet the user
//also the place where the list is initialized
int main()
{
	welcome(); //welcome the user
	list my_list; //initialize a list
		
	while(menu(my_list)); //as long as user wants to keep doing things
		
	return 0;

}
//welcome the user with a big cout statement and information
void welcome()
{
	cout << "\n\n\n\n\n\nWelcome to the Command Line Awesome Posting System, or CLAPS"
		 << "\nIt works similar to eBay or Craigslist, but in a much simpler fashion.\n"
		 << "Follow the menu prompt to enter a posting, and view postings. \n" <<endl;

}
//main manager that calls functions for the program. Takes in the list as an argument and manages it from there/
bool menu(list alist)
{
	char userinput; //make temp variable for user single char input
	char tempname[100]; //holds temporary array data user enters

	cout << "\n\nThis is the Menu Selection System.\n" 
		 << "Please enter one of the following choices: \n"
		 << "A - Add posting\n"
		 << "D - Display all postings\n"
		 << "J - Display only postings of type job\n"
		 << "H - Display only postings of type housing\n"
		 << "F - Display only postings of type for sale\n"
		 << "X - Exit the program\n"
		 << "Enter here: "; //tell the options they have
	cin >> userinput; //get their selection
	cin.ignore(100, '\n');
	userinput = toupper(userinput); //capitalize character for matching
	
	if (userinput == 'A') //if a, add posting
	{
		cout << "What would you like the title of the posting to be? " <<endl;
		cin.get(tempname, 100, '\n');
		cin.ignore(100, '\n');
		alist.add(tempname);
		return true;
	}
	else if(userinput == 'D') //if d, search for all postings
	{
		alist.display_all();
		return true;
	}
	else if(userinput == 'J') // if j, display job postings
	{
		alist.display_type('J');
		return true;
	}
	else if(userinput == 'H') //if h display housing postings
	{
		alist.display_type('H');
		return true;
	}
	else if(userinput == 'F') //if f display for sale stuffs
	{
		alist.display_type('F');
		return true;
	}

	else if (userinput == 'X') //if want to quit, return false and while looop in main will die and program will exit
		return false;
}

