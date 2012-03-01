TRUNK	= sub1_stderr
EXE		= .exe
OBJ		= .obj
#OBJ		= main.o
SRC		= .c
#CC		= gcc
CC		= cl
WORD	= def

#all: $(TRUNK)$(EXE)

$(TRUNK)_$(CC)$(EXE): $(TRUNK)_$(CC)$(OBJ)
	$(CC) /Fe$(TRUNK)_$(CC)$(EXE) $(TRUNK)_$(CC)$(OBJ)

$(TRUNK)_$(CC)$(OBJ): $(TRUNK)$(SRC)
	$(CC) /Fo$(TRUNK)_$(CC)$(OBJ) $(TRUNK)$(SRC)

set_vars:
	echo vcvars32
	vcvars32
