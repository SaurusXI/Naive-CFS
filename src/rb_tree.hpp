#ifndef _TREE_
#define _TREE_
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
 using namespace std;

#define RED		1
#define BLACK	2
 
struct node {
	int key;
	struct node *left, *right, *p;
	int color;
};
 
typedef struct node *_nodeptr;
struct node NIL;
_nodeptr NILPTR = &NIL;
 
_nodeptr search(_nodeptr root, int k) {
	if (root == NILPTR || root->key == k)
		return root;
	if (k < root->key)
		return search(root->left, k);
	else
		return search(root->right, k);
}
 
_nodeptr minimum(_nodeptr root) {
	while (root->left != NILPTR)
		root = root->left;
	return root;
}
 
_nodeptr maximum(_nodeptr root) {
	while (root->right != NILPTR)
		root = root->right;
	return root;
}
 
_nodeptr successor(_nodeptr root, int x) {
	_nodeptr temp = search(root, x);
	if (temp == NILPTR) {
		printf("%d not in tree\n", x);
		return temp;
	}
	if (temp->right != NILPTR)
		return minimum(temp->right);
	_nodeptr y = temp->p;
	while (y != NILPTR && temp == y->right) {
		temp = y;
		y = y->p;
	}
	return y;
}
 
_nodeptr predecessor(_nodeptr root, int x) {
	_nodeptr temp = search(root, x);
	if (temp == NILPTR) {
		printf("%d not in tree\n", x);
		return temp;
	}
	if (temp->left != NILPTR)
		return maximum(temp->left);
	_nodeptr y = temp->p;
	while (y != NILPTR && temp == y->left) {
		temp = y;
		y = y->p;
	}
	return y;
}

void display(const string& prefix, _nodeptr current_node, bool is_left) {
    if (current_node != NILPTR) {
        cout << prefix;
        printf((is_left? "├──": "└──"));
        string c = "black";
        if(current_node->color == RED) 
            c = "red";
        cout << current_node->key << ',' << c << endl;
        display( prefix + (is_left ? "│   " : "    "), current_node->left, true);
        display( prefix + (is_left ? "│   " : "    "), current_node->right, false);
    }
}


void inorder(_nodeptr x) {
	if (x != NILPTR) {
		inorder(x->left);
		printf("%d ", x->key);
		inorder(x->right);
	}
}
 
void leftrotate(_nodeptr *treeroot, _nodeptr x) {
	_nodeptr y = x->right;
	x->right = y->left;
	if (y->left != NILPTR)
		y->left->p = x;
	y->p = x->p;
	if (x->p == NILPTR)
		*treeroot = y;
	else if (x->p->left == x)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}
 
void rightrotate(_nodeptr *treeroot, _nodeptr y) {
	_nodeptr x = y->left;
	y->left = x->right;
	if (x->right != NILPTR)
		x->right->p = y;
	x->p = y->p;
	if (y->p == NILPTR)
		*treeroot = x;
	else if (y->p->left == y)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}
 
void rbinsertfixup(_nodeptr *treeroot, _nodeptr z) {
	while (z->p->color == RED) {
		if (z->p == z->p->p->left) {
			_nodeptr y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->right) {
					z = z->p;
					leftrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				rightrotate(treeroot,z->p->p);
			}
		}
		else {
			_nodeptr y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else {
				if (z == z->p->left) {
					z = z->p;
					rightrotate(treeroot,z);
				}
				z->p->color = BLACK;
				z->p->p->color = RED;
				leftrotate(treeroot,z->p->p);
			}
		}
	}
	(*treeroot)->color = BLACK;
}
 
void rbinsert(_nodeptr *treeroot, int z) {
	_nodeptr Z = (_nodeptr) malloc(sizeof(struct node));
	Z->key = z;
	_nodeptr y = NILPTR;
	_nodeptr x = *treeroot;
	while (x != NILPTR) {
		y = x;
		if (Z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	Z->p = y;
	if (y == NILPTR)
		*treeroot = Z;
	else if (Z->key < y->key)
		y->left = Z;
	else
		y->right = Z;
	Z->left = NILPTR;
	Z->right = NILPTR;
	Z->color = RED;
	rbinsertfixup(treeroot,Z);
}
 
void rbtransplant(_nodeptr *treeroot, _nodeptr u, _nodeptr v) {
	if (u->p == NILPTR)
		*treeroot = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	v->p = u->p;
}
 
void rbdeletefixup(_nodeptr *treeroot, _nodeptr x) {
	while (x != *treeroot && x->color == BLACK) {
		if (x == x->p->left) {
			_nodeptr w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				leftrotate(treeroot,x->p);
				w = x->p->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
			 	if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rightrotate(treeroot,w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				leftrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
		else {
			_nodeptr w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				rightrotate(treeroot,x->p);
				w = x->p->left;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->p;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					leftrotate(treeroot,w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				rightrotate(treeroot,x->p);
				x = *treeroot;
			}
		}
	}
	x->color = BLACK;
}
 
void rbdelete(_nodeptr *treeroot, int z) {
	_nodeptr Z = search(*treeroot, z);
	if (Z == NILPTR) {
		printf("Node to be deleted not found\n");
		return;
	}
	_nodeptr y = Z;
	int yoc = y->color;
	_nodeptr x;
	if (Z->left == NILPTR) {
		x = Z->right;
		rbtransplant(treeroot,Z,Z->right);
	}
	else if (Z->right == NILPTR) {
		x = Z->left;
		rbtransplant(treeroot,Z,Z->left);
	}
	else {
		y = minimum(Z->right);
		yoc = y->color;
		x = y->right;
		if (y->p == Z)
			x->p = y;
		else {
			rbtransplant(treeroot,y,y->right);
			y->right = Z->right;
			y->right->p = y;
		}
		rbtransplant(treeroot,Z,y);
		y->left = Z->left;
		y->left->p = y;
		y->color = Z->color;
	}
	if (yoc == BLACK)
		rbdeletefixup(treeroot,x);
}

void execute(_nodeptr treeroot) {

}
#endif