#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    printf("1.List all the contact details");
    printf("\n2.Print by category");
    printf("\n3.Print Specfic contacts");
    int lich;
    printf("\nEnter the list choice:");
    scanf("%d",&lich);
    switch(lich)
    {
        case 1:
            printf("NAME \t Phone Number \t Email");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                printf("\n %s\t%s\t%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
        case 2:
            printf("1.Print Name's");
            printf("2.Phone No");
            printf("3.Email");
            int catch;
            printf("Enter the choice:");
            scanf("%d",&catch);
            switch(catch)
            {
                case 1:
                    printf("NAME");
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        printf("\n%s",addressBook->contacts[i].name);
                    }
                    break;
                case 2:
                    printf("NAME \t Phone NO");
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        printf("\n%s \t %s",addressBook->contacts[i].name,addressBook->contacts[i].phone);
                    }
                    break;
                case 3:
                    printf("NAME \t EMAIL");
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        printf("%s \t %s",addressBook->contacts[i].name,addressBook->contacts[i].email);
                    }
                    break;
            }
            break;
        
        case 3:
            printf("1.By NAME");


    }

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int is_valid_name(char * ne_name)
{
    return 1;
}

int is_unique(char check[],AddressBook *addressBook)
{
    for(int i=0;i< addressBook->contactCount;i++)
    {
        if(strcmp(check,addressBook->contacts[i].phone)==0)
        {
            return 1;
        }
        if(strcmp(check,addressBook->contacts[i].email)==0)
        {
            return 1;
        }
    }
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char new_name[50],new_phone[50],new_mail[50];
    int phlen;
    char *emaill;
    char *emcom;
    
        label_name:
        printf("Enter the Name:");
        //scanf("%s",addressBook->contacts[i].name);
        scanf("%s",new_name);
        int i=0,alpha=0;
        while(new_name[i])
        {
            alpha=0;
            if(isalpha(new_name[i]))
            {
                alpha=1;
            }
            i++;
        }
        if(alpha)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,new_name);
            
            label_phoneno:
            printf("\nEnter the Phone Number:");
            //scanf("%s",addressBook->contacts[i].phone);
            scanf("%s",new_phone);
            phlen=strlen(new_phone);
            if(phlen==10)
            {
                i=0;
                int digit=0;
                while(new_phone[i])
                {
                    digit=0;
                    if(isdigit(new_phone[i]))
                    {
                        digit=1;
                    }
                    i++;
                }
                if(digit)
                {
                    if(is_unique(new_phone,addressBook))
                    {
                        strcpy(addressBook->contacts[addressBook->contactCount].phone,new_phone);

                        label_email:
                        printf("Enter the Email:");
                        scanf("%s",new_mail);
                        //int *emaill,*emcom;
                        emaill=strchr(new_mail,'@');
                        emcom=strstr(new_mail,".com");
                        if(emaill && emcom)
                        {
                            int alphanum=isalnum(emaill-1);
                            if(alphanum)
                            {
                                int alphanum2=isalnum(emcom-1);
                                if(alphanum2)
                                {
                                    if(is_unique(new_mail,addressBook))
                                    {
                                        strcpy(addressBook->contacts[addressBook->contactCount].email,new_mail);
                                        printf("Contact Created successfully ");
                                        addressBook->contactCount++;
                                    }
                                    else{
                                        printf("The email id is already existing");
                                        goto label_email;
                                    }
                                }
                                else{
                                    printf("Email should contain domain name");
                                    goto label_email;
                                }
                            }
                            else{
                                printf("Email should contain characters in front of @");
                                goto label_email;
                            }
                        }
                        else
                        {
                            printf("Email should contain @ and .com");
                            goto label_email;
                        }
                    }
                    else
                    {
                        printf("The Phone Number already exist ");
                        goto label_phoneno;
                    }
                }
                else{
                    printf("The Phone number contain other than digits,Please enter digits only");
                    goto label_phoneno;
                }
            }
            else{
                printf("The Phone number should be 10 digits");
                goto label_phoneno;
            }

           
            //scanf("%s",addressBook->contacts[i].email);
        }
        else
        {
            printf("\nName Should Contain Alphabetic elements only");
            goto label_name;
        }
}

int search(char ele[],int opt,AddressBook *addressBook)
{
    if(opt==1)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(ele,addressBook->contacts[i].name)==0)
            {
                return i;
            }
        }
    }
    if(opt==2)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(ele,addressBook->contacts[i].phone)==0)
            {
                return i;
            }
        }

    }
    if(opt==3)
    {
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(ele,addressBook->contacts[i].name)==0)
            {
                return i;
            }
        }
    }
    return 0;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char nameser[50],phoneser[50],emailser[50];
    printf("1.Search By NAME:\n2.Search By Phone_NO\n3.Search By Email");
    printf("Enter the choice:");
    int sercho,ret;
    scanf("%d",&sercho);
    switch(sercho)
    {
        case 1:
            printf("Enter the name to be searched:");
            scanf("%s",nameser);
            ret=search(nameser,1,addressBook);
            if(ret)
            {
                printf("\n %s \t %s \t %s",addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
                
            }
            else{
                printf("\nNOT FOUND!!");
            }
            //stringcmp(nameser,addressBook->contacts[0].name);
            break;
        case 2:
            printf("Enter the Phone Number:");
            scanf("%s",phoneser);
            ret=search(phoneser,2,addressBook);
            if(ret)
            {
                printf("\n %s \t %s \t %s",addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
            }
            else{
                printf("\nNOT FOUND!!");
            }
            break;
        case 3:
            printf("Enter the Email id to be searched:");
            scanf("%s",emailser);
            ret=search(emailser,3,addressBook);
            if(ret)
            {
                printf("\n %s \t %s \t %s",addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
            }
            else{
                printf("\nNOT FOUND!!");
            }
            break;
        default:
            printf("Invalid Choice");

    }
    
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char edname[50];
    searchContact(addressBook);
    printf("1.Edit Name\n2.Edit Phone Number\n3.Edit Email");
    printf("Enter the choice:");
    int edcho;
    scanf("%d",edcho);
    switch(edcho)
    {
        case 1:
            
            printf("Enter the Person who's Name to be changed");
            scanf("&s",edname);


    }
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    while(1)
    {
        printf("\n1.ID");
        printf("\n2.Name");
        printf("\n3.Exit");
        int cho,size;
        printf("Enter the Choice:");
        scanf("%d",&cho);
        switch(cho)
        {
            case 1:
                char delname[50];
                printf("Enter the ID:");
                scanf("%s",delname);
                for(int i=0;i<size;i++)
                if(1)
                {
                        printf("k");
                }
        }
    }

   
}
