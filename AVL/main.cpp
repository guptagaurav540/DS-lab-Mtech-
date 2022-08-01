#include<iostream>
#include"avl.h"

#include <stack>
#include<queue>
using namespace std;


AVL_Tree::AVL_Tree()
{
    root = NULL;
}

// copy constructor 
AVL_Tree::AVL_Tree(const AVL_Tree &T)
{
    
    AVL_Node *temp=T.root;
    root=NULL;
    if(temp!=NULL)
    {
        // Level order traversal
        queue<AVL_Node *> qu;
        // insert first node in queue 
        qu.push(temp);
        while(!qu.empty())
        {
            // Remove one node from queue and find the children and insert the element in new tree 
            temp=qu.front();
            qu.pop();
            cout<<temp->key;
            // Insert element in tree 
            this->AVL_Insert(temp->key);
            // Check left subtree of current node 
            if(temp->LChild!=NULL)
            {
                qu.push(temp->LChild);
            }
            // Check right Subtree of current node 
            if(temp->RChild!=NULL)
            {
                qu.push(temp->RChild);
            }
        }

    }
}

// Assignment Operator 
AVL_Tree& AVL_Tree::operator=(const AVL_Tree &T)
{    
    AVL_Node *temp=T.root;
    root=NULL;
    if(temp!=NULL)
    {
        // Level order traversal
        queue<AVL_Node *> qu;
        // insert first node in queue 
        qu.push(temp);
        while(!qu.empty())
        {
            // Remove one node from queue and find the children and insert the element in new tree 
            temp=qu.front();
            qu.pop();
            cout<<temp->key;
            // Insert element in tree 
            this->AVL_Insert(temp->key);
            // Check left subtree of current node 
            if(temp->LChild!=NULL)
            {
                qu.push(temp->LChild);
            }
            // Check right Subtree of current node 
            if(temp->RChild!=NULL)
            {
                qu.push(temp->RChild);
            }
        }

    }
    return *this;
}

