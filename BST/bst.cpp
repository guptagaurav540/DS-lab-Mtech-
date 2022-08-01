#include <iostream>
#include<cstdlib>
using namespace std;

// Ltag==0 left points to the in-order predecessor
// Ltag===1 left points to the left child
// Rtag==0 right points to the in-order succesor
// Rtag===1 right points to the right child
// tag==-1 means NULL

// this class store the node information 
class BSTnode
{
public:
    int data;                               // used to store the value of node 
    int Ltag ;                          // stores left tree info -1 means NULL,1 means threaded,0 means subtree 
    int Rtag ;                          // stores Right tree info -1 means NULL,1 means threaded,0 means subtree 
    int rcount;                         // count the number of element in right subtree
    BSTnode *left;                          // left pointer
    BSTnode *right;                         // right pointer 
    // constructor of BSTnode 
    BSTnode(int value) : data(value), left(NULL), right(NULL), Ltag(-1), Rtag(-1),rcount(0){};
};
// linklist strucure
struct linknode
{
    int data;           // store value of a node 
    linknode *next;     // stores next node address;
};


// tree class stores the information of root and functions 
class BSTthread
{
    BSTnode *root = NULL;

public:
    BSTthread()
    {
        root = NULL;
    }
    BSTthread(int x);
    BSTthread(BSTthread &x);                    //copy constructor
    void insert(int value);         // insert element in BSTthread
    BSTnode *search(int value);     // search a element in BSTthread
    void Delete(int value);         // delete a existing value from BSTthread 
    void print();                   // print the tree in png file
    void inorderprint();            // print inorder traversal of tree
    void print3();
    linknode *allElementsBetween(int k1, int k2);   // find all elements between range from k1 to k2 
    BSTnode *min_element();         
    int successor(BSTnode *node);   // find succesor a BSTthread node 
    linknode *reverseInorder();     // return a linklist which contain the reverse inorder sequence 
    void kthElement(int k);         // find the kth largest element of tree
    void inorderInsert(BSTnode *);  // traverse tree in inorder and insert nodes in tree 
    BSTthread split(int k);               // split a tree in two tree first tree contain elemnts which is <=k and other >k
};

BSTnode *inordersuccessor(BSTnode *node);
BSTnode *inorderpredecssor(BSTnode *node);

// constructor
BSTthread::BSTthread(int value)
{
    root = new BSTnode(value);
}

// inorder insert function helping function for copy constructor
void BSTthread::inorderInsert(BSTnode *root)
{
    this->insert(root->data);
    if (root->Ltag == 0)
        this->inorderInsert(root->left);
    if (root->Rtag == 0)
        this->inorderInsert(root->right);
}

BSTthread::BSTthread(BSTthread &x)
{   
    if(x.root!=NULL)
        this->inorderInsert(x.root);
}


#include <queue>
void BSTthread::print3()
{
    FILE *fp = fopen("tree.dot", "w");
    queue<BSTnode *> q;

    BSTnode *temp = root;
    q.push(temp);
    if (fp == NULL)
    {
        cout << "File error";
        return;
    }
    if (root != NULL)
    {
        fprintf(fp, "digraph g{\n");
        fprintf(fp, "label=\"root %d \"\n", root->data);
        fprintf(fp, "%d[root=true]\n", root->data);
    }
    while (!q.empty())
    {
        temp = q.front();
        q.pop();
        if (temp->Ltag == 0)
        {
            fprintf(fp, "%d->%d;\n", temp->data, temp->left->data);
            q.push(temp->left);
        }
        if (temp->Ltag == 1)
        {
            fprintf(fp, "%d->%d[style=dotted];\n", temp->data, temp->left->data);
        }
        if (temp->Rtag == 1)
        {
            fprintf(fp, "%d->%d[style=dotted];\n", temp->data, temp->right->data);
        }
        if (temp->Rtag == 0)
        {
            fprintf(fp, "%d->%d;\n", temp->data, temp->right->data);
            q.push(temp->right);
        }
        /*
        if (temp->Rtag == -1)
            break;
        temp = inordersuccessor(temp);*/
    }
    fprintf(fp, "}");
    fclose(fp);
    system("dot -Tpng tree.dot -o png_file_name.png");
}

