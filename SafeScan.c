#include <stdio.h>
#include <stdlib.h>

#define STRING_CAPACITY 255

struct InputString {
    char* string_ptr;
    size_t length;
    size_t capacity;
};

// Add character to string
// Like a stack
void addchar(struct InputString* str, char ch) {
    if (str->length == str->capacity) {
        str->capacity += STRING_CAPACITY;
        char* new_str_ptr = realloc(str->string_ptr, str->capacity);

        // Make sure allocation worked
        if (new_str_ptr != NULL) {
            str->string_ptr = new_str_ptr;
        } else {
            // Big sad, unfunny
            return NULL;
        }
    }

    // Push char
    memcpy(str->string_ptr + str->length, &ch, 1);

    str->length++;
}

void* getInput() {
    // Allocate enough heap to store an InputString struct
    void* inp_ptr = malloc(sizeof(struct InputString));

    struct InputString* inp;

    // Make sure allocation was successful
    if (inp_ptr != NULL) {
        // Construct InputString
        inp = inp_ptr;
        inp->string_ptr = malloc(STRING_CAPACITY);
        inp->length = 0;
        inp->capacity = STRING_CAPACITY;
    } else {
        // Allocation unsuccessful :(
        return NULL;
    }

    char ch;

    // Read STDIN until newline character
    while ((ch = getchar()) != 10) {
        addchar(inp, ch);
    }

    addchar(inp, 0);  // NULL termination

    // Now that we have the input string
    // Let's realloc to get rid of the heap we didn't need
    void* new_str_ptr = realloc(inp->string_ptr, inp->capacity);

    if (new_str_ptr != NULL)
    {
        inp->capacity = inp->length;
        inp->string_ptr = new_str_ptr;
    } else {
        // Reallocation didn't work
        // Thankfully, we still have the string stored in heap
        // The only issue is we dont use a big portion of the heap...
        // In this case it won't really matter. So just return the InputString anyways
    }

    return inp;
}

int main(void) {
    struct InputString* inp = getInput();

    printf("%s", inp->string_ptr);

    return 0;
}
