#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LEN 4
/* Repeated Substr lab */


char* strnsub (char *p, int n);

int main()
{
    char line[] = "His textbook was bought from that bookstore";  
    char *p1, *p2;
    int i, e;
    i = 0;
    e = 0;

    p1 = (char*) malloc(5);
    p2 = (char*) malloc(5);
	
    while (i < strlen(line)-5) 	
    {
	p1 = strnsub(line + i, 4);
		
        while (e < strlen(line)-5)	
        {
		p2 = strnsub(line + (4 + e), 4);

            if(strncmp(p1, p2, 4) == 0) 
            {
                printf("The original string is:\n%s\n", line);
                printf("The first substring:  %s\n", strnsub(p1, LEN));
                printf("The second substring: %s\n", strnsub(p2, LEN));
                return 0;
            }
				
            e++;
        }
	e = i;
        i++;
    }
    printf("No repeated patterns of length %d in the following string:\n%s\n",
            LEN, line);
    return 0;
}


// returns a string with the first n characters of string p //
char* strnsub (char *p, int n)
{
    char* result = malloc(n + 1);
    strncpy(result, p, n);
    result[n + 1] = '\0';

    return result;
}
