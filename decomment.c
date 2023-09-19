#include <stdio.h>
#include <ctype.h>

/* Declare global data types (not variables) */
enum CharState {CODE, COMMENT, SLASH, ASTERISK, LITERAL1, LITERAL2, BACKSLASH1, BACKSLASH2};
enum ExitStatus {EXIT_SUCCESS, EXIT_FAILURE};


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
        printf("%c", c);
    } else if (c == '"') {
        state = LITERAL2;
        printf("%c", c);
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
        state = ASTERISK;
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

enum CharState handleBackslash1(int c)    /*always writes*/
{
    /*enum CharState state;
    state = LITERAL;*/
    printf("%c", c);
    return LITERAL1;
}

enum CharState handleBackslash2(int c)    /*always writes*/
{
    /*enum CharState state;
    state = LITERAL;*/
    printf("%c", c);
    return LITERAL2;
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
    int line = 1;
    enum CharState state = CODE;                  /*want it to start at CODE*/

    /* Read char-by-char until the file ends */
    while ((c = getchar()) != EOF) {
        switch (state) {  
            case CODE:                        /*there are only "real/countable" \n in the code and comment states*/
               line += findNewline(c);
               state = handleCode(c);
               break;
            case COMMENT:
               line += findNewline(c);
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
            case BACKSLASH1:                      /*contained in a literal, so can't be a \n character*/
               state = handleBackslash1(c);
               break; 
            case BACKSLASH2:                      /*contained in a literal, so can't be a \n character*/
               state = handleBackslash2(c);
               break;
        }
    }

    /*Raise error for unfinished comment. Return ExitStatus.*/
    if (state == ASTERISK || state == COMMENT) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", line);
        return EXIT_FAILURE;
    } else {
        if (state == SLASH) {     /* make up the lagging slash print */
            printf("/");
        }
        return EXIT_SUCCESS;
    }

}
