//
// Created by Javier Arango on 2/11/22.
//

#pragma once

#include <iostream>
#include <vector>


class avl_tree {
    // Tree node
    class TreeNode {
    public:
        // Attributes
        int gatorID;
        std::string fullName;
        int height;
        TreeNode *left, *right;

        // Constructor
        TreeNode(int id, std::string &name) : gatorID(id), fullName(name), height(0), left(nullptr), right(nullptr) {}

        // Methods
        int getHeight(TreeNode *node) {
            // Check if the node is empty
            if (node == nullptr) return -1;

            // Increase the height
            return 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    };

    // Attributes
    TreeNode *rootNode;

    // Normal methods
    TreeNode *deleteTree(TreeNode* root);  // Delete all the nodes from memory
    int getBalance(TreeNode *node);  // Get balance of the node
    TreeNode *leftRotation(TreeNode *root);  // Left rotation
    TreeNode *rightRotation(TreeNode *root);  // Right rotation
    TreeNode *getParentNode(TreeNode *root, int id);  // Helper function to find the parent node

    // Helper methods
    TreeNode *insertHelper(TreeNode *root, int id, std::string name);  // Helper method to insert ID and Name into node
    TreeNode *removeIDHelper(TreeNode *root, int id);  // Helper method to remove ID
    TreeNode *inorderSuccessor(TreeNode *root);  // Find the in order successor to delete when is two children
    TreeNode *searchIDHelper(TreeNode* root, int id);  // Helper method to search for specific ID
    void searchNameHelper(TreeNode *root, std::vector<int> &namesVector, std::string &name);  // Helper method to search for specific name
    void printInorderHelper(TreeNode *root, std::vector<std::string> &names);  // Helper method to print inorder traversal
    void printPreorderHelper(TreeNode *root, std::vector<std::string> &names);  // Helper method to print preorder traversal
    void printPostorderHelper(TreeNode *root, std::vector<std::string> &names);  // Helper method to print postorder traversal
    void removeInorderNHelper(TreeNode *root, int &idVector, int &count, int targetN);  // Helper function to delete Nth node

public:
    // Constructor
    avl_tree() : rootNode(nullptr) {}

    // Destructor
    ~avl_tree() { rootNode = deleteTree(rootNode); }

    // Public Methods
    void insertNameID(int id, std::string &name);  // Add a Student object into the tree with the specified name, NAME and GatorID number, ID.
    void removeID(int id);  // Find and remove the account with the specified ID from the tree.
    void searchID(int id);  // Search for the student with the specified ID from the tree.
    void searchName(std::string name);  // Search for the student with the specified ID from the tree.
    void printInorder();  // Print out a comma separated inorder traversal of the names in the tree.
    void printPreorder();  // Print out a comma separated preorder traversal of the names in the tree.
    void printPostorder();  // Print out a comma separated postorder traversal of the names in the tree.
    void printLevelCount();  // Prints the number of levels that exist in the tree.
    void removeInorderN(int n);  // Remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc).
};
