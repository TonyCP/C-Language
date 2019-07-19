#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <dirent.h> 
#include <unistd.h>

/*This method is used to retrieve this DMS password from user.
  @return true - password correct
  @return false - password incorrect 
  @param passent - user entered password*/
bool psswrd(char *passent);

/* This method is used to greet the user and continously display the menu of this DMS. */
void welcome();

/*This method is used to create the file of a new diary entry for this 
  DMS. 
  @param fName- filename*/
void create(char *fName);

/*This method is used to add the entry created for this DMS, to the created    file.
  @param fName - filename*/
void add(char* fName);

/*This method is used to view entries within this DMS by file name.
  @param fName - file name*/ 
void view(char *fName);

/*This method prompts user for file name to be deleted from this DMS, then     deletes file inputed.
  @param fName - file name*/
void del(char *fName);

/*This method is used to display a list of all available files
  within this DMS folder*/
void list();
