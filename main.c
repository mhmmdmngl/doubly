#include <stdio.h>
#include <malloc.h>

struct node
{
    int data;
    struct node* next;
    struct node* prev;
};

struct node* start;

struct node* createNewNode(int data)
{
    //We allocate memory for node
    struct node* newNode = (struct node*)malloc(sizeof (struct node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void addLast(int data)
{
    struct node* toBeLast = createNewNode(data);
    if(start == NULL)
        start = toBeLast;
    else
    {
        struct node* temp = start;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = toBeLast;
        //Difference of doubly linked list is we have to declare previous node
        toBeLast->prev = temp;
    }
}

void addFirst(int data)
{
    struct node* toBeFirst = createNewNode(data);
    //if we don't have any nodes, we just assign new node as start
    if(start == NULL)
    {
        start = toBeFirst;
        return;
    }
    //we store current start node to be second node...
    struct node* toBeSecond = start;
    start = toBeFirst;
    //we set new nodes next and previous pointers...
    toBeFirst->next = toBeSecond;
    toBeSecond->prev = start;
}

void addAnyWhere(int data, int givenNode, int beforeAfter)
{
    struct node* newNode = createNewNode(data);
    //beforeAfter = 1 means, we add node before given node..
    if(beforeAfter == 1 && start->data == givenNode)
    {
        addFirst(data);
        return;
    }

    struct node* temp = start;
    while(temp != NULL)
    {
        if(temp->data == givenNode)
            break;
        temp = temp->next;
    }
    if(temp->next == NULL && temp->data == givenNode && beforeAfter == 0)
    {
        addLast(data);
        return;
    }
    if(temp->next == NULL)
    {
        printf("\n given node is not exists in the list...");
    }

    if(beforeAfter == 1)
    {
        //beforeAfter == 1 means we add node before given data...
        struct node* previousNode = temp->prev;
        previousNode->next = newNode;
        newNode->next = temp;
        newNode->prev = previousNode;
        temp->prev = newNode;
    }
    else
    {
        struct node* nextNode = temp->next;
        temp->next = newNode;
        newNode->next = nextNode;
        newNode->prev = temp;
        nextNode->prev = newNode;
    }
}

void deleteLast()
{
    if(start == NULL)
        return;
    if(start->next == NULL)
        start = NULL;
    else
    {
        struct node* temp = start;
        while(temp->next != NULL)
            temp = temp->next;
        struct node* prevNode = temp->prev;
        prevNode->next = NULL;
        free(temp);
    }
}

void deleteFirst()
{
    if(start == NULL)
        return;
    if(start->next == NULL)
        start = NULL;
    else
    {
        struct node* tobeFirst = start->next;
        free(start);
        start = tobeFirst;
        tobeFirst->prev = NULL;
    }
}

void deleteGivenNode(int givenNode)
{
    if(start == NULL)
        return;
    if(start->data == givenNode)
        deleteFirst();
    else
    {
        struct node* temp = start;
        while(temp != NULL)
        {
            if(temp->data == givenNode)
                break;
            temp = temp->next;
        }
        if(temp->next == NULL && temp->data == givenNode)
            deleteLast();
        else
        {
            printf("\nthis line run %d", temp->data);
            struct node* previousNode = temp->prev;
            printf("\nprev node %d", previousNode->data);
            struct node* nextNode = temp->next;
            printf("\nnext node %d", nextNode->data);

            free(temp);
            previousNode->next = nextNode;
            nextNode->prev = previousNode;
        }
    }
}

void print()
{
    printf("\n");
    struct node* temp = start;
    while(temp != NULL)
    {
        printf(" %d ", temp->data);
        temp = temp->next;
    }
}

void menu()
{
    while(1 == 1)
    {
        int option, data, position;
        printf("\n1-) Add Last");
        printf("\n2-) Add First");
        printf("\n3-) Add Before");
        printf("\n4-) Add After");
        printf("\n5-) Delete Last Node");
        printf("\n6-) Delete First Node");
        printf("\n7-) Delete Given Node");
        printf("\n Select your choise ... ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("enter data for insert last ... ");
                scanf("%d", &data);
                addLast(data);
                print();
                break;
            case 2:
                printf("enter data for insert first ... ");
                scanf("%d", &data);
                addFirst(data);
                print();
                break;
            case 3:
                printf("enter data for insert before position... ");
                scanf("%d", &data);
                printf("which node to insert before on");
                scanf("%d", &position);
                addAnyWhere(data, position, 1);
                print();
                break;
            case 4:
                printf("enter data for insert After position... ");
                scanf("%d", &data);
                printf("which node to insert After on");
                scanf("%d", &position);
                addAnyWhere(data, position, 0);
                print();
                break;
            case 5:
                deleteLast();
                print();
                break;
            case 6:
                deleteFirst();
                print();
                break;
            case 7:
                printf("Which node data do you want to delete?... ");
                scanf("%d", &data);
                deleteGivenNode(data);
                print();
                break;

        }

    }
}

int main()
{
    menu();
}