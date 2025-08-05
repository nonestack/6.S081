#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void
getname(char *path, char *fname)
{
  char *p = path + strlen(path);  // *p == 0
  --p;

  while (*p == '/') {
    *p = 0;
    --p;
  }

  while (p >= path && *p != '/') --p; // *p == '/'
  ++p;
  memmove(fname, p, strlen(p));
}

void
find(char *path, char *filename)
{  
  int fd;
  struct stat st;
  struct dirent de;

  if ((fd = open(path, 0)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    return;
  }

  char fn[512];
  getname(path, fn);
  if (strcmp(fn, filename) == 0) {
    fprintf(1, "%s\n", path);
  }

  if (st.type == T_FILE) {
    return;
  }

  if (st.type == T_DIR) {
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0)
        continue;

      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;

      char subpath[512];
      memmove(subpath, path, strlen(path));
      memmove(subpath + strlen(path), de.name, strlen(de.name));
      find(subpath, filename);
    }
  }
  
}

int
main(int argc, char *argv[])
{
  //now argc == 1 && argc == 2 not support
  if (argc == 1) {  //find . all: print all file in this dir or file
    fprintf(2, "using: find path filename\n");
  }
  else if (argc == 2) { // find . filename
    fprintf(2, "using: find path filename\n");
  }
  else { // find path filename ***
    find(argv[1], argv[2]);
  }
  exit(0);
}
