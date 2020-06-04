# Documentation for the functions used in Naive-CFS

* The project code is available entirely in the `src` folder
* There are two files there - `rb_tree.hpp` contains implementation logic of the red black tree data structure, and `scheduler.cpp` provides an interface to use this data structure in the scheduler backend.
* A functional programming approach is followed and thus all logic is achieved through functions

### Functions
The functions created in `rb_tree.hpp` are documented here:
*  The tree is based on the node data structure. Pointer to `node` is available as `_nodeptr`.
* `NILPTR` is a special node pointer which stores the sentinal null node.
* `search(_nodeptr, int)` takes the root of tree and key to be searched, and returns the `_nodeptr` of the key if found; if not found returns `NILPTR`
* `minimum(_nodeptr)` takes root of tree, and returns a `_nodeptr` to the node containing minimum value
* `maximum(_nodeptr)` takes root of tree, and returns a `_nodeptr` to the node containing maximum value
* `display()` pretty prints the current tree
* `rbinsert(_nodeptr, int)` inserts a key into the tree
* `rbdelete(_nodeptr, int)` deletes a key from the tree
* `rightrotate() and leftrotate()` perform node rotation to achieve tree validity as per rules.
* `rbinsertfixup()` performs color flipping to achieve tree validity as per rules.

`scheduler.cpp` merely provides an interface to these functions. The user can call the functions here the way the scheduler would. For more details on such usage, refer to `README.md`