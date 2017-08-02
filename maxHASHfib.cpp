#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cmath>
#include "maxHASHfib.h"
using namespace std;
//Initialize the Heap//

node *H = InitHEAP();
int nNodeINlist;

node* retHEADnode()
{
	return H;
}

node* InitHEAP()

{
	node* n1;
	n1 = NULL;
	return n1;
}

//Create Node and instantiate the data value//
node* createNODE(int value)
{
	node *x = new node;
	x->key = value;
	return x;
}

//Insert a node//
node* insertNODE(node *H, node *x)
{
	x->degree = 0;
	x->left = x;
	x->right = x;
	x->child = NULL;
	x->parent = NULL;
	x->C = 'N';
	x->marked = 'F';
	//Check if any node exists in the fibonacci heap//
	if(H != NULL)
	{
		//Check the parent. If present point its right pointer to the newly inserted node//
		(H->left)->right = x;
		//point the newly inserted to maintain a circular list//
		x->right = H;
		//make the left pointer point to the parent and shift the linked list right//
		x->left = H->left;
		//Join the shifted list to x//
		H->left = x;
		if(x->key > H->key)
		{
			H = x;
		}
		
	}
  else
  {
    H = x;
  }
	//Increment the number of nodes in the circular list//
	nNodeINlist++;
	return H;
}


//This is a test function to print the heap
int displayTREE(node *H1)
{
	node* p = H1;
	if(p == NULL)
	{
		cout<<"The heap is empyty"<<endl;
		return 0;
	}
	cout << "The root nodes of the heap are: " << endl;
	
	do
	{
		cout<<p->key;
		p = p->right;
		if(p != H1)
		{
			cout<<"-->";
		}
		
	}
    
	while(p != H1 && p->right != NULL);
	cout<<endl;
}

//Establish linkage between parent and child nodes
int EstLINK(node *H1, node *a, node *b)
{
	//Remove the node from the circular list of siblings//
	(a->left)->right=a->right;
    (a->right)->left=a->left;
    if(b->right==b)
	{
      H1=b;
	}
    a->left=a;
    a->right=a;
    //Make the parent pointer of a as b
	a->parent=b;
	a->marked='F';
    if(b->child==NULL)
      b->child=a;
    a->right=b->child;
    a->left=(b->child)->left;
    ((b->child)->left)->right=a;
    (b->child)->left=a;
    if(a->key>(b->child)->key)
      b->child=a;
  
    b->degree++;
  
}

//Increase the key value of a node
int increaseKEY(node *H1,node *lookupPTR,  int oldKEY, int newKEY)
{
	node* gNODE;

	if(lookupPTR == NULL)
	{
		cout<<"Heap doesnot have the given key"<<endl;
		return NULL;
	}
	if(lookupPTR->key > newKEY)
	{
		return 0;
	}
	lookupPTR->key += newKEY;
	gNODE = lookupPTR->parent;
	if(gNODE != NULL && lookupPTR->key > gNODE->key)
	{
		cutNODE(H1, lookupPTR, gNODE);
    childCUTnode(H1, gNODE);
	}
	
	if(lookupPTR->key > H1->key)
	{
		H1 = lookupPTR;
	}
}

//Remove the node with maxmimum key
node* removeMAX(node *H1)

{
    node* retNODE;
    node* ptr;
    node* copyHEAP = H1;
    retNODE = copyHEAP;
    ptr = copyHEAP;
    //Check it the heap is empty//
	if (copyHEAP == NULL)
        return copyHEAP;
    node* x;
    node* np;
    x = NULL;
	//To remove the MAX node, first point to its child//
    if (copyHEAP->child != NULL)
        x = copyHEAP->child;
	//Check if MAX node has a child//	
    if (x != NULL)
    {
        ptr = x;
		//Add of the children of MAX node
        do
        {
            np = x->right;
            (H1->left)->right = x;
            x->right = H1;
            x->left = H1->left;
            H1->left = x;
            //Check if the child of z is max or sibling of the MAX node
			if (x->key > H1->key)
                H1 = x;
            x->parent = NULL;
            x = np;
        }
        while (np != ptr);
    }
	//Remove the MAX node from the circular list//
    (copyHEAP->left)->right = copyHEAP->right;
    (copyHEAP->right)->left = copyHEAP->left;
    H1 = copyHEAP->right;
    if (copyHEAP == copyHEAP->right && copyHEAP->child == NULL)
        H1 = NULL;
    else
    {
        H1 = copyHEAP->right;
        meldHEAP(H1);
    }
    nNodeINlist = nNodeINlist - 1;
    return retNODE;
}


