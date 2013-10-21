/*
 * Filename: nameSortDecending.c
 * Author: Matthhew Schwegler
 * Userid: cs30xfw
 * Description: Method to take in two values of strings containing names
 *              and sort these strings in a Decending order that is
 *              z,y,x......
 *
 * Date: May 27, 2013
 * Sources of Help: Lecture notes
 */

#include <stdio.h>
#include <string.h>
#include "myls.h"
/*
* Function name: nameSortDecending.c
* Function prototype: int nameSortDecending (const void *p1, const coid *p2 )
*
* Description: The function takes in two pointers to names in a struct
*              it then sorts them in decending order that is z,x,y ect
*
* Parameters:  *ptr1: a pointer to a struct containing a name param
*              *ptr2: a pointer to a struct containing a name param
*
*            
* Side Effects: 
* 
* Error Conditions:
*
* Return Value: Returns <0 if ptr2 is larger
*                       >0 if ptr1 is larger
*                       ==0 if they are the same value
*
* 
*/
int nameSortDecending (const void *p1, const void *p2 )
{
  //Casts the passed in const void pointers
  const struct fileInfo *tempPtr1 = p1;
  const struct fileInfo *tempPtr2 = p2;

  return strcmp(tempPtr2->name,tempPtr1->name);

}
