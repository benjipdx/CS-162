/* Ben Reichert
Assignment #3 for CS162 at Portland State University

Purpose: Store a schedule of an annex to a Comic-Con event. 
This program takes in input and stores it with structs and 
external data files. Stores events and booths for the event. 


*/
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

struct booth_struct
{
	char name[40];
	char category[40];
	char description[100];
	char email[60];
};

struct event_struct
{
	char name[40];
	char accomplishments[100];
};


//function prototypes
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
bool find_booth(char userinputname, int & index);

int main()
{
	booth_struct booth[20];
	event_struct event[3];

	int booth_index = 0;
	int event_index = 0;

	event_index = get_index_event();
	booth_index = get_index_booth();
	cout << "The final booth index is: " <<booth_index <<endl;
	cout << "The final event index is: " <<event_index <<endl;


	welcome();

	char userinput;
	menu(userinput);

	while(userinput != 'X')
	{
		if (userinput == 'B' )
		{
				if(booth_index < 20)
				{
					cout <<"User entered b" <<endl;
					for(int i =0; again() == true && booth_index < 20; ++i)
					{
						booth_input(booth[i]);
						write_booth_to_file(booth[i], booth_index + 1);
						++booth_index;
					}
				}
				else if (booth_index >= 20)
				{
					cout << "There are already 20 booths registered for Comic-Con" <<endl;	
				}
				
			menu(userinput);			
		}

		else if (userinput == 'E')
		{
			if (event_index < 3)
			{
				cout <<"User entered e" <<endl;

				for(int i = 0; again() == true && event_index < 3; ++i)
				{
					event_input(event[i]);
					write_event_to_file(event[i], event_index+1);
					++event_index;
				}
			}
			else if (event_index > 3);
			{
				cout << "There are already three events registered for Comic-Con." <<endl;
			}

			menu(userinput);
		}

		else if (userinput == 'F')
		{
			//find()
			cout <<"User entered f" <<endl;
			int booth_location = 0;
			char userinputname[40];
			cout << "Enter a booth's name: ";
			cin.get(userinputname, 40, '\n');

			if(find_booth(userinputname, booth_location) == true)
				cout << "The booth, " <<userinputname <<" is located at booth number " <<booth_location <<endl;
			else if (find_booth(userinputname, booth_location) == false)
				cout << "Sorry, there are no booths matching " <<userinputname <<endl;

			menu(userinput);
		}

		else if (userinput == 'D') //display events
		{
			event_display();
			menu(userinput);
		}
		else if (userinput == 'G') //display booths
		{
			booth_display();
			menu(userinput);
		}
		else
		{
			cout << userinput << " is not a valid command. Please try another." <<endl;
			menu(userinput);
		}
	}
	
	return 0;
}

void welcome()
{
cout << "\n\n\n\n\n\nWelcome to the Comic-Con Annex Organizer. " <<endl;
}

void menu(char & userinput)
{
	cout << "Please enter:\n'b' to enter a booth\n'f' to find a booth\n'e' to enter an event\n"
	     << "'d' to display events\n'g' to display booths\n'x' to exit" <<endl <<"Enter here: ";
	cin >> userinput;
	cin.ignore(100,'\n');
	userinput = toupper(userinput);
}

void booth_input(booth_struct & booth)
{
	cout << "Please enter the name of the booth: ";
	cin.get(booth.name, 40, '\n');
	cin.ignore(100, '\n');

	cout << "Please enter the category of the booth: ";
	cin.get(booth.category, 40, '\n');
	cin.ignore(100, '\n');
	
	cout << "Please enter the description of the booth: ";
	cin.get(booth.description, 100, '\n');
	cin.ignore(100, '\n');

	cout << "Please enter an email or facebook page for the booth";
	cin.get(booth.email, 60, '\n');
	cin.ignore(100, '\n');

}

void write_booth_to_file(booth_struct & booth, int index)
{
	ofstream outfile; //set a output file variable
	outfile.open("booths.txt", ios::app); //open booths.txt for writing, in append mode so as not to write over existing data
	outfile << index <<'%' //write the firstname of structure course followed by a :
			<<booth.name <<'%' //write the lastname of structure course followed by a :
			<<booth.category <<'%' //write the crn to the file followed by a :
			<<booth.description <<'%' //write the course designator to the file followed by a :
			<<booth.email <<'\n'; //write the section, followed by a :, and a \n as a delimeter for the end of the data entry
	outfile.close(); //close the file when done writing to it
}


