#ifndef _SWITCH_TO_H
#define _SWITCH_TO_H

typedef void (func_t) (void*);
#define MAGIC 0xDEADBEEF

enum ctx_state_e {CTX_READY, CTX_ACTIVATED, CTX_TERMINATED};
struct ctx_s {
  enum ctx_state_e ctx_state;
  func_t* ctx_f;
  void* ctx_args;
  void* ctx_esp;
  void* ctx_ebp;
  unsigned char* ctx_stack;
  unsigned int magic;
};

int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args);
void switch_to_ctx(struct ctx_s *ctx) ;
void exec_f(struct ctx_s *ctx);
#endif
