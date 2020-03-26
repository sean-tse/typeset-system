/* Solution to comp10002 Assignment 1, 2019 semester 2.

   Authorship Declaration:

   (1) I certify that the program contained in this submission is completely
   my own individual work, except where explicitly noted by comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students,
   or by non-students as a result of request, solicitation, or payment,
   may not be submitted for assessment in this subject.  I understand that
   submitting for assessment work developed by or in collaboration with
   other students or non-students constitutes Academic Misconduct, and
   may be penalized by mark deductions, or by other penalties determined
   via the University of Melbourne Academic Honesty Policy, as described
   at https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will
   I do so until after the marks are released. I understand that providing
   my work to other students, regardless of my intention or any undertakings
   made to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring
   service, or drawing the attention of others to such services and code
   that may have been made available via such a service, may be regarded
   as Student General Misconduct (interfering with the teaching activities
   of the University and/or inciting others to commit Academic Misconduct).
   I understand that an allegation of Student General Misconduct may arise
   regardless of whether or not I personally make use of such solutions
   or sought benefit from such actions.

   Signed by: [Sean Tse 1080339]
   Dated:     [20/9/2019]

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
# define CHARMAX 999                /* Maximum number of characters */
typedef char inline_t[CHARMAX+1];   /* Max length of input line */

/******************************************************************************/
       
/* Function Prototypes */
int mygetchar();
int mygetline(char L[], int limit);
int printmargin(int M);
int printn(int M);
int printword(char inputt[], int word_start, int word_len);
int printline(int start, char inputt[]);

/******************************************************************************/

/* main program controls all the action
 */

int
main(int argc, char *argv[]) {
    /* Setup: run only once */
    
    inline_t inputt;            /* one line of input */
    int leftmargin = 4;         /* Default margin = 4 */
    int maxlinelength = 50;     /* Default max line length = 50 */
    int curlen = 0;             /* Current length of output line */
    
    /* Tracks number of consecutive newline printed to prevent excessive breaks 
     */
    int newlines = 1;    

    /* s1, s2, s3 corresponds to Section/subsection/subsubsection number */
    int s1 = 0; 
    int s2 = 0;
    int s3 = 0; 

    while (mygetline(inputt, CHARMAX) != EOF) {
       /* Processes input line by line */
       /* Runs for every input line */
        
        int index = 0;          /* position currently being looked at */
        int word_start = 0;     /* position that current word starts at */
        int word_len = 0;       /* length of current word */

        /* Checks if start is period or if line is empty */
        if ((inputt[0] == '.') || (inputt[0] == '\0')  
        || (inputt[0] == '\n') ){
           
            /* Insert break: maximum of 1 newline printed */
            if ((inputt[0] == '.') && (inputt[1] == 'b') && (newlines <= 1)){
                printn(1 - newlines);  
                newlines = 1;
                curlen = 0;      
            }

            /* Insert paragraph break: maximum of 2 newline printed */
            else if ((inputt[0] == '.') && (inputt[1] == 'p') 
            && (newlines <= 2) ){
                printn(2 - newlines);  
                newlines = 2;
                curlen = 0;   
            }

            /* Modifies left margin: maximum of 2 newline printed */
            else if ((inputt[0] == '.') && (inputt[1] == 'l') 
            && (newlines <= 2)){              
                printn(2 - newlines);  
                newlines = 2;
                curlen = 0;               
                leftmargin = atoi(inputt + 3);
            }

            /* Modifies maximum length of output line:
             * maximum of 2 newline printed 
             */
            else if ((inputt[0] == '.') && (inputt[1] == 'w') 
            && (newlines <= 2)){               
                printn(2 - newlines);  
                newlines = 2;
                curlen = 0;   
                maxlinelength = atoi(inputt + 3);
            }
 
            /* Centers line */
            else if ((inputt[0] == '.') && (inputt[1] == 'c')) {  
                index = 2;
                
                /* Length of rest of line */
                int line_length = 0; 

                /* While we have not reached end of line */
                while ((inputt[index] != '\0') && (inputt[index] != '\n')){ 
                     
                    word_len = 0;
                    /* Skips all whitespaces */
                    while ((inputt[index] == ' ') || (inputt[index] == '\t') 
                    || (inputt[index] == '\n')){
                        index++;
                    }
                    
                    /* Start of next word must be here */
                    word_start = index + 1 - 1; 
               
                    /* Finds the length of the current word */
                    while ((inputt[word_start + word_len] != ' ') 
                    && (inputt[word_start + word_len] != '\t') 
                    && (inputt[word_start + word_len] != '\n') 
                    && (inputt[word_start + word_len] != '\0')) {
                        word_len++;
                        index++;
                    }
                     
                   line_length += word_len + 1;
                }
                line_length -= 1;

                /* Insert paragraph break: maximum of 2 newline printed */
                printn(1 - newlines);
                newlines = 1;
                
                /* Determines margin to print */
                if (line_length > maxlinelength){
                    printmargin(leftmargin);
                    }
                else {
                    /* Sets margin to be half of 
                     * remaining space rounded down
                     */
                    printmargin(floor(0.5 * (maxlinelength - line_length)));
                }
                
                /* Prints rest of line from position 2 onwards, 
                 * stripping consecutive whitespaces
                 */
                int start = 2;
                printline(start, inputt);
                
                
                /* Prints following break */
                printf("\n");
                newlines = 1;


            }

            /* Creates and prints heading */
            else if ((inputt[0] == '.') && (inputt[1] == 'h')) { 
                
                /* adjusts levels of sections, 
                 * subsections, subsubsections
                 */

                /* .h 1 */
                if ((inputt[3] - '0') == 1){
                    s1 += 1;
                    s2 = 0; 
                    s3 = 0;
                }
                /* .h 2 */
                else if ((inputt[3] - '0') == 2){
                    s2 += 1;
                    s3 = 0;
                }
                /* .h 3 */
                else if ((inputt[3] - '0') == 3){
                    s3 += 1;
                }
                
                /* Insert paragraph break: maximum of 2 newline printed */
                printn(2 - newlines);  
                newlines = 2;
                curlen = 0;
                printmargin(leftmargin);
                
                /* If new section: */
                if ((s2 == 0) && (s3 == 0)) {
                    int i;
                    for ( i = 0; i < maxlinelength; i++) {
                        printf("-");
                    }
                    printf("\n");
                    printmargin(leftmargin);
                    printf("%d ", s1);
                }

                /* If new subsection: */
                else if (s3 == 0) {
                    printf("%d.%d ", s1, s2);
                }

                /* If new subsubsection: */
                else {
                    printf("%d.%d.%d ", s1, s2, s3);
                }
                
                /* Prints rest of line from position 4 onwards,
                 * stripping consecutive whitespaces
                 */
                int start = 4;
                printline(start, inputt);
                
                
                /* Inserts following paragraph break */
                printn(2);  
                newlines =2;
                curlen = 0;

            }

        }

        /* if Normal line */
        else {
            
            /* Scans line character by character,
             * detecting spaces and adjusting accordingly
             */
            
            /* While we have not reached end of line */
            while ((inputt[index] != '\0') && (inputt[index] != '\n')){ 
                
                /* Prints left margin if output is new line */
                if (curlen == 0){            
                    printmargin(leftmargin); 
                }
                
                   
                word_len = 0;
                /* Skips all whitespaces */
                while ((inputt[index] == ' ') 
                || (inputt[index] == '\t') || (inputt[index] == '\n')){
                   index++;
                }
                /* Start of next word must be here */
                word_start = index +1 -1; 
        
                /* Finds the length of the current word that it is looking at */
                while ((inputt[word_start + word_len] != ' ') 
                && (inputt[word_start + word_len] != '\t') 
                && (inputt[word_start + word_len] != '\n') 
                && (inputt[word_start + word_len] != '\0')) {
                    word_len++;
                    index++;
                }
                
                
                
                 
                
                /* If single word exceeds line length, print it by itself */
                if (word_len >= maxlinelength){
                    printf("\n");
                    printmargin(leftmargin);
                    printword(inputt, word_start, word_len);
                    printf("\n");
                    newlines = 1;
                    curlen = 0;
                }

                /* If the addition of this word exceeds the line length,
                 * print it on a new line and continue
                 */
                else if (curlen + word_len > maxlinelength) {
                    printf("\n");
                    printmargin(leftmargin);
                    printword(inputt, word_start, word_len);
                    printf(" ");
                    curlen = word_len + 1;
                    newlines = 0;
                }

                /* If selected word can fit on current line,
                 * print it and continue
                 */
                else if (curlen + word_len <= maxlinelength) {
                    printword(inputt, word_start, word_len);
                    printf(" ");
                    curlen += (word_len + 1) ;
                    newlines = 0;
                }
        
                /* If not end of line, keep reading */
                if ((inputt[index] != '\n') && (inputt[index] != '\0')){
                    index++;
                }
            }
        }   
    }
    return 0;
}
	
