#include "list.h"
#include <ctype.h>



// Create list &  return pointer to list //
person *create()
{
    return makeNode();
}


// Make node & return pointer to node //
// Return a NULL pointer if failed //
person *makeNode()
{
    person *tmp = (person *) malloc(sizeof(person));
    if (tmp == NULL)
    {
        puts("MakeNode: Memory allocation failed");
        return NULL;
    }

    fflush(stdin);
    printf("Please input first name: ");
    scanf("%s", tmp->first);
    fflush(stdin);
    printf("Please input last name: ");
    scanf("%s", tmp->last);
    fflush(stdin);
    printf("Please input ID:         ");
    scanf("%d", &(tmp->id));
    fflush(stdin);
    tmp->next = NULL;
    return tmp;
}


// Display list //
void display(person *l)
{
	person *tmp = l;
	printf("\n[*********************");

	while(tmp != NULL){
		printf("\n%s %-20s %s %-20s %s %d) ","(First:", tmp->first, "Last:", tmp->last, "ID:",  tmp->id);
		tmp = tmp->next;
	}
	printf("\n*********************]\n");
}


// Check for unique id //
// Yes return 1; Otherwise return 0 //
int isUniqueID(person *l, person *p)
{
    person *tmp = l;
    while(tmp != NULL) {
        if((tmp->id) == (p->id))
            return 0;
        tmp = tmp->next;
    }
    return 1;
}


// Append node to tail of list & return updated list //
person *append(person *l, person *p)
{
	// In case of no list //
	if(l == NULL){
		printf("\nPlease create list before appending..\n");
		return NULL;
	}

	person *tmp = l;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = (person*) malloc(sizeof(person));
	tmp->next = p;
	tmp->next->next = NULL;
	return l;
}


// Save data of current list to file fn //
void save(person *l, char fn[])
{
    FILE *fout = fopen(fn, "w");
    if(fout == NULL) {
        printf("Save: File open failed (%s)\n", fn);
        return;
    }
    person *current = l;
    while(current != NULL) {
        fprintf(fout, "%s %s %d\n", 
                current->first, current->last, current->id);
        current = current->next;
    }
    fclose(fout);
}


// Create person node & return node //
person *buildNode(char fname[], char lname[], int id)
{
    person *p = (person *) malloc(sizeof(person));
    if(p == NULL) {
        puts("BuildNode: Memory Allocation Failed!");
        return NULL;
    }

    strcpy(p->first, fname);
    strcpy(p->last, lname);
    p->id = id;
    return p;
}


// Load data from file fn, append person list, return the resulting list //
person *load(person *l, char fn[])
{
    int id, rt;
    person *head = l;
    char fname[MAX], lname[MAX];
    FILE *fin = fopen(fn, "r");

    if(fin == NULL) {
        printf("InLoad: File open failed (%s)\n", fn);
        return NULL;
    }

    while (1) {
        rt = fscanf(fin, "%s %s %d\n", fname, lname, &id);
        if (rt < 3)
            break;
        if (head == NULL)
            head = buildNode(fname, lname, id);
        else
            append(head, buildNode(fname, lname, id));
    }
    fclose(fin);
    return head;
}


// Count list recursively //
int count (person *l)
{
    if (l == NULL)
        return 0;
    else
        return (1 + count(l -> next));
}


// Destroy list & release memory to system //
void destroy (person **l)
{
    if(!(*l))
        return;
    destroy (&((*l)->next));
    free(*l);
    *l = NULL;
}


// Find person by ID & return person //
person *find (person *l, int id)
{
	// In case of no list //
	if(l == NULL)
		return NULL;

	// Navigate through list //
	person *tmp = l;
	while(tmp->id != id){
		// On the last node //
		if(tmp->next == NULL){
			printf("\n ID NOT FOUND!\n");
			return NULL;
		}else{
			tmp = tmp->next;
		}
	}

	// In case of data found return current node //
	return tmp;
}


// Insert node after person ID //
// Append node if person with ID not found //
void insertAfter(person *l, int id, person *p)
{
    person *tmp = find (l, id);
    if(tmp != NULL) {
        p->next = tmp->next;
        tmp->next = p;
    }
    else
    {
	    append(l, p);
    }
}


// Delete person node & release memory to system //
void deleteNode(person **l, int id)
{
    person * current = *l;
    person * previous = current;
    while(current != NULL) {
        if ((current->id) == id) {
            if(previous == current)  // the first node //
                *l = (current->next);
            else // not the first node //
                previous->next = current->next;
            
            free (current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
