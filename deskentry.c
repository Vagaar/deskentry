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
//----------------------------------------------------------------
//this function receive entryline_t structure, merge all data in it to one string and write it to file
void writeEntry(int fd, entryline_t *entryline)
{
    char line[ENTRY_LINE_MAX] = {0};

    strcpy(line, getKeyStrByIndex(entryline->key));
    strcat(line, entryline->locale);
    strcat(line, " = ");
    strcat(line, entryline->value);
    strcat(line, "\n");

    writeFullStr(fd, line, strlen(line));

}

//----------------------------------------------------------------
// Read one line from desktop entry file
// Return entryline_t structure that contain index of key and value
entryline_t *readEntry(int fd)
{
    int index = 0;
    int i = 0;
    char step = 0;
    char buff[PATH_MAX] = {0};
    u_int8_t isNewLine = 1;
    u_int8_t local = 0;
    entryline_t *entryline = malloc(sizeof(entryline_t));
    memset(entryline->locale, 0, LOCALE_MAX);
    memset(entryline->value, 0, NAME_MAX);

    while (read(fd, &step, sizeof(char)) != 0)
    {
        if (step == -1)
        {
            //perror("Reading file");
            return NULL;
        }

        switch (step)
        {

        case '=': //value pars start
            if (isNewLine)
                index = indexOfKey(buff);

            memset(buff, 0, strlen(buff));
            isNewLine = 0;
            i = 0;
            break;

        case '\n': //key pars start
            if (!isNewLine && index != -1)
            {
                entryline->key = index;
                strncpy(entryline->value, buff, PATH_MAX);
                return entryline;
            }
            isNewLine = 1;
            memset(buff, 0, strlen(buff));
            i = 0;
            break;

        case '[':  //local pars start
            if (isNewLine && buff[0] != '\0')
            {
                memset(entryline->locale, 0, strlen(entryline->locale));
                while (read(fd, &step, sizeof(char)))
                {
                    if (step == ']')
                        break;

                    entryline->locale[local] = step;
                    ++local;
                }
            }

            break;

        default:
            buff[i] = step;
            ++i;
            break;
        }
    }

    return NULL;
}
//----------------------------------------------------------------
// Get entry key index providet by EEntryKeys enum
// Return string that contained in array of entry keys by current index or NULL
const char *getKeyStrByIndex(EEntryKeys key)
{
    if (key < NUM_OF_KEYS)
    {
        return entryKeys[key];
    }

    return NULL;
}

//----------------------------------------------------------------
int writeFullStr(int fd, const char *sourceStr, size_t lenth)
{
    size_t ret;

    while (lenth != 0 && (ret = write(fd, sourceStr, lenth)) != 0)
    {
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;
            //perror("write");
            return -1;
        }
        lenth -= ret;
        sourceStr += ret;
    }

    return 0;
}

