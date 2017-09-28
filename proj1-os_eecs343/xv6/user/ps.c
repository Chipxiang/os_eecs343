#include "types.h"
#include "user.h"
#include "proc.c"

int
main(int argc, char *argv[])
{
    int res;
    res = getprocs(void);
    printf(1,"%d", res);
    exit();
}
