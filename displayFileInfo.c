/*
 * Filename: displayFileInfo.c
 * Author: Matthhew Schwegler
 * Userid: cs30xfw
 * Description: This function takes passed in pointer to a place in
 *              memory containing a series of files or directories
 *              the function determines how to and what files to display
 *              to the user

 *
 * Date: May 30, 2013
 * Sources of Help: Lecture notes
 */

#include <stdio.h>
#include "myls.h"
#include <stdlib.h> 
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

/*
* Function name: displayFileInfo.c
* Function prototype: void displayFileInfo( struct fileInfo * const table,
*                                         const int entries,
*                                         const int displayMode ) 
*
* Description: This function takes passed in pointer to a place in
*              memory containing a series of files or directories
*              the function determines how to and what files to display
*              to the user
*
* Parameters:  entries: The number of entries in the table
*              table: a pointer to a pointer of a fileInfo struct
*              displayMode: flag signifying how to display files
*
*            
* Side Effects: Displays to user the table of files in a desired format
*	              
*Error Conditions:
*
*Return Value: N/A
*/ 


void displayFileInfo(struct fileInfo * const table, 
                    const int entries, const int displayMode)
{
  /*
   * Local Variables
   */
  //counter
  int i;
  char *tempString;
  struct fileInfo *table1 = table;
  int numOptions = 0;
  char buffer[80];

    //For Time
    struct tm *currenttime;

  /*
   * Creates a variable numOptions that counts num of flags active
   */
  if ( displayMode & AFLAG )
    numOptions++;
  if ( displayMode & LFLAG )
    numOptions++;
  if ( displayMode & RFLAG )
    numOptions++;
  if ( displayMode & TFLAG )
    numOptions++;


  /*
   * IF NO SWITCHES ACTIVE
   */
  
  if ( displayMode == 0)
  {
    //Preforms a call for Ascending alphabetical order
    (void) qsort (table, entries, sizeof(struct fileInfo), nameSortAscending );

    for ( i = 0; i < entries; i++)
    {
      //removes path from the string
      tempString = basename(table1->name);

      //if to check for hidden files
      if(tempString[0] != '.')
      {
        (void)printf("%s\n", tempString);
      }
      table1++;
    }
  }

  /*
   * IF -a IS ONLY OPTION
   */

  if(numOptions == 1)
  {
   if ( displayMode & AFLAG )
   {
     //Preforms a call for Ascending alphabetical order
     (void) qsort (table, entries, sizeof(struct fileInfo), nameSortAscending );

     for ( i = 0; i < entries; i++)
     {
       //removes path from the string
       tempString = basename(table1->name);

        //if to check for hidden files
        (void)printf("%s\n", tempString);
       table1++;
     }
   }
  }

  /*
   * IF -l IS ONLY OPTION
   */

  if(numOptions == 1)
  {
    if( displayMode & LFLAG )
    {
    //Preforms a call for Ascending alphabetical order
     (void) qsort (table, entries, sizeof(struct fileInfo), nameSortAscending );

       for(i = 0; i < entries; i++)
        {
        //removes path from the string
        tempString = basename(table1->name);

         //if to check for hidden files
          if(tempString[0] != '.')
          {
            //print for access options
            displayPermissions(table1->stbuf.st_mode);
            //prints the # items linkd too
            (void)printf( "%3.ld ", table1->stbuf.st_nlink);
            //Call and prints from ownername and groupname
            displayOwnerName(table1->stbuf.st_uid);
            displayGroupName(table1->stbuf.st_gid);
            //Format and print strings for time
            (void)printf("%11.ld", table1->stbuf.st_size);
            currenttime = localtime(&(table1->stbuf.st_mtime));
            (void)strftime (buffer,80," %b %e %H:%M",currenttime);
            (void)fputs(buffer,stdout);  
            //Prints the file name
            (void)printf(" %s\n", tempString);
          }
          table1++;

        }
    }
  }

  /*
   * IF -r IS ONLY OPTION
   */
 if(numOptions == 1)
  {
    if( displayMode & RFLAG )
    {
     (void) qsort (table, entries, sizeof(struct fileInfo), nameSortDecending );

       for(i = 0; i < entries; i++)
        {
         //removes path from the string
         tempString = basename(table1->name);

         //if to check for hidden files
          if(tempString[0] != '.')
          {
            (void)printf("%s\n", tempString);
          }
          table1++;
        }
    }
  }

  /*
   *IF -t IS ONLY OPTION
   */
 if(numOptions == 1)
  {
    if( displayMode & TFLAG )
    {
     (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortAscending );

       for(i = 0; i < entries; i++)
        {
         //removes path from the string
         tempString = basename(table1->name);

         //if to check for hidden files
          if(tempString[0] != '.')
          {
            (void)printf("%s\n", tempString);
          }
          table1++;
        }
    }
  }



  /*
  *IF  a & l ARE USED OPTIONS
  */

  if(numOptions == 2)
  {
    if ( displayMode & AFLAG )
    {
      //Getting to this point means you print '.' files
     if (displayMode & LFLAG )
     {
        //Sort using name ascending
        (void) qsort (table, entries, sizeof(struct fileInfo), nameSortAscending );

        //Getting to this point means you display '.' files and all info
        for(i = 0; i < entries; i++)
        {

          //removes path from the string
          tempString = basename(table1->name);

          //Prints the permissions options
          displayPermissions(table1->stbuf.st_mode);
          //Prints the # of links to each file
          (void)printf( "%3.ld ", table1->stbuf.st_nlink);
          //Prints from displayowner and group
          displayOwnerName(table1->stbuf.st_uid);
          displayGroupName(table1->stbuf.st_gid);
          //Prints the time
          (void)printf("%11.ld", table1->stbuf.st_size);
          currenttime = localtime(&(table1->stbuf.st_mtime));
          (void)strftime (buffer,80," %b %e %H:%M",currenttime);
          (void)fputs(buffer,stdout);         
          //prints the filename
          (void)printf(" %s\n", tempString);

          table1++;
        }
      }
    }
  }

  /*
   * IF a & r ARE USED OPTIONS
   */

  if(numOptions == 2)
  {
    if(displayMode & AFLAG)
    {
      if(displayMode & RFLAG)
      {
        (void) qsort (table, entries, sizeof(struct fileInfo), nameSortDecending );

        for(i = 0; i < entries; i++)
          {
            //removes path from the string
            tempString = basename(table1->name);
            (void)printf("%s\n", tempString);
            table1++;
          }
      }
    }
    
  }

  /*
   * IF a & t ARE USED OPTIONS
   */
  if(numOptions == 2)
  {
    if(displayMode & AFLAG)
    {
      if(displayMode & TFLAG)
      {
        (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortAscending );

        for(i = 0; i < entries; i++)
          {
            //removes path from the string
            tempString = basename(table1->name);
            (void)printf("%s\n", tempString);
            table1++;
          }
      }
    }
    
  }

  /*
   * IF l & r ARE USED OPTIONS
   */
    if(numOptions == 2)
    {
      if ( displayMode & LFLAG )
      {
      //Getting to this point means you print '.' files
        if (displayMode & RFLAG )
        {
          //Preforms a call for Ascending alphabetical order
          (void) qsort (table, entries, sizeof(struct fileInfo), nameSortDecending );

          //Getting to this point means you display '.' files and all info
          for(i = 0; i < entries; i++)
          {
            //removes path from the string
            tempString = basename(table1->name);

            //if to check for hidden files
            if(tempString[0] != '.')
            {
              //print for access options
              displayPermissions(table1->stbuf.st_mode);
              //prints the # items linkd too
              (void)printf( "%3.ld ", table1->stbuf.st_nlink);
              //Call and prints from ownername and groupname
              displayOwnerName(table1->stbuf.st_uid);
              displayGroupName(table1->stbuf.st_gid);
              //Format and print strings for time
              (void)printf("%11.ld", table1->stbuf.st_size);
              currenttime = localtime(&(table1->stbuf.st_mtime));
              (void)strftime (buffer,80," %b %e %H:%M",currenttime);
              (void)fputs(buffer,stdout);  
              //Prints the file name
              (void)printf(" %s\n", tempString);
            }
            table1++;

          }

        }
      }
    }

    /*
     * IF l & t ARE USED OPTIONS
     */
    if(numOptions == 2)
    {
      if ( displayMode & LFLAG )
      {
      //Getting to this point means you print '.' files
        if (displayMode & TFLAG )
        {
          //Preforms a call for Ascending alphabetical order
          (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortAscending );

          //Getting to this point means you display '.' files and all info
          for(i = 0; i < entries; i++)
          {
            //removes path from the string
            tempString = basename(table1->name);

            //if to check for hidden files
            if(tempString[0] != '.')
            {
              //print for access options
              displayPermissions(table1->stbuf.st_mode);
              //prints the # items linkd too
              (void)printf( "%3.ld ", table1->stbuf.st_nlink);
              //Call and prints from ownername and groupname
              displayOwnerName(table1->stbuf.st_uid);
              displayGroupName(table1->stbuf.st_gid);
              //Format and print strings for time
              (void)printf("%11.ld", table1->stbuf.st_size);
              currenttime = localtime(&(table1->stbuf.st_mtime));
             // (void)printf("%s", ctime(&(table1->stbuf.st_mtime)));
              (void)strftime (buffer,80," %b %e %H:%M",currenttime);
              (void)fputs(buffer,stdout);  
              //Prints the file name
              (void)printf(" %s\n", tempString);
            }
            table1++;

          }

        }
      }
    }

    /*IF r & t ARE USED OPTIONS
     */

  if(numOptions == 2)
  {
    if( displayMode & RFLAG )
    {
      if( displayMode & TFLAG)
      {
        (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortDecending );

        for(i = 0; i < entries; i++)
        {
          //removes path from the string
          tempString = basename(table1->name);

          //if to check for hidden files
          if(tempString[0] != '.')
          {
            (void)printf("%s\n", tempString);
          }
          table1++;
        }
      }
    }
  }

  /*
   * IF a & l & r ARE USED OPTIONS
   */

  if(numOptions == 3)
  {
    if ( displayMode & AFLAG )
    {
      //Getting to this point means you print '.' files
     if (displayMode & LFLAG )
     {
       if(displayMode & RFLAG)
       {
         //Sort using name ascending
         (void) qsort (table, entries, sizeof(struct fileInfo), nameSortDecending );

         //Getting to this point means you display '.' files and all info
         for(i = 0; i < entries; i++)
         {

           //removes path from the string
           tempString = basename(table1->name);

            //Prints the permissions options
            displayPermissions(table1->stbuf.st_mode);
            //Prints the # of links to each file
            (void)printf( "%3.ld ", table1->stbuf.st_nlink);
            //Prints from displayowner and group
            displayOwnerName(table1->stbuf.st_uid);
            displayGroupName(table1->stbuf.st_gid);
            //Prints the time
            (void)printf("%11.ld", table1->stbuf.st_size);
            currenttime = localtime(&(table1->stbuf.st_mtime));
            (void)strftime (buffer,80," %b %e %H:%M",currenttime);
            (void)fputs(buffer,stdout);         
            //prints the filename
            (void)printf(" %s\n", tempString);

            table1++;
          }
        }
      }
    }
  }

  /*
   * IF a & l & t
   */
  if(numOptions == 3)
  {
    if ( displayMode & AFLAG )
    {
      //Getting to this point means you print '.' files
     if (displayMode & LFLAG )
     {
       if(displayMode & TFLAG)
       {
         //Sort using name ascending
         (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortAscending );

         //Getting to this point means you display '.' files and all info
         for(i = 0; i < entries; i++)
         {

           //removes path from the string
           tempString = basename(table1->name);

            //Prints the permissions options
            displayPermissions(table1->stbuf.st_mode);
            //Prints the # of links to each file
            (void)printf( "%3.ld ", table1->stbuf.st_nlink);
            //Prints from displayowner and group
            displayOwnerName(table1->stbuf.st_uid);
            displayGroupName(table1->stbuf.st_gid);
            //Prints the time
            (void)printf("%11.ld", table1->stbuf.st_size);
            currenttime = localtime(&(table1->stbuf.st_mtime));
            (void)strftime (buffer,80," %b %e %H:%M",currenttime);
            (void)fputs(buffer,stdout);         
            //prints the filename
            (void)printf(" %s\n", tempString);

            table1++;
          }
        }
      }
    }
  }

  /*
   * IF a & r & t
   */

  if(numOptions == 3)
  {
    if ( displayMode & AFLAG )
    {
      //Getting to this point means you print '.' files
     if (displayMode & RFLAG )
     {
       if(displayMode & TFLAG)
       {
         //Sort using name ascending
         (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortDecending );

         //Getting to this point means you display '.' files and all info
         for(i = 0; i < entries; i++)
         {

           //removes path from the string
           tempString = basename(table1->name);


            (void)printf("%s\n", tempString);

            table1++;
          }
        }
      }
    }
  }

  /*
   * IF l & r & t
   */
  if(numOptions == 3)
  {
    if ( displayMode & LFLAG )
    {
      //Getting to this point means you print '.' files
     if (displayMode & RFLAG )
     {
       if(displayMode & TFLAG)
       {
         //Sort using name ascending
         (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortDecending );

         //Getting to this point means you display '.' files and all info
         for(i = 0; i < entries; i++)
         {
           //removes path from the string
           tempString = basename(table1->name);
           //if to check for hidden files
           if(tempString[0] != '.')
           {
            //Prints the permissions options
            displayPermissions(table1->stbuf.st_mode);
            //Prints the # of links to each file
            (void)printf( "%3.ld ", table1->stbuf.st_nlink);
            //Prints from displayowner and group
            displayOwnerName(table1->stbuf.st_uid);
            displayGroupName(table1->stbuf.st_gid);
            //Prints the time
            (void)printf("%11.ld", table1->stbuf.st_size);
            currenttime = localtime(&(table1->stbuf.st_mtime));
            (void)strftime (buffer,80," %b %e %H:%M",currenttime);
            (void)fputs(buffer,stdout);         
            //prints the filename
            (void)printf(" %s\n", tempString);
           }
           table1++;
          }
        }
      }
    }
  }

  if(numOptions == 4)
  {
    if ( displayMode & LFLAG )
    {
      //Getting to this point means you print '.' files
     if (displayMode & RFLAG )
     {
       if(displayMode & TFLAG)
       {
         if(displayMode & AFLAG)
         {
          //Sort using name ascending
          (void) qsort (table, entries, sizeof(struct fileInfo), mtimeSortDecending );

          //Getting to this point means you display '.' files and all info
          for(i = 0; i < entries; i++)
          {
            //removes path from the string
            tempString = basename(table1->name);
            //if to check for hidden files
            //Prints the permissions options
            displayPermissions(table1->stbuf.st_mode);
            //Prints the # of links to each file
            (void)printf( "%3.ld ", table1->stbuf.st_nlink);
            //Prints from displayowner and group
            displayOwnerName(table1->stbuf.st_uid);
            displayGroupName(table1->stbuf.st_gid);
            //Prints the time
            (void)printf("%11.ld", table1->stbuf.st_size);
             currenttime = localtime(&(table1->stbuf.st_mtime));
            (void)strftime (buffer,80," %b %e %H:%M",currenttime);
            (void)fputs(buffer,stdout);         
            //prints the filename
            (void)printf(" %s\n", tempString);
            table1++;
           }
          }
        }
      }
    }
  }















}