// finding the succesor of a node helping function for print a tree 
BSTnode *inordersuccessor(BSTnode *node)
{
    BSTnode *temp;
    if (node->Rtag == 1)
    {
        // Rtag=1 means node is threaded right pointer of node points to succesor of element 
        return (node->right);
    }
    else
    {
        // finding smallest element in right subtree 
        temp = node->right;
        while (1)
        {
            // if Ltag!=0 means samllest element 
            if (temp->Ltag !=0)
                break;
            temp = temp->left;
        }
        // return the succesor element 
        return temp;
    }
}
// printing the tree 
void BSTthread::print()
{
    // creating a trr.dot file 
    FILE *fp = fopen("tree.dot", "w");
    BSTnode *temp = root;
    if (fp == NULL)
    {
        cout << "File creating Error :";
        return;
    }
    // if root is null means no node is found 
    if (root != NULL)
    {
        fprintf(fp, "digraph g{\n");
        fprintf(fp, "label=\"rooted at %d \"\n", root->data);
        fprintf(fp, "%d[root=true]\n", root->data);
    }
    if(root!=NULL){
        // finding the samllest element of tree Ltag=-1 means smallest element 
        while (temp->Ltag != -1)
        {
            temp = temp->left;
        }

        while (1)
        {
            // largest element 
            if (temp->Rtag == 1)
            {
                fprintf(fp, "%d->%d[style=dotted];\n", temp->data, temp->right->data);
            }
            if (temp->Rtag == 0)
            {
                fprintf(fp, "%d->%d;\n", temp->data, temp->right->data);
            }
            if (temp->Ltag == 0)
            {
                fprintf(fp, "%d->%d;\n", temp->data, temp->left->data);
            }
            if (temp->Ltag == 1)
            {
                fprintf(fp, "%d->%d[style=dotted];\n", temp->data, temp->left->data);
            }

            if (temp->Rtag == -1)
                break;

            // finding inorder succesor of node ;
            temp = inordersuccessor(temp);
        }
        fprintf(fp, "}");
        fclose(fp);
        // creating png image file from dot file 
        system("dot -Tpng tree.dot -o png_file_name.png");
    }
}
//1. insert (x) -- insert an element x (if not present) into the BST. If x is present, throw an exception.
void BSTthread::insert(int value)
{
    // root=Null means no element  is present so creade a node and insert 
    if (root == NULL)
    {
        root = new BSTnode(value);
    }
    else
    {
        // finding the correct position of element to insert 
        BSTnode *parent = root, *temp2;
        while (1)
        {
            // if new elemrnt is less then root then we traverse in left subtree.
            if (parent->data > value)
            {
                // Ltag!=0 means tree have no left subtree so we can insert 
                if (parent->Ltag != 0)
                {
                    // creating new node 
                    temp2 = new BSTnode(value);
                    // pointeing predecessor of node;
                    temp2->left = parent->left;
                    // pointing succesor of node 
                    temp2->Ltag = parent->Ltag;
                    temp2->Rtag = 1;
                    temp2->right = parent;
                    parent->Ltag = 0;
                    parent->left = temp2;
                    break;
                }
                else
                {
                    // if pointer have left child then traverse to the left child 
                    parent = parent->left;
                }
            }
            // if new elemrnt is less then root then we traverse in left subtree.
            else if (parent->data < value)
            {   
                // increase rcount by 1 
                // rcount contain number of element in right subtree
                parent->rcount++;
                // if Rtag!=0 means no subtree then we can insert elment here 
                if (parent->Rtag != 0)
                {
                    // creating new node and pointing succesor and predecessor 
                    temp2 = new BSTnode(value);
                    temp2->right = parent->right;
                    temp2->Rtag = parent->Rtag;
                    temp2->left = parent;
                    temp2->Ltag = 1;

                    parent->Rtag = 0;
                    parent->right = temp2;
                    break;
                }
                // if node have right subtree we need to traverse to right subtree 
                else
                {
                    parent = parent->right;
                }
            }
            else
            {
                // if value is already present then break the loop 
                cout << value << " is already present in tree:\n";
                break;
            }
        }
    }
}

