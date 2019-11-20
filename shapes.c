#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>

int circles;
int pid;
//char* pathname;
//char *pathname1;
//char *pathname2;
int status1,status2;



void Worker1(char* sh,char* input_file,char *output,float x,float y,float r,int o,int p) {

	char xs[20],ys[20],rs[20],of[20],pr[20];

	sprintf(xs,"%f",x);
	sprintf(ys,"%f",y);
	sprintf(rs,"%f",r);
        sprintf(of,"%d",o);
	sprintf(pr,"%d",p);
	execl(sh,"-i",input_file,"-o",output,"-a",xs,ys,rs,"-f",of,"-n",pr,NULL);
}

void Worker2(char* sh,char* input_file,char *output,float x,float y,float r1,float r2,int o,int p) {

	char xs[20],ys[20],r1s[20],r2s[20],of[20],pr[20];

	sprintf(xs,"%f",x);
	sprintf(ys,"%f",y);
	sprintf(r1s,"%f",r1);
	sprintf(r2s,"%f",r2);
        sprintf(of,"%d",o);
	sprintf(pr,"%d",p);
	execl(sh,"-i",input_file,"-o",output,"-a",xs,ys,r1s,r2s,"-f",of,"-n",pr,NULL);
	//exit(0); /* Worker ends */
}

void Worker3(char* sh,char* input_file,char *output,float x,float y,float r1,char *co,int o,int p) {

	char xs[20],ys[20],r1s[20],of[20],pr[20];

	sprintf(xs,"%f",x);
	sprintf(ys,"%f",y);
	sprintf(r1s,"%f",r1);
        sprintf(of,"%d",o);
	sprintf(pr,"%d",p);
	execl(sh,"-i",input_file,"-o",output,"-a",xs,ys,r1s,co,"-f",of,"-n",pr,NULL);
	//exit(0); /* Worker ends */
}

