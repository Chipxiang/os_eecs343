#include "types.h"
#include "user.h"
#include "param.h"
#include "ProcessInfo.h"
int
main(int argc, char *argv[])
{
  int *p = NULL;
  int a = *p;
  *p = 999;
  int *p1 = NULL;
  printf(1, "%d %d %d\n", *p, a, *p1);
  exit();
}