//2. search(x) -- search an element x, if found return its reference, otherwise return NULL.
BSTnode *BSTthread::search(int value)
{
    BSTnode *temp = root;

    while (1)
    {
        // if search element is less then root then we find element in left subtree
        if (value < temp->data)
        {

            // Ltag!=0 means there is no subtree so element not found un tree
            if (temp->Ltag != 0)
            {
                return NULL;
            }
            else
            {
                temp = temp->left;
            }
        }

        // if search element is greater then root then we find element in right subtree
        else if (value > temp->data)
        {
            // rtag!=0 means there is no subtree so element not found un tree
            if (temp->Rtag != 0)
            {
                return NULL;
            }
            else
            {
                temp = temp->right;
            }
        }
        // elemtemt foind in tree
        else
        {
            return temp;
        }
    }
}
//delete(x) -- delete an element x, if the element x is not present, throw an exception.
void BSTthread::Delete(int value)
{
    BSTnode *parent = NULL, *current = root;
    int found = 0;
    // finding element is present in s
    if(root==NULL)
    {
        cout<<"Tree is empty :";
        return;
    }
    
    BSTnode *se=this->search(value);
    if(se==NULL)
    {
        found=0;
    }
    else
	{
        found=1;
    }
	if (found == 0)
    {
        cout << "Element is not present in tree :";
    }
    
    else
    {
		//cout<<"element is present";
        current = root;
        parent = NULL;
        while (current != NULL)
        {
            if (current->data == value)
            {
                found = 1;
                break;
            }

            parent = current;
            if (value < current->data)
            {
                if (current->Ltag != 0)
                    break;
                current = current->left;
            }
            else
            {
                if (current->Rtag != 0)
                    break;
                current->rcount--;

                current = current->right;
            }
        }
        
        // if deleted node have two children
        
        if (current->Ltag == 0 && current->Rtag == 0)
        {

            // find sucessor node and  add at that place and delete exixting node
            BSTnode *succ = inordersuccessor(current);
            BSTnode *temp = current->right, *succpar = current;
           // cout << succ->data << "\n";
           if(current->right==succ)
           {
               //cout<<"cur"<<current->data<<"su"<<succ->data;
               current->data=succ->data;
               current->right=succ->right;
               current->Rtag=succ->Rtag;
               //this->inorderprint();
           }
           else{
                while (temp->data != succ->data)
                {
                    succpar = temp;
                    temp = temp->left;
                }
                current->data = succ->data;
                succpar->left = succ->left;
                succpar->Ltag = succ->Ltag;
           }
        }
        // means starting node deleted :
        else if(parent==NULL)
        {
            if(current->Ltag!=0 && current->Rtag!=0)
            {
                root=NULL;
            }

            else if(root->Rtag!=0)
            {
                BSTnode *pre=inorderpredecssor(root);
                root=root->left;
                
                if(pre->data==root->data)
                {
                    pre->Rtag=-1;
                    pre->right=NULL;
                }
                else{
                    pre->right=root;
                }
            }        
            else if(root->Ltag!=0)
            {
                BSTnode* succ=inordersuccessor(root);
                root=root->right;
                
                if(succ->data==root->data)
                {
                    succ->Ltag=-1;
                    succ->left=NULL;
                }
                else{
                    succ->left=root;
                }
            }
        }
        
        // deleted node have only one child
        // node have right tree
        else if (current->Rtag == 0)
        {
                parent->right = current->right;
                parent->Rtag = current->Rtag;
                if(parent->Rtag==0)
                {
                    parent->right->left = parent;
                }
        }
        // if node have left child
        else if (current->Ltag == 0)
        {
            parent->left = current->left;
            parent->Ltag = current->Ltag;
            if(parent->Ltag==0){
                parent->left->right = parent;
            }
        }
        // node have no child
        else
        {
            if (parent->data > value)
            {
                parent->left = current->left;
                parent->Ltag = 1;
                if (current->Ltag == -1)
                    parent->Ltag = -1;
            }
            else if (parent->data < value)
            {
                parent->right = current->right;
                parent->Rtag = 1;
                if (current->Rtag == -1)
                    parent->Rtag = -1;
            }
        }
        /*
        */
    }
}
// healper function for print bst inorderprint 
void print_bst(BSTnode *root)
{
    if (root != NULL)
    {
        // if left subtree then traverse to left 
        if (root->Ltag == 0)
            print_bst(root->left);
        // print root data
        cout <<root->data <<" ";
        // if right subtree then traverse to right subtree 
        if (root->Rtag == 0)
            print_bst(root->right);
    }
}
// print inordert travesal 
void BSTthread::inorderprint()
{
    print_bst(root);
    cout << "\n";
}

// finding minimum element in tree
BSTnode *BSTthread::min_element()
{
    BSTnode *temp = root;
    // finding the leftmost element of tree
    while (temp->Ltag != 0)
    {
        temp = temp->left;
    }
    return (temp);
}

