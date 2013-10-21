#
# Makefile template for CSE 30 -- PA3
#

HEADERS		= myls.h

C_SRCS		= myls.c buildFileInfoTable.c displayFileInfo.c\
		  mtimeSortAscending.c nameSortDecending.c\
                  displayPermissions.c displayOwnerName.c

ASM_SRCS	= mtimeSortDecending.s nameSortAscending.s\
                  displayGroupName.s

C_OBJS  	= myls.o buildFileInfoTable.o displayFileInfo.o\
		  mtimeSortAscending.o nameSortDecending.o\
                  displayPermissions.o displayOwnerName.o

ASM_OBJS        = mtimeSortDecending.o nameSortAscending.o\
                  displayGroupName.o

OBJS            = ${C_OBJS} ${ASM_OBJS}

EXE		= myls

#
# You should not need to change anything below this line
#

#
# Relevant man pages:
#
# man gcc
# man as
# man lint
#

GCC		= gcc
ASM		= $(GCC)
LINT		= lint

GCC_FLAGS	= -c -g -Wall -D__EXTENSIONS__
LINT_FLAGS1	= -c -err=warn
LINT_FLAGS2	= -u -err=warn
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall

#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Linting each C source file separately ..."
	$(LINT) $(LINT_FLAGS1) $<
	@echo ""
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be a single default "a.out" executable.
#

$(EXE):	$(OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo "Done."

${C_OBJS}:      ${HEADERS}




clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o $(EXE) *.ln core
	@echo ""
	@echo "Clean."


