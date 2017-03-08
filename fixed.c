//sayang to linis pa naman ahu huhuhuuuhhuuHUHUHUH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
  char sbox[4][4][4];

  int sbox_sequence[4];
  int ip[16];
  int ip_inverse[16];
  int expand[16];
  int pbox[8];
  int key_permutation[4][16];
  char plaintext[16];
  char key[12];
  char old_right[8];
  char old_left[8];
  char new_left[8];
  char new_right[8];
} Des;

void setup_des(Des *);
void change_sequence(Des *);
void change_pbox(Des *);
void change_ip(Des *);
void change_ip_inverse(Des *);
void permute(Des *);
void set_key(Des *);
void set_plaintext(Des *);
void get_input();
void copy(int [], int[], int, int);
int main(){
  Des *small_des = (Des *) malloc(sizeof(Des)) ;

  setup_des(small_des);
  int i = 0;
  printf("%s\n",small_des->plaintext );
  // small_des->ip[0] = 10;

  return 0;
};
void setup_des(Des *small_des){
  strcpy(small_des -> plaintext, "1000110010000000");
  strcpy(small_des -> key, "111000110000");
  int sbox_sequence[4] = {1,2,3,4};
  int ip[16] = {10, 3, 4, 5, 9, 11, 13, 1, 6, 16, 2, 14, 8, 15, 7, 12};
  int ip_inverse[16] = {8, 11, 2, 3, 4, 9, 15, 13, 5, 1, 6, 16, 7, 12, 14, 10};
  int expand[16] = {8, 1, 2, 3, 2, 3, 4, 5, 4, 5, 6, 7, 6, 7, 8, 1};
  int pbox[8] = {3, 5, 8, 6, 2, 4, 1, 7};
  char sbox[4][4][4][2] = {
   {
     {"00", "00", "01", "01"},
     {"10", "10", "11", "11"},
     {"00", "00", "01", "01"},
     {"10", "10", "11", "11"}
   },
   {
     {"00", "00", "00", "00"},
     {"10", "10", "10", "10"},
     {"01", "01", "01", "01"},
     {"11", "10", "11", "11"},
   },
   {
     {"00", "10", "01", "11"},
     {"00", "10", "01", "11"},
     {"00", "10", "01", "11"},
     {"00", "10", "01", "11"}
   },
   {
     {"00", "10", "01", "11"},
     {"00", "01", "10", "11"},
     {"00", "01", "10", "11"},
     {"00", "01", "10", "11"},
   }
  };
  for (int i; i<4;i++){
    for (int j; j<4; j++){
      for int k; k<4; k++
    };
  };
};


void copy(int data[], int copy[], int index, int copysize){
    int counter;
    for (counter = 0; counter < copysize; counter++){
      copy[counter] = data[index+counter];
    };
};
