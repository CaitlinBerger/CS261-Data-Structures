Assignment #4

Files: link

Deviation from these guidelines will result in a zero score. No exceptions

Code must compile using the provided makefile without error
Do not change the function signatures (i.e., void fooB(int k))
Do not add or remove files.
Submission of all files is to be in a single ZIP (not tar, gz, etc.) archive containing only the files specified.
Part I

In the files bst.h and bst.c, a binary search tree implementation is given. Note that the value of each BST node is a pointer to the following struct found in structs.h

struct data {
    int number;
    char *name;
};
You are to complete the following functions

struct data * findNode(struct Node *tree, int val)
int countNodes(struct Node *tree)
int secondLargestNode(struct Node *tree)
void flattenPreorder(struct Node *tree, struct cirListDeque * d)
void flattenPostorder(struct Node *tree, struct cirListDeque * d)
void flattenInorder(struct Node *tree, struct cirListDeque * d)
Desciptions for each function are provided in the comments of the bst.c file.

In the latter three functions, you can expect that d will be an initialized deque containing no items. You are required to add struct * data pointers to the end of deque as you traverse the tree. For example, the BST t:

         4
        / \
       1   8
          /
         5    
called with flattenInorder(t,d) (where d is an empty deque) would return with deque d containing struct data* pointers with the following number values in the order below

1 <-> 4 <-> 5 <-> 8
The call flattenPostorder(t,d) would return with deque d containing struct data* pointers with the following number values in the order below

1 <-> 5 <-> 8 <-> 4
You can test your code using testBST.c.
