#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <errno.h>

// Initial capacity of the list
#define INITCAPACITY 2

/**
    Struct representation of an array.
 */
typedef struct
{
    // Void pointer to make the array generic.
    void *data;
    // Keeps the size of the element
    size_t elementSize;
    // entries of the array
    int size;
    // Total capacity,
    int capacity;
} Array;

/**
    Return an array of specided values ( int, string, char )
    @param valSize size of the value we want the array to hold.
    @return an array of specified values.
 */
Array *arrayConstructor(size_t valSize)
{
    // Allocate mem for list.
    Array *list = malloc(sizeof(Array));
    // Check if list can be allocated.
    if (list == NULL)
    {
        perror("Can't allocate memory for list.");
    }
    // Allocate mem for the data.
    list->data = calloc(INITCAPACITY, valSize);
    // Check if data can be allocated.
    if (list->data == NULL)
    {
        // Free the list
        free(list);
        perror("Can't allocate memory for list->data.");
    }
    // Init size
    list->size = 0;
    // Init capacity.
    list->capacity = INITCAPACITY;
    // Set elemSize.
    list->elementSize = valSize;
    // Return the array.
    return list;
}

/**
    Returns true if list is zero
    @param list we wan to check if empty
    @return true if list size is 0
 */
bool isEmpty(Array *list)
{
    return list->size == 0;
}
/**
    Resizes the array.
    @param list to resize
 */
void resize(Array *list)
{
    // Increase the capacity
    list->capacity = list->capacity * 2;
    // Realloc the list->data
    list->data = realloc(list->data, list->elementSize * list->capacity);
}

/**
    Adds to the end of the list
    @param list that we want to append to
    @param val void pointer to the value we want to add
 */
void append(Array *list, void *val)
{
    // Ensure that we have room in the list.
    if (list->size == list->capacity)
    {
        // If not resize.
        resize(list);
    }

    // Check if the size is 0.
    if (list->size == 0)
    {
        memcpy((char *)list->data, val, list->elementSize);
        list->size++;
        return;
    }
    // Store the value at the end of the list.
    memcpy((char *)list->data + list->size * list->elementSize, val, list->elementSize);
    // Increase the list size.
    list->size++;
}

/**
    Adds the specified value to the beggining of the list.
    @param list we want to add to the beggining of
    @param element value we want to add.
 */
void prepend(Array *list, void *element)
{
    // Ensure that we have room in the list.
    if (list->size == list->capacity)
    {
        // If not resize.
        resize(list);
    }
    // Check if the size is 0.
    if (list->size == 0)
    {
        memcpy((char *)list->data, element, list->elementSize);
        list->size++;
        return;
    }
    memmove((char *)list->data + list->elementSize, list->data, list->size * list->elementSize);
    memcpy((char *)list->data, element, list->elementSize);
    //  Increase the list size.
    list->size++;
}

/**
    Adds a value into a specified index.
    @param list we want to add to
    @param index we want to add at
    @param val that we add
 */
void add(Array *list, int index, void *val)
{
    // Ensure that we have room in the list.
    if (list->size == list->capacity)
    {
        // If not resize.
        resize(list);
    }
    // Check if index more than capacity.
    if (index > list->size)
    {
        printf("Index can't be bigger or equal to the capacity of the list.\nCapacity of the list: %d", list->capacity);
        return;
    }
    // Add to an empty list.
    if (list->size == 0)
    {
        memcpy((char *)list->data, val, list->elementSize);
        list->size++;
        return;
    }
    // Move values only if we are not adding to the end - no values to move
    if (index < list->size)
    {
        memmove((char *)list->data + (index + 1) * list->elementSize, (char *)list->data + index * list->elementSize, (list->size - index) * list->elementSize);
    }
    memcpy((char *)list->data + index * list->elementSize, val, list->elementSize);
    list->size++;
}

void *removeIndex(Array *list, int index)
{
    if (isEmpty(list))
    {
        puts("The list is already empty.");
        return NULL;
    }
    // Create the pointer to the value
    void *value = malloc(list->elementSize);
    // Save the value
    memcpy(value, list->data + index * list->elementSize, list->elementSize);

    if (list->size == 1)
    {
        list->size = 0;
    }
    else
    {
        memmove((char *)list->data + index * list->elementSize, (char *)list->data + (index + 1) * list->elementSize, (list->size - index - 1) * list->elementSize);
        list->size--;
    }
    return value;
}

void *removeFirst(Array *list)
{
}

void *removeLast(Array *list)
{
}

/**
    Return a value at specified index.
    @param list we want to get a value from
    @param index we want to retrieve value
    @return void poiter to the value at the index
 */
void *get(Array *list, int index)
{
    if (index >= list->size)
    {
        puts("Index cant be more than size.");
        return NULL;
    }
    return list->data + index * list->elementSize;
}

/**
    Returns the first value in the list
    @param list we want to get the first
    @return first value in the list
 */
