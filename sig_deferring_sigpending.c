#include<unistd.h>
#include<sys/signalfd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>

int main(int argc,char**argv){
	sigset_t set,saved_set,pending_set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	int fd=signalfd(-1,&set,SFD_NONBLOCK);
	struct signalfd_siginfo siginfo;

	int n=0;
	int rc;
	struct timespec begin,end,elapse,remain;
	elapse.tv_sec=argc!=2?10:atoi(argv[1]);
	elapse.tv_nsec=0;
	const double NANO=1.0/1000000000;
	printf("sleep for %d in each round\n",elapse.tv_sec);
	while(1){
		sigprocmask(SIG_BLOCK,&set,&saved_set);

		clock_gettime(CLOCK_MONOTONIC,&begin);
		nanosleep(&elapse,&remain);
		clock_gettime(CLOCK_MONOTONIC,&end);
		double ta=remain.tv_sec+remain.tv_nsec*NANO;
		double tb=end.tv_sec-begin.tv_sec
				 +(end.tv_nsec-begin.tv_nsec >0? (end.tv_nsec-begin.tv_nsec)*NANO
						                       : (1+end.tv_nsec-begin.tv_nsec)*NANO-1
				  );		
		printf("%d: sleep:%.3f remain:%.3f\n",n,tb,ta);
		++n;
		sigemptyset(&pending_set);
		sigpending(&pending_set);

		if (sigismember(&pending_set,SIGINT)){
			printf("Gotten a SIGINT!!!\n");
			break;
		}
	}
}
