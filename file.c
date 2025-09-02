#include <stdio.h>
#include "file.h"
//#include "contacts.csv"

void saveContactsToFile(AddressBook *addressBook) {

   FILE *fp =fopen("contacts.csv","w");
   if(fp==NULL)
   {
      printf("File Open failed");
      return ;
   }

   for(int i=0;i<addressBook->contactCount;i++)
   {
      fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
   }
   fclose(fp);

}

void loadContactsFromFile(AddressBook *addressBook) {

   FILE *fptr =fopen("contacts.csv","r");
   if(fptr==NULL)
   {
      printf("File open failed!");
      return;
   }
   int i=0;
   while((fscanf(fptr,"%[^,],%[^,],%[^,\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email))!=EOF)
   {
      i++;
      addressBook->contactCount++;
   }
   fclose(fptr);

    
}