void *first(Array *list)
{
    if (isEmpty(list))
    {
        return NULL;
    }
    return list->data;
}

/**
    Returns the last value in the list
    @param list we want to get the last value
    @return the last value in the list
 */
void *last(Array *list)
{
    if (isEmpty(list))
    {
        return NULL;
    }

    return list->data + (list->size - 1) * list->elementSize;
}

/**
    Used to print the list.
    @param list we want to print
 */
void print(Array *list)
{
    printf("Size of the array %d.\n\n", list->size);
    for (size_t i = 0; i < list->size; i++)
    {
        int *element = (int *)list->data;
        printf("Element at %d is %d.\n", i, element[i]);
    }
    puts("");
}

/**
    Frees the memory
 */
void freeArray(Array *list, void *value)
{
    free(value);
    free(list->data);
    free(list);
}

/**
    Test adding to the beggingin.
 */
void testPrepend()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing Prepend\n");
    printf("------------------------------------------------\n\n");

    Array *list = arrayConstructor(sizeof(int));

    // Ensure the list is empty.
    assert(isEmpty(list) == true);

    // Check list using int.
    int *element = (int *)list->data;

    assert(first(list) == NULL);
    assert(last(list) == NULL);

    int x = 98;
    // Add to the beggining.
    prepend(list, &x);
    assert(list->size == 1);
    // Ensure the first value is 98
    assert(element[0] == 98);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 98);

    x = 99;
    prepend(list, &x);
    assert(element[0] == 99);
    assert(element[1] == 98);
    assert(list->size == 2);

    assert(*(int *)first(list) == 99);
    assert(*(int *)last(list) == 98);

    x = 100;
    prepend(list, &x);

    assert(element[0] == 100);
    assert(element[1] == 99);
    assert(element[2] == 98);
    assert(list->size == 3);

    assert(*(int *)first(list) == 100);
    assert(*(int *)last(list) == 98);

    x = 111;
    prepend(list, &x);

    assert(element[0] == 111);
    assert(element[1] == 100);
    assert(element[2] == 99);
    assert(element[3] == 98);
    assert(list->size == 4);

    assert(*(int *)first(list) == 111);
    assert(*(int *)last(list) == 98);
    print(list);

    printf("\n------------------------------------------------");
    printf("\n               End of testing Prepend \n");
    printf("------------------------------------------------\n");
    freeArray(list, NULL);
}

/**
    Test adding to the end of the list.
 */
void testAppend()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing Append\n");
    printf("------------------------------------------------\n\n");

    Array *list = arrayConstructor(sizeof(int));

    // Ensure the list is empty.
    assert(isEmpty(list) == true);

    assert(first(list) == NULL);
    assert(last(list) == NULL);

    // Check list using int.
    int *element = (int *)list->data;

    int x = 98;
    // Add to the beggining.
    append(list, &x);
    assert(list->size == 1);
    // Ensure the first value is 98
    assert(element[0] == 98);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 98);

    x = 99;
    append(list, &x);
    assert(element[0] == 98);
    assert(element[1] == 99);
    assert(list->size == 2);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 99);

    x = 100;
    append(list, &x);

    assert(element[0] == 98);
    assert(element[1] == 99);
    assert(element[2] == 100);
    assert(list->size == 3);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 100);

    x = 111;
    append(list, &x);

    assert(element[0] == 98);
    assert(element[1] == 99);
    assert(element[2] == 100);
    assert(element[3] == 111);
    assert(list->size == 4);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 111);

    print(list);

    printf("\n------------------------------------------------");
    printf("\n               End of testing Append \n");
    printf("------------------------------------------------\n");
    freeArray(list, NULL);
}

/**
    Test adding to the end of the list.
 */
