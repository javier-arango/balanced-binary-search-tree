#include <iostream>
#include <vector>
#include <regex>

#include "avl_tree.h"


using namespace std;


// Verify name
bool checkIsWord(string &word) {
    regex isAlphaObj = regex("^[\"A-Za-z\\s]*$");

    bool checkIfContainRegex = regex_search(word, isAlphaObj);

    return checkIfContainRegex;
}

// Verify ID
bool checkIsNumber(string &word) {
    regex isAlphaObj = regex("^[0-9]*$");

    // Check if the string only have digits
    if (regex_search(word, isAlphaObj)) {
        // Check if the string only have 8 digits max
        if (word.length() <= 8) return true;
    }

    // Return false otherwise
    return false;
}

// Get name
string getName(string firstName) {
    // Check if there is a last name and get it
    while(firstName.at(firstName.length()-1) != '"') {
        string lastName;  // Last name
        cin >> lastName;  // Get last name

        // Add the names
        firstName += " " + lastName;
    }


    // Check if there is double inverted commas  TODO: CHECK
    if (firstName.find('"') != string::npos) {
        firstName.erase(remove(firstName.begin(), firstName.end(), '\"' ), firstName.end());
    }

    // Return name
    return firstName;
}


int main() {
    // Operations
    const std::string INSERT = "insert";
    const std::string REMOVE = "remove";
    const std::string REMOVEINORDER = "removeInorder";
    const std::string SEARCH = "search";
    const std::string PRINTINORDER = "printInorder";
    const std::string PRINTPREORDER = "printPreorder";
    const std::string PRINTPOSTORDER = "printPostorder";
    const std::string PRINTLEVELCOUNT = "printLevelCount";

    // Tree
    avl_tree avlTree;

    // Welcome message
    cout << "Welcome to the AVL Tree Menu! (organize student accounts based on IDs)" << endl;
    cout << "You are allow to manipulate the tree by using different operations such as: " << endl;
    cout << "1- insert: Add a Student object into the tree with the specified name, number ID. The ID must be unique." << endl;
    cout << "2- remove: Find and remove the account with the specified ID from the tree." << endl;
    cout << "3- removeInorder. Remove the Nth ID from the inorder traversal of the tree (N = 0 for the first item, etc)." << endl << endl;
    cout << "4- search: Search for the student with the specified ID or name from the tree." << endl;
    cout << "5- printInorder: Print the tree using inOrder traversal." << endl;
    cout << "6- printPreorder: Print the tree using preOrder traversal." << endl;
    cout << "7- printPostorder: Print the tree using postOrder traversal." << endl;
    cout << "8- printLevelCount: Print the tree using levelOrder traversal." << endl;


    // Get number of commands
    int commandNum = 0;
    cout << "Please enter the number the operations (use integers numbers) you want to do (Example: 1): ";
    cin >> commandNum;  // Get number


    // Logic
    for (int i = 0; i < commandNum; i++) {
        // Data
        string tempVal = " ";  // temporary value to store name or id
        string studentName = " ";
        int gatorID = 0;
        int nthValue = 0;

        // Get operation to execute
        string operation = " ";
        cout << "Please add the operation you want to do using the names provided in the menu. ";
        cin >> operation;  // Get operation

        // Do the operation
        // Insert data to tree
        if(operation == INSERT) {
            // Get student name
            cout << "Please add the student name (added inside double quotes). Example: \"Brandon\" ";
            cin >> studentName;
            studentName = getName(studentName);  // Get full name if available
            if (checkIsWord(studentName)) {
                // Get gator id
                cout << "Please add the student ID. Example: 45679999 ";
                cin >> tempVal;
                if (checkIsNumber(tempVal)) {
                    gatorID = stoi(tempVal);

                    // Insert name and id
                    avlTree.insertNameID(gatorID, studentName);  // Insert data
                }
                // The id is wrong
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            // The name is wrong
            else {
                cout << "unsuccessful" << endl;
            }
        }

        // Remove data from tree
        else if (operation == REMOVE) {
            // Get gator id
            cout << "Please add the student ID that you want to remove. Example: 45679999 ";
            cin >> tempVal;
            if (checkIsNumber(tempVal)) {
                gatorID = stoi(tempVal);
                avlTree.removeID(gatorID);  // Remove data
            } else {
                cout << "unsuccessful" << endl;
            }
        }

        // Search student in tree
        else if (operation == SEARCH) {
            cout << "Please add the student ID that you want to search. Example: 45679999 ";
            cin >> tempVal;
            // Search with name
            if (checkIsWord(tempVal)) {
                studentName = tempVal;
                studentName = getName(studentName);  // Get full name if available
                avlTree.searchName(studentName);  // Search name
            }
            // Else search with id
            else if (checkIsNumber(tempVal)) {
                gatorID = stoi(tempVal);
                avlTree.searchID(gatorID);  // Search ID
            } else {
                cout << "unsuccessful" << endl;
            }
        }

        // Print inorder traversal
        else if (operation == PRINTINORDER) {
            cout << "Printing in order:" << endl;
            avlTree.printInorder();  // Print inorder
        }

        // Print preorder traversal
        else if (operation == PRINTPREORDER) {
            cout << "Printing in preorder:" << endl;
            avlTree.printPreorder();  // Print preorder
        }

        // Print postorder traversal
        else if (operation == PRINTPOSTORDER) {
            cout << "Printing in postorder:" << endl;
            avlTree.printPostorder();  // Print postorder
        }

        // Print level count
        else if (operation == PRINTLEVELCOUNT) {
            cout << "Printing in level count:" << endl;
            avlTree.printLevelCount();  // Print level count
        }

        // Remove the Nth node
        else if (operation == REMOVEINORDER) {
            // Get the position to delete
            cout << "Please add the position of the node you want to delete: ";
            cin >> tempVal;

            if (checkIsNumber(tempVal)) {
                nthValue = stoi(tempVal);
                avlTree.removeInorderN(nthValue);  // Remove inorder
            } else {
                cout << "unsuccessful" << endl;
            }
        }

        // Else the operation is wrong
        else {
            cout << "unsuccessful" << endl;
        }
    }


    return 0;
}
