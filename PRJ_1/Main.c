#include "dFunct.h"

void newEntry();
char *cf;

int main(){
  char *pw;
  char YN, filen[30];
  int choice = 0, chance, i;
//-----------------------------------------------------------------------//
  // Prompt user for password to gain access to this Diary Management
  // System. Only 3 attempts for entry.
  printf("\nWelcome.. Please enter password to gain access: \n");
  fflush(stdin);
  scanf("%s", pw);

  for(chance = 0; chance < 2; chance++){
    if(psswrd(pw)){
     printf("\nACCESS GRANTED!\n");
     break;
    }else{
      printf("\nPlease re-enter your password - 2 attempts remain: \n");
      fflush(stdin);
      scanf("%s", pw);
    }
  }

  if(chance >= 2 && !psswrd(pw)){
    printf("\nACCESS DENIED..SYSTEM EXITING\n");
    exit(EXIT_SUCCESS);
  }

//-----------------------------------------------------------------------//
  // Prompt welcome menu and user options
  do{
    welcome();
    fflush(stdin);
    scanf("%d", &choice);

    switch(choice){
      case 1: // NEW ENTRY
        newEntry();

         // Add entry to file if fname is valid
        if(cf != NULL){
        printf("\nPlease enter text to be added to this entry: \n\n");
        scanf("%d", &i); //used to pause for command line input
        add(cf);
        printf("\n........Entry saved!........\n");
        }
        break;

      case 2: // VIEW ENTRY
        printf("\nView menu options to list all file names.........");
        printf("\nPlease enter an entry name to be viewed: \n");  
        scanf("%s", filen);
        view(filen);
        break;

      case 3: // DELETE ENTRY
        chance = 0;
        printf("\nView menu options to list all file names.........");
        printf("\nPlease enter an entry name to be deleted:\n");

        scanf("%s", filen);
        getchar();
        printf("\nAre you sure you want to delete file: %s ?(Y / N)\n", filen);
        fflush(stdin);

        // 3 attempts for file name entry
        for(chance = 0; chance < 2; chance++){
          scanf("%c", &YN);

          if(YN == 'y' || YN == 'Y'){
            del(filen);
            break;
          }
          if(YN == 'n' || YN == 'N'){
            printf("\nFile deletion canceled..");
            break;
          }
          else{
            printf("\nInvalid option: Y for (yes) or N for (no):\n");
          }
        }
        break;
      
      case 4: // LIST ALL FILE ENTRIES
        list();
        break;

      case 5: // EXIT
      break;

      default:
        printf("\nInvalid option... try again!\n");
     
    }

  }
  while(choice!= 5);
  printf("\nProgram Exiting.........\n");
  exit(EXIT_SUCCESS);
  
  return 0;
}

//-----------------------------------------------------------------------//
void newEntry(){
  char text[20];

  // Set unique dated filename for each entry created
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  strftime(text, sizeof(text)-1, "%m-%d-%Y.txt", t);

  // Check if file exists
  if(access(text, F_OK) != -1){
    printf("\nFile name: %s exists... ", text);
    printf("\nPlease delete existing file to use file name.\n");
    
  }else{
    // Create file using filename
    cf = text;
    create(cf);
    printf("\n........Entry creation success!........\n");
  }

}


