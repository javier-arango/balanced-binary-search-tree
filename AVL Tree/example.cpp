#include <iostream>
#include <vector>
#include <regex>
#include "AVLTree.h"


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
    const std::string SEARCH = "search";
    const std::string PRINTINORDER = "printInorder";
    const std::string PRINTPREORDER = "printPreorder";
    const std::string PRINTPOSTORDER = "printPostorder";
    const std::string PRINTLEVELCOUNT = "printLevelCount";
    const std::string REMOVEINORDER = "removeInorder";

    // Tree
    AVLTree avlTree;

    // Get number of commands
    int commandNum = 0;
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
        cin >> operation;  // Get operation

        // Do the operation
        // Insert data to tree
        if(operation == INSERT) {
            // Get student name
            cin >> studentName;
            studentName = getName(studentName);  // Get full name if available
            if (checkIsWord(studentName)) {
                // Get gator id
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
            avlTree.printInorder();  // Print inorder
        }

        // Print preorder traversal
        else if (operation == PRINTPREORDER) {
            avlTree.printPreorder();  // Print preorder
        }

        // Print postorder traversal
        else if (operation == PRINTPOSTORDER) {
            avlTree.printPostorder();  // Print postorder
        }

        // Print level count
        else if (operation == PRINTLEVELCOUNT) {
            avlTree.printLevelCount();  // Print level count
        }

        // Remove the Nth node
        else if (operation == REMOVEINORDER) {
            // Get the position to delete
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
