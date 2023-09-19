#include <stdio.h>
#include <ctype.h>

/* Declare global data types (not variables) */
enum CharState {CODE, COMMENT, SLASH, ASTERISK, LITERAL, BACKSLASH};
enum ExitStatus {EXIT_SUCCESS, EXIT_FAILURE};


enum CharState handleCode(int c)       /* all cases here write to stdout*/
{
    enum CharState state;         /*LOCAL variable of enumeration type*/ 
    if (c == '/') {      
        state = SLASH;
    } else if (c == '\'' || c == '"') {
        state = LITERAL;
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
    } else if (c == '/') {
        /* printf(" "); */
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

enum CharState handleLiteral(int c)     /*all cases write*/
{
    enum CharState state;
    if (c == '\'' || c == '"') {
        state = CODE;
    } else if (c == '\\') {
        state = BACKSLASH;
    } else {
        state = LITERAL;
    }
    printf("%c", c);
    return state;
}

enum CharState handleBackslash(int c)    /*always writes*/
{
    enum CharState state;
    state = LITERAL;
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
            case LITERAL:
               state = handleLiteral(c);
               break;
            case BACKSLASH:                      /*contained in a literal, so can't be a \n character*/
               state = handleBackslash(c);
               break; 
        }
    }

    /*Raise error for unfinished comment. Return ExitStatus.*/
    if (state == ASTERISK || state == COMMENT) {
        fprintf(stderr, "Error: line %d: unterminated comment\n", line);
        return EXIT_FAILURE;
    }
    else {
        return EXIT_SUCCESS;
    }

}
