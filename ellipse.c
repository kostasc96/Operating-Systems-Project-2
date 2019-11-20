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
    int offset=0;
    int points_read=0;
    char output[50];
    float h;
    float k;
    float a;
    float b;
    int j=0;
    for(j=0; j<argc; j++)
    {
	char* c=argv[j];
        if(!strcmp(c,"-i"))
        {
            strcpy(input_file,argv[j+1]);
        }
        if(!strcmp(c,"-o"))
        {
            strcpy(output,argv[j+1]);
        }
        if(!strcmp(c,"-a"))
        {
            h = atof(argv[j+1]);
            k = atof(argv[j+2]);
            a = atof(argv[j+3]);
            b = atof(argv[j+4]);
        }
        if(!strcmp(c,"-f"))
        {
            offset = atoi(argv[j+1]);
        }
	if(!strcmp(c,"-n"))
        {
            points_read = atoi(argv[j+1]);
        }
    }
    FILE *filepointer;
    struct MyRecord rec;
    //long lSize;
    int i;
    filepointer = fopen (input_file,"rb");
    if (filepointer==NULL)
    {
      	printf("Cannot open binary file\n");
        return -1;
    }
    else
    {
        fseek (filepointer, offset*sizeof(rec) , SEEK_SET);
        //lSize = ftell (filepointer);
        //rewind (filepointer);
        //numOfrecords = (int) lSize/sizeof(rec);
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
    		float dx = fabs(h-x0);
    		float dy = fabs(k-y0);
    		if((dx<=a)&&(dy<=b))
    		{
    			//char str[60];
        		//sprintf(str,"%f %f\n",x0,y0);
			//printf("%s\n",str);
			write(f,&rec,sizeof(struct MyRecord));
		}
        }
    }
    return 0;
}

