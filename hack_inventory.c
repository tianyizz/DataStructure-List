/*
Tianyi Zhang
ECE2230-001
Fall
Assignment 2
*/
#include<stdlib.h>
#include<stdio.h>
#include"list.h"
#include"hack_object.h"
#include"hack_inventory.h"
/** pointer to opaque inventory type to be defined in hack_inventory.c */
struct h_inventory{
  list itemL;
  h_object* current;
};
/** Creates a new empty inventory.
*
*  The current object is initially NULL.
*
*  Returns the new inventory or NULL on error.
*/
h_inventory h_inventory_create(void){
  h_inventory newI = (h_inventory)malloc(sizeof(*newI));
  newI->itemL=list_init();
  newI->current=NULL;
  return newI;
}
/** Adds a new object to the inventory.
*
*  OBJECT is inserted into the inventory in order sorted by
*  OBJECT->class. The new object is appended to the end of all the
*  objects with the same class (see example).
*
*  OBJECT->id must be unique within the inventory. Attempting to add
*  an object with a duplicate id is an error.
*
*  The current object remains the same.
*
*  Example:
*  | call                   | inventory                 |
*  |------------------------+---------------------------|
*  | inventory_add(potion1) | potion1                   |
*  | inventory_add(tool)    | tool,potion1              |
*  | inventory_add(food)    | tool,potion1,food         |
*  | inventory_add(potion2) | tool,potion1,potion2,food |
*
*  Returns OBJECT or NULL on error.
*/
h_object *h_inventory_add(h_inventory inventory, h_object *object){
  h_object* temp=list_first(inventory->itemL);

  //IF NO VALID DATA
  if(object==NULL) return NULL;

  //IF REPEAT ID
  else if(h_inventory_find_id(inventory,object->id)!=NULL) return NULL;

  //IF EMPTY LIST
  else if(temp==NULL) return temp=list_insert(inventory->itemL,object);

  else{
    //RESET TEMP
    temp=list_first(inventory->itemL);

    //FIND THE EQUAL CLASS
    while(temp!=NULL&&temp->class!=object->class)
          temp=list_next(inventory->itemL);


  //FOUND THE EQUAL CLASS
    if(temp!=NULL){
      //APPENDING THE NEW OBJECT TO THE SAME CLASS OBJECTS
      while(temp!=NULL&&temp->class==object->class)
        temp=list_next(inventory->itemL);

      //ADJUST POINTER TO PROPER POSITION
      if(temp!=NULL)
        temp=list_prev(inventory->itemL);
      else temp=list_last(inventory->itemL);

      //APPEND
      return temp=list_insert_after(inventory->itemL,object);
    }
    else{
      //IF NO SAME CLASS OBJECT EXITS, FIND THE PROPER POSITION (EMPTY LIST
      //SITUATION HAS BEEN TAKEN CARE OF BEFORE)
      temp=list_first(inventory->itemL);
      while(temp!=NULL&&temp->class<object->class)
        temp=list_next(inventory->itemL);

      if(temp!=NULL)
       return temp=list_insert_before(inventory->itemL,object);
      else
        return temp=list_append(inventory->itemL,object);

    }
  }
}
/** Removes the current object from the inventory.
*
*  The new current object becomes the object after the current object
*  (or NULL if there is no object after the current object).
*
*  Returns the object that was removed or NULL if the current object
*  was NULL.
*/
h_object *h_inventory_delete(h_inventory inventory){
  h_object* temp=list_first(inventory->itemL);
  if(inventory->current==NULL) return NULL;
  else{
    //LOOKING FOR THE OBJECT NODE
    while(h_object_compare(temp,inventory->current)!=0)
      temp=list_next(inventory->itemL);

    //DO REMOVE FUNCTION
    temp=list_remove(inventory->itemL);
    inventory->current=list_curr(inventory->itemL);
  }
  return temp;
}
/** Move to the first object in the inventory.
*
*  Sets the current object to the first object in the inventory (or
*  NULL if the inventory is empty).
*
*  Returns the first object in the inventory or NULL if the inventory
*  is empty.
*/
h_object *h_inventory_first(h_inventory inventory){
  h_object* temp=list_first(inventory->itemL);
  inventory->current=temp;
  return temp;
}
/** Move to the next object in the inventory.
*
*  Sets the new current object to the object after the current
*  object. There is no object after the NULL current object.
*
*  Returns the object after the current object or NULL if there is no
*  object after the current object.
*/
h_object *h_inventory_next(h_inventory inventory){
  h_object* temp=list_next(inventory->itemL);
  inventory->current=temp;
  return temp;
}
/** Finds an object by its id.
*
*  Sets the current object to the object whose id is equal to ID (or
*  NULL if no such object was found).
*
*  Returns the matching object or NULL if no such object was found.
*/
h_object *h_inventory_find_id(h_inventory inventory, int id){
  h_object* temp=list_first(inventory->itemL);
  //SEARCH FOR ID
  while(temp!=NULL&&temp->id!=id)temp=list_next(inventory->itemL);
  if(temp!=NULL)inventory->current=temp;
  return temp;
}
/** Destroys the inventory and frees its memory.
*
*  Storage for any objects in the inventory is never freed.
*/
void h_inventory_destroy(h_inventory inventory){
  list_finalize(inventory->itemL);
  free(inventory);
}
