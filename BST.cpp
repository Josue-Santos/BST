#include "BST.h"
#include <iostream>
#include<iomanip>
using namespace std;

/******************************************************************************
Name: BST.cpp
Des: BST.cpp is the implementation file of wordcnt.cpp that contains the code
to implement the function descriptions of the header file (BST.h). This implementation
file will show the code for the Constructor and a Destructor. Then it will contain 
the code for nine public functions followed by 11 private functions that will 
make this program work.Before each function you will find a description of what 
the function is doing. This programs gets a text file, reads in each word of the text file
and adds it to a BST, if the word is repeated we just add one to the frequency of the 
word. If it is not, we add it to the tree. Once the tree is built the program asks
the user to insert a letter for the program to display all the words that start with
that letter, then the user can delete a word, the process will keep happening until
the user stops it. The program display the list of words in a separate text file named
after the name of the first textfile. The extension of the new textfile is .frq. 
Author: Josue Santos
******************************************************************************/

//Constructor
BST::BST(){

	root = nullptr;
}

//Destructor
BST::~BST() {
	BSTdeletetree(root);
}

/*************************************************************************************************
This is the bool BSTadd Function which will accept a BST type parameter (a char array)
and will add each word to our BST. If the word is not in the list we add it to the tree, if it is 
we add one to its frequency. This function handles every single word it is given and finds
the right place in the tree before insertion. Also at the end of the function we add one to nodecount
to keep track of the number of nodes we have in the BST.
**************************************************************************************************/
bool BST::BSTadd(BSTtype data) {
	//get dynamic memory, if unable return message to client
	BSTptr newnode = new BSTnode;
	if (newnode == nullptr)
		return false;
	//initialize node with information to place in tree
	strcpy_s(newnode->word, data);
	newnode->lt = newnode->rt = nullptr;
	newnode->freq = 1;
	//insert node in tree, if tree empty this becomes the root
	if (root == nullptr)
		root = newnode;
	
	else
	{
		//tree not empty, find insertion point and insert as leaf
		BSTptr current = root;
		BSTptr parent = current;
		//find insertion spot, parent will point to insertion node
		while (current != nullptr)
		{
			parent = current;
			//condition to see if the new word is lesser than the current one
			//if it is we add it to the left
			if(strcmp(data, current->word) < 0)
				current = current->lt;
			//if it is greater it is added at the right branch of the tree
			else
				current = current->rt;
		}
		//graft node onto parent

		if (strcmp(data, parent->word) < 0) {
			parent->lt = newnode;
		}
		else {
			parent->rt = newnode;
		}
	}
	//To keep track of the nodes.
	nodeCount++;
	return true;
	
}
//delete a node from the BST
/*************************************************************************************************
This is the bool BSTdelete Function which will accept a BST type  parameter (a char array)
and will delete that word from our BST. If the word is not found on our tree we return false. If it
found we check which case of deletion will happen. First we check if thats the only node in the tree.
If it is then we just delete the current node and set the root to null and return true. If that is not
the case we looked for the other three cases and get into the functions to handle those cases.
**************************************************************************************************/

bool BST::BSTdelete(BSTtype word) {
	BSTptr current= nullptr, parent= nullptr;
	if (BSTexists(word) == false) {
		return false;
	}
	//Find a WAY TO GET A POINTER THAT POINTS TO CURRENT and Parent
	current=BSTfindPtr(current, word);
	
	parent = BSTfindParent(current, parent);
	//Special case when there is only one node in the tree
	if (nodeCount == 1 || nodeCount==0) {
		delete current;
		root = NULL;
		return true;
	}
	/**************************************************************************/
	//Leaf Case
	if (current->lt == nullptr && current->rt == nullptr) {
		BSTDeleteLeaf(current, parent);
		
		return true;
	}
	/*************************************************************************/
	//One way Case
	if ((current->lt == nullptr && current->rt != nullptr) ||
		(current->lt != nullptr && current->rt == nullptr)) {
		BSTDeleteOneWay(current, parent);
		return true;
	}
	/**************************************************************************/
	//Two Cases
	if ((current->lt != nullptr && current->rt != nullptr)){
		BSTDeleteTwoWay(current/*, parent*/);
		return true;
	}
	else {
		return false;
	}

}

