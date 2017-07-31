#ifndef _INCLUDE_ERL_C_NODE_H
#define _INCLUDE_ERL_C_NODE_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "erl_interface.h"
#include "ei.h"


#define BUFSIZE 1000

static ETERM *foo();
static ETERM *bar();
static ETERM *baz();
static ETERM *quax();

const static struct _fnames {
  const char *name;
  ETERM *(*func)(void);
} fns[] = {
  { "foo", foo },
  { "bar", bar },
  { "baz", baz },
  { "quax", quax }
};

typedef struct _thread_data_t {
  int fd;
  int idx;
  char *node;
} thread_data_t;

static int my_listen(int);
static short int get_fn_idx(char *);
static void *message_read_loop(void *);

extern struct ErlNodeConfig;

#endif /* _INCLUDE_ERL_C_NODE_H */
