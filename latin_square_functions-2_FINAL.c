/******************************************************************************
 * @file: latin_square_functions.c
 *
 * htnguyen23
 * Huong Nguyen
 * 9080716005
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Huong Nguyen (htnguyen23@wisc.edu)
 * @modified: 11/13/21
 *****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "latin_square_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgprint_latin_square(n, LS) if (DEBUG) { Print_Latin_Square(n, LS); }

/******************************************************************************
 * Data Types and Structures
 *****************************************************************************/

// ADD ANY ADDITIONAL DATA TYPES OR STRUCTSvHERE 

/******************************************************************************
 * Globals
 *****************************************************************************/

extern void Print_Latin_Square(const size_t n, char **latin_square);

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

// function to search for an element in a char array. Returns 0 if not found, and 1 if found
int inArr(char *arrToSearch, int arrSize, char lookFor) {
	for (int i = 0; i < arrSize; i++) {
		//printf("%d vs %d\t", *(arrToSearch+i), lookFor);
		if (*(arrToSearch + i) == lookFor)  {
			//printf("found\n");
			return 1;
		}
	}
	//printf("not found\n");
	return 0;
}

// function to search for the index of an element in a char array. Returns -1 if not found, and index if found
int arri(char *arrToSearch, int arrSize, char lookFor) {
	for (int i = 0; i < arrSize; i++) {
		if (*(arrToSearch + i) == lookFor) 
			return i;
	}
	return -1;
}

void printArr(int *arrToPrint) {
	for (int i = 0; i < sizeof(arrToPrint); i++) {
		printf("%d", *(arrToPrint + i));
	}
}

int verifyRow(int arrSize, char *ls_row) {
	// iterate through the array to add the char to a "set" array (no repeated elements)
	char *char_ls = malloc(arrSize * sizeof(char));
	//char *char_count = malloc(n * sizeof(int));
	int char_total = 0;
	int char_i = 0;
	char currChar;
	for (int i = 0; i < arrSize; i++) {
		currChar = *(ls_row+i);
		if (!inArr(char_ls, arrSize, currChar)) {
			char_total += 1;
			if (char_total > arrSize) {
				return 0;
			}
			*(char_ls+char_i) = currChar;
			char_i += 1;
		} else {
			return 0;
		}
	}
	// printf("char_ls: %s\n", char_ls);
	free(char_ls);
	char_ls = NULL;
	return 1;
}

int verifyCol(int arrSize, char **ls, int iCol) {
	// iterate through the column to add the char to a "set" array (no repeated elements)
	char *char_ls = malloc(arrSize * sizeof(char));
	int char_total = 0;
	int char_i = 0;
	char currChar;
	for (int i=0; i < arrSize; i++) {
		currChar = *(*(ls+i)+iCol);
		if (!inArr(char_ls, arrSize, currChar)) {
			char_total += 1;
			if (char_total > arrSize) {
				return 0;
			}
			*(char_ls+char_i) = currChar;
			char_i += 1;
		} else {
			return 0;
		}
	}
	// printf("char_ls: %s\n", char_ls);
	free(char_ls);
	char_ls = NULL;
	return 1;
}

/******************************************************************************
 * Verification functions
 *****************************************************************************/

