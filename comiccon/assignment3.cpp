/* Ben Reichert



*/
#include <fstream>
#include <iostream>
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
void event_input(event_struct & event, int index);

int main()
{
	booth_struct booth[20];
	event_struct event[3];

	booth_input(booth[0]);
	write_booth_to_file(booth[0], 0);


	return 0;
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

//	write_booth_to_file(index);
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
	if (toupper(enteranother) == 'Y') //if the user wants to enter more, return true
		return true;
	else if (toupper(enteranother) == 'N') //if the user wants to end the program, return false
		return false;
}


void event_input(event_struct & event, int index)
{
	cout << "Please enter the name of the event presenter: ";
	cin.get(event.name, 40, '\n');
	cin.ignore(100, '\n');

	cout << "Please enter the accomplishments of the event presenter: ";
	cin.get(event.accomplishments, 100, '\n');
	cin.ignore(100, '\n');
	
//	write_event_to_file(index);

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
	int index;
	char tempname[40];
	char tempaccomplishments[100];

	ifstream infile;
	infile.open("events.txt");
	
	while(!infile.eof())
	{
		//infile >> index;
		infile.ignore(100, '%');
		infile.get(tempname, 40, '%');
		infile.ignore(100, '%');
		infile.get(tempaccomplishments, 100, '%');
		infile.ignore(100, '\n');
	}

	cout << tempname <<" is on day " <<index << "." 
		 << "\nThe presenter's accomplishments are: " <<tempaccomplishments <<endl <<endl;
}

