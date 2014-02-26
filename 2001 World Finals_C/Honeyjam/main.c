/*******
*	The 2001 25th Annual acm International Collegiate
*		Programming Contest World Finals
*			sponsored by IBM
*      
*		Problem C
*	__Crossword Puzzle__
*
*	resolver : Kim Bom
*	date : 2014 / 02 / 26
*
*******/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define true 1
#define false 0
typedef struct _area{
	int x;
	int y;
	char key;
}AREA;
int Input(int *testcase,AREA **area,char ***word);	// Input 
int* Calculate(int testcase,AREA *area,char **word,int wordcount);
void CreateBoard(char ***board,AREA *area,char **word,int testcase,int wordcount,int *amax,int *dmax);	//Create Board
void ResetBoard(char **board,int amax,int dmax,int *findCount);	//all board element = '_'
int SetBoard(char **board,AREA area,char *word,char key,int *findCount);	//Insert string to board
void ResetAnswer(int *answer,int max);	//reset answer all element = -1
void InsertAnser(int *answer,int element,int max);	//store correct string	
int CheckAnswer(int *answer,int element,int max);	//except used string
int AnswerLen(int *answer,int max);	
void RemoveAnswer(int *answer,int max);	
void RestartBoard(char **board,int *answer,AREA *area,char **word,int amax,int dmax,int *findCount);	//delete wrong string
void Find(char **board,int testcase,AREA *area,char **word,int wordcount,int i,int *answer,int amax,int dmax,int *findCount);
void Output(int *answer,int wordcount,char **word,int testcase);	//Output
int main(int argc,char* argv[]){
	int testcase;	//testcase
	AREA *area;		//word x,y point
	char **word;	
	int wordcount;	
	int *answer;	
	wordcount=Input(&testcase,&area,&word);
	answer=Calculate(testcase,area,word,wordcount);
	Output(answer,wordcount,word,testcase);
	return 0;
}
int Input(int *testcase,AREA **area,char ***word){
	int i;
	int wordcount=0;
	FILE *fp;
	char filename[80];
	scanf("%s",filename);
	fp=fopen(filename,"r");
	fscanf(fp,"%d",testcase);
	*area=(AREA*)calloc(*testcase,sizeof(AREA));
	for(i=0;i<*testcase;i++){
		fscanf(fp,"%d %d %c",&(*area+i)->x,&(*area+i)->y,&(*area+i)->key);
	}
	*word=(char**)calloc(*testcase,sizeof(char*));
	i=0;
	while(i==0 || (i>0 && strcmp(*((*word)+(i-1)),"0")!=0)){
		if(i>=*testcase){
			*word=(char**)realloc(*word,(i+1)*sizeof(char*));
		}
		*(*word+i)=(char*)calloc(80,sizeof(char));
		fscanf(fp,"%s",*((*word)+i));
		i++;
		wordcount++;
	}
	fclose(fp);
	return wordcount-1;	
}
int* Calculate(int testcase,AREA *area,char **word,int wordcount){
	int i;	//area`s index OR for loop control
	int *answer;
	char **board;	//testing board
	int amax,dmax;	//board size - 
	int findCount=0;
	answer=(int*)calloc(testcase+1,sizeof(int));
	CreateBoard(&board,area,word,testcase,wordcount,&amax,&dmax); //char board[dmax][amax];
	ResetBoard(board,amax,dmax,&findCount);	//reset board - all element='_'
	ResetAnswer(answer,testcase+1);	//reset answer - all element=-1
	i=0;	
	Find(board,testcase,area,word,wordcount,i,answer,amax,dmax,&findCount);	
	for(i=0;i<dmax;i++){
		if(board[i]!=NULL){
			free(board[i]);
			board[i]=NULL;
		}
	}
	if(board!=NULL){
		free(board);
		board=NULL;
	}
	if(area!=NULL){
		free(area);
		area=NULL;
	}
	return answer;
}
void Output(int *answer,int wordcount,char **word,int testcase){
	int i,j;
	int flag;	//find not used string
	int *notUse;	//not used string s
	int index=0;
	notUse=(int*)calloc(wordcount+1,sizeof(int));
	ResetAnswer(notUse,wordcount+1);	//set notUse[] all element=-1;
	for(i=0;i<wordcount;i++){
		flag=false;
		for(j=0;answer[j]!=-1;j++){
			if(i==answer[j]){
				flag=true;
			}
		}
		if(flag==false){
			notUse[index]=i;
			index++;
		}
	}
	if(AnswerLen(answer,testcase)!=testcase){
		printf("Trial 2: Impossible\n");
	}
	else if(index>=1){
		if(index==1){
			printf("Trial 1: ");
		}else{
			printf("Trial 3: ");
		}
		for(i=0;notUse[i]!=-1;i++){
			printf("%s ",word[notUse[i]]);
		}
		printf("\n");
	}
	for(i=0;i<wordcount;i++){
		if(word[i]!=NULL){
			free(word[i]);
			word[i]=NULL;
		}
	}
	if(word!=NULL){
		free(word);
		word=NULL;
	}
	if(notUse!=NULL){
		free(notUse);
		notUse=NULL;
	}
}
void CreateBoard(char ***board,AREA *area,char **word,int testcase,int wordcount,int *amax,int *dmax){
	int i;
	int asize,dsize;
	int maxString=0;
	int len;
	*amax=0;
	*dmax=0;
	for(i=0;i<wordcount;i++){	//find maxString
		len=strlen(word[i]);
		if(maxString<len){
			maxString=len;
		}
	}
	for(i=0;i<testcase;i++){	//Set board size
		if(area[i].key=='D'){
			dsize=area[i].x;
			if(*dmax<dsize){
				*dmax=dsize;
			}
		}else if(area[i].key=='A'){
			asize=area[i].y;
			if(*amax<asize){
				*amax=asize;
			}
		}
	}
	(*amax)+=maxString;	
	(*dmax)+=maxString;
	*board=(char**)calloc(*dmax,sizeof(char*));	//Create Board
	for(i=0;i<*dmax;i++){
		*((*board)+i)=(char*)calloc(*amax,sizeof(char));
	}
}
void ResetBoard(char **board,int amax,int dmax,int *findCount){
	int i;
	for(i=0;i<dmax;i++){
		memset(board[i],'_',sizeof(char)*amax);
	}
	*findCount=0;
}
void RestartBoard(char **board,int *answer,AREA *area,char **word,int amax,int dmax,int *findCount){
	int i=0;
	ResetBoard(board,amax,dmax,findCount);
	while(answer[i]!=-1){
		SetBoard(board,area[i],word[answer[i]],'s',findCount);
		i++;
	}
}
int SetBoard(char **board,AREA area,char *word,char key,int *findCount){
	int i,index=0;
	int not=true;	//type is bool
	if(area.key=='A'){	//if ACROSS
		i=area.y;
		while(word[index]!=NULL && not==1){	//testing possible or impossible
			if(board[area.x][i]=='_' || board[area.x][i]==word[index]){
				index++;
				i++;
			}else{
				not=false;
			}
		}
		if(key!='t'){
			index=0;
			i=area.y;
			while(word[index]!=NULL && not!=0){	//if possible? ->set board
				board[area.x][i]=word[index];
				index++;
				i++;
			}
		}
	}else if(area.key=='D'){	//if DOWN
		i=area.x;
		while(word[index]!=NULL && not==1){
			if(board[i][area.y]=='_'|| board[i][area.y]==word[index]){
				index++;
				i++;
			}else{
				not=false;
			}
		}
		if(key!='t'){
			index=0;
			i=area.x;
			while(word[index]!=NULL && not!=0){
				board[i][area.y]=word[index];
				index++;
				i++;
			}
		}
	}
	if(not==true && key!='t'){
		(*findCount)++;
	}
	return not;
}
void ResetAnswer(int *answer,int max){
	int i;
	for(i=0;i<max;i++){
		answer[i]=-1;
	}
}
void InsertAnser(int *answer,int element,int max){
	int i=0;
	while(i<max && answer[i]!=-1){
		i++;
	}
	answer[i]=element;
}
int CheckAnswer(int *answer,int element,int max){	
	int i=0;
	int check=false;
	while(i<max && answer[i]!=-1 && check==0){
		if(answer[i]==element){
			check=true;
		}
		i++;
	}
	return check;	//used?	true			notused? false
}
int AnswerLen(int *answer,int max){
	int i=0;
	while(i<max && answer[i]!=-1){
		i++;
	}
	return i;
}
void RemoveAnswer(int *answer,int max){
	int i=0;
	while(i<max && answer[i]!=-1){
		i++;
	}
	answer[i-1]=-1;
}
void Find(char **board,int testcase,AREA *area,char **word,int wordcount,int i,int *answer,int amax,int dmax,int *findCount){
	int esc=0;
	int j;
	for(j=0;j<wordcount && AnswerLen(answer,wordcount)<testcase;j++){
		if(CheckAnswer(answer,j,wordcount)==false ){	
			if(SetBoard(board,area[i],word[j],'t',findCount)){	// if next string is correct?
				SetBoard(board,area[i],word[j],'r',findCount);
				i++; //next area
				InsertAnser(answer,j,wordcount);	//save used string

				Find(board,testcase,area,word,wordcount,i,answer,amax,dmax,findCount);	//find next string
				i--;
				if(AnswerLen(answer,wordcount)!=testcase && *findCount!=testcase){	//if answer is wrong
					RemoveAnswer(answer,wordcount);		
					RestartBoard(board,answer,area,word,amax,dmax,findCount);
				}
			}
		}else{
			esc++;	
		}
		if(AnswerLen(answer,wordcount)==0){	//do not found answer?
			ResetBoard(board,amax,dmax,findCount);	//reset board
		}
	}
	if(esc==j){	//all string is Wrong
		return ;
	}
}



