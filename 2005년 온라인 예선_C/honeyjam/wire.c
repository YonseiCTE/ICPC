/*******
* acm_Wiring Cost_problem
* resolver : Kong ji yeon
* date : 2014 / 02 / 23
* comment :
*******/
#include<stdio.h>
#include<stdlib.h>
typedef struct _element{
	int wire;
	int length;
}ELEMENT;
void Input(int *test,int **testcase,ELEMENT ***element,int **requirement);
int* Calculate(int test,int *testcase,ELEMENT **element,int *requirement);
void Output(int *result,int test);
int compare(const void* one,const void* other);
int main(int argc,char *argv[]){
	int test;
	int *testcase;
	ELEMENT **element;
	int *requirment;
	int *result;
	Input(&test,&testcase,&element,&requirment);
	result=Calculate(test,testcase,element,requirment);
	Output(result,test);
	return 0;
}
void Input(int *test,int **testcase,ELEMENT ***element,int **requirement){
	int i,j;
	FILE *fp;
	char filename[80];
	scanf("%s",filename);
	fp=fopen(filename,"r");
	fscanf(fp,"%d",test);
	*testcase=(int*)calloc(*test,sizeof(int));
	*requirement=(int*)calloc(*test,sizeof(int));
	*element=(ELEMENT**)calloc(*test,sizeof(ELEMENT*));
	for(i=0;i<*test;i++){
		fscanf(fp,"%d",*testcase+i);
		*(*element+i)=(ELEMENT*)calloc(*(*testcase+i),sizeof(ELEMENT));
		for(j=0;j<*(*testcase+i);j++){
			fscanf(fp,"%d",&(*(*element+i)+j)->wire);
		}
		for(j=0;j<*(*testcase+i);j++){
			fscanf(fp,"%d",&(*(*element+i)+j)->length);
		}
		fscanf(fp,"%d",*requirement+i);
	}
	fclose(fp);
}
int* Calculate(int test,int *testcase,ELEMENT **element,int *requirement){
	int *result;
	int sum;
	int i,j;
	result = (int*)calloc(test,sizeof(int));
	for(i=0;i<test;i++){
		qsort(element[i],testcase[i],sizeof(ELEMENT),compare);
		sum=0;
		for(j=0;sum<requirement[i];j++){
			sum+=element[i][j].length;
		}
		result[i]=element[i][j-1].wire;
		if(element[i]!=NULL){
			free(element[i]);
			element[i]=NULL;
		}
	}
	if(testcase!=NULL){
		free(testcase);
		testcase=NULL;
	}
	if(requirement!=NULL){
		free(requirement);
		requirement=NULL;
	}

	if(element!=NULL){
		free(element);
		element=NULL;
		}
	return result; 
}
void Output(int* result,int test){
	int i;
	for(i=0;i<test;i++){
		printf("%d\n",result[i]);
	}
	if(result !=NULL){
		free(result);
		result = NULL;
	} 
} 
int compare(const void* one,const void* other){
	return ((ELEMENT*)one)->wire-((ELEMENT*)other)->wire;
}