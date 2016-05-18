#ifndef DESKENTRY_H_INCLUDED
#define DESKENTRY_H_INCLUDED

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>

#define F_LEN_COMM        1024
#define F_LEN_TYPE        28
#define F_LEN_CTEG        28
#define ENTRY_KEY_MAX     22
#define LOCALE_MAX        50
#define ENTRY_LINE_MAX    PATH_MAX + ENTRY_KEY_MAX
#define NUM_OF_KEYS       23

#define INITIAL_LINE      "[Desktop Entry]"

//----------------------------------------------------------------

typedef enum EEntryKeys
{
  Type = 0,
  Version,
  Name,
  GenericName,
  NoDisplay,
  Comment,
  Icon,
  Hidden,
  OnlyShowIn,
  NotShowIn,
  DBusActivatable,
  TryExec,
  Exec,
  Path,
  Terminal,
  Actions,
  MimeType,
  Categories,
  Implements,
  Keywords,
  StartupNotify,
  StartupWMClass,
  URL

} EEntryKeys;
//----------------------------------------------------------------

typedef struct entryline_t
{
  EEntryKeys key;
  char value[PATH_MAX];
  char locale[LOCALE_MAX];

} entryline_t;
//----------------------------------------------------------------
// return file descriptor or NULL if error
// need path of file with name
int openFile(char *path);
//----------------------------------------------------------------
// return file descriptor or NULL if error
// need path of file with name
int createFile(char *path);
//----------------------------------------------------------------
// function takes char *key and return index of this key in const array
// if have no key return -1
int indexOfKey(const char *key);
//----------------------------------------------------------------
// this function receive entryline_t structure,
// merge all data in it to one string and write it to file
void writeEntry(int fd, entryline_t *entryline);
//----------------------------------------------------------------
// Read one line from desktop entry file
// Return entryline_t structure that contain index of key and value
entryline_t *readEntry(int fd);
//----------------------------------------------------------------
// Get entry key index providet by EEntryKeys enum
// Return string that contained in array of entry keys by current index or NULL
const char *getKeyStrByIndex(EEntryKeys key);
//----------------------------------------------------------------



#endif // DESKENTRY_H_INCLUDED
