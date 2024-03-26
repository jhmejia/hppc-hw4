#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


/***
 * strtok implementation that is thread-safe and does not modify the input string.
 * 
 * @param input The input string to tokenize. If NULL, the function will continue tokenizing the string from the last context.
 * @param delim The delimiter string.
 * @param context The context to store the current position in the input string.
 * 
 * @return The next token in the input string or NULL if there are no more tokens.
*/
char* strtok_raw_threadsafe(const char* input, const char* delim, char** context)
{
    if (!input && !(*context)) {
        return NULL; // No input string and no context
    }

    if (input) {
        *context = (char*)input; // Initialize context
    }

    char* start = *context;
    if (*start == '\0') {
        return NULL; // We've reached the end of the string
    }

    // Look for the end of the token
    char* end = start;
    while (*end) {
        if (strchr(delim, *end)) {
            break;
        }
        end++;
    }

    // Allocate memory for the token
    ptrdiff_t tokenLength = end - start;
    char* token = (char*)malloc(tokenLength + 1);

    if (!token) {
        return NULL; // Allocation failure
    }

    strncpy(token, start, tokenLength);
    token[tokenLength] = '\0';

    *context = *end ? end + 1 : end; // Update the context

    return token;
}

void free_token(char* token) {
    free(token);
}

int main() {
    const char* inputString = "The quick brown fox jumps over the lazy dog";
    const char* delimiters = " ";

    char* context = NULL;
    char* token = strtok_raw_threadsafe(inputString, delimiters, &context);
    while (token != NULL) {
        printf("Token: %s\n", token);
        free_token(token); // Free the memory allocated for token
        token = strtok_raw_threadsafe(NULL, delimiters, &context);
    }
    return 0;
}