/******************************************************************************/

/* modified version of getchar(), sourced from 
 * comp10002 Assignment 1, 2019s2 FAQ page
 */

int
mygetchar() {
	int c;
	while ((c=getchar())=='\r') {
	}
	return c;
}

/******************************************************************************/

/* Extracts a single line out of standard input, of not more than 
 * limit characters. Derived from getword() from textbook
 * Modifications: reads non alphanumeric characters, 
 * and breaks when reaching a newline character
 */

int
mygetline(char L[], int limit) {
	int c, len = 0;
	
    /*Skips EOF*/
	if ((c = mygetchar())==EOF) {
		return EOF;
	}
	
    /* ok, first character of next word has been found */
	while ((len < limit) &&  (c != '\n') && (c != EOF)) {
		/* another character to be stored */
		L[len++] = c;
        c = mygetchar();
	}
	/* now close off the string */
	L[len] = '\0';
	
    return 0;
}

/******************************************************************************/

/* Prints left margin of variable length 
 */

int
printmargin(int M){
    int i;
    for (i = 0; i <= M; i++){
        printf(" ");
    }
    return 0;
}

/******************************************************************************/

/* Prints entered number of newline characters 
 */

int
printn(int M){
    int i;
    for (i = 0; i < M; i++){
        printf("\n");
    }
    return 0;
}

/******************************************************************************/

/* Prints all characters from a given input string 
 * from position word_start to word_end
 */

int
printword(char inputt[], int word_start, int word_len){
    /*Prints word*/                  
    int i;
    for (i = 0; i< word_len; i++){
        printf("%c", inputt[word_start +i]);
    }
    return 0;                
}

/******************************************************************************/

/* Prints rest of string from position start onwards, 
 * stripping consecutive whitespaces
 */

int
printline(int start, char inputt[]){

    /*counts consecutive whitespace, 
    initialised at =1 to skip first whitespaces of line*/
    int counter = 1; 
                
    int i;
    for ( i = start; i < strlen(inputt); i++){
        /*If character is the first whitespace,
        print a single space*/
        if (((inputt[i] == ' ') 
        || (inputt[i] == '\t')) && (counter == 0)) {  
            printf(" ");
            counter += 1;
        }
        /*If character is not whitespace, print it*/
        else if ((inputt[i] != ' ') 
        && (inputt[i] != '\t') && (inputt[i] != '\n')){
            printf("%c", inputt[i]);
            counter = 0;
        }   
    }
    return 0;            
}

/******************************************************************************/




/*algorithms is fun*/