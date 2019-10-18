# Gustaovo Puche Makefile /dev/cde-extensions 2018/02/15 11:00:00 
##########################################################################
#
#  Makefile for maximize-vertically
#
#  (c) Copyright 2018 GUSECO Soft.
#
##########################################################################

CC		= cc
RM		= rm -f

PROGRAM 	= maximize-vertically
SOURCES 	= maximize-vertically.c
OBJECTS 	= maximize-vertically.o

# PROGRAM1	= occupy
# SOURCES1	= occupy.c
# OBJECTS1	= occupy.o

# PROGRAM2	= wsinfo
# SOURCES2	= wsinfo.c
# OBJECTS2	= wsinfo.o

DEFINES		= 
CDEBUGFLAGS	= -O
CFLAGS		= $(DEFINES) $(CDEBUGFLAGS)

DTINCLUDE	= -I/usr/dt/include
X11INCLUDE	= -I/usr/include

INCLUDES	= $(DTINCLUDE) $(X11INCLUDE)

DTLIBS		= -L/usr/dt/lib -lDtSvc -ltt -lXm
X11LIBS		= -L/usr/lib -lXt -lX11 -lXmu
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
