// -*- coding:utf-8-unix; mode:c; -*-
/*
  get the active window on X window system
  http://k-ui.jp/blog/2012/05/07/get-active-window-on-x-window-system/
 */

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include <X11/Xlib.h>           // `apt-get install libx11-dev`
#include <X11/Xmu/WinUtil.h>    // `apt-get install libxmu-dev`

Bool xerror = False;

Display* open_display(){
  printf("connecting X server ... ");
  Display* d = XOpenDisplay(NULL);
  if(d == NULL){
    printf("fail\n");
    exit(1);
  }else{
    printf("success\n");
  }
  return d;
}

int handle_error(Display* display, XErrorEvent* error){
  printf("ERROR: X11 error\n");
  xerror = True;
  return 1;
}

Window get_focus_window(Display* d){
  Window w;
  int revert_to;
  printf("getting input focus window ... ");
  XGetInputFocus(d, &w, &revert_to); // see man
  if(xerror){
    printf("fail\n");
    exit(1);
  }else if(w == None){
    printf("no focus window\n");
    exit(1);
  }else{
    printf("success (window: %d)\n", (int)w);
  }

  return w;
}

// get the top window.
// a top window have the following specifications.
//  * the start window is contained the descendent windows.
//  * the parent window is the root window.
Window get_top_window(Display* d, Window start){
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

// search a named window (that has a WM_STATE prop)
// on the descendent windows of the argment Window.
Window get_named_window(Display* d, Window start){
  Window w;
  printf("getting named window ... ");
  w = XmuClientWindow(d, start); // see man
  if(w == start)
    printf("fail\n");
  printf("success (window: %d)\n", (int) w);
  return w;
}

// (XFetchName cannot get a name with multi-byte chars)
void print_window_name(Display* d, Window w){
  XTextProperty prop;
  Status s;

  printf("window name:\n");

  s = XGetWMName(d, w, &prop); // see man
  if(!xerror && s){
    int count = 0, result;
    char **list = NULL;
    result = XmbTextPropertyToTextList(d, &prop, &list, &count); // see man
    if(result == Success){
      printf("\t%s\n", list[0]);
    }else{
      printf("ERROR: XmbTextPropertyToTextList\n");
    }
  }else{
    printf("ERROR: XGetWMName\n");
  }
}

void print_window_class(Display* d, Window w){
  Status s;
  XClassHint* class;

  printf("application: \n");

  class = XAllocClassHint(); // see man
  if(xerror){
    printf("ERROR: XAllocClassHint\n");
  }

  s = XGetClassHint(d, w, class); // see man
  if(xerror || s){
    printf("\tname: %s\n\tclass: %s\n", class->res_name, class->res_class);
  }else{
    printf("ERROR: XGetClassHint\n");
  }
}

void print_window_info(Display* d, Window w){
  printf("--\n");
  print_window_name(d, w);
  print_window_class(d, w);
}

int main(void){
  Display* d;
  Window root;
  Window w;
  unsigned int width, height;     /* Window size */
  int x, y;                       /* Window position */
  int x_local, y_local;           /* Window position */
  unsigned int border_width;
  unsigned int depth;
  int screen_num;
  unsigned int display_width, display_height;
  XWindowAttributes attr;

  // for XmbTextPropertyToTextList
  setlocale(LC_ALL, ""); // see man locale

  d = open_display();
  XSetErrorHandler(handle_error);

  /* Get screen size from display structure macro */
  screen_num = DefaultScreen(d);
  display_width = DisplayWidth(d, screen_num);
  display_height = DisplayHeight(d, screen_num);

  // Debug
  printf("Display width %d pixels\n",display_width);
  printf("Display height %d pixels\n",display_height);

  Window child;
  root =  XRootWindow(d, 0);

  // get active window
  w = get_focus_window(d);

  XTranslateCoordinates(d, w, root, 0, 0, &x, &y, &child);

  // Debug
  printf("Window focus_window x %d pixels\n",x);
  printf("Window focus_window y %d pixels\n",y);

  w = get_top_window(d, w);

  XTranslateCoordinates(d, w, root, 0, 0, &x, &y, &child);

  // Debug
  printf("Window top_window x %d pixels\n",x);
  printf("Window top_window y %d pixels\n",y);

  w = get_named_window(d, w);

  /* XTranslateCoordinates(d, w, root, 0, 0, &x, &y, &child); */

  /* // Debug */
  /* printf("Window named_window x %d pixels\n",x); */
  /* printf("Window named_window y %d pixels\n",y); */

  if (!XGetGeometry(d, w, &root, &x_local, &y_local, &width, &height, 
                            &border_width, &depth))
  {
	  printf("ERROR getting Geometry!!!\n");
	  return -1;
  }

  // Debug
  printf("Window x %d pixels\n",x);
  printf("Window y %d pixels\n",y);
  printf("Window width %d pixels\n",width);
  printf("Window height %d pixels\n",height);
  printf("Window border_width %d pixels\n",border_width);
  printf("Window depth %d pixels\n",depth);


  XGetWindowAttributes(d, w, &attr);

  // Debug
  printf("Window Attribute x %d pixels\n",attr.x);
  printf("Window Attribute y %d pixels\n",attr.y);
  printf("Window Attribute width %d pixels\n",attr.width);
  printf("Window Attribute height %d pixels\n",attr.height);
  printf("Window Attribute border_width %d pixels\n",
		 attr.border_width);
  printf("Window Attribute depth %d pixels\n",attr.depth);

  
  // Move to y=0
  XMoveWindow(d,w,x,0);
  XResizeWindow(d,w,width,display_height);
  
  print_window_info(d, w);
}
