#!/bin/env python
def f(*args):
    for (i,arg) in enumerate(args):
        print "in function 'f':args[%d]=%s\n" % (i,str(arg))


if __name__ == "__main__":
    f(1,1,2)
    a=(1,2,3)
    f(a)
