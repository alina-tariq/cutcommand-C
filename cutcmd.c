#include <stdlib.h>
#include <stdio.h>
#include "cutcmdfuncs.h"
#define MaxAllowed 100

int main(int argc, char *argv[])
{
  /*
  Function: main
  Purpose: to validate command line arguments (CLA), get input from stdin,
          and cut input as specified by arguments
  Return: exit code 1 if there's an error or exit code 0 if no errors
  Input: argc (number of CLA incl. program name), argv (CLAs)
  Output: None; see return instead
  */

  char *line; // pointer to line input from stdin
  line = (char *)malloc(1000); // allocates spaces for line

  // outputs error message if arguments aren't valid
  if (ValidArgs(argc, argv, MaxAllowed))
  {
    fprintf(stderr, "%s: specify input_delimiter output_delimiter and 1-%d fields in order\n", argv[0], MaxAllowed);
    exit(1);
  }

  // gets input from stdin and continues to apply CutCommand function
  // until input is NULL 
  while ((fgets(line, 1000, stdin)) != NULL)
  {
    CutCommand(argc, argv, line);
  }

  exit(0);
}
