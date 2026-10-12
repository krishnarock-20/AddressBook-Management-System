#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <unistd.h>

// Initialize address book by loading data from file
void initialize(AddressBook *addressBook) 
{
    // populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook); // Load saved contacts 
    
}

void loading()
{
    char temp[30];
    for(int i = 0; i <= 100; i++)
    {
        printf("Loading............. %d%%\r",i);
        fflush(stdout); 
        usleep(10000);
    }
}
//Function definition to display all contacts
void listContacts(AddressBook *addressBook) 
{
    
    if(addressBook->contactCount > 0)
    {
        // Bubble sort contacts by name
        for (int i = 0; i < addressBook->contactCount - 1; i++)
        {
            for(int j = 0; j < addressBook->contactCount - i - 1; j++)
            {
                if(strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name) > 0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                    addressBook->contacts[j + 1] = temp;
                }
            }
        }

        loading();
        //After sorting print all conatcts
        
        printf("Loaded Successfully\n");
        printf("--------------------------------------------------------\n");
        printf("|                         List                         |\n");
        printf("--------------------------------------------------------\n");
        printf("%-7s%-20s%-15s%-25s\n","Sl.No","Name","Phone","Email");
       
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            printf("%-7d%-20s%-15s%-25s\n",
                   i + 1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
        }

        printf("--------------------------------------------------------\n");
    }
    else
    {
        printf("No contacts\n");
    }
}




// void saveAndExit(AddressBook *addressBook) {
//     saveContactsToFile(addressBook); // Save contacts to file
//     exit(EXIT_SUCCESS); // Exit the program
// }
//Validate name(only character, space, and dot allowed)
int validate_name(char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || name[i] == ' ' || name[i] == '.'))
        {
            return 0;// if name invalid retun 0
        }
    }
    return 1;// if name is valid return 1
}

// Check duplicate phone number
int isDuplicate_phone(AddressBook *addressBook, char *phone)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 1;//if duplicate found return 1
        }
    }
    return 0;// i phone number is unique return 0
}

// Validate mobile number (10 digits only)
int validate_mobile(char *mobile)
{
    int i;
    if (strlen(mobile) != 10)//length of the mobile number should be 10 digits
    {
        return 0;
    }
    for (i = 0; mobile[i] != '\0'; i++)
    {
        if (!(mobile[i] >= '0' && mobile[i] <= '9'))//Number should be digits only
        {
            return 0;// for invalid return 0
        }
    }
    return 1;//for valid number return 1
}

// Check duplicate email
int isDuplicate_mail(AddressBook *addressBook, char *mail)
{
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if((strcmp(mail, addressBook->contacts[i].email)) == 0)
        {
            return 1;//if duplicate found return 1
        }
    }
    return 0;//for unique mail return 0
}

