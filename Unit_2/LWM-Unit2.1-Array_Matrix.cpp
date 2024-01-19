/*
    Written by: Lukas Myers
    Date: 1-14-2024
    Class: CSC 543 Advanced Algorithms
    Project: Unit 2.1 - Array sparse matrix
*/

#include <iostream>
#include <limits>
#include <iomanip>
#include <cstring>
using namespace std;

const int MAX_SIZE = 100;
int matrix[MAX_SIZE][MAX_SIZE] = {0};
int sparseMatrix[MAX_SIZE][3];

void displayInfo(string &assignment, string &stDate);
int rowColNum(char kind, int &val);
int inputSparseMatrix(int rows, int cols, int count);
void displayMatrix(int rows, int cols);
void displaySparseMatrix(int rows);
void searchValue(int rows);

int main() {
    string stDate = "Jan 14 2024";
    string assignment = "Unit 2.1 - Sparse Matrix - display the values of a sparse matrix using an array";
	displayInfo(assignment, stDate);  // display project information

    int rows, cols, count = 0;

    // main input loop
    do {
        cout << "\nEnter the number of rows: ";

        // Input the number of rows and columns of the matrix
        rows = rowColNum('r', rows);
        if (rows == -1)
            break;  // exit program
        cols = rowColNum('c', cols);
        if (cols == -1) 
            break;

        // Input the elements of the matrix, return count
        count = inputSparseMatrix(rows, cols, count);

        // Display the original matrix
        displayMatrix(rows, cols);

        // Search for a value in the sparse matrix, displays indexes if found
        searchValue(count);

        // Display the sparse matrix
        displaySparseMatrix(count);

        // Reset array count and matrix 
        count = 0;
        memset(matrix, 0, sizeof matrix);
    } while(true);
    
    return 0;
}

// Row and column input values
int rowColNum(char kind, int &val) {
    do {
        // while input is empty
        while (cin.peek() == '\n') {
            cin.clear();    // clear buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // ignore buffer to new line
            if(kind == 'r')
                cout << "\nEnter the number of rows (-1 to exit): ";
            else if (kind == 'c')
                cout << "\nEnter the number of columns (-1 to exit): ";
            else
                cout << "\nEnter the value to search in the sparse matrix: ";
        }
        // while not a number
        while (!(cin >> val)) {
            cout << "\nInput Error: Invalid input value (numbers only)";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(kind == 'r')
                cout << "\nEnter the number of rows (-1 to exit): ";
            else if (kind == 'c')
                cout << "\nEnter the number of columns (-1 to exit): ";
            else
                cout << "\nEnter the value to search in the sparse matrix: ";
        }
    } while(cin && cin.peek() != '\n');
    return val;
}

// function input array values
int inputSparseMatrix(int rows, int cols, int count) {
    int numCnt = rows * cols;
    int inputSize = numCnt/2;
    int rowIndex, colIndex;
    bool check = false;
    // get value input size based on array size
    if (!(numCnt % 2))
        inputSize--;
    cout << "\nEnter " << inputSize << " matrix values (Greater than 0)" << endl;
    // fill array with values and zeros
    for (int x = 0; x < inputSize; x++) {
        rowIndex = rand() % rows; //generates a random number between 0 and rows
        colIndex = rand() % cols;
        cout << "Value #" << x+1 << ": ";
        do{
            check = false;
            if (matrix[rowIndex][colIndex] == 0) {
                cin >> matrix[rowIndex][colIndex];
            } else {
                check = true;
                rowIndex = rand() % rows; //generates a random number between 0 and rows
                colIndex = rand() % cols;
            }
        } while(check);
    }
    
    // fill array with sparse matrix non-zero values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] != 0) {
                sparseMatrix[count][0] = i; // Row index
                sparseMatrix[count][1] = j; // Column index
                sparseMatrix[count][2] = matrix[i][j]; // Value
                count++;
            }
        }
    }
    cin.clear();    // clear buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');    // ignore buffer to new line
    return count;
}

// function display the normal matrix
void displayMatrix(int rows, int cols) {
    cout << "\nSparse Matrix:" << endl;
    cout << "Rows=" << rows << " Cols=" << cols << endl;
    for (int i = 0; i < rows; ++i) {
        cout << setw(1);
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << setw(4);
        }
        cout << endl;
    }
}

// Function to display the sparse matrix
void displaySparseMatrix(int rows) {
    cout << "\nSparse Matrix Non-Zero Index Values:" << endl;
    cout << " Row " << setw(3) << " Col " << setw(3) << " Value" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << setw(4) << sparseMatrix[i][j];
        }
        cout << endl;
    }
}

// Function to search for a value in the sparse matrix and return indices
void searchValue(int rows) {
    cout << "\nEnter a value to search in the sparse matrix: ";
    int search = rowColNum('s', rows);
    string result = "Value "+to_string(search)+" was NOT found!";
    for (int i = 0; i < rows; ++i) {
        if (sparseMatrix[i][2] == search) {
            //cout << "Value " << search << " found at index (" << sparseMatrix[i][0] << ", " << sparseMatrix[i][1] << ")" << endl;
            result = "Value "+to_string(search)+" found at index ("+to_string(sparseMatrix[i][0])+", "+to_string(sparseMatrix[i][1])+")";
            break;
        }
    }
    cout << result << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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