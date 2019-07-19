#include "dFunct.h"
#define SIZE 5000

char *pass = "GVSU";
FILE *systm;

/* This method is used to retrieve this DMS password from user.
   @return true - password correct
   @return false - password incorrect 
   @param passent - user entered password*/
bool psswrd(char *passent){
  bool lock;
  if(strcmp(passent,pass)==0){
    lock = true;
  }
  else{
    printf("\n Invalid password entered.. access denied\n");
    lock = false;
  }
  return lock;
}

/*This method is used to greet the user and continously display the menu of    this DMS.*/
void welcome(){
  printf("\n------------------------------------------------------------\n");
  printf("        Welcome to Diary Management System\n\n");
  printf("1. CREATE Diary Entry               2. VIEW Diary Entry\n");
  printf("3. DELETE Diary Entry               4. LIST Diary Entry\n");
  printf("                      5. EXIT DMS\n");
  printf("\n------------------------------------------------------------\n");
}

/*This method is used to create the file of a new diary entry for this 
  DMS. 
  @param fName- filename*/
void create(char *fName){
  int len;

  // Checks for valid txt filename. String cannot be null and must end 
  // with .txt.
  if( (len=strlen(fName)>3) && (strcmp(len+fName-4, ".txt")) ){
    systm=fopen(fName, "w");
    fclose(systm);
  }
  else{
    // If filename invalid system exit
    printf("\nTXT FILENAME INVALID... try again\n");
  }

}

/*This method is used to add the entry created for this DMS, to the created    file.
  @param fName - filename*/
void add(char* fName){
  time_t now;
  char e[SIZE];
  int c = 0;
  
  // Open the file create to begin adding entry
  systm = fopen(fName, "w");

  // Throw error if filename cannot be opened
  if(systm == NULL){
    printf("\nUnable to open file: '%s' .\n", fName);
    perror("Error");
  }else{
    
  // Add the date and time of current entry creation to file before entry
  time(&now);
  fprintf(systm, "Entry Date: %s", ctime(&now));

  // Add the actual diary entry
  fprintf(systm, "Entry: \n\n");
  fgets(e, sizeof(e), stdin);
  fputs(e, systm);

  // Close file when done
  fclose(systm);
  }

}

/*This method is used to view entries within this DMS by file name.
  @param fName - file name*/ 
void view(char *fName){
  
  char ch;
  int count = 0;
  systm = fopen(fName, "r");

  // Throw error if filename cannot be opened and exit
  if(systm == NULL){
    printf("\nUnable to open file: '%s' .\n", fName);
    perror("Error");
   
  }else{

  // Else print the requested entry for user to view
  printf("\nDisplaying requested entry... \n");
  printf("==============================================================\n\n");
  while( ( ch = fgetc(systm) ) != EOF ){
    printf("%c", ch);
  }
  printf("\n\n");
  printf("==============================================================\n\n\n");

  // Close the file after reading
  fclose(systm);
  }
     
}

/*This method prompts user for file name to be deleted from this DMS, then     deletes file inputed.
  @param fName - file name*/
void del(char *fName){

// Check if file exists
if(access(fName, F_OK) != -1){
  // Check remove status
  if(remove(fName)){
     printf("\nUnable to remove file: %s\n", fName);
  }else{
    printf("\nFile: %s successfully deleted\n", fName);
  }

}else{
    perror("Error");
 }
}

/*This method is used to display a list of all available files
  within this DMS folder*/
void list(){

  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  

  if(d){
    printf("\nDisplaying all files... \n");
    printf("==============================================================\n\n");
    while ((dir = readdir(d)) != NULL) {
      int length = strlen(dir->d_name);
      if(strncmp(dir->d_name + length -4, ".txt", 4) ==0){
        printf("%s\n", dir->d_name); 
      }
    }
    printf("\n");
    printf("==============================================================\n\n\n");
    closedir(d);        
  }

}
