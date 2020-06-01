enum class Color {
    RED,
    BLACK
};

class Node {
    Color color;
    Node* lchild;
    Node* rchild;

public:
    Node() {
        color = Color::RED;
        lchild = new NullNode();
        rchild = new NullNode();
    }
    
    friend class RB_tree;
};

class NullNode: public Node {
    Color color;

public:
    NullNode() {
        color = Color::BLACK;
    }
};

class RB_tree {
    Node* root;

public:
    RB_tree() {
        root = new Node();
        root->color = Color::BLACK;
    }


};