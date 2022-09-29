#ifndef MACRO_H
#define MACRO_H

#define SHARED_MEM_KEY 2233
#define MAX_LEN 1000

struct data {
    int writen;
    char msg[MAX_LEN];
};

#endif