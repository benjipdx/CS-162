/* Benjamin Reichert
CS162
Portland State University

Booth.cpp class implementation
*/

#include "comiccon.h"

/*


class event
{
	public:
		event(); //default constructor
		void input();
		bool again();
		void write_to_file();
		void display();

	private:
		char name[40];
		char accomplishments[100];

};
*/

event::event()
{
	name[0] = '\0';
	accomplishments[0] = '\0';
}

void event::input(int index)
{
	cout << "Please enter the name of the event presenter: ";
	cin.get(name, 40, '\n');
	cin.ignore(100, '\n');

	cout << "Please enter the accomplishments of the event presenter: ";
	cin.get(accomplishments, 100, '\n');
	cin.ignore(100, '\n');
	
	write_to_file(index);

}

void event::write_to_file(int index)
{
	ofstream outfile; //set a output file variable
	outfile.open("events.txt", ios::app); //open booths.txt for writing, in append mode so as not to write over existing data
	outfile << index <<'%' //write the firstname of structure course followed by a :
			<<name <<'%' //write the lastname of structure course followed by a :
			<<accomplishments <<'\n'; //write the section, followed by a :, and a \n as a delimeter for the end of the data entry
	outfile.close(); //close the file when done writing to it
}
/*
void event::display()
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
*/


bool event::again()
{	
	char enteranother; //create local variable to hold y/n character
	cout << "Do you want to enter another event? (y/n)" <<endl; //prompt user for input
	cin >> enteranother; //read in their single character
	if (toupper(enteranother) == 'Y') //if the user wants to enter more, return true
		return true;
	else if (toupper(enteranother) == 'N') //if the user wants to end the program, return false
		return false;
}