//Inorder traversal  
// traverse is helper function for node print 
void AVL_Tree::traverse2(AVL_Node *root)
{

    if(root!=NULL)
    {
        // First Traverse left subtree 
        traverse2(root->LChild);
        // Print node and Balanace factor 
        cout<<root->key<<" ";
        // Traverse Right Subtree 
        traverse2(root->RChild);
    }
}
// Print Inorder Tree 
void AVL_Tree::print_tree()
{
    
    traverse2(root);
    cout<<"\n";
}
// Helper finction for AVL_Print 
void AVL_Tree::traverse(AVL_Node *root,FILE *fp)
{
    if(root!=NULL)
    {
        // If root have child then insert edge in file 
        fprintf(fp,"%d [label=\"<f0>|<f1>%d|<f2>%d |<f3>\"];\n",root->key,root->key,root->bf);
        if(root->LChild!=NULL)
        {
            fprintf(fp, "%d:f0->%d:f1\n",root->key, root->LChild->key);
            traverse(root->LChild,fp);
        }
        if(root->RChild!=NULL)
        {
            fprintf(fp, "%d:f3->%d:f1\n",root->key, root->RChild->key);

            traverse(root->RChild,fp);
        }
        // traverse left child and right Child 
        
    }
}
// printing the tree
void AVL_Tree::AVL_Print(const char *filename)
{
    // creating a trr.dot file
    string dot_file_name="";
    dot_file_name=dot_file_name+filename+".dot";
    FILE *fp = fopen(dot_file_name.c_str(), "w");
    AVL_Node *temp = root;
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
        fprintf(fp, "label=\"rooted at %d \"\n", root->key);
        fprintf(fp, "%d[root=true]\n", root->key);
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


// Search an element in Tree if element is found in tree then return TRUE otherwise False 
bool AVL_Tree::AVL_Search(int k)
{
    AVL_Node *temp = root;
    // If temp==NULL means there is no element in tree so simply return false 
    while (temp != NULL)
    {
        // if temp->key==k means element is found in tree so return true 
        if (temp->key == k)
        {
            return true;
        }
        // if temp->key<k means root is less then search element so find element in right subtree 
        else if (temp->key < k)
        {
            temp = temp->RChild;
        }
        // if temp->key>k means root is greater then search element so find element in left subtree
        else
        {
            temp = temp->LChild;
        }
    }
    return false;
}
// Take the node which have BF -2 or +2 and return the root node of modified subtree 
AVL_Node *AVL_Tree::LL_Rotation(AVL_Node *node)
{
    // In the LL_Rotation we make the left node as a root node of subtree 
    // and modify the balance factor ,
    // Rotate right means right child of modified root node is unbalanced node 

    AVL_Node *temp=node;
    // node points to the root of subtree 
    node=temp->LChild;
    temp->LChild=node->RChild;
    //right child of root points to the unbalanced node 
    node->RChild=temp;
    // Balance factor modification
    node->bf=0;
    temp->bf=0;
    // Return the root node of subtree 
    return node;
}
// Take the node which have BF -2 or +2 and return the root node of modified subtree 
AVL_Node *AVL_Tree::RR_Rotation(AVL_Node *node)
{
    // In the RR_Rotation we make the right node as a root node of subtree 
    // and modify the balance factor ,
    // Rotate left means left child of modified root node is unbalanced node 

    AVL_Node *temp;
    // temp points to the root node of subtee 
    temp = node->RChild;
    node->RChild=temp->LChild;
    // left child of root points to unbalanced node 
    temp->LChild=node;
    node->bf=0;
    temp->bf=0;
    // return the root node of subtree 
    return temp;

}
// Take the node which have BF -2 or +2 and return the root node of modified subtree 
AVL_Node *AVL_Tree::LR_Rotation(AVL_Node *node)
{
    
    AVL_Node *left,*lright;
    left = node->LChild;
    lright=left->RChild;
    
    left->RChild=lright->LChild;
    lright->LChild=left;
    node->LChild=lright->RChild;
    lright->RChild=node;
    
    if(lright->bf==0)
    {
        left->bf=0;
        node->bf=0;
    }
    else if(lright->bf<0)
    {
        node->bf=0;
        lright->bf=0;
        left->bf=1;
    }
    else if(lright->bf>0)
    {
        left->bf=0;
        lright->bf=0;
        node->bf=-1;
    }
    return lright;

}

// Take the node which have BF -2 or +2 and return the root node of modified subtree 
AVL_Node *AVL_Tree::RL_Rotation(AVL_Node *node)
{
    AVL_Node *right,*rleft;
    right = node->RChild;
    rleft=right->LChild;
    
    right->LChild=rleft->RChild;
    rleft->RChild=right;
  
    node->RChild=rleft->LChild;
    rleft->LChild=node;
    if(rleft->bf==0)
    {
        node->bf=0;
        right->bf=0;
    }
    else if(rleft->bf>0)
    {
        right->bf=-1;
        node->bf=0;
        rleft->bf=0;
    }
    else if(rleft->bf<0)
    {
        node->bf=1;
        rleft->bf=0;
        right->bf=0;
    }
    return rleft;

}


void AVL_Tree::AVL_Insert(int k)
{
    // search element in tree if element exist in tree then elment is already present 
    bool a=this->AVL_Search(k);
    if(a==true)
    {
        cout<<"Element is already present:\n";
        return;
    }
    // if element is not present
    // stack is used to store the pointers from root to the poisition where the node is inserted  
    stack<AVL_Node *> sta; 
    AVL_Node *temp = root, *curr, *parent = NULL;
    while (temp != NULL)
    {
        // push the current pointer in stack
        sta.push(temp);
        parent = temp;
        // if inserted element is less then the key value go to left subtree otherwise right subtree
        if (k < temp->key)
        {
            temp = temp->LChild;
        }
        else if(k>temp->key)
        {
            temp = temp->RChild;
        }
    }
    // New node created with key element which is inserted 
    curr = new AVL_Node(k);
    // if pr==NULL means parents are null means root inserted as first element 
    if (parent == NULL)
    {
        // make root as current node and return 
        root = curr;
        return;
    }
    // if inserted element is less then the key vale of leaf node then make new node as left child 
    if (k < parent->key)
    {
        parent->LChild = curr;
    }

    // if inserted element is greater then the key vale of leaf node then make new node as right child 
    else
    {
        parent->RChild = curr;
    }
    // balancing the ancestor nodes 
    while (!sta.empty())
    {
        parent = sta.top();
        sta.pop();
        
        // hight of tree is increased in left subtree then balance factor of node is increased by 1 
        if (parent->LChild == curr)
        {
            parent->bf++;
        }
        // if hight of tree is increased in right subtree then balance factor of node decrease by 1 
        else
        {
            parent->bf--;
        }
        // after increasing and decreasing balance factor of node if balance factor is 0 means inserted node not increase the hight  
        if (parent->bf == 0)
        {
            break;
        }
        // after increasing and decreasing balance factor of node if balance factor is 1 or -1 
        //means hght of left or right subtree increases so it may be it unbalance the ancestor nodes
        else if (parent->bf == -1) // hight increased in right subtree 
        {
            curr = parent;
        }
        else if(parent->bf==1)  // hight increased in left subtree
        {
            curr = parent;
        }
        // if balance factor of node is +2 or -2 means tree is unbalance so we need to balance the tree
        else 
        {
            // if parent and child have same sign of bf then single rotation
            // if parent and child have diffrent sign then double rotation
            // balance factor of node >0 means the left subtree have greater height then right subtree
            // if one time balance haven then no need to balanace again tree is now balanced 
            if (parent->bf > 0)
            {
                if (curr->bf > 0)
                {
                    // LL unbalanaced 
                    parent= LL_Rotation(parent);
                }
                else
                {
                    // LR unbalanaced
                    parent=LR_Rotation(parent);
                }
            }
            // balance factor is <0 means right subtree have greater size 
            else if (parent->bf < 0)
            {
                if (curr->bf < 0)
                {
                    // RR unbalanace 
                    parent= RR_Rotation(parent);
                }
                else
                {
                    // RL unbalanced
                    parent=RL_Rotation(parent);
                }
            }
            break;
        }
    }
    // if stack is empty means root node is unbalanced do make root as a balanced tree root 
    if (!sta.empty())
    {
         // check balanced root key is less then the ancestor then balance tree is left subtree otherwise right subtree
        AVL_Node *temp2 = sta.top();
        if (parent->key < temp2->key)
        {
            temp2->LChild = parent;
        }
        else
        {
            temp2->RChild = parent;
        }
        
    }
    else
    {
       root = parent;
    }

}

void AVL_Tree::AVL_Delete(int k)
{
    AVL_Node *temp=root,*parent=NULL;
    // stack contain the address of ancestor nodes which comes in path of deleted node 
    stack<AVL_Node*> sta;
    // Search the deleted element 
    // temp contain the address of deleted node 
    while(temp!=NULL)
    {
        
        if(temp->key==k)
        {
            break;
        }
        parent=temp;
        // push the nodes in stack
        sta.push(parent);
        // if deleted key < current node then search in left subtree otherwise search in right subtee
        if(temp->key<k)
        {
            temp=temp->RChild;
        }
        else{
            temp=temp->LChild;
        }
    }
    // element not found in tree
    if(temp==NULL)
    {
        cout<<"Element not found :\n";
        return;
    }
    AVL_Node *child;
    // case 1: node have both children 
    if(temp->LChild!=NULL && temp->RChild!=NULL)
    {
        parent=temp;
        sta.push(parent);
        // find succesor and swap with delete item  
        child=temp->RChild;
        // finding succesor of deleted node 
        while(child->LChild!=NULL)
        {
            parent=child;
            sta.push(parent);
            child=child->LChild;
        }
        // copy the succesor key to deleted key and make deleted key as succsor key
        temp->key=child->key;
        temp=child;
    
    }
    // deleted key must have only one child or no child 
    // find child of deleted node  
    if(temp->LChild!=NULL)
    {
        child=temp->LChild;
    }
    else
    {
        child=temp->RChild;
    }
    // parent is null means deleted node is root node  
    if(parent==NULL)
    {
        root=child;
    }
    else
    {
        // temp is deleted node 
        // Now child  of parent node is child of deleted node  
        if(parent->LChild==temp)
        {
            parent->LChild=child;
        }
        else{
            parent->RChild=child;
        }
        // Due to deletion ancestor nodes may be unbalanced 
        while(!sta.empty())
        {

            parent=sta.top();
            sta.pop();
            // if deleted node is from left sutree then balance factor decrease 
            if(temp->key<parent->key)
            {
                parent->bf--;
                if(parent->bf==-1)  // means tree is balances so no need to further check
                    break;
            }
            // if deleted node is from right subtree then balance factor increases 
            else{
                parent->bf++;
                if(parent->bf==1)   // means tree is balances so no need to further check
                    break;
            }
            if(parent->bf!=0)                   // means bf is either 2 or -2
            {

                if(parent->bf==2)        //we need to balance the node and left subtree 
                {
                    child=parent->LChild;
                }
                else{
                    child=parent->RChild;
                }
                if(child->bf==0)        // child node have balance factor 0 means left subtree and right subtree have same height
                {
                    // menas balance the node and right subtree 
                    if(parent->bf==-2)
                    {
                        AVL_Node *right=parent->RChild;
                        parent->RChild=right->LChild;
                        right->LChild=parent;
                        parent=right;
                        parent->bf=1;
                        parent->LChild->bf=-1;
                    }
                    // balance the node and right subtree
                    else{
                        AVL_Node *left=parent->LChild;
                        parent->LChild=left->RChild;
                        left->RChild=parent;
                        parent=left;
                        parent->bf=-1;
                        parent->RChild->bf=1;
                    }
                    if(!sta.empty())
                    {
                        AVL_Node *a=sta.top();
                        if(a->key<parent->key)
                            a->RChild=parent;
                        else{
                            a->LChild=parent;
                        }
                    }
                    else{
                        root=parent;
                    }
                    break;
                }
                // 
                else{
                    // if balance factor of parent and child have same sign then single 
                    //rotation required otherwise double rotation required 
                    if(parent->bf>0)
                    {
                        if(child->bf>0)
                        {
                            // LL unbalance so single rotation
                            parent=LL_Rotation(parent);
                        }
                        else{
                            // LR unbalance so double rotation 
                            parent=LR_Rotation(parent);
                        }// combine rotated tree with main tree
                        if(!sta.empty())
                        {
                            if(sta.top()->key<parent->key)
                            {
                                (sta.top())->RChild=parent;
                            }
                            else{
                                sta.top()->LChild=parent;
                            }
                        }
                        else{
                            root=parent;
                        }
                    }
                    else{
                        if(child->bf<0)
                        {
                            // RR unbalanced so single rotation
                            parent=RR_Rotation(parent);
                        }
                        else{
                            // RL unbalanced so double rotation 
                            parent=RL_Rotation(parent);
                        }

                        // combine rotated tree with main tree
                        if(!sta.empty())
                        {
                            if(sta.top()->key<parent->key)
                            {
                                (sta.top())->RChild=parent;
                            }
                            else{
                                sta.top()->LChild=parent;
                            }
                        }
                        else{
                            root=parent;
                        }
                    }
                }

            }
            child=parent;
        }
        delete temp;
    }


}


// Destructor 
AVL_Tree::~AVL_Tree()
{
    // Create a queue which store pointer for level order traversal
    queue<AVL_Node*> qu;
    // push root node in queue 
    qu.push(root);
    // queue is empty means no pointer is left for deleted 
    while(!qu.empty())
    {
        // pop front element of queue and find the left and righ subtree if child exist then push it in 
        // queue and delete the front element 
        AVL_Node *temp=qu.front();
        qu.pop();
        if(temp->LChild!=NULL)
        {
            qu.push(temp->LChild);
        }
        if(temp->RChild!=NULL)
        {
            qu.push(temp->RChild);
        }
        delete temp;
    }
    
}



int main()
{
    cout<< "Gaurav Kumar \nRoll-Number- 214101018\nMain Menu :\n";
    AVL_Tree tree1;
    
    int choice;
    int a[]= {20,50,100,10,25,150,75};
    int n=sizeof(a)/sizeof(int);
   for(int i=0;i<n;i++)
    {
        tree1.AVL_Insert(a[i]);
    }
    tree1.print_tree();
    cout<<"\n";

    cout<<"1. Insert\n";
    cout<<"2. Delete\n";
    cout<<"3. Search\n";
    cout<<"4. Print the tree :\n";
    cout<<"0. Exit\n";
    do{
        cout<<"Enter your choice :";
        cin>>choice;
        int number,n;
        bool a=0;
        char filename[20];
        switch (choice)
        {
            case 1:
                    cout<<"Enter inserted element :";
                       cin>>number;
                        tree1.AVL_Insert(number);
                    
                    cout<<"New tree inorder sequence is :";
                    tree1.print_tree();
                     cout<<"\n";
        
                break;
            case 2:
                tree1.print_tree();
                cout<<"Delete Number :";
                cin>>number;
                tree1.AVL_Delete(number);
                cout<<"After deletion inorder sequence is :";
                tree1.print_tree();
                cout<<"\n";
        
                break;
            case 3:
                cout<<"Search Element :";
                cin>>number;
                a=tree1.AVL_Search(number);
                if(a==true)
                {
                    cout<<"Element is found in tree :\n";
                }
                else{
                    cout<<"Element Not found in tree :\n";
                }
                break;
            case 4:
                cout<<"Enter File name :";
                cin>>filename;
                tree1.AVL_Print(filename);
                cout<<"png file created :\n";

                break;
            default:

                break;
        }


    }while(choice!=0);
    /**/
    
}
