#include <stack>
#include<map>
#include <bits/stdc++.h>
#include<queue>
#include <cstdlib>
#include <ctime>

using namespace std;
// create a treap class 
class Treap_Node
{

private:
    int data;                       // key value 
    int priority;                   // priority 
    int height;                           // height 
    Treap_Node *left;                          // left pointer
    Treap_Node *right;               // right pointer
    friend class Treap;
public:                         
    // constructor of Treap_Node 
    Treap_Node();
    Treap_Node(int value,int prio) : data(value),priority(prio),height(0), left(NULL), right(NULL){};
};

// tree class stores the information of root and functions 
class Treap
{
    Treap_Node *root = NULL;
    map<int,int> entry;
    // count the number of rotation
    long int no_of_rotation=0;
    //  count the number of comparison
    long int no_of_comparision=0;

public:
    // constructor 
    Treap()
    {
        root = NULL;
    }
    Treap(int x,int prio);
    void insert(int value);         // insert element in Treap
    Treap_Node *search(int value);     // search a element in Treap
    Treap_Node *R_rotation(Treap_Node *);       // R_rotation for rearranging priority 
    Treap_Node *L_rotation(Treap_Node *);       // L_rotation for rearranging priority
    void inorderprint();
    void print_treap(Treap_Node *node);
    void Treap_Print(char filename[]);
    void traverse(Treap_Node *root,FILE *fp);
    void Delete(int x);
    int traverse2(Treap_Node *node);
    int average_node_height();
    int count_node();
    int traverse3(Treap_Node *);
    int treap_height()
    {
        // return the height of root node 
        return root->height;
    }
    int treap_rotation_count(){ return no_of_rotation; }        // return the number of rotation
    int treap_comparision_count(){return no_of_comparision; }   // return the number of comaparison
            
};



using namespace std;

// constructor
Treap::Treap(int value, int prio)
{
    root = new Treap_Node(value, prio);
}
// helping function for node count 
int Treap::traverse3(Treap_Node *node)
{
    if (node != NULL)
    {
        return (1 + traverse3(node->left) + traverse3(node->right));
    }
    return 0;
}
// count the number of node available in tree 
int Treap::count_node()
{
    return (traverse3(root));
}
// helping  function for average height of nodes 
int Treap::traverse2(Treap_Node *root)
{
    if (root != NULL)
    {
        // sum of height of node and subtrees 
        return (root->height + traverse2(root->left) + traverse2(root->right));
    }
    return 0;
}
// return sum of height of nodes 
int Treap::average_node_height()
{

    return traverse2(root);
    cout << "\n";
}

// healper function for print bst inorderprint
void Treap::print_treap(Treap_Node *node)
{
    if (node != NULL)
    {
        print_treap(node->left);
        cout << node->data << " ";
        print_treap(node->right);
    }
}
// print inordert travesal
void Treap::inorderprint()
{
    print_treap(root);
    
}