//Meld the heap after removeMAX operation
int meldHEAP(node* H1)
{
    int d, i;
    int D = nNodeINlist; //Degree Table
    node* A[D];
    for (i = 0; i <= D; i++)
        A[i] = NULL;
    node* x = H1;
    node* y;
    node* np;
    node* pt = x;
	node* p = H1;
	node* array[nNodeINlist]; //Array to store root circular nodes//
	int cnt = 0;
	//Fill up the root circular in an array//
	do
	{
		array[cnt] = p;
		p = p->right;
		cnt++;
	}
	while(p!=H1);
  
  //Start the pairwise combination of nodes//
  //If two nodes have the same key value, make the node with greate degree as the parent//
   for(int i =0;i<cnt;i++)
    {
		x = array[i];
        d = x->degree;
        // 
		while (A[d] != NULL)
        {
            y = A[d];
			//Make the node with larger key as the parent of the smaller node
            if (x->key < y->key)
            {
				np = x;
                x = y;
                y = np;
            }
			//Make the node with larger degree as the parent of the node with smaller degree
			if(x->key == y->key)
			{
				if(x->degree < y->degree)
				{
					np = x;
					x = y;
					y = np;
				}
			}
			
            if (y == H1)
                H1 = x;
			//Establish the parent child relationship
			EstLINK(H1, y, x);
            if (x->right == x)
			{
                H1 = x;
			}
                A[d] = NULL;	
            
			//Increase the degree for the next iteration of degree table check//
			d = d + 1;
        }
		
        A[d] = x;
    }

	//Combine the nodes of different degree to make the circular list//
    H = NULL;
	for (int j = 0; j < D; j++)
    {
        if (A[j] != NULL)
        {
            A[j]->left = A[j];
            A[j]->right =A[j];
            if (H != NULL)
            {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->key > H->key)
                H = A[j];
            }
            else
            {
                H = A[j];
            }
            if(H == NULL)
                H = A[j];
            else if (A[j]->key > H->key)
                H = A[j];
        }
    }
}

//Cut the a given node from the heap
int cutNODE(node* root, node* childNODE, node* parent)
{
	//Check if the node childNODE has a sibling. If its the only sibling set the parent's child pointer to null//
    if (childNODE == childNODE->right)
	{
        parent->child = NULL;
    }
	else 
	{
        parent->child = childNODE->right;
	}
    //Remove the Child node from parent//
	(childNODE->left)->right = childNODE->right;
    (childNODE->right)->left = childNODE->left;
	//Decrease the Degree of the Parent//
    parent->degree = parent->degree - 1;
	//Make the left and the right pointers of the child to point to itself//
    childNODE->right = childNODE;
    childNODE->left = childNODE;
	//Insert the child node into the root circular list//
    (root->left)->right = childNODE;
    childNODE->right = root;
    childNODE->left = root->left;
    root->left = childNODE;
	//Makint the parent and marked fields as FALSE respectively
    childNODE->parent = NULL;
    childNODE->marked = 'F';
}

//Cascade cut 
int childCUTnode(node* root, node* y)
{
    node* z = y->parent;
   //Check it the node is in the root or not// 
	if (z != NULL)
    {
        
		if (y->marked == 'F')
        {
            y->marked = 'T';
	    }
        else
        {
            cutNODE(root, y, z);
            childCUTnode(root, z);
        }
    }
}

