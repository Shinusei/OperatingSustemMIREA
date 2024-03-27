#include <pthread.h>
#include <stdio.h>
#include <iostream>

#ifndef C
#define C (500000)
#endif

#ifndef X
#define X (2)
#endif

int mat1[X][X];
int mat2[X][X];
int step_i = 0;

using namespace std;

void* multi(void* arg)
{
    int i = step_i++; //i denotes row number of resultant matC
    int res=0;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < X; j++) {
            for (int k = 0; k < X; k++) {
                res += mat1[i][k] * mat2[k][j];
            }
            mat1[i][j] = res;
         }
    }
    return NULL;
}

int main(){
    for(int i=0; i<X; i++){
        for(int j=0; j<X; j++){
            mat1[i][j] = 1;
            mat2[i][j] = 1;
        }
    }
    pthread_t threads;
 
    for (int i = 0; i < C; i++) {
        pthread_create(&threads, NULL, multi, NULL);
    }
 
    // joining and waiting for all threads to complete
    for (int i = 0; i < C; i++) 
        pthread_join(threads, NULL);    
 
    // Displaying the result matrix
    cout << endl
         << "Multiplication of A and B" << endl;
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < X; j++) 
            cout << mat1[i][j] << " ";        
        cout << endl;
    }
    return 0;
}