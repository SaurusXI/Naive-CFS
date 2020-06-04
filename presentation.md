# Naive-CFS

Implementation of a CPU scheduler using Red-Black Trees. Similar to the Linux Completely Fair Scheduler (CFS), but not as optimized. <br>

## Motivation
The idea here was to implement the underlying scheduling data structure used in the process scheduler called CFS. A scheduler is responsible for feeding processes to the CPU for execution. Thus a scheduler is critical to the responsiveness and performance of an operating system. A key idea in the evolution of CPU schedulers has been the prevention of **starvation**. <br><br> Starvation is when processes are deprived of execution time by processes that hog the processor. To prevent starvation and reduce average turn around time, the following approch is usually adopted:
* An incoming process is accomodated in an organising data structure
* The data structure organizes processes according to the amount of time the process has already spent in execution. For new processes, this value is 0.
* The scheduler uses this data structure to select the next process to execute
* If a processes reaches the end of its alloted execution time without completing, it is reinserted in this data structure with its new execution time.
<br><br>
Thus selecting a good data structure is important. This leads us to our discussion on the red-black tree data structure-

## Red-Black Tree:
A type of self-balancing binary search tree. <br>
This data structure follows four rules:
1. Every node in BST is either red or black 
2. Root node and leaf nodes (called sentinel nodes, have NULL value) are always black
3. No two red nodes are adjacent to each other
4. Every path from a node to any descendant sentinel node has the same number of black nodes

### Why Red-Black Tree?
A red black tree provides an approximately balanced binary search tree. It is not perfectly balanced like an AVL tree. Therefore search is usually slower in red-black tree when compared to that in AVL tree. <br>
The tradeoff is that by compromising on perfect balance, red-black trees are able to provide faster insertion and deletion. Since operating systems work with an extremely large number of processes, and processors today are fast, fast insertion and deletion are required for the scheduler to keep up. This makes the red-black tree data structure a better candidate for scheduling processes.

![Image of Red-Black Tree](./assets/redblacktree.png?raw=true "Sample Red-Black tree")

### Operations in Red-Black Tree:
The checked processes have been successfully implemented -
- [X] Display
- [X] Search
- [X] Find smallest node
- [X] Find largest node
- [X] Find successor of a node
- [X] Find predecessor of a node
- [X] Insertion
- [X] Deletion

## Scheduler
### Algorithm
Uses the following algorithm (which can be found on [wikipedia](https://en.wikipedia.org/wiki/Completely_Fair_Scheduler#Algorithm)):
1. The leftmost node of the scheduling tree is chosen (as it will have the lowest spent execution time), and sent for execution.
2. If the process simply completes execution, it is removed from the system and scheduling tree.
3. If the process reaches its maximum execution time or is otherwise stopped (voluntarily or via interrupt) it is reinserted into the scheduling tree based on its new spent execution time.
4. The new leftmost node will then be selected from the tree, repeating the iteration.
<br><br>
### Demonstration
The file `src/scheduler.cpp` contains logic for sample scheduler execution. The OS usually tracks the execution time of a process and updates process meta data accordingly for the scheduler to use; for demonstration purposes however, the program executes in the command line and gives the user a number of options to try out (instead of doing everything automatically; after all it doesn't make sense to replace the scheduler in your OS for the sake of demonstration). <br><br>
For demo execution instructions, refer `README.md`
