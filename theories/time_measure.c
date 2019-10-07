/*
Use for measuring the elapsed time after running a function.
*/
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h> // for sleep()
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for clock(), time(), and clock_gettime()
#include <sys/time.h> // for gettimeofday()
void doSomething(){
    sleep(2); // sleep for 1 seconds
}

int main(){
    // WAY 1: clock()
    clock_t t = clock();
    doSomething();
    t = clock() - t;
    printf("Elapsed: %lf\n", ((double)t)/CLOCKS_PER_SEC); // which will not output 1 seconds because it only measure the time run by CPU.

    // WAY 2: time()
    time_t et = time(NULL);
    doSomething();
    et = time(NULL) - et;
    printf("Elapsed: %ld\n", et); // output 1 but it is only shown in seconds, not miliseconds.

    // WAY 3: gettimeofday() 
    // WARNING: might not work on Windows
    struct timeval start, end;

    gettimeofday(&start, NULL);

    doSomething();

    gettimeofday(&end, NULL);

    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Elapsed: %ld seconds or %ld micros\n", seconds, micros);

    return 0;
}

