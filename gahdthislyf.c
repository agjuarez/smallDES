/*
Sample
Input: 1000110010000000 key: 111000110000
ciphertext: 0 1 0 1 1 1 0 0 0 1 0 0 1 1 0 0
Input: 1 1 0 0 1 1 0 0 1 0 0 1 1 0 0 1 key: 1 1 1 1 0 0 1 1 0 1 0 0
ciphertext:1 1 1 1 1 1 0 0 1 1 0 0 0 0 1 1
Input: 1111000011110000 key: 111100110101
ciphertext: 1111100101110001
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void Permute(int PermutationTable[], int Data[], int PermutatedData[], int arraysize){
  int counter;
  for (counter = 0; counter < arraysize; counter++){
      int index  = PermutationTable[counter] - 1;
      PermutatedData[counter] = Data[index];

    };
};

void PrintARRAY( int array[], int arraysize){
  int counter;
  for (counter = 0;  counter < arraysize; counter++){
    printf("%d ", array[counter]);
  };
};

void XOR (int op1[], int op2[], int resultant[], int arraysize){
  int counter;
  for (counter = 0; counter < arraysize; counter++){
    resultant[counter] = (op1[counter] != op2[counter])? 1:0;
  };
};

void copy(int Data[], int Copy[], int index, int copysize){
    int counter;
    for (counter = 0; counter < copysize; counter++){
      Copy[counter] = Data[index+counter];
    };
};


void feistel(int newRight[], int key[], int keySize, int expansionTable[], int sbox[][4], int pbox[]){
  printf("\nfeistel f enter:\n oldright\n");
  PrintARRAY(newRight,8);
  int expandedRight[keySize];
  Permute(expansionTable, newRight, expandedRight, keySize);
  printf("\nexpanded\n");
  PrintARRAY(expandedRight,keySize);
  int XOResult[16];
  XOR(expandedRight,key,XOResult, keySize);
  printf("\nxor\n");
  PrintARRAY(XOResult,keySize);
  //sbox +
  //inverse expansion
  int inverseExpandedBits[8];
  int iteration;
  int assignedbits = 0;

  for (iteration = 0; iteration < keySize; iteration += 4){
    //outer bits
    int row =( XOResult[iteration] * 2) + XOResult[iteration + 3];
    // printf("\nrow%d\n",row );
    //inner bits
    int column =( XOResult[iteration + 1] * 2) + XOResult[iteration + 2];
    // printf("column%d\n",column );
    int bit = sbox[row][column];
    // printf("%d\n",bit);
    // firtsbit
    inverseExpandedBits[assignedbits] = bit/10;
    // second bit
    inverseExpandedBits[assignedbits+1]=bit%10;
    assignedbits +=2;
  };
  printf("\ninverse expanded bits:\n" );
  PrintARRAY(inverseExpandedBits,8);

  //pbox
  Permute(pbox, inverseExpandedBits, newRight, 8);
  printf("\npbox:\n");
  PrintARRAY(newRight, 8);
  printf("\nfeistel f exit\n" );


};
int main(){
  int ciphertext[16];
  //int plaintext[16] = {1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0};
  int plaintext[16] = {1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1};
  //int key[12] = {1,1,1,0,0,0,1,1,0,0,0,0};
  int key[12] = {1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0};
  int oldRight[8], oldLeft[8], newRight[8], newLeft[8];
  int InitialPermutation[16] = {10, 3, 4, 5, 9, 11, 13, 1, 6, 16, 2, 14, 8, 15, 7, 12};
  int FinalPermutation[16] = {8, 11, 2, 3, 4, 9, 15, 13, 5, 1, 6, 16, 7, 12, 14, 10};
  int ExpansionPermutation[16] = {8, 1, 2, 3, 2, 3, 4, 5, 4, 5, 6, 7, 6, 7, 8, 1};
  int Pbox[8] = {3, 5, 8, 6, 2, 4, 1, 7};
  int keyPermutation[4][16]= {
    {1, 2, 3, 1, 4, 5, 6, 2, 7, 8, 9, 3, 10, 11, 12, 4},
    {1, 2, 3, 2, 4, 5, 6, 4, 7, 8, 9, 6, 10, 11, 12, 8},
    {1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12},
    {1, 2, 3, 4, 4, 5, 6, 8, 7 ,8, 9, 12, 10, 11, 12, 4}
  };
  int Sbox[4][4][4] = {
    {
      {00, 00, 01, 01},
      {10, 10, 11, 11},
      {00, 00, 01, 01},
      {10, 10, 11, 11}
    },
    {
      {00, 00, 00, 00},
      {10, 10, 10, 10},
      {01, 01, 01, 01},
      {11, 10, 11, 11},
    },
    {
      {00, 10, 01, 11},
      {00, 10, 01, 11},
      {00, 10, 01, 11},
      {00, 10, 01, 11}
    },
    {
      {00, 10, 01, 11},
      {00, 01, 10, 11},
      {00, 01, 10, 11},
      {00, 01, 10, 11},
    }
  };
  printf("plaintext:");
  PrintARRAY(plaintext, 16);
  Permute(InitialPermutation, plaintext, ciphertext, 16);
  printf("\npermutated input:");
  PrintARRAY(ciphertext, 16);
  copy(ciphertext, oldLeft, 0, 8);
  //divide 2 parts
  printf("\nLeft:");
  PrintARRAY(oldLeft,8);
  printf("\nRight:");
  copy(ciphertext, oldRight, 8, 8);
  PrintARRAY(oldRight,8);
  //
  copy(oldLeft, newLeft, 0, 8);
  copy(oldRight, newRight, 0, 8);


  int iteration = 0;
  for (;iteration<4;iteration++){
    printf("\n feistel iteration %d", iteration);

    //li = r-1
    printf("\nold right:\n");
    PrintARRAY(oldRight,8);
    copy(oldRight,newLeft, 0, 8);
    printf("\nnewLeft:\n");
    PrintARRAY(newLeft,8);

    // permutate key
    int permutedKey[16];
    Permute(keyPermutation[iteration], key, permutedKey, 16);
    printf("\npermuted key\n" );
    PrintARRAY(permutedKey,16);

    //feistel f
    feistel(oldRight, permutedKey , 16, ExpansionPermutation, Sbox[iteration], Pbox);
    //xor w oldleft
    printf("\noldLeft:\n");
    PrintARRAY(oldLeft,8);
    XOR(oldLeft, oldRight, newRight, 8);
    printf("\nnew right:\n");
    PrintARRAY(newRight,8);

    copy(newLeft, oldLeft, 0, 8);
    copy(newRight, oldRight, 0, 8);



    //copy old


  }
  printf("\nresult\n");
  printf("newleft\n" );
  PrintARRAY(newLeft,8);
  printf("\nnewright\n" );
  PrintARRAY(newRight,8);
  // int permutedKey[16];
  // Permute(keyPermutation[iteration], key, permutedKey, 16);
  // printf("\npermuted key\n" );
  // PrintARRAY(permutedKey,16);
  // feistel(oldRight, permutedKey , 16, ExpansionPermutation, Sbox[iteration], Pbox, oldLeft);
  //concat
  //inverse ip
  return 0;
}
