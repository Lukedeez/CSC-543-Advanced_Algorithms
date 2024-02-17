/*
    Written by: Lukas Myers
    Date: 2-11-2024
    Class: CSC 543 Advanced Algorithms
    Project: Unit 6 - Compression algorithm using the Huffman coding, to analyze the frequency of characters or symbols.
*/

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

// huffman tree node
struct Node {
    char input;
    int freq;
    Node *left;
    Node *right;

    Node(char input, int freq) : input(input), freq(freq), left(nullptr), right(nullptr) {}
};

// compare and order the min heap
struct compare {
    bool operator()(Node *l, Node *r) {
        return (l->freq > r->freq);
    }
};

void displayInfo(string &assignment, string &stDate);
void printPreorder(Node *root, string code, vector<string> &huffmanCodes);
void huffmanTree(unordered_map<char, int> &charFreqMap);


int main() {
    string stDate = "Feb 11 2024";
    string assignment = "Unit 6 - Compression algorithm using the Huffman coding, to analyze the frequency of characters or symbols";
	displayInfo(assignment, stDate);  // display project information

    string input = "abcdef";
    int freq[] = {5, 9, 12, 13, 16, 45};

    cout << "String input: "+input << endl;
    cout << "Frequencies: ";

    int i = 0;
    unordered_map<char, int> charFreqMap;
    for (char c : input) {
        cout << freq[i] << " ";
        charFreqMap[c] = freq[i];
        i++;
    }
    cout << endl;

    huffmanTree(charFreqMap);

    return 0;
}


// print the huffman codes in preorder
void printPreorder(Node *root, string code, vector<string> &huffmanCodes) {
    // if no root exit
    if (!root)
        return;

    // store leaf node code
    if (!root->left && !root->right) {
        cout << root->input << " : " << code << endl;
        huffmanCodes[root->input - 'a'] = code;
    }

    // left side
    printPreorder(root->left, code + "0", huffmanCodes);

    // right side
    printPreorder(root->right, code + "1", huffmanCodes);
}

// build the huffman tree
void huffmanTree(unordered_map<char, int> &charFreqMap) {
    priority_queue<Node*, vector<Node*>, compare> minHeap;

    // tree nodes stored in min heap que
    for (auto &entry : charFreqMap) {
        minHeap.push(new Node(entry.first, entry.second));
    }

    while (minHeap.size() != 1) {
        // get 2 smallest nodes from the heap
        Node *left = minHeap.top();
        minHeap.pop();

        Node *right = minHeap.top();
        minHeap.pop();

        // new node with the sum of the two nodes as frequency 
        Node *newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // push new node to min heap que
        minHeap.push(newNode);
    }

    // display huffman codes from the tree
    string code = "";
    vector<string> huffmanCodes(charFreqMap.size());
    printPreorder(minHeap.top(), code, huffmanCodes);
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