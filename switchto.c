#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "switchto.h"

struct ctx_s* current_ctx = NULL;

int init_ctx(struct ctx_s *ctx, int stack_size, func_t* f, void *args){
  ctx->ctx_stack = malloc(stack_size);
  if(ctx->ctx_stack == NULL)
    return 0;
  ctx->ctx_state = CTX_READY;
  ctx->ctx_f = f;
  ctx->ctx_args = args;
  ctx->magic = MAGIC;
  ctx->ctx_esp = &ctx->ctx_stack[stack_size-4];
  ctx->ctx_ebp = &ctx->ctx_stack[stack_size-4];
  return 1;
}

void switch_to_ctx(struct ctx_s *ctx){
  assert(ctx != NULL);
  assert(ctx->magic == MAGIC);
  assert(ctx->ctx_state != CTX_TERMINATED);
  if(current_ctx != NULL){
    asm("movl %%esp, %0"
	:"=r" (current_ctx->ctx_esp));
    asm("movl %%ebp, %0"
	:"=r" (current_ctx->ctx_ebp));
  }
  current_ctx = ctx;
  asm("movl %0, %%ebp"
      ::"r" (current_ctx->ctx_ebp));
  asm("movl %0, %%esp"
      ::"r" (current_ctx->ctx_esp));
  if(current_ctx->ctx_state == CTX_READY)
    exec_f(current_ctx);
}

void exec_f(struct ctx_s *ctx){
  ctx->ctx_state = CTX_ACTIVATED;
  ctx->ctx_f(ctx->ctx_args);
  printf("--");
  while(1);
}
