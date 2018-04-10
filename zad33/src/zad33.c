/*
 ============================================================================
 Name        : zad33.c
 Author      : mc
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int data;
	int key;

	struct node *next;
	struct node *prev;
};

//this link always point to first Link
struct node *head = NULL;

//this link always point to last Link
struct node *last = NULL;

struct node *current = NULL;

//is list empty
bool isEmpty() {
	return head == NULL;
}

int length() {
	int length = 0;
	struct node *current;

	for (current = head; current != NULL; current = current->next) {
		length++;
	}

	return length;
}

//display the list from last to first
void display() {

	//start from the last
	struct node *ptr = last;

	//navigate till the start of the list
	printf("\n[ ");

	while (ptr != NULL) {

		//print data
		printf("(%d,%d) ", ptr->key, ptr->data);

		//move to next item
		ptr = ptr->prev;

	}

}

//insert link at the first location
void insert_index(int key, int data) {

	//create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->key = key;
	link->data = data;

	if (isEmpty()) {
		//make it the last link
		last = link;
	} else {
		//update first prev link
		head->prev = link;
	}

	//point it to old first link
	link->next = head;

	//point first to new first link
	head = link;
}

//insert link at the last location
void insertLast(int key, int data) {

	//create a link
	struct node *link = (struct node*) malloc(sizeof(struct node));
	link->key = key;
	link->data = data;

	if (isEmpty()) {
		//make it the last link
		last = link;
	} else {
		//make link a new last link
		last->next = link;

		//mark old last node as prev of new link
		link->prev = last;
	}

	//point last to new last node
	last = link;
}

//delete a link with given key

struct node* delete(int key) {

	//start from the first link
	struct node* current = head;
	struct node* previous = NULL;

	//if list is empty
	if (head == NULL) {
		return NULL;
	}

	//navigate through list
	while (current->key != key) {
		//if it is last node

		if (current->next == NULL) {
			return NULL;
		} else {
			//store reference to current link
			previous = current;

			//move to next link
			current = current->next;
		}
	}

	//found a match, update the link
	if (current == head) {
		//change first to point to next link
		head = head->next;
	} else {
		//bypass the current link
		current->prev->next = current->next;
	}

	if (current == last) {
		//change last to point to prev link
		last = current->prev;
	} else {
		current->next->prev = current->prev;
	}

	return current;
}

bool insertAfter(int key, int newKey, int data) {
	//start from the first link
	struct node *current = head;

	//if list is empty
	if (head == NULL) {
		return false;
	}

	//navigate through list
	while (current->key != key) {

		//if it is last node
		if (current->next == NULL) {
			return false;
		} else {
			//move to next link
			current = current->next;
		}
	}

	//create a link
	struct node *newLink = (struct node*) malloc(sizeof(struct node));
	newLink->key = newKey;
	newLink->data = data;

	if (current == last) {
		newLink->next = NULL;
		last = newLink;
	} else {
		newLink->next = current->next;
		current->next->prev = newLink;
	}

	newLink->prev = current;
	current->next = newLink;
	return true;
}

int main() {
	insert_index(1, 10);
	insert_index(2, 20);
	insert_index(3, 30);
	insert_index(4, 40);
	insert_index(5, 50);
	insert_index(6, 60);
	insert_index(7, 70);
	insert_index(8, 80);
	insert_index(9, 90);
	insert_index(10, 100);

	printf("\nLista przed: ");
	display();

	printf("\n");

	printf("\nList wyciecie 5 i 7 : ");
	delete(5);
	delete(7);
	display();
}
