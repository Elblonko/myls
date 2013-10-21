/*
 * Filename: mtimeSortAscending.c
 * Author: Matthhew Schwegler
 * Userid: cs30xfw
 * Description: his function takes in two pointers to the stat mtime struct
 *              using these pointers determines which is the earlier point in
 *              time

 *
 * Date: May 27, 2013
 * Sources of Help: Lecture notes
 */

#include <stdio.h>
#include "myls.h"

/*
* Function name: mtimeSortAscending.c
* Function prototype: int mtimeSortAscending ( const void *p1, const void *p2 )
*
* Description: This function takes in two pointers to the stat mtime struct
*              using these pointers determines which is the earlier point in
*              time
*
* Parameters:  *p1: pointer to a struct st_mtime
*              *p2: pointer to a struct st_mtime
*
*            
* Side Effects: Returns a value signifying which value is larger
*               <0 means ptr1 is larger
*               >0 means ptr2 is larger
*               ==0 same 
*
* Error Conditions:
*
* Return Value: refer to side affects returns a value signifying the
*               relationship between ptr 1 and ptr2
*/


int mtimeSortAscending ( const void *p1, const void *p2 )
{
  //Casts the pointers to struct stat
  const struct fileInfo *tempPtr1 = p1;
  const struct fileInfo *tempPtr2 = p2;

  //Runs compare and gives a return value for qsort to use
  //printf("%d - %d", tempPtr2->stbuf.st_mtime,tempPtr1->stbuf.st_mtime);
  return ( (tempPtr2->stbuf.st_mtime) - (tempPtr1->stbuf.st_mtime) );
}
