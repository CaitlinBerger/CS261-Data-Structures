/*
   File: bst.c
    Implementation of the binary search tree data structure.

*/
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "bst.h"



/*
   function to initialize the binary search tree.
    param tree
     pre: tree is not null
     post:tree size is 0
     root is null
*/
void initBSTree(struct BSTree *tree)
{

  tree->root = 0;
}

/*
    function to create a binary search tree.
      param: none
        pre: none
	  post: tree->count = 0
	  tree->root = 0;
*/


struct BSTree*  newBSTree()
{
  struct BSTree *tree = (struct BSTree *)malloc(sizeof(struct BSTree));
  assert(tree != 0);

  initBSTree(tree);
  return tree;
}

/*----------------------------------------------------------------------------*/
/*
  function to free the nodes of a binary search tree
  param: node  the root node of the tree to be freed
   pre: none
    post: node and all descendants are deallocated
*/
void _freeBST(struct Node *node)
{
  if (node != 0) {
    _freeBST(node->left);
    _freeBST(node->right);
    free(node);
  }
}

/*
   function to clear the nodes of a binary search tree
    param: tree    a binary search tree
     pre: tree ! = null
      post: the nodes of the tree are deallocated
      tree->root = 0;
      tree->cnt = 0
*/
void clearBSTree(struct BSTree *tree)
{
  _freeBST(tree->root);
  tree->root = 0;

}

/*
   function to deallocate a dynamically allocated binary search tree
    param: tree   the binary search tree
     pre: tree != null;
      post: all nodes and the tree structure itself are deallocated.
*/

void deleteBSTree(struct BSTree *tree)
{
  clearBSTree(tree);
  free(tree);
}


/*----------------------------------------------------------------------------*/
/*
   function to determine if  a binary search tree is empty.

    param: tree    the binary search tree
     pre:  tree is not null
*/
int isEmptyBSTree(struct BSTree *tree) { return tree == 0; }



/*----------------------------------------------------------------------------*/
/*
   recursive helper function to add a node to the binary search tree.
    HINT: You have to use the compare() function to compare values.
    param:  curthe current root node
    valthe value to be added to the binary search tree
    pre:val is not null
*/
struct Node *_addNode(struct Node *cur, BST_DATA_TYPE val)
{

  struct Node *newnode;
  /* case1 - cur is null */
  if (cur == NULL)
    {/*create new node and return*/
      newnode = (struct Node *)malloc(sizeof(struct Node));
      assert(newnode != 0);
      newnode->val = val;
      newnode->left = newnode->right = 0;
      return newnode;
    }
  if (compare(val,cur->val) == -1)
    cur->left = _addNode(cur->left,val);
  else if (compare(val, cur->val) == 1)
    cur->right = _addNode(cur->right, val);
  return cur;
}

/*
   function to add a value to the binary search tree
    param: tree   the binary search tree
    valthe value to be added to the tree

    pre:tree is not null
    val is not null
     pose:  tree size increased by 1
     tree now contains the value, val
*/

void addBSTree(struct BSTree *tree, BST_DATA_TYPE val)
{
  tree->root = _addNode(tree->root, val);

}

/*
   function to determine if the binary search tree contains a particular element
    HINT: You have to use the compare() function to compare values.
    param:treethe binary search tree
    valthe value to search for in the tree
    pre:tree is not null
    val is not null
    post:none
*/


int containsBSTree(struct BSTree *tree, BST_DATA_TYPE val)
{

  struct Node *cur = tree->root;

  while (cur != 0) {
    if (compare(val,cur->val) == 0)
      return 1; /* Return true if val found. */
    if (compare(val, cur->val) == -1)
      cur = cur->left; /* Otherwise, go to the left */
    else cur = cur->right; /* or right, depending on val. */
  }
  return 0;


}

/*
    helper function to find the left most child of a node
      return the value of the left most child of cur
      param: curthe current node
      pre:cur is not null
        post: none
*/
BST_DATA_TYPE _leftMost(struct Node *cur)
{

  while (cur->left != 0)
    cur = cur->left;
  return cur->val;

}

/*
    recursive helper function to remove the left most child of a node
      HINT: this function returns cur if its left child is NOT NULL. Otherwise,
        it returns the right child of cur and free cur.

	 Note:  If you do this iteratively, the above hint does not apply.

	 param: curthe current node
	 pre:cur is not null
	 post:the left most node of cur is not in the tree
*/
struct Node *_removeLeftMost(struct Node *cur)
{


  struct Node *node;

  if (cur->left != 0) {
    cur->left = _removeLeftMost(cur->left);
    return cur;
  }

  node = cur->right;
  free(cur);
  return node;
}

/*
    recursive helper function to remove a node from the tree
      HINT: You have to use the compare() function to compare values.
      param:curthe current node
      valthe value to be removed from the tree
      pre:val is in the tree
      cur is not null
      val is not null
*/
struct Node *_removeNode(struct Node *cur, BST_DATA_TYPE val)
{

