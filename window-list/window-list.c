#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <errno.h>

#include <Xm/XmAll.h>
#include <Dt/WsmP.h>

/* compile -lX11 */
Bool xerror = False;

int handle_error(Display* display, XErrorEvent* error);
Window *winlist (Display *disp, unsigned long *len);
char *winame (Display *disp, Window win); 
Window get_top_window(Display* d, Window start);
Window get_parent_window(Display* d, Window w);

int main(int argc, char *argv[]) {
    int i;
    unsigned long len;
    Display *disp = XOpenDisplay(NULL);
    Window *list;
    char *name;
	
	Window returnedroot;
	Window returnedparent;
	Window * children;
	Window root;
	unsigned int numchildren;

	Atom **listclients;
	unsigned long numclients;

	root = XDefaultRootWindow(disp);
	
	/* XQueryTree(disp,root,&returnedroot, */
	/* 		   &returnedparent,&children, &numchildren); */

	/* for (int i=0; i < numchildren ;i++) */
	/* { */

	/* 	if (get_parent_window(disp,children[i]) == root) */
	/* 	{ */
	/* 		name = winame(disp,children[i]); */
	/* 		printf("Top Level Window[%d]-->%s<--\n",i,name); */
	/* 	} */
	/* 	else */
	/* 	{ */
	/* 		name = winame(disp,children[i]); */
	/* 		printf("Child Window[%d]-->%s<--\n",i,name); */
	/* 	} */
	/* } */
	
	/* // DEBUG */
	/* printf("Number of children of XQueryTree = %d\n", */
	/* 	   (int)numchildren); */

    /* if (!disp) { */
    /*     puts("no display!"); */
    /*     return -1; */
    /* } */
 
    /* list = (Window*)winlist(disp,&len); */

	/* printf("Number of windows: %d\n",(int)len); */
	
    /* for (i=0;i<(int)len;i++) { */
    /*     name = winame(disp,list[i]); */
    /*     printf("-->%s<--\n",name); */
    /*     free(name); */
    /* } */

	// DEBUG
	printf("Start winding...\n");

	Window *mwmWindow;
	
	_DtGetMwmWindow(disp,root,mwmWindow);
	
	// DEBUG
	printf("Start listing...\n");

	_DtGetEmbeddedClients(disp,root,listclients,&numclients);

	printf("_DtGetEmbeddedClients...\n");

	for (int i=0;i<numclients;i++)
	{
		printf("Cliente type for [%d]=%s\n",
			   i,
			   XmGetAtomName(disp,listclients[i]));
	}

	// DEBUG
	printf("End listing...\n");
	
    XFree(list);
 
    XCloseDisplay(disp);
    return 0;
}
 
int handle_error(Display* display, XErrorEvent* error)
{
  printf("ERROR: X11 error\n");
  xerror = True;
  return 1;
}

Window *winlist (Display *disp, unsigned long *len) {
    Atom prop = XInternAtom(disp,"_NET_CLIENT_LIST",False), type;
    int form;
    unsigned long remain;
    unsigned char *list;
 
    errno = 0;
    if (XGetWindowProperty(disp,XDefaultRootWindow(disp),prop,0,1024,False,XA_WINDOW,
                &type,&form,len,&remain,&list) != Success) {
        perror("winlist() -- GetWinProp");
        return 0;
    }
     
    return (Window*)list;
}
 
 
char *winame (Display *disp, Window win) {
    Atom prop = XInternAtom(disp,"WM_NAME",False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;
 
    errno = 0;
    if (XGetWindowProperty(disp,win,prop,0,1024,False,XA_STRING,
                &type,&form,&len,&remain,&list) != Success) {
        perror("winlist() -- GetWinProp");
        return NULL;
    }
 
    return (char*)list;
}

Window get_top_window(Display* d, Window start)
{
  Window w = start;
  Window parent = start;
  Window root = None;
  Window *children;
  unsigned int nchildren;
  Status s;

  printf("getting top window ... \n");
  while (parent != root) {
    w = parent;
    s = XQueryTree(d, w, &root, &parent, &children, &nchildren); // see man

    if (s)
      XFree(children);

    if(xerror){
      printf("fail\n");
      exit(1);
    }

    printf("  get parent (window: %d)\n", (int)w);
  }

  printf("success (window: %d)\n", (int)w);

  return w;
}

Window get_parent_window(Display* d, Window w)
{
  Window parent;
  Window root = None;
  Window *children;
  unsigned int nchildren;
  Status s;

  printf("getting parent window ... \n");

  s = XQueryTree(d, w, &root, &parent, &children, &nchildren); // see man

  if (s)
      XFree(children);
  
  return parent;
}
