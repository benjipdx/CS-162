/* Ben Reichert
Assignment #3 for CS162 at Portland State University
2/20/13

Purpose: Store a schedule of an annex to a Comic-Con event. 
This program takes in input and stores it with structs and 
external data files. Stores events and booths for the event. 

It's also the largest program by far that I have ever written. 
Yay!
*/
#include <fstream>
#include <iostream>
#include <cstring> //for strcmp in find_booth()
using namespace std;

//a struct that holds information about booths
struct booth_struct
{
	char name[40]; //holds the name of the booth
	char category[40]; //holds the category of the booth
	char description[100]; //holds the description of the booth
	char email[60]; //holds the email of the booth
};


//a struct that holds information for events
struct event_struct
{
	char name[40]; //holds the name of the event presenter
	char accomplishments[100]; //hold the accomplishments of the presenter
};


//*******************FUNCTION PROTOTYPES************************//
void event_display();
void booth_input(booth_struct & booth);
bool again();
void write_booth_to_file(booth_struct & booth, int index);
void write_event_to_file(event_struct & event, int index);
void event_input(event_struct & event);
void booth_display();
void menu(char & userinput);
void welcome();
int get_index_event();
int get_index_booth();
bool find_booth(char userinputname[], int & index);
/*****************************************************************/


//main is the huge workhorse here where all of the logic of the program takes place
//calls all of the functions, has a long list of conditional logic for determining 
//what the user wants from the menu input system
int main()
{
	booth_struct booth[20]; //create an array of 20 booths of struct type booth_struct
	event_struct event[3]; //create an array of 3 events of struct type event_struct

	int booth_index = 0; //set the index (location) to 0
	int event_index = 0; //set the index (day) to 0

	event_index = get_index_event(); //call function to read in file and get actual index
	booth_index = get_index_booth(); // call function to read in file to get actual index

	welcome(); //display welcome message
 
	char userinput; //initialize character input variable
	menu(userinput); //run menu feeding in userinput

	while(userinput != 'X') //as long as the user doesnt want to exit
	{
		if (userinput == 'B' ) //if the user enters b
		{
				if(booth_index < 20) //and there aren't already too many entries
				{
					for(int i =0; again() == true && booth_index < 20; ++i) //loop through and enter data
					{
						booth_input(booth[i]);
						write_booth_to_file(booth[i], booth_index + 1); 
						++booth_index; //increment counter
					}
				}
				else if (booth_index >= 20) //if already are too many booth entries ( more than 20) 
				{
					cout << "There are already 20 booths registered for Comic-Con" <<endl;
				}
				
			menu(userinput); //open menu again
		}

		else if (userinput == 'E') //if user enters e
		{
			if (event_index < 3) //and there aren't already too many entries
			{
				for(int i = 0; again() == true && event_index < 3; ++i) //loop through and enter data
				{
					event_input(event[i]);
					write_event_to_file(event[i], event_index+1);
					++event_index; //increment counter
				}
			}
			else if (event_index > 3); //if already too many entries
			{
				cout << "There are already three events registered for Comic-Con." <<endl;
			}

			menu(userinput); //open menu back up
		}

		else if (userinput == 'F') //if the user enters f
		{
			int booth_location = 0; //initialize searched for booth location to 0
			char userinputname[40]; //holds users search query
			cout << "Enter a booth's name: "; 
			cin.get(userinputname, 40, '\n'); //get input info
			cin.ignore(100, '\n');

			if(find_booth(userinputname, booth_location) == true) //if the input query is found output in nice format
				cout << "The booth, " <<userinputname <<" is located at booth number " <<booth_location <<endl;
			else if (find_booth(userinputname, booth_location) == false) //if not tell user they are out of luck
				cout << "Sorry, there are no booths matching " <<userinputname <<endl;

			menu(userinput); //open menu selection
		}

		else if (userinput == 'D') //display events if user enters d
		{
			event_display(); 
			menu(userinput); //open menu
		}
		else if (userinput == 'G') //display booths if user enters g
		{
			booth_display(); 
			menu(userinput); //open menu
		}
		else
		{
			cout << userinput << " is not a valid command. Please try another." <<endl; //if user enters command not on list
			menu(userinput); //run menu again
		}
	}
	
	return 0;
}


