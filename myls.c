/*
 * Filename: myls.c
 * Author: Matthhew Schwegler
 * Userid: cs30xfw
 * Description: This is the main function of a larger program that is designed
 *              to work as the unix "ls" function with less robust 
 *              capabilities

 *
 * Date: May 29, 2013
 * Sources of Help: Lecture notes
 */

#include <stdio.h>
#include "myls.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

/*
* Function name: myls.c
* Function prototype: int main ( int argc, char *argv[] )
*
* Description: This is the main function of a larger program that is designed
*              to work as the unix "ls" function with less robust 
*              capabilities
*
* Parameters:  argc: The number of arguments passed into main
*              *argv: a pointer to the strings passed in via terminal
*
*            
* Side Effects: Runs the main of the myls program generating the output to the
*               user according to myls.
*
* Error Conditions: Bad user input
*
* Return Value: Returns a 0 if completed without error.
*
* 
*/



//Global variable to be used by assembly for offest
int stbuff = (int) offsetof(struct fileInfo, stbuf);
int stTime = (int) offsetof(struct stat, st_mtime);
//Global variable to be used by assembly for offset
int stGid = (int) offsetof(struct stat, st_gid );
//includes errno


int main ( int argc, char *argv[] )
{
  //String to hold the options
  char *options = "alrt";
  char *dot = ".";
  int opt = 0;
  int flag = 0;
  struct fileInfo *table;
  int numEntries;


  //Check if argc = 1
  if( argc == 1)
  {
    numEntries = buildFileInfoTable(dot, &table);
    if(numEntries != 0)
      displayFileInfo(table, numEntries, flag);
    free(table);
  }

  while ( (opt = getopt( argc, argv, options ) ) != -1  )
  {
    
    switch (opt)
    {
      //displays all entries does not hide
      case 'a':
        flag = ( flag | AFLAG);
        break;

      //Use long listing format for print
      case 'l':
        flag = ( flag | LFLAG);
        break;

        //DisplayPermissions
        //DisplayOwner
        //displayTime
        //Display file
       
      //List reverse order while sorther
      case 'r':
        flag = ( flag | RFLAG);
        break;


      //sort by modification time
      case 't':
        flag = ( flag | TFLAG);
        break;

      //Default print if case not recognized
      default:
     // (void)fprintf(stderr, "%c\n", optopt);
      (void)fprintf(stderr, "Usage: myls [-alrt] [file ...]\n");
      exit(1);

    }
  }


  //Checks for optind
  if (optind == (argc) && argc !=1 )
  {
    //buildFileInfoTable on all files
    numEntries = buildFileInfoTable(dot, &table);
    if(numEntries != 0)
    {
      displayFileInfo(table, numEntries, flag);
      free(table);
    }
  }
    else
    {
      for(; optind < argc ; optind++)
      {
        numEntries = buildFileInfoTable(argv[optind], &table);
        if(numEntries != 0)
          displayFileInfo(table, numEntries, flag);

        free(table);
      }
    }
  


}

