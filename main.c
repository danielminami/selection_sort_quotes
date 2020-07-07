/*
Daniel Minami <minamid@sheridancollege.ca>
----------------------------------------------------------------------
 */

// Assignment N2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The name of the input file and output file
#define IN_FILE "quotes.txt"
#define OUT_FILE "output.txt"

// Defines how many quotes will be in the OUT_FILE
#define MAX_QUOTES 5

// This function will be used in sorting to swap strings ("pointers").
void swap(char**, char**);

// Selection Sort function here.
void selection_sort(char**, size_t);

// Read quotes from file and add them to array of pointers.
// You also must user selection_sort inside this function!
void read_in(char**);

// Print the quotes using array of pointers.
void print_out(char**);

// Save the sorted quotes in the OUT_FILE file.
void write_out(char**);

// Free memory pointed by pointers in the array of pointers!
void free_memory(char**);


int main() {

    // Create array of pointers. Each pointer should point to heap memory where each quote is kept. 
    // I.e. quotes[0] points to smallest string.
    // We need +1 to insert the new quote at the end of the array and then re-sort.
    char* quotes[MAX_QUOTES+1]={NULL};

    // Read quotes from file and place them into array quotes. 
    // Also, sort as you add them
    // You also need to print how many lines were processed
    read_in(quotes);
   
    // Print MAX_QUOTES shortest quotes
    print_out(quotes);

    // Save MAX_QUOTES shortest quotes in the file OUT_FILE
    write_out(quotes);
    
    // Free memory allocated by array of pointers
    free_memory(quotes);
    
    return (0);
}

// Add all required functions below!

void read_in(char** str) {
    FILE *frp;
   
    if ((frp=fopen(IN_FILE, "r")) == NULL) {
        perror("Could not open file.\n");
        exit(1);
    }
    
    int c, counter=0, maxstr=0, numOfLines=0;
    while ((c = fgetc(frp)) != EOF) { 
       if((char)c == '\r') {
           if (counter>maxstr) maxstr=counter;
           if (counter>1) numOfLines++; counter=0;
       } else {
           counter++;
       }
    }
    
    rewind(frp);
    
    size_t len=0;
    int sortCount=0;
    char* tmp = (char*) calloc(maxstr, sizeof(char));
    if (tmp == NULL) {
        printf("Cannot allocate memory for string %s\n", tmp);
        exit(1);
    }
        
    while (fgets(tmp, maxstr, frp)) {
        tmp[strcspn(tmp,"\r")]=0;
        len = strlen(tmp);
        if (len > 0) {
            if (sortCount == 0) {
                *str = (char*) calloc(maxstr, sizeof(char));
                if (str == NULL) {
                    printf("Cannot allocate memory for string %s\n", tmp);
                    exit(1);
                }
                strcpy(*str, tmp);
                sortCount++;
            } else if (sortCount <= (MAX_QUOTES)){ 
                *(str + sortCount) = (char*) calloc(maxstr, sizeof(char));
                if (str == NULL) {
                    printf("Cannot allocate memory for string %s\n", tmp);
                    exit(1);
                }
                strcpy(*(str + sortCount), tmp);
                sortCount++;
                selection_sort(str, sortCount);
            } else {
                strcpy(*(str + sortCount-1), tmp);
                selection_sort(str, (sortCount));
            }
        }
    }
    free(tmp);
    fclose(frp);
    
}

void selection_sort(char** st, size_t n) {
    int i, j, min_idx; 
  
    for (i=0; i<n-1; i++) { 
        min_idx = i; 
        for (j=i+1; j<n; j++){ 
            if (strlen(st[j]) < strlen(st[min_idx])){
                min_idx = j; 
            } else if (strlen(st[j]) == strlen(st[min_idx])) {
                if (strcoll(st[j], st[min_idx])) min_idx = j; 
            }       
        }
        swap(&st[min_idx], &st[i]); 
    }
}
    
void swap(char** p1, char** p2){
    char* temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void print_out(char** str) {
    printf("These are the %d shortest quotes:\n", MAX_QUOTES);
    for (int i = 0; i<MAX_QUOTES && *(str+i) != NULL; i++)
        printf("\n%s", *(str+i));
    
}

void write_out(char** str) {
    FILE *fwp;
    
    if ((fwp=fopen(OUT_FILE, "w")) == NULL) {
        fclose(fwp);
        perror("Could not create file.\n");
        exit(1);
    }
    
    for (int i = 0; i<MAX_QUOTES && *(str+i) != NULL; i++) {
        fprintf(fwp, "%s\n", *(str+i));
    }
    
    printf("\n\nFile saved successfully!");
    fclose(fwp);
    
}

void free_memory(char** str) {
    free(*str);
}