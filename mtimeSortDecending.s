/*
 * Filename: mtimeSortDecending.s
 * Author: Matthew Schwegler
 * Userid: cs30xfw
 * Description: 
 *
 *
 * Date: May 12, 2013
 * Sources of Help: Lecture notes
 */

	.global		mtimeSortDecending

	.section ".data"		! The data segment begins here

	.section ".text"		! The text segment begins here
/*
 * Function name: mtimeSortDecending
 * Function prototype: mtimeSortDecending(const void *p1, const void *p2 )
 *
 * Description: Similair to the mtimeSortAscending function uses the 
 * 		mtime struct to compare file time stamps for use in the
 * 		myls program
 *
 * Parameters: Two pointers to struct mtime for comparison
 * Side Effects: 
 * Error Conditions: 
 * Return Value: 0 if *ptr1=*ptr2, positive in if ptr2>ptr1, negative int
 * 		 if ptr2<ptr1
 * Registers Used: 
 *
 *	%i0 - poiner to struct fileInfo
 *	%i1 - pointer to struct fileInfo
 *
 *
 */


mtimeSortDecending:

	save	%sp, -96,%sp	! Saves the callers window

	mov	%i0, %l1	! Loads ptr1 into l0
	mov	%i1, %l2	! Loads ptr2 into l1

	set	stbuff,%l5	! Loads in my offset
	ld	[%l5],%l5
	add	%l5,%l1,%l1	! Moves ptr1 offset to stbuff
	add	%l5,%l2,%l2	! Moves ptr2 offset to stbuff

	
	set 	stTime,%l5	! sets the offset for stTime into l5
	ld	[%l5], %l5
	add	%l5,%l1,%l1	! Moves to m_time in struct
	add	%l5,%l2,%l2

	ld	[%l1], %l1	! Loads ptr1 into l0
	ld	[%l2], %l2	! Loads ptr2 into l1


	sub	%l1,%l2,%i0	! Subtracts the two times


	ret			! returns %i0
	restore

