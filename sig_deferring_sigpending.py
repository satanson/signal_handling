#!/bin/env python
import sys
from pysigset import *
from time import sleep
from signal import *
from posix_timers import *

if __name__ == "__main__":
    st=10 if len(sys.argv)!=2 else int(sys.argv[1])
    print "sleep for %ds in each round\n" %(st)

    s=SIGSET()
    saved_s=SIGSET()
    pending_s=SIGSET()
    #sigemptyset(s)
    sigaddset(s,SIGINT)
    n=0
    MICRO=1.0/1000000.0
    while True:
        sigprocmask(SIG_BLOCK,s,saved_s)
        bt=clock_gettime(CLOCK_MONOTONIC)
        sleep(st)
        et=clock_gettime(CLOCK_MONOTONIC)
        print "sleep:%f" %(et-bt)
        ++n
        sigpending(pending_s)
        if sigismember(pending_s,SIGINT):
            print "Gotten a SIGINT!!\n"
            break
        else:
            pass


