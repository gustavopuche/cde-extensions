# $Gustavo Puche: Makefile 2018/02/26 13:15:00
##########################################################################
#
#  Makefile for move-to-left
#
#  (c) Copyright 2018 Gustavo Puche Rodríguez 
#
##########################################################################

CC		= cc
RM		= rm -f

PROGRAM 	= move-to-left
SOURCES 	= move-to-left.c
OBJECTS 	= move-to-left.o

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