/*************************************************************************************************
This is the bool BSTexist Function which will accept a BST type parameter (a char array)
and will search word to our BST. If the word is not found we return false, else we return true.

**************************************************************************************************/
bool BST::BSTexists(BSTtype word) {
	bool found = false;
	BSTptr current = root;
	while (current != nullptr)
	{
		//Condition to test if the node we are inserting was a previous
		//inserted word, if that is the case we add one to the frequency of
		//the word.
		if (strcmp(word, current->word) == 0) {
			found = true;
			
		}
		//condition to see if the new word is lesser than the current one
		//if it is we add it to the left
		if (strcmp(word, current->word) < 0)
			current = current->lt;
		//if it is greater it is added at the right branch of the tree
		else
			current = current->rt;
	}
	
	return found;

}

/*************************************************************************************************
This is the bool BSTinc function that will accept a BST type parameter (a char array)
and will increment the node count if the word already exists.
**************************************************************************************************/
void BST::BSTinc(BSTtype word) {
	BSTptr temp = root;
	BSTptr current=nullptr;
	current= BSTfindPtr(temp, word);
	current->freq++;
}


/*************************************************************************************************
This function its called BST print which will help us print out all the word starting with a 
specific letter. There is another function called BSTinorderPartial that will help it with this 
assigment.
**************************************************************************************************/
void BST::BSTprint(char letter, ostream& file) {
	// Doing and in Order Traversal to print values of node
	//In Order Traversal
	BSTptr temp = root;
	BSTinorderPartial(temp, letter, file);
	

}

/*************************************************************************************************
This is the BSTprint function that will print the entire list in our .frq file
**************************************************************************************************/
void BST::BSTprint(ostream& fout){
	BSTptr temp = root;
	BSTinorder(temp, fout);
}

/*************************************************************************************************
This is the getBSTheight function that with help of the maxHeight function will give us 
the height of our BST.
**************************************************************************************************/
int BST::getBSTHeight() {
	
	BSTptr temp = root;
	return maxHeight(temp);
	
}

/*************************************************************************************************
This is the getBSTNodeCount function which will return the NodeCount of our BST
**************************************************************************************************/
int BST::getBSTNodeCount() {
	return nodeCount;
}

/*************************************************************************************************
This the BST deletetree function that will help the destructor delete every Node in our BST
after the execution of the program. This function uses a POST order traversal to delete each node.
**************************************************************************************************/
void BST::BSTdeletetree(BSTptr temp)
{
	//Post Order traversal
	if (temp == nullptr) return;
	
	//first recur on left subtree
	BSTdeletetree(temp->lt);
	//then recur on right subtree
	BSTdeletetree(temp->rt);
	//Now delete the node
	delete temp;
	
}

/*************************************************************************************************
This is the BSTinorderPartial function which will help outputting the list of words that start
with an specific letter.
**************************************************************************************************/

void BST::BSTinorderPartial(BSTptr temp, char letter, ostream & file)
{
	
	if (temp == nullptr)return;
	//first  recur to the left subtree
	
	BSTinorderPartial(temp->lt, letter, file);
	//then we print the data of the node
	//declare a variable that contains the first letter of temp->word
	//So that we can compare it to the letter we are searching for.
	char * word = temp->word;
	if (word[0] == letter) {
		cout << setw(20) << left << temp->word << "          " << setw(20) << left << temp->freq << endl;
	}
		
	//then we recur on the rigth subtree
	BSTinorderPartial(temp->rt, letter, file);
		
	return;
	
	
}

/*************************************************************************************************
This is the BSTinorder function that will help to print out the list of nodes left in our tree to the
.frq file.
**************************************************************************************************/
void BST::BSTinorder(BSTptr temp, ostream &file)
{
	//In Order Traversal
	if (temp == nullptr)return;
	//first  recur to the left subtree
	BSTinorder(temp->lt,file);
	//then we print the data of the node
	file << setw(20) << left << temp->word << "         " << setw(20) << left << temp->freq << endl;
	//then we recur on the rigth subtree
	BSTinorder(temp->rt,file);
	
}

//This function is to find the pointer to the Node we want to delete (current)
BSTptr BST::BSTfindPtr(BSTptr&temp, BSTtype word){
	
	BSTptr current = root;
	while (current != nullptr)
	{
		BSTptr parent = current;
		//Condition to test if the node we are inserting was a previous
		//inserted word, if that is the case we add one to the frequency of
		//the word.
		if (strcmp(word, parent->word) == 0) {
			current = parent;
			return current;
		}
		//condition to see if the new word is lesser than the current one
		//if it is we add it to the left
		if (strcmp(word, current->word) < 0)
			current = current->lt;
		//if it is greater it is added at the right branch of the tree
		else
			current = current->rt;
	}

	return current;

}
//This function is to find the pointer to the parent Node of the word we want to delete

