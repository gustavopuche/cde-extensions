#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_window_properties(Display *display, Window *window) {
    char *window_name;
    int pid;
    {
        XTextProperty text_data;
        Atom atom = XInternAtom(display, "WM_NAME", True);
        int status = XGetTextProperty(display, window, &text_data, atom);
        window_name = (char *)text_data.value;
    }
    {
        XTextProperty text_data;
        Atom atom = XInternAtom(display, "_NET_WM_PID", True);
        int status = XGetTextProperty(display, window, &text_data, atom);
        if(text_data.nitems) {
            pid = (unsigned char *)text_data.value;
            pid = text_data.value[1] * 256;
            pid += text_data.value[0];
        }
    }
	
	if (window_name != NULL)
	{
		printf("pid=%5i wm_name=%s\n", pid, window_name);
	}
}

void get_windows(Display *display, Window rootwin, int depth) {
    Window parent;
    Window *children;
    Window *child;
    unsigned int no_of_children;

    Status status = XQueryTree(display, rootwin, &rootwin,
							   &parent, &children, &no_of_children);
    //printf("status=%i\n", status);

    //printf("no_of_children=%i\n", no_of_children);

    if(!status) {
        //printf("Error retrieving windows\n");
        return;
    }

    if(!no_of_children) {
        //printf("No more windows\n");
        return;
    }

    int i;
    for(i = 0; i < no_of_children; i++) {
        child = children[i];
		if (depth==0)
		{
			print_window_properties(display, child);
			printf("depth=%i, child=%p parent=%p\n",
				   depth, child, parent);
		}
        get_windows(display, child, depth + 1);
    }

}

int main() {
    Display *display;

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot connect to X server %s\n", "simey:0");
        exit (-1);
    }

    int screen_num = DefaultScreen(display);
    printf("screen_num %i\n", screen_num);
    printf("display dimensions %i,%i\n", DisplayWidth(display, screen_num), DisplayHeight(display, screen_num));

    Window rootwin = DefaultRootWindow(display);

    int depth;
    get_windows(display, rootwin, 0);

    return 0;
}
