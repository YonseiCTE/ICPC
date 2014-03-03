/*******
*	ACM_ICPC 2010 Daejeon 
*		problem B string popping
*
*	resolver : kong ji yeon
*	date : 2014 / 03 / 01
*
*******/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Input(int (*testcase),char *(**string));
int* Calculate(int testcase,char **string);
int SetIndexes(char *string,int *indexes);
void Output(int *answer,int testcase);
int Check(char *string,int *indexes);
int main(int argc,char* argv[]){
	int testcase;
	char **string;
	int *answer;
	Input(&testcase,&string);
	answer=Calculate(testcase,string);
	Output(answer,testcase);
	return 0;
}
void Input(int (*testcase),char *(**string)){
	int i;
	scanf("%d",testcase);
	*string=(char**)calloc(*testcase,sizeof(char*));
	for(i=0;i<*testcase;i++){
		*(*string+i)=(char*)calloc(1000,sizeof(char));
		scanf("%s",*(*string+i));
	}
}	
int* Calculate(int testcase,char **string){
	int i;			
	int *answer;	
	int *indexes;
	answer=(int*)calloc(testcase,sizeof(int));
	for(i=0;i<testcase;i++){
		indexes=(int*)calloc(1000,sizeof(int));
		SetIndexes(string[i],indexes);
		answer[i]=Check(string[i],indexes);
		if(string[i]!=0){
			free(string[i]);		
			string[i]=0;
		}
		free(indexes);
	}
	if(string!=0){
		free(string);		
		string=0;
	}
	return answer;
}
int SetIndexes(char *string,int *indexes){
	int i=0;
	char temp=string[i];
	int index=0;
	memset(indexes,-1,1000*sizeof(int));
	indexes[index]=i;
	while(string[i]!=0){
		if(string[i]!=temp){
			temp=string[i];
			indexes[++index]=i;
		}
		i++;
	}
	return index+1;
}
int Check(char *string,int *indexes){
	int i;
	int *temp;
	char *stringTemp;
	int remove=0;
	char key;
	int len;
	int ret=0;
	temp=(int*)calloc(1000,sizeof(int));
	stringTemp=(char*)calloc(1000,sizeof(char));
	memcpy(temp,indexes,1000*sizeof(int));
	memcpy(stringTemp,string,1000);
	len=strlen(stringTemp);
	for(i=0;temp[i]!=-1;i++){
		if(temp[i]!=-2 && strlen(stringTemp)>1){
			key=stringTemp[temp[i]];
			remove=0;
			while(string[remove+temp[i]]==key){
				remove++;
			}
			if(remove>1){
				memmove(stringTemp+temp[i],stringTemp+temp[i]+remove,sizeof(char)*strlen(stringTemp)-remove);
				stringTemp[len-remove]=0;
				if(strlen(stringTemp)==0){
					free(temp);
					free(stringTemp);
					return 1;
				}
				temp[i]=-2;
				SetIndexes(stringTemp,temp);
				ret=Check(stringTemp,temp);
				if(ret==1){
					free(temp);
					free(stringTemp);
					return 1;
				}
			}
			memcpy(temp,indexes,1000*sizeof(int));
			memcpy(stringTemp,string,1000);
		}
	}	
	free(temp);
	free(stringTemp);
	return 0;
}
void Output(int *answer,int testcase){
	int i;
	for(i=0;i<testcase;i++){
		printf("%d\n",answer[i]);
	}
	if(answer!=NULL){
		free(answer);
		answer=NULL;
	}
}

