/*
*   Copyright (C) 2016 Dmytro Volovnenko
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "deskentry.h"

//----------------------------------------------------------------
const char *entryKeys[] = {  "Type",
                              "Version",
                              "Name",
                              "GenericName",
                              "NoDisplay",
                              "Comment",
                              "Icon",
                              "Hidden",
                              "OnlyShowIn",
                              "NotShowIn",
                              "DBusActivatable",
                              "TryExec",
                              "Exec",
                              "Path",
                              "Terminal",
                              "Actions",
                              "MimeType",
                              "Categories",
                              "Implements",
                              "Keywords",
                              "StartupNotify",
                              "StartupWMClass",
                              "URL"
                           };
//----------------------------------------------------------------

int writeFullStr(int fd, const char *sourceStr, size_t lenth);
//----------------------------------------------------------------
//function takes char *key and return index of this key in const array
//if have no key return -1
int indexOfKey(const char *key)
{
    int index = -1;
    int i = 0;
    for (; i < NUM_OF_KEYS; ++i)
    {
        if (!strcmp(key, entryKeys[i]))
        {
            index = i;
            break;
        }
    }

    return index;
}
//----------------------------------------------------------------
// return file descriptor or NULL if error
// need path of file with name
int openFile(char *path)
{
    int fd = 0;

    if ((fd = open(path, O_RDONLY)) == -1)
    {
        //perror("Create file");
        return -1;
    }

    return fd;
}
//----------------------------------------------------------------
// return file descriptor or NULL if error
// need path of file with name
int createFile(char *path)
{
    int fd = 0;

    if ((fd = open(path, O_WRONLY, O_CREAT | O_EXCL)) == -1)
    {
        //perror("Open file");
        return -1;
    }
    writeFullStr(fd, INITIAL_LINE"\n", strlen(INITIAL_LINE));

    return fd;
}
