/*
 * Filename: myls.h
 * Author: Matthew Schwegler
 * Userid: cs30xfw
 * Description: 
 *
 * Date: May 27, 2013
 * Sources of Help: Lecture notes
 */


/*
 * Defines used in myls
 */
#ifndef _MYLS_H
#define _MYLS_H


#define AFLAG 0x1
#define LFLAG 0x2
#define RFLAG 0x4
#define TFLAG 0x8

#include <dirent.h> /* To pick up MAXNAMLEN ­ maximum filename length */
#include <sys/stat.h> /* For struct stat definition */

#include <errno.h>
/*
 * Structures
 */

struct fileInfo
{
  char name[MAXNAMLEN];
  struct stat stbuf;
};

/*
 * C routines
 */

int buildFileInfoTable (const char *filename, struct fileInfo ** const tablePtr);

void displayFileInfo ( struct fileInfo * const table, const int entries, 
                      const int displayMode );

int mtimeSortAscending ( const void *p1, const void *p2 );

int nameSortDecending ( const void *p1, const void *p2 );

void displayPermissions ( const mode_t mode );

void displayOwnerName ( const uid_t uid );



/*
 * Aseembly routines
 */

int mtimeSortDecending ( const void *p1, const void *p2);

int nameSortAscending ( const void *p1, const void *p2);

void displayGroupName ( const gid_t gid );


#endif /* _MYLS_H */


