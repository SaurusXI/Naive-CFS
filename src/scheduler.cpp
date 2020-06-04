#include <iostream>
#include "rb_tree.hpp"
using namespace std;

int main() {
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK;
	_nodeptr tree = NILPTR;
	int n;
    printf("\nEnter the expected turnaround time of a process (as would be precomputed by scheduler) to see how this CFS would organize processes.");
	while (1) {
		printf("\n1. Insert Process by Execution Time\n2. Search Process by Execution Time\n3. Inorder Walk\n4. Find total execution time of process that will be selected next\n5. Process with maximum execution time\n6. Successor\n7. Predecessor\n8. Delete process from tree\n9. Display current tree\n10. Execute next process\n11. Exit\n");
		scanf("%d", &n);
		if (n == 1) {
			printf("Enter already acquired execution time of incoming process:\n");
			int num;
			scanf("%d", &num);
			rbinsert(&tree, num);
		}
		else if (n == 2) {
			printf("Enter the number to be search\n");
			int num;
			scanf("%d", &num);
			if (search(tree, num) == NILPTR)
				printf("%d not found\n", num);
			else
				printf("%d found\n", num);
		}
		else if (n == 3) {
			inorder(tree);
			printf("\n");
		}
		else if (n == 4)
			printf("%d\n", minimum(tree)->key);
		else if (n == 5)
			printf("%d\n", maximum(tree)->key);
		else if (n == 6) {
			printf("Enter the number whose successor needs to be found\n");
			int num;
			scanf("%d", &num);
			_nodeptr t = successor(tree, num);
			if (t != NULL)
				printf("%d\n", t->key);
		}
		else if (n == 7) {
			printf("Enter the number whose predecessor needs to be found\n");
			int num;
			scanf("%d", &num);
			_nodeptr t = predecessor(tree, num);
			if (t != NULL)
				printf("%d\n", t->key);
		}
		else if (n == 8) {
			printf("Enter the execution time of process to be deleted\n");
			int num;
			scanf("%d", &num);
			rbdelete(&tree, num);
		}
        else if (n == 9) {
            cout << endl;
            display("", tree, false);
        }
		else if (n == 10) {
			int et;
			cout << "Enter the amount of time the next process will execute on CPU for\n";
			cin >> et;
			int min = minimum(tree)->key;
			cout << "Executing process with current total execution time " << min << "\n";
			int new_et = et + min;
			rbdelete(&tree, min);
			cout << "The process has finished executing and now has an execution time of " << new_et << "\n";
			rbinsert(&tree, new_et);
		}
		else 
			break;
	}
	return 0;
}
 