void testAdd()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing Add\n");
    printf("------------------------------------------------\n\n");

    Array *list = arrayConstructor(sizeof(int));

    // Ensure the list is empty.
    assert(isEmpty(list) == true);

    // Check list using int.
    int *element = (int *)list->data;

    // Add first element
    int x = 76;
    add(list, 0, &x);
    assert(list->size == 1);
    assert(element[0] == 76);
    assert(*(int *)get(list, 0) == 76);

    assert(*(int *)first(list) == 76);
    assert(*(int *)last(list) == 76);

    x = 78;
    add(list, 0, &x);
    assert(list->size == 2);
    assert(element[0] == 78);
    assert(*(int *)get(list, 0) == 78);
    assert(element[1] == 76);
    assert(*(int *)get(list, 1) == 76);

    assert(*(int *)first(list) == 78);
    assert(*(int *)last(list) == 76);

    x = 80;
    add(list, 0, &x);
    assert(list->size == 3);
    assert(element[0] == 80);
    assert(*(int *)get(list, 0) == 80);
    assert(element[1] == 78);
    assert(*(int *)get(list, 1) == 78);
    assert(element[2] == 76);
    assert(*(int *)get(list, 2) == 76);

    assert(*(int *)first(list) == 80);
    assert(*(int *)last(list) == 76);

    x = 82;
    add(list, 0, &x);
    assert(list->size == 4);
    assert(element[0] == 82);
    assert(*(int *)get(list, 0) == 82);
    assert(element[1] == 80);
    assert(*(int *)get(list, 1) == 80);
    assert(element[2] == 78);
    assert(*(int *)get(list, 2) == 78);
    assert(element[3] == 76);
    assert(*(int *)get(list, 3) == 76);
    assert(get(list, 10) == NULL);

    assert(*(int *)first(list) == 82);
    assert(*(int *)last(list) == 76);

    x = 84;
    add(list, 0, &x);
    // Change the poiter so that it points to the new location after reallocating memory.
    element = (int *)list->data;
    assert(list->size == 5);
    assert(element[0] == 84);
    assert(element[1] == 82);
    assert(element[2] == 80);
    assert(element[3] == 78);
    assert(element[4] == 76);

    // Add to the end.
    x = 91;
    add(list, 5, &x);
    assert(list->size == 6);
    assert(element[0] == 84);
    assert(*(int *)get(list, 0) == 84);
    assert(element[1] == 82);
    assert(*(int *)get(list, 1) == 82);
    assert(element[2] == 80);
    assert(*(int *)get(list, 2) == 80);
    assert(element[3] == 78);
    assert(*(int *)get(list, 3) == 78);
    assert(element[4] == 76);
    assert(*(int *)get(list, 4) == 76);
    assert(element[5] == 91);
    assert(*(int *)get(list, 5) == 91);

    assert(*(int *)first(list) == 84);
    assert(*(int *)last(list) == 91);

    // Add element into the middle.
    x = 100;
    add(list, 2, &x);
    assert(list->size == 7);
    assert(element[0] == 84);
    assert(*(int *)get(list, 0) == 84);
    assert(element[1] == 82);
    assert(*(int *)get(list, 1) == 82);
    assert(element[2] == 100);
    assert(*(int *)get(list, 2) == 100);
    assert(element[3] == 80);
    assert(*(int *)get(list, 3) == 80);
    assert(element[4] == 78);
    assert(*(int *)get(list, 4) == 78);
    assert(element[5] == 76);
    assert(*(int *)get(list, 5) == 76);
    assert(element[6] == 91);
    assert(*(int *)get(list, 6) == 91);

    assert(*(int *)first(list) == 84);
    assert(*(int *)last(list) == 91);

    // Print to see output.
    print(list);

    printf("\n------------------------------------------------");
    printf("\n               End of testing Add \n");
    printf("------------------------------------------------\n");
    freeArray(list, NULL);
}

/**
    Test removing from the list.
 */
void testRemove()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing Remove\n");
    printf("------------------------------------------------\n\n");

    Array *list = arrayConstructor(sizeof(int));

    // Ensure the list is empty.
    assert(isEmpty(list) == true);

    assert(first(list) == NULL);
    assert(last(list) == NULL);

    // Check list using int.
    int *element = (int *)list->data;

    int x = 98;
    // Add to the beggining.
    append(list, &x);
    assert(list->size == 1);
    // Ensure the first value is 98
    assert(element[0] == 98);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 98);

    x = 99;
    append(list, &x);
    assert(element[0] == 98);
    assert(element[1] == 99);
    assert(list->size == 2);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 99);

    x = 100;
    append(list, &x);

    assert(element[0] == 98);
    assert(element[1] == 99);
    assert(element[2] == 100);
    assert(list->size == 3);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 100);

    x = 111;
    append(list, &x);

    assert(element[0] == 98);
    assert(element[1] == 99);
    assert(element[2] == 100);
    assert(element[3] == 111);
    assert(list->size == 4);

    assert(*(int *)first(list) == 98);
    assert(*(int *)last(list) == 111);

    print(list);

    // Test removing the first value.
    int *i = (int *)removeIndex(list, 0);
    assert(*i == 98);
    assert(element[0] == 99);
    assert(element[1] == 100);
    assert(element[2] == 111);
    assert(list->size == 3);

    print(list);

    i = removeIndex(list, 2);

    assert(*i == 111);
    assert(element[0] == 99);
    assert(element[1] == 100);
    assert(list->size == 2);

    print(list);

    i = removeIndex(list, 1);

    assert(*i == 100);
    assert(element[0] == 99);

    i = removeIndex(list, 1);

    assert(isEmpty(list) == true);

    print(list);

    printf("\n------------------------------------------------");
    printf("\n               End of testing Remove \n");
    printf("------------------------------------------------\n");
    freeArray(list, i);
}
/**
    User for testing the linked list.
    Using inline tesing.
 */
int main()
{
    testPrepend();
    testAppend();
    testAdd();
    testRemove();

    return EXIT_SUCCESS;
}
