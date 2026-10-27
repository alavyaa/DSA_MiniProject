# DSA Mini Projects – PPF Week 9

This repository contains two C++ mini-projects developed as part of the PPF Week 9 Data Structures and Algorithms assignment.

## Projects

### Project 1: Campus Route Finder Using Graphs

A console-based application that represents campus locations as vertices and paths as edges in an undirected graph.

**Features**
- Represents the campus network using an adjacency list.
- Uses Breadth-First Search (BFS) to find the route with the minimum number of edges.
- Uses Depth-First Search (DFS) to display reachable locations.
- Identifies locations unreachable from a selected starting point.
- Accepts user input for source and destination locations.

**Concepts Used**
- Graph representation
- Adjacency lists
- BFS and DFS
- Queues and recursion
- Visited arrays and parent tracking
- Reachability and shortest paths in unweighted graphs

**Time Complexity**
- BFS: `O(V + E)`
- DFS: `O(V + E)`
- Adjacency-list storage: `O(V + E)`

Here, `V` represents the number of vertices and `E` represents the number of edges.

### Project 2: Student Record Search System Using Binary Search Tree

A menu-driven application that stores and manages student records using a Binary Search Tree (BST). Each record contains an enrolment ID, student name, and department.

**Features**
- Inserts student records using unique enrolment IDs.
- Searches for students by enrolment ID.
- Deletes records while handling leaf nodes, nodes with one child, and nodes with two children.
- Displays inorder, preorder, and postorder traversals.
- Rejects duplicate enrolment IDs.
- Compares tree height and search comparisons for different insertion orders.

**Concepts Used**
- Binary Search Trees
- Insertion, searching, and deletion
- Inorder, preorder, and postorder traversals
- Recursion and tree height
- Balanced-looking versus skewed trees
- Time and space complexity analysis

**Time Complexity**
- Insertion: Average `O(log n)`, worst case `O(n)`
- Searching: Average `O(log n)`, worst case `O(n)`
- Deletion: Average `O(log n)`, worst case `O(n)`
- Traversals: `O(n)`

Here, `n` represents the number of student records.

## Repository Structure

```text
DSA-Mini-Projects/
├── project1.cpp    # Campus Route Finder using Graphs
├── project2.cpp    # Student Record Search System using BST
└── README.md       # Project documentation
```

## Requirements

- C++ compiler, such as GCC (`g++`)
- Visual Studio Code or another C++ editor
- Terminal or command prompt

## How to Compile and Run

### Project 1: Campus Route Finder

Compile:

```bash
g++ project1.cpp -o project1
```

Run on Windows:

```powershell
.\project1.exe
```

### Project 2: Student Record Search System

Compile:

```bash
g++ project2.cpp -o project2
```

Run on Windows:

```powershell
.\project2.exe
```

## Testing

Both projects should be tested with valid and invalid inputs.

**Project 1**
- Test a direct route between two locations.
- Test a route requiring multiple stops.
- Test DFS traversal and location reachability.

**Project 2**
- Test insertion and searching.
- Test duplicate enrolment IDs.
- Test deletion of leaf nodes, nodes with one child, and nodes with two children.
- Test all three tree traversals.
- Compare balanced-looking and sorted insertion orders.

## Learning Outcomes

These projects provide practical experience in implementing graphs and trees in C++, applying fundamental data structure algorithms, validating user input, and analysing algorithm efficiency.

