#include <stdio.h>
#include "file.h"
//#include "contacts.csv"

//While calling the save function it will save the datas which are newly added/deleted/edit datas into the file from struct
void saveContactsToFile(AddressBook *addressBook) {

   FILE *fp =fopen("contacts.csv","w");
   if(fp==NULL)
   {
      printf("File Open failed");
      return ;
   }

   //This will take each iteam loaded in the struct and then it will write into the file contactcount times and then it will add into file by seperaing it with commas
   for(int i=0;i<addressBook->contactCount;i++)
   {
      fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
   }
   fclose(fp);

}

//it is used to load the csv files into the struct 

void loadContactsFromFile(AddressBook *addressBook) {

   FILE *fptr =fopen("contacts.csv","r");
   if(fptr==NULL)
   {
      printf("File open failed!");
      return;
   }
   int i=0;
   //this reads the file input one by one and then access each element by comma(,) first it will get input till the comma then by next it will cancel out then till next comma then it will cancel out and at last it will be read till new line and then store the values into the struct
   while((fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email))!=EOF)
   {
      i++;
      addressBook->contactCount++;
   }
   fclose(fptr);

    
}
