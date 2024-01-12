/*
    Written by: Lukas Myers
    Date: 1-8-2024
    Class: CSC 543 Advanced Algorithms
    Project: Indices - get index of two array values sum that equals target value.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

void displayInfo(string &assignment);
vector<int> findSum(vector<int> &arrs, int &target);

int main() {
    string assignment = "Unit 1 - Indices - get array index of values that equal the sum of a target value";
	displayInfo(assignment);  // display project information

    int vsize, nums, target;   // input values
    vector<int> vec, result;    // vectors to hold numbers
    cout << "Enter an array of numbers (separated by spaces): ";
    
    // loop for input
    do {
        // loop for number array
        do {
            // while input is empty
            while (cin.peek() == '\n') {
                cin.clear();    // clear buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    // ignore buffer to new line
                cout << "\nEnter an array of numbers (separated by spaces) (-1 to exit): ";
            }
            
            // while not a number
             while (!(cin >> nums)) {
                cout << "\nInput Error: array has an invalid input value (numbers only)";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vec.clear();    // clear vector array
                cout << "\nEnter an array of numbers (separated by spaces) (-1 to exit): ";
            }

            // push to vector if between -109 and 109
            if (nums >= -109 && nums <= 109) {
                vec.push_back(nums);
            } else {
                cout << "\nInput Error: array value " << nums << " is out of range";
                cin.clear();    
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                vec.clear();
                cout << "\nEnter an array of numbers (separated by spaces) (-1 to exit): ";
            }
        } while (cin && cin.peek() != '\n');

        // break loop and exit
        if (nums == -1) { break; }

        // get and check size of vector
        vsize = vec.size();
        if (vsize >= 2 && vsize <= 104) {
            // enter target number
            cout << "Enter the target value: ";
            cin >> target;
            if (target >= -109 && target <= 109) {
                result = findSum(vec, target);  // returns indexes of the sum of numbers that equal target

                // print out input values
                cout << "Input: numbers = [";
                for (int i = 0; i < vsize; i++)
                {
                    if (i > 0) {
                        cout << ", " << vec[i];
                    } else {
                        cout << vec[i];
                    }
                }
                cout << "], target = " << target << "\n";
                
                // print output results
                if (!result.empty()) {
                    cout << "Output: indexes = [" << result[0] << ", " << result[1] << "] - (" << vec[result[0]] << " + " << vec[result[1]] << " = " << target << ")\n";
                } else {
                    cout << "No solution found.\n";
                }
            } else {
                cout << "\nInput Error: target value " << target << " is out of range";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } else {
            //cout << "\nInput Error: array requires more values (2 or more)";
        }

        vec.clear();    // clear vector
        result.clear();
    } while (nums != -1);

    return 0;
}

// find sum in array
vector<int> findSum(vector<int> &vec, int &target) {
    unordered_map<int, int> map;    // map to hold number index values
    for (int i = 0; i < vec.size(); ++i) {
        int remaining = target - vec[i];    // get remainder from target
        // find remaining value in the map
        if (map.find(remaining) != map.end()) {
            // return the indices of the two numbers that add up to the target
            return {map[remaining], i};
        }
        // insert the current index number to the map
        map[vec[i]] = i;
    }
    // return an empty vector if no sum is found
    map.clear();
    return {};
}

// diplay project information
void displayInfo(string &assignment)
{
	cout << "****************************************\n";
	cout << "Written by   : Lukas Myers" << endl;
	cout << "Course       : CSC 543 Advanced Algorithms" << endl;
	cout << "Instructor   : Dr. Farah Kamw" << endl;
	cout << "Assignment   : " << assignment << endl;
	cout << "Compile Date : " << __DATE__ << endl; //2 underscores DATE 2 underscores
	cout << "****************************************\n";
}