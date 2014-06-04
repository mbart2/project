#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 10
void* mymalloc(int size){
		void* ptr = malloc(size);
		fprintf(stderr,"malloc: %p\n", ptr);
		return ptr;
	}
	
	void myfree(void* ptr){
		fprintf(stderr, "free: %p\n",ptr);
		free(ptr);
	}

char *concatenate(char *a, char *b)
{
	int size = sizeof(a) *strlen(a);
	size += sizeof(b) * strlen(b);
	char *c = (char*)mymalloc(size);
	memcpy(c,a,strlen(a));
	memcpy(c+(strlen(a)*sizeof(char)),b,(sizeof(char)*strlen(b)));
	return c;
}


int main(int argc, char **argv)
{
	if(argc > 4)
	{
		printf("Usage: hw1_leaky <count> <firstword> <secondword> \n");
		exit(1);
	}
	
	char *middle = "cruel";
	char number[MAXCHAR];
	int i=0;

	for(i=0;i<=atoi(argv[1]); i++)
	{
		sprintf(number,"%d",i);
		
		//begin leaky
		char *line_3 = concatenate(number,argv[3]);
		char *line_2 = concatenate(middle, line_3);
		char *line_1 = concatenate(argv[2],number);
		char *line   = concatenate(line_1, line_2);
		myfree(line_3);
		myfree(line_2);
		myfree(line_1);
		/*char *line = concatenate(// not leaked
				concatenate(argv[2], number),//leaked
				concatenate(middle, //leaked
				concatenate(number, argv[3]))); //leaked
		*/
		if(i>0) //should not free statically allocated "cruel" string
		  myfree(middle);
		
		//end leaky
		printf("%s \n",line);
		middle = line;
		
	}
	
	

	myfree(middle);

}
