#include <iostream>
#include<cstdlib>
#include<time.h>
#include <stack>
#include<map>
#include <bits/stdc++.h>
using namespace std;

class BST_node
{

private:
    int data; 
    int height;                           // used to store the value of node 
    BST_node *left;                          // left pointer
    BST_node *right;               // right pointer
    friend class BST;
public:                         
    // constructor of BST_node 
    BST_node();
    BST_node(int value) : data(value),height(0), left(NULL), right(NULL){};
};
// linklist strucure
struct linknode
{
    int data;           // store value of a node 
    linknode *next;     // stores next node address;
};


// tree class stores the information of root and functions 
class BST
{
    BST_node *root = NULL;
    int no_of_rotation=0;
    int no_of_comparision=0;
public:
    BST()
    {
        root = NULL;
    }
    BST(int x);
    void insert(int value);         // insert element in BST
    BST_node *search(int value);     // search a element in BST
    void inorderprint();
    void print_bst(BST_node *node);
    void BST_print();
    void traverse(BST_node *root,FILE *fp);
    void Delete(int x);
    BST_node *Succesor(BST_node *);
    int traverse2(BST_node *node);
    int average_node_height();
    int count_node();
    int traverse3(BST_node *);
    int height()
    {
        return root->height;
    }
    int rotation()
    {
        return no_of_rotation;
    }
    int comparision()
    {
        return no_of_comparision;
    }
    
};




// constructor
BST::BST(int value)
{
    root = new BST_node(value);
}
// healper function for print bst inorderprint 
void BST::print_bst(BST_node *node)
{
    if (node != NULL)
    {
        // if left subtree then traverse to left 
        if (node->left != NULL)
            print_bst(node->left);
        // print root data
        cout <<node->data <<" "<<"\n";
        // if right subtree then traverse to right subtree 
        if (node->left != NULL)
            print_bst(node->right);
    }
}
// print inordert travesal 
void BST::inorderprint()
{
    print_bst(root);
}


