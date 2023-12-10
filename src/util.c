#include "util.h"

FILE* open_file(const char* fname) {
    FILE* f = NULL;
    f = fopen(fname, "r");
    return f;
}

long size_of_file(FILE* f) {
    long l;
    fseek(f, 0, SEEK_END);
    l = ftell(f);
    fseek(f, 0, SEEK_SET);

    return l;
}

config_t* read_config(const char* fname) {
    config_t* c = (config_t*) calloc(1, sizeof(config_t));
    if (!c) {
        fprintf(stderr, "Failed to allocate memory for config_t*\n");
        exit(EXIT_FAILURE);
    }

    if ( (c->f = open_file(fname)) ) {
        c->fname = fname;
        c->fsize = size_of_file(c->f);
        c->fbuf = malloc(c->fsize + 1);

        if (c->fbuf) {
            fread(c->fbuf, 1, c->fsize, c->f);
            c->fbuf[c->fsize] = '\0';
        }
        return c;
    } else {
        return NULL;
    }
}
