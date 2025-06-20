#include "Linklist.h"
#include"Book.h"
#include"User.h"

void InitBookLinkList(bookList &L) {// Initialize the link list
	L = (bookList)new book;
	if (L == NULL) {
		exit(1); // Memory allocation failed
	}
	L->next = NULL; // Set the next pointer of the head node to NULL
}
void DeleteBookLinkList(bookList& L) { // Delete the link list
	if (L == NULL) return; // If the list is empty, do nothing
	bookList p = L->next; // Start from the first node
	while (p != NULL) {
		bookList temp = p; // Store the current node
		p = p->next; // Move to the next node
		delete temp; // Delete the current node
	}
	L = NULL; // Set the head pointer to NULL
}
void DeleteUserLinkList(userList& L) { // Delete the link list
	if (L == NULL) return; // If the list is empty, do nothing
	userList p = L; // Start from the first node
	while (p != NULL) {
		userList temp = p; // Store the current node
		p = p->next; // Move to the next node
		delete temp; // Delete the current node
	}
	L = NULL; // Set the head pointer to NULL
}