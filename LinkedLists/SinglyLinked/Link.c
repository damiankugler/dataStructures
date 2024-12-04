/**
    Implementation and inline testing of a singly linked list with a sentinel node.
    The list can, add, remove, removeFirst, addBefore, addAfter, addFront.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/** Linked List */
typedef struct Node
{
    int x;
    struct Node *next;
} Node;

// Keeps track of the lists size;
static int listSize;

void fail(char *str)
{
    printf("Fail Reason: %s", str);
}

/**
    Adds a new node to the end of the list.
    @param head root node
    @param val value we want to add.
 */
void add(Node **head, int val)
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
    newNode->x = val;
    if (listSize == 0)
    {
        // Acctual head.
        (*head)->next = newNode;
        listSize++;
        return;
    }
    // Create a current val to iterrate over the list.
    Node *current = *head;
    // Iterate over the list
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    listSize++;
}

/**
    Adds affter a chosen value.
    @param root node
    @param val value that we want to add.
    @param before value that we add before
 */
void addBefore(Node **head, int val, int before)
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
    newNode->x = val;

    // List is emplty only contains the sentinel node
    if (listSize == 0)
    {
        // Add new node to the begginig of the list
        (*head)->next = newNode;
        listSize++;
        return;
    }

    // Create a current val to iterrate over the list.
    Node *current = *head;

    while (current->next != NULL && current->next->x != before)
    {
        current = current->next;
    }
    // Make sure the value that we want to add after exitst.
    if (current == NULL)
    {
        printf("Value %d not found in the list. Node not added.\n", before);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;

    listSize++;
}

/**
    Adds affter a chosen value.
    @param root node
    @param val value that we want to add.
    @param after value that we add after
 */
void addAfter(Node **head, int val, int after)
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
    newNode->x = val;

    // List is emplty only contains the sentinel node
    if (listSize == 0)
    {
        // Add new node to the begginig of the list
        (*head)->next = newNode;
        listSize++;
        return;
    }

    // Create a current val to iterrate over the list.
    Node *current = (*head)->next;

    while (current != NULL && current->x != after)
    {
        current = current->next;
    }
    // Make sure the value that we want to add after exitst.
    if (current == NULL)
    {
        printf("Value %d not found in the list. Node not added.\n", after);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;

    listSize++;
}

/**
    Adds to the front of the list.
    @param root node
    @param val value that we want to add.
 */
void addFront(Node **root, int val)
{
    // Create new node
    Node *newNode = malloc(sizeof(Node));
    newNode->x = val;
    newNode->next = (*root)->next;
    // Root points to newNode ( ->next because we are using a sentinel Node )
    (*root)->next = newNode;
    // Increase the size of list.
    listSize++;
}

void removeNode(Node **head, int val)
{
    // Check head for null.
    if (head == NULL)
    {
        fail("Head was null\n");
        return;
    }

    Node *current = *head;
    while (current->next != NULL && current->next->x != val)
    {
        current = current->next;
    }

    // Make sure the value exist.
    if (current == NULL)
    {
        printf("Value %d not found in the list. Node not added.\n", val);
        return;
    }
    // Next node points to the node after the one we want to remove;
    current->next = current->next->next;
    listSize--;
}

void removeFirst(Node **head)
{
    // Check head for null.
    if (head == NULL)
    {
        fail("Head was null\n");
        return;
    }

    if (listSize == 0)
    {
        printf("The list is empty.\n");
        return;
    }

    (*head)->next = (*head)->next->next;
    listSize--;
}

/**
    Prints the list in order.
    @param root node
 */
void print(Node **root)
{
    int index = 0;

    if (listSize == 0)
    {
        printf("The list is empty.\n");
    }

    Node *current = (*root)->next;
    while (current != NULL)
    {
        printf("Value at current Node %d is %d\n", index, current->x);
        current = current->next;
        index++;
    }
}

/**
    Free the allocated memory.
    @param root node of the list.
 */
void freeNode(Node **root)
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
}

void testBefore()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing addBefore\n");
    printf("------------------------------------------------\n\n");
    Node *head = malloc(sizeof(Node));
    head->next = NULL;
    head->x = 0;
    listSize = 0;

    printf("List Values:\n");

    addAfter(NULL, 78, 10);

    // Make sure the size is 0
    assert(listSize == 0);

    // Since the size is 0 it doesnt matter what value we put for before.
    addBefore(&head, 78, 10);
    assert(listSize == 1);
    assert(head->next->x == 78);

    // Add in front of the 1st node.
    addBefore(&head, 10, 78);
    assert(listSize == 2);
    assert(head->next->x == 10);
    assert(head->next->next->x == 78);

    // Add before the last node.
    addBefore(&head, 2, 78);
    assert(listSize == 3);
    assert(head->next->x == 10);
    assert(head->next->next->x == 2);
    assert(head->next->next->next->x == 78);

    addBefore(&head, 999, 123);

    print(&head);

    printf("\n------------------------------------------------");
    printf("\n               End of testing addBefore \n");
    printf("------------------------------------------------\n");
    freeNode(&head);
}

