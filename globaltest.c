#include <stdio.h>

int a = 5;
void change();
int main(){
  a = 6;
  change();
  printf("%d",a);
  return 0;
}

void change(){
  a = 7;
}
