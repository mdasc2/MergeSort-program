/* Lab 3, Andrew Chow, CS110C.
The purpose of this is to use the mergesort algorithm in to sort a random user entry of numbers using the node class and print back out
the sorted entry of numbers afterward to the user */ 

#include <iostream>
#include <sstream>
#include "Node.h"
using namespace std;
/*
function merges two seperate linked lists into one linked list
pre: 2 ptrs to different linked lists
post: returns a ptr to a combined list of both of them 
*/

template<typename ItemType>
Node<ItemType>* merge( Node<int>*& , Node<int>*& );

/* 
pre: takes in a linked list ptr
post: uses the mergedSort algorithm to sort all the values within the list in numeric order
*/

template<typename ItemType>
void mergeSort(Node<int>*&);

/* Function adds a node to the front of the linked list
pre: takes in a int and a pointer to a linked list
post: puts the int in a node, that is placed in the linked list 
*/
void addNode(Node<int>*&, int);

/* prints the linked list out in order 
pre: takes in a linked list ptr
post: prints the whole list out 
*/
void printList(Node<int>*&);

/* 
pre: takes in 3 linked list ptrs, one is the original, the other two are used to store the two halfs that we split the original into
post: stores the broken halfs into 2 node ptrs passed in.
*/
void splitLinkedList(Node<int>*&, Node<int>*&, Node<int>*&);

int main()
{
	stringstream ss;
	int item;
	string input;


	cout << "Enter numbers to be sorted(w/ a space between each integer): " << endl; 
	getline(cin, input);
	ss << input;

	Node<int> *headPtr = nullptr;
	
	while(ss >> item)
	{
		addNode(headPtr,item);
	}
	
	mergeSort<int>(headPtr);

	cout << "Here are your sorted numbers : " << endl;
	printList(headPtr);

	ss.clear();
	return 0;
}





template<typename ItemType>
void mergeSort(Node<int>*& head)
{
	Node<int> *first = nullptr;
	Node<int> *second = nullptr;
	
	if ( head == nullptr ||  head->getNext() == nullptr)
	return;

	splitLinkedList(head, first, second);
	
	mergeSort<int>(first);
	mergeSort<int>(second);
	
	head = merge<int>(first,second);
}





template<typename ItemType>
Node<ItemType>* merge( Node<int>*& head1, Node<int>*& head2 )
{
	
	Node<int> * mergedCur = nullptr;
	
	if( head1 == nullptr)
		return head2;	
	if (head2 == nullptr)
		return head1;

	if ( head1->getItem() <= head2->getItem() )
	{
		mergedCur = head1;
		head1 = head1->getNext();
		mergedCur->setNext(merge<int>(head1,head2));
		
	}
	else
	{
		mergedCur = head2;
		head2 = head2->getNext();
		mergedCur ->setNext(merge<int>(head1, head2));
	}
	
	head1 = nullptr;
	head2 = nullptr;

	return mergedCur;	


}


void addNode(Node<int>*&headPtrRef, int numbertoadd )
{
	Node<int> *newNode = new Node<int>(numbertoadd);
	newNode->setNext(headPtrRef);
	headPtrRef = newNode;
}


void printList( Node<int>*&headPtrRef)
{
	while(headPtrRef!= nullptr)
	{
		cout << headPtrRef->getItem() << " ";
		headPtrRef = headPtrRef->getNext();
	}

}

void splitLinkedList( Node<int>*& original, Node<int>*& firsthalf, Node<int>*& secondhalf)
{

	Node<int> *track1 = nullptr;
	Node<int> *track2 = nullptr;

	if ( original == nullptr || original->getNext() == nullptr )
	{	firsthalf = original;
		secondhalf = nullptr;
	}
	else
	{
		track2 = original;
		track1 = original->getNext();
		
		while(track1 != nullptr)
		{
			track1 = track1->getNext();
			if (track1 != NULL)
			{	
				track1 = track1->getNext();
				track2 = track2->getNext();	
			}
		}
		firsthalf = original;
		secondhalf = track2->getNext();
		track2->setNext(nullptr);		
	}



} 
