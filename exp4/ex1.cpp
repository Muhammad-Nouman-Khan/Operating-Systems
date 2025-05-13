#include<pthread.h>
#include<iostream>
#include<cstdlib>

using namespace std;

int threadNumber = -1;

void* fibonacciGenerator(void* input){

    int limit = *((int * ) input);
   
    int a = 0;
    int b = 1;
    int c;
    
    cout << "Thread "  << ++threadNumber << " : " << a << " , " << b ;
    
    while(1){
        c = a + b;
        if(c > limit){
            break;
        }
        
        cout << " , " << c ;
        a = b;
        b = c;
    }
    cout << endl;
    pthread_exit(0);
}

int main(int argc, char*argv[]){    
    if(argc < 2){
        cout << "Error "<< endl;
        return 1;
    }
    pthread_t threadID[argc - 1];
    
    for(int i = 0;i<(argc-1);i++){
        int limit = atoi(argv[i+1]);
        pthread_create(&threadID[i],NULL,fibonacciGenerator,&limit);
        pthread_join(threadID[i],NULL);
    }

    return 0;
}
