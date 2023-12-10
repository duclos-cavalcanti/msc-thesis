#ifndef __MAIN__H
#define __MAIN__H

#include <stdio.h>
#include <stdlib.h>
#include <lxc/lxccontainer.h>
#include <lxc/attach_options.h>

typedef struct config {
    FILE* f;
    char *fname; 
    long  fsize;
    char* fbuf;
} config_t;

typedef struct container {
    struct lxc_container *c;

    void (*exit)(struct container*);
    struct container* next;
} container_t;

typedef struct agent {
    container_t* c_list;

    void (*exit)(void);
} agent_t;


extern agent_t* agent;

#endif /* __MAIN__H */
