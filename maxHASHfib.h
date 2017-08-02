//Node declalration
struct node
{
	//pointers//
	node* parent;
	node* child;
	node* right;
	node* left;
	//Degree of node//
	int degree;
	//Mark
	char marked;
	//Child
	char C;
	// key
	int key;
};

    
	
	// Initialize the heap//
	node* InitHEAP();
	// Establish fibonacci link between nodes
	int EstLINK(node *, node *, node *);
	//Insert a node
	node* insertNODE(node *, node *) ;
	//Create a new node//
	node* createNODE(int);
	//increase key function decreases the key value for a given node.
	int increaseKEY(node *,node *, int , int);
	//Remove the max node meld
	node* removeMAX(node *);
	//Cut the node from the heap//
	int cutNODE(node *,node *,node *);
	//Cascade Cut if marked
	int childCUTnode(node *,node *);
	//Meld the Heap
	int meldHEAP(node *);
	//Diplay the tree. This is a test function//
	int displayTREE(node *);
	//Head node//
	node* retHEADnode();
  //node* H;
 //node* H = InitHEAP();
 
