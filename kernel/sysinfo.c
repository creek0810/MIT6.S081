#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"
#include "proc.h"
#include "sysinfo.h"

uint64
sys_sysinfo(void)
{
  // get arg
  uint64 addr;
  if(argaddr(0, &addr) < 0)
    return -1;

  // construct sysinfo
  struct sysinfo info;
  info.nproc = get_proc_num();
  info.freemem = get_freemem();

  // update
  struct proc *p = myproc();
  if(copyout(p->pagetable, addr, (char *)&info, sizeof(info)) < 0)
    return -1;
  return 0;
}