//just a little meet and greet function that takes no arguments or returns values
void welcome()
{
	cout << "\n\n\n\n\n\nWelcome to the Comic-Con Annex Organizer. " <<endl; //output statement
}

//This is where the menu tells the user what they have for options, and when reads in input
// and feeds it back to the calling function, which is usally a conditional in main()
//takes in userinput by reference so it doesn't have to return it
void menu(char & userinput)
{
	cout << "Please enter:\n'b' to enter a booth\n'f' to find a booth\n'e' to enter an event\n"
	     << "'d' to display events\n'g' to display booths\n'x' to exit" <<endl <<"Enter here: ";
	cin >> userinput;
	cin.ignore(100,'\n');
	userinput = toupper(userinput);
}

//input information about a booth
//takes in booth struct as argument by reference 
void booth_input(booth_struct & booth)
{
	cout << "Please enter the name of the booth: ";
	cin.get(booth.name, 40, '\n'); //prompt and read booth name
	cin.ignore(100, '\n');

	cout << "Please enter the category of the booth: ";
	cin.get(booth.category, 40, '\n'); //prompt and read booth category
	cin.ignore(100, '\n');
	
	cout << "Please enter the description of the booth: ";
	cin.get(booth.description, 100, '\n'); //prompt and read booth description
	cin.ignore(100, '\n');

	cout << "Please enter an email or facebook page for the booth: ";
	cin.get(booth.email, 60, '\n'); //prompt and read booth email
	cin.ignore(100, '\n');
}

//takes in booth and index as arguments to write to correct spots
//writes booth to file as requested, one booth structure at a time
void write_booth_to_file(booth_struct & booth, int index)
{
	ofstream outfile; //set a output file variable
	outfile.open("booths.txt", ios::app); //open booths.txt for writing, in append mode so as not to write over existing data
	outfile << index <<'%' //write the index followed by a %
			<<booth.name <<'%' //write the name  of structure followed by a %
			<<booth.category <<'%' //write the category to the file followed by a %
			<<booth.description <<'%' //write the description to the file followed by a %
			<<booth.email <<'\n'; //write the section, followed by a %, and a \n as a delimeter for the end of the data entry
	outfile.close(); //close the file when done writing to it
}

//asks the user if they would like to enter more information
//returns true if yes, false if no
bool again()
{	
	char enteranother; //create local variable to hold y/n character
	cout << "Do you want to enter? (y/n)" <<endl; //prompt user for input
	cin >> enteranother; //read in their single character
	cin.ignore(100, '\n');
	if (toupper(enteranother) == 'Y') //if the user wants to enter more, return true;
		return true;
	else if (toupper(enteranother) == 'N') //if the user wants to end the program, return false
		return false;
	else //if entered something else, assume false
		return false;
}

//takes in event as argument and reads in information to record in the struct
//returns nothing, since struct was passed in by reference
void event_input(event_struct & event)
{
	cout << "Please enter the name of the event presenter: ";
	cin.get(event.name, 40, '\n'); //prompt and read in event name
	cin.ignore(100, '\n');

	cout << "Please enter the accomplishments of the event presenter: ";
	cin.get(event.accomplishments, 100, '\n'); //prompt and read in event accomplishments
	cin.ignore(100, '\n');
}


//writes the event structure to file using index to properly write it
//to the right location, returns nothing
void write_event_to_file(event_struct & event, int index)
{
	ofstream outfile; //set a output file variable
	outfile.open("events.txt", ios::app); //open events.txt for writing, in append mode so as not to write over existing data
	outfile << index <<'%' //write the index followed by %
			<<event.name <<'%' //write the name of presenter followed by %
			<<event.accomplishments <<'\n'; //write the \n as a delimeter for the end of the data entry
	outfile.close(); //close the file when done writing to it
}


//displays all of the events listed in the events.txt file
//reads in the file and outputs what it finds
void event_display()
{ 
	int index = 0;  //all three are temporary holders just for outputing to stdout
	char tempname[40];
	char tempaccomplishments[100];

	ifstream infile;
	infile.open("events.txt");
	if (infile) //file is valid and opened
	{
		cout << "The Schedule is: " <<endl;

		while(!infile.eof()) //while not at the end of the file
		{
			infile >> index; //read in index
			infile.ignore(100, '%'); 
			infile.get(tempname, 40, '%'); //read in name
			infile.ignore(100, '%');
			infile.get(tempaccomplishments, 100, '%'); //read in accomplishments
			infile.ignore(100, '\n');
			
			cout << tempname <<" is on day " <<index << "." 
				 << "\nThe presenter's accomplishments are: " <<tempaccomplishments <<endl <<endl; 
				 //output the found data and loop back through the looop for the next entry
		}

	}
	else 
		cout << "File does not exits, or read operation failed." <<endl; //if it cannot reach the file, tells user
}


