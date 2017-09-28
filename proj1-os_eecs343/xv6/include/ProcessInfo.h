#ifndef PROCESSINFO_H
#define PROCESSINFO_H
struct ProcessInfo {
  int pid; // process id
  int ppid; // parent pid
  int state; // state
  uint sz; // size in bytes
  char name[16]; // name of process
};
#endif
