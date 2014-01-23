#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream inFile;
	ofstream outFile;
		
	inFile.open("data.txt");
	outFile.open("newdata.txt");

	outFile << "Testing scores are st00pidz" <<endl;

	inFile.close();
	outFile.close();

	return 0;
}
