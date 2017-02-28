/*
Sample
Input: 1000110010000000 key: 111000110000
ciphertext: 0101110001001100
Input: 1100110010011001 key: 111100110100
ciphertext:1111110011000011
Input: 1111000011110000 key: 111100110101
ciphertext: 1111100101110001
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void getInput(){

  // key={};
};

void Permute(int PermutationTable[], int Data[], int PermutatedData[], int arraysize){
  int counter;
  for (counter = 0; counter < arraysize; counter++){
      int index  = PermutationTable[counter] - 1;
      PermutatedData[counter] = Data[index];
    };
};

void PrintARRAY( int array[], int arraysize){
  int counter;
  for (counter = 0;  counter < 16; counter++){
    printf("%d ", array[counter]);
  };
};

void EXOR (int op1[], int op2[], int resultant[], int arraysize){
  int counter;
  for (counter = 0; counter < arraysize; counter++){
    resultant[counter] = (op1[counter] != op2[counter])? 1:0;
  };
};
int main(){
  int ciphertext[16];
  int plaintext[16] = {1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0};
  int key[12] = {1,1,1,0,0,0,1,1,0,0,0,0};
  PrintARRAY(plaintext, 16);

  //getInput(plaintext);
  int InitialPermutation[16] = {10, 3, 4, 5, 9, 11, 13, 1, 6, 16, 2, 14, 8, 15, 7, 12};
  int FinalPermutation[16] = {8, 11, 2, 3, 4, 9, 15, 13, 5, 1, 6, 16, 7, 12, 14, 10};
  int Pbox[8] = {3, 5, 8, 6, 2, 4, 1, 7};


  Permute(InitialPermutation, plaintext, ciphertext, 16);
  puts("\n");
  PrintARRAY(ciphertext, 16);
  int exortest[16];
  EXOR(plaintext,ciphertext,exortest,16);
  puts("\n");
  PrintARRAY(exortest, 16);

  int keyPermutation[4][16]= {
    {1, 2, 3, 1, 4, 5, 6, 2, 7, 8, 9, 3, 10, 11, 12, 4},
    {1, 2, 3, 2, 4, 5, 6, 4, 7, 8, 9, 6, 10, 11, 12, 8},
    {1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12},
    {1, 2, 3, 4, 4, 5, 6, 8, 7 ,8, 9, 12, 10, 11, 12, 4}
  };
  int Sbox[4][4][4] = {
    {
      {0, 1, 2, 3 },
      {4, 5, 6, 7 },
      {8, 9, 10, 11 },
      {12, 13, 14, 15}
    },
    {
      {0, 8, 1, 9 },
      {4, 12, 3, 12 },
      {2, 10, 10, 11 },
      {6, 12, 7, 15 },
    },
    {
      {0, 4, 2, 6 },
      {1, 5, 3, 7 },
      {8, 12, 10, 14 },
      {9, 13, 11, 15 }
    },
    {
      {0, 4, 2, 6},
      {8, 10, 12, 14},
      {1, 3, 5, 7},
      {9, 11, 13, 15 },

    }
  };
  int oldRight[8], oldLeft[8], newRight[8], newLeft[8];



  return 0;
}