  struct Node *temp;
  if (compare(val, cur->val) == 0) { /* Found val. */
    if (cur->right == 0) {
      temp = cur->left;
      free(cur);
      return temp;
    }
    cur->val = _leftMost(cur->right);
    cur->right = _removeLeftMost(cur->right);
  }
  else if (compare(val, cur->val) == -1)
    cur->left = _removeNode(cur->left, val);
  else
    cur->right = _removeNode(cur->right,val);
  return cur;
}
/*
    function to remove a value from the binary search tree
      param: tree   the binary search tree
      valthe value to be removed from the tree
      pre:tree is not null
      val is not null
      val is in the tree
      pose:tree size is reduced by 1
*/
void removeBSTree(struct BSTree *tree, BST_DATA_TYPE val)
{
  if (containsBSTree(tree, val)) {
    tree->root = _removeNode(tree->root, val);
  }
}

/*
    Function to find a data struct with "number" equal to val, and return it.
      param: tree the binary search tree
        val the value to be found
      pre: the tree and value are not null
      post: the data struct containing the value is returned
*/
struct data * findNode(struct Node *tree, int val)
{
  struct Node * cur = tree;

  while (cur != NULL) {
    if (val == cur->val->number) {
      /* If the value  is found, return the current node */
      return cur->val;
    } else if (val < cur->val->number) {
      /* If val is less than cur, go left */
      cur = cur->left;
    } else {
      /* Otherwise, val is greater than cur, go right */
      cur = cur->right;
    }
  }

  /* if no nodes are found containing value, return NULL */
  return NULL;
}
/*
    Function to recursively count the number of nodes in the tree
      param: tree the binary search tree
      pre: the tree is not null
      post: returns the number of nodes present including the initial node
*/
int countNodes(struct Node *tree)
{
<<<<<<< HEAD
=======
  /*  Returns the number of nodes present in tree including tree
      itself */
  int count;
>>>>>>> origin/master
  if (tree != NULL) {
    count = 1; /* Count initialized to one (for the current node)*/
    count += countNodes(tree->left);
    count += countNodes(tree->right);
  }

  return count;
}

/*
    Function to return the secodn largest "number" found in the tree
      param: root node of the tree to be searched, with values greaer than 0
      pre: the tree is not null
      post: returns the second largest number. Returns -1 if the tree contains
        less than 2 nodes
*/
int secondLargestNode(struct Node *tree){
  struct Node *cur = tree;
  struct Node *next;

  if (cur->right != NULL) {
    while (next->right != NULL) {
      //while there is still a right node, increment current and next one to the right
      cur = next;
      next = next->right;
    }
    //return cur's value as the second largest value
    reutrn cur->val->number;
  } else if (cur->left) {
    //if there is a left tree, find the right most node and reutrn it's "number"
    while (cur->right != NULL)
      cur = cur->right;
    return cur->val->number;
  } else {
    //otherwise, there is only one node, reutrn -1
    return -1;
  }
}

/*
    Function to perform a preorder traversal of a tree, and appends nodes in the
        order of the traversal to the deque
      param: tree the binary search tree's root node
        d the cirListDeque
      pre: the tree is not null, d is a new empty deque
      post: the deque will be full of preordered values from the tree
*/
void  flattenPreorder(struct Node *tree, struct cirListDeque * d){
  if (tree != NULL){
    addBackCirListDeque(d, tree->val); //append current value to the deque
    flattenPreorder(tree->left, d); //process left sub-tree
    flattenPreorder(tree->right, d); //process right sub-tree
  }
  return;
}

/*
    Function to perform a postorder traversal of a tree, and appends nodes in
        the order of the traversal to the deque
      param: tree the binary search tree's root node
        d the cirListDeque
      pre: the tree is not null, d is a new empty deque
      post: the deque will be full of preordered values from the tree
*/
void  flattenPostorder(struct Node *tree,struct cirListDeque * d){
  if (tree != NULL) {
    flattenPreorder(tree->left, d); //process left sub-tree
    flattenPreorder(tree->right, d); //process right sub-tree
    addBackCirListDeque(d, tree->val); //append current value to the deque
  }


  return;
}

/*
    Function to perform an inorder traversal of a tree, and appends nodes in
        the order of the traversal to the deque
      param: tree the binary search tree's root node
        d the cirListDeque
      pre: the tree is not null, d is a new empty deque
      post: the deque will be full of preordered values from the tree
*/
void  flattenInorder(struct Node *tree,struct cirListDeque * d){

  if (tree != NULL) {
    flattenPreorder(tree->left, d); //process left sub-tree
    addBackCirListDeque(d, tree->val); //append current value to the deque
    flattenPreorder(tree->right, d); //process right sub-tree
  }

  return;
}
/*----------------------------------------------------------------------------*/

/* The following is used only for debugging, set to "#if 0" when used
   in other applications */
#if 1
#include <stdio.h>

/*----------------------------------------------------------------------------*/
void printNode(struct Node *cur) {
  if (cur == 0) return;
  printf("(");
  printNode(cur->left);
  /*Call print_type which prints the value of the BST_DATA_TYPE*/
  print_type(cur->val);
  printNode(cur->right);
  printf(")");
}

void printTree(struct BSTree *tree) {
  if (tree == 0) return;
  printNode(tree->root);
}
/*----------------------------------------------------------------------------*/

#endif
