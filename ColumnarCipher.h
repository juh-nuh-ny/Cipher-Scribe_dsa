#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef COLUMNAR_CIPHER_H
#define COLUMNAR_CIPHER_H

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    char text[MAX_ROWS][MAX_COLS];
    int length;
} EncryptedText;

typedef struct {
    char text[MAX_ROWS][MAX_COLS];
    int length;
} DecryptedText;

typedef enum {
    ENCRYPT,
    DECRYPT
} CipherMode;

void columnarCipher(const char *inputText, const char *key, char *outputText, CipherMode mode) {
    int keyLength = strlen(key);
    int textLength = strlen(inputText);

    int numRows = textLength / keyLength;
    if (textLength % keyLength != 0)
        numRows++;

    char matrix[MAX_ROWS][MAX_COLS];
    int index = 0;

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < keyLength; j++) {
            if (index < textLength) {
                matrix[i][j] = inputText[index];
                index++;
            } else {
                matrix[i][j] = ' ';
            }
        }
    }

    int columnOrder[MAX_COLS];
    int visited[MAX_COLS] = {0};

    for (int i = 0; i < keyLength; i++) {
        int min = 127;
        int minIndex = -1;

        for (int j = 0; j < keyLength; j++) {
            if (visited[j] == 0 && key[j] < min) {
                min = key[j];
                minIndex = j;
            }
        }

        visited[minIndex] = 1;
        columnOrder[i] = minIndex;
    }

    index = 0;
    if (mode == ENCRYPT) {
        for (int i = 0; i < keyLength; i++) {
            int col = columnOrder[i];
            for (int j = 0; j < numRows; j++) {
                outputText[index++] = matrix[j][col];
            }
        }
    } else if (mode == DECRYPT) {
        char decryptedMatrix[MAX_ROWS][MAX_COLS];
        index = 0;
        for (int i = 0; i < keyLength; i++) {
            int col = columnOrder[i];
            for (int j = 0; j < numRows; j++) {
                decryptedMatrix[j][col] = inputText[index++];
            }
        }

        index = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < keyLength; j++) {
                outputText[index++] = decryptedMatrix[i][j];
            }
        }
    }
}

int Columnar(void) {
    char plaintext[MAX_ROWS * MAX_COLS];
    char key[MAX_COLS];

    printf("Enter plaintext: ");
    scanf(" %[^\n]s", plaintext);

    printf("Enter key: ");
    scanf("%s", key);

     int choice;
    printf("Choose an option:\n");
    printf("1. Encrypt\n");
    printf("2. Decrypt\n");
    scanf("%d", &choice);

    char outputText[MAX_ROWS * MAX_COLS];

    switch (choice) {
        case 1:
            columnarCipher(plaintext, key, outputText, ENCRYPT);
            printf("Encrypted Text: %s\n", outputText);
            break;
        case 2:
            columnarCipher(plaintext, key, outputText, DECRYPT);
            printf("Decrypted Text: %s\n", outputText);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }


    return 0;
}

#endif /* COLUMNAR_CIPHER_H */