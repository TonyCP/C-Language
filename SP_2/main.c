/* This is a simple C program. The program will check whether an alphabet 
is a vowel or a constant. */
#include <stdio.h>
#include <string.h>

int main() {
  // User input //
  char* alpha;
  // Loop counter //
  int i;

  // Requests user input at commmand line //
  printf("\nPlease enter the character(s) of the alphabet in string format 
         to check for vowels or constants: ");
  scanf("%s", alpha);

  // Loops the length of character input //
  for(i = 0; i < strlen(alpha); i++){
    // Checks for vowels (a, e, i, o, u) but not (y) //
    if(alpha[i]=='a' || alpha[i]=='A' || alpha[i]=='e' || alpha[i]=='E' || 
       alpha[i]=='i' || alpha[i]=='I' || alpha[i]=='o' || alpha[i]=='O' || 
       alpha[i]=='u' || alpha[i]=='U'){

      // Informs user of vowels found within input //
      printf("\nVowel Found: %c\n", alpha[i]);
    }

    else
    // Informs user of constants found within input //
    printf("\nConstant Found: %c\n", alpha[i]);
  }

  return 0;
}
