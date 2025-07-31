#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path, char *filename)
{
  int pd;
  struct stat st;

  if ((pd = open(path, 0)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if (fstat(pd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    return;
  }

  if (st.type == T_FILE) {
    fprintf(2, "find: %s is not path\n", path);
    return;
  }

    
}

int
main(int argc, char *argv[])
{
  if (argc > 3) {
    printf("using: find dir filename\n");
    exit(0);
  }

  find(argv[1], argv[2]);
  exit(0);
}
