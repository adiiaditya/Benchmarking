//
//  Disk_Benchmark.c
//  
//
//  Created by Aditya on 10/02/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

void SequentialRead(void *numOfBytes){
    int size = (long)numOfBytes;
    int i;
    //Open a file
    FILE *fp = fopen("sample_sequential.rtf", "r");
    
    char *buffer = (char *)malloc(sizeof(char)*size);
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i< 100000/size; i++) {
        fread(buffer, size, 1, fp);
    }
    
    fclose(fp);
    free(buffer);
}

void RandomRead(void *numOfBytes){
    int size = (long)numOfBytes;
    int i;
    //Open a file
    FILE *fp = fopen("sample_random.rtf", "r");

    char *buffer = (char *)malloc(sizeof(char)*size);
    int pos = rand();
    fseek(fp, pos, SEEK_SET);

    for (i = 0; i< 100000/size; i++) {
        fread(buffer, size, 1, fp);
    }
    
    fclose(fp);
    free(buffer);
}

void SequentialWrite(void *numOfBytes){
    int size = (long)numOfBytes;
    int i;
    //Open a file
    FILE *fp = fopen("sample_sequential.rtf", "w");
 
    char *buffer = (char *)malloc(sizeof(char)*size);
    fseek(fp, 0, SEEK_SET);
    for (i = 0; i< 100000/size; i++) {
        fwrite(buffer, size, 1, fp);
    }
    
    fclose(fp);
    free(buffer);
}

void RandomWrite(void *numOfBytes){
    int size = (long)numOfBytes;
    int i;
    //Open a file
    FILE *fp = fopen("sample_random.rtf", "w");
    char *buffer = (char *)malloc(sizeof(char)*size);
    int pos = rand();
    fseek(fp, pos, SEEK_SET);
    for (i = 0; i< 100000/size; i++) {
        fwrite(buffer, size, 1, fp);
    }
    
    fclose(fp);
    free(buffer);
    
}

int main(){
    
    int numberOfThreads,i,j,numOfBytes;
    double time;
    double latency, throughput;
    struct timeval startTime, stopTime;
    
    for(numberOfThreads=1; numberOfThreads<=2; numberOfThreads++){ // number of threads:1 and 2
        
        //Defines a Thread
        pthread_t thread[numberOfThreads];
        
        
        //****** SEQUENTIAL WRITE ******//
        for(j=0; j<3; j++){ //1 byte, 1024 bytes and 1048576 bytes
            numOfBytes = pow(1024,(double)j);
            
            //Clock starts
            gettimeofday(&startTime, NULL);
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_create(&thread[i], NULL, SequentialWrite, numOfBytes);
            }
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_join(thread[i], NULL);
            }
            
            //Clock Stops
            gettimeofday(&stopTime, NULL);
            
            //time in second
            time = ((stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0));
            latency = (time)*1000.0; // in millisecond
            throughput = (numberOfThreads*numOfBytes/(1024.0*1024.0*time)); //MB/sec
            printf("For sequential write %10d bytes, with %d thread(s), the throughput: %10f MB/sec and the latency: %10f ms\n", numOfBytes, numberOfThreads , throughput, latency);
        }

        
        //****** SEQUENTIAL READ ******//
        for(j=0; j<3; j++){ //1 byte, 1024 bytes and 1048576 bytes
            numOfBytes = pow(1024,(double)j);
            
            //Clock starts
            gettimeofday(&startTime, NULL);
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_create(&thread[i], NULL, SequentialRead, numOfBytes);
            }
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_join(thread[i], NULL);
            }
            
            //Clock Stops
            gettimeofday(&stopTime, NULL);
            
            //time in second
            time = ((stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0));
            latency = (time)*1000.0; // in millisecond
            throughput = (numberOfThreads*numOfBytes/(1024.0*1024.0*time)); //MB/sec
            printf("For sequential read %10d bytes, with %d thread(s), the throughput: %10f MB/sec and the latency: %10f ms\n", numOfBytes, numberOfThreads, throughput, latency);
        }
        
        
        //****** RANDOM WRITE ******//
        for(j=0; j<3; j++){ //1 byte, 1024 bytes and 1048576 bytes
            numOfBytes = pow(1024,(double)j);
            
            //Clock starts
            gettimeofday(&startTime, NULL);
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_create(&thread[i], NULL, RandomWrite, numOfBytes);
            }
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_join(thread[i], NULL);
            }
            
            //Clock Stops
            gettimeofday(&stopTime, NULL);
            
            //time in second
            time = ((stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0));
            latency = (time)*1000.0; // in millisecond
            throughput = (numberOfThreads*numOfBytes/(1024.0*1024.0*time)); //MB/sec
            printf("For random write %10d bytes, with %d thread(s), the throughput: %10f MB/sec and the latency: %10f ms\n", numOfBytes, numberOfThreads , throughput, latency);
        }
        
        //****** RANDOM READ ******//
        for(j=0; j<3; j++){ //1 byte, 1024 bytes and 1048576 bytes
            numOfBytes = pow(1024,(double)j);
            
            //Clock starts
            gettimeofday(&startTime, NULL);
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_create(&thread[i], NULL, RandomRead, numOfBytes);
            }
            
            for(i = 0; i <= numberOfThreads; i++){
                pthread_join(thread[i], NULL);
            }
            
            //Clock Stops
            gettimeofday(&stopTime, NULL);
            
            //time in second
            time = ((stopTime.tv_sec - startTime.tv_sec) + ((stopTime.tv_usec - startTime.tv_usec)/1000000.0));
            latency = (time)*1000.0; // in millisecond
            throughput = (numberOfThreads*numOfBytes/(1024.0*1024.0*time)); //MB/sec
            printf("For random read %10d bytes, with %d thread(s), the throughput: %10f MB/sec and the latency: %10f ms\n", numOfBytes, numberOfThreads , throughput, latency);
        }
    }
}