// Validate email format
int validate_mail(char *mail)
{
    int i;
    int at = -1, dot = -1, count = 0;
    for (i = 0; mail[i] != '\0'; i++)
    {
         // Allow lowercase, digits, '@' and '.'
        if(!((mail[i] >= 'a' && mail[i] <= 'z') || mail[i] == '@' || (mail[i] >= '0' && mail[i] <='9')|| mail[i] == '.' ))
        {
            return 0;
        }
        if(mail[i] == '@')
        {
            at = i;
            count++;
        }
        if(mail[i] == '.')
        {
            dot = i;
            count++;
        }
    }
    if(strcasestr(mail, ".com") == NULL)//Email must contain ".com"
    {
        return 0;
    }
    if(at == 0 || dot == 0 || count != 2 || mail[dot - 1] == '@')
    {
        return 0;
    } 
    for(int i = at + 1; i < dot; i++)
    {
        if(!(mail[i] >= 'a' && mail[i] <= 'z'))
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    // Create a new contact
    char name[20];
    int valid;

    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]",name);// Read name from user
        valid = validate_name(name);
        if(valid == 1)// if name is valid then break
            break;
    }

    char mobile[11];
    int m_valid;

    while(1)
    {
        printf("Enter the mobile number : ");
        scanf(" %[^\n]",mobile);// Read mobile number from user
        m_valid = validate_mobile(mobile);//call function to validate mobile number
        if(m_valid == 0)
        {
            printf("Not valid!\n");
            continue;

        }
        //check for duplicate number
        if(isDuplicate_phone(addressBook, mobile))
        {
            printf("Number is already exist\n");
            continue;
        }
        break; 
    }

    char mail[30];
    int mail_valid;
    while(1)
    {

        printf("Enter the mail id: ");
        scanf(" %[^\n]",mail);//Read mail id from user
        mail_valid = validate_mail(mail);
        if(mail_valid == 0)
        {
            printf("Not valid!\n");
            continue;
        }
        //check for dupliacte mail id
        if(isDuplicate_mail(addressBook, mail))
        {
            printf("Email is already exist\n");
            continue;
        }
        break;
           
    }
    //After validation store name, number, and mail id in structure
    strcpy(addressBook->contacts[addressBook->contactCount].name,name );
    strcpy(addressBook->contacts[addressBook->contactCount].phone,mobile);
    strcpy(addressBook->contacts[addressBook->contactCount].email,mail );
    addressBook->contactCount++;//Increment contactcount
    printf("Contacts added successfully\n");
}

// Function to search contact by name
int search_by_name(AddressBook *addressBook)
{
    char name[50];
    printf("Enter the name: ");
    scanf(" %[^\n]",name); // Read full string (including spaces)
        if(addressBook -> contactCount == 0)//Check if addressbook is empty
        {
            printf("List is empty\n");
            return -2;
        }

        int s = 1, count = 0, ind[100];// s: serial no, count: matches, ind: store index
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].name, name) != NULL)
            {
                printf("%-7d%-15s%-20s%-25s\n", s++, // Print matched contact
                        addressBook->contacts[i].name, 
                        addressBook->contacts[i].phone, 
                        addressBook->contacts[i].email);
                ind[count++] = i;// Store index and increment count
            }
        }
        if(count == 0)// No matches found
        {
            return -1;
        }
        else if(count == 1)//if only one match 
        {
            return ind[0];//return index value
        }
        else
        {
            int choice;
            printf("Multiple contacts found\n");
            printf("Enter the serial number to select contact\n");
            scanf("%d",&choice);// User selects one contact
            if(!(choice > 0 && choice <= count)) //choice should be above 0 
            {
                printf("Invalid choice\n");
                return -2;
            }
            int select_ind = ind[choice - 1];// Get selected index
            printf("Selected contacts:\n");
            printf("%-7d%-15s%-20s%-25s\n",1,addressBook->contacts[select_ind].name, addressBook->contacts[select_ind].phone,addressBook->contacts[select_ind].email);
            return select_ind;// Return selected index
        }   
}

int search_by_phone(AddressBook *addressBook)
{
    char mobile[100];
    printf("Enter the mobile number : ");
    scanf(" %[^\n]",mobile);// Read mobile number to search 
        if(addressBook -> contactCount == 0)// No contacts found
        {
            printf("List is empty");
            return -2;
        }

        int s = 1, count = 0, ind[100];
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].phone, mobile) != NULL)
            {
                printf("%-7d%-15s%-20s%-25s\n", s++, //print matched contacts
                        addressBook->contacts[i].name, 
                        addressBook->contacts[i].phone, 
                        addressBook->contacts[i].email);
                ind[count++] = i;//store index value in array of integers
                
            }
        }
        if(count == 0)
        {
            return -1;//if no matches
        }
        else if(count == 1)//if only one contact matched return first index
        {
            return ind[0];
        }
        else
        {
            //For multiple contacts -- read serial number to select contact
            int choice;
            printf("Multiple contacts found\n");
            printf("Enter the serial number to select contact\n");
            scanf("%d",&choice);
            if(!(choice > 0 && choice <= count))
            {
                printf("Invalid choice\n");
                return -2;
            }
            int select_ind = ind[choice - 1];
            printf("Selected contacts:\n");
            //print particular selected contact
            printf("%-7d%-15s%-20s%-25s\n",1,
                    addressBook->contacts[select_ind].name, 
                    addressBook->contacts[select_ind].phone,
                    addressBook->contacts[select_ind].email);
            return select_ind; // return index
        } 
}

