/*******
*
*Acm_ProblemA_Shopping
*Resolver : Kong ji yeon
*2014 02 08
*Comment : 파일채로 올리는 법을 모르겠습니다.
*		   소스가 간단하니 소스만 첨부하도록 하겠습니다.
*******/
#include<stdio.h>
#include<stdlib.h>
void Input(int *T,int **N,int ***W,int ***C,char *filename);
int* Calculate(int T,int *N,int **W,int **C);
void Output(int T,int (*answer));
int main(int argc,char *argv[]){
	int T;	//test case
	int *N;	//kind
	int **W;	//gram
	int **C;	//price
	int *answer;	//answer
	Input(&T,&N,&W,&C,argv[1]);	
	answer=Calculate(T,N,W,C);
	Output(T,answer);
	return 0;
}
void Input(int *T,int **N,int ***W,int ***C,char *filename){
	int i,j;	//for loop control
	FILE *fp=NULL;
	fp=fopen(filename,"r");
	fscanf(fp,"%d",T);
	*N=(int*)calloc(*T,sizeof(int));
	*W=(int**)calloc(*T,sizeof(int*));
	*C=(int**)calloc(*T,sizeof(int*));
	for(i=0;i<*T;i++){
		fscanf(fp,"%d",(*N)+i);
		*((*W)+i)=(int*)calloc(*((*N)+i),sizeof(int));
		*((*C)+i)=(int*)calloc(*((*N)+i),sizeof(int));
		for(j=0;j<*((*N)+i);j++){
			fscanf(fp,"%d",(*((*W)+i)+j));
			fscanf(fp,"%d",(*((*C)+i)+j));
		}
	}
	fclose(fp);
}
int* Calculate(int T,int *N,int **W,int **C){
	int i,j;
	double gValue;
	int *answer;
	answer=(int*)calloc(T,sizeof(int));
	for(i=0;i<T;i++){
		gValue=(double)*(*(C+i)) / *(*(W+i)) ;
		answer[i]=**(C+i);
		for(j=0;j<*(N+i);j++){
			if(gValue > (double)*(*(C+i)+j) / *(*(W+i)+j)){ 
				gValue=(double)*(*(C+i)+j) / *(*(W+i)+j); 
				answer[i]=*(*(C+i)+j);
			}
		}
		if(W[i]!=NULL){
			free(*(W+i));
			W[i]=NULL;
		}
		if(C[i]!=NULL){
			free(*(C+i));
			C[i]=NULL;
		}
	}
	if(N!=NULL){
		free(N);
		N=NULL;
	}
	if(W!=NULL){
		free(W);
		W=NULL;
	}
	if(C!=NULL){
		free(C);
		C=NULL;
	}
	return answer;
}
void Output(int T,int (*answer)){
	int i;
	for(i=0;i<T;i++){
		printf("%d\n",*(answer+i));
	}
	if(answer!=NULL){
		free(answer);
	}
}

