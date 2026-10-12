#include <stdio.h>
#include "file.h"

//Function to save all contacts from memory into file.
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.txt","w");//Opens file in write mode ("w") → creates new file / overwrites existing data.
    
    if(fptr == NULL)//Checks if file opening failed.
    {
        perror("File open failed\n");
        return;
    }
    fprintf(fptr, "#%d\n", addressBook->contactCount);//Writes total number of contacts at top of file
    //Loop to save all contacts to file
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", 
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
    }
    fclose(fptr);
}

//Function to load contacts from file into memory.
void loadContactsFromFile(AddressBook *addressBook) 
{
       //Initialize count to 0 before loading
        addressBook->contactCount = 0;
        FILE *fptr = fopen("contacts.txt","r");//Opens file in read mode ("r").
        if(fptr == NULL)
        {
            perror("File open failed\n");
            return;
        }
        char first_ch[50];//Buffer to store first line of file.
        fscanf(fptr, "%[^\n]\n", first_ch);
        
        while (fscanf(fptr, " %[^,],%[^,],%[^\n]",
        addressBook->contacts[addressBook->contactCount].name,
        addressBook->contacts[addressBook->contactCount].phone,
        addressBook->contacts[addressBook->contactCount].email) == 3)//Stores values into structure ensures all 3 fields are read successfully.
        {
            addressBook->contactCount++;//increment count
        }
        
        fclose(fptr);
        printf("Loaded contacts: %d\n", addressBook->contactCount);
    }
