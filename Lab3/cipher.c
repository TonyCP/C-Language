#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Encrypt-Decrpyt lab */

char encrypt(char ch, int k);

int main(int argc, char* argv[])
{  
	int choice, i, len;
	int *keyArr;
	char ch; 
	char *key;
	FILE *fin, *fout;

	if (argc != 5)
	{
		printf ("Usage: cipher option key infile, outfile\n");
		printf ("Option 1 for encryption and 2 for decryption");
		exit(1);
	}
	
	choice = atoi(argv[1]);
	key = argv[2];
	len = strlen(key);
	keyArr = (int *) malloc(len * sizeof(int));

	for( i = 0; i < len; i++)
	{
	 	// Check for decryption choice
		if(choice == 2) {
			keyArr[i] = -(key[i]) +64;

		}else {
			keyArr[i] = key[i] -64;

		}
	}


	// Data file to be encrypted/decrypted //
	fin = fopen(argv[3], "r");
	// Data file to be encrypted/decrypted //
	fout = fopen(argv[4], "w");

	if(fin == NULL || fout == NULL) 
	{
		printf("File could not be opened\n");
		exit(1);
	}

	int x = 0;
	while( fscanf(fin, "%c", &ch) != EOF ) {
		fprintf(fout, "%c", encrypt(ch, keyArr[x%len]));
		x++;
	}

	fclose(fin);
	fclose(fout);
	return 0;
}

// Encryption function //
char encrypt(char ch, int k)
{

	if ( k < 0 )
		k = k + 26;

	if ( isupper(ch) )
		return (ch - 'A' + k) % 26 + 'A';
	
	if ( islower(ch) )
		return (ch - 'a' + k) % 26 + 'a';
	
	return ch;
}
