#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/** Linked List */
typedef struct Node
{
    int x;
    struct Node *next;
    struct Node *prev;
} Node;

// Keeps track of the size
static int listSize;

/** Print out an error message and exit. */
static void fail(char const *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

/**
    Adds a new node to the end of the list.
    @param head root node
    @param val value we want to add.
 */
void add(Node **head, Node **tail, int val)
{
    // Check head for null.
    if (head == NULL)
    {
        fail("Head was null\n");
        return;
    }
    // Create new node
    Node *newNode = malloc(sizeof(Node));
    // Ensure that it was creaeted
    if (newNode == NULL)
        fail("New Node Allocation Failed");
    // Ending node set next to null
    newNode->next = NULL;
    // Set the note to null.
    newNode->prev = NULL;

    newNode->x = val;

    if (listSize == 0)
    {
        // Actual head.
        (*head)->next = newNode;
        (*tail)->prev = newNode;
        newNode->next = *tail;
        newNode->prev = *head;
        listSize++;
        return;
    }

    (*tail)->prev->next = newNode;
    newNode->prev = (*tail)->prev;
    (*tail)->prev = newNode;
    newNode->next = *tail;

    listSize++;
}

/**
    Adds a new node to the end of the list.
    Adding to the list in O(1).
    @param head root node
    @param val value we want to add.
 */
void addFirst(Node **head, int val)
{
    // Check head for null.
    if (head == NULL)
    {
        fail("Head was null\n");
        return;
    }
    // New node to add.
    Node *newNode = malloc(sizeof(Node));
    newNode->x = val;

    newNode->next = (*head)->next;
    (*head)->next->prev = newNode;
    (*head)->next = newNode;
    newNode->prev = (*head);

    listSize++;
}

/**
    Returns the value of the first node.
    @param head begining of the list.
    @return x value of the first node.
 */
int first(Node **head)
{
    return (*head)->next->x;
}

/**
    Returns the value of the specified Node
    @param head start of the list
    @param index
 */
int get(Node **head, Node **tail, int index)
{
    // Check the index. Make sure that its not bigger then the listSize and not < than 0.
    if (index >= listSize || index < 0)
    {
        printf("The value %d is bigger than the list size %d.", index, listSize);
        return -1;
    }
    Node *current;
    //
    if (index < listSize / 2)
    {
        current = *head;
        // Get to the node specified by the index.
        for (int i = 0; i < index; i++)
        {
            // Traverse over the list
            current = current->next;
        }
    }
    else
    {
        current = *tail;
        // Get to the node specified by the index.
        for (int i = listSize - 1; i > index; i--)
        {
            // Traverse over the list
            current = current->prev;
        }
    }
    // Return the value of the node.
    return current->x;
}

/**
    Check if list is empty.
    @return true if the list is empty. False if not.
 */
bool isEmpty()
{
    // Return true if list is empty.
    return (listSize == 0);
}

/**
    Removes the specified node if the node exists.
    @param head points to the beginning of the list.
    @param val we want to remove.
 */
void removeNode(Node **head, int val)
{
    // Check if the list is empty.
    if (listSize == 0)
    {
        printf("List is empty. Nothing to remove.\n");
        return;
    }
    // Used to travers.
    Node *current = *head;
    // While value is not null and not the val
    while (current->next != NULL && current->next->x != val)
    {
        current = current->next;
    }

    // Ensure that the value is in the list.
    if (current->next == NULL)
    {
        // value wasnt find.
        printf("Coulnt find the value.\n");
        return;
    }
    // Skip the next node
    current->next = current->next->next;
    // Link the next nodes prev to the current one
    current->next->prev = current;
    // Decresse the size of the list.
    listSize--;
}

/**
    Removes the first node in O(1)
    @param head start of the list
 */
void removeFirst(Node **head)
{
    // Check if the list is empty.
    if (listSize == 0)
    {
        printf("List is empty. Nothing to remove.\n");
        return;
    }
    (*head)->next = (*head)->next->next;
    (*head)->next->prev = (*head);
    listSize--;
}

/**
    Remove the last node in the list in O(1).
    @param tail pointer to the tail node.
 */
void removeLast(Node **tail)
{
    // Check if the list is empty.
    if (listSize == 0)
    {
        printf("List is empty. Nothing to remove.\n");
        return;
    }
    (*tail)->prev = (*tail)->prev->prev;
    (*tail)->prev->next = (*tail);
    listSize--;
}

/**
    Changes the value of the previous node to a new value O(n)
    @param head usedd to traverse the list
    @param val to replace
    @param newVal new value
 */
void set(Node **head, int val, int newVal)
{
    Node *current = *head;
    while (current != NULL && current->x != val)
    {
        current = current->next;
    }
    // Check if the value exists
    if (current == NULL)
    {
        printf("Val %d not in the list.\n", val);
        return;
    }
    // Change the value
    current->x = newVal;
}

/**
    Returns the size of the list O(1) sice we keep track of the size.
    @return size of the list
 */
int size()
{
    return listSize;
}
/**
    Returns the value of the last node.
    @param tail end of the list
    @return value of the last node.
 */
int last(Node **tail)
{
    // Return value of the node.
    return (*tail)->prev->x;
}

/**
    Prints the list in order.
    @param root node
 */
void print(Node **head)
{
    Node *current = (*head)->next;
    int i = 0;
    while (current->next != NULL)
    {
        printf("Value %d at index %d.\n", current->x, i++);
        current = current->next;
    }
    printf("ListSize: %d.\n", listSize);
}

/**
    Free the allocated memory.
    @param root node of the list.
 */
void freeNode(Node **root, Node **tail)
{
    // Node used to
    Node *current = *root;
    // Node we are going t remove
    Node *remNode;
    while (current != NULL)
    {
        // Save current node
        remNode = current;
        // Move to the next node
        current = current->next;
        // Free the previous node
        free(remNode);
    }
    // Change list to 0
    listSize = 0;
    // Change root to null;
    *root = NULL;
    *tail = NULL;
}

/**
    Test adding to the end of the list.
 */
void testAdd()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing add\n");
    printf("------------------------------------------------\n\n");

    // Create head.
    Node *sentinelHead = malloc(sizeof(Node));
    // Create tail.
    Node *sentinelTail = malloc(sizeof(Node));
    // Check if head and tail are not NULL
    if (!sentinelHead || !sentinelTail)
    {
        fail("Cant create head or tail");
    }

    sentinelHead->next = sentinelTail;
    sentinelHead->prev = NULL;
    sentinelHead->x = 0;

    sentinelTail->next = NULL;
    sentinelTail->prev = sentinelHead;
    sentinelTail->x = 0;
    // Initialize size to 0.
    listSize = 0;

    assert(isEmpty() == true);

    // Add to empty list.
    add(&sentinelHead, &sentinelTail, 16);
    assert(sentinelHead->next->x == 16);
    assert(listSize == 1);
    assert(isEmpty() == false);
    assert(last(&sentinelTail) == 16);
    // Check first value.
    assert(first(&sentinelHead) == 16);

    add(&sentinelHead, &sentinelTail, 19);
    assert(sentinelHead->next->x == 16);
    assert(sentinelHead->next->next->x == 19);
    assert(last(&sentinelTail) == 19);
    // Check first value.
    assert(first(&sentinelHead) == 16);
    assert(listSize == 2);
    assert(isEmpty() == false);

    add(&sentinelHead, &sentinelTail, 91);
    assert(sentinelHead->next->x == 16);
    assert(sentinelHead->next->next->x == 19);
    assert(sentinelHead->next->next->next->x == 91);
    assert(last(&sentinelTail) == 91);
    assert(listSize == 3);
    assert(isEmpty() == false);

    add(&sentinelHead, &sentinelTail, 83);
    assert(sentinelHead->next->x == 16);
    assert(sentinelHead->next->next->x == 19);
    assert(sentinelHead->next->next->next->x == 91);
    assert(sentinelHead->next->next->next->next->x == 83);
    assert(last(&sentinelTail) == 83);
    assert(listSize == 4);
    assert(isEmpty() == false);

    set(&sentinelHead, 91, 100);

    set(&sentinelHead, 16, 101);

    set(&sentinelHead, 19, 102);

    set(&sentinelHead, 83, 103);

    set(&sentinelHead, 199, 102);

    removeFirst(&sentinelHead);

    assert(listSize == 3);

    removeLast(&sentinelTail);

    assert(listSize == 2);

    print(&sentinelHead);

    printf("\n------------------------------------------------");
    printf("\n               End of testing add \n");
    printf("------------------------------------------------\n");
    freeNode(&sentinelHead, &sentinelTail);
}

