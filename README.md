Deskentry Library
==================

This is library can help you manage desktop menu launchers from you code.
All about .desktop file can be found here https://specifications.freedesktop.org/desktop-entry-spec/latest/

Build&Installation
==================

    $: make
    $: sudo make install

Uninstall
=========

    $: sudo make uninstall

Example
==================
'''
    #include <stdio.h>
    #include <stdlib.h>
    #include <deskentry.h>

    int main(int argc, char *argv[])
    {
      int fd = openFile("/usr/share/applications/xfce4-power-manager-settings.desktop");
      if (fd)
      {
          entryline_t *entryline = 0;
          while ((entryline = readEntry(fd)))
          {
              printf("%15s %5s = %s\n", getKeyStrByIndex(entryline->key), entryline->locale, entryline->value);
              free(entryline);
          }
      }
      return 0;
    }
'''
Build Example
===================

$: gcc source_code.c -ldeskentry
