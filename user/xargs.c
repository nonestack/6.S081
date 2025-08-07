#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"


int
main(int argc, char *argv[])
{
  if (argc >= MAXARG) {
    fprintf(2, "too many parameter\n");
    exit(0);
  }

  
}
