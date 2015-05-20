#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* fromHex(char hexInput, int *decPtr)
{
  char *bin;
  switch(hexInput) {
    case '0':
      bin = "0000"; 
      *decPtr = 0;
      break;
    case '1':
      bin = "0001"; 
      *decPtr = 1;
      break;
    case '2':
      bin = "0010"; 
      *decPtr = 2;
      break;
    case '3':
      bin = "0011"; 
      *decPtr = 3;
      break;
    case '4':
      bin = "0100"; 
      *decPtr = 4;
      break;
    case '5':
      bin = "0101"; 
      *decPtr = 5;
      break;
    case '6':
      bin = "0110"; 
      *decPtr = 6;
      break;
    case '7':
      bin = "0111"; 
      *decPtr = 7;
      break;
    case '8':
      bin = "1000"; 
      *decPtr = 8;
      break;
    case '9':
      bin = "1001"; 
      *decPtr = 9;
      break;
    case 'A':
      bin = "1010"; 
      *decPtr = 10;
      break;
    case 'B':
      bin = "1011"; 
      *decPtr = 11;
      break;
    case 'C':
      bin = "1100"; 
      *decPtr = 12;
      break;
    case 'D':
      bin = "1101"; 
      *decPtr = 13;
      break;
    case 'E':
      bin = "1110"; 
      *decPtr = 14;
      break;
    case 'F':
      bin = "1111"; 
      *decPtr = 15;
      break;
    default:
      bin = "";
      *decPtr = 0;
  }
  return bin;
}

int main()
{
  char nextLine[80];
  int decPtr;
  char tmpIn;
  char *tmpOut;

  while(fgets(nextLine, sizeof(nextLine), stdin)) {
    if(nextLine[0] == 'Q')
      break;
    int i; 
    int len = strlen(nextLine);
    for(i=0; i<len-1; i++) {
      tmpIn = toupper(nextLine[i]); 
      tmpOut = fromHex(tmpIn, &decPtr);
      printf("Dec: %d\tHex: %c\tBin: %s\n", decPtr, tmpIn, tmpOut); 
    }
  }

  return 0;
}
