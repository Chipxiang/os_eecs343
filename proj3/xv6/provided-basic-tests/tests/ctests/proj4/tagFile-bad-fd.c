/* call tagFile with bad fd argument.  tagFile should return -1. */
#include "types.h"
#include "user.h"

#define O_RDONLY  0x000
#define O_WRONLY  0x001
#define O_RDWR    0x002
#define O_CREATE  0x200

#undef NULL
#define NULL ((void*)0)

int ppid;
volatile int global = 1;

#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

int
main(int argc, char *argv[])
{
   ppid = getpid();
   int fd = open("ls", O_RDWR);
   printf(1, "fd of ls: %d\n", fd);
   char* key = "type";
   char* val = "utility";
   int len = 7;
   int res = tagFile(-1, key, val, len);
   assert(res == -1);

   res = tagFile(1000, key, val, len);
   assert(res == -1);

   close(fd);
   res = tagFile(fd, key, val, len);
   assert(res == -1);

   printf(1, "TEST PASSED\n");
   exit();
}