int search_by_mail(AddressBook *addressBook)
{
    char mail[50];

    printf("Enter the mail id: ");
    scanf(" %[^\n]",mail);// Read mail id to search
        if(addressBook -> contactCount == 0)// no matches
        {
            printf("List is empty");
            return -2;
        }

        int s = 1, count = 0, ind[100];
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcasestr(addressBook->contacts[i].email, mail) != NULL)
            {
                printf("%-7d%-15s%-20s%-25s\n", s++, // print matched contacts
                        addressBook->contacts[i].name, 
                        addressBook->contacts[i].phone, 
                        addressBook->contacts[i].email);
                ind[count++] = i;// store index value in array 
            }
        }
        if(count == 0)
        {
            return -1;
        }
        else if(count == 1)//only one contact matched return its inedx
        {
            return ind[0];
        }
        else
        {
            //For multiple contacts, choose serial number to selcect particular contact
            int choice;
            printf("Multiple contacts found\n");
            printf("Enter the serial number to select contact\n");
            scanf("%d",&choice);
            if(!(choice > 0 && choice <= count))
            {
                printf("Invalid choice\n");
                return -2;
            }
            int select_ind = ind[choice - 1];
            printf("Selected contacts:\n");
            //print particular selected  contact
            printf("%-7d%-15s%-20s%-25s\n",1,
                    addressBook->contacts[select_ind].name, 
                    addressBook->contacts[select_ind].phone,
                    addressBook->contacts[select_ind].email);
            return select_ind;//return index value
        }
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
   int option;
    
   printf("Search by :\n");//select option to seacrh
   printf("1.Name\n2.Phone\n3.Mail\n");
   scanf("%d", &option);

   switch(option)
   {
    case 1:
    // if user selects 1 , call function to search by name
        if(search_by_name(addressBook) == -1)
        {
            printf("Name is not present\n");
            break;
        }
        else
        {
            break;
        }
    case 2:
    //if user selects 2, call function to search by phone
        if(search_by_phone(addressBook) == -1)
        {
            printf("Number is not present\n");
            break;
        }
        else
        {
            break;
        }
       
    case 3:
    //if user selects 3, call function to search by mail id
        if(search_by_mail(addressBook) == -1)
        {
            printf("Number is not present\n");
            break;
        }
        else
        {
            break;
        }
    default:
        printf("Invalid Input");
   }
}

void edit_name(AddressBook *addressBook, int n)// n = index of contact
{
    char new_name[100];//Read new name to edit
    int valid;
    while(1)//Loop until valid name
    {
        printf("Enter the new name : ");
        scanf(" %[^\n]",new_name);
        valid = validate_name(new_name);// validate name
        if(valid == 1)// valid
            break;
    }
    strcpy(addressBook->contacts[n].name,new_name);// Update the new name

}
//Function definition to edit particular number in matched index
void edit_phone(AddressBook *addressBook, int n)
{
    char new_mobile[100];
    int valid;
    while(1)
    {
        printf("Enter the new Mobile number : ");
        scanf(" %[^\n]",new_mobile);//Read the new mobile number to edit
        valid = validate_mobile(new_mobile);// validate
        if(valid == 1)// valid
            break;
    }
    strcpy(addressBook->contacts[n].phone,new_mobile);//Update the new mobile number 
}

