#include<stdio.h>
#include <stdlib.h>
#include "switchto.h"

struct ctx_s ctx_ping; 
struct ctx_s ctx_pong; 
struct ctx_s ctx_pung; 

void f_ping(void *arg);
void f_pong(void *arg);
void f_pung(void *arg);
int main(int argc, char *argv[])
{
  init_ctx(&ctx_ping, 16384, f_ping, NULL);
  init_ctx(&ctx_pong, 16384, f_pong, NULL);
  init_ctx(&ctx_pung, 16384, f_pung, NULL);	
  switch_to_ctx(&ctx_ping);
  
  exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
  while(1) {
    printf("A") ;
    switch_to_ctx(&ctx_pong);
    printf("B") ;
    switch_to_ctx(&ctx_pong);
    printf("C") ;
    switch_to_ctx(&ctx_pong);
  }
}

void f_pong(void *args)
{
  while(1) {
    printf("1") ;
    switch_to_ctx(&ctx_pung);
    printf("2") ;
    switch_to_ctx(&ctx_pung);
  }
} 

void f_pung(void *args)
{
  while(1) {
    printf("*alpha*") ;
    switch_to_ctx(&ctx_ping);
    printf("*beta*") ;
    switch_to_ctx(&ctx_ping);
  }
}  