void testAfter()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing addAfter\n");
    printf("------------------------------------------------\n\n");
    Node *head = malloc(sizeof(Node));
    head->next = NULL;
    head->x = 0;
    listSize = 0;

    printf("List Values:\n");

    addAfter(NULL, 78, 10);

    // Make sure the size is 0
    assert(listSize == 0);

    // Since the size is 0 it doesnt matter what value we put for after.
    addAfter(&head, 78, 10);
    assert(listSize == 1);
    assert(head->next->x == 78);

    // Add in front of the 1st node.
    addAfter(&head, 10, 78);
    assert(listSize == 2);
    assert(head->next->x == 78);
    assert(head->next->next->x == 10);

    // Add before the last node.
    addAfter(&head, 2, 78);
    assert(listSize == 3);
    assert(head->next->x == 78);
    assert(head->next->next->x == 2);
    assert(head->next->next->next->x == 10);

    addAfter(&head, 999, 123);

    print(&head);

    printf("\n------------------------------------------------");
    printf("\n               End of testing addAfter \n");
    printf("------------------------------------------------\n");
    freeNode(&head);
}

void testAdd()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing add ( add to end )\n");
    printf("------------------------------------------------\n\n");
    Node *head = malloc(sizeof(Node));
    head->next = NULL;
    head->x = 0;
    listSize = 0;

    printf("List Values:\n");

    add(NULL, 78);

    // Make sure the size is 0
    assert(listSize == 0);

    // Since the size is 0 it doesnt matter what value we put for after.
    add(&head, 83);
    assert(listSize == 1);
    assert(head->next->x == 83);

    // Add in front of the 1st node.
    add(&head, 10);
    assert(listSize == 2);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);

    add(&head, 2);
    assert(listSize == 3);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);
    assert(head->next->next->next->x == 2);

    print(&head);

    printf("\n------------------------------------------------");
    printf("\n               End of testing add ( add to end ) \n");
    printf("------------------------------------------------\n");
    freeNode(&head);
}

void testRemove()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing add remove\n");
    printf("------------------------------------------------\n\n");
    Node *head = malloc(sizeof(Node));
    head->next = NULL;
    head->x = 0;
    listSize = 0;

    printf("List Values:\n");

    add(NULL, 78);

    // Make sure the size is 0
    assert(listSize == 0);

    // Since the size is 0 it doesnt matter what value we put for after.
    add(&head, 83);
    assert(listSize == 1);
    assert(head->next->x == 83);

    // Add in front of the 1st node.
    add(&head, 10);
    assert(listSize == 2);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);

    add(&head, 2);
    assert(listSize == 3);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);
    assert(head->next->next->next->x == 2);

    add(&head, 5);
    assert(listSize == 4);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);
    assert(head->next->next->next->x == 2);
    assert(head->next->next->next->next->x == 5);

    print(&head);

    printf("\n");
    // Remove last node.
    removeNode(&head, 5);

    assert(listSize == 3);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);
    assert(head->next->next->next->x == 2);

    printf("\n");

    print(&head);

    // Remove first node.
    removeNode(&head, 83);

    assert(listSize == 2);
    assert(head->next->x == 10);
    assert(head->next->next->x == 2);

    printf("\n");

    print(&head);

    printf("\n------------------------------------------------");
    printf("\n               End of testing remove \n");
    printf("------------------------------------------------\n");
    freeNode(&head);
}

void testRemoveFirst()
{
    printf("\n------------------------------------------------\n");
    printf("                Testing add removeFirst\n");
    printf("------------------------------------------------\n\n");
    Node *head = malloc(sizeof(Node));
    head->next = NULL;
    head->x = 0;
    listSize = 0;

    printf("List Values:\n");

    add(NULL, 78);

    // Make sure the size is 0
    assert(listSize == 0);

    // Since the size is 0 it doesnt matter what value we put for after.
    add(&head, 83);
    assert(listSize == 1);
    assert(head->next->x == 83);

    // Add in front of the 1st node.
    add(&head, 10);
    assert(listSize == 2);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);

    add(&head, 2);
    assert(listSize == 3);
    assert(head->next->x == 83);
    assert(head->next->next->x == 10);
    assert(head->next->next->next->x == 2);

    print(&head);

    removeFirst(&head);

    assert(listSize == 2);
    assert(head->next->x == 10);
    assert(head->next->next->x == 2);

    printf("\n");

    print(&head);

    removeFirst(&head);

    assert(listSize == 1);
    assert(head->next->x == 2);

    printf("\n");

    print(&head);

    removeFirst(&head);

    assert(listSize == 0);

    printf("\n");

    print(&head);

    removeFirst(&head);

    printf("\n------------------------------------------------");
    printf("\n               End of testing removeFirst \n");
    printf("------------------------------------------------\n");
    freeNode(&head);
}

/**
    User for testing the linked list.
    Using inline tesing.
 */
int main()
{
    testBefore();
    testAfter();
    testAdd();
    testRemove();
    testRemoveFirst();
    return EXIT_SUCCESS;
}