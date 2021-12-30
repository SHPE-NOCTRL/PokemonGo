#include <thread>
#include "String.h"
#include "pokeQueueNode.h"
#include <iostream>

using namespace std;

int main () {
	
	pokeQueueNode* start = new pokeQueueNode();// A pointer to a new pokeQueueNode() object. start is the address of the new object. &start is the address of the pointer since pointers take space. *star is the new object itself and will not print without operator overloading.
	pokeQueueNode adding;// An object. adding will not print as is without operator overloading. &adding is the address of the object. *adding is not valid as it is not a pointer to an object it is the object.
	pokeQueueNode& ref = adding;// An alias to the start pointer. ref and *start can be treated as the same. &ref prints the same as start. *ref is not valid.
	start->setValue(1);
	cout << start << endl << &start->getNext() << endl << &adding << endl;
	start->setNext(ref);
	cout << start << endl << &start->getNext() << endl << &adding << endl;
	cout << start->getValue() << endl << start->getNext().getValue() << endl;
	adding.setValue(33);
	cout << start->getValue() << endl << start->getNext().getValue() << endl;
	start->~pokeQueueNode();
	cout << start->getValue() << endl << start->getNext().getValue() << endl;
	cout << start << endl << &start->getNext() << endl << &adding << endl;
	//Question: 
	//	What is a best practice for behaviors of the node?

	return 1;
}