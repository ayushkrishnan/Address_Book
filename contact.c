#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>


int newindex[MAX_CONTACTS]={};
int count=0;


void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    //1.List by given data
    //2.List the elements sorted by name
    //3.List the elments sorted by phone number
    //4.Lizt the elments sorted by email id
    

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
             for (int i = 0; i < addressBook->contactCount - 1; i++) 
            {
             for (int j = i + 1; j < addressBook->contactCount; j++) 
             {
                if (strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) 
                {
                    // Swap whole structs
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
                }
            }
            int slno=1;
            for(int i=0;i<addressBook->contactCount;i++)
            {
                
                printf("\n%d\t%s\t%s\t%s",slno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                slno++;
            } 
            break;
        
        case 3:

            printf("\n NAME \t Phone Number \t Email");
            // qsort(addressBook,addressBook->contactCount,sizeof(addressBook),comparestring);
            for (int i = 0; i < addressBook->contactCount - 1; i++) 
            {
             for (int j = i + 1; j < addressBook->contactCount; j++) 
             {
                if (strcasecmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone) > 0) 
                {
                    // Swap whole structs
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                }
                }
            }
             slno=1;
            for(int i=0;i<addressBook->contactCount;i++)
            {
                printf("\n%d\t%s\t%s\t%s",slno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                slno++;
            }
            break;
        
        case 4:
            slno=1;
            printf("\n NAME \t Phone Number \t Email");
            for(int i=0;i<addressBook->contactCount-1;i++)
            {
                for(int j=i+1;j<addressBook->contactCount;j++)
                {
                    int len=strlen(addressBook->contacts[i].email);
                    if (strncmp(addressBook->contacts[i].email, addressBook->contacts[j].email,len) > 0) 
                    {
                        // Swap whole structs
                        Contact temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
                    
                        printf("\n%d\t%s\t%s\t%s",slno,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        slno++;
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

//This is used to save the newly added contacts or deleted or updated items into file if not done while exit the program the data will be lost and next iteration it will start from the previous contact

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//It will validate the name and check it contains only alphabets
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

//check the emaili only contains lower letters
int is_low(char *emaill)
{
    int low,i=0;
    while(emaill[i])
    {
        
        if (isalpha(emaill[i]) && !islower(emaill[i])) {
            return 0;  // Found an uppercase letter
        }
        i++;
    }
        return 1;  // All alphabetic characters are lowercase
    
}

//Check if phone number is valid
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


//Check the phone number is unique
int is_unique(char check[],AddressBook *addressBook)
{
    for(int i=0;i< addressBook->contactCount;i++)
    {
        if(strcmp(check,addressBook->contacts[i].phone)==0)
        {
            return 0;
        }
    }
    return 1;
}

//check if the email is unique
int is_unique_email(char check[],AddressBook *addressBook)
{
    int len = strlen(check);//to check the upto the length of the given string and to avoid unwanted charaters
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strncmp(check,addressBook->contacts[i].email,len)==0)
        {
            return 0;
        }
    }
    return 1;
}

//Used to create contact it inputs name email and phone number inserts into the struct if both phone and email are unique

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
                        if(is_low(new_mail))
                        {
                            
                        
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
                                    
                                    if(is_unique_email(new_mail,addressBook))
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
                    else{
                        printf("Email contains upper case character\n");
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


//Search the elements accordingly

int search(char ele[],int opt,AddressBook *addressBook)
{

   // printf("The option is %d\n",opt);
   // printf("The input inside the fucntion %s\n",ele);
    switch(opt)
    {
        case 1:
        {
            int j=0;
            int i=0;
            int len = strlen(ele);
            while(i<addressBook->contactCount)
            {
                if(strncmp(ele,addressBook->contacts[i].name,len)==0)
                {
                    newindex[j++]=i;
                    count++;
                    //return i;
                    
                }
                i++;
            }
            //return i;
        }
        // return 1;
        break;

        case 2:
        {
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(ele,addressBook->contacts[i].phone)==0)
                {
                    newindex[0]=i;
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
                    newindex[0]=i;
                    return i;
                }
            }
        }
        return 0;
    }
    return 1;
}

//  int search(char ele[],int opt,AddressBook *addressBook)
// {
//     switch(opt)
//     {
//         case 2:
//         {
//             for(int i=0;i<addressBook->contactCount;i++)
//             {
//                 if(strcmp(ele,addressBook->contacts[i].phone)==0)
//                 {
//                     newindex[0]=i;
//                     return i;
//                 }
//             }

//         }
//         break;
//         case 3:
//         {

//            printf("THE given email => %s",ele);
//            int len = strlen(ele);
//             for(int i=0;i<addressBook->contactCount;i++)
//             {
//                 //printf("%d %s\n",i,addressBook->contacts[i].email);
//                 if(strncmp(ele,addressBook->contacts[i].email,len)==0)
//                 {
//                     newindex[0]=i;
//                     return i;
//                 }
//             }
//         }
//     //return 0;
//     }
//     return 1;
// }


//it is used to search the people by name,phone and email

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char nameser[50],phoneser[50],emailser[50];
    printf("1.Search By NAME\n2.Search By Phone_NO\n3.Search By Email\n");
    printf("Enter the choice:");
    int sercho,ret=0;
    scanf("%d",&sercho);
    switch(sercho)
    {
        case 1:
            int i=0;
            printf("Enter the name to be searched:");
            scanf("%s",nameser);
            count=0;
            ret=search(nameser,1,addressBook);
            if(ret)
            {
                if(count>1)
                {
                for(int j=0;j<count;j++)
                {
                    printf("\n%d \t %s \t %s \t %s\n",++i,addressBook->contacts[newindex[j]].name,addressBook->contacts[newindex[j]].phone,addressBook->contacts[newindex[j]].email);
                    //addcount
                    //newindex[i++]=ret;
                    //count++;
                }
                break;
            }
                if(count=1)
                {
                    printf("\n%d \t %s \t %s \t %s",1,addressBook->contacts[newindex[0]].name,addressBook->contacts[newindex[0]].phone,addressBook->contacts[newindex[0]].email);
                }

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
                printf("\n%d \t %s \t %s \t %s",i+1,addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
                //newindex[i++]=ret;
                count++;
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
                printf("\n%d \t %s \t %s \t %s",i+1,addressBook->contacts[ret].name,addressBook->contacts[ret].phone,addressBook->contacts[ret].email);
            }
            else{
                printf("\nNOT FOUND!!");
                return 0;
            }
            break;
        default:
            printf("\nInvalid Choice\n");
            return 0;

    }
    return 1;
}

//it is used to edit the contact deatils of the person according to its email its phone and name
//uses search contact to found the contact

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    char edname[50],edphno[20],edmail[50];
    if(searchContact(addressBook))
    {
        printf("\n1.Edit Name\n2.Edit Phone Number\n3.Edit Email\n");
        printf("Enter the choice:");
        int edcho,alpha,slno=1;
        scanf("%d",&edcho);
        switch(edcho)
        {
            case 1:
                //slno=1;
                if(count>1)
                {
                    printf("Enter the serial number of which one to change:");
                    scanf("%d",&slno);
                }

                printf("Enter the New Name :");
                scanf("%s",edname);
                int i=0;
                alpha=is_valid_name(edname);
                if(alpha)
                {
                    strcpy(addressBook->contacts[newindex[slno-1]].name,edname);
                    printf("%d \t %s \t %s \t %s",i+1,addressBook->contacts[newindex[slno-1]].name,addressBook->contacts[newindex[slno-1]].phone,addressBook->contacts[newindex[slno-1]].email);
                    printf("\nName is updated succesfully");
                
                }
                else{
                    printf("Name Contains other elements");
                }
                break;
        
            case 2:
                
                //label_edphno:
                slno=1;
                if(count>1)
                {
                    printf("Enter the serial number of which one to change:");
                    scanf("%d",&slno);
                }
                label_edphno:
                printf("Enter the new phone number:");
                scanf("%s",edphno);
                int phlen;
                phlen=strlen(edphno);
                //printf("\nph len is ;%d",phlen);
                if(phlen==10)
                {
                    i=0;
                    //printf("\nbefore checkvalid");
                    int digit=is_valid_phone(edphno);
                    if(digit)
                    {
                        //printf("\nAfter checkvalid");
                        if(is_unique(edphno,addressBook))
                        {
                            //printf("\nafter unique");
                            strcpy(addressBook->contacts[newindex[slno-1]].phone,edphno);
                            printf("\n%d \t %s \t %s \t %s",i+1,addressBook->contacts[newindex[slno-1]].name,addressBook->contacts[newindex[slno-1]].phone,addressBook->contacts[newindex[slno-1]].email);
                            printf("Phone Number Updated succesfully");
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
               // char edemail[50];
                slno=1;
                if(count>1)
                {
                    printf("Enter the serial number of which one to change:");
                    scanf("%d",&slno);
                }
                label_email1:
                i=0;
                printf("Enter the new Email:");
                scanf("%s",edmail);
                char *emailat,*emcom;
                        emailat=strchr(edmail,'@');
                        emcom=strstr(edmail,".com");
                    if(is_low(edmail))
                    {    
                        if(emailat && emcom)
                        {
                            int alphanum=isalnum(*(emailat-1));
                            if(alphanum)
                            {
                                int alphanum2=isalnum(*(emcom-1));
                                if(alphanum2)
                                {
                                    if(is_unique(edmail,addressBook))
                                    {
                                        strcpy(addressBook->contacts[newindex[slno-1]].email,edmail);
                                        //strcpy(addressBook->contacts[newindex[slno-1]].email,edmail);
                                        
                                        printf("Email updated successfully \n");
                                        printf("%d \t %s \t %s \t %s\n",i+1,addressBook->contacts[newindex[slno-1]].name,addressBook->contacts[newindex[slno-1]].phone,addressBook->contacts[newindex[slno-1]].email);
                                        //addressBook->contactCount++;
                                    }
                                    else{
                                        printf("The email id is already existing\n");
                                        goto label_email1;
                                    }
                                }
                                else{
                                    printf("Email should contain domain name\n");
                                    goto label_email1;
                                }
                            }
                            else{
                                printf("Email should contain characters in front of @\n");
                                goto label_email1;
                            }
                        }
                        else
                        {
                            printf("Email should contain @ and .com\n");
                            goto label_email1;
                        }
                    }
                    else{
                        printf("Email should contain only lower case\n");
                    }
            break;        
        }
     }
     else{
        return;
    }
}

//Uses the previous index to shift and delete the previous element
void delete(int indexx,AddressBook *addressBook)
{
    for(int i=newindex[indexx];i<addressBook->contactCount;i++)
    {
        strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
        strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
        strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
    }
}

//It is used to call the delete function and pass the seatils to delete
//it uses the search contact to find the people
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
        if(searchContact(addressBook))
        {
            printf("\n1.Delete by Name\n2.Delete by Phone\n3.Delete by email\n");
            int cho,size,slno=1;
            printf("Enter the Choice:");
            scanf("%d",&cho);
            switch(cho)
            {
                case 1:
                    int i=0;
                    char delname[50];
                    
                    printf("Enter the Name:");
                    scanf("%s",delname);
                    if(count>1)
                    {
                        printf("Enter the serial number of which one to change:");
                        scanf("%d",&slno);
                    }
                    int ret=search(delname,1,addressBook);

                    if(ret)
                    { 
                        delete(slno-1,addressBook);
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
        else{
            //printf("Invalid choice");
            return;
        }
        
   
}

