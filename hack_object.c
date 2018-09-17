/*
Tianyi Zhang
ECE2230-001
Fall
Assignment 2
*/
#include<stdlib.h>
#include<stdio.h>
#include"hack_object.h"

/** Print the string representation of an object.
*
*  Writes the string representation of OBJECT to STREAM.
*
*  Returns the number of characters printed (not including the
*  trailing '\0') or -1 on error.
*/
int h_object_print(FILE *stream, const h_object *object){
  int num1=0,num2=0;

  num1 = fprintf(stream, "ID: %d\nLocation (l,x,y):%d %d %d\nType:%d\n",
              object->id,object->loc.l,object->loc.x,object->loc.y,
              object->type);
  if(num1<0)return -1;

  num2 = fprintf(stream,"Class: %d\nStatus: %d\nCharge: %d\nWeight: %d\n\n",
                    object->class,object->status,object->charge,
                    object->weight);
  if(num2<0)return -1;

  return num1+num2;

}
/** Compare two game objects.
*
*  Returns an integer greater than, equal to, or less than 0,
*  according as the h_object LEFT is greater than, equal to, or less
*  than the h_object RIGHT.
*/
int h_object_compare(const void *left, const void *right){
  const h_object* a=left;
  const h_object* b=right;

  if(a==NULL||b==NULL) return 0;
  else{
    if(a->id!=b->id)  return(a->id>b->id?1:-1);
    if(a->loc.l!=b->loc.l) return(a->loc.l>b->loc.l?1:-1);
    if(a->loc.x!=b->loc.x) return(a->loc.x>b->loc.x?1:-1);
    if(a->loc.y!=b->loc.y) return(a->loc.y>b->loc.y?1:-1);
    if(a->type!=b->type) return(a->type>b->type?1:-1);
    if(a->class!=b->class) return(a->class>b->class?1:-1);
    if(a->status!=b->status) return(a->status>b->status?1:-1);
    if(a->charge!=b->charge) return(a->charge>b->charge?1:-1);
    if(a->weight!=b->weight) return(a->weight>b->weight?1:-1);
  }
  return 0;
}
