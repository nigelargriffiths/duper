#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RANGE(min,max) ((int)random() % ((max) - (min) +1)) + (min)

#define WIDTH 80
#define SETS 20

struct entry {
	struct entry *next;
	char *string;
};
/* debug off by default */
int debug = 0;

int        max_item[SETS];
struct entry *items[SETS];

/* debug only */
void listitems()
{
	int i;
	struct entry *p;

	for(i=0;i<SETS;i++) {
	   if(max_item[i] >0) {
		for(p=items[i];p != 0;p = p->next)
		   fprintf(stderr, "Set %d (max=%d): string=%s\n",i,max_item[i],p->string);
	   }
	}
}

void putitems(int set, char *file)
{
FILE *fp;
char buffer[WIDTH+1];
struct entry *p = 0;

	fprintf(stderr, "Reading file \"%s\" as set %d, ",file,set);
	if((fp = fopen(file,"r")) == NULL) {
		perror(file);
		exit(42);
	}
	while( fgets(buffer,WIDTH, fp) != 0) {
		if(buffer[strlen(buffer)-1] == '\n') /* ditch NL's */
			buffer[strlen(buffer)-1] = 0;
		max_item[set]++;
		if(p == 0) {
			items[set] = p = malloc(sizeof(struct entry));
		}
		else {
			p->next = malloc(sizeof(struct entry));
			p = p->next;
		}
		p->next = 0;
		p->string = malloc(strlen(buffer)+1);
		strcpy(p->string,buffer);
	}
	fprintf(stderr, "%d items found\n",max_item[set]);
}

char *getitem(int set, int num, int del)
{
	struct entry *p;
	struct entry *q;
	int i;

	if(debug)
	fprintf(stderr, "getitem(set=%d,num=%d,del=%d) max=%d\n",set,num,del,max_item[set]);
	if(max_item[set] == 0) {
		fprintf(stderr, "ERROR: no items left in set %d\n", set);
		exit(46);
	}
	if(num > max_item[set]) {
		fprintf(stderr, "ERROR: num %d bigger than the max %d for set %d\n",
				num,max_item[set],set);
		exit(45);
	}
	q = p = items[set];
	for(i=0;i<num-1;i++) {
		q = p;
		p = p->next;
	}
	if(del) {  
		/* delete this item so that we do not use it again */
		if(p == items[set])
			items[set] = q->next;
		else
			q->next = p->next;
		max_item[set]--;
		/* lets not bother to free the memory as we do not need more */
	}
	return(p->string);
}

int main(int argc, char ** argv)
{
	int min;
	int max;
	int rmin;
	int rmax;
	int setnum;
	int i;
	char *p;
	char *q;
	char string[1024];

	if( !strcmp(argv[1],"-?") || argc < 4) {
		printf("%s: Hint\n", argv[0]);
		printf("%s min max \"C-language-printf-string\" file1, file2...\n", argv[0]);
		printf("- min max  = how makes lines to output\n");
		printf("- file1, file2 etc = files with answers 1 per line\n");
		printf("- use 2>/dev/null to remove info output\n\n");

		printf("\"printf-string\" details\n");
		printf("%%d = current line number\n");
		printf("- up to ten %%d's per line\n");
		printf("- Example: duper 25 125 \"number %%d\"\n\n");

		printf("@[n,m] = random number in range from n to m inclusive\n");
		printf("- Example: duper 1 10 \"Random @[0,100] percent\n\n");

		printf("@(1) = random entry from file1, similar for @(2) and file2, etc\n");
		printf("- Example: duper 1 10 \"Loto number is @(1)\" possible-numbers-file\n\n");

		printf("@{1} = random entry from file1 (once only), similar for @{2}, etc\n");
		printf("- Example: duper 1 10 \"name=@{1} prize=@{2}\" names prizes\n");
		printf("- If it runs out answer - it will complain\n");

		exit(42);
	}
	/* save the first two arguments */
	min = atoi(argv[1]);
	max = atoi(argv[2]);

	/* if the shell environment variable set DEBUG */
	if(getenv("DEBUG") != 0)
		debug++;

	/* 
	 * if the shell environment variable set 
	 *	NORANDOM=<number> 
	 * then use this number as the seed so its re-runable with
	 * the same "random" number sequence again!!
	 */
	if((q = getenv("NORANDOM")) != 0)
		srandom(atoi(q));
	else
		srandom(getpid());

	argc -= 3; /* remove other arguments */

	/* the rest are the filenames of files containing lists */
	for(i=0;i<argc-1;i++)
		putitems(i,argv[4+i]);

	/* main loop */
	for(i=min;i<=max;i++) {
		if(debug) listitems();
		strcpy(string,argv[3]);
		p = &string[0];
		q = &string[0];
		for(;*q!=0;q++) {
			if(*q == '@' && *(q+1) == '[' ) { /* @[n,m] */
				*q = 0;
				printf(p,i,i,i,i,i,i,i,i,i,i);
				rmin = atoi(q+2);/* skip the @[ */
				while(*q != ',') /* skip to next number */
					q++;
				q++;
				rmax = atoi(q);
				while(*q != ']') /* skip to after final ] */
					q++;
				printf("%d",RANGE(rmin,rmax));
				p = q +1;
			}
			if(*q == '@'  && *(q+1) == '(' ) { /* @(n) */
				*q = 0;
				printf(p,i,i,i,i,i,i,i,i,i,i);
				setnum = atoi(q+2) -1; /* humans count from 1 */
				while(*q != ')')
					q++;
				printf("%s",getitem(setnum,RANGE(0,max_item[setnum]),0));
				p = q +1;
			}
			if(*q == '@'  && *(q+1) == '{' ) { /* @{n} */
				*q = 0;
				printf(p,i,i,i,i,i,i,i,i,i,i);
				setnum = atoi(q+2) -1; /* humans count from 1 */
				while(*q != '}')
					q++;
				printf("%s",getitem(setnum,RANGE(0,max_item[setnum]),1));
				p = q +1;
			}
		}
		printf(p,i,i,i,i,i,i,i,i,i,i);
		printf("\n");
	}
	return 0;
}
