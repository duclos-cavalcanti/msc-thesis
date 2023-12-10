#include "main.h"

agent_t* agent = { 0 };
container_t* c = { 0 };

void post(void) {
    container_t* head = agent->c_list;
    while( (head) ) {
        head->exit(head);
        head = head->next;
    }

    free(agent);
    return;
}

int pre(void) {

    return 0;
}

int main(int argc, char* argv[]) {
    struct lxc_container *c;
    int ret = 1;

    /* Setup container struct */
    c = lxc_container_new("apicontainer", NULL);
    if (!c) {
        fprintf(stderr, "Failed to setup lxc_container struct\n");
        goto out;
    }

    if (c->is_defined(c)) {
        fprintf(stderr, "Container already exists\n");
        goto out;
    }

    /* Create the container */
    if (!c->createl(c, "download", NULL, NULL, LXC_CREATE_QUIET,
                    "-d", "ubuntu", "-r", "jammy", "-a", "amd64", NULL)) {
        fprintf(stderr, "Failed to create container rootfs\n");
        goto out;
    }

    /* Start the container */
    if (!c->start(c, 0, NULL)) {
        fprintf(stderr, "Failed to start the container\n");
        goto out;
    }

    /* Query some information */
    printf("Container state: %s\n", c->state(c));
    printf("Container PID: %d\n", c->init_pid(c));

    const char *program = "/bin/ls"; // Replace with the full path to the program inside the container
    const char *const args[] = {program, "-l", NULL}; // Specify the program and its arguments
    ret = c->attach_run_wait(c, NULL, program, args);

    if (ret == -1) {
        fprintf(stderr, "Failed running ls in container\n");
        goto out;
    }
    printf("Container ls command return code: %d\n", ret);

    /* Stop the container */
    if (!c->shutdown(c, 30)) {
        printf("Failed to cleanly shutdown the container, forcing.\n");
        if (!c->stop(c)) {
            fprintf(stderr, "Failed to kill the container.\n");
            goto out;
        }
    }

    /* Destroy the container */
    if (!c->destroy(c)) {
        fprintf(stderr, "Failed to destroy the container.\n");
        goto out;
    }

    ret = 0;
out:
    lxc_container_put(c);
    return ret;
    return 0;
}
