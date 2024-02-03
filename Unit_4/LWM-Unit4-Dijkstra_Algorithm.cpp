/*
    Written by: Lukas Myers
    Date: 1-28-2024
    Class: CSC 543 Advanced Algorithms
    Project: Unit 4 - Dijkstra's algorithm implementation using characters a-z vertices and non-negative edges on an undirected graph.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <sstream>

using namespace std;

// edge of a graph
struct Edge {
    char destination;
    int weight;
};

// node in the selected priority queue
struct Node {
    char vertex;
    int distance;
};

// comparison function for priority queue
struct CompareNodes {
    bool operator()(const Node &a, const Node &b) {
        return a.distance > b.distance;
    }
};

void displayInfo(string &assignment, string &stDate);
int checkVal(char kind, int val, int vertices);
void inputGraph(vector<vector<Edge>> &graph, int edges);
bool checkEdges(int vertices, int edges);
void addEdge(vector<vector<Edge>> &graph, char source, char destination, int weight);
bool edgeExists(const vector<vector<Edge>> &graph, char source, char destination);
void dijkstra(const vector<vector<Edge>> &graph, char source, char destination, vector<int> &distance, unordered_map<char, char> &parent);
bool validNode(char node, int vertices);
char checkStartEnd(char kind, int vertices, vector<vector<Edge>> &graph);
void displayGraph(const vector<vector<Edge>> &graph);
void displayBestPath(char destination, const unordered_map<char, char> &parent, const vector<vector<Edge>> &graph);


int main() {
    string stDate = "Jan 28 2024";
    string assignment = "Unit 4 - Dijkstra's Algorithm - displays the shortest path with the lowest cost";
	displayInfo(assignment, stDate);  // display project information

    do {
        int vertices, edges;

        // input vertices and edges
        cout << "Enter the number of vertices: ";
        vertices = checkVal('v', vertices, vertices);
        if(vertices==-1)
            break;  // exit program with -1

        cout << "Enter the number of edges: ";
        edges = checkVal('e', edges, vertices);
        if(edges==-1)
            break;  // exit program with -1

        // input the graph data
        vector<vector<Edge>> graph(vertices);

        // input the graph data using letters as vertices
        cout << endl << "Edge source and destinations must be in range from 'A' to '" << static_cast<char>(toupper(char('a' + graph.size() - 1))) << "'" << endl;
        inputGraph(graph, edges);

        // display the graph
        cout << endl << "Adjacency List Graph:" << endl;
        displayGraph(graph);

        // input starting and ending nodes
        char start, end;
        start = checkStartEnd('s', vertices, graph);
        end = checkStartEnd('e', vertices, graph);

        // dijkstra's algorithm finding best path
        vector<int> distance;  // holds the distance values
        unordered_map<char, char> parent;   // holds the vertex values
        dijkstra(graph, start, end, distance, parent);

        // display the cost of the shortest path if it exists
        if (distance[end - 'a'] == numeric_limits<int>::max())
            cout << endl << "No path exists between '" << static_cast<char>(toupper(start)) << "' and '" << static_cast<char>(toupper(end)) << "'" << endl;
         else {
            cout << endl << "Cost of the Shortest Path from '" << static_cast<char>(toupper(start)) << "' to '" << static_cast<char>(toupper(end)) << "' : " << distance[end - 'a'] << endl;
            // display the shortest path
            displayBestPath(end, parent, graph);
         }

        // clear
        cin.clear();    // clear buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');    // ignore buffer to new line
        cout << endl << "[Exit with -1]" << endl;
    } while(true);
    return 0;
}

// functions //

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

// check input values
int checkVal(char kind, int val, int vertices) {
    do {
        // while input is empty
        while (cin.peek() == '\n') {
            cin.clear();    // clear buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // ignore buffer to new line
            if(kind == 'v')
                cout << "\nEnter the number of vertices (-1 to exit): ";
            else if (kind == 'e')
                cout << "\nEnter the number of edges (-1 to exit): ";
        }
        
        // while NOT an integer
        while(!(cin>>val)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(kind == 'v') {
                cout << endl << "Input Error: Vertices input is NOT a valid positive number";
                cout << endl << "Enter the number of vertices (-1 to exit): ";
            } else if (kind == 'e') {
                cout << endl << "Input Error: Edges input is NOT a valid positive number"; 
                cout << endl << "Enter the number of edges (-1 to exit): ";
            }
        }
        
        // while vertex less than -1 and greater than 26
        while (kind=='v' && (val>26 || val<-1)) {
            do {
                cout << endl << "Input Error: Currently the number of vertices must NOT be greater than (26) or less than (0)";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nEnter the number of vertices (-1 to exit): ";
            } while(!(cin>>val)); // while not an integer
        }

        // while edge is not greater than max edge size
        while (kind=='e' && !checkEdges(vertices, val)) {
            do {
                cout << endl << "Input Error: Invalid number of edges, the max number of edges is (" << (vertices * (vertices - 1)) / 2 << ")";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nEnter the number of edges (-1 to exit): ";
            } while(!(cin>>val)); // while not an integer
        }

    } while(cin && cin.peek() != '\n'); // while not empty
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

// check if the number of edges is within the maximum
bool checkEdges(int vertices, int edges) {
    // maximum number of edges in an undirected graph
    int maxEdges = (vertices * (vertices - 1)) / 2;
    return (edges >= 0) && (edges <= maxEdges);
}

// input graph data
void inputGraph(vector<vector<Edge>> &graph, int edges) {
    for (int i = 0; i < edges; ++i) {
        char source, destination;
        int weight;
        cout << "Enter edge " << i + 1 << " (source destination weight): ";
        cin >> source >> destination >> weight;
        source = tolower(source);
        destination = tolower(destination);

        // check if input nodes are within the valid range
        if ( (('a' <= source && source <= 'z') || ('A' <= source && source <= 'Z')) && (('a' <= destination && destination <= 'z') || ('A' <= destination && destination <= 'Z')) ) {
            if ( ('a' <= source && source < 'a' + graph.size() && 'a' <= destination && destination < 'a' + graph.size()) ) {
                if (!edgeExists(graph, source, destination)) {
                    if (weight>=0 && weight) {
                        addEdge(graph, source, destination, weight);  // undirected graph
                    } else {
                        cout << endl << "Input Error: Weight needs to be a greater than or equal to 0" << endl;
                        --i;  // decrement i to repeat the input for this edge
                    }
                } else {
                    cout << endl << "Input Error: Edge already exists" << endl;
                    --i;  // decrement i to repeat the input for this edge
                }
            } else {
                cout << endl << "Input Error: Invalid source or destination, nodes must be letters in the range [A, " << static_cast<char>(toupper(char('a' + graph.size() - 1))) << "]" << endl;
                --i;  // decrement i to repeat the input for this edge
            }
        } else {
            cout << endl << "Input Error: Source and Destination must be letters (case insensitive)." << endl;
            --i;  // decrement i to repeat the input for this edge
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// check if an edge already exists in the graph
bool edgeExists(const vector<vector<Edge>> &graph, char source, char destination) {
    for (const Edge &edge : graph[source - 'a']) {
        if (edge.destination == destination) {
            return true;
        }
    }
    for (const Edge &edge : graph[destination - 'a']) {
        if (edge.destination == source) {
            return true;
        }
    }
    return false;
}

// add an edge to the graph if it doesn't already exist
void addEdge(vector<vector<Edge>> &graph, char source, char destination, int weight) {
    // check if source and destination vertices are within the valid range and are characters
    if ('a' <= source && source < 'a' + graph.size() && 'a' <= destination && destination < 'a' + graph.size() ) {
        // check if destination vertex exists
        if ('a' <= destination && destination < 'a' + graph.size()) {
            // add edge if it doesn't exist already
            if (!edgeExists(graph, source, destination)) {
                graph[source - 'a'].push_back({destination, weight});
                graph[destination - 'a'].push_back({source, weight});  // Assuming an undirected graph
            } else {
                cout << endl << "Input Error: Edge already exists. Enter different edge value" << endl;
            }
        } else {
            cout << "Destination vertex does not exist. Enter a valid destination vertex.\n";
        }
    } else {
        cout << "Invalid source or destination vertex. Nodes must be letters in the range [a, " << char('a' + graph.size() - 1) << "]. Try again.\n";
    }
}

// check if a vertex node is within the valid range
bool validNode(char node, int vertices) {
    return ('A' <= node && node < 'A' + vertices) || ('a' <= node && node < 'a' + vertices);
}

// get a valid starting or ending node input
char checkStartEnd(char kind, int vertices, vector<vector<Edge>> &graph) {
    char input;
    while (true) {
        if (kind == 's')
            cout << endl << "Enter the starting node: ";
        else if (kind == 'e')
            cout << "Enter the ending node: ";
        cin >> input;
        // check if the node is within the valid range
        if (validNode(input, vertices)) {
            return input;
        }
        cout << endl << "Input Error: Please enter a valid node in range from 'A' to '" << static_cast<char>(toupper(char('a' + graph.size() - 1))) << "]";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// display the adjacency list graph
void displayGraph(const vector<vector<Edge>> &graph) {
    for (char c = 'a'; c < 'a' + graph.size(); ++c) {
        cout << c << " -> ";
        for (const Edge &edge : graph[c - 'a']) {
            cout << edge.destination << "(" << edge.weight << ") ";
        }
        cout << endl;
    }
}

// perform dijkstras algorithm
void dijkstra(const vector<vector<Edge>> &graph, char source, char destination, vector<int> &distance, unordered_map<char, char> &parent) {
    int gSize = graph.size();

    // priority queue that stores nodes with their distances
    priority_queue<Node, vector<Node>, CompareNodes> pq;

    // set distances to all vertices as infinity
    distance.assign(gSize, numeric_limits<int>::max());

    // set distance to source vertex to 0
    distance[source - 'a'] = 0;

    // parent map to store the shortest path
    parent[source] = '\0';

    // push source node into the priority queue
    pq.push({source, 0});

    while (!pq.empty()) {
        // get the minimum distance node from the priority queue
        Node node = pq.top();
        pq.pop();

        char nVertex = node.vertex;

        // when the destination node is reached, break the loop
        if (nVertex == destination) {
            break;
        }

        // iterate through all adjacent vertices
        for (const Edge &edge : graph[nVertex - 'a']) {
            char eDest = edge.destination;
            int weight = edge.weight;

            // check vertex and compare edges relaxing neighbors
            if (distance[nVertex - 'a'] != numeric_limits<int>::max() && distance[nVertex - 'a'] + weight < distance[eDest - 'a']) {
                distance[eDest - 'a'] = distance[nVertex - 'a'] + weight;
                parent[eDest] = nVertex;
                pq.push({eDest, distance[eDest - 'a']});
            }
        }
    }
}

// print the shortest path from source to destination with weights
void displayBestPath(char destination, const unordered_map<char, char> &parent, const vector<vector<Edge>> &graph) {
    vector<char> path;
    // while the node vertex is not infinite
    while (destination != '\0') {
        path.push_back(destination);
        destination = parent.at(destination);
    }
    // display path
    cout << "Shortest Path: ";
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i];
        if (i > 0) {
            cout << " -> ";
            // find the weight of the edge
            char u = path[i];
            char v = path[i - 1];
            int weight = 0;
            for (const Edge &edge : graph[u - 'a']) {
                if (edge.destination == v) {
                    weight = edge.weight;
                    break;
                }
            }
            cout << "(" << weight << ") ";
        }
    }
    cout << endl;
}