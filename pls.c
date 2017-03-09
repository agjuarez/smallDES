#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#define FEISTEL_ROUNDS 4

/*
to do:
sbox sequence
bruteforce
file reading
*/

void change_ip(int *, int*, int, int);
void change_sequence(int *);
void change_pbox(int *, int, int);

void small_des(char*, char*,char *, int*);
void permute(int*, char *, char *, int);
void xor(char *,char*, char*);
void feistel(char *, char *, int*);
void sbox(char*, char*);


int main(){
  // clock_t start =  clock();
  // input1
  char plaintext[17] = "1000110010000000";
  char key[17] = "111000110000";
  // input2
  // char plaintext[17] = "1100110010011001";
  // char key[17] = "111100110100";
  // input3
  // char plaintext[17] = "1111000011110000";
  // char key[17] = "111100110101";
  char ciphertext[17];
  int config[24];
  ciphertext[16] = '\0';
  // printf("plaintext: %s\n",plaintext );
  small_des(plaintext, key, ciphertext, config);
  const char *output = "0101110001001100";
  if (!(strcmp(output,ciphertext))){
    printf("yes\n");
  }

  int ip[16] = {10, 3, 4, 5, 9, 11, 13, 1, 6, 16, 2, 14, 8, 15, 7, 12};
  int ip_inverse[16] = {8, 11, 2, 3, 4, 9, 15, 13, 5, 1, 6, 16, 7, 12, 14, 10};
  change_ip(ip, ip_inverse, 5, 11 );
  int i;
  for (i = 0; i<16;i++){
    printf("%d ",ip[i] );
  }
  printf("\n" );
  for (i = 0; i<16;i++){
    printf("%d ",ip_inverse[i] );
  }
  // int pbox[4] = {1,2,3,4};
  // change_pbox(pbox,2,1);
  // printf("\n%d %d %d %d\n", pbox[0], pbox[1], pbox[2], pbox[3] );
  // printf("OUTPUT: %s\n", ciphertext);
  // clock_t end = clock();
  // long double time_spent = ((long double) (end - start)) / CLOCKS_PER_SEC;
  // printf("%Le\n",time_spent );

};
/************************************************
              BREAKER FUNCTIONS
**************************************************/
void swap(int *array, int index, int value, int to_swap, int size){
  int counter;
  for (counter = 0; counter < size; counter++){
    if (counter == index) continue;
    array[counter] = (array[counter] == value + 1)? to_swap : array[counter];
  };
}
void change_ip(int *ip,int *ip_inverse, int index, int value){
  int ip_to_swap = ip[index];
  ip[index] = value + 1;
  swap(ip, index, value, ip_to_swap, 16);
  int ip_inverse_to_swap =  ip_inverse[value];
  ip_inverse[value] = index + 1;
  swap(ip_inverse, value, index, ip_inverse_to_swap,16);
  // ip_inverse[value1] = index1 + 1;
  // ip_inverse[value2] = index2 + 1;
};
void change_pbox(int *pbox, int index, int value){
  //int pbox_to_be_swap = pbox[index];
  int to_swap = pbox[index];
  pbox[index] = value + 1;
  swap(pbox, index, value, to_swap, 8);
  // int counter;
  // for (counter = 0; counter < 8; counter++){
  //   if (counter == index) continue;
  //   pbox[counter] = (pbox[counter] == value + 1)? pbox_to_be_swap : pbox[counter];
  // };

};
void change_sequence(int *sequence){};


