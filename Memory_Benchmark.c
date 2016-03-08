//
//  Memory_Benchmark.c
//  
//
//  Created by Aditya on 08/02/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

void SequentialAccess(void *numOfBytes){
    int size = (long)numOfBytes;
    int numOfLoops = 100000000;
    int i;
    char * sourceBlock = (char *)malloc(sizeof(char)*numOfLoops);
    char * destinationBlock = (char *)malloc(sizeof(char)*numOfLoops);
    
    for (i = 0; i< numOfLoops/size; i++) {
        memcpy(destinationBlock, sourceBlock, size);
    }
    free(sourceBlock);
    free(destinationBlock);

}

void RandomAccess(void *numOfBytes){
    int size = (long)numOfBytes;
    int numOfLoops = 100000000;
    int i;
    char * sourceBlock = (char *)malloc(sizeof(char)*numOfLoops);
    char * destinationBlock = (char *)malloc(sizeof(char)*numOfLoops);
    
    for (i = 0; i< numOfLoops/size; i++) {
        int index = rand()%numOfLoops;
        memcpy(destinationBlock+index, sourceBlock+index, size);
    }
    free(sourceBlock);
    free(destinationBlock);

}


int main(){
    
    int numberOfThreads,i,j,numOfBytes;
    double time;
    double latency, throughput;
    struct timeval startTime, stopTime;

    
    for(numberOfThreads=1; numberOfThreads<=2; numberOfThreads++){ // number of threads:1 and 2
        
        
        //****** SEQUENTIAL ACCESS ******//
        for(j=0; j<3; j++){ //1 byte, 1024 bytes and 1048576 bytes
            numOfBytes = pow(1024,(double)j);
            
            //Defines a Sequential Access Thread
            pthread_t threadSequential[numberOfThreads];
            //Clock starts
            gettimeofday(&startTime, NULL);
            
            for(i = 0; i < numberOfThreads; i++){
                pthread_create(&threadSequential[i], NULL, SequentialAccess, numOfBytes);
            }
            
            for(i = 0; i < numberOfThreads; i++){
                pthread_join(threadSequential[i], NULL);
            }
            
            //Clock Stops
            gettimeofday(&stopTime, NULL);
            
            //time in second
            time = ((stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0));
            latency = time*1000.0; // in millisecond
            throughput = (numberOfThreads*numOfBytes/ (1024.0*1024.0*time)); //MB/sec
            printf("For sequential access %10d bytes, with %d thread(s), the throughput: %10f MB/sec and the latency: %10f ms\n", numOfBytes, numberOfThreads , throughput, latency);
        }
        
        
        //****** RANDOM ACCESS ******//
        for(j=0; j<3; j++){ //1 byte, 1024 bytes and 1048576 bytes
            numOfBytes = pow(1024,(double)j);
            
            //Defines a Random Access Thread
            pthread_t threadRandom[numberOfThreads];
            //Clock starts
            gettimeofday(&startTime, NULL);
            
            for(i = 0; i < numberOfThreads; i++){
                pthread_create(&threadRandom[i], NULL, RandomAccess, numOfBytes);
            }
            
            for(i = 0; i < numberOfThreads; i++){
                pthread_join(threadRandom[i], NULL);
            }
            
            //Clock Stops
            gettimeofday(&stopTime, NULL);
            
            //time in second
            time = ((stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0));
            latency = time*1000.0; // in millisecond
            throughput = (numberOfThreads*numOfBytes/ (1024.0*1024.0*time)); //MB/sec
            printf("For random access %10d bytes, with %d thread(s), the throughput: %10f MB/sec and the latency: %10f ms\n", numOfBytes, numberOfThreads , throughput, latency);
        }

    }
        







}
