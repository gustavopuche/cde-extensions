# $XConsortium: Makefile.ibm /main/2 1996/05/13 11:53:53 drk $
##########################################################################
#
#  Makefile for dtwidget examples (IBM)
#
#  (c) Copyright 1993, 1994 Hewlett-Packard Company	
#  (c) Copyright 1993, 1994 International Business Machines Corp.
#  (c) Copyright 1993, 1994 Sun Microsystems, Inc.
#  (c) Copyright 1993, 1994 Novell, Inc.
#
##########################################################################

CC		= cc
RM		= rm -f

PROGRAM 	= move-to-pos
SOURCES 	= move-to-pos.c
OBJECTS 	= move-to-pos.o

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
