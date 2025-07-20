#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/syscall.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  char *err_message = "usage:sleep seconds\n";
  if (argc < 2) {
    write(2, err_message, strlen(err_message));
  }

  int t = atoi(argv[1]);

  sleep(t);
  exit(0);
  
}
