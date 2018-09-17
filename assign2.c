/*
Tianyi Zhang
ECE2230-001
Fall
Assignment 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "hack_object.h"
#include "hack_inventory.h"

int main(){
  struct h_inventory* newDB=h_inventory_create();

  //check if database created. Terminate program if not
  if(newDB==NULL){
    printf("Machine is out of memory.\nProgram terminated.\n");
    return 0;
  }

  //will become 0 if user enters quit
  int quit=1;

  while(quit){
    //dynamically allocating strings to store inputs
    char* inputStr=(char*)malloc(sizeof(char)*100);
    char* commandStr=(char*)malloc(sizeof(char)*10);
    char* keyStr=(char*)malloc(sizeof(char)*90);

    //recoding number of input statement
    int a;

    //waiting for input
    if(fgets(inputStr,99,stdin)){

      //parsing
      a=sscanf(inputStr,"%s %[^\n]",commandStr,keyStr);

      if(a==1){
        if(strcmp(commandStr,"ADD")==0){
          h_object* newGtar=malloc(sizeof(struct h_object_s));
          int temp=0;

          //prompting for guitar info if database still has space

          printf("ID: ");
          scanf(" %d", &newGtar->id);
          printf("Location l: ");
          scanf(" %d", &newGtar->loc.l);
          printf("Location x: ");
          scanf(" %d", &newGtar->loc.l);
          printf("Location y: ");
          scanf(" %d", &newGtar->loc.l);
          printf("Type: ");
          scanf(" %d", &temp);
          newGtar->type=temp;
          printf("Class: ");
          scanf(" %d", &temp);
          newGtar->class=temp;
          printf("Status: ");
          scanf(" %d", &temp);
          newGtar->status=temp;
          printf("Charge: ");
          scanf(" %d", &newGtar->charge);
          printf("Weight: ");
          scanf(" %d", &newGtar->weight);

          //consum the last new line character before another command comes
          fgets(inputStr,99,stdin);
          if(h_inventory_add(newDB,newGtar)!=NULL)
            printf("New object is initialized.\n" );
          else{
            printf("Data cannot be added. The ID: %d is dupilcated.\n",
                  newGtar->id);
            free(newGtar);
          }

          printf("\n");
        }
        else if(strcmp(commandStr,"LIST")==0){
          //setting cursor to the first element
          h_object* h=h_inventory_first(newDB);

          if(h==NULL)printf("The inventory is empty.\n");

          //iterator
          while(h!=NULL){
            printf("%d %d %d %d\n",h->id,h->type
                                  ,h->class,h->status);
            h=h_inventory_next(newDB);
          }

          printf("\n");
        }
      else if(strcmp(commandStr,"FIRST")==0){
          h_object* h=h_inventory_first(newDB);

          if(h!=NULL){
            printf("ID: %d\n",h->id);
            printf("Location l: %d\n",h->loc.l);
            printf("Location x: %d\n",h->loc.x);
            printf("Location y: %d\n",h->loc.y);
            printf("Type: %d\n",h->type);
            printf("Class: %d\n",h->class);
            printf("Status: %d\n",h->status);
            printf("Charge: %d\n",h->charge);
            printf("Weight: %d\n",h->weight);
            printf("\n");
          }
          else printf("No valid data\n");

        }
       else if(strcmp(commandStr,"LAST")==0){
          h_object* h_temp=h_inventory_first(newDB);
          h_object* h=NULL;

          for(;h_temp!=NULL;h_temp=h_inventory_next(newDB))h=h_temp;

          if(h!=NULL){
            printf("ID: %d\n",h->id);
            printf("Location l: %d\n",h->loc.l);
            printf("Location x: %d\n",h->loc.x);
            printf("Location y: %d\n",h->loc.y);
            printf("Type: %d\n",h->type);
            printf("Class: %d\n",h->class);
            printf("Status: %d\n",h->status);
            printf("Charge: %d\n",h->charge);
            printf("Weight: %d\n",h->weight);
            printf("\n");
          }
          else printf("No valid data\n");
      }
      else if(strcmp(commandStr,"NEXT")==0){
          h_object* h=h_inventory_next(newDB);

          if(h!=NULL){
            printf("ID: %d\n",h->id);
            printf("Location l: %d\n",h->loc.l);
            printf("Location x: %d\n",h->loc.x);
            printf("Location y: %d\n",h->loc.y);
            printf("Type: %d\n",h->type);
            printf("Class: %d\n",h->class);
            printf("Status: %d\n",h->status);
            printf("Charge: %d\n",h->charge);
            printf("Weight: %d\n",h->weight);
            printf("\n");
          }
          else printf("No valid data\n");

        }
        else if(strcmp(commandStr,"QUIT")==0){
          //free any remaining guitar instances
          h_object* h=h_inventory_first(newDB);
          for(;h!=NULL;h=h_inventory_next(newDB)){
            free(h);
          }
          printf("Program terminated.\n\n");
          quit=0;
        }
        //if wrong input was entered
        else printf("Enter a command (ADD LOOK(key) DEL(key) LIST NEXT FIRST LAST QUIT)\n\n");

      }
      else if(a==2){
        //parsing key number entered by user
        int keyEntered=0,i,size;
        for(size=0;size<90;size++) if(keyStr[size]=='\0')break;
        size--;
        for(i=0;i<90;i++){
          int temp=1,tempcounter=(size-i);
          if(keyStr[i]!='\0'){
            while(tempcounter--)temp*=10;
            keyEntered+=(temp*(keyStr[i]-'0'));
          }
          else break;
        }

        //checking for wrong key number input (max key number is 99)
        if(keyEntered<1){
          printf("Invalid key entered.\n");
        }
        else{
          if(strcmp(commandStr,"LOOK")==0){
            h_object* h=h_inventory_find_id(newDB,keyEntered);
            if(h==NULL)
              printf("Data not found\n");
            else{
              printf("ID: %d\n",h->id);
              printf("Location l: %d\n",h->loc.l);
              printf("Location x: %d\n",h->loc.x);
              printf("Location y: %d\n",h->loc.y);
              printf("Type: %d\n",h->type);
              printf("Class: %d\n",h->class);
              printf("Status: %d\n",h->status);
              printf("Charge: %d\n",h->charge);
              printf("Weight: %d\n",h->weight);
              printf("\n");
            }
          }
          else if(strcmp(commandStr,"DEL")==0){
            h_object* h=h_inventory_find_id(newDB,keyEntered);
            if(h!=NULL){
              h=h_inventory_delete(newDB);
              free(h);
              printf("Data deleted\n");
            }
            else
              printf("Data not found\n");
          }
          else{
            printf("Wrong input.\n");
            printf("Enter a command (ADD LOOK(key) DEL(key) LIST NEXT FIRST LAST QUIT)\n\n");          }
        }
        printf("\n");
      }
      else{
       printf("Enter a command (ADD LOOK(key) DEL(key) LIST NEXT FIRST LAST QUIT)\n\n");
      }
    }
    //free dynamically located memory before new cycle starts
    free(commandStr);
    free(keyStr);
    free(inputStr);
  }

  //free database
  h_inventory_destroy(newDB);
  return 0;
}
