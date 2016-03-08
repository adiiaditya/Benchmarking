//
//  CPU_Benchmark.c
//  
//
//  Created by Aditya on 01/02/16.
//
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>


//Default Values
long numberOfLoops = 1000000000;
double pi = 3.14159;

//Number of float operations
void* FLOPS(){
    int i;
    double result = 0.0;
    for(i = 0; i < numberOfLoops; i++){
        result = pi*i; //Operation = 1
        result *= pi*pi+i*i; //Operation = 4
        result *= pi*pi*pi*pi+i*i*i*i; //Operation = 8
        result *= pi*pi*pi*pi*pi+i*i*i*i*i; //Operation = 10
     }
}


//Number of integer operations
void* IOPS(){
    int i;
    int result = 0;
    for(i=0; i<numberOfLoops; i++){
        result = i*i; //Operation = 1
        result *= i*i+i*i; //Operation = 4
        result *= i*i*i*i+i*i*i*i; //Operation = 8
        result *= i*i*i*i*i+i*i*i*i*i; //Operation = 10
    }
}

int main()
{
    int i,j;
    double time;
    struct timeval startTime, stopTime;
    
    int numberOfThreads[3] = {1,2,4};
    
    for(i=0; i<=2; i++){ // number of threads:1, 2 and 4
        
    long numberOfOperations =  numberOfThreads[i]*numberOfLoops*23;
    pthread_t thread[numberOfThreads[i]];
    
    //****** FLOPS ******//
        printf("\n****** FLOPS ******");
    //Clock starts
    gettimeofday(&startTime, NULL);
    
    for(j = 0; j <= numberOfThreads[i]; j++){
        pthread_create(&thread[j], NULL, FLOPS, NULL);
    }
    
    for(j = 0; j <= numberOfThreads[i]; j++){
        pthread_join(thread[j], NULL);
    }
    
    //Clock Stops
    gettimeofday(&stopTime, NULL);
    
    time = (stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0);
    double flops = ((double)numberOfOperations/time)/1e9;
    printf("\nFor %d threads, execution time is %10f s and the GFLOPS is %10f\n", numberOfThreads[i], time, flops);
    
    
    //****** IOPS ******//
        printf("\n****** IOPS ******");
    //Clock starts
    gettimeofday(&startTime, NULL);
    
    for(j = 0; j <= numberOfThreads[i]; j++){
        pthread_create(&thread[i], NULL, IOPS, NULL);
    }
    
    for(j = 0; j <= numberOfThreads[i]; j++){
        pthread_join(thread[i], NULL);
    }
    
    //Clock Stops
    gettimeofday(&stopTime, NULL);
    
    time = (stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0);
    double iops = ((double)numberOfOperations/time)/1e9;
    printf("\nFor %d threads, execution time is %10f s and the GIOPS is %10f\n", numberOfThreads[i], time, iops);
    
  }
}
