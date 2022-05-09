//
// Created by Javier Arango on 2/11/22.
//

#pragma once

#include <iostream>
#include <vector>


// AVL Tree
class AVLTree {
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
    AVLTree() : rootNode(nullptr) {}

    // Destructor
    ~AVLTree() { rootNode = deleteTree(rootNode); }

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

// TODO: Helper methods
// Delete all the nodes from memory
AVLTree::TreeNode *AVLTree::deleteTree(TreeNode* root) {
    if(root == nullptr) return nullptr;
    else {
        deleteTree(root->left);  // Go to the left node
        deleteTree(root->right);  // Go to the right node
        delete root;  // Delete curr node
    }
    return nullptr;
}

// Insert function | Helper method
AVLTree::TreeNode *AVLTree::insertHelper(TreeNode *root, int id, std::string name) {
    // Create new node if root is empty
    if (root == nullptr) { root = new TreeNode(id, name); }

    // Insert value in left node else insert it in right node
    else if (id < root->gatorID) root->left = insertHelper(root->left, id, name);
    else root->right = insertHelper(root->right, id, name);

    // Update node height
    //root->height = root->getHeight(root);
    // Get node balance
    int balance = getBalance(root);

    // Left-Left Case or Left-Right Case
    if (balance > 1) {
        if (getBalance(root->left) < 0) root = leftRotation(root->left);  // Left-Right Case | Left Right Rotation
        return rightRotation(root);  // Right Rotation
    }
    // Right-Right or Right-left Case
    else if (balance < -1) {
        if (getBalance(root->right) > 0) root->right = rightRotation(root->right);  // Right-Left Case | Right Left Rotation
        return leftRotation(root);  // Left Rotation
    }

    // Return head
    return root;
}

// Find the in order successor to delete when is two children
AVLTree::TreeNode *AVLTree::inorderSuccessor(TreeNode *root) {
    // The tree is empty
    if (root == nullptr) return nullptr;

    // Keep going left until left is null
    if (root->left != nullptr) return inorderSuccessor(root->left);
    else return root;
}

// Helper function to find the parent node
AVLTree::TreeNode *AVLTree::getParentNode(TreeNode *root, int id) {
    // Empty tree
    if (root == nullptr) return nullptr;

    // Parent node
    TreeNode *parent = nullptr;

    if (root->gatorID == id) return root;
    else {
        while (root != nullptr) {
            // Go to the left nodes
            if (id < root->gatorID) {
                parent = root;
                root = root->left;
            }
            // Go to the right nodes
            else if (root->gatorID < id) {
                parent = root;
                root = root->right;
            }
            // break bc we found the parent already, and I don't need the child
            else break;
        }
    }

    // Return parent
    return parent;
}

// Helper method to remove ID
AVLTree::TreeNode *AVLTree::removeIDHelper(TreeNode *root, int id) {
    // Search id and parent of the ID node
    TreeNode *parent = getParentNode(root, id);  // Find parent
    TreeNode *curr = searchIDHelper(root, id);  // Find the node to remove

    // The id was not found
    if (curr == nullptr || parent == nullptr) {
        std::cout << "unsuccessful" << std::endl;
        return root;
    }

    // Case 1 | Node to remove have Not Children
    if (curr->left == nullptr && curr->right == nullptr) {
        if (curr != root) {
            if (parent->left == curr) parent->left = nullptr;
            else parent->right = nullptr;
        }
        // Delete the root
        else root = nullptr;

        // TODO: Free Memory
        free(curr);
    }
    // Case 2 | Node to remove have One Child
    else if (curr->left == nullptr || curr->right == nullptr) {
        // Child node
        TreeNode *child = (curr->right != nullptr ? curr->right : curr->left);

        if (curr != root) {
            if (parent->left == curr) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }
        // Delete the root
        else root = child;

        // TODO: Free Memory
        free(curr);
    }

    // Case 3 | Node to remove have Two Children
    else {
        // Inorder successor
        TreeNode *successor = inorderSuccessor(curr->right);

        // Swap values
        curr->gatorID = successor->gatorID;
        curr->fullName = successor->fullName;
        curr->height = successor->height;

        // Delete successor
        root->right = removeIDHelper(root->right, successor->gatorID);
    }

    return root;
}

// Search for specific ID | Helper method
AVLTree::TreeNode *AVLTree::searchIDHelper(TreeNode* root, int id) {
    // Empty node
    if (root == nullptr) return nullptr;

    if (root->gatorID == id) return root;  // We found the id
    else if (id < root->gatorID) root = searchIDHelper(root->left, id);  // We got to the left
    else root = searchIDHelper(root->right, id);  // We go to the right

    return root;
}

// Helper method to search for specific name
void AVLTree::searchNameHelper(TreeNode *root, std::vector<int> &idsVector, std::string &name) {
    if (root == nullptr) return;

    // ROOT
    if (root->fullName == name) {
        idsVector.push_back(root->gatorID);
        std::cout << root->gatorID << std::endl;
    }
    // LEFT - RIGHT
    searchNameHelper(root->left, idsVector, name);
    searchNameHelper(root->right, idsVector, name);
}

// Helper method print inorder traversal
void AVLTree::printInorderHelper(TreeNode *root, std::vector<std::string> &names) {
    if (root == nullptr) return;

    // LEFT - ROOT - RIGHT
    printInorderHelper(root->left, names);
    names.push_back(root->fullName);
    printInorderHelper(root->right, names);
}

// Helper method print preorder traversal
void AVLTree::printPreorderHelper(TreeNode *root, std::vector<std::string> &names) {
    if (root == nullptr) return;

    // ROOT - LEFT - RIGHT
    names.push_back(root->fullName);
    printPreorderHelper(root->left, names);
    printPreorderHelper(root->right, names);
}

// Helper method print postorder traversal
void AVLTree::printPostorderHelper(TreeNode *root, std::vector<std::string> &names) {
    if (root == nullptr) return;

    // LEFT - RIGHT - ROOT
    printPostorderHelper(root->left, names);
    printPostorderHelper(root->right, names);
    names.push_back(root->fullName);
}

// Helper function to delete Nth node
void AVLTree::removeInorderNHelper(TreeNode *root, int &getId, int &count, int targetN) {
    if (root == nullptr) return;

    // Move left
    removeInorderNHelper(root->left, getId, count, targetN);
    // Find the node to delete
    if (count++ == targetN) getId = root->gatorID;

    // Move right
    removeInorderNHelper(root->right, getId, count, targetN);
}

// Get node balance | height(node->left) - height(node->right)
int AVLTree::getBalance(TreeNode *node) { return node->getHeight(node->left) - node->getHeight(node->right); }

// Left rotation
AVLTree::TreeNode *AVLTree::leftRotation(TreeNode *root) {
    TreeNode *grandChild = root->right->left;
    TreeNode *newParent = root->right;
    newParent->left = root;
    root->right = grandChild;

    return newParent;
}

// Right rotation
AVLTree::TreeNode *AVLTree::rightRotation(TreeNode *root) {
    TreeNode *grandChild = root->left->right;
    TreeNode *newParent = root->left;
    newParent->right = root;
    root->left = grandChild;

    return newParent;
}


// TODO: Normal Methods
// Insert name & ID into tree
void AVLTree::insertNameID(int id, std::string &name) {
    if (searchIDHelper(rootNode, id) == nullptr) {
        rootNode = insertHelper(rootNode, id, name);
        std::cout << "successful" << std::endl;
    } else {
        std::cout << "unsuccessful" << std::endl;
    }
}

// Search user by ID
void AVLTree::searchID(int id) {
    TreeNode *idSearched = searchIDHelper(rootNode, id);

    if (idSearched == nullptr) std::cout << "unsuccessful" << std::endl;
    else std::cout << idSearched->fullName << std::endl;
}

// Search for the student with the specified ID from the tree.
void AVLTree::searchName(std::string name) {
    std::vector<int> ids;
    searchNameHelper(rootNode, ids, name);
    if (ids.empty()) std::cout << "unsuccessful" << std::endl;
}

// Find and remove the account with the specified ID from the tree.
void AVLTree::removeID(int id) {
    rootNode = removeIDHelper(rootNode, id);
    if (rootNode != nullptr) std::cout << "successful" << std::endl;
}

// Print out a comma separated inorder traversal of the names in the tree.
void AVLTree::printInorder() {
    if (rootNode == nullptr) return;
    else {
        std::vector<std::string> names;
        printInorderHelper(rootNode, names);

        for (int i = 0; i < names.size(); i++) {
            if (i == names.size()-1) std::cout << names[i];
            else std::cout << names[i] << ", ";
        }
        std::cout << std::endl;
    }
}

// Print out a comma separated preorder traversal of the names in the tree.
void AVLTree::printPreorder() {
    if (rootNode == nullptr) return;
    else {
        std::vector<std::string> names;
        printPreorderHelper(rootNode, names);

        for (int i = 0; i < names.size(); i++) {
            if (i == names.size()-1) std::cout << names[i];
            else std::cout << names[i] << ", ";
        }
        std::cout << std::endl;
    }
}

// Print out a comma separated postorder traversal of the names in the tree.
void AVLTree::printPostorder() {
    if (rootNode == nullptr) return;
    else {
        std::vector<std::string> names;
        printPostorderHelper(rootNode, names);

        for (int i = 0; i < names.size(); i++) {
            if (i == names.size()-1) std::cout << names[i];
            else std::cout << names[i] << ", ";
        }
        std::cout << std::endl;
    }
}

// Prints the number of levels that exist in the tree.
void AVLTree::printLevelCount() {
    if (rootNode == nullptr) std::cout << 0 << std::endl;
    else std::cout << rootNode->getHeight(rootNode) + 1 << std::endl;
}

// Remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc).
void AVLTree::removeInorderN(int n) {
    int count = 0;
    int nodeID = 1000000;
    removeInorderNHelper(rootNode, nodeID, count, n);
    rootNode = removeIDHelper(rootNode, nodeID);
    if (rootNode != nullptr) std::cout << "successful" << std::endl;
}