//1. insert (x) -- insert an element x (if not present) into the BST. If x is present, throw an exception.
void BST::insert(int value)
{
    stack<BST_node*> sta;
    // root=Null means no element  is present so creade a node and insert 
    
    if (root == NULL)
    {
        root = new BST_node(value);
    }
    else
    {
        // finding the correct position of element to insert 
        BST_node *parent = root, *temp2;
        while (1)
        {
            sta.push(parent);
            // if new elemrnt is less then root then we traverse in left subtree.
            if (parent->data > value)
            {
                // Ltag!=0 means tree have no left subtree so we can insert 
                if (parent->left==NULL)
                {
                    // creating new node 
                    temp2 = new BST_node(value);
                    parent->left = temp2;
                    sta.push(temp2);
                    
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
                // if Rtag!=0 means no subtree then we can insert elment here 
                if (parent->right ==NULL)
                {
                    // creating new node and pointing succesor and predecessor 
                    temp2 = new BST_node(value);
                    parent->right = temp2;
                    sta.push(temp2);
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
                //cout << value << " is already present in tree:\n";
                break;
            }
            no_of_comparision++;
        }

        while(!sta.empty())
        {
            int h1=-1,h2=-1;
            temp2=sta.top();
            sta.pop();
            if(temp2->left!=NULL)
                h1=temp2->left->height;
            if(temp2->right!=NULL)
                h2=temp2->right->height;
            temp2->height=h1>h2?h1+1:h2+1;
        }
    }
}


//2. search(x) -- search an element x, if found return its reference, otherwise return NULL.
BST_node *BST::search(int value)
{
    BST_node *temp = root;

    while (1)
    {
        // if search element is less then root then we find element in left subtree
        if (value < temp->data)
        {

            // Ltag!=0 means there is no subtree so element not found un tree
            if (temp->left ==NULL)
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
            if (temp->right == NULL)
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





// Helper finction for AVL_Print 
void BST::traverse(BST_node *root,FILE *fp)
{
    if(root!=NULL)
    {
        // If root have child then insert edge in file 
        fprintf(fp,"%d [label=\"<f0>|<f1>%d|<f2> %d|<f3>\"];\n",root->data,root->data,root->height);
        if(root->left!=NULL)
        {
            fprintf(fp, "%d:f0->%d:f1\n",root->data, root->left->data);
            traverse(root->left,fp);
        }
        if(root->right!=NULL)
        {
            fprintf(fp, "%d:f3->%d:f1\n",root->data, root->right->data);

            traverse(root->right,fp);
        }
        // traverse left child and right Child 
        
    }
}
// printing the tree
void BST::BST_print()
{
    char filename[]="abc";
    // creating a trr.dot file
    string dot_file_name="";
    dot_file_name=dot_file_name+filename+".dot";
    FILE *fp = fopen(dot_file_name.c_str(), "w");
    BST_node *temp = root;
    if (fp == NULL)
    {
        cout << "File creating Error :";
        return;
    }
    // if root is null means no node is found
    if (root != NULL)
    {
        fprintf(fp, "digraph g{\n");
        fprintf(fp,"node [shape=record, height=0.1];\n");
        fprintf(fp, "label=\"rooted at %d \"\n", root->data);
        fprintf(fp, "%d[root=true]\n", root->data);
    }
    if (root != NULL)
    {
        this->traverse(root,fp); 
    
        fprintf(fp, "}");
        fclose(fp);
        string png_file="";
        png_file=png_file+filename+".png";
        string s="dot -Tpng ";
        s=s+dot_file_name+" -o "+png_file;
        const char *command=s.c_str();
        system(command);
    }
}
BST_node* BST::Succesor(BST_node *node)
{
    node=node->right;
    while(node->left!=NULL)
    {
        node= node->left;
    }
    return node;
}

void BST::Delete(int x)
{
    stack<BST_node*> s;
    BST_node *current=root;
    while(current!=NULL)
    {
        if(current->data==x)
        {
            s.push(current);
            break;
        }
        else if(current->data>x)
        {

            s.push(current);
            current=current->left;
        }
        else{

            s.push(current);
            current=current->right;
        }
        no_of_comparision++;
    }

    if(current!=NULL)
    {
    	// succesor available 
        if(current->right!=NULL)
        {
        	
            BST_node *temp=current->right;
            s.push(temp);
            while(temp->left!=NULL)
            {
                temp=temp->left;
                s.push(temp);
            }
            current->data=temp->data;
                
            s.pop();
            if(current-> right == temp)
            {
                current->right=temp->right;
            }
            else{
                s.top()->left=temp->right;
            }
        }
        // succesdor not available 
        else
        {
        	//cout<<s.top()->data;
            s.pop();
            
			if(s.empty())
            {	
				if(current->left!=NULL)
                	root=current->left;
                else
                	root=NULL;
            }
            else
            {
            	if(s.top()->left==current)
            	{
            		s.top()->left=current->left;
				}
				else{
					s.top()->right=current ->left;
				}
            }
        }
        while(!s.empty())
        {
            int h1=-1,h2=-1;
            BST_node *temp=s.top();
            s.pop();
            if(temp->left!=NULL)
                h1=temp->left->height;
            if(temp->right!=NULL)
                h2=temp->right->height;
            temp->height=h1>h2?h1+1:h2+1;
        }

    }
    else{
       // printf("Element is not present in BST\n");
    }
}


int BST::traverse2(BST_node *root)
{
    if(root!=NULL)
    {
        return(root->height+traverse2(root->left)+traverse2(root->right));
    }
    return 0;
}

int BST::average_node_height()
{
    
    return traverse2(root);
    cout<<"\n";
}

int BST::traverse3(BST_node *node)
{
    if(node!=NULL)
    {
        return(1+traverse3(node->left)+traverse3(node->right));
    }
    return 0;
}
int BST::count_node()
{
	if(root!=NULL)
    return(traverse3(root));
    else{
    	return 0;
	}
}

