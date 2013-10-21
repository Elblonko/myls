/*
 * Filename: nameSortAscending.s
 * Author: Matthew Schwegler
 * Userid: cs30xfw
 * Description: This function takes in a two pointers to names inside of a
 * 		a struct. It then compares them and returns a value indicating
 * 		the relationship of these two names
 *
 * Date: May 12, 2013
 * Sources of Help: Lecture notes
 */

	.global		nameSortAscending

	.section ".data"		! The data segment begins here

	.section ".text"		! The text segment begins here
/*
 * Function name: nameSortAscending
 * Function prototype: int nameSortAscending ( const void *p1, const void *p2 )

 *
 * Description: This function takes in a two pointers to names inside of a
 * 		a struct. It then compares them and returns a value indicating
 * 		the relationship of these two names
 * 
 * Parameters: Two pointers to string names to be compared
 * Side Effects: 
 * Error Conditions: 
 * Return Value: 0 if ptr1=+ptr2, positive in if ptr1>ptr2, negative int
 * 		 if ptr1<ptr2
 * Registers Used: 
 *
 *	%i0 - poiner to name string
 *	%i1 - pointer to name string
 *
 *
 */


nameSortAscending:

	save	%sp, -96,%sp	! Saves the callers window

	mov	%i0, %o0	! Loads ptr1 into l0
	mov	%i1, %o1	! Loads ptr2 into l1

	call	strcmp		! Calls string Compare
	nop

	mov	%o0,%i0		! Moves variables for return

	ret			! returns %i0
	restore

