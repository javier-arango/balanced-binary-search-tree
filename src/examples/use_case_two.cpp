//
// Created by Javier Arango on 1/31/23.
//

#include "avl_tree.h"


using namespace std;

int main() {
    // Tree
    avl_tree avlTree;

    // Student names and ID
    string studentNames[10] = {"Amelia Rose", "Olivia Grace", "Ethan James", "Liam Alexander",
                        "Mia Isabella", "Amelia", "Olivia", "Ethan", "Liam", "Mia"};

    int studentIDs[10] = {45679999, 45680000, 45680001, 45680002,
                          45680003, 45680004, 45680005, 45680006, 45680007, 45680008};

    // Insert students
    cout << "Insert students: " << endl;
    for (int i = 0; i < 10; i++) avlTree.insertNameID(studentIDs[i], studentNames[i]);

    // Search by name
    cout << "\nSearch by name and get ids: " << endl;
    for (int i = 0; i < 10; i++) avlTree.searchName(studentNames[i]);

    // Search by ids and get names
    cout << "\nSearch by IDs: " << endl;
    for (int i = 0; i < 10; i++) avlTree.searchID(studentIDs[i]);

    // Print in order
    cout << "\nPrint inorder: " << endl;
    avlTree.printInorder();

    // Print post order
    cout << "\nPrint postorder: " << endl;
    avlTree.printPostorder();

    // Print pre order
    cout << "\nPrint preorder: " << endl;
    avlTree.printPreorder();

    // Print level count
    cout << "\nPrint level count: " << endl;
    avlTree.printLevelCount();

    // Remove all the students left
    cout << "\nRemove students by id: " << endl;
    for (int i = 0; i < 10; i++) avlTree.removeID(studentIDs[i]);

    // Remove the nth student
    cout << "\nInsert students names: " << endl;
    avlTree.insertNameID(studentIDs[0], studentNames[0]);
    avlTree.insertNameID(studentIDs[1], studentNames[1]);

    cout << "\nPrint in order: " << endl;
    avlTree.printInorder();

    cout << "\nRemove student name by the nth position: " << endl;
    avlTree.removeInorderN(1);

    cout << "\nPrint in order: " << endl;
    avlTree.printInorder();

    return 0;
}

