// --------------------------- DEFINTIONS ---------------------------

enum class Color {
    RED,
    BLACK
};

class Node {
    Color color;
    Node* lchild;
    Node* rchild;
    int val;
    bool is_null = false;

public:
    Node(int val) {
        color = Color::RED;
        lchild = new NullNode();
        rchild = new NullNode();
        this->val = val;
    }
    
    friend class RB_tree;
};

class NullNode: public Node {
    Color color;
    bool is_null = true;

public:
    NullNode() {
        color = Color::BLACK;
    }
};

class RB_tree {
    Node* root;
    void recursively_insert(int, Node*);
    bool recursively_validate(Node*);

public:
    RB_tree() {
        root = new NullNode();
    }
    void insert(int);
    void validate();
};




// --------------------------- METHODS ---------------------------


void RB_tree::insert(int n) {
    if (root->is_null) {
            Node* temp = root;
            root = new Node(n);
            root->color = Color::BLACK;
            delete temp;
        }

    else
        recursively_insert(n, root);
}

void RB_tree::recursively_insert(int n, Node* current) {
    Node* nextnode;                 // Next candidate node for recursion
    bool stop_here;                   // If selected candidate is null, stop recursing
    
    if (n <= current->val) {
        nextnode = current->lchild;
        if (current->lchild->is_null)
            stop_here = true;
        else
            stop_here = false;
    }
    else {
        nextnode = current->rchild;
        if (current->rchild->is_null)
            stop_here = true;
        else
            stop_here = false;
    }


    if (stop_here) {
        Node* temp = nextnode;
        nextnode = new Node(n);
        delete temp;
    }
    else
        recursively_insert(n, nextnode);
}

void RB_tree::validate() {
    
}