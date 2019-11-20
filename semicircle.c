#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <ctype.h>


struct MyRecord
{
	float x;
	float y;
};

int main(int argc, char* argv[])
{
    char input_file[60];
    char output[50];
    int offset=0;
    int points_read=0;
    float x;
    float y;
    float r;
    int j=0;
    char* d;
    for(j=0; j<argc; j++)
    {
	char* a=argv[j];
        if(!strcmp(a,"-i"))
        {
            strcpy(input_file,argv[j+1]);
        }
        if(!strcmp(a,"-o"))
        {
            strcpy(output,argv[j+1]);
        }
        if(!strcmp(a,"-a"))
        {
            x = atof(argv[j+1]);
            y = atof(argv[j+2]);
            r = atof(argv[j+3]);
            d = argv[j+4];
        }
	if(!strcmp(a,"-f"))
        {
            offset = atoi(argv[j+1]);
        }
	if(!strcmp(a,"-n"))
        {
            points_read = atoi(argv[j+1]);
        }
    }
    FILE *filepointer;
    struct MyRecord rec;
    int i;
    filepointer = fopen (input_file,"rb");
    if (filepointer==NULL) 
    {
      	printf("Cannot open binary file\n");
    }
    fseek (filepointer, offset*sizeof(rec) , SEEK_SET);
    int f = open(output,O_WRONLY);
    if(f == -1){
	perror("open error");
	exit(-1);
    }
    for (i=0; i<points_read ; i++)
    {
    fread(&rec, sizeof(rec), 1, filepointer);
    float x0=rec.x;
    float y0=rec.y;
    float dx = fabs(x0-x);
    float dy = fabs(y0-y);
    if((dx<=r)&&(dy<=r))
    {
        //int x_k = x0 - x;
        //int y_k = y0 - y;
        if(!strcmp(d,"N"))
        {
            if(y0>=y)
            {
		write(f,&rec,sizeof(struct MyRecord));
            }
        }
        if(!strcmp(d,"S"))
        {
            if(y0<=y)
            {
                write(f,&rec,sizeof(struct MyRecord));
            }
        }
        if(!strcmp(d,"W"))
        {
            if(x0<=x)
            {
                write(f,&rec,sizeof(struct MyRecord));
            }
        }
       	if(!strcmp(d,"E"))
        {
            if(x0>=x)
            {
                write(f,&rec,sizeof(struct MyRecord));
            }
        }
    }
    }
    return 0;
}