/**
    Test adding to the end of the list.
 */
void testAddFirst()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing addFirst\n");
    printf("------------------------------------------------\n\n");

    // Create head.
    Node *sentinelHead = malloc(sizeof(Node));
    // Create tail.
    Node *sentinelTail = malloc(sizeof(Node));
    // Check if head and tail are not NULL
    if (!sentinelHead || !sentinelTail)
    {
        fail("Cant create head or tail");
    }

    sentinelHead->next = sentinelTail;
    sentinelHead->prev = NULL;
    sentinelHead->x = 0;

    sentinelTail->next = NULL;
    sentinelTail->prev = sentinelHead;
    sentinelTail->x = 0;
    // Initialize size to 0.
    listSize = 0;

    assert(isEmpty() == true);

    // Add to empty list.
    addFirst(&sentinelHead, 16);
    assert(sentinelHead->next->x == 16);
    // Check first value.
    assert(first(&sentinelHead) == 16);
    assert(last(&sentinelTail) == 16);
    assert(listSize == 1);
    assert(isEmpty() == false);

    add(&sentinelHead, &sentinelTail, 19);
    assert(sentinelHead->next->x == 16);
    assert(sentinelHead->next->next->x == 19);
    assert(last(&sentinelTail) == 19);
    assert(listSize == 2);
    assert(isEmpty() == false);

    addFirst(&sentinelHead, 91);
    assert(sentinelHead->next->x == 91);
    // Check first value.
    assert(first(&sentinelHead) == 91);
    assert(sentinelHead->next->next->x == 16);
    assert(sentinelHead->next->next->next->x == 19);
    assert(last(&sentinelTail) == 19);
    assert(listSize == 3);
    assert(isEmpty() == false);

    addFirst(&sentinelHead, 83);
    // Check first value.
    assert(first(&sentinelHead) == 83);
    assert(sentinelHead->next->x == 83);
    assert(sentinelHead->next->next->x == 91);
    assert(sentinelHead->next->next->next->x == 16);
    assert(sentinelHead->next->next->next->next->x == 19);
    assert(last(&sentinelTail) == 19);
    assert(listSize == 4);
    assert(isEmpty() == false);

        removeNode(&sentinelHead, 91);

    print(&sentinelHead);

    printf("\n------------------------------------------------");
    printf("\n               End of testing addFirst \n");
    printf("------------------------------------------------\n");
    freeNode(&sentinelHead, &sentinelTail);
}

/**
    User for testing the linked list.
    Using inline tesing.
 */
int main()
{
    testAdd();
    testAddFirst();

    return EXIT_SUCCESS;
}