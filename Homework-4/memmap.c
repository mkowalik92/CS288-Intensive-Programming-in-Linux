#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int argvCharCount = 0;
int outputSpaces = 0;
char **temp;
char **argvChanged;
char **tempUnchanged;

void printEmptyLine()
{
  printf("       +------+------+------+------+\n");
}

void printDividerLine()
{
  for ( int i = 0; i < 3; i++ )
    {
      printEmptyLine();
    }
}

void printFirstLine()
{
  printf("       +------+------+------+------+ FFFFFFFF\n");
}

void printLastLine()
{
  printf("       +------+------+------+------+ 00000000\n");
}

void argvContents(int argc, char **argv)
{
  argc--;
  int argcStart = argc;
  int charsPrinted = 0;
  int argvPointerChanges = 0;
  int threeLetter = 0;
  if ( outputSpaces == 0 )
    {
      printf("       ");
      charsPrinted = 0;
    }
  if ( outputSpaces == 3 )
    {
      printf("       |      |      |      ");
      charsPrinted = 3;
    }
  if ( outputSpaces == 2 )
    {
      printf("       |      |      ");
      charsPrinted = 2;
    }
  if ( outputSpaces == 1 )
    {
      printf("       |      ");
      charsPrinted = 1;
    }
  while ( argc >= 0 )
    {
      for (int i = strlen(argv[argc]); i >= 0; i--)
	{
	  if ( argv[argc][i] == '\0' )
	    {
	      printf("|  \\0  ");
	    }
	  else
	    {
	      printf("|  %c   ", argv[argc][i]);
	    }
	  charsPrinted++;	  
	  if ( charsPrinted == 4)
	    {
	      charsPrinted = 0;
	      if ( (argc == 0) && (i == 0) )
		{
		  argvPointerChanges++;
		  printf("| %x\n", *argvChanged);
		  printEmptyLine();
		  break;
		}
	      else
		{
		  printf("| %x\n", *argvChanged);
		  if ( i == 0 )
		    {
		      argvChanged--;
		      argvPointerChanges++;
		    }
		  printEmptyLine();
		  printf("       ");
		}
	    }
	}
      argc--;
      if ( argvPointerChanges > 0 )
	{
	  argvPointerChanges = 0;
	  continue;
	}
      else
	{
	  argvChanged--;
	}
    }
  printDividerLine();
  printEmptyLine();
}

void printArgvs(int argc, char **argv)
{
  argc--;
  tempUnchanged--;
  for ( int i = argc; i >= 0; i-- )
    {
      char argvString[9];
      sprintf(argvString, "%x", &(**tempUnchanged));
      printf("argv+%d |  %c%c  |  %c%c  |  %c%c  |  %c%c  | %x\n", i, argvString[0], argvString[1], argvString[2], argvString[3], argvString[4], argvString[5], argvString[6], argvString[7], &(*tempUnchanged));
      printEmptyLine();
      printEmptyLine();
      tempUnchanged--;
    }
}

int main(int argc, char **argv)
{
  int i = 0;
  temp = argv;
  argvChanged = argv;
  while (*argv)
    {
      argvCharCount += strlen(*argv) + 1;
      argvChanged++;
      argv++;
    }
  argvChanged--;
  tempUnchanged = argv;
  argv = temp;
  outputSpaces = 4 - (argvCharCount % 4);
  printFirstLine();
  printDividerLine();
  if (outputSpaces == 4)
    {
      outputSpaces = 0;
    }
  argvContents(argc, argv);
  printArgvs(argc, argv);
  printEmptyLine();
  printEmptyLine();
  argv = temp;
  printf("argc   |  00  |  00  |  00  |  0%d  | %x\n", argc, &argc);
  printEmptyLine();
  printEmptyLine();
  char argvString[9];
  sprintf(argvString, "%x", &(*argv));
  printf("argv   |  %c%c  |  %c%c  |  %c%c  |  %c%c  | %x\n", argvString[0], argvString[1], argvString[2], argvString[3], argvString[4], argvString[5], argvString[6], argvString[7], &argv);
  printDividerLine();
  printLastLine();
  return 0;
}
