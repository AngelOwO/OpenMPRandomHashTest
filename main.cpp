// g++ -std=c++17 -lssl -lcrypto -fopenmp -lpthread main.cpp Timer.cpp -o aaa
#include <iostream>
#include <openssl/sha.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "Timer.h"
#include <sys/time.h>
#include <omp.h>


#define STRING_LENGTH 256
#define SEED_SIZE 256
#define HOW_MANY_TIMES 1000000
#define THREAD_NUM 8


static const char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void generateRandString(char *charArray,int size,unsigned int seed){
    srand(seed);
    for(int i=0;i<size;i++){
        charArray[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
        //printf(" %c",charArray[i]);
    }
}

unsigned char *calHash256(char *randomString,size_t len){
    SHA256_CTX c;
    int statCode;

    statCode = SHA256_Init(&c);
    statCode = SHA256_Update(&c,(void*)randomString,len);
    //unsigned char shaAns[SHA256_DIGEST_LENGTH+1] = {'\0'};
    unsigned char *shaAns = new unsigned char[SHA256_DIGEST_LENGTH+1]();
    memset(shaAns,'\0',SHA256_DIGEST_LENGTH+1);
    statCode = SHA256_Final(shaAns,&c);
    return shaAns;
}


int main(){

    {
    Timer t;
    std::vector<unsigned int> seedVec;

    omp_set_num_threads(THREAD_NUM);
    #pragma omp parallel shared(seedVec)
    {
        //int tid = omp_get_thread_num();
        char *randomString = new char[STRING_LENGTH];
        memset(randomString,'\0',STRING_LENGTH);
        #pragma omp for
        for(int i=0;i<HOW_MANY_TIMES/THREAD_NUM;i++){
            unsigned int seedTemp;
            #pragma omp critical
            {
                if(seedVec.empty()==true){
                    char seed[SEED_SIZE];
                    for(int i=0;i<SEED_SIZE;i++){
                        seed[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
                        seedVec.push_back((unsigned int)seed[i]);
                    }
                }
                seedTemp = seedVec.back();
                seedVec.pop_back();
            }
            generateRandString(randomString,STRING_LENGTH,seedTemp);

            unsigned char *ansStr = calHash256(randomString,STRING_LENGTH);
            //#pragma omp critical
            //{
            //    printf("tid = %d, ",tid);
            //    for(int x=0;x<SHA256_DIGEST_LENGTH;x++){
            //        printf("%x ",ansStr[x]);
            //    }
            //    printf("\n");
            //}
            delete[](ansStr);
        }
        delete[](randomString);
    }
    }
    return 0;
}