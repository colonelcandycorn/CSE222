#include "main.h"
#include <string>
#include <stdbool.h>
#define MAX_STR 100

using namespace std;
int main(void) {
	char input[100];
	char choice;
	char data[20];
	bool isRunning=true;
	int error;
	DataNode *list = init();

	while (isRunning) {
		printf(">");
		fgets(input, MAX_STR, stdin);
		sscanf(input, "%c%s", &choice, data);
		switch (choice) {
			case 'i':
				if ((error = search(list, data))) {
					puts("NODE ALREADY IN LIST");
				} else if ( !(error = add(list, data)) ) {
					puts("HEAP FULL");
				} else {
					puts("SUCCESS");
				}
				break;
			case 'p':
				print(list);
				break;
			case 's':
				if ((error = search(list, data))) {
					puts("FOUND");
				} else {
					puts("NOT FOUND");
				}
				break;
			case 'd':
				if ((error = myDelete(list, data))) {
					puts("SUCCESS");
				} else {
					puts("NODE NOT FOUND");
				}
				break;
			case 'x':
				cleanup(list);
				isRunning=false;
				break;
			default :
				puts("Valid Commands:");
				puts("i data (insert data), p (print list), s data (search data)");
				puts("d data (delete data), x (exit program)");
		}
	}
}