bool again()
{	
	char enteranother; //create local variable to hold y/n character
	cout << "Do you want to enter another? (y/n)" <<endl; //prompt user for input
	cin >> enteranother; //read in their single character
	cin.ignore(100, '\n');
	if (toupper(enteranother) == 'Y') //if the user wants to enter more, return true;
		return true;
	else if (toupper(enteranother) == 'N') //if the user wants to end the program, return false
		return false;
	else
		return false;
}


void event_input(event_struct & event)
{
	char name[40];
	cout << "Please enter the name of the event presenter: ";
	cin.get(event.name, 40, '\n');
	cin.ignore(100, '\n');

	cout << "Please enter the accomplishments of the event presenter: ";
	cin.get(event.accomplishments, 100, '\n');
	cin.ignore(100, '\n');
}

void write_event_to_file(event_struct & event, int index)
{
	ofstream outfile; //set a output file variable
	outfile.open("events.txt", ios::app); //open booths.txt for writing, in append mode so as not to write over existing data
	outfile << index <<'%' //write the firstname of structure course followed by a :
			<<event.name <<'%' //write the lastname of structure course followed by a :
			<<event.accomplishments <<'\n'; //write the section, followed by a :, and a \n as a delimeter for the end of the data entry
	outfile.close(); //close the file when done writing to it
}

void event_display()
{
	//char index[3];
	int index = 0;
	char tempname[40];
	char tempaccomplishments[100];

	ifstream infile;
	infile.open("events.txt");
	if (infile) //file is valid and opened
	{
		cout << "The Schedule is: " <<endl;

		while(!infile.eof())
		{
			infile >> index;
			infile.ignore(100, '%');
			infile.get(tempname, 40, '%');
			infile.ignore(100, '%');
			infile.get(tempaccomplishments, 100, '%');
			infile.ignore(100, '\n');
			
			cout << tempname <<" is on day " <<index << "." 
				 << "\nThe presenter's accomplishments are: " <<tempaccomplishments <<endl <<endl;
			
		}

	}
	else 
		cout << "File does not exits, or read operation failed." <<endl;
}

void booth_display()
{
	//char index[3];
	int index = 0;
	char tempname[40];
	char tempcategory[40];
	char tempdescription[100];
	char tempemail[60];

	ifstream infile;
	infile.open("events.txt");
	if (infile) //file is valid and opened
	{
		cout << "Here are all of the booths: " <<endl;

		while(!infile.eof())
		{
			infile >> index;
			infile.ignore(100, '%');
			infile.get(tempname, 40, '%');
			infile.ignore(100, '%');
			infile.get(tempcategory, 40, '%');
			infile.ignore(100, '\n');
			infile.get(tempdescription, 100, '%');
			infile.ignore(100, '%');
			infile.get(tempemail, 60, '%');
			infile.ignore(100, '\n');

			cout << "The booth: " <<tempname <<" is in location " <<index << "." 
				 << "\nThe category of the booth is:  " <<tempcategory 
				 << "\nThe description of the booth is: " <<tempdescription
				 << "\nThe email of the booth is: " <<tempemail <<endl;
			
		}

	}
	else 
		cout << "File does not exits, or read operation failed." <<endl;
}


int get_index_event()
{
	int index = 0;
	ifstream infile;
	infile.open("events.txt");

	if (infile) //file is valid and connected
		while(!infile.eof())
		{
			infile >> index;
			infile.ignore(100, '%');
			infile.ignore(100, '%');
			infile.ignore(100, '\n');
			cout << "Index is: " <<index <<endl;
		}	
	else 
		cout << "File does not exits, or read operation failed." <<endl;
	
	return index;
}


int get_index_booth()
{
	int index = 0;
	ifstream infile;
	infile.open("booths.txt");

	if (infile) //file is valid and connected
		while(!infile.eof())
		{
			infile >> index;
			infile.ignore(100, '%');
			infile.ignore(100, '%');
			infile.ignore(100, '%');
			infile.ignore(100, '%');
			infile.ignore(100, '\n');
			cout << "Index is: " <<index <<endl;
		}
	
	else 
		cout << "File does not exits, or read operation failed." <<endl;

	return index;
}

bool find_booth(char userinputname, int & index)
{
	char tempname[40];
	bool found = false;
	ifstream infile;
	infile.open("booths.txt");

	if(infile) //connected to file and valid file
	{	while(!infile.eof() && found == false)
		{
			infile >> index;
			infile.ignore(100, '%'); //ignore up to name
			infile.get(tempname, 40, '%');// get the name of the line of the file
			infile.ignore(100, '%');
			infile.ignore(100, '%');
			infile.ignore(100, '\n');
			if (strcmp(tempname, userinputname) == 0);
			{
				found = true;
				return found;
			else
				return found; //which will be false at this point if not found
			{
		}
	}
}
