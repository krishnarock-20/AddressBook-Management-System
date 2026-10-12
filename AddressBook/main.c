/*  Title       : Address Book Management System
    Name        : Shrikrishna Ranbhare
    Date        : 11/04/2026
    ID          : 26001_120
    Description : This project is a console-based Address Book application developed in C.
                  It allows users to manage contact details efficiently using fundamental
                  programming concepts such as structures, arrays, pointers, file handling,
                  and string manipulation.

                  The Address Book stores multiple contacts, where each contact consists of
                  a name, phone number, and email address. The application provides a
                  user-friendly menu-driven interface to perform various operations.
                  This addressBook allows us to:
                  1. Create contact                                     
                  2. Search contact                                     
                  3. Edit contact                                       
                  4. Delete contact                                     
                  5. List all contacts                                  
                  6. Save and Exit 

*/

#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    


    do 
    {
        printf("--------------------------------------------------------\n");
        printf("|                   Address Book Menu                  |\n");
        printf("|------------------------------------------------------|\n");
        printf("|1. Create contact                                     |\n");
        printf("|2. Search contact                                     |\n");
        printf("|3. Edit contact                                       |\n");
        printf("|4. Delete contact                                     |\n");
        printf("|5. List all contacts                                  |\n");
    	printf("|6. Save and Exit                                      |\n");		
        // printf("7. Exit\n");
        printf("--------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);//call funtion to creat contact
                break;
            case 2:
                searchContact(&addressBook);//call function to search contact
                break;
            case 3:
                editContact(&addressBook);//call function to edit the contact
                break;
            case 4:
                deleteContact(&addressBook);//call function to delete contact
                break;
            case 5:          
                listContacts(&addressBook);//call function to list out of all contacts
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
    
    return 0;
}