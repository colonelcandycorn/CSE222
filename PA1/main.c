/*
	Sarah Dylan 01/14/2023 CSE222

	This program is a demonstration of the Linked List ADT. The implementation
	of the list is abstracted away from the user. The user only has to worry about
	5 commands they can use, and the data they want to store. The implementation of
	the list is in functions.c. The program calls the init function to create a
	'empty' list. It also initializes several variables: one char array to store
	any command line input, a char to store the letter of the command they want,
	another char array to store the data they want to store. IsRunning just makes
	the while loop go continously until the user exits. Error just keeps track of
	cases where there is failure. The program has a large switch case which handles
	all the commands they could enter. The data is stored in order according to strcmp.
	No duplicates are allowed in the main program. 
*/



#include "main.h" // function declarations
#include <string>
#define MAX_STR 100 //used to store command line input

using namespace std;
int main(void) {

	//initialize variables

	char input[MAX_STR];
	char choice;
	char data[20];
	bool isRunning=1;
	int error;

	//DataNode is a struct consisting on a char array and a pointer to a datanode
	DataNode *list = init();

	//continuous loop so user can keep entering in data
	// only becomes false when user types x
	while (isRunning) {
		data[0] = '\0'; // empty out data 
		printf(">");

		//fgets to store data from stdin
		// which then gets parsed by sscanf into a single char and a char array

		fgets(input, MAX_STR, stdin);
		error = sscanf(input, "%c%s", &choice, data);
		// this is to stop people from doing i, d, s command without a string
		// error will equal one if they don't so we check to if choice is p or x
		// if it's neither then we set choice to some arbitrary letter so we get the default
		// switch case
		if (error != 2 && (choice != 'p' && choice != 'x')) choice = 'e';
		switch (choice) {
			// the user wants to insert data
			// uses search first to confirm whether the node is in the list
			// also checks if the heap is full
			case 'i':
				if ((error = search(list, data))) {
					puts("NODE ALREADY IN LIST");
				} else if ( !(error = add(list, data)) ) {
					puts("HEAP FULL");
				} else {
					puts("SUCCESS");
				}
				break;

			// the user wants the list printed which outputed on a single line seperated
			// by spaces

			case 'p':
				print(list);
				break;

			//the user wants to see if they already put something in the list
			case 's':
				if ((error = search(list, data))) {
					puts("FOUND");
				} else {
					puts("NOT FOUND");
				}
				break;

			// user wants to delete something from the list
			// the delete function will return with 0 if the item isn't in the list
			case 'd':
				if ((error = myDelete(list, data))) {
					puts("SUCCESS");
				} else {
					puts("NODE NOT FOUND");
				}
				break;
			//deallocates all the malloc'ed memory and exits the loop
			case 'x':
				cleanup(list);
				isRunning=0;
				break;
			// default case means they typed something other than the 5 acceptable letters
			// so it reminds the user of valid commands
			default :
				puts("Valid Commands:");
				puts("i data (insert data), p (print list), s data (search data)");
				puts("d data (delete data), x (exit program)");
		}
	}
}
