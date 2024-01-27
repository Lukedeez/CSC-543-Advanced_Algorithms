/*
    Written by: Lukas Myers
    Date: 1-21-2024
    Class: CSC 543 Advanced Algorithms
    Project: Unit 2.2 - Linked list implementation of a sparse matrix
*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;

// node structure for the linked list
struct Node {
    int row;
    int col;
    int value;
    Node* next;
};

// matrix array
const int MAX_SIZE = 100;
int matrix[MAX_SIZE][MAX_SIZE] = {0};

void displayInfo(string &assignment, string &stDate);
int checkVal(char kind, int val);
void inputSparseMatrix(Node *&head, int rows, int cols);
void insertNode(Node *&head, int row, int col, int value);
void displayList(Node *head);
int inputCheck(int val, int &nodeCnt);

// main start
int main() {
    string stDate = "Jan 21 2024";
    string assignment = "Unit 2.2 - Sparse Matrix - display the values of a sparse matrix using a linked list";
	displayInfo(assignment, stDate);  // display project information
    
    do {
        // vars
        Node* head = nullptr;
        int rows=0, cols=0;

        // input and check row/col values
        cout << "Enter the number of rows in the matrix: ";
        rows = checkVal('r', rows);
        if(rows==-1)
            break;
        cout << "Enter the number of columns in the matrix: ";
        cols = checkVal('c', cols);
        if(cols==-1)
            break;

        // input sparse matrix
        inputSparseMatrix(head, rows, cols);

        // display the linked list
        displayList(head);

        // clean up memory delete linked list
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        memset(matrix, 0, sizeof matrix);   // reset array
        cin.clear();    // clear buffer
        cout << "[Exit with -1]" << endl;
    } while(true);

    return 0;
}

// row col value check
int checkVal(char kind, int val) {
    do {
        // while input is empty
        while (cin.peek() == '\n') {
            cin.clear();    // clear buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // ignore buffer to new line
            if(kind == 'r')
                cout << "\nEnter the number of rows (-1 to exit): ";
            else if (kind == 'c')
                cout << "\nEnter the number of columns (-1 to exit): 1s";
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
        }

        // while less than exit code -1
        while(val < -1) {
            cout << "\nInput Error: Invalid input value (positive numbers only)";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(kind == 'r')
                cout << "\nEnter the number of rows (-1 to exit): ";
            else if (kind == 'c')
                cout << "\nEnter the number of columns (-1 to exit): ";
            cin >> val;    
        }

    } while(cin && cin.peek() != '\n');
    cin.clear();    // clear buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

// input
void inputSparseMatrix(Node*& head, int rows, int cols) {
    int numCnt = rows * cols;
    int inputSize = numCnt/2;
    int rowIndex, colIndex;
    bool check = false;
    if (!(numCnt % 2))
        inputSize--;
    cout << "\nInput " << inputSize << " Sparse Matrix Values" << endl;
    int row, col, value, nodeCnt=0;
    // Allowing users to input matrix elements and their locations
    do {
        cout << "Enter #" << nodeCnt + 1 << " (Row Column Value): ";
        cin >> row >> col >> value;
        // check inputs
        if (row < rows && row >= 0) {
            if (col < cols && col >= 0) {
                if (value >= 0) {
                    matrix[row][col] = value; // Value
                    nodeCnt++;
                } else {
                    cout << endl << "Error: Value " << value << " is not valid" << endl;
                }
            } else {
                cout << endl << "Error: Column index " << col << " is out of bounds" << endl;
            }
        } else {
            cout << endl << "Error: Row index " << row << " is out of bounds" << endl;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (nodeCnt<inputSize);
    
    // display the sparse matrix
    cout << "\nSparse Matrix:" << endl;
    cout << "Rows=" << rows << " Cols=" << cols << endl;
    for (int i = 0; i < rows; i++) {
        cout << setw(1);
        for (int j = 0; j < cols; j++) {
            value = matrix[i][j];
            cout << value << setw(4);
            // insert non-zero values to node
            if(value != 0)
                insertNode(head, i, j, value);
        }
        cout << endl;
    }
    cout << endl;
};

// insert a new node into the linked list
void insertNode(Node *&head, int row, int col, int value) {
    Node* newNode = new Node;
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        // if the list is empty, set the new node as the head
        head = newNode;
    } else {
        // else traverse to the end and insert the new node
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
};

// display the linked list
void displayList(Node* head) {
    cout << "Linked List representation of the sparse matrix:" << endl;
    Node* temp = head;
    int cnt = 1;
    while (temp != nullptr) {
        cout << "Node #" << cnt << " Row: " << temp->row << ", Column: " << temp->col << ", Value: " << temp->value << endl;
        temp = temp->next;
        cnt++;
    }
    cout << endl;
};

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