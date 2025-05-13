#include<pthread.h>
#include<iostream>
#include<cstdlib>

using namespace std;

int size = 0;

void* average(void* input){
    int* numbers = ((int *)input);
    int sum = 0;
    int average = 0;
    for(int i =0;i<size;i++){
        sum = sum + numbers[i];
    }
    
    average = sum / size;
    cout << "The average value is " << average << endl;
        pthread_exit(0);
    
}

void* minimum(void* input){
    int* numbers = ((int *)input);
    int min = numbers[0];
    for(int i=1;i<size;i++){
        if(min > numbers[i]){
            min = numbers[i];
        }
    }
     
    cout << "The minimum value is " << min << endl;
    pthread_exit(0);
}

void* maximum(void* input){
    int* numbers = ((int *)input);
    int max = numbers[0];
    for(int i=1;i<size;i++){
        if(max < numbers[i]){
            max = numbers[i];
        }
    }
     
    cout << "The maximum value is " << max << endl;
    
     pthread_exit(0);
}

int main(int argc, char*argv[]){    
    if(argc < 2){
        cout << "Error "<< endl;
        return 1;
    }
    pthread_t threadID[3];
        
    int numbers[argc - 1];
    
    size = argc - 1;
    
    for(int i = 0; i < (argc - 1);i++){
        numbers[i] = atoi(argv[i+1]);
    }

    pthread_create(&threadID[0],NULL,average,&numbers);
    pthread_join(threadID[0],NULL);
    pthread_create(&threadID[1],NULL,minimum,&numbers);
    pthread_join(threadID[1],NULL);
    pthread_create(&threadID[2],NULL,maximum,&numbers);
    pthread_join(threadID[2],NULL);
        
    return 0;
}