/* 
 * This function takes the name of the file containing the latin square
 * and reads in the data to the the latin_square parameter.  
 *
 * There are many approaches that will work to read in the latin square data.
 * In any approach you choose, you will need to do at least the following:
 *     1) open the file 
 *     2) read in the text from the file
 *     3) figure out the dimensions of the latin square (n)
 *     4) reserve memory for the latin_square. This requires 2 steps
 *         4a) reserve an array of pointers to the rows
 *         4b) reserve an array of characters for each row
 *     5) fill in the latin_square data structure 
 *     6) close the file
 *
 * @param filename The name of the file to read in
 * @param latin_square_in A pointer to the latin square variable in main
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 */
void Read_Latin_Square_File(const char *filename, 
                            char ***latin_square_in, 
                            size_t *n) {
	// arr[i][j] is the same as *(*(arr+i)+j)
	// *(t+i) gets the pointer to the row 

    // open the file
	FILE *fp;
	fp = fopen(filename, "r"); // fopen = open file
	if (fp == NULL) {
		// printf("something went wrong - null file\n");
		exit(1);
	}
	char *file_text = malloc(100 * sizeof(char));
	char ch;
	int ichar = 0;
	int newlineFlag = 0;
	int count = 0;
	// use fgetsc to populate char array file_text with each symbol in latin square
	while ((ch = fgetc(fp)) != EOF) {
		*(file_text + ichar) = ch;
		ichar += 1;
		if (ch == '\n')
			newlineFlag = 1;
		if (!newlineFlag)
			count += 1;
	}
	// *n = squareRoot(count);
	*n = count;
	// reserve memory for the latin_square
	*latin_square_in = malloc(*n * sizeof(char *)); // reserve an array of pointers to the rows
	for (int i = 0; i < *n; i++){
		(*((*latin_square_in) + i)) = malloc(*n * sizeof(char)); // reserve an array of characters for each row
	}
	/*
	if ((latin_square_in = malloc(*n * sizeof(char *))) != NULL) {
		printf("made it");
		for (int i=0; i<*n; i++) {
			*(latin_square_in + i) = malloc(*n * sizeof(char));
		}
	}
	*/
	// fill in the latin_square data structure
	int char_i = 0;
	for (int i = 0; i < *n; i++) {
		for (int j = 0; j < *n; j++) {
			if ( (*(file_text+char_i)) == '\n' )
				char_i += 1;
			*(*(*latin_square_in+i)+j) = *(file_text+char_i);
			char_i += 1; 
		}
	}
	fclose(fp); // close file
	free(file_text);
}

/* 
 * This function checks to see that exactly n symbols are used and that 
 * each symbol is used exactly n times.
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
int Verify_Alphabet(const size_t n, char **latin_square) {
    if (latin_square == NULL) {
        printf("Verify_Alphabet - latin_square is NULL\n"); 
        return 0;
    }
	// use parallel arrays to keep track of how many symbols are used and how many times each are used
    	char *char_ls = calloc(n, sizeof(char));
	// printf("after malloc(): char_ls: %s\n", char_ls);
	int char_total = 0;
	int char_i = 0;
	int *char_count = calloc(n, sizeof(int));
	int in = 0;
	char currChar;
	// loop through latin square to collect and count symbols
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			currChar = *(*(latin_square+i)+j);
			if (!inArr(char_ls, n, currChar)) {
				char_total += 1;
				if (char_total > n) {
					printf("%d > %d\n", char_total, n);
					return 0;
				}
				*(char_ls+char_i) = currChar;
				char_i += 1;
			}
			in = arri(char_ls, n, currChar); // arri() gets the index of that elem in the array
			*(char_count+in) += 1;
		}
	}
	for (int i = 0; i < n; i++) {
		if ((*(char_count+i)) != n) {
			return 0;
		}
	}
	free(char_ls);
	free(char_count);
	char_ls = NULL;
	char_count = NULL;
    return 1;
}

/* 
 * This function verifies that no symbol is used twice in a row or column.
 * It prints an error message alerting the user which rows or columns have 
 * duplicate symbols. This means that you will have at most n row error prints
 * and n column error prints.
 * 
 * Note: Test all rows first then test all columns.
 * 
 * Error messages have been included for you. Do not change the format out the 
 * print statements, as our grading scripts will use exact string matching. You
 * change the variable passed as the formatting argument to printf.
 * 
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 * @return 1 if valid, 0 if not
 */
 int Verify_Rows_and_Columns(const size_t n, char **latin_square){
    if (latin_square == NULL) {
        printf("Verify_Rows_and_Columns - latin_square is NULL\n"); 
        return 0;
    }
	int valid = 1;
	// ROWS:
	// loop over all rows and use verifyRow helper function that checks if row is valid
	for (int i = 0; i < n; i++) {
		if (!verifyRow(n, *(latin_square+i))) {
    			printf("Error in row %d\n", i);
			valid = 0;
		}
	}

	// COLUMN:
	// loop over all columns and use verifyCol helper function that checks if column is valid
	for (int i = 0; i < n; i++) {
		if (!verifyCol(n, latin_square, i)) {
			printf("Error in column %d\n", i);
			valid = 0;
		}
	}
    return valid;
}

/* 
 * This function calls free to allow all memory used by the latin_square 
 * verification program to be reclaimed.
 *
 * Note: you will have n+1 calls to free
 *
 * @param n The value of both dimensions of the latin square (i.e. nxn)
 * @param latin_square_in A pointer to the latin square variable in main
 */ 
void Free_Memory(const size_t n, char **latin_square) {
	for (int i = 0; i < n; i++) {
		free(*(latin_square+i));
	}
	free(latin_square);
}


