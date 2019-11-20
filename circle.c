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
	float x1;
	float y1;
};

int main(int argc, char* argv[])
{
    char input_file[60];
    int offset=0;
    int points_read=0;
    float x=0;
    float y=0;
    float r=0;
    char output[50];
    int j=0;
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
    //long lSize;
    int i;
    filepointer = fopen (input_file,"rb");
    if (filepointer==NULL) 
    {
      	printf("Cannot open binary file\n");
    }
    fseek (filepointer, offset*sizeof(rec) , SEEK_SET);
    //lSize = ftell (filepointer);
    //rewind (filepointer);
    //numOfrecords = (int) lSize/sizeof(rec);
    //strcpy(output,strcat(output,"|"));
    //printf("%s\n",output);
    int f = open(output,O_WRONLY);
    if(f == -1){
	perror("open error");
	exit(-1);
	}
    for (i=0; i<points_read ; i++)
    {
	fread(&rec, sizeof(rec), 1, filepointer);
	float x0 = rec.x1;
	float y0 = rec.y1;
	//float dx = fabs(x0-x);
        //float dy = fabs(y0-y);
	float dx = x0 - x;
	float dy = y0 - y;
	if(((dx*dx)+(dy*dy))<=r*r)
    	{
		//char str[60];
        	//sprintf(str,"%f %f\n",x0,y0);
		//printf("%s\n",str);
		write(f,&rec,sizeof(struct MyRecord));
    	}
    }
    fclose(filepointer);
    return 0;
}