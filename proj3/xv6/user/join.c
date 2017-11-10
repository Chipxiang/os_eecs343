#include "types.h"
#include "user.h"

#define PGSIZE (4096)

int global = 1;

void DoThreadWork(void* arg_ptr);

int
main(int argc, char* argv[])
{

 void* stack = malloc(PGSIZE*2); // as before, allocate 2 pages
 if((uint)stack % PGSIZE){
 stack = stack + (PGSIZE - (uint)stack % PGSIZE); // make sure the stack is page aligned
 }

 int arg = 42;
 int clone_pid = clone(worker, &arg, stack);
 // main thread continues executing...
 int join_pid = join(clone_pid); // ...but waits for the new thread to complete
 // note that join_pid should equal clone_pid
 printf(1, "global: %d\n", global); // prints "global: 43"
 exit();
}

void
DoThreadWork(void *arg_ptr) {
 int arg = *(int*)arg_ptr;
 global = global + arg;
 exit();
}
