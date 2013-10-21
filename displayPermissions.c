/*
 * Filename: displayPermissions.c
 * Author: Matthhew Schwegler
 * Userid: cs30xfw
 * Description: This function takes in a mode_t struct and displays
 *               to the user the file permissions based on this passed
 *               in struct

 *
 * Date: May 28, 2013
 * Sources of Help: Lecture notes
 */

#include <stdio.h>
#include <sys/stat.h>
#include "myls.h"


/*
* Function name: displayPermissions.c
* Function prototype: displayOwnerName ( const uid_t uid)
*
* Description: This function takes in a mode_t struct and displays
*               to the user the file permissions based on this passed
*               in struct
*
* Parameters:  mode: mode_t struct containing file permissions info
*
*            
* Side Effects: Displays info on file permissions
*
* Error Conditions:
*
* Return Value: N/A
*/



void displayPermissions( const mode_t mode)
{
  int permissions = mode;
  
  if(permissions & S_IFDIR)
    (void)printf("d");
    else
      (void)printf("-");

  //Check for user read permissions
  if ( permissions & S_IRUSR )
    (void) printf("r");
    else
      (void) printf("-");

  //Check for user write permissions
  if( permissions & S_IWUSR )
    (void) printf("w");
    else
      (void) printf("-");

  //Check for user execute permissions
  if( permissions & S_IXUSR )
    (void) printf("x");
     else
      (void) printf("-");

  //Check for group read permissions
  if( permissions & S_IRGRP )
    (void) printf("r");
    else
      (void) printf("-");

  //check for group write permissions
  if( permissions & S_IWGRP )
    (void) printf("w");
    else
      (void) printf("-");

  //check for group execture permissions  
  if( permissions & S_IXGRP)
    (void) printf("x");
    else
      (void) printf("-");

  //check for other read permissions
  if( permissions & S_IROTH)
    (void) printf("r");
    else
      (void) printf("-");

  //check for other write permissions
  if( permissions & S_IWOTH)
    (void) printf("w");
    else
      (void) printf("-");

  //check for other execute permissions
  if( permissions & S_IXOTH)
    (void) printf("x");
    else
      (void) printf("-");

  (void) printf(" ");
}
