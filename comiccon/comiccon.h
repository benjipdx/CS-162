/* Benjamin Reichert
Header file for Assignment #3

*/

#include <iostream>
#include <fstream>

using namespace std;

class booth
{
	public:
		booth(); //default constructor
		void input();
		bool again();
		void write_to_file();
		void display();

	private:
		char name[40];
		char category[40];
		char description[100];
		char email[60];

};

class event
{
	public:
		event(); //default constructor
		void input(int index);
		bool again();
		void write_to_file(int index);
//		void display();

	private:
		char name[40];
		char accomplishments[100];

};


class manager
{
	public:
		manager();
	//	void list_events();
	//	void list_booths();

	private:
		event events[3];
		booth booths[20];
		int num_booths;
		int num_events;

};
