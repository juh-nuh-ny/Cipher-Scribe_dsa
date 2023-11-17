//TRANSPOSITION COLUMNAR CIPHER
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

#ifndef COLUMNAR_CIPHER_H
#define COLUMNAR_CIPHER_H

#define MAX_TEXT_LENGTH 500
#define MAX_KEY_LENGTH 500
#define ENCRYPT 1
#define DECRYPT 2

//structure for the nodes to store column wise linked list
struct Node {
    char data;
    struct Node* link;
}typedef node;

//create a node of the lenked list
node* create(char a)
{
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = a;
    newNode->link = NULL;
    return newNode;
}

//creation of a linked list by insert at the end 
node* append(node* head,char chr)
{
    node* new=create(chr);
    if(new == NULL)
    {
        printf("Memory allocation falied");
        return NULL;    
    }
    if(head==NULL)
        head=new;
    else
    {
        node* temp=head;
        while(temp->link !=NULL)
            temp=temp->link;
        temp->link=new;
    }
    return head;
}

//printing the linked list
void display(node* head)
{
    node* p=head;;
    while(p!=NULL)
    {   
        printf("%c",p->data);
        p=p->link;
    }
}  

void emptyList(node* head) 
{
    node* p=head;
    while (p!=NULL) 
    {
        node* temp = p;
        p = p->link;
        free(temp);
    }
}


//convert the key to uppercase using toupper function for easier usage
void UpperCase(char* key,int len)
{
    for(int i=0;i<len;i++)
        key[i]=toupper(key[i]);
}

//called in the qsort function to sort they key according to alphabetical order
int compareChar(const void *a, const void *b) 
{
    return ((*(char*)a) - (*(char*)b));
}

int isAlphabetic(const char* str) 
{
    for (int i=0;str[i]!='\0';i++) 
    {
        if (!isalpha(str[i])) 
            return 0;  // Not alphabetic
    }
    return 1;  // Alphabetic
}


int Columnar(void)
{
    char text[MAX_TEXT_LENGTH],key[MAX_KEY_LENGTH];
    int ch;

    printf("Enter the plain-text:");
    scanf(" %[^\n]",text);
    printf("Enter the key(only alphabets):");
    scanf("%s",key);

    if (!isAlphabetic(key)) 
    {
        printf("Key should only contain alphabetic characters.\n");
        return 1;  // Exit with an error code
    }

    int len_k=strlen(key);
    int len_txt=strlen(text);
    int row=(int)ceil((double)len_txt/len_k);
    UpperCase(key,len_k);
    
    printf("1]Encrypt\n2]Decrypt\nEnter the choice:");
    scanf("%d",&ch);

    switch(ch)
{
    case ENCRYPT:
    {
        node* heads[len_k];

        //linked lists to store the columns mapped to their characters' in the key
        for(int i=0;i<len_k;i++)
        {   heads[i]=NULL;
            int j=i;
            while(j<len_txt)
            {
                heads[i] = append(heads[i],text[j]);
                j=j+(len_k);
            }
        }

        //creating an array-order to store the position of the key characters in their alphabetical order
        int order[len_k];
        for (int i=0;i<len_k;i++) 
            order[i] = i;

        //change the order array based on the alphabetical order of key
        for (int k = 0; k < len_k - 1; k++) 
        {   int tmp = k;
            for (int j=k+1; j < len_k; j++) 
            {
                if (key[order[j]] < key[order[tmp]]) 
                tmp = j;
            }
            int temp = order[k];
            order[k] = order[tmp];
            order[tmp] = temp;
        }

        //printing the encrypted text according to the alphabetical order of keys
        printf("The encrypted text is: ");
        for(int i=0;i<len_k;i++)
            display(heads[order[i]]);
        printf("\n");
        //freeing memory
        for(int i=0;i<len_k;i++)
            emptyList(heads[i]);
        
    }
    break;
    case DECRYPT:
    {
        node* heads[len_k];
        int order[len_k];
        char dup_key[len_k];

        //dup_key is a dulicate of the key to manipulate it
        strcpy(dup_key,key);

        //rearrange the key based on alphabetical order
        qsort(dup_key,len_k,1,compareChar);

        //store the order of the keys according to the original order
        for (int i=0;i<len_k;i++) 
        {   
            for (int j=0;j<len_k;j++) 
            {
                if (key[i]== dup_key[j]) 
                    order[i]=j;
            }   
        }
        
        //linked list to store the deciphered text
        for(int i=0;i<len_k;i++)
        {   
            heads[i]=NULL;
            for(int j=0;j<len_k;j++)
            {   
                int temp=(order[j]*len_k)+i;
                heads[i] = append(heads[i],text[temp]);
            }
        }

        //print the decrypted message by reading each column
        printf("The decrypted text: ");
        for(int i=0;i<len_k;i++)
            display(heads[i]);
        printf("\n");
        
        //freeing memory
        for(int i=0;i<len_k;i++)
            emptyList(heads[i]);
        
    }
    break;
    default:
        printf("invalid");
    break;
    }


return 0;

}

#endif /* COLUMNAR_CIPHER_H */