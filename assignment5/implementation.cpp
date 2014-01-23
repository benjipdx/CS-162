/* Benjamin Reichert 
CS162 @ Portland State University
3/18/13 
Assignment #5 
Part of the Command Line Awesome Posting System, or CLAPS 
*/

#include "class.h"

//default constructor, intializes data 
list::list()
{
	head = NULL;
}

//default deconstructor
list::~list()
{
	delete head;
}

//adds an item to the LLL and updates head to point there
void list::add()
{
	char tempname[100]; //create a holder for a temp name
	if (head == NULL) //if there aren't any items in the list
	{
		head = new node; //create a new item
		cout << "What should the posting's title be? "; //ask what the title should be
		cin.get(tempname, 100, '\n'); //read in tempname
		cin.ignore(200, '\n'); //ignore input buffer
		head->post.create_posting(tempname); //fill new node with populated data
		head -> next = NULL; //set the next pointer to null as it is the last in the list now
	}
	else if(head != NULL) //if there are items in the list
	{
		node * current = head; //create a current pointer and set it to head
		while(current -> next != NULL) //while there is another item in the list
		{
			current = current -> next; //traverse
		}
		current -> next = new node; //reached end of list, add new node
		current = current -> next; //traverse to new node
 
		cout << "What should the posting's title be? "; //read in title
		cin.get(tempname, 100, '\n'); //get title
		cin.ignore(200, '\n');
		current->post.create_posting(tempname); //populate new posting
	}

}
//display all of the postings for the LLL of items
void list::display_all()
{
	if(head) //while head points to something
	{
		head->post.display_posting('H'); //display the current posting head points to
		node * current = head; // create a pointer for current and have it point to head
		while(current) //while current points to something	
		{
			current->post.display_posting('H'); //display the current posting
			current = current -> next; //traverse to the next node
		}
	}
}


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
void posting::display_posting(char type)
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