void edit_mail(AddressBook *addressBook, int n)
{
    char new_mail[100];
    int valid;
    while(1)
    {
        printf("Enter the new mail id: ");
        scanf(" %[^\n]",new_mail);// Read new mail id from user
        valid = validate_mail(new_mail);// validate the mail id
        if(valid == 1)// valid
            break;
    }
    strcpy(addressBook->contacts[n].email,new_mail);// update the new mail id
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    int ind;//declare ind variable to store index value
    while(1)
    {
    int ch;
    
        printf("Search by: \n1.Name\n2.Phone\n3.Mail\n");
        printf("Enter the option : \n");
        scanf("%d",&ch);
       
        switch(ch)
        {
        case 1:
            while(1)
            {
                ind = search_by_name(addressBook);//call function and collect the particular index
                if(ind == -1)
                {
                    printf("No matches found\n");
                    printf("Please Enter the vaid name: \n");
                    continue;
                }
            break;
            }
        break;
        case 2:
            while(1)
            {
                ind = search_by_phone(addressBook);//call function and collect the particular index
                if(ind == -1)
                {
                    printf("No matches found\n");
                    printf("Please Enter the valid Mobile number :\n");
                    continue;
                }
            break;
            }
        break;
        case 3:
            while(1)
            {
                ind = search_by_mail(addressBook);//call function and collect the particular index
                if(ind == -1)
                {
                    printf("No matches found");
                    printf("Please Enter the valid mail id :\n");
                    continue;
                }
            break;
            }
        break;
        default:
            printf("Invalid option\n");
            continue;
        }
        break;
    }
    
    printf("Select the field to edit:\n");
    //Select what do you want to edit
    printf("1.Name\n2.Phone\n3.Email\n4.Exit\n");
    int op;
    printf("Enter the option: \n");
    scanf("%d",&op);//select option to edit 

    
    switch(op)
    {
        case 1:
            edit_name(addressBook,ind);//Edit the name at particular index
            break;
        case 2:
            edit_phone(addressBook,ind);//Edit the mobile number at particular index
            break;
        case 3:
            edit_mail(addressBook,ind);//Edit the mail id at particular index
            break;
        case 4:
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

void delete_name(AddressBook *addressBook, int n)
{
    //start the loop from matched index and shift left
    for(int i = n; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;//Decrement count

}

void delete_mobile(AddressBook *addressBook, int n)
{
    //start the loop from matched index and shift left
    for(int i = n; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;//Decrement count
    
}

void delete_mail(AddressBook *addressBook, int n)
{
    //start the loop from matched index and shift left
    for(int i = n; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;//Decrement count

}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int ch;
    int ind;
    printf("Search by: \n1.Name\n2.Phone\n3.Mail\n");
    while(1)
    {
        printf("Enter the option : \n");
        scanf("%d",&ch);
       
        switch(ch)
        {
        case 1:
            while(1)
            {
                ind = search_by_name(addressBook);//call function to search name and store index value
                if(ind >= 0)
                {
                    delete_name(addressBook,ind);//call function to delete contact
                }
                if(ind == -1)
                {
                    printf("No matches found\n");
                    printf("Please Enter the vaid name: \n");
                    continue;
                }
                break;
            }
        break;
        case 2:
            while(1)
            {
                ind = search_by_phone(addressBook);//call function to search mobile number and store index value
                if(ind >= 0)
                {
                    delete_mobile(addressBook, ind);//callfunction to delete
                }
                if(ind == -1)
                {
                    printf("No matches found\n");
                    printf("Please Enter the valid Mobile number :\n");
                    continue;
                }
                break;
            } 
        break;
        case 3:
            while(1)
            {
                ind = search_by_mail(addressBook);//call function to search mail id and store index value
                if(ind >= 0)
                {
                    delete_mail(addressBook,ind);//call function to delete contact
                }
                if(ind == -1)
                {
                    printf("No matches found\n");
                    printf("Please Enter the valid Mobile number :\n");
                    continue;
                }
                break;
            }  
        break;
        default:
            printf("Invalid option\n");
            continue;
        }

    break;
    }
}