//displays all of the booths in booths.txt after reading them all in
//outputs each entry in one instance of the loop
void booth_display()
{
	//char index[3];
	int index = 0;
	char tempname[40];
	char tempcategory[40];
	char tempdescription[100];
	char tempemail[60];
	//^^^^ All temporary variables simply used to hold info for stdout

	ifstream infile;
	infile.open("booths.txt");
	if (infile) //file is valid and opened
	{
		cout << "Here are all of the booths: " <<endl;

		while(!infile.eof()) //while not at the end of the file
		{
			infile >> index; //read in index
			infile.ignore(100, '%');
			infile.get(tempname, 40, '%'); //read in name
			infile.ignore(100, '%');
			infile.get(tempcategory, 40, '%'); //read in category
			infile.ignore(100, '\n');
			infile.get(tempdescription, 100, '%'); //read in description
			infile.ignore(100, '%');
			infile.get(tempemail, 60, '%'); //read in email
			infile.ignore(100, '\n');

			cout << "The booth: " <<tempname <<" is in location " <<index << "." 
				 << "\nThe category of the booth is:  " <<tempcategory 
				 << "\nThe description of the booth is: " <<tempdescription
				 << "\nThe email of the booth is: " <<tempemail <<endl <<endl;
			//output all found data in a nice format :)
		}

	}
	else 
		cout << "File does not exits, or read operation failed." <<endl; //if couldn't find file, tell user
}

//returns the curent last index of the file so that entries are not overwritten and dont
//have duplicate numbers between runs of the program
int get_index_event()
{
	int index = 0; //if file doesn't exist, the default will be 0
	ifstream infile; 
	infile.open("events.txt");

	if (infile) //file is valid and connected
		while(!infile.eof()) //as long as were not at the end of the file
		{
			infile >> index; //read in index
			infile.ignore(100, '%'); //skip the rest until next index
			infile.ignore(100, '%');
			infile.ignore(100, '\n');
		}	
	else 
		cout << "File does not exits, or read operation failed." <<endl; //if failed to find file, tell user
	
	return index; //return found index, or 0 by default
}

//used to find the index of the booths.txt entries
//returns the int of the last index so not to overwrite things or duplicated
int get_index_booth()
{
	int index = 0; //default value
	ifstream infile;
	infile.open("booths.txt");

	if (infile) //file is valid and connected
		while(!infile.eof()) //while not at the end of the file
		{
			infile >> index; //read in index
			infile.ignore(100, '%'); // ignore the rest until next index
			infile.ignore(100, '%');
			infile.ignore(100, '%');
			infile.ignore(100, '%');
			infile.ignore(100, '\n');
		}
	
	else 
		cout << "File does not exits, or read operation failed." <<endl; //if failed, tell user

	return index; //return index of found value or 0 if not found as default
}


//finds a booth in the database that matches a name entered by the user
//returns true if found and with index of where booth will be located
//returns false if cannot find
bool find_booth(char userinputname[], int & index)
{
	char tempname[40]; //used to hold name from database
	bool found = false; //by default, haven't found yet
	ifstream infile; 
	infile.open("booths.txt");

	if(infile) //connected to file and valid file
	{	while(!infile.eof() && found == false) //not at the end of the file and haven't found yet
		{
			infile >> index; //read in index
			infile.ignore(100, '%'); //ignore up to name
			infile.get(tempname, 40, '%');// get the name of the line of the file
			infile.ignore(100, '%');
			infile.ignore(100, '%');//ignore the rest
			infile.ignore(100, '\n');
			if (strcmp(tempname, userinputname) == 0) //if strcmp matches the two
			{
				found = true;  //we found it
				return found; //return found 
			}
			else
				return found; //which will be false at this point if not found
			
		}
	}
}

//Thanks for grading! :) //
