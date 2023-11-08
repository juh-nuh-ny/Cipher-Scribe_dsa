#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef VIGÉNERE_CIPHER_H
#define VIGÉNERE_CIPHER_H

struct VigNode {
    char data;
    struct VigNode* next;
    struct VigNode* prev;
};

struct VigNode* createVigNode(char data) {
    struct VigNode* newVigNode = (struct VigNode*)malloc(sizeof(struct VigNode));
    if (newVigNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newVigNode->data = data;
    newVigNode->next = NULL;
    newVigNode->prev = NULL;
    return newVigNode;
}

void appendVigNode(struct VigNode** head, char data) {
    struct VigNode* newVigNode = createVigNode(data);
    if (*head == NULL) {
        *head = newVigNode;
    } else {
        struct VigNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newVigNode;
        newVigNode->prev = current;
    }
}

void Vigencrypt(struct VigNode* text, const char* key) {
    int keyLen = strlen(key);
    int keyIndex = 0;
    struct VigNode* current = text;

    while (current != NULL) {
        if (isalpha(current->data)) {
            char base = isupper(current->data) ? 'A' : 'a';
            int shift = key[keyIndex] - 'A';
            current->data = base + (current->data - base + shift) % 26;
            keyIndex = (keyIndex + 1) % keyLen;
        }
        current = current->next;
    }
}

void Vigdecrypt(struct VigNode* text, const char* key) {
    int keyLen = strlen(key);
    int keyIndex = 0;
    struct VigNode* current = text;

    while (current != NULL) {
        if (isalpha(current->data)) {
            char base = isupper(current->data) ? 'A' : 'a';
            int shift = key[keyIndex] - 'A';
            current->data = base + (current->data - base - shift + 26) % 26;
            keyIndex = (keyIndex + 1) % keyLen;
        }
        current = current->next;
    }
}

void displaylist(struct VigNode* head) {
    struct VigNode* current = head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}

void uppercase(char *str) {
    for(int i=0;str[i];i++){
        str[i]=toupper(str[i]);
    }
}

int is_alpha_string(const char* str) {
    for (int i = 0; str[i]; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return 0;
        }
    }
    return 1;
}

int Vigenere(void) {
    struct VigNode* text = NULL;
    char inputText[100];
    char key[100];
    int choice;

    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    printf("Enter your choice (1/2): ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) {
        printf("Invalid choice. Exiting...\n");
        return 1;
    }

    printf("Enter the text:");
    scanf(" %[^\n]s", inputText); // Read a whole line, including spaces
    if (!is_alpha_string(inputText)) {
        printf("Input text should contain only alphabets and spaces. Exiting...\n");
        return 1;
    }

    printf("Enter the key:");
    scanf("%s", key);
    if (!is_alpha_string(key)) {
        printf("Key should contain only alphabets. Exiting...\n");
        return 1;
    }
    uppercase(key);

    for (int i = 0; i < strlen(inputText); i++) {
        appendVigNode(&text, inputText[i]);
    }

    switch (choice) {
        case 1:
            Vigencrypt(text, key);
            printf("Encrypted Text:");
            break;
        case 2:
            Vigdecrypt(text, key);
            printf("Decrypted Text:");
            break;
        default:
            printf("invalid Choice");
            break;
    }

    displaylist(text);

    return 0;
}

#endif /* VIGÉNERE_CIPHER_H */