/*
NAME:Ayush Krishnan
DATE:26/AUG/2025
DESC:Address book project
*/

#include <stdio.h>
#include <stdio_ext.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice,sortChoice;
    
    //Datatype   variable
    AddressBook addressBook;
     
    //intilaizing the addressbook count as 0.
    addressBook.contactCount=0;
    loadContactsFromFile(&addressBook);  //Load the contacts to the struct

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        __fpurge(stdin);
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:  
                printf("1.List All items given order \n2.List items by Name \n3.List items By phone Number \n4.List items Email\n");
                //int lich;
                printf("Enter the list choice:");
                //scanf("%d",&lich);
                scanf("%d",&sortChoice);
                listContacts(&addressBook, sortChoice);
                
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("Thankyou \nExiting the program\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                //break;
        }
    } while (choice != 7);
    
       return 0;
    
}
