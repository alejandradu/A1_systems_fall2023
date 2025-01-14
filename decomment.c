#include <stdio.h>
#include <ctype.h>

/* Declare global data types (not variables) */

/* DFA states */
enum CharState {CODE, COMMENT, SLASH, ASTERISK, LITERAL1, LITERAL2, BACKSLASH1, BACKSLASH2, UNTERMINATED};
/* Exit status */
enum ExitStatus {EXIT_SUCCESS, EXIT_FAILURE};
/* States to define when a line number is recorded as a comment start */
enum NewComment {ACCEPT, REJECT};


 /*  Handle transitions from the CODE state
 *   Write the current char to stdout if not part of a comment.
 *   If input is an incomplete comment, results in an unwritten
 *   slash, added later in main()
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state
 */
enum CharState handleCode(int c)
{
    /* Local variable to allocate the next DFA state */
    enum CharState state; 
    if (c == '/') {      
        state = SLASH;          /* don't write: '/' might be a comment */
    } else if (c == '\'') {
        state = LITERAL1;
        printf("%c", c);
    } else if (c == '"') {
        state = LITERAL2;
        printf("%c", c);
    } else {
        state = CODE;
        if (c != EOF) {         /* exception: don't write EOF */
            printf("%c", c);
        }
    }
    return state;
}

 /*  Handle transitions from the SLASH state
 *   Write the current char to stdout iff not part of a comment.
 *   If writing, print a slash before the current char to make
 *   up for the unwritten slash in the SLASH state.
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state
 */
enum CharState handleSlash(int c)
{
    enum CharState state;
    if (c == '*') {         /* identifies the start of a comment */
        printf(" ");        /* write whitespace to replace comment */
        state = ASTERISK;  
    } else if (c == '/') {
        state = SLASH;
        printf("/");
    } else if (c == EOF) {
        state = SLASH;
    } else if (c == '\'') {
        state = LITERAL1;
        printf("/%c", c);
    } else if (c == '"') {
        state = LITERAL2;
        printf("/%c", c);
    } else {
        state = CODE;
        printf("/%c", c);
    }
    return state;

}

 /*  Handle transitions from the ASTERISK state
 *   Does not write to stdout, except for newline characters.
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state
 */
enum CharState handleAsterisk(int c)    
{
    enum CharState state;
    if (c == '*') {
        state = ASTERISK;
    } else if (c == '\n') {
        printf("\n");
        state = COMMENT;
    } else if (c == '/') {
        state = CODE;
    } else if (c == EOF) {
        state = UNTERMINATED;
    } else {
        state = COMMENT;
    }
    return state;
}

 /*  Handle transitions from the COMMENT state
 *   Does not write to stdout, except for newline characters.
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state
 */
enum CharState handleComment(int c)
{
    enum CharState state;
    if (c == '*') {
        state = ASTERISK;
    } else if (c == '\n') {
        printf("\n");
        state = COMMENT;
    } else if (c == EOF) {
        state = UNTERMINATED;
    } else {
        state = COMMENT;
    }
    return state;
}

 /*  Handle transitions from the LITERAL1 state
 *   Handles literals in single quotations.
 *   Write the current char to stdout (not EOF)
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state
 */
enum CharState handleLiteral1(int c)
{
    enum CharState state;
    if (c == '\'') {
        state = CODE;
    } else if (c == '\\') {
        state = BACKSLASH1;
    } else {
        state = LITERAL1;
    }
    if (c != EOF) { 
            printf("%c", c);
        }
    return state;
}

 /*  Handle transitions from the LITERAL2 state
 *   Handles literals in double quotations.
 *   Write the current char to stdout (not EOF)
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state
 */
enum CharState handleLiteral2(int c) 
{
    enum CharState state;
    if (c == '"') {
        state = CODE;
    } else if (c == '\\') {
        state = BACKSLASH2;
    } else {
        state = LITERAL2;
    }
    if (c != EOF) { 
            printf("%c", c);
        }
    return state;
}

 /*  Handle transitions from the BACKSLASH1 state
 *   Handles backslash characters within literals:
 *   Writes to stdout the current char (not EOF)
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state (the same prior literal)
 */
enum CharState handleBackslash1(int c)    /*always writes*/
{
    if (c != EOF) { 
            printf("%c", c);
        }
    return LITERAL1;
}

 /*  Handle transitions from the BACKSLASH2 state
 *   Handles backslash characters within literals:
 *   Writes to stdout the current char (not EOF)
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: next DFA state (the same prior literal)
 */
enum CharState handleBackslash2(int c)    /*always writes*/
{
    if (c != EOF) { 
            printf("%c", c);
        }
    return LITERAL2;
}

 /*  Determine if the current char is a newline character
 *
 *   c: currently read char given by getchar() in main()
 *
 *   returns: 1 if true, 0 if false
 */
int findNewline(int c)
{
    if (c == '\n') {
        return 1;
        }
    else {
        return 0;
    }
}

int main(void) 
{
    /* Initialize local variables of the global enumeration types */

    /* Current char */
    int c;                     
    /* Current line number counter */
    int curr = 1;
    /* Line number of the most recently read comment */
    int last_comment_start;
    /* Initialize DFA in CODE state */
    enum CharState state = CODE;
    /* Initialize variable to accept a new comment line number */
    enum NewComment new = ACCEPT;

    /* Read char-by-char */
    while ((c = getchar())) {
        /* Add to the newline counter */
        curr += findNewline(c);
        switch (state) {  
            case CODE:       
               new = ACCEPT;                 /* can only accept new comments */
               state = handleCode(c);        /* coming from a code state*/
               break;
            case COMMENT:
                if (new == ACCEPT) {
                  last_comment_start = curr; /* Update line start of most recent comment */
                }
                new = REJECT;                 /* Reject new comment start lines while in */
                state = handleComment(c);     /* the current comment */
                break;
            case SLASH:
                state = handleSlash(c);
                break;
            case ASTERISK:
                state = handleAsterisk(c);
                break;
            case LITERAL1:
                state = handleLiteral1(c);
                break;
            case LITERAL2:
                state = handleLiteral2(c);
                break;
            case BACKSLASH1:                   
                state = handleBackslash1(c);
                break; 
            case BACKSLASH2:                
                state = handleBackslash2(c);
                break;
            case UNTERMINATED:        /* added for correctness, no effect */
                break;
        }

        if (c == EOF) {
            if (state == SLASH) {     /* make up for the lagging slash print */
            printf("/");
            }

            break;                    /* break the while loop regardless of state */
        }
    }

    /* Return ExitStatus */
    if (state == UNTERMINATED) {     /* Rejecting state */
        fprintf(stderr, "Error: line %d: unterminated comment\n", last_comment_start);
        return EXIT_FAILURE;
    } else {
        return EXIT_SUCCESS;         /* Accepting states */
    }

}
