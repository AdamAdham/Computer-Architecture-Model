#define _GNU_SOURCE
#define CORE_ID 1  // Change this to the desired core ID
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <linux/sched.h>
#include <string.h>
#include <time.h>

int delay = 1000000000;
float totalTime = 0;
double start1, end1,end2,end3,end4;
int policy;

void* func1(void* arg) {
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    start1 = start.tv_sec + (start.tv_nsec / 1e9);
    printf("Start time 1: %lf \n",start.tv_sec + (start.tv_nsec / 1e9));
    for(int i=0;i<delay;i++){
    }
    pthread_t id = pthread_self();
    printf("First thread id: %lu\n", (unsigned long) id);
    clock_gettime(CLOCK_MONOTONIC, &end);
    end1 = end.tv_sec + (end.tv_nsec / 1e9);
    if(policy==SCHED_FIFO){
        elapsed = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);
        totalTime = totalTime + elapsed;
        printf("Time taken thread 1 is: %.6f seconds\n", elapsed);
    }else{
        printf("End time thread 1 is: %.6f seconds\n", end1);
    }
    pthread_exit(NULL);
}

void* func2(void* arg) {
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("Start time 2: %lf \n",start.tv_sec + (start.tv_nsec / 1e9));
    for(int i=0;i<delay;i++){

    }
    pthread_t id = pthread_self();
    printf("Second thread id: %lu\n", (unsigned long) id);
    clock_gettime(CLOCK_MONOTONIC, &end);
    end2 = end.tv_sec + (end.tv_nsec / 1e9);
    if(policy==SCHED_FIFO){
        elapsed = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);
        totalTime = totalTime + elapsed;
        printf("Time taken thread 2 is: %.6f seconds\n", elapsed);
    }else{
        printf("End time thread 2 is: %.6f seconds\n", end2);
    }
    pthread_exit(NULL);
}

void* func3(void* arg) {
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("Start time 3: %lf \n",start.tv_sec + (start.tv_nsec / 1e9));
    for(int i=0;i<delay;i++){

    }
    pthread_t id = pthread_self();
    printf("Third thread id: %lu\n", (unsigned long) id);
    clock_gettime(CLOCK_MONOTONIC, &end);
    end3 = end.tv_sec + (end.tv_nsec / 1e9);
    if(policy==SCHED_FIFO){
        elapsed = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);
        totalTime = totalTime + elapsed;
        printf("Time taken thread 3 is: %.6f seconds\n", elapsed);
    }else{
        printf("End time thread 3 is: %.6f seconds\n", end3);
    }
    pthread_exit(NULL);
}

void* func4(void* arg) {
    struct timespec start, end;
    double elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    printf("Start time 4: %lf \n",start.tv_sec + (start.tv_nsec / 1e9));
    for(int i=0;i<delay;i++){

    }
    pthread_t id = pthread_self();
    printf("Fourth thread id: %lu\n", (unsigned long) id);
    clock_gettime(CLOCK_MONOTONIC, &end);
    end4 = end.tv_sec + (end.tv_nsec / 1e9);
    if(policy==SCHED_FIFO){
        elapsed = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);
        totalTime = totalTime + elapsed;
        printf("Time taken thread 4 is: %.6f seconds\n", elapsed);
    }else{
        printf("End time thread 4 is: %.6f seconds\n", end4);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t ptid1, ptid2, ptid3, ptid4;
    char* scheduler = argv[1];

    if (strcmp(scheduler, "rr") == 0) {
        policy = SCHED_RR;
    }else if(strcmp(scheduler, "fifo") == 0){
        policy = SCHED_FIFO;
    }else if (strcmp(scheduler, "other") == 0){
        policy = SCHED_OTHER;
    }else{
        printf("Given scheduling algorithm is invalid \n");
        return 0;
    }
    
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(CORE_ID, &cpuset);

    // Set priorities for each thread
    struct sched_param param1;
    param1.sched_priority = 1;
    sched_setscheduler(ptid1, policy, &param1);

    struct sched_param param2;
    param2.sched_priority = 1; 
    sched_setscheduler(ptid2, policy, &param2);

    struct sched_param param3;
    param3.sched_priority = 1;
    sched_setscheduler(ptid3, policy, &param3);

    struct sched_param param4;
    param4.sched_priority = 1;
    sched_setscheduler(ptid4, policy, &param4);

    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    // Create thread attributes
    pthread_attr_t attr;
    // Initialize with default attributes
    pthread_attr_init(&attr); 
    
    // Create threads and calculate start time
    pthread_create(&ptid1, &attr, &func1, NULL);
    pthread_create(&ptid2, &attr, &func2, NULL);
    pthread_create(&ptid3, &attr, &func3, NULL);
    pthread_create(&ptid4, &attr, &func4, NULL);

    // Setting the cpu for each thread
    pthread_setaffinity_np(ptid1, sizeof(cpu_set_t), &cpuset);
    pthread_setaffinity_np(ptid2, sizeof(cpu_set_t), &cpuset);
    pthread_setaffinity_np(ptid3, sizeof(cpu_set_t), &cpuset);
    pthread_setaffinity_np(ptid4, sizeof(cpu_set_t), &cpuset);

    // Wait for threads to finish and calculate end time
    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);
    pthread_join(ptid3, NULL);
    pthread_join(ptid4, NULL);

    double max = end1;
    if(policy!=SCHED_FIFO){
        if (end2 > max) {
            max = end2;
        }     
        if (end3 > max) {
            max = end3;
        }  
        if (end4 > max) {
            max = end4;
        }
        totalTime = max - start1;
        printf("Did not display time taken per thread because it is not accurate due to execution time of the core of round robin/other algorithm is being alternated between the threads. \n");
    }
    printf("Total time taken: %f \n",totalTime);

    // Clean up thread attributes
    pthread_attr_destroy(&attr);
    
    return 0;
}