/************************************************
              SMALL DES FUNCTIONS
**************************************************/
void small_des(char* plaintext, char* key, char* result, int *config){
    int ip[16] = {10, 3, 4, 5, 9, 11, 13, 1, 6, 16, 2, 14, 8, 15, 7, 12};
    int ip_inverse[16] = {8, 11, 2, 3, 4, 9, 15, 13, 5, 1, 6, 16, 7, 12, 14, 10};
    int pbox[8] = {3, 5, 8, 6, 2, 4, 1, 7};
    int key_permutation[4][16]= {
      {1, 2, 3, 1, 4, 5, 6, 2, 7, 8, 9, 3, 10, 11, 12, 4},
      {1, 2, 3, 2, 4, 5, 6, 4, 7, 8, 9, 6, 10, 11, 12, 8},
      {1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12},
      {1, 2, 3, 4, 4, 5, 6, 8, 7 ,8, 9, 12, 10, 11, 12, 4}
    };
    //change stuff using config
    char old_right[9], old_left[9], new_right[9], new_left[9];
    old_right[8]  = '\0';
    old_left[8] = '\0';
    new_right[8] = '\0';
    new_left[8] = '\0';
    char ciphertext[17];
    permute(ip,plaintext,ciphertext,16);

    strncpy(old_left, ciphertext+ 0 , 8);
    strncpy(old_right, ciphertext + 8, 8);
    strcpy(new_left,old_left);
    strcpy(new_right,old_right);

    // printf("permuted plaintext: %s\n",ciphertext);
    // printf("old_left: %s\n",old_left );
    // printf("old_right: %s\n",old_right );
    // printf("new_left: %s\n",new_left );
    // printf("new_right: %s\n",new_right );

    int iteration;
    for (iteration = 0; iteration < FEISTEL_ROUNDS; iteration++ ){
      // printf("--------------------------ITERATION%d START\n",iteration );
      // Li = Ri-1
      strcpy( new_left,old_right);
      char permuted_key[17];
      permute(key_permutation[iteration], key, permuted_key,16);
      // printf("L%d  %s\n",iteration, old_right );
      // printf("permuted key: %s\n", permuted_key);


      // f( R-1 XOR Ki)
      feistel(old_right, permuted_key, pbox);
      // Ri = Li-1 XOR f( R-1 XOR Ki)
      // printf("%s\n%s\n",old_left,old_right );
      xor(old_left, old_right, new_right);

      // printf("R%d = Li-1 XOR f( Ri-1 XOR Ki) %s\n",iteration, new_right );

      strcpy(old_left, new_left);
      strcpy(old_right, new_right);

      // printf("--------------------------ITERATION%d END\n\n",iteration );

    };

    strcpy(ciphertext, new_left);
    strcat(ciphertext, new_right);
    permute(ip_inverse, ciphertext, result, 16);


    // printf("CIPHERTEXT: %s\n",ciphertext );

};

void permute(int *permute_table, char *data,char *permuted_data, int permuted_data_size){
  int counter;
  permuted_data[permuted_data_size] = '\0';
  for(counter = 0; counter < permuted_data_size; counter++){
    int index = permute_table[counter] - 1;
    //printf("%s\n",data[index] );
    permuted_data[counter] = data[index];

  };
};

void xor( char *op1, char* op2, char* dest){
  int counter;
  for(counter = 0; counter< strlen(op1); counter++){
    dest[counter] = (op1[counter] != op2[counter])? '1':'0';
  };
};
void sbox (char *expanded_right, char* old_right){
  char sbox[4][4][4][3] = {
   {
     {"00\0", "00\0", "01\0", "01\0"},
     {"10\0", "10\0", "11\0", "11\0"},
     {"00\0", "00\0", "01\0", "01\0"},
     {"10\0", "10\0", "11\0", "11\0"}
   },
   {
     {"00\0", "00\0", "00\0", "00\0"},
     {"10\0", "10\0", "10\0", "10\0"},
     {"01\0", "01\0", "01\0", "01\0"},
     {"11\0", "10\0", "11\0", "11\0"},
   },
   {
     {"00\0", "10\0", "01\0", "11\0"},
     {"00\0", "10\0", "01\0", "11\0"},
     {"00\0", "10\0", "01\0", "11\0"},
     {"00\0", "10\0", "01\0", "11\0"}
   },
   {
     {"00\0", "10\0", "01\0", "11\0"},
     {"00\0", "01\0", "10\0", "11\0"},
     {"00\0", "01\0", "10\0", "11\0"},
     {"00\0", "01\0", "10\0", "11\0"},
   }
  };
  // don't forget sequnce must be changed
  strcpy(old_right, "");
  int iteration;
  for (iteration = 0; iteration < strlen(expanded_right) - 1; iteration+=4){
    int row = (int)(expanded_right[iteration] - '0') * 2 + (int)(expanded_right[iteration + 3] - '0');
    int column = (int)(expanded_right[iteration + 1] - '0') * 2 + (int)(expanded_right[iteration + 2] - '0');
    strcat(old_right, sbox[iteration/4][row][column]);
  };
  // printf("sbox + inverse expanded bits: %s\n", old_right );
};
void feistel(char *old_right, char* permuted_key, int* pbox ){
  int expand[16] = {8, 1, 2, 3, 2, 3, 4, 5, 4, 5, 6, 7, 6, 7, 8, 1};
  char expanded_right[17];
  permute(expand, old_right, expanded_right, 16);
  // printf("expanded_right: %s\n",expanded_right);
  xor(expanded_right, permuted_key, expanded_right);
  // printf("expanded_right xor key: %s\n",expanded_right);
  sbox(expanded_right, old_right);
  char old_right_copy[9];
  strcpy(old_right_copy, old_right);
  permute(pbox, old_right_copy, old_right, 8);
  // printf("pbox'ed: %s\n", old_right );

};
