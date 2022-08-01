using namespace std;
class AVL_Node
{
private:
    int key;
    int bf; // balance factor bf = height(left subtree) – height(right subtree)
    AVL_Node *LChild, *RChild;
    friend class AVL_Tree;

public:
    AVL_Node();
    AVL_Node(int k)
    {
        key = k;
        bf = 0;
        LChild = NULL;
        RChild = NULL;
    }
};
class AVL_Tree
{
private:
    AVL_Node *root;

public:
    AVL_Tree();
    AVL_Tree(const AVL_Tree &T);
    AVL_Tree &operator=(const AVL_Tree &T);
    void AVL_Insert(int k);
    void AVL_Delete(int k);
    bool AVL_Search(int k);
    void AVL_Print(const char *filename);
    ~AVL_Tree();
    AVL_Node *LL_Rotation(AVL_Node *node);
    AVL_Node *RR_Rotation(AVL_Node *node);
    AVL_Node *LR_Rotation(AVL_Node *node);
    AVL_Node *RL_Rotation(AVL_Node *node);
    
    void print_tree();
    void traverse(AVL_Node *node,FILE *fp);

    void traverse2(AVL_Node *node);
};
