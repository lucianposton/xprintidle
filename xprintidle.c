/*

This program prints the "idle time" of the user to stdout.  The "idle
time" is the number of milliseconds since input was received on any
input device.  If unsuccessful, the program prints a message to stderr
and exits with a non-zero exit code.

Copyright (c) 2005, 2008 Magnus Henoch <henoch@dtek.chalmers.se>
Copyright (c) 2006, 2007 by Danny Kukawka
                         <dkukawka@suse.de>, <danny.kukawka@web.de>
Copyright (c) 2008 Eivind Magnus Hvidevold <hvidevold@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the
Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

*/

#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>
#include <X11/extensions/scrnsaver.h>
#include <stdio.h>

void usage(char *name);

int main(int argc, char *argv[])
{
  XScreenSaverInfo *ssi;
  Display *dpy;
  int event_basep, error_basep;

  if (argc != 1) {
    usage(argv[0]);
    return 1;
  }
  
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL) {
    fprintf(stderr, "couldn't open display\n");
    return 1;
  }
  
  if (!XScreenSaverQueryExtension(dpy, &event_basep, &error_basep)) {
    fprintf(stderr, "screen saver extension not supported\n");
    return 1;
  }

  ssi = XScreenSaverAllocInfo();
  if (ssi == NULL) {
    fprintf(stderr, "couldn't allocate screen saver info\n");
    return 1;
  }   
  
  if (!XScreenSaverQueryInfo(dpy, DefaultRootWindow(dpy), ssi)) {
    fprintf(stderr, "couldn't query screen saver info\n");
    return 1;
  }
  
  printf("%lu\n", ssi->idle);

  XFree(ssi);
  XCloseDisplay(dpy);
  return 0;
}

void usage(char *name)
{
  fprintf(stderr,
	  "Usage:\n"
	  "%s\n"
	  "That is, no command line arguments.  The user's idle time\n"
	  "in milliseconds is printed on stdout.\n",
	  name);
}