// 5. successor(ptr) -- returns the key value of the node which is the inorder
//   successor of the x, where x is the key value of the node pointed by ptr
int BSTthread::successor(BSTnode *node)
{
    BSTnode *temp;
    if (node->Rtag == 1)
    {
        // if node have Rtag==1 mean node have not right child and it point to the succesor node then return
        // the value of next node
        return (node->right->data);
    }
    else
    {
        // when node have right child then it find the largest key value in right subtree
        temp = node->right;
        while (1)
        {

            if (temp->Ltag != 0)
                break;
            temp = temp->left;
        }
        return temp->data;
    }
}

// inorder predec
BSTnode *inorderpredecssor(BSTnode *node)
{
    BSTnode *temp;
    if (node->Ltag == 1)
    {
        return (node->left);
    }
    else
    {
        temp = node->left;
        while (1)
        {
            if (temp->Rtag == 1 || temp->Rtag == -1)
                break;
            temp = temp->right;
        }
        return temp;
    }
}

/*** this function used for solving the problem  allElementsBetween(k1, k2)*/

linknode *find_element(BSTnode *root, int k1, int k2)
{
    BSTnode *temp = root;
    while (1)
    {
        // find the fist element which is in range if [k1,k2]
        if (temp->data <= k2 && temp->data >= k1)
        {
            break;
        }
        else if (temp->data < k1)
        {
            // if k1 is larger then largest element of the tree then it returs NULL.
            if (temp->Rtag != 0)
                return NULL;
            temp = temp->right;
        }
        else if (temp->data > k2)
        {
            //if k2 is smaller then smallest element of tree then it returns NULL
            if (temp->Ltag != 0)
                return NULL;
            temp = temp->left;
        }
    }
    // finding the smallest element which is greater and equal to k1
    while (temp->Ltag == 0)
    {
        if (temp->left->data >= k1)
        {
            temp = temp->left;
        }
        else
        {
            break;
        }
    }
    if (temp->data < k1 || temp->data > k2)
        return NULL;
    linknode *temp2 = NULL;
    // add key value in linklist and find the next inorder succesor
    while (temp->data <= k2 && temp->Rtag != -1)
    {
        linknode *temp3 = new linknode;
        temp3->data = temp->data;
        temp3->next = temp2;
        temp2 = temp3;
        temp = inordersuccessor(temp);
    }
    return (temp2);
}

/*7. allElementsBetween(k1, k2) -- returns a singly linked list (write your own
class) that contains all the elements (k) between k1 and k2, i.e., k1 <= k <= k2. Your
code should run in O(h + N) time, where N is the number of elements that appears
between k1 and k2 in the BST.*/

linknode *BSTthread::allElementsBetween(int k1, int k2)
{
    if (root == NULL)
    {
        printf("No element present :");
        return NULL;
    }
    BSTnode *temp = root;
    return (find_element(temp, k1, k2));
}
/* 
4. reverseInorder() -- returns a singly linked list containing the elements of
the BST in max to min order. You should not use any extra stack and use threading
for non-recursive implementation.
*/
linknode *BSTthread::reverseInorder()
{

    BSTnode *temp = root;
    if (root == NULL)
    {
        return NULL;
    }
    // finding smallest element
    while (temp->Rtag == 0)
    {
        temp = temp->right;
    }
    linknode *list = NULL, *head;
    // loop runs untill all key value inserted in linklist
    while (1)
    {
        if (list == NULL)
        {
            list = new linknode;
            list->data = temp->data;
            head = list;
        }
        else
        {
            list->next = new linknode;
            list = list->next;
            list->data = temp->data;
        }
        // Rtag==-1 means largest element reached
        if (temp->Ltag == -1)
        {
            list->next = NULL;
            break;
        }
        temp = inorderpredecssor(temp);
    }
    return head;
}

/*
8. kthElement(k) -- finds the k-th largest element in the BST and prints the
key value. Your code should run in O(h) time.
*/

