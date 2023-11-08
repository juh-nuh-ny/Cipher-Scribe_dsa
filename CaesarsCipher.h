#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CAESARS_CIPHER_H
#define CAESARS_CIPHER_H

//comstants for comparision 
#define SIZE 250
#define UPPER_A 'A'
#define UPPER_Z 'Z'
#define LOWER_A 'a'
#define LOWER_Z 'z'
#define NUMBER_0 '0'
#define NUMBER_9 '9'
#define ALPHABET_SIZE 26
#define NUMBER_SIZE 10


//Point with two datapoints, one for holding the original string
//two for the function changed value of the original
typedef struct Point
{
    char pointOne;
    char pointTwo;
    struct Point *next;
} Point;

typedef struct LinkedList
{
    Point *head;
} LinkedList;

//basic linked list functions
Point *createPoint(char input)
{
    Point *newPoint = (Point *)malloc(sizeof(Point));
    newPoint->pointOne = input;
    newPoint->pointTwo = input;
    newPoint->next = NULL;
    return newPoint;
}

Point *insertLast(Point *head, char input)
{   
    if (head == NULL) {
        return createPoint(input);
    }
    Point* temp = head;
    while(temp->next != NULL){
        temp = temp->next;    
    }
    temp->next = createPoint(input);
    return head;
}

//function to display all the original values, redundant in this case but can be put to use if need be
void displayMain(Point* head){
    Point* temp = head;
    while(temp != NULL){
        printf("%c", temp->pointOne);
        temp = temp->next;
    }
    printf("\n");
}

//function to display the encrypted value
void displayCrypt(Point* head){
    Point* temp = head;
    while(temp != NULL){
        printf("%c", temp->pointTwo);
        temp = temp->next;
    }
    printf("\n");
}

//shifts inout character by key times in ascii value
//if lowercase, adds to that, vice versa for the uppercase as well
Point* encrypt(Point *head, int key)
{
    Point* temp = head;
    while(temp != NULL){
        char pick = temp->pointOne;
        char encrypted = pick;
        if ((pick >= UPPER_A && pick <= UPPER_Z) || (pick >= LOWER_A && pick <= LOWER_Z)){
            char base = (pick >= LOWER_A && pick <= LOWER_Z) ? LOWER_A : UPPER_A;
            encrypted = base + (pick - base + key + ALPHABET_SIZE) % ALPHABET_SIZE;
        }
        else if (pick >= NUMBER_0 && pick <= NUMBER_9){
            encrypted = NUMBER_0 + (pick - NUMBER_0 + key + NUMBER_SIZE) % NUMBER_SIZE;
        }
        temp->pointTwo = encrypted;
        temp = temp->next;
    }
    return head;
}

//takes in an encrypted string and shifts the value by negative key
Point* decrypt(Point* head, int key)
{
    int newkey = -key;
    return encrypt(head, newkey);
}

//once functionality is done, clears memory
void clearMemory(Point* head)
{
    Point* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int Caesar(void)
{
    LinkedList list;
    list.head = NULL;

    char message[SIZE];
    int key;
    int choice;


//printf("Enter the plain-text:");
// scanf(" %[^\n]",text);
// printf("Enter the len_k(only alphabets):");
// scanf("%s",key);
    //takes in input and appends to a linked list
    printf("Message input: ");
    scanf(" %249[^\n]", message);
    for (int i = 0; message[i] != '\0'; i++) {
    list.head = insertLast(list.head, message[i]);
    }

    //get cipher key
    printf("Key? ");
    scanf("%d", &key);


    //choice 
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            list.head = encrypt(list.head, key);
            printf("Encrypted Message: ");
            displayCrypt(list.head);
            break;
        case 2:
            list.head = decrypt(list.head, key);
            printf("Decrypted Message: ");
            displayCrypt(list.head);
            break;
        default:
            printf("Invalid choice\n");
    }

    clearMemory(list.head);
    return 0;
}
#endif /* CAESARS_CIPHER_H */