/* Benjamin Reichert
CS162
Portland State University

manager.cpp class implementation
*/

#include "comiccon.h"

/*
class manager
{
	public:
		manager();
		list_events();
		list_booths();

	private:
		event event[3];
		booth booth[20];
		int num_booths;
		int num_events;

};
*/

manager::manager()
{
	
}

void booth::input(int index);
{
	cout << "Please enter the name of the booth: ";
	cin.get(name, 40, '\n');
	cin.ignore(100, '\n');

	cout << "Please enter the category of the booth: ";
	cin.get(category, 40, '\n');
	cin.ignore(100, '\n');
	
	cout << "Please enter the description of the booth: ";
	cin.get(description, 100, '\n');
	cin.ignore(100, '\n');

	cout << "Please enter an email or facebook page for the booth";
	cin.get(email, 60, '\n');
	cin.ignore(100, '\n');

	write_to_file(index);

}

void booth::write_to_file(int index)
{
	ofstream outfile; //set a output file variable
	outfile.open("booths.txt", ios::app); //open booths.txt for writing, in append mode so as not to write over existing data
	outfile << index <<'%' //write the firstname of structure course followed by a :
			<<name <<'%' //write the lastname of structure course followed by a :
			<<category <<'%' //write the crn to the file followed by a :
			<<description <<'%' //write the course designator to the file followed by a :
			<<email<<'%' <<'\n'; //write the section, followed by a :, and a \n as a delimeter for the end of the data entry
	outfile.close(); //close the file when done writing to it
}


bool booth::again()
{	
	char enteranother; //create local variable to hold y/n character
	cout << "Do you want to enter another booth? (y/n)" <<endl; //prompt user for input
	cin >> enteranother; //read in their single character
	if (toupper(enteranother) == 'Y') //if the user wants to enter more, return true
		return true;
	else if (toupper(enteranother) == 'N') //if the user wants to end the program, return false
		return false;
}

