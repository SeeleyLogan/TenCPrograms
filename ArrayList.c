#include <stdio.h>
#include <stdlib.h>

struct ArrayList {
    char* elements;
    size_t ele_size;
    size_t size;
    size_t capacity;
};

/*
* array_size: amount of elements in array
* ele_size: byte size of each element
*/
void *createArrayList(size_t array_size, size_t ele_size) {
    // Allocate heap to store a struct of type `array`
    void* arr_ptr = malloc(sizeof(struct ArrayList));

    struct ArrayList* arr;

    // Make sure allocation was successful
    if (arr_ptr != NULL) {
        // Construct ArrayList
        arr = arr_ptr;
        arr->ele_size = ele_size;
        arr->size = 0;
        arr->capacity = array_size;

        // Allocate (array_size * ele_size) of heap, this is where the elements will be located
        arr->elements = calloc(array_size, ele_size);

        // Allocation didn't work... free up the previously allocated heap and return NULL
        if (arr->elements == NULL) {
            free(arr_ptr);

            return NULL;
        }
    }
    // Allocation didn't work, return NULL
    else {
        return NULL;
    }

    // Return pointer to struct
    return arr;
}

// Push element onto ArrayList
// Erm... are we just making a stack?
void push(struct ArrayList* arr, int ele) {
    if (arr->size == arr->capacity) {
        // NAURRR!!!! we ran out of allocated memory :(
        // It's ok, we can just reallocate
        // Hopefully size is never bigger than capacity, because that would be bad
        arr->capacity += 100;  // YODA NOTATION??? not really but whatever
        char* new_arr_ptr = realloc(arr->elements, arr->ele_size * arr->capacity);

        // Make sure allocation worked
        if (new_arr_ptr != NULL) {
            arr->elements = new_arr_ptr;
        } else {
            // Erm, guess it didn't :(
            return NULL;
        }
    }

    // Push element
    memcpy(arr->elements + arr->size * arr->ele_size, &ele, arr->ele_size);

    arr->size++;
}

// Pops the last element from the array (like a stack)
void pop(struct ArrayList* arr) {
    // HHAHAHHAHAHAHAHAH (this works)
    arr->size--;

    // I should probably reallocate if the array gets too small... (to save memory)
    // TODO: do that later lol
}

char *get(struct ArrayList* arr, int i) {
    return arr->elements + (arr->ele_size * i);
}

int main() {
    struct ArrayList* arr = createArrayList(2, 4);

    // Erm... allocation didn't work (bad)
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    // Hopefully none of these return NULL (because I dont handle that bs)
    push(arr, 255);
    push(arr, 1024);
    push(arr, 65000);

    // For each element in array
    for (int i = 0; i < arr->size; i++) {
        printf("%d\n", *(int *)get(arr, i));
    }

    return EXIT_SUCCESS;
}
