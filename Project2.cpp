
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Structure for a student record and BST node
struct Node {
    int enrolmentID;
    string name;
    string department;
    Node* left;
    Node* right;

    Node(int id, string n, string d) {
        enrolmentID = id;
        name = n;
        department = d;
        left = nullptr;
        right = nullptr;
    }
};

class StudentBST {
private:
    Node* root;

    // Insert a student into the BST
    Node* insertNode(Node* node, int id,
                     string name, string department) {
        if (node == nullptr) {
            return new Node(id, name, department);
        }

        if (id < node->enrolmentID) {
            node->left = insertNode(
                node->left, id, name, department
            );
        } else if (id > node->enrolmentID) {
            node->right = insertNode(
                node->right, id, name, department
            );
        } else {
            cout << "Duplicate enrolment ID not allowed.\n";
        }

        return node;
    }

    // Search for a student
    Node* searchNode(Node* node, int id, int& comparisons) const {
        while (node != nullptr) {
            comparisons++;

            if (id == node->enrolmentID) {
                return node;
            }

            if (id < node->enrolmentID) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        return nullptr;
    }

    // Find the minimum node in a subtree
    Node* findMinimum(Node* node) const {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Delete a node from the BST
    Node* deleteNode(Node* node, int id, bool& found) {
        if (node == nullptr) {
            return nullptr;
        }

        if (id < node->enrolmentID) {
            node->left = deleteNode(node->left, id, found);
        } else if (id > node->enrolmentID) {
            node->right = deleteNode(node->right, id, found);
        } else {
            found = true;

            // Case 1: Leaf node
            if (node->left == nullptr &&
                node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: Node has one child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Node has two children
            Node* successor = findMinimum(node->right);

            node->enrolmentID = successor->enrolmentID;
            node->name = successor->name;
            node->department = successor->department;

            bool successorDeleted = false;
            node->right = deleteNode(
                node->right,
                successor->enrolmentID,
                successorDeleted
            );
        }

        return node;
    }

    // Inorder: Left, Root, Right
    void inorder(Node* node) const {
        if (node == nullptr) return;

        inorder(node->left);
        displayStudent(node);
        inorder(node->right);
    }

    // Preorder: Root, Left, Right
    void preorder(Node* node) const {
        if (node == nullptr) return;

        displayStudent(node);
        preorder(node->left);
        preorder(node->right);
    }

    // Postorder: Left, Right, Root
    void postorder(Node* node) const {
        if (node == nullptr) return;

        postorder(node->left);
        postorder(node->right);
        displayStudent(node);
    }

    void displayStudent(Node* node) const {
        cout << "ID: " << node->enrolmentID
             << " | Name: " << node->name
             << " | Department: " << node->department
             << "\n";
    }

    // Calculate tree height
    int treeHeight(Node* node) const {
        if (node == nullptr) return 0;

        return 1 + max(
            treeHeight(node->left),
            treeHeight(node->right)
        );
    }

    // Release allocated memory
    void destroyTree(Node* node) {
        if (node == nullptr) return;

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    StudentBST() {
        root = nullptr;
    }

    ~StudentBST() {
        destroyTree(root);
    }

    void insert(int id, string name, string department) {
        root = insertNode(root, id, name, department);
    }

    void search(int id) const {
        int comparisons = 0;
        Node* result = searchNode(root, id, comparisons);

        if (result != nullptr) {
            cout << "\nStudent found:\n";
            displayStudent(result);
        } else {
            cout << "\nStudent with ID " << id
                 << " was not found.\n";
        }

        cout << "Comparisons: " << comparisons << "\n";
    }

    void remove(int id) {
        bool found = false;
        root = deleteNode(root, id, found);

        if (found) {
            cout << "Student record deleted successfully.\n";
        } else {
            cout << "Student ID not found.\n";
        }
    }

    void showInorder() const {
        cout << "\n--- INORDER (SORTED BY ID) ---\n";
        inorder(root);
    }

    void showPreorder() const {
        cout << "\n--- PREORDER ---\n";
        preorder(root);
    }

    void showPostorder() const {
        cout << "\n--- POSTORDER ---\n";
        postorder(root);
    }

    int height() const {
        return treeHeight(root);
    }

    int countComparisons(int id) const {
        int comparisons = 0;
        searchNode(root, id, comparisons);
        return comparisons;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

// Insert ten sample records
void loadSampleRecords(StudentBST& bst) {
    int ids[] = {
        105, 102, 108, 101, 103,
        107, 110, 104, 106, 109
    };

    for (int id : ids) {
        bst.insert(
            id,
            "Student" + to_string(id),
            "CSE"
        );
    }

    cout << "10 sample records inserted.\n";
}

// Compare balanced-looking and sorted insertion orders
void compareInsertionOrders() {
    StudentBST balancedLooking;
    StudentBST sortedOrder;

    int balancedIDs[] = {
        5, 3, 7, 2, 4, 6, 8
    };

    int sortedIDs[] = {
        2, 3, 4, 5, 6, 7, 8
    };

    for (int id : balancedIDs) {
        balancedLooking.insert(
            id, "Student" + to_string(id), "CSE"
        );
    }

    for (int id : sortedIDs) {
        sortedOrder.insert(
            id, "Student" + to_string(id), "CSE"
        );
    }

    int target = 8;

    cout << "\n--- BST EFFICIENCY COMPARISON ---\n";
    cout << "Records in each tree: 7\n";
    cout << "Search target ID: " << target << "\n\n";

    cout << "Balanced-looking insertion order:\n";
    cout << "Height: " << balancedLooking.height() << "\n";
    cout << "Search comparisons: "
         << balancedLooking.countComparisons(target) << "\n\n";

    cout << "Sorted insertion order:\n";
    cout << "Height: " << sortedOrder.height() << "\n";
    cout << "Search comparisons: "
         << sortedOrder.countComparisons(target) << "\n";
}

int main() {
    StudentBST bst;
    int choice, id;
    string name, department;

    while (true) {
        cout << "\n====================================\n";
        cout << "   STUDENT RECORD SEARCH SYSTEM\n";
        cout << "       USING BINARY SEARCH TREE\n";
        cout << "====================================\n";
        cout << "1. Insert Student Record\n";
        cout << "2. Search Student Record\n";
        cout << "3. Delete Student Record\n";
        cout << "4. Display Inorder Traversal\n";
        cout << "5. Display Preorder Traversal\n";
        cout << "6. Display Postorder Traversal\n";
        cout << "7. Display Tree Height\n";
        cout << "8. Load 10 Sample Records\n";
        cout << "9. Compare Insertion Orders\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter enrolment ID: ";
                if (!(cin >> id)) {
                    cout << "Invalid ID.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }

                cin.ignore(10000, '\n');

                cout << "Enter student name: ";
                getline(cin, name);

                cout << "Enter department: ";
                getline(cin, department);

                if (name.empty() || department.empty()) {
                    cout << "Name and department cannot be empty.\n";
                    break;
                }

                bst.insert(id, name, department);
                break;

            case 2:
                cout << "Enter enrolment ID to search: ";
                if (cin >> id) {
                    bst.search(id);
                } else {
                    cout << "Invalid ID.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;

            case 3:
                cout << "Enter enrolment ID to delete: ";
                if (cin >> id) {
                    bst.remove(id);
                } else {
                    cout << "Invalid ID.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                break;

            case 4:
                bst.showInorder();
                break;

            case 5:
                bst.showPreorder();
                break;

            case 6:
                bst.showPostorder();
                break;

            case 7:
                cout << "Tree height: " << bst.height() << "\n";
                break;

            case 8:
                if (bst.isEmpty()) {
                    loadSampleRecords(bst);
                } else {
                    cout << "Load sample records into an empty tree "
                         << "to avoid duplicate IDs.\n";
                }
                break;

            case 9:
                compareInsertionOrders();
                break;

            case 10:
                cout << "Thank you for using the system!\n";
                return 0;

            default:
                cout << "Invalid choice. Select 1 to 10.\n";
        }
    }

    return 0;
}
