#include <stdio.h>
//convert .c files to .h files and use them header files here on the mail
#include "CaesarsCipher.h"
#include "ColumnarCipher.h"
#include "VigénereCipher.h"

int main() {
    int status = 1;
    while(status == 1){
        int choice;
    printf("Choose a cipher:\n");
    printf("1. Caesar's Cipher\n");
    printf("2. Columnar Cipher\n");
    printf("3. Vigenére Cipher\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            Caesar();
            break;
        case 2:
            Columnar();
            break;
        case 3:
            Vigenere();
            break;
        case 4:
            status = 0;
            break;
        default:
            printf("Invalid choice\n");
            break;
    }}
    

    return 0;
}