int main(int argc, char *argv[])
{
int in_fd;
int wcount=0;
int count=0;
char InputBinaryFile[50];
char TempDir[50];
int WorkersCount;
int j=0;
for(j=0; j<argc; j++)
    {
	char* a=argv[j];
        if(!strcmp(a,"-i"))
        {
            strcpy(InputBinaryFile,argv[j+1]);
        }
        if(!strcmp(a,"-w"))
        {
            WorkersCount = atoi(argv[j+1]);
        }
        if(!strcmp(a,"-d"))
        {
            strcpy(TempDir,argv[j+1]);
        }
    }
char shape[20];
char compass[10];
float x,y;
int pids[20];
long sz,sz1,n;
float r,r1,r2;
/*
anoigei arxeio kai metraei mege8os
*/
FILE *fp;
fp=fopen(InputBinaryFile,"r");
fseek(fp, 0L, SEEK_END);
sz = ftell(fp);
sz1=sizeof(float);
n=(sz/sz1)/2; /* posa exei */
int PointsToReadCount = n/WorkersCount;
int points_read[WorkersCount+1];
long int offset[WorkersCount+1];
int k=0;
offset[0]=0;
for(k=1;k<=WorkersCount;k++)
{
    offset[k] = offset[k-1] + PointsToReadCount;
}
int k1=0;
for(k1=0;k1<=(WorkersCount-1);k1++)
{
	points_read[k1] = PointsToReadCount;
}
points_read[WorkersCount-1] = n - offset[WorkersCount-1];
int command=0;

printf("CLI> ");
char buf[1000];
while(scanf("%[^\n]s",buf)==1){
command++;
char buf1[1000];
char arg_count[50];
//char ***array = (char***) malloc(50 * sizeof(char**));
//int w;
int arg=0;
//for(w=0;w<100;w++)
//{
 //   array[w] = (char**) malloc(50 * sizeof(char*));
//}
int theseis;
char* temp1;
theseis=0;
char *token = strtok(buf, ",");
//array[theseis][arg] = malloc((strlen(token)+1) * sizeof(char));
char array[50][50][20];
while(token != NULL)
{
	if(token[0] == ' ')
		token++;
	if(token[strlen(token)-1] == ';')
		token[strlen(token)-1] = '\0';
    	if(strcmp(token,"exit") == 0)
	{
		exit(0);
	}
    theseis++;
    arg=0;
    temp1 = token;
    while(sscanf(temp1,"%s",buf1)==1)
    {
	 arg++;
         temp1 += strlen(buf1);
         if(temp1[0] == ' ')
         temp1++;
        // array[theseis-1][arg-1] = malloc((strlen(buf1)+1) * sizeof(char));
         strcpy(array[theseis-1][arg-1],buf1);
    }
    arg_count[theseis-1] = arg;
    token = strtok(NULL, ",");
}
	char shpid[theseis][60];
	int i1=0;
	for(i1=0;i1<theseis;i1++)
	{
		pid = fork();
		if(pid==0)
		break;
		else
		pids[i1] = pid;
        }
	if(pid != 0) {
		//printf("Master\n");
        	int hndlrs;
		for(hndlrs=0;hndlrs<theseis;hndlrs++)
		circles = wait(&status1); /* master waits */
		char gnu_file[30];
		sprintf(gnu_file,"%d_script.gnuplot",command);
		char gnu_name[30];
		strcpy(gnu_name,gnu_file);
		char shpid_name[30];
		FILE *fp3 = fopen(gnu_file,"r");
		FILE *fp2 = fopen(gnu_file,"w");
		fprintf(fp2,"%s\n","set terminal png");
		fprintf(fp2,"%s\n","set size ratio -1");
		char temp_array1[] = "set output \"./";
		char temp_array2[60];
		sprintf(temp_array2,"%d_image.png\"",command);
		strcat(temp_array1,temp_array2);
		fprintf(fp2,"%s\n",temp_array1);
		fprintf(fp2,"%s\n","plot \\");
		int h=0;
		for(h=0;h<theseis;h++)
		{
			sprintf(shpid_name,"%d.out",pids[h]);
			char temp_array3[50];
			if(h<theseis-1){
			sprintf(temp_array3,"\"%s/%s\" notitle with points pointsize 0.5 linecolor rgb \"%s\",\\",TempDir,shpid_name,array[h][arg_count[h]-1]);
			}
			else if(h==theseis-1){
			sprintf(temp_array3,"\"%s/%s\" notitle with points pointsize 0.5 linecolor rgb \"%s\"",TempDir,shpid_name,array[h][arg_count[h]-1]);
			}
			fprintf(fp2,"%s\n",temp_array3);
		}
		pid = fork();
		 if(pid == 0)
            {
                execlp("gnuplot", "gnuplot",gnu_name, (char*)0);
		exit(0);
            }
	    exit(0);	/* Master ends */
	}
	else {
		//printf("child Handler\n");
		pid = getpid();
		int f=0;
		char pathname[WorkersCount][60];
		char in_fd_array[WorkersCount];
		for(f=0;f<WorkersCount;f++)
		{
			count = f + 1;
			sprintf(pathname[f],"%s/%d_w%d.fifo", TempDir, pid, count);
			mkfifo(pathname[f], 0777);
			in_fd = open(pathname[f], O_RDONLY|O_NONBLOCK);
			in_fd_array[f] = in_fd;
			if(in_fd == -1)
			{
				perror("open error");
				exit(-1);
			}

		}
 	int work = 0;
	for(work=0;work<WorkersCount;work++)
	{
      		pid = fork();
		if(pid==0)
		break;
	}
	/* makes Worker */
        if(pid != 0) {
	    int wrks=0;
            for(wrks=0;wrks<WorkersCount;wrks++)
            circles = wait(&status2); /* handler waits */
	    struct MyRecord
            {
                float x1;
                float y1;
            };
	    int pidh = getpid();
            struct MyRecord ptr;
	    sprintf(shpid[i1],"%s/%d.out",TempDir,pidh);
	    FILE *fp1 = fopen(shpid[i1],"w");
	    int handl=0;
	    for(handl=0;handl<WorkersCount;handl++)
	    {
            	int numread = read(in_fd_array[handl] ,&ptr,sizeof(struct MyRecord));
		while(numread>0)
		{
			fprintf(fp1,"%f %f\n",ptr.x1,ptr.y1);
	    		numread = read(in_fd_array[handl] ,&ptr,sizeof(struct MyRecord));
		}
	    }
            exit(0); /* Handler ends */
        }
   	else {
	//printf("child Worker\n");
	if(!strcmp(array[i1][0],"circle"))
	{
			//printf("circle\n");
			Worker1(array[i1][0],InputBinaryFile,pathname[work],atof(array[i1][1]),atof(array[i1][2]),atof(array[i1][3]),offset[work],points_read[work]);
	}
	if(!strcmp(array[i1][0],"square"))
	{
			//printf("square\n");
			strcpy(shape,array[i1][0]);
			x = atof(array[i1][1]);
			y = atof(array[i1][2]);
			r = atof(array[i1][3]);
			Worker1(shape,InputBinaryFile,pathname[work],x,y,r,offset[work],points_read[work]);
	}
	if(!strcmp(array[i1][0],"ring"))
	{
			//printf("ring\n");
			strcpy(shape,array[i1][0]);
			x = atof(array[i1][1]);
			y = atof(array[i1][2]);
			r1 = atof(array[i1][3]);
			r2 = atof(array[i1][4]);
			Worker2(shape,InputBinaryFile,pathname[work],x,y,r1,r2,offset[work],points_read[work]);
	}
	if(!strcmp(array[i1][0],"semicircle"))
	{
			//printf("semicircle\n");
			strcpy(shape,array[i1][0]);
			x = atof(array[i1][1]);
			y = atof(array[i1][2]);
			r1 = atof(array[i1][3]);
			strcpy(compass,array[i1][4]);
			Worker3(shape,InputBinaryFile,pathname[work],x,y,r1,compass,offset[work],points_read[work]);
	}
	if(!strcmp(array[i1][0],"ellipse"))
	{
			//printf("ellipsis\n");
			strcpy(shape,array[i1][0]);
			x = atof(array[i1][1]);
			y = atof(array[i1][2]);
			r1 = atof(array[i1][3]);
			r2 = atof(array[i1][4]);
			Worker2(shape,InputBinaryFile,pathname[work],x,y,r1,r2,offset[work],points_read[work]);
	}
	exit(0);               /*worker ends*/
	}
}
/*int k2,l;
for(k2=0;k2<theseis;k2++){
	for(l=0;l<(arg_count[k2]);l++){
		free(array[k2][l]);}
free(array[k2]);
}
free(array);  */
//exit(0); /* Master ends */

}
}

