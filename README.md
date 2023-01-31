# Custom AVL Tree
> This project was made for the Data Structure and Algorithms class (It might contain small errors in the code)

Binary Search Trees (BST) can often be an efficient and useful way to store and retrieve sorted data. However, the efficiency of these data trees relies heavily on how balanced a BST is. For example, searching through the BST on the left is much more efficient than searching through the BST on the right, despite both figures showing valid BST with the exact same elements.

To avoid inefficient binary search trees, we use balanced Binary Search Trees. A balanced BST has a balance factor of less than ±threshold, where the balance factor is the difference in heights of the left and right subtrees at any given tree node. One such balanced tree is an AVL tree that maintains a threshold of 1. As soon as a node in an AVL tree has a balance factor of +2/-2, “tree rotations” are performed to maintain balance in the tree.

## Methods build in the AVL Tree:
| Method          | Description |
|-----------------| ----------- |
| insert          | Add a Student object into the tree with the specified name, number ID. The ID must be unique. |
| remove          | Find and remove the account with the specified ID from the tree. |
| removeInorder   | Remove the Nth ID from the inorder traversal of the tree (N = 0 for the first item, etc). |
| search          | Search for the student with the specified ID or name from the tree. |
| printInorder    | Print the tree using inOrder traversal. |
| printPreorder   | Print the tree using preOrder traversal. |
| printPostorder  | Print the tree using postOrder traversal. |
| printLevelCount | Print the tree using levelOrder traversal. |

## Source folder
- `src`: contains all the code
  - `AVLTree` is where all the code for tree is located
    - `AVLTree.h` is the definition of the AVL tree
    - `AVLTree.cpp` is the implementation of the AVL tree
  - `examples` contains two use cases of the AVL tree (both files have the main function, you would have to comment one, so you would be able to run the other one)
    - `useCaseOne.cpp` contains a use case of the AVL tree using the terminal (a menu shows and asking user for inputs)
    - `useCaseTwo.cpp` contains a use case of the AVL tree using the function calling from the tree (simple use example)
  
## Example User Input
> 8 \
> insert "Brandon" 45679999 \
> insert "Brian" 35459999 \
> insert "Briana" 87879999 \
> insert "Bella" 95469999 \
> printInorder \
> remove 45679999 \
> removeInorder 2 \
> printInorder

## Example Output Result
> successful \
> successful \
> successful \
> successful \
> Brian, Brandon, Briana, Bella \
> successful \
> successful \
> Brian, Briana
