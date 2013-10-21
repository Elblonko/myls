/*
 * Filename: displayOwnerName.c
 * Author: Matthhew Schwegler
 * Userid: cs30xfw
 * Description: This function takes in a part of the stat struct uid_t
 *               it uses this to determine the owner of the file and
 *               displays this

 *
 * Date: May 28, 2013
 * Sources of Help: Lecture notes
 */

#include <stdio.h>
#include "myls.h"
#include <pwd.h> 

/*
* Function name: displayOwnerName ( const uid_t uid)
* Function prototype: void displayOwnerName (const uid_t uid)
*
* Description: This function takes in a part of the stat struct uid_t
*               it uses this to determine the owner of the file and
*               displays this
*
* Parameters:  uid: the stat struct item uid containing owner info
*
*            
* Side Effects: Displays  user information
*
* Error Conditions:
*
* Return Value: N/A
*/

void displayOwnerName (const uid_t uid)
{
  //struct passwd to hold getpwuid() return
  struct passwd *pass;

  if( ( pass = getpwuid(uid) ) == NULL )
  {
    //if getpuid fails print num value uid
    (void)printf("%d  ", uid);
  }
  else
  {
    (void)printf("%s  ", pass->pw_name);
  }

}
