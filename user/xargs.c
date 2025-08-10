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
    exit(1);
  }
  if (argc < 2) {
    fprintf(2, "using: xargs command parameters ...\n");
    exit(1);
  }


  if (fork() > 0) { // parent
    wait(0);
  }
  else {  // child
    
    char str[PARAM_SIZE];
    char *arr[MAXARG] = {0};

    int ret = 0;
    char *p = malloc(PARAM_SIZE * sizeof(char));
    memset(p, 0, PARAM_SIZE);
    int idx = 0;
    int pidx = 0;
    int sidx = 0;

    for (int i = 1; i < argc; ++i) {
      memmove(p, argv[i], strlen(argv[i]));
      arr[idx++] = p;
      p = malloc(PARAM_SIZE * sizeof(char));
      memset(p, 0, PARAM_SIZE);
      
    }
    
    while ((ret = read(0, str, PARAM_SIZE)) > 0) {

      for (int i = 0; i < ret; ++i) {
        if (str[sidx] != '\n') {
          p[pidx++] = str[sidx++];
        }
        else {
          if (idx >= MAXARG) break;
          arr[idx++] = p;
          p = malloc(PARAM_SIZE * sizeof(char));
          memset(p, 0, PARAM_SIZE);
          pidx = 0;
        }
        
      }
      sidx = 0;
    }

    exec(argv[1], arr);
  }

  exit(0);
}
