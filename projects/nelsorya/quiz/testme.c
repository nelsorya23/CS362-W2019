#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
   
    //generate random characters between the space character and right bracket character
    int maxVal = 125; 
    int minVal = 32;
    return (rand() % (maxVal - minVal + 1)) + minVal;
}

char *inputString()
{
    // TODO: rewrite this function
    
    int maxVal = 116;
    int minVal = 101;
    const int strLen = 6;
    char* str = (char*) malloc((sizeof(char))*strLen);

    int i;
    for(i = 0; i < strLen; i++)
    {
       //gen random chars between e and t
       if(i < 5)
       {
          str[i] = (rand() % (maxVal - minVal + 1)) + minVal;
       }
       //last position in array, gen random chars between NULL and STX chars
       else
       {
          str[i] = (rand() % ((maxVal - 114) - (minVal - 101) + 1)) + (minVal - 101);
       }
    }
    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
