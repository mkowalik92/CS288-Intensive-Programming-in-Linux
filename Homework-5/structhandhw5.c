#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1000

struct clip *build_a_lst();
//struct clip *append();
//int find_length();
//void print_lst();
//void split_line();

struct clip {
  int views;
  char *user;
  char *id;
  char *title;
  //char *duration;
  struct clip *next;
} *head;

int main(int argc, char **argv) {
  int n;
  head = build_a_lst(*(argv+1));
  //n = find_length(head);
  //printf("%d clips\n",n);
  //print_lst(head);		/* prints the table */
  return 0;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[5];
  char line[LINE_LENGTH];
  int cnt=0;
  hp=NULL;

  // open fn
  fp = fopen(fn, "r");
  // while no more lines
  while( fgets(line, LINE_LENGTH, fp) != NULL )
    {
      printf("%s",line);
      //printf("%s", line);
      //split_line(fields, line);
      //printf("%s - ", fields[0]);
      //printf("%s\n", fields[1]);
      //hp = append(hp, fields);
    }
  // read a line
  // split the line into four substrings/int and store them in a struct
  // append - add the struct at the end of the list
  // return the head pointer holding the list

  return hp;
}

/* fields will have four values stored upon return */
void split_line(char **fields,char *line) {
  int i=0;
  char *token, *delim;
  delim = ",\n";
  //token = line;
  //printf("%s", line);
   // call strtok(line, delim);
  //printf("%s\n", line);
  //fields = strtok(line, delim);
  //printf("%s", line);
  //strtok(line, delim);
  //printf("%s", line);
  //cp->title = (char*) malloc(strlen(cp->title) + 1);
  
  fields[i] = strtok(line, delim);
  
  //printf("%s\n", fields[i]);
  //printf("%s\n", strtok(line, delim));
   // repeat until strtok returns NULL using strtok(NULL, delim);
  
  //while ( fields[++i] = strtok(NULL, delim) );
  //printf("%s - ", fields[0]);
  //printf("%s\n", fields[1]);
  
  while ( fields[++i] = strtok(NULL, delim) );
}

/* set four values into a clip, insert a clip at the of the list */
struct clip *append(struct clip *hp,char **five) {
  struct clip *cp,*tp;
  //char* temp;
  // views users id titles next

  //printf("%s,", five[0]);
  //printf("%s,", five[1]);
  //printf("%s,", five[2]);
  //printf("%s\n", five[3]);
  
     // malloc tp
  cp = malloc(sizeof(hp));
  //tp->views = malloc;
  //cp->views = (int*)malloc(sizeof(atoi(*five)));

  cp->views = atoi(five[0]);
  cp->user = (char*)malloc(strlen(five[1]));
  cp->id = (char*)malloc(strlen(five[2]));
  cp->title = (char*)malloc(strlen(five[3]));
  
  //tp->views = atoi(five[0]);
  //printf("%d\n", tp->views);
  //printf("%s\n", five[1]);
  //strcpy(tp->user, five[1]);
  //strcpy(tp->id, five[2]);
  //tp->title = five[1];
  //tp->title = NULL;
  strcpy(tp->user, five[1]);
  strcpy(tp->id, five[2]);
  strcpy(tp->title, five[3]);
  //printf("%s\n", tp->title);
  //strcpy(cp->title, five[1]);
  
  //printf("%s\n", cp->title);
  //strcpy(tp->duration, five[4]);
  //tp->next = hp;
  //cp = hp;
  
  
  if ( hp )
    {
      cp = hp;
      while (cp->next)
	{
	  cp = cp->next;
	}
      cp->next = tp;
    }
  else
    {
      hp = tp;
    }
  
  
     // set views using atoi(*five)
     // malloc for four strings.
     // strcpy four strings to tp
     // insert tp at the end of the list pointed by hp
     // use cp to traverse the list

  return hp;
}

int find_length(struct clip *cp) {
  int count = 0;
  struct clip *tp;
  tp = cp;
  while ( tp )
    {
      count++;
      tp = tp->next;
    }
  return count;
}

void print_lst(struct clip *cp) {
  /* 
     use a while loop and the statement below to print the list
     printf("%d,%s,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title,cp->time);
  */
  struct clip *tp;
  tp = cp;
  while ( tp )
    {
      printf("%d,%s,%s,%s\n",cp->views,cp->user,cp->id,cp->title);
      tp = tp->next;
    }
}

/* end */
