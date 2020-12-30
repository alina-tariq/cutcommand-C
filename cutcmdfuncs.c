#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cutcmdfuncs.h"

int ValidArgs(int argc, char *argv[], int MaxAllowed)
{
  /*
  Function: ValidArgs
  Purpose: evaluate if given command line arguments (CLA) are valid
  Return: 0 (true) if valid, 1 (false) if invalid
  Input: argc (number of CLA incl. program name), argv (CLAs), 
        MaxAllowed (max fields allowed to be cut)
  Output: None; see return instead
  */

  int i;    // counter for arguments in argv[]
  int curr; // stores current field number
  int next; // stores field number after curr
  
  // ensures correct number of arguments
  if (argc < 4 || argc > (MaxAllowed + 3))
  {
    return 1;
  }

  // ensures delimiters are a single char long
  for (i = 1; i < 3; i++)
  {
    if (strlen(argv[i]) > 1)
    {
      return 1;
    }
  }

  curr = atoi(argv[3]);
  int lastarg = curr;
  int count = 0;

  while (lastarg != 0)
  {
    lastarg /= 10;
    ++count;
  }

  for (i = 4; i < argc; i++)
  {
    next = atoi(argv[i]);

    if (curr < 1 || next < 1)
    {
      return 1; // invalidates non-numerical fields and fields smaller than 1
    }
    else if (curr > MaxAllowed || next > MaxAllowed)
    {
      return 1; // invalidates fields greater than 100
    }
    else if (next <= curr)
    {
      return 1; // invalidates fields not given in ascending order
    }
    else if (strlen(argv[i - 1]) != count)
    {
      // invalidates case where last arg can bypass atoi even
      // while having a mix of numeric and non-numeric chars
      return 1;
    }
    else if (strlen(argv[i]) != (1 + (int)log10(next)))
    {
      // invalidates arguments that bypass atoi by having a
      // mix of numeric and non-numeric chars
      return 1;
    }

    curr = atoi(argv[i]);
  }

  return 0; // returns true if all test cases are passed
}

void CutCommand(int argc, char *argv[], char *line)
{
  /*
  Function: CutCommand
  Purpose: to tokenize string in stdin using input delimiter and print 
          requested fields separated by output delimiter  
  Return: None; see output instead
  Input: argc (number of CLA incl. program name), argv (CLAs), line (input from stdin)
  Output: field(s) specified in argv for tokenized line separated by output delimiter
  */

  char word[1000];   // holds each word/token in string
  char *fields[100]; // pointer array to each field
  int i = 0;         // to parse through each character in line
  int j = 0;         // counter to walk through word variable
  int k = 0;         // counter for fields pointers array
  int fNum;          // field number to be cut
  int fStart = 3;    // start of field arguments in argv[]
  int highestField;  // highest field number found in line

  while (line[i] != '\0')
  {
    // once input delimiter is encountered, adds null string to end of word
    // and adds word to address at pointer k in fields pointer array
    if (line[i] == *argv[1])
    {
      word[j] = '\0';

      fields[k] = malloc(sizeof(word));
      strcpy(fields[k], word);

      j = 0;
      k++;
      memset(word, 0, sizeof(word)); // resets words variable to be empty
    }
    else
    {
      // adds character from line to word if no input delimiter is encountered
      word[j++] = line[i];
    }
    i++;
  }

  // terminates the last word (or new line char) with null string
  // and adds it as a field
  word[j] = '\0';
  fields[k] = malloc(sizeof(word));
  strcpy(fields[k], word);

  // for case where there's only one field or a blank line
  if (k == 0)
  {
    printf("%s", fields[k]);
  }
  else
  {
    highestField = findHighest(argc, argv, k);
    i = 0; // reassigned to parse through tokens in fields pointer array
    j = 3; // reassigned to go through each field given in arguments
    fNum = atoi(argv[j]) - 1;
    j++;

    if (highestField == 0)
    {
      printf("\n");
    }
    else
    {
      while (i < highestField)
      {
        // if argument field number matches field number of token
        if (i == fNum)
        {
          // if field is the last possible field
          if (i == highestField - 1)
          {
            if (i == k)
            { // doesn't print new line if field was also the last field in input
              printf("%s", fields[i]);
            }
            else
            { // prints a new line if field wasn't the last field in input
              printf("%s\n", fields[i]);
            }
          }
          else
          { // if not last possible field, adds output delimiter next to it
            printf("%s%c", fields[i], *argv[2]);
          }
        }
        i++;

        // if current token field is larger than field argument, goes to next field
        // argument as long as next field argument exists
        if (i > fNum && j < argc)
        {
          fNum = atoi(argv[j]) - 1;
          j++;
        }
      }
    }
  }
}

int findHighest(int argc, char *argv[], int maxTokens)
{
  /*
  Function: findHighest
  Purpose: compares field arguments with number of tokens in line to find 
          largest field number that can exist for input line  
  Return: highest field number from arguments contained in line
  Input: argc (number of CLA incl. program name), argv (CLAs),
        maxTokens (number of tokens/words that are in the line)
  Output: None; see return instead
  */

  int field; // holds field number from arguments

  for (int a = argc - 1; a > 2; a--)
  {
    field = atoi(argv[a]);
    if (field <= maxTokens + 1)
    {
      return (field);
    }
  }
  return 0;
}
