/*
 * Filename: buildFileInfoTable.c
 * Author: Matthhew Schwegler
 * Userid: cs30xfw
 * Description: This function takes in a file or directory name and builds
 *              creates a space in memory to hold a table of every file pointed
 *              too by passed in pointer

 *
 * Date: May 27, 2013
 * Sources of Help: Lecture notes
 */

#include <stdio.h>
#include "myls.h"
//includes for functions
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/*
* Function name: buildFileInfoTable.c
* Function prototype: int buildFileInfoTable(const char * filename, 
*                                            struct fileInfo ** const tablePtr) 
* Description: This function takes in a file or directory name and builds
*              creates a space in memory to hold a table of every file pointed
*              too by passed in pointer
*
* Parameters:  filename: a pointer to a file or directory file
*              tablePtr: a pointer to a pointer of a fileInfo struct
*
*            
* Side Effects: Creates a series of entries in memory containing all files and
*               directories pointed to by the passed in filename param
*	              
*Error Conditions:
*
*Return Value: Returns an int passed on how many files where pointed too
*/ 




int buildFileInfoTable(const char * filename,
                      struct fileInfo ** const tablePtr)
{
  /*
   * Local Variable creation
   */
  //struct stat *buf for lstat calls
  struct stat fileStat;
  //pointer to pass to lstat call
//  struct stat buff = fileStat;
  //pointer to space to be used for fileInfo
  struct fileInfo *buffer = NULL;
  //Number of entries
  int numOfEntries = 0;
  //tableptrptr
  struct fileInfo *tablePtr1 = NULL;
  DIR *dir = NULL;
  struct dirent * dirent = {NULL };

  //reset errno for calls that could set its value
  errno = 0;

  int detect = lstat( filename, &fileStat );
    //check if errno is set after lstat call
    if ( detect !=0 || errno !=0 )
    {
      (void) printf(" lstat -- ");
      perror(filename);
    }
  //If S_ISDIR is true then file is a directly
 if( S_ISDIR(fileStat.st_mode) )
 {
   (void) printf("%s:\n",filename);

  //opens dir
 dir = opendir(filename);
 while( ( dirent = readdir(dir) ) != NULL  )
  {
    //new string to hold dir path
    char s[BUFSIZ];
    //creates new string with full path
    //MIGHT NEED A SLASH
    (void)snprintf(s,BUFSIZ, "%s/%s",filename, dirent->d_name ) ;
    //(void)strcpy (s, filename);
    // (void)strcat (s, dirent->d_name );

    //increments to count the numOfEntries
    numOfEntries++;

    
    errno = 0;
    detect = 0;

    detect = lstat(s, &fileStat);
    if ( detect !=0 || errno !=0 )
    {
      (void) printf(" lstat -- ");
      perror(filename);
    }

    //Call realloc to make space for the files
    buffer = (struct fileInfo*) realloc(buffer, (numOfEntries * sizeof(struct fileInfo) ) );
    
    
    tablePtr1 = &buffer[numOfEntries - 1];

    //Set the tablePtr
    (void)strncpy (tablePtr1->name, dirent->d_name, MAXNAMLEN);
    tablePtr1->name[MAXNAMLEN -1 ] = '\0';
    tablePtr1->stbuf = fileStat;
    
  }


  *tablePtr = buffer;
  //clearn errno
  errno = 0;
  (void)closedir(dir);
  if( errno != 0)
    (void)fprintf(stderr, "Close dir failed to close file");
  return numOfEntries; 
 }

/*How do i create a while loop, im not passed an array
 * just a single pointer to a single file?
 */

  
  numOfEntries = 1;

  //Call malloc to allocate space
  buffer = (struct fileInfo*) malloc(sizeof(struct fileInfo) );
  
  //if malloc fails returns null pointer, check for that
  if( buffer == NULL )
  {
    (void) perror("Malloc failed to allocated space for struct fileInfo");
  }

  tablePtr1 = buffer ;


  //fill in the struct fileInfo ptr
  (void)memset(tablePtr1, 0 , sizeof(struct fileInfo) );

  //Set the tablePtr
  (void)strncpy (tablePtr1->name, filename, MAXNAMLEN);
  tablePtr1->name[MAXNAMLEN -1 ] = '\0';
  tablePtr1->stbuf = fileStat;

  *tablePtr = tablePtr1;

  return numOfEntries;


}
