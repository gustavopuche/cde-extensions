# Gustavo Puche: Makefile 2018/03/12 
##########################################################################
#
#  Makefile for list-windows-pids
#
#  (c) Copyright 2018 Gustavo Puche
#
##########################################################################

CC		= cc
RM		= rm -f

PROGRAM 	= list-windows-pids
SOURCES 	= list-windows-pids.c
OBJECTS 	= list-windows-pids.o

DEFINES		= 
CDEBUGFLAGS	= -O
CFLAGS		= $(DEFINES) $(CDEBUGFLAGS)

DTINCLUDE	= -I/usr/dt/include
X11INCLUDE	= -I/usr/include

INCLUDES	= $(DTINCLUDE) $(X11INCLUDE)

DTLIBS		= -L/usr/dt/lib -lDtSvc -ltt -lXm
X11LIBS		= -L/usr/lib -lXt -lX11 -lXmu -lXrandr
SYSLIBS		= 

LIBRARIES	= $(DTLIBS) $(X11LIBS) $(SYSLIBS)
LDFLAGS		= 

.c.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $<

all::	$(PROGRAM)

$(PROGRAM)::	$(OBJECTS)
	$(CC) -o $(PROGRAM) $(LDFLAGS) $(OBJECTS) $(LIBRARIES)

clean::
	$(RM) $(PROGRAM) $(OBJECTS)
