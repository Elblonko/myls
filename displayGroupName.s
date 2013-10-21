/*
 * Filename: displayGroupName.s
 * Author: Matthew Schwegler
 * Userid: cs30xfw
 * Description: This function takes in a struct gid_t and uses this to display
 * 	 	the group properties of the struct to the user
 *
 *
 * Date: May 30, 2013
 * Sources of Help: Lecture notes
 */

	.global		displayGroupName! Declares the symbol globally

	.section ".data"		! The data segment begins here
PNUM:
	.asciz "%d"
PWORD:
	.asciz "%s"



	.section ".text"		! The text segment begins here
/*
 * Function name: displayGroupName.s
 * Function prototype: void displayGroupName( const gid_t gid )
 *
 * Description: This function takes in a struct gid_t and uses this to display
 * 	 	the group properties of the struct to the user
 *
 * Parameters: Struct gid_t containting group info
 *
 * Side Effects: 
 *
 * Error Conditions: 
 *
 * Return Value:Display the group properties of a file to the user 
 *
 * Registers Used: 
 *
 *	%i0 - poiner to git_t
 *	%i1 - pointer to git_t 
 *
 *
 */


displayGroupName:

	save	%sp, -96,%sp	! Saves the callers window

	mov	%i0, %o0	! Loads ptr1 into l0
	mov	%i0, %l0

	set	errno,%l4	! Errno to %l4
	st	%g0,[%l4]

	mov	%i0,%o0
	mov	%i1,%o1

	call	getgrgid	! Calls string Compare
	nop

	ld	[%l4],%l4
				! Check if null print out group name
	cmp	%l4,%g0		! Compares errno to 0
	bne	ERROR
	nop

	ld	[%o0],%o1		! Moves the string group name
	set	PWORD,%o0	! Moves the string for print

	call	printf		! Call for print f on success
	nop

	ret			! returns %i0
	restore
ERROR:
	set	PNUM,%o0
	ld	[%l0],%o1		! Moves for variable in print command

	call	printf		! Prints the number value of a failed call
	nop

	ret			! returns %i0
	restore