void BSTthread::kthElement(int k)
{
    BSTnode *node = root;
    int x = k;
    // finding the largest element present in the tree
    while (1)
    {
        if (node->rcount + 1 == k)
        {
            break;
        }
        else if (k <= node->rcount)
        {

            node = node->right;
        }
        else
        {
            k = k - (node->rcount + 1);
            node = node->left;
        }
    }
    cout << "Element " << x << " th largest is " << node->data << "\n";
}
vector<BSTnode *> split_k(BSTnode *root, int x)
{
    vector<BSTnode *> ans(2, NULL);
    if (root == NULL)
    {
        return ans;
    }
    if (x < root->data)
    {
        if(root->Ltag!=0)
        {
            ans[0]=NULL;
            ans[1]=root;    
            //cout << "NULL" << " " << ans[1]->data << "\n";
        
        }
        else{
            vector<BSTnode *> t;
            t = split_k(root->left, x);

            root->left = t[1];
            ans[1] = root;
            ans[0] = t[0];
          //  cout << ans[0]->data << " " << ans[1]->data << "\n";
        
        }
        return (ans);
    }
    if (x > root->data)
    {
        if(root->Rtag!=0)
        {

            ans[1]=NULL;
            ans[0]=root;
            //cout << ans[0]->data << " " << "NULL" << "\n";
        
        }
        else{
            vector<BSTnode *> t;
            t = split_k(root->right, x);
            ans[1] = t[1];
            root->right = t[0];
            ans[0] = root;
           // cout << ans[0]->data << " " << ans[1]->data << "\n";
        
        }
        return ans;
    }
    else
    {
        ans[0] = root;
        
        ans[1] = root->right;
        root->right=NULL;

        //cout << ans[0]->data << " " << ans[1]->data << "\n";
        return ans;
    }
}

BSTthread BSTthread::split(int k)
{
    BSTthread t1;
    vector<BSTnode *> ans;
    ans = split_k(root, k);
    root = ans[0];
    t1.root = ans[1];
    return t1;
}

int main()
{
	BSTthread tree;

    int choice = 0;
    int e[]={50,30,100,5,40,90,105,0,10,35,45,85,95};
    for(int i=0;i<sizeof(e)/sizeof(int);i++)
    {
        tree.insert(e[i]);
    }
    BSTnode *x;
    int k1, k2;
        

    linknode *ele;
        
    BSTthread tree2=tree;
    BSTthread tree3;
        
        cout << "Roll Number-214101018\n\n";
        cout << "Main Menu-\n";
        cout << "1. Insert :\n";
        cout<<"2. Search :\n";
        cout<<"3. Delete : \n";
        cout << "4. revesalnorder :\n";
        cout << "5. succesor :\n";
        cout << "6. split(k) :\n";
        cout << "7. allelementBetween :\n";
        cout << "8. kthElement :\n";
        cout << "9. PrintTree :\n";
        cout << "0 for exit\n";
        
    do
    {
        cout << "\n\nEnter Your choice - ";
        cin >> choice;
        int element;
        int n;

        switch (choice)
        {
        case 1:
            cout << "Number of element : ";
            cin >> n;
            cout << "Enter N numbers :";
            for (int i = 0; i < n; i++)
            {
                cin >> element;
                tree.insert(element);
            }
            tree.inorderprint();

            break;
        case 2:
        	tree.inorderprint();
            cout << "Enter Search Element :";
            cin >> element;
            x = tree.search(element);
            if (x == NULL)
            {
                cout << "Element Not found \n";
            }
            else
            {
                cout << "Element present :\n";
            }
            break;

        case 3:
            tree.inorderprint();
            cout << "Enter element :";
            cin >> element;
            tree.Delete(element);
            tree.inorderprint();            
            break;
        case 4:
            tree.inorderprint();
            cout << "Reversal inorder is :\n";
            ele = tree.reverseInorder();
            if (ele == NULL)
            {
                cout << "No element is present :";
            }
            else
            {
                while (ele != NULL)
                {
                    cout << ele->data << " ";
                    ele=ele->next;
                }
                cout << "\n";
            }
            break;

        case 5:
            tree.inorderprint();
            cout << "For succesor we need root pointer succesor is used for complete this assignment :\n";
            break;
        case 6:
            tree.inorderprint();
            //tree2.inorderprint();
            cout << "\nType Number :";
            cin>>element;
            tree3=tree2.split(element);
            cout<<"splited trees :\n";
            tree2.inorderprint();
            tree3.inorderprint();
            break;
        case 7:
            tree.inorderprint();
            cout << "Type k1 and k2 \n ";
            cin >> k1;
            cin >> k2;
            ele = tree.allElementsBetween(k1, k2);
            if (ele == NULL)
            {
                cout << "No element is present :\n";
            }
            else
            {
                while (ele != NULL)
                {
                    cout << ele->data << " ";
                    ele=ele->next;
                }
                cout << "\n";
            }

            break;
        case 8:
            tree.inorderprint();
            cout << "Enter K :";
            cin >> element;
            tree.kthElement(element);
            break;
        case 9:
            tree.print3();
            break;
        }

    } while (choice != 0);
}
