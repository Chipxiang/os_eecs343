#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#define PGSIZE (4096)

int
thread_create(void (*start_routine)(void*), void *arg)
{
  void *userstack = malloc(PGSIZE*2);
  if (!userstack) {
    printf(1, "Error: malloc failed\n");
    exit();
  }
  if((uint)userstack % PGSIZE > 0) {
    userstack = userstack + 4096 - (uint)userstack % PGSIZE;
  }
  return clone(start_routine, arg, userstack);
}

int
thread_join(int pid)
{
  int tid = join(pid);
  if (tid != -1) {
    struct proc *p;
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
        if (p->pid == pid){
            free(p->tstack);
        }
    release(&ptable.lock);
  }
  return tid;
}

void lock_acquire(lock_t* lock){
  while (xchg(lock, 1) == 1)
    ; // spin
}

void lock_release( lock_t *lock) {
  *lock = 0;
}

void lock_init(lock_t *lock) {
  *lock = 0;
}