BSTptr BST::BSTfindParent(BSTptr child, BSTptr parent) {
	bool found = false;
	BSTptr start = root;
	while (start != nullptr) {
		BSTptr Location = start;
		//We test if The Word is in the ROOT
		if (strcmp(child->word,Location->word) == 0) {
			parent = Location;
			return parent;
		}
		//We test if the Child Node is Located at the Left of the Parent Node
		if (Location->lt == child) {
			parent = Location;
			return parent;
		}
		//We test if the Child Node is Located at the Right of the Parent Node
		if (Location->rt == child) {
			parent = Location;
			return parent;
		}
		//condition to see if the new word is lesser than the current one
		//if it is we add it to the left
		if (Location->lt != NULL) {
			if(strcmp(child->word,Location->word)<0)
				start = start->lt;
			else
				start = start->rt;
		}
			
		//if it is greater it is added at the right branch of the tree
		else
			start = start->rt;
		
	}

}

//Function to Trim Tree, Leaf Case
void BST::BSTDeleteLeaf(BSTptr & P, BSTptr parent) {
	//check for root
	
	if (parent == nullptr) {
		root = nullptr;
		return;
	}
	else {
		if (parent->lt == P)
			parent->lt = nullptr;
		
		else
			parent->rt = nullptr;
	}
	
	delete P;
	//P = nullptr;
	return;
	
}
//Function to delete a One Way Case
void BST::BSTDeleteOneWay(BSTptr & current, BSTptr parent) {
	//First we have to check if the current Node has a left or right subtree
	//I will start checking if the left subtree is NULL, then the right subtree must exist
	if (current->lt == nullptr) 
	{

		//Checking for Root Case
		if (current == root)
		{
			root = root->rt;
			delete current;
			return;
		}


		//Reataching Subtree To Parent
		if (parent->lt == current)
		{  
			// Now we assign current right subtree to parent left subtree
			parent->lt = current->rt; 
			delete current;
			return;
		}
		else
		{ 
			parent->rt = current->rt;
			delete current;
			return;
		}
		
	}

	//Now checking if the right subtree is NULL, then the left subtree must exist
	if (current->rt == nullptr) 
	{
		//Checking for Root Case
		if (current == root)
		{
			root = root->lt;
			delete current;
			return;
		}

		//Reataching Subtree To Parent
		// Now we assign current left subtree to parent left subtree
		if (parent->lt == current) {
			parent->lt = current->lt;
			delete current;
		}
		else {
			parent->rt = current->lt;
			delete current;
		}
		return;
	}
}
//Function to delete a Two Way Case
void BST::BSTDeleteTwoWay(BSTptr& current/*, BSTptr parent*/) {
	//Find Closes predecessor(cp)
	BSTptr cp;
	BSTptr parent=nullptr;
	cp = current->lt;
	cp = recurRight(cp);
	//Find Parent to Cp
	parent= BSTfindParent(cp,parent);
	//Copy cp->nfo to P->info 
	strcpy_s(current->word, cp->word);
	/*parent = BSTfindParent(current, parent);
*/
	//Call the delete Leaf or Delete One CHild

	/**************************************************************************/
	//Leaf Case
	if (cp->lt == nullptr && cp->rt == nullptr) {
		BSTDeleteLeaf(cp, parent);
		return;
	}
	/*************************************************************************/
	//One way Case
	if ((cp->lt == nullptr && cp->rt != nullptr) ||
		(cp->lt != nullptr&& cp->rt == nullptr)) {
		BSTDeleteOneWay(cp, parent);
		return;
	}
	/**************************************************************************/

}
//Function that will help get the height of the tree.
int BST::maxHeight(BSTptr temp) {
	
	if (temp == nullptr) return 0;
	int lHeight = maxHeight(temp->lt);
	int rHeight = maxHeight(temp->rt);

	//Now we see which is the larger one
	if (lHeight > rHeight)
		return(lHeight + 1);
	else return(rHeight + 1);

}
//this function helps us get to the correct node of the tree when we want to 
//delete a word and it is a root case.
BSTptr BST::recurRight(BSTptr cp) {
	BSTptr start = cp;
	while (start->rt!=nullptr) {
		start = start->rt;
	}
	return start;	
}