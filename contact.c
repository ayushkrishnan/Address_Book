#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>


int newindex[MAX_CONTACTS]={0};
int count=0;

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria

    switch(sortCriteria)
    {
        case 1:
            printf("\n NAME \t Phone Number \t Email");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                printf("\n%s\t%s\t%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
        case 2:
            
                //case 1:
                    printf("\nNAME");
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        printf("\n%s",addressBook->contacts[i].name);
                    }
                    break;
               // case 2:
                    printf("\nNAME \t Phone NO");
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        printf("\n%s \t %s",addressBook->contacts[i].name,addressBook->contacts[i].phone);
                    }
                    break;
               // case 3:
                    printf("\nNAME \t EMAIL");
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        printf("%s \t %s",addressBook->contacts[i].name,addressBook->contacts[i].email);
                    }
                    break;
            //}
            break;
        
        case 3:

            printf("\n NAME \t Phone Number \t Email");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                for(int j=i+1;j<addressBook->contactCount;j++)
                {
                    if(addressBook->contacts[i].phone>addressBook->contacts[j].phone)
                        printf("\n%s\t%s\t%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;
        
        case 4:
    
            printf("\n NAME \t Phone Number \t Email");
            for(int i=0;i<addressBook->contactCount;i++)
            {
                for(int j=i+1;j<addressBook->contactCount;j++)
                {
                    if(addressBook->contacts[i].email>addressBook->contacts[j].email)
                        printf("\n%s\t%s\t%s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
            }
            break;


    }

    
}

// void initialize(AddressBook *addressBook) {
//     addressBook->contactCount = 0;
//    // populateAddressBook(addressBook);
    
//     // Load contacts from file during initialization (After files)
//     //loadContactsFromFile(addressBook);
// }

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int is_valid_name(char * ne_name)
{
    int alpha;
    int i=0;
            while(ne_name[i])
            {
                alpha=0;
                if(isalpha(ne_name[i]))
                {
                    alpha=1;
                }
                i++;
            }
    return alpha;
}

int is_valid_phone(char *ph_no)
{
    int digit,i=0;
    while(ph_no[i])
    {
        digit=0;
        if(isdigit(ph_no[i]))
        {
            digit=1;
        }
        i++;
    }
    return digit;
}

int is_unique(char check[],AddressBook *addressBook)
{
    for(int i=0;i< addressBook->contactCount;i++)
    {
        if(strcmp(check,addressBook->contacts[i].phone)==0)
        {
            return 0;
        }
        if(strcmp(check,addressBook->contacts[i].email)==0)
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char new_name[50],new_phone[20],new_mail[50];
    int phlen;
    char *emaill;
    char *emcom;
    
        label_name:
        printf("Enter the Name:");
        //scanf("%s",addressBook->contacts[i].name);
        scanf("%s",new_name);
        int i=0,alpha=0;
        alpha=is_valid_name(new_name);
        if(alpha)
        {
            strcpy(addressBook->contacts[addressBook->contactCount].name,new_name);
            
            label_phoneno:
            printf("Enter the Phone Number:");
            //scanf("%s",addressBook->contacts[i].phone);
            scanf("%s",new_phone);
            phlen=strlen(new_phone);
            if(phlen==10)
            {
                int digit=is_valid_phone(new_phone);
                if(digit)
                {
                    if(is_unique(new_phone,addressBook) )
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
        
                            int alphanum=isalnum(*(emaill-1));
                           
                            if(alphanum)
                            {
                                int alphanum2=isalnum(*(emcom-1));
                                if(alphanum2)
                                {
                                    
                                    if(is_unique(new_mail,addressBook))
                                    {
                                        strcpy(addressBook->contacts[addressBook->contactCount].email,new_mail);
                                        printf("Contact Created successfully \n");
                                        addressBook->contactCount++;
                                    }
                                    else{
                                        printf("The email id is already existing\n");
                                        goto label_email;
                                    }
                                }
                                else{
                                    printf("Email should contain domain name\n");
                                    goto label_email;
                                }
                            }
                            else{
                                printf("Email should contain characters in front of @\n");
                                goto label_email;
                            }
                        }
                        else
                        {
                            printf("Email should contain @ and .com\n");
                            goto label_email;
                        }
                    }
                    else
                    {
                        printf("The Phone Number already exist\n");
                        goto label_phoneno;
                    }
                }
                else{
                    printf("The Phone number contain other than digits,Please enter digits only\n");
                    goto label_phoneno;
                }
            }
            else{
                printf("The Phone number should be 10 digits\n");
                goto label_phoneno;
            }

           
            //scanf("%s",addressBook->contacts[i].email);
        }
        else
        {
            printf("Name Should Contain Alphabetic elements only\n");
            goto label_name;
        }
}

int search(char ele[],int opt,AddressBook *addressBook)
{
    printf("The option is %d\n",opt);
    printf("The input inside the fucntion %s\n",ele);
    switch(opt)
    {
        case 1:
        {
            int j=0;
            int i;
            for(i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(ele,addressBook->contacts[i].name)==0)
                {
                    newindex[j++]=i;
                    
                }
            }
            return i;
        }
        break;
        case 2:
        {
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(ele,addressBook->contacts[i].phone)==0)
                {
                    return i;
                }
            }

        }
        break;
        case 3:
        {

           printf("THE given email => %s",ele);
           int len = strlen(ele);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                //printf("%d %s\n",i,addressBook->contacts[i].email);
                if(strncmp(ele,addressBook->contacts[i].email,len)==0)
                {
                    return i;
                }
            }
        }
    //return 0;
    }
    return 0;
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char nameser[50],phoneser[50],emailser[50];
    printf("1.Search By NAME:\n2.Search By Phone_NO\n3.Search By Email\n");
    printf("Enter the choice:\n");
    int sercho,ret=0;
    scanf("%d",&sercho);
    switch(sercho)
    {
        case 1:
            int i=0;
            printf("Enter the name to be searched:");
            scanf("%s",nameser);
            ret=search(nameser,1,addressBook);
            if(ret)
            {
                printf("\n%d \t %s \t %s \t %s",ret,addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
                //addcount
                //newindex[i++]=ret;
                count++;

            }
            else{
                printf("\nNOT FOUND!!");
            }
            //stringcmp(nameser,addressBook->contacts[0].name);
            break;
        case 2:
        {
            int i=0;
            printf("Enter the Phone Number:");
            scanf("%s",phoneser);
            ret=search(phoneser,2,addressBook);
            if(ret)
            {
                printf("\n%d \t %s \t %s \t %s",ret,addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
                //newindex[i++]=ret;
                //count++;
            }
            else{
                printf("\nNOT FOUND!!");
                return 0;
            }
            break;
        }
        case 3:
           // getchar();
           //__fpurge(stdin);
            printf("Enter the Email id to be searched:");
            scanf(" %s",emailser);
            printf("The readed email id => %s",emailser);
            ret=search(emailser,3,addressBook);
            if(ret)
            {
                printf("\n%d \t %s \t %s \t %s",ret,addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
            }
            else{
                printf("\nNOT FOUND!!");
                return 0;
            }
            break;
        default:
            printf("\nInvalid Choice\n");

    }
    
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char edname[50],edphno[20],edmail[50];
    if(searchContact(addressBook))
    {
        printf("1.Edit Name\n2.Edit Phone Number\n3.Edit Email\n");
        printf("Enter the choice:");
        int edcho,alpha;
        scanf("%d",&edcho);
        switch(edcho)
        {
            case 1:
            
                printf("Enter the New Name :");
                scanf("%s",edname);
                int i=0;
                alpha=is_valid_name(edname);
                if(alpha)
                {
                    strcpy(addressBook->contacts[newindex[i]].name,edname);
                    printf("%d \t %s \t %s \t %s",i,addressBook->contacts[newindex[i]].name,addressBook->contacts[newindex[i]].phone,addressBook->contacts[newindex[i]].email);
                    printf("Name is updated succesfully");
                
                }
                else{
                    printf("Name Contains other elements");
                }
                break;
        
            case 2:
                
                label_edphno:
                printf("Enter the new phone number");
                scanf("%s",edphno);
                int phlen;
                phlen=strlen(edphno);
                if(phlen==10)
                {
                    i=0;
                    int digit=is_valid_phone(edphno);
                    if(digit)
                    {
                        if(is_unique(edphno,addressBook))
                        {
                            strcpy(addressBook->contacts[newindex[i]].phone,edphno);
                        }
                        else{
                            printf("Number Already exist\n");
                            goto label_edphno;
                        }
                    }
                    else{
                        printf("\nNumber should contain only digits");
                    }
                }
                else{
                    printf("\nThe Numeber should contain 10 elements");
                }

                break;

            case 3:
                label_email1:
                i=0;
                printf("Enter the new Email");
                char *emaill,*emcom;
                        emaill=strchr(edmail,'@');
                        emcom=strstr(edmail,".com");
                        if(emaill && emcom)
                        {
                            int alphanum=isalnum(emaill-1);
                            if(alphanum)
                            {
                                int alphanum2=isalnum(emcom-1);
                                if(alphanum2)
                                {
                                    if(is_unique(edmail,addressBook))
                                    {
                                        strcpy(addressBook->contacts[newindex[i]].email,edmail);
                                        printf("Email updated successfully ");
                                        //addressBook->contactCount++;
                                    }
                                    else{
                                        printf("The email id is already existing");
                                        goto label_email1;
                                    }
                                }
                                else{
                                    printf("Email should contain domain name");
                                    goto label_email1;
                                }
                            }
                            else{
                                printf("Email should contain characters in front of @");
                                goto label_email1;
                            }
                        }
                        else
                        {
                            printf("Email should contain @ and .com");
                            goto label_email1;
                        }
        }
     }
     else{
        return;
    }
}

void delete(int indexx,AddressBook *addressBook)
{
    for(int i=indexx;i<addressBook->contactCount;i++)
    {
        strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
        strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
        strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
        if(searchContact(addressBook))
        {
            printf("\n1.Delete by Name\n2.Delete by Phone\n3.Delete by email\n");
            int cho,size;
            printf("Enter the Choice:");
            scanf("%d",&cho);
            switch(cho)
            {
                case 1:
                    int i=0;
                    char delname[50];
                    printf("Enter the Name:");
                    scanf("%s",delname);
                    int ret=search(delname,1,addressBook);
                    if(ret)
                    { 
                        delete(ret,addressBook);
                        printf("Deleted Succes fully");
                    }

                    break;
                case 2:
                    char delphno[20];
                    printf("Enter the Phone number:");
                    scanf("%s",delphno);
                    ret=search(delphno,2,addressBook);
                    if(ret)
                    {
                        delete(ret,addressBook);
                        printf("Deleted Succesfully");
                        return;
                    }
                    break;
                case 3:

                    char delem[50];
                    printf("Enter the email:");
                    scanf("%s",delem);
                    ret=search(delem,3,addressBook);
                    if(ret)
                    {
                        delete(ret,addressBook);
                        printf("Deleted succesfully");
                        return;
                    }
                
            }
        }

   
}
