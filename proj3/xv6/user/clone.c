#include "types.h"
#include "user.h"

#define PGSIZE (4096)

volatile int global = 1;

void DoThreadWork(void* arg_ptr); // function signature for our DoThreadFunction

int
main(int argc, char* argv[])
{
 void* stack = malloc(PGSIZE*2); // allocate 2 pages of space
 if((uint)stack % PGSIZE) {
 // make sure that stack is page-aligned
 stack = stack + (PGSIZE - (uint)stack % PGSIZE);
 }

 void* arg = NULL; // our DoThreadWork function is simple and doesn't need an arg
 int clone_pid = clone(DoThreadWork, arg, stack);
 clone_pid = clone_pid + 0;
 // the main thread of execution (aka parent process) continues executing here
 while(global != 5) {
 ; // wait for child thread to finish
 }
 printf(1, "global: %d\n", global); // prints "global: 5"
 exit();
}

void
DoThreadWork(void* arg_ptr) {
 // clone creates a new thread, which begins execution here
 global = 5;
 exit();
}
