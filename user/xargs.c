#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

#define PARAM_SIZE 128

int
main(int argc, char *argv[])
{
  if (argc >= MAXARG) {
    fprintf(2, "too many parameter\n");
    exit(0);
  }

  if (fork() > 0) { // parent
    wait(0);
  }
  else {  // child
    char params[MAXARG][PARAM_SIZE];

    char c;
    char p[PARAM_SIZE] = {0};
    int pidx = 0;
    int psidx = 0;
    while (read(1, &c, 1) == 1) {
      fprintf(1, "%c = %d\n", c, c);
      if (c != '\n') {
        p[pidx++] = c;
      }
      else {
        memmove(params[psidx++], p, PARAM_SIZE);
        memset(p, 0, PARAM_SIZE);
        pidx = 0;
      }
    }

    if (p[0] != 0 && pidx > 0) {
      memmove(params[psidx++], p, PARAM_SIZE);
    }


    for (int i = 1; i < argc; ++i) {
      // p[i - 1] = argv[i];
      fprintf(1, "p%d = %s\n", i, argv[i]);
    }

    for (int i = 0; i < psidx; ++i) {
      fprintf(1, "ps%d = %s\n", i, params[i]);
    }
    exit(0);
    
  }

  exit(0);
}
