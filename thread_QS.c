#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#define size 1000 
#define threadSize 10  
int a[size];
int sum[10] = { 0 }; 
int part = 0;  
void* sumArray(void* arg) {  
    int thread_part = part++;
    for (int i = thread_part * (size / 10); i < (thread_part + 1) * (size / 10); i++) 
        sum[thread_part] += a[i]; 
} 
int main() {
    for(int i=0;i<1000;i++){
	a[i]=i+1;
    }
    pthread_t threads[threadSize]; 
    for (int i = 0; i < threadSize; i++) 
        pthread_create(&threads[i], NULL, sumArray, (void*)NULL); 
    for (int i = 0; i < threadSize; i++) 
        pthread_join(threads[i], NULL); 
    int total_sum = 0; 
    for (int i = 0; i < threadSize; i++) 
        total_sum += sum[i];   
    printf("Sum of threads = %d",&total_sum);   
    return 0; 
} 
