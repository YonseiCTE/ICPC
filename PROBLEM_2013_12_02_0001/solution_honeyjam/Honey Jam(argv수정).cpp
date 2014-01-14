/*
*	acm practice week1
*	examiner : park sang hyun
*	resolver : kong ji yeon
*	date : 2013.12.30
*/
#include<stdio.h>
#include<stdlib.h>
struct point{	// 배열 좌표 잡는 구조체 정의
	int i;
	int j;
};
int K;	//energy count
char sum;	//save y or n
void gotoload(char (**board),char (**test),struct point robot,int M,int N);	//함수의 원형 정의
int main(int argc,char* argv[])
{	
	int T;	// test case number
	int M,N;	//m x n 행렬 [doesn`t change]
	char **board;	//보드판 정의
	char **test;	//test board (원본 보드를 건드릴수 없으니 test보드를 만든다.)
	char *answer;	//결과값 배열
	int i,j;		//반복제어 
	int key=0;		//answer배열 첨자용
	//-----------file i.o---------
	FILE *fp=NULL;
	fp=stdin;	//fopen(argv[2],"r");
	//----------------------------
	fscanf(fp,"%d",&T);	//test case input
	answer=(char*)malloc(sizeof(char*)*T);	
	while(T>0)	
	{
		sum='n';
		fscanf(fp,"%d",&K);	//energy input
		fscanf(fp,"%d%d",&M,&N);	//m x n input
		board=(char**)calloc(sizeof(char**),M);	//board와 test를 2차원 배열로 동적할당
		test=(char**)calloc(sizeof(char**),M);
		for(i=0;i<N;i++)
		{
			board[i]=(char*)calloc(sizeof(char*),N);
			test[i]=(char*)calloc(sizeof(char*),N);
		}
		//--------------made m x n board----------보드 판을 만든다.
		for(i=0;i<N;i++)
		{
			for(j=0;j<M;j++)
			{
				fscanf(fp,"%s",&board[i][j]);	//보드 입력
				test[i][j]='o';	//테스트보드를 모두 'o'으로 만든다.
			}
		}
		//-------find s , t --------	시작 점을 찾는다.
		struct point robot={-1,-1};	//로봇 구조체 정의
		for(i=0;i<M;i++)
		{
			for(j=0;j<N;j++)
			{
				if(board[i][j]=='s')
				{
					robot.i=i;
					robot.j=j;
				}
			}
			if(robot.i!=-1)	//찾았으면 반복문 종료
				break;
		}
		//--------------------
		test[robot.i][robot.j]='x';	//시작점을 x로 만든다.
		gotoload(board,test,robot,M,N);	//재귀함수 인자로 전달
		answer[key]=sum;	//결과값을 answer배열에 전달
		key++;
		T--;
		if(board!=NULL){	//할당 해제
			free(board);
			board=NULL;
		}
		if(test!=NULL){
			free(test);
			test=NULL;
		}
	}
	printf("---------------------------\n");
	for(i=0;i<key;i++)
		printf("%c\n",answer[i]);

	if(answer!=NULL){
		free(answer);
		answer=NULL;
	}
}
void gotoload(char (**board),char (**test),struct point robot,int M,int N)	// y n을 계산하여 구하는 재귀함수
{
	if(sum=='y')	//sum 이 y일경우 더이상 계산할 필요가 없다.
		return ;
	/*UP*/
	if(
		(robot.i-1>=0) &&	// 0 미만의 배열로는 들어갈수 없다.(무조건 참이여야함)
		(((board[robot.i-1][robot.j]=='.' || board[robot.i-1][robot.j]=='t') &&	(test[robot.i-1][robot.j]!='x'))
		/*     가려는 곳이 . 이나 t이면 갈수있다.	                                 x 표시 된곳은 지나왓던길이기 떄문에 가지 않는다.*/
		|| (K>0 && board[robot.i-1][robot.j]=='*'))
		/*또는 K(에너지)가 존재하면서 보드판이 *이면 뚫고 들어갈수 있다.*/
		)
	{
		if(board[robot.i-1][robot.j]=='*')	//만일 가려는곳이 *이면, 즉 장애물을 부쉇으면
			K--;		//에너지 감소

		test[robot.i][robot.j]='x';	//이전에 있엇던곳에 x표시를 한다.

		robot.i-=1;	// 로봇의 위치를 움직인다.
		if(board[robot.i][robot.j]=='t')
		{
			/*로봇의 위치가 t이면 sum을 y로 바꾸고 함수를 종료한다.*/
			sum='y';
			return ;
		}
		gotoload(board,test,robot,M,N);	//로봇의 위치와 보드(배열) 을 재귀함수로 전달
		test[robot.i][robot.j]='o';	//재귀가 풀리면서 x친곳을 o로 바꾼다.
		robot.i+=1;	//로봇의 위치를 원위치 시킨다.

		if(board[robot.i-1][robot.j]=='*')	// 원래 있엇던곳이 * 이면 재귀가 풀리면서
			K++;	//다시 계산하기위해 에너지를 복구한다.
	}
	if(sum=='y')	
		return ;
	// 주석 설명 이하 동일
	//-----------------------------------------------------------------------------------------------
	/*DOWN*/
	if(
		(robot.i+1<N) &&	// N이상의 배열로는 들어갈수 없다.
		(((board[robot.i+1][robot.j]=='.' || board[robot.i+1][robot.j]=='t') &&
		(test[robot.i+1][robot.j]!='x'))
		|| (K>0 && board[robot.i+1][robot.j]=='*'))
		)
	{
		if(board[robot.i+1][robot.j]=='*')
			K--;
		test[robot.i][robot.j]='x';	

		robot.i+=1;	
		if(board[robot.i][robot.j]=='t')
		{
			sum='y';
			return ;
		}
		gotoload(board,test,robot,M,N);	
		test[robot.i][robot.j]='o';	
		robot.i-=1;

		if(board[robot.i+1][robot.j]=='*')
			K++;
	}
	if(sum=='y')	
		return ;
	//-----------------------------------------------------------------------------------------------
	/*LEFT*/
	if(
		(robot.j-1>=0) &&	//0미만의 배열로는 들어갈수 없다.
		(((board[robot.i][robot.j-1]=='.' || board[robot.i][robot.j-1]=='t') &&
		(test[robot.i][robot.j-1]!='x'))
		|| (K>0 && board[robot.i][robot.j-1]=='*'))
		)
	{
		if(board[robot.i][robot.j-1]=='*')
			K--;
		test[robot.i][robot.j]='x';	

		robot.j-=1;	
		if(board[robot.i][robot.j]=='t')
		{
			sum='y';
			return ;
		}
		gotoload(board,test,robot,M,N);	
		test[robot.i][robot.j]='o';	
		robot.j+=1;

		if(board[robot.i][robot.j-1]=='*')
			K++;
	}
	if(sum=='y')	
		return ;
	//-----------------------------------------------------------------------------------------------
	/*RIGHT*/
	if(
		(robot.j+1<M) &&	//M이상의 배열로는 들어갈수 없다.
		(((board[robot.i][robot.j+1]=='.' || board[robot.i][robot.j+1]=='t') &&
		(test[robot.i][robot.j+1]!='x'))
		|| (K>0 && board[robot.i][robot.j+1]=='*'))
		)
	{
		if(board[robot.i][robot.j+1]=='*')
			K--;
		test[robot.i][robot.j]='x';	

		robot.j+=1;	
		if(board[robot.i][robot.j]=='t')
		{
			sum='y';
			return ;
		}
		gotoload(board,test,robot,M,N);	
		test[robot.i][robot.j]='o';	
		robot.j-=1;

		if(board[robot.i][robot.j+1]=='*')
			K++;
	}
}
