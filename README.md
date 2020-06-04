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

### Main commands
While many of the commands demonstrate the underlying the red-black tree data structure, to mimic the behaviour of scheduler, use the options
* `Insert Process by Execution Time`
* `Execute next process`
* `Display current tree`
<br><br> Example usage can be seen in the screenshots below:
![Screen Capture 1](./assets/screenshot1.jpg?raw=True)
![Screen Capture 2](./assets/screenshot2.jpg?raw=True)
![Screen Capture 3](./assets/screenshot3.jpg?raw=True)
