# Naive-CFS
An unoptimized implementation of the Linux Completely Fair Scheduler based on Red-Black Trees. For a discussion on the subject, see `presentation.md`

## Demo Execution
1. Clone this repository onto your system by either downloading zip from the button at the top left corner `clone or download` and extracting to `~/Naive-CFS`, or preferably by using git instead:
```bash
git clone https://github.com/SaurusXI/Naive-CFS.git ~/Naive-CFS
```
2. Extract the repo and navigate to the `src` folder in the repo.
```bash
cd ~/Naive-CFS/src
```
3. In the `src` folder, compile the scheduler source file
```bash
g++ scheduler.cpp -o scheduler.out
```
4. Execute the generated binary
```bash
./scheduler.out
```

### Main Commands Explained
While many of the commands demonstrate the underlying the red-black tree data structure, to mimic the behaviour of scheduler, use the options
* `Insert Process by Execution Time` - Allows you to add a process to the waiting queue according to the total time it has already spent being executed in the CPU. For a completely new process, this is time should be entered as 0.
* `Execute next process` - The underlying tree picks the best candidate for execution and executes it according to the execution time you give it.
* `Display current tree` - Displays the current state of the underlying tree. Each node refers to a process, and contains the execution time of the process and the color of the node (red or black). In the output, the **left child is displayed first**. This can be seen in the second example screenshot below, where the children of 10 (2, 12) are displayed with top on top of 12.
* `Delete process from tree` - Allows you to delete a process from the tree according to its execution time. This is done by the scheduler when the process no longer needs to execute and can be safely removed from the waiting queue. 
<br><br> Example usage can be seen in the screenshots below:
![Screen Capture 1](./assets/screenshot1.jpg?raw=True)
![Screen Capture 2](./assets/screenshot2.jpg?raw=True)
![Screen Capture 3](./assets/screenshot3.jpg?raw=True)
