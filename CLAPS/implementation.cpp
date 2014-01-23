/* Benjamin Reichert 
CS162 @ Portland State University
3/2/13 
Assignment #4 
Part of the Command Line Awesome Posting System, or CLAPS 
*/

#include "class.h"

//default constructor implementation for posting class
posting::posting() 
{
	title = '\0'; //holds title, set to hold nothing but \0
	description = '\0'; //holds desc, set to hold \0
 	location = '\0'; //holds location, set to hold \0
	email = '\0'; //holds email address, set to hold \0
 	compensation = '\0'; //holds work compensation, set to \0
 	type = '\0'; //type of posting, job, housing, for sale
 	rent = 0; //set initial rent to 0
 	bedrooms = 0; //set initial bedrooms to 0
 	squarefeet = 0; //set initial sq ft to 0
 	cost = 0; //set initial cost to 0
}
//default deconstructor for posting class
posting::~posting()
{
	delete [] title; //kills all of the memory the array pointers point to
	delete [] description;
	delete [] location;
	delete [] email;
	delete [] compensation;
}

//this function creates a post and has some logic to determine what fields to 
//fill out depending on what kind of post it is, take in an array as the title
//for the new posting
void posting::create_posting(char input_title[])
{
	bool goon = false; //set go on to false initially
	
	char temp[200]; //set up a place to store temporary words
	title = new char[strlen(input_title) + 1]; // make room for title and \0
	strcpy(title, input_title); //copy input title into title
	cout << "Creating a posting with the title: " << title << "." <<endl;

	do{ //reads in description from user
	cout << "Please enter a description: " <<endl;
	cin.get(temp, 200, '\n');
	cin.ignore(200, '\n');
	description = new char[strlen(temp) + 1];
	strcpy(description, temp);
	}while(description == '\0');

	do{ //reads in location from user
	cout << "Please enter a location: " <<endl;
	cin.get(temp, 200, '\n');
	cin.ignore(200, '\n');
	location = new char[strlen(temp) + 1];
	strcpy(location, temp);
	}while(location == '\0');
 
	do{ //reads in email address from user
	cout << "Please enter an email address to contact you at: " <<endl;
	cin.get(temp, 200, '\n');
	cin.ignore(200, '\n');
	email = new char[strlen(temp) + 1];
	strcpy(email, temp);
	}while(email == '\0');

	do { //asks user what kind of post this is
	cout << "What type of posting is this? Please enter: " <<endl
		 << "F -- for sale \n J -- job \n H -- housing\n" <<endl;
	cin >> type;
	cin.ignore(100, '\n');
	type = toupper(type);
	cout << "type is: " <<type <<endl;
	if(type == 'F' || type == 'J' || type == 'H') //if it is a valid entry
	{	
		goon = true; //set go on to be true
	}
	}while(goon != true); //while user inputs bad info, keep looping

	if (type == 'F') //if it is a for sale posting, fill in the appropriate fields
	{		
		do{
		cout << "Please enter the amount you would like to sell the item for: " <<endl;
		cin >> cost;
		cin.ignore(100, '\n');
		}while(cost < 0);	
	}
	else if(type == 'J') //if it is a job entry, get job info
	{
		cout << "Please enter compensation benefits for the job: " <<endl;
		cin.get(temp, 200, '\n');
		cin.ignore(200, '\n');
		compensation = new char[strlen(temp) + 1];
		strcpy(compensation, temp);
	}
	else if(type == 'H') //if it is housing, get sq ft, bedrooms, rent
	{
		cout << "Please enter the rent: " <<endl; //get rent, and check to make sure it is above 9
		do{
		cin >> rent;
		cin.ignore(100, '\n');
		}while(rent < 0);

		do{
		cout << "Please enter the number of bedrooms: " <<endl; //get bedrooms and make sure is valid
		cin >> bedrooms;
		cin.ignore(100, '\n');
		}while(bedrooms < 0);

		do{
		cout << "Please enter the square feet: " <<endl; //get sq ft and make sure is valid
		cin >> squarefeet;
		cin.ignore(100, '\n');
		}while(squarefeet < 0);
	}
}

//outputs the contents of the class data for a posting
void posting::display_posting()
{
	cout << "POSTING: " << title << endl;
	cout << "DESCRIPTION: " << description <<endl;
	cout << "LOCATION: " << location <<endl;
	cout << "EMAIL: " << email <<endl;
	if (type == 'F') //if it is a specific post, output it's specific information
		cout << "PRICE: " << cost <<endl; 
	else if(type == 'J')
		cout << "COMPENSATION: " <<compensation <<endl;
	else if(type == 'H'){
		cout << "RENT: " <<rent <<endl;
		cout << "BEDROOMS: " <<bedrooms <<endl;
		cout << "SQUARE FEET: " <<squarefeet <<endl;
	}
}
//a way to ask the program if character given to the function is the same as type of posting
bool posting::is_type(char asking_type)
{
	if(type == toupper(asking_type)) // if same, return true
		return true;
	else
		return false;
}

///implementation for lists ///

//default constructor
list::list()
{
	numpostings = 0; //set num postings to 0
}

//default deconstructor
list::~list()
{
	//nothing to deconstryct	
}
//displays all the postings in a list of postings
void list::display_all()
{ 
	for(int i = 0; i < numpostings; ++i) //as long as ther are postings
	{  
		postings[i].display_posting(); //display the postings
	}
}
//display postings of a specific type, like housing, jobs or for sale
void list::display_type(char type)
{
	for(int i = 0; i < numpostings; ++i) 
	{
		if (postings[i].is_type(type) == true) //if the type is the same
			postings[i].display_posting(); //display the match
	}
}
//create a new posting in the list
void list::add(char title[])
{
	postings[numpostings].create_posting(title); //create the posting in the right place
	numpostings = numpostings + 1; //increment post counter since one was added
}
