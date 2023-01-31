#include "avl_tree.h"

// TODO: Helper methods
// Delete all the nodes from memory
avl_tree::TreeNode *avl_tree::deleteTree(TreeNode* root) {
    if(root == nullptr) return nullptr;
    else {
        deleteTree(root->left);  // Go to the left node
        deleteTree(root->right);  // Go to the right node
        delete root;  // Delete curr node
    }
    return nullptr;
}

// Insert function | Helper method
avl_tree::TreeNode *avl_tree::insertHelper(TreeNode *root, int id, std::string name) {
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
avl_tree::TreeNode *avl_tree::inorderSuccessor(TreeNode *root) {
    // The tree is empty
    if (root == nullptr) return nullptr;

    // Keep going left until left is null
    if (root->left != nullptr) return inorderSuccessor(root->left);
    else return root;
}

// Helper function to find the parent node
avl_tree::TreeNode *avl_tree::getParentNode(TreeNode *root, int id) {
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
avl_tree::TreeNode *avl_tree::removeIDHelper(TreeNode *root, int id) {
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
avl_tree::TreeNode *avl_tree::searchIDHelper(TreeNode* root, int id) {
    // Empty node
    if (root == nullptr) return nullptr;

    if (root->gatorID == id) return root;  // We found the id
    else if (id < root->gatorID) root = searchIDHelper(root->left, id);  // We got to the left
    else root = searchIDHelper(root->right, id);  // We go to the right

    return root;
}

// Helper method to search for specific name
void avl_tree::searchNameHelper(TreeNode *root, std::vector<int> &idsVector, std::string &name) {
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
void avl_tree::printInorderHelper(TreeNode *root, std::vector<std::string> &names) {
    if (root == nullptr) return;

    // LEFT - ROOT - RIGHT
    printInorderHelper(root->left, names);
    names.push_back(root->fullName);
    printInorderHelper(root->right, names);
}

// Helper method print preorder traversal
void avl_tree::printPreorderHelper(TreeNode *root, std::vector<std::string> &names) {
    if (root == nullptr) return;

    // ROOT - LEFT - RIGHT
    names.push_back(root->fullName);
    printPreorderHelper(root->left, names);
    printPreorderHelper(root->right, names);
}

// Helper method print postorder traversal
void avl_tree::printPostorderHelper(TreeNode *root, std::vector<std::string> &names) {
    if (root == nullptr) return;

    // LEFT - RIGHT - ROOT
    printPostorderHelper(root->left, names);
    printPostorderHelper(root->right, names);
    names.push_back(root->fullName);
}

// Helper function to delete Nth node
void avl_tree::removeInorderNHelper(TreeNode *root, int &getId, int &count, int targetN) {
    if (root == nullptr) return;

    // Move left
    removeInorderNHelper(root->left, getId, count, targetN);
    // Find the node to delete
    if (count++ == targetN) getId = root->gatorID;

    // Move right
    removeInorderNHelper(root->right, getId, count, targetN);
}

// Get node balance | height(node->left) - height(node->right)
int avl_tree::getBalance(TreeNode *node) { return node->getHeight(node->left) - node->getHeight(node->right); }

// Left rotation
avl_tree::TreeNode *avl_tree::leftRotation(TreeNode *root) {
    TreeNode *grandChild = root->right->left;
    TreeNode *newParent = root->right;
    newParent->left = root;
    root->right = grandChild;

    return newParent;
}

// Right rotation
avl_tree::TreeNode *avl_tree::rightRotation(TreeNode *root) {
    TreeNode *grandChild = root->left->right;
    TreeNode *newParent = root->left;
    newParent->right = root;
    root->left = grandChild;

    return newParent;
}


// TODO: Methods
// Insert name & ID into tree
void avl_tree::insertNameID(int id, std::string &name) {
    if (searchIDHelper(rootNode, id) == nullptr) {
        rootNode = insertHelper(rootNode, id, name);
        std::cout << name << " was successfully added to the tree" << std::endl;
    } else {
        std::cout << "unsuccessful insertion" << std::endl;
    }
}

// Search user by ID
void avl_tree::searchID(int id) {
    TreeNode *idSearched = searchIDHelper(rootNode, id);

    if (idSearched == nullptr) std::cout << "unsuccessful search by ID" << std::endl;
    else std::cout << idSearched->fullName << std::endl;
}

// Search for the student with the specified ID from the tree.
void avl_tree::searchName(std::string name) {
    std::vector<int> ids;
    searchNameHelper(rootNode, ids, name);
    if (ids.empty()) std::cout << "unsuccessful search by name" << std::endl;
}

// Find and remove the account with the specified ID from the tree.
void avl_tree::removeID(int id) {
    rootNode = removeIDHelper(rootNode, id);
    if (rootNode != nullptr)
        std::cout << "Student with id: " << id << " was successfully removed from the tree." << std::endl;
}

// Remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc).
void avl_tree::removeInorderN(int n) {
    int count = 0;
    int nodeID = 1000000;
    removeInorderNHelper(rootNode, nodeID, count, n);
    rootNode = removeIDHelper(rootNode, nodeID);
    if (rootNode != nullptr)
        std::cout << "Student at location " << n << " was: " << rootNode->fullName << " and it was successfully removed from the tree." << std::endl;
}

// Print out a comma separated inorder traversal of the names in the tree.
void avl_tree::printInorder() {
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
void avl_tree::printPreorder() {
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
void avl_tree::printPostorder() {
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
void avl_tree::printLevelCount() {
    if (rootNode == nullptr) std::cout << 0 << std::endl;
    else std::cout << rootNode->getHeight(rootNode) + 1 << std::endl;
}
