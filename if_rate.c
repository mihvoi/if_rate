
/*
 LICENSE:
 Author: Mihai Voicu : mihvoi@gmail.com
 Free usage.
 No warranties. 
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>


#define MAX_LINE_FIS_PROC_SIZE 1024
#define MAX_NR_INTERFETE 20
#define MAX_LEN_NUME_INTERFATA 20
#define MAX_NR_COUNTERI 20
#define SEPARATORI " \t\n\r"
#define DEFAULT_NR_SEC_MONITORIZARE 1

unsigned long long int md_get_msec_time(void);

int main(int argc,char **argv)
{
unsigned long long int time_start;
unsigned long long int time_stop;
int interval_msecs;
int nr_crt,prima_oara,i;
int interval_secs;
const char* fis_dev="/proc/net/dev";
char *p;
char *p_supp;
FILE *f;

unsigned long long int counteri[MAX_NR_INTERFETE][MAX_NR_COUNTERI];
unsigned long long int counteri_anterior[MAX_NR_INTERFETE][MAX_NR_COUNTERI];

unsigned long long int tmp_uint;
char buff[MAX_LINE_FIS_PROC_SIZE+1];


	
	if(argv[1]==NULL)
		{
		interval_secs=0;
		}
	else
		{
		interval_secs=atoi(argv[1]);
		if(interval_secs==0)
			{
			printf("Usage: if_rate [interval_in_seconds] (1..60, default 1)\n");
			exit(-1);
			};
		}

	if((interval_secs<=0)||(interval_secs>60))
		{
		interval_secs=DEFAULT_NR_SEC_MONITORIZARE;
		printf("Assuming interval of %d seconds\n",interval_secs);
		}

	f=fopen(fis_dev,"r");
	if(f==NULL){
		printf("Cannot open file:\"%s\"",fis_dev);
		exit(-1);
		}
	prima_oara=1;

	time_start=0;
	while(1){
		system("clear"); //Ugly but portable
		time_stop=md_get_msec_time();
		interval_msecs=time_stop-time_start;
		if(!prima_oara)
		{
			printf("Averages for the last %d msec\n",interval_msecs);
		}
		else
		{
			printf("Calculating rates for %d seconds...\n",interval_secs);
		}



		printf("----------------------------------------------------------------------\n");
		printf("|| %-10s ||%-25s||%-25s||\n","IF","Input","Output");
		printf("----------------------------------------------------------------------\n");
		nr_crt=-1;


		while(nr_crt<MAX_NR_INTERFETE-2){
			nr_crt++;
			p=fgets(buff,MAX_LINE_FIS_PROC_SIZE,f);
			if(p==NULL){
				//printf("End of file\n");
				break;
				}

		p=strchr(buff,':');
		if(p==NULL)
			{
			continue;
			}
		*p='\0';
		p++;
		i=-1;
		printf("||%-11s ",buff);	
		p=strtok(p,SEPARATORI);
		while(p!=NULL)
			{
			i++;
			if(i>MAX_NR_COUNTERI){
				printf("Reached MAX_NR_COUNTERI=%d\n",MAX_NR_COUNTERI);
				exit(-1);
				}
			tmp_uint=strtoul(p,&p_supp,10);
			if(p_supp==NULL)
				{
				printf("Invalid format for number argument :\"%s\"\n",p);
				exit(-1);
				}
			counteri[nr_crt][i]=tmp_uint;
			
			if(!prima_oara)
			{
				if(i==0||i==8) //bytes
			  		printf("||%7Lu kbps",(counteri[nr_crt][i]-counteri_anterior[nr_crt][i])*8/interval_msecs);
				if(i==1||i==9)//pachet
					printf("|%7Lu pk/s",(counteri[nr_crt][i]-counteri_anterior[nr_crt][i])*1000/interval_msecs);
			}
			counteri_anterior[nr_crt][i]=counteri[nr_crt][i];
			p=strtok(NULL,SEPARATORI);
			}
		printf("||\n");
		time_start=time_stop;
		}
		if(fseek(f,0,SEEK_SET)!=0){
			printf("Can not fseek to the start of the file %s\n",fis_dev);
			exit(-1);
			}

		if(prima_oara){
			prima_oara=0;
			}
		else{
			}
			
		printf("----------------------------------------------------------------------\n");
		sleep(interval_secs);
		}

}


unsigned long long int md_get_msec_time(void)
{
	struct timeval tv;
	struct timezone tz;
	tz.tz_dsttime=0;
	tz.tz_minuteswest=0;
	gettimeofday(&tv,&tz);
	return(tv.tv_sec*1000+(tv.tv_usec)/1000);
}

