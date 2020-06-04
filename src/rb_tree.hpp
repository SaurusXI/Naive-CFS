#include <tuple>
#include <iostream>
using namespace std;

enum class Color {
    RED,
    BLACK
};

enum class ProblemChild {
    LEFT,
    RIGHT,
    NONE
};


// --------------------------- DEFINTIONS ---------------------------

class Node {
    Color color;
    Node* lchild;
    Node* rchild;
    int val;
    bool is_null = false;

public:
    Node() {
        color = Color::BLACK;
        is_null = true;
    }
    Node(int val) {
        color = Color::RED;
        lchild = new Node();
        rchild = new Node();
        this->val = val;
        is_null = false;
    }
    
    friend class RB_tree;
};

// type containing (is subtree valid, which grandchild is conflicting, subtree head after mutation) 
typedef tuple<bool, ProblemChild, Node*> validity_info;

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
    validity_info recursively_validate(Node*);
    Node* color_flip(Node*);
    Node* rotate(Node*, ProblemChild, ProblemChild);

public:
    RB_tree() {
        cout << 'a';
        root = new Node();
    }
    void insert(int);
    void validate();
};



// --------------------------- METHODS ---------------------------

// Mutate

Node* RB_tree::color_flip(Node* current) {
    current->lchild->color = Color::BLACK;
    current->rchild->color = Color::BLACK;
    current->color = Color::RED;

    return current;
}

Node* RB_tree::rotate(Node* current, ProblemChild problem_child, ProblemChild problem_grandchild) {
    if (problem_child == ProblemChild::LEFT) {
        if (problem_grandchild == ProblemChild::LEFT) {
            Node* head = current->lchild;
            Node* no_problem_grandchild = head->rchild;
            
            current->lchild = no_problem_grandchild;
            head->rchild = current;

            return head;
        }

        else if (problem_grandchild == ProblemChild::RIGHT) {
            Node* head = current->lchild->rchild;
            Node* problem_child_node = current->lchild;

            Node* temp1 = head->lchild;
            Node* temp2 = head->rchild;

            head->lchild = problem_child_node;
            head->rchild = current;
            problem_child_node->rchild = new Node();
            current->lchild = new Node();

            delete temp1;
            delete temp2;

            return head;
        }
    }

    else if (problem_child == ProblemChild::RIGHT) {
        if (problem_grandchild == ProblemChild::LEFT) {
            Node* head = current->rchild->lchild;
            Node* problem_child_node = current->rchild;

            Node* temp1 = head->lchild;
            Node* temp2 = head->rchild;

            head->rchild = problem_child_node;
            head->lchild = current;
            current->rchild = new Node();
            problem_child_node->lchild = new Node();

            delete temp1;
            delete temp2;

            return head;
        }

        else if (problem_grandchild == ProblemChild::RIGHT) {
            Node* head = current->rchild;
            Node* no_problem_grandchild = head->lchild;

            current->rchild = no_problem_grandchild;
            head->rchild = current;
            return head;
        }
    }
}

// Enforce validity

void RB_tree::validate() {
    if (root->is_null)
        return;

    if (!root->lchild->is_null) 
        recursively_validate(root->lchild);
    if (!root->rchild->is_null) 
        recursively_validate(root->rchild);

    if (root->color == Color::RED) 
        root->color = Color::BLACK;
}

validity_info RB_tree::recursively_validate(Node* current) {
    if (!current->lchild->is_null) {
        auto l_validity = recursively_validate(current->lchild);
        current->lchild = get<2>(l_validity); 

        if (!get<0>(l_validity)) {
            
            if (current->rchild->color == Color::RED) {
                current = color_flip(current);
            }
            else if(current->rchild->color == Color::BLACK) {
                current = rotate(current, ProblemChild::LEFT, get<1>(l_validity));
            }
        }
    }
    if (!current->rchild->is_null) {
        auto r_validity = recursively_validate(current->rchild);
        current->rchild = get<2>(r_validity); 

        if (!get<0>(r_validity)) {

            if(current->lchild->color == Color::RED) {
                current = color_flip(current);
            }
            else if (current->lchild->color == Color::BLACK) {
                current = rotate(current, ProblemChild::RIGHT, get<1>(r_validity));
            }    
        }
    }
    
    if (current->color == Color::RED && current->lchild->color == Color::RED) {
        validity_info info(false, ProblemChild::LEFT, current);
        return info;
    }
    if (current->color == Color::RED && current->rchild->color == Color::RED) {
        validity_info info(false, ProblemChild::RIGHT, current);
        return info;
    }

    validity_info info(true, ProblemChild::NONE, current);
    return info;
}

// Insertion

void RB_tree::insert(int n) {
    if (root->is_null) {
            Node* temp = root;
            root = new Node(n);
            root->color = Color::BLACK;
            delete temp;
        }

    else {
        recursively_insert(n, root);
        validate();
    }
}

void RB_tree::recursively_insert(int n, Node* current) {
    Node* nextnode;                 // Next candidate node for recursion
    bool stop_here;                   // If next candidate is null, stop recursing
    
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
