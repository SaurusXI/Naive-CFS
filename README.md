# Naive CFS Implementation

Implementation of a CPU scheduler using Red-Black Trees. Similar to the Linux Completely Fair Scheduler (CFS), but not nearly as optimized. <br><br>

### TO-DO
Project is divided in two parts (reflected as two separate C++ modules in source code):
- [ ] Write Red-Black Tree data structure
- [ ] Implement scheduler using data structure

## Red-Black Tree:
A type of self-balancing binary search tree. <br>
This data structure follows four rules:
1. Every node in BST is either red or black 
2. Root node and leaf nodes (called sentinel nodes, have NULL value) are always black
3. No two red nodes are adjacent to each other
4. Every path from a node to any descendant sentinel node has the same number of black nodes

![Image of Red-Black Tree] 
(./assets/redblacktree.png?raw=true "Red-Black Tree")

### Operations in Red-Black Tree:
- [ ] Display
- [ ] Search
- [ ] Check validity
- [ ] Enforce validity
- [ ] Insertion
- [ ] Deletion

## Scheduler
Uses the following algorithm (which can be found on [wikipedia](https://en.wikipedia.org/wiki/Completely_Fair_Scheduler#Algorithm)):
1. The leftmost node of the scheduling tree is chosen (as it will have the lowest spent execution time), and sent for execution.
2. If the process simply completes execution, it is removed from the system and scheduling tree.
3. If the process reaches its maximum execution time or is otherwise stopped (voluntarily or via interrupt) it is reinserted into the scheduling tree based on its new spent execution time.
4. The new leftmost node will then be selected from the tree, repeating the iteration.