// R-rotation of node 
Treap_Node *Treap::R_rotation(Treap_Node *node)
{
    // increase the number of rotation 
    no_of_rotation++;
    int h1 = -1, h2 = -1;
    // rotation 
    Treap_Node *lchild = node->left;
    node->left = lchild->right;
    lchild->right = node;

    // height balance of tree 
    if (node->left != NULL)
        h1 = node->left->height;
    if (node->right != NULL)
        h2 = node->right->height;

    // height update of node 
    node->height = h1 > h2 ? h1 + 1 : h2 + 1;
    h1 = -1;
    h2 = -1;
    if (lchild->left != NULL)
        h1 = lchild->left->height;
    h2 = node->height;
    lchild->height = h1 > h2 ? h1 + 1 : h2 + 1;

    // return the modified root of rotated tree 
    return lchild;
}
// L-rotation of node 
Treap_Node *Treap::L_rotation(Treap_Node *node)
{
    // increase the number of rotation 
    no_of_rotation++;
    int h1 = -1, h2 = -1;
    //rotation
    Treap_Node *rchild = node->right;
    node->right = rchild->left;
    rchild->left = node;
    
    // height balance of tree 
    if (node->left != NULL)
        h1 = node->left->height;
    if (node->right != NULL)
        h2 = node->right->height;
    // height update of node 
    node->height = h1 > h2 ? h1 + 1 : h2 + 1;
    h1 = -1;
    h2 = -1;

    h1 = node->height;
    if (node->right != NULL)
        h2 = node->right->height;
    rchild->height = h1 > h2 ? h1 + 1 : h2 + 1;
    // return modified root of tree after rotation
    return rchild;
}
//1. insert (x) -- insert an element x (if not present) into the BST. If x is present, throw an exception.
void Treap::insert(int value)
{
    int count = 0;
    stack<Treap_Node *> sta;        // stack for inserting the tree nodes path 
    int prio;
    while (1)
    {
        // asigning priority to the inserted node 
        prio = rand() % 10000;
        // if priority is already present then assign other priority 
        if (entry.count(prio) == 0)
        {
            break;
        }
    }

    // root=Null means no element  is present so creade a node and insert
    if (root == NULL)
    {
        root = new Treap_Node(value, prio);
        entry[prio] = value;
    }
    else
    {
        // finding the correct position of element to insert
        Treap_Node *parent = root, *temp2;
        while (1)
        {
            sta.push(parent);
            // if new elemrnt is less then root then we traverse in left subtree.
            if (parent->data > value)
            {
                // left==NULL means tree have no left subtree so we can insert
                if (parent->left == NULL)
                {
                    // creating new node
                    temp2 = new Treap_Node(value, prio);
                    parent->left = temp2;
                    sta.push(temp2);
                    entry[prio] = value;
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
                // if right==NULL means no subtree then we can insert elment here
                if (parent->right == NULL)
                {
                    // creating new node and pointing succesor and predecessor
                    temp2 = new Treap_Node(value, prio);
                    parent->right = temp2;
                    sta.push(temp2);
                    entry[prio] = value;
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
                no_of_comparision -= count;
                break;
            }
            // number of comparision increased accourding to height
            no_of_comparision++;
            count++;
        }
        // inserted by comparing value now we have to arrange priority
        Treap_Node *current = sta.top();
        sta.pop();
        // Here we balancing the number tree we maintain a stack which is used for modified tree
        while (!sta.empty())
        {
            int h1 = -1, h2 = -1;
            Treap_Node *parent = sta.top();
            sta.pop();
            // if inserted element priority is greater then rotate tree and 
            // modified untill the tree is not correct

            // if insered node is at correct posiotion  
            if (parent->priority <= current->priority)
            {
                if (parent->left != NULL)
                    h1 = parent->left->height;
                if (parent->right != NULL)
                    h2 = parent->right->height;
                parent->height = h1 > h2 ? h1 + 1 : h2 + 1;

                break;
            }
            // if inserted element is priority is less then parent 
            else
            {
                // if element is in left side of parent then r-rotation
                if (parent->left == current)
                {
                    if (!sta.empty())
                    {
                        if (sta.top()->left == parent)
                        {
                            current = R_rotation(parent);
                            sta.top()->left = current;
                        }
                        else
                        {
                            current = R_rotation(parent);
                            sta.top()->right = current;
                        }
                    }
                    else
                    {
                        root = R_rotation(parent);
                        break;
                    }
                }
                // else rotate left 
                else
                {
                    if (!sta.empty())
                    {
                        if (sta.top()->right == parent)
                        {
                            current = L_rotation(parent);
                            sta.top()->right = current;
                        }
                        else
                        {
                            current = L_rotation(parent);
                            sta.top()->left = current;
                        }
                    }
                    else
                    {
                        root = L_rotation(parent);
                        break;
                    }
                }
            }

            parent = current;
        }
    }
}

//2. search(x) -- search an element x, if found return its reference, otherwise return NULL.
Treap_Node *Treap::search(int value)
{
    Treap_Node *temp = root;
	if(root==NULL)
	{
		return NULL;
	}
    while (1)
    {
        // if search element is less then root then we find element in left subtree
        if (value < temp->data)
        {

            // left==NULL means there is no subtree so element not found un tree
            if (temp->left == NULL)
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
            // right=NULL means there is no subtree so element not found un tree
            if (temp->right == NULL)
            {
                return NULL;
            }
            else
            {
                temp = temp->right;
            }
        }
        // element found in tree
        else
        {
            return temp;
        }
    }
}

// Helper finction for AVL_Print
void Treap::traverse(Treap_Node *root, FILE *fp)
{
    if (root != NULL)
    {
        // If root have child then insert edge in file
        fprintf(fp, "%d [label=\"<f0>|<f1>%d|<f2>%d |<f3>\"];\n", root->data, root->data, root->priority);
        if (root->left != NULL)
        {
            fprintf(fp, "%d:f0->%d:f1\n", root->data, root->left->data);
            traverse(root->left, fp);
        }
        if (root->right != NULL)
        {
            fprintf(fp, "%d:f3->%d:f1\n", root->data, root->right->data);

            traverse(root->right, fp);
        }
        // traverse left child and right Child
    }
}
// printing the tree
void Treap::Treap_Print(char filename[])
{
    //char filename[]="abc";
    // creating a trr.dot file
    string dot_file_name = "";
    dot_file_name = dot_file_name + filename + ".dot";
    FILE *fp = fopen(dot_file_name.c_str(), "w");
    Treap_Node *temp = root;
    if (fp == NULL)
    {
        cout << "File creating Error :";
        return;
    }
    // if root is null means no node is found
    if (root != NULL)
    {
        fprintf(fp, "digraph g{\n");
        fprintf(fp, "node [shape=record, height=0.1];\n");
        fprintf(fp, "label=\"rooted at %d \"\n", root->data);
        fprintf(fp, "%d[root=true]\n", root->data);
    }
    if (root != NULL)
    {
        this->traverse(root, fp);

        fprintf(fp, "}");
        fclose(fp);
        string png_file = "";
        png_file = png_file + filename + ".png";
        string s = "dot -Tpng ";
        s = s + dot_file_name + " -o " + png_file;
        const char *command = s.c_str();
        system(command);
    }
}

void Treap::Delete(int x)
{
    stack<Treap_Node *> s;
    Treap_Node *current = root;
    while (current != NULL)
    {
        if (current->data == x)
        {
            //cout<<"element found :\n";
            break;
        }
        else if (current->data > x)
        {
            // push path nodes in stack 
            s.push(current);
            current = current->left;
        }
        else
        {

            // push path nodes in stack 
            s.push(current);
            current = current->right;
        }
        // increase number of comparison 
        no_of_comparision++;
    }

    if (current != NULL)
    {
        // increase priority of inserted element as infinite
        current->priority = 15000;

        Treap_Node *parent = NULL;
        if (!s.empty())
        {
            parent = s.top();
            //s.pop();
        }
        while (1)
        {
            // if deleted element have no parent 
            if (parent == NULL)
            {

                //cout<<"deletion case when parent is null:\n";
                if (current->left == NULL && current->right == NULL)
                {
                    root = NULL;
                    // printf("Element deleted :\n");
                    break;
                }
                else
                {
                    Treap_Node *temp;
                    // if deleted element have no left tree then left rotation
                    if (current->left == NULL)
                    {
                        root = L_rotation(current);
                    }
                    // if deleted element have no right subtree then right rotation 
                    else if (current->right == NULL)
                    {
                        root = R_rotation(current);
                    }
                    else
                    {
                        // if deleted element have both tree ]

                        // if left child have hight priority then parent then right rotation
                        if (current->left->priority < current->right->priority)
                        {
                            root = R_rotation(current);
                        }
                        
                        // if right child have hight priority then parent then left rotation
                        else
                        {
                            root = L_rotation(current);
                        }
                    }
                }
                parent = root;
                s.push(root);
            }
            // if deleted node have parent node 
            else
            {
                Treap_Node *temp;
                //cout<<"deletion case when parent is not null:\n";
                // if deleted node have no child 
                if (current->left == NULL && current->right == NULL)
                {
                    //  printf("Element deleted :");
                    if (parent->left == current)
                    {
                        parent->left = NULL;
                    }
                    else
                    {
                        parent->right = NULL;
                    }
                    break;
                }
                // if deleted node have not left child 
                else
                {
                    // if deleted node have no left subtree
                    if (current->left == NULL)
                    {
                        // if deleted node is left node of parent node 
                        if (parent->left == current)
                        {
                            temp = L_rotation(current);
                            parent->left = temp;
                        }
                        // if deletd node is right node of parent node 
                        else
                        {
                            temp = L_rotation(current);
                            parent->right = temp;
                        }
                    }
                    // if deleted node have no right subtree
                    else if (current->right == NULL)
                    {
                        // if deleted node is left node of parent node 
                        
                        if (parent->left == current)
                        {
                            temp = R_rotation(current);
                            parent->left = temp;
                        }
                        // if deletd node is right node of parent node 
                        
                        else
                        {
                            temp = R_rotation(current);
                            parent->right = temp;
                        }
                    }
                    // if current node have both children 
                    else
                    {

                        if (current->left->priority < current->right->priority)
                        {
                            if (parent->left == current)
                            {
                                temp = R_rotation(current);
                                parent->left = temp;
                            }
                            else
                            {
                                temp = R_rotation(current);
                                parent->right = temp;
                            }
                        }
                        else
                        {
                            if (parent->left == current)
                            {
                                temp = L_rotation(current);
                                parent->left = temp;
                            }
                            else
                            {
                                temp = L_rotation(current);
                                parent->right = temp;
                            }
                        }
                    }
                }
                parent = temp;
                s.push(parent);
            }
        }

        // height balancing of tree 
        while (!s.empty())
        {
            //    cout<<"Height balance :\n";
            int h1 = -1, h2 = -1;
            Treap_Node *temp = s.top();
            if (temp->left != NULL)
                h1 = temp->left->height;
            if (temp->right != NULL)
                h2 = temp->right->height;

            temp->height = h1 > h2 ? h1 + 1 : h2 + 1;
            s.pop();
        }
    }
    // element is not found in tree 
    else
    {
        //printf("Element is not present in Treap\n");
    }
}
