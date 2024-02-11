/*
    Written by: Lukas Myers
    Date: 2-4-2024
    Class: CSC 543 Advanced Algorithms
    Project: Unit 5 - Dynamic programming using the longest common substring problem, to find the longest string that is a substring of two or more strings.
*/

#include <iostream>
#include <vector>

using namespace std;

void displayInfo(string &assignment, string &stDate);
string longestCommonSubstring(const string &str1, const string &str2);

int main() {
    string stDate = "Feb 4 2024";
    string assignment = "Unit 5 - Dynamic programming using the longest common substring problem, to find the longest string that is a substring of two or more strings";
	displayInfo(assignment, stDate);  // display project information

    string str1 = "ABABC";
    string str2 = "BABAC";

    do {
        cout << "Enter string 1: ";
        cin >> str1;
        if(str1=="-1")
            break;
        cout << "Enter string 2: ";
        cin >> str2;
        if(str2=="-1")
            break;
           
        string commonSubstring = longestCommonSubstring(str1, str2);    // longest common substring 
        cout << endl << "Longest Common Substring: '" << commonSubstring << "' with length [" << commonSubstring.length() << "]" << endl << endl;
        cout << "[Exit with -1]" << endl;
    } while(true);
    return 0;
}

// get longest common substring
string longestCommonSubstring(const string &str1, const string &str2) {
    int m = str1.length();
    int n = str2.length();

    // the 2D table to store the length of the common substring
    vector<vector<int>> grid(m + 1, vector<int>(n + 1, 0));

    // vars for length and the longest common substring
    int maxLength = 0;
    int endIndex = 0;

    // fill the dynamic programming table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i - 1] == str2[j - 1]) {
                grid[i][j] = grid[i - 1][j - 1] + 1;
                if (grid[i][j] > maxLength) {
                    maxLength = grid[i][j];
                    endIndex = i - 1;
                }
            } else {
                grid[i][j] = 0;
            }
        }
    }

    // display the dynamic programming table
    cout << endl << "Dynamic Programming Table:" << endl;
    cout << "  ";
    for (int j = 0; j < m; ++j) {
        cout << str1[j] << " ";
    }
    cout << endl;

    for (int i = 1; i <= m; ++i) {
        cout << str2[i - 1] << " ";
        for (int j = 1; j <= n; ++j) {
            cout << grid[j][i] << " ";
        }
        cout << endl;
    }

    // Extract the longest common substring
    string result = str1.substr(endIndex - maxLength + 1, maxLength);
    return result;
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