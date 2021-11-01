/********************************************************************
	File: BST.h
	Des:  This file contains the class definition for a Binary Search
	Tree (A)bstract (D)ata (T)ype.  It also contains information on
	the type of data being stored in the tree and identifiers to
	be used with this ADT.


	Author: Josue Santos
********************************************************************/
#include <fstream>
using namespace std;

//Max size of a BstType
#define BstTypeLength 30

//A BstType is a 30 character array
typedef char BSTtype[BstTypeLength];

//The Bst will consist of BSTnodes
struct BSTnode;

//A BSTptr will a pointer to a BSTnode
typedef BSTnode *BSTptr;

//A BSTnode will consist of a word, frequency and left and right
//pointers
struct BSTnode
{
	BSTtype word;
	int freq;
	BSTptr lt, rt;
};

//Class definition for a Binary Search Tree
class BST
{
public:

	//constructor
	BST();

	//destructor
	~BST();

	//add a node to the BST
	bool BSTadd(BSTtype data);

	//delete a node from the BST
	bool BSTdelete(BSTtype);

	//determine if a node exists in BST
	bool BSTexists(BSTtype);

	//increment the freq of a node in BST
	void BSTinc(BSTtype);

	//print out a partial word list
	void BSTprint(char, ostream&);

	//print out the entire list
	void BSTprint(ostream&);

	//get height of tree
	int getBSTHeight();

	//get node count
	int getBSTNodeCount();


private:
	//NOTE: These functions do not have to be implemented in order for your code
	//to compile.  I used these to support some of my public functions
	//deletion of entire tree - used by destructor
	void BSTdeletetree(BSTptr);

	//partial inorder traversal  of BST - used by it's corresponding BSTprint
	//function
	void BSTinorderPartial(BSTptr, char, ostream&);

	//complete inorder traversal of BST - used by it's corresponding BSTprint
	//function
	void BSTinorder(BSTptr, ostream&);
	//Function to Delete Leaf Case
	void BSTDeleteLeaf(BSTptr&, BSTptr);
	//Function to delete a One Way Case
	void BSTDeleteOneWay(BSTptr&, BSTptr);
	//Function to delete a Two Way Case
	void BSTDeleteTwoWay(BSTptr&);
	//function to return pointer
	BSTptr BSTfindPtr(BSTptr&, BSTtype);
	//function to return a parent pointer
	BSTptr BSTfindParent(BSTptr, BSTptr);
	//Functions to help us find the height
	int maxHeight(BSTptr);
	BSTptr recurRight(BSTptr);
	//member variables to store root of BST, it's height and how many nodes
	//are in the BST
	BSTptr root;
	int height;
	int nodeCount;
};
