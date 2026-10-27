
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
using namespace std;

class CampusGraph {
private:
    int V;
    vector<string> locations;
    vector<vector<int>> adj;

public:
    // Constructor
    CampusGraph() {
        V = 8;

        locations = {
            "Main Gate",
            "Library",
            "Block 1",
            "Block 2",
            "Cafeteria",
            "Auditorium",
            "Parking",
            "Lab"
        };

        adj.resize(V);

        // Create campus paths (undirected graph)
        addEdge(0, 1);
        addEdge(0, 6);
        addEdge(1, 2);
        addEdge(1, 4);
        addEdge(2, 3);
        addEdge(2, 7);
        addEdge(3, 4);
        addEdge(4, 5);
    }

    // Add an undirected edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Display all campus locations
    void displayLocations() const {
        cout << "\n--- CAMPUS LOCATIONS ---\n";

        for (int i = 0; i < V; i++) {
            cout << i + 1 << ". " << locations[i] << "\n";
        }
    }

    // BFS: Find shortest route in an unweighted graph
    void findShortestRoute(int source, int destination) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;

        visited[source] = true;
        q.push(source);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == destination) {
                break;
            }

            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        if (!visited[destination]) {
            cout << "\nNo route exists between "
                 << locations[source] << " and "
                 << locations[destination] << ".\n";
            return;
        }

        // Reconstruct the route using parent[]
        vector<int> path;

        for (int node = destination;
             node != -1;
             node = parent[node]) {
            path.push_back(node);
        }

        cout << "\n--- BFS SHORTEST ROUTE ---\n";
        cout << "From: " << locations[source] << "\n";
        cout << "To:   " << locations[destination] << "\n";
        cout << "Route: ";

        for (int i = static_cast<int>(path.size()) - 1;
             i >= 0; i--) {
            cout << locations[path[i]];

            if (i > 0) {
                cout << " -> ";
            }
        }

        cout << "\nMinimum number of edges: "
             << path.size() - 1 << "\n";
    }

    // Recursive DFS helper
    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << locations[node] << "\n";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited);
            }
        }
    }

    // Display all locations reachable using DFS
    void displayReachableLocations(int source) {
        vector<bool> visited(V, false);

        cout << "\n--- DFS TRAVERSAL ---\n";
        cout << "Starting from: "
             << locations[source] << "\n\n";

        dfs(source, visited);
    }

    // Display locations unreachable from the selected source
    void displayDisconnectedLocations(int source) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[source] = true;
        q.push(source);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        cout << "\n--- CONNECTIVITY REPORT ---\n";
        cout << "Starting location: "
             << locations[source] << "\n";

        bool found = false;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                cout << "Unreachable: "
                     << locations[i] << "\n";
                found = true;
            }
        }

        if (!found) {
            cout << "All campus locations are reachable "
                 << "from " << locations[source] << ".\n";
        }
    }

    // Validate a user-entered location number
    int getLocationChoice() {
        int choice;

        while (true) {
            cout << "Enter location number (1-" << V << "): ";

            if (cin >> choice &&
                choice >= 1 && choice <= V) {
                return choice - 1;
            }

            cout << "Invalid input! Please enter a number "
                 << "between 1 and " << V << ".\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
        }
    }
};

int main() {
    CampusGraph campus;
    int choice;

    cout << "====================================\n";
    cout << "       CAMPUS ROUTE FINDER\n";
    cout << "          Using Graphs\n";
    cout << "====================================\n";

    while (true) {
        cout << "\n1. Display Campus Locations";
        cout << "\n2. Find Shortest Route (BFS)";
        cout << "\n3. Display Reachable Locations (DFS)";
        cout << "\n4. Find Unreachable Locations";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            continue;
        }

        switch (choice) {
            case 1:
                campus.displayLocations();
                break;

            case 2: {
                cout << "\nSelect source location:\n";
                campus.displayLocations();
                int source = campus.getLocationChoice();

                cout << "\nSelect destination location:\n";
                int destination = campus.getLocationChoice();

                campus.findShortestRoute(source, destination);
                break;
            }

            case 3: {
                campus.displayLocations();
                int source = campus.getLocationChoice();
                campus.displayReachableLocations(source);
                break;
            }

            case 4: {
                campus.displayLocations();
                int source = campus.getLocationChoice();
                campus.displayDisconnectedLocations(source);
                break;
            }

            case 5:
                cout << "\nThank you for using "
                     << "Campus Route Finder!\n";
                return 0;

            default:
                cout << "Invalid choice! Select 1 to 5.\n";
        }
    }

    return 0;
}
