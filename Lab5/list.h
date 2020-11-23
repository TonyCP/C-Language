/* Define a structure and functions to implement a linear linked list */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

struct person {
    char first[MAX];
    char last[MAX];
    int id;
    struct person *next;
};

typedef struct person person;

// Make node & return pointer to the node //
person *makeNode();

// Create list //
person *create();

// Display list //
void display(person *l);

// Append node to the tail of list & return updated list //
person *append(person *l, person *p);

// Save list: save the data to a file //
void save(person *l, char fn[]);

// Load list: load data from a file, append to person list, return list //
person *load(person *l, char fn[]);

// Build person node //
person *buildNode(char fname[], char lname[], int id);

// Count list //
int count(person *l);

// Destroy list //
void destroy(person **l);

// Find person by id //
person *find (person *l, int id);

// Insert person in list after person id //
void insertAfter(person *l, int id, person *p);

// Delete person node by id //
void deleteNode(person **l, int id);

// Check for unique id //
int isUniqueID(person *l, person *p);
