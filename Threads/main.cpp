#include <pthread.h>
#include <iostream>
using namespace std;

#ifndef c
#define c (5)
#endif

#ifndef x
#define x (3)
#endif


int a[x][x];
int b[x][x];
int temp[x] = {0};

void fillMatrix(int matrix[x][x]){
    for (int i = 0; i < x; i++){
        for (int j = 0; j < x; j++){
            //matrix[i][j]=1;
            cin>>matrix[i][j];
        }
    }
}

void* multiply(void* arg) {
    int num = *((int*)arg);

    for (int i = num; i < x; i += c) {
        for (int j = 0; j < x; j++) {
            for (int k = 0; k < x; k++) {
                temp[j] += a[i][k] * b[k][j];
            }
        }

        for(int r = 0; r < x; r++){
            a[i][r] = temp[r];
            temp[r] = 0;
        }
    }

    pthread_exit(NULL);
}

int main() {
    cout<<"В ведите квадратную матрицу а размером "<<x<<endl;
    fillMatrix(a);
    cout<<"В ведите квадратную матрицу b размером "<<x<<endl;
    fillMatrix(b);

    pthread_t threads[x];
    int thread_args[x];

    for (int i = 0; i < x; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, multiply, &thread_args[i]);
    }

    for (int i = 0; i < x; i++) {
        pthread_join(threads[i], NULL);
    }

    cout<<"Matrix a*b:\n";
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            cout<<" "<<a[i][j];
        }
        cout<<("\n");
    }

    return 0;
}