/*
    Written by: Lukas Myers
    Date: 2-18-2024
    Class: CSC 543 Advanced Algorithms
    Project: Unit 7&8 - Blockchain & hash algorithms, using SHA-256 to hash a string of the book of Mark.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include "sha256.h"

using namespace std;

void displayInfo(string &assignment, string &stDate);

int main() {
    string stDate = "Feb 18 2024";
    string assignment = "Units 7 & 8 - Hash algorithms, using SHA-256 on the text from the book of Mark.";
	displayInfo(assignment, stDate);  // display project information

    // open file
    ifstream file("book_of_mark.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open file.\n";
        return 1;
    }

    // file contents converted to a string
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    cout << "Hash SHA-256 of the book of Mark:" << endl;
    cout << sha256(content) << endl;

    return 0;
}

// diplay project information
void displayInfo(string &assignment, string &stDate)
{
	cout << "****************************************\n";
	cout << "Written by   : Lukas Myers" << endl;
    cout << "Start Date   : " << stDate << endl;
	cout << "Course       : CSC 543 Advanced Algorithms" << endl;
	cout << "Instructor   : Dr. Farah Kamw" << endl;
	cout << "Assignment   : " << assignment << endl;
	cout << "Compile Date : " << __DATE__ << endl; //2 underscores DATE 2 underscores
	cout << "****************************************\n";
}