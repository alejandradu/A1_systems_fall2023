#include <stdio.h>
#include <ctype.h>

/* Declare global data types (not variables) */
enum CharState {CODE, COMMENT, SLASH, ASTERISK, LITERAL1, LITERAL2, BACKSLASH1, BACKSLASH2};
enum ExitStatus {EXIT_SUCCESS, EXIT_FAILURE};
enum NewComment {ACCEPT, REJECT};


enum CharState handleCode(int c)       /* all cases here write to stdout*/
{
    enum CharState state;         /*LOCAL variable of enumeration type*/ 
    if (c == '/') {      
        state = SLASH;
    } else if (c == '\'') {
        state = LITERAL1;
        printf("%c", c);
    } else if (c == '"') {
        state = LITERAL2;
        printf("%c", c);
    } else {
        state = CODE;
        printf("%c", c);
    }
    return state;
}

enum CharState handleSlash(int c)
{
    enum CharState state;
    if (c == '*') {
        printf(" ");
        state = ASTERISK;  
    } else if (c == '/') {
        state = SLASH;
        printf("/"); 
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
    } else {
        state = COMMENT;
    }
    return state;
}

enum CharState handleComment(int c)      /*nothing writes to stdout, only stderr*/
{
    enum CharState state;
    if (c == '*') {
        state = ASTERISK;
    } else if (c == '\n') {
        printf("\n");
        state = COMMENT;
    } else {
        state = COMMENT;
    }
    return state;
}

enum CharState handleLiteral1(int c)     /*all cases write*/
{
    enum CharState state;
    if (c == '\'') {
        state = CODE;
    } else if (c == '\\') {
        state = BACKSLASH1;
    } else {
        state = LITERAL1;
    }
    printf("%c", c);
    return state;
}

enum CharState handleLiteral2(int c)     /*all cases write*/
{
    enum CharState state;
    if (c == '"') {
        state = CODE;
    } else if (c == '\\') {
        state = BACKSLASH2;
    } else {
        state = LITERAL2;
    }
    printf("%c", c);
    return state;
}

enum CharState handleBackslash(enum CharState state, int c)    /*always writes*/
{
    printf("%c", c);
    return state;
}

int findNewline(int c)
{
    if (c == '\n') {
        return 1;
        }
    else {
        return 0;
    }
}

int main(void)    /*don't have to declare a return type for main*/
{
    /* Initialize local variables of the global enumeration types */
    int c;                                        /*declare. C requires variable declarations*/ 
    int curr = 1;
    int last_comment_start;
    enum CharState state = CODE;                  /*want it to start at CODE*/
    enum NewComment new = ACCEPT;

    /* Read char-by-char until the file ends */
    while ((c = getchar()) != EOF) {
        curr += findNewline(c);
        switch (state) {  
            case CODE:       
               new = ACCEPT;            /* can only come back to accept new comment when def back in code */
               state = handleCode(c);
               break;
            case COMMENT:
               if (new == ACCEPT) {
                  last_comment_start = curr;
               }
               new = REJECT;
               state = handleComment(c);
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
               state = handleBackslash(LITERAL1, c);
               break; 
            case BACKSLASH2:                
               state = handleBackslash(LITERAL2, c);
               break;
        }
    }

    /*Raise error for unfinished comment. Return ExitStatus.*/
    if (state == ASTERISK || state == COMMENT) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", last_comment_start);
        return EXIT_FAILURE;
    } else {
        if (state == SLASH) {     /* make up the lagging slash print */
            printf("/");
        }
        return EXIT_SUCCESS;
    }

}
