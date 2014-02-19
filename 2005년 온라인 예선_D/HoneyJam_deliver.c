/*******
*	acm_deliver_problem
*	resolver : kong ji yeon
*	date : 2014.2.20
*	comment : 
*******/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct _location{
	int x;
	int y;
}Location;
void Input(int *T,int **N,Location ***guest);
int* Calculate(int T,int *N,Location **guest);
void Output(int *answer,int T);
int main(int argc,char* argv[]){
	int T;	//test case
	int *N;	//guest count
	Location **guest;	//guest
	int *answer;	//answer
	Input(&T,&N,&guest);
	answer=Calculate(T,N,guest);
	Output(answer,T);
	return 0;
}
void Input(int *T,int **N,Location ***guest){
	int i,j;	//for loop control
	FILE *fp;
	char filename[80];
	scanf("%s",filename);
	fp=fopen(filename,"r");
	fscanf(fp,"%d",T);
	*N=(int*)calloc(*T,sizeof(int));
	*guest=(Location**)calloc(*T,sizeof(Location*));
	for(i=0;i<*T;i++){
		fscanf(fp,"%d",*N+i);
		*((*guest)+i)=(Location*)calloc(*(*N+i)+1,sizeof(Location));
		for(j=0;j<*(*N+i)+1;j++){
			fscanf(fp,"%d %d",&(*(*guest+i)+j)->x,&(*(*guest+i)+j)->y);
		}
	}
	fclose(fp);
}
int* Calculate(int T,int *N,Location **guest){
	int i,j,k;		//for loop control
	int *answer;	//answer
	Location startLocation;	//new start location
	Location north,south,east,west;	//near location
	int distance[4];	//The distance close to location()
	int minDistance;	//min distance
	int distanceSum;	//distance sum -> answer
	int close[2];		
	Location temp[2];	
	int index;
	answer=(int*)calloc(T,sizeof(int));
	for(i=0;i<T;i++){
		startLocation=*(*(guest+i));
		distanceSum=0;
		for(j=0;j<*(N+i);j++){
			north.x=(*(guest+i)+(j+1))->x;
			north.y=(*(guest+i)+(j+1))->y+1;
			south.x=(*(guest+i)+(j+1))->x;
			south.y=(*(guest+i)+(j+1))->y-1;
			east.x=(*(guest+i)+(j+1))->x+1;
			east.y=(*(guest+i)+(j+1))->y;
			west.x=(*(guest+i)+(j+1))->x-1;
			west.y=(*(guest+i)+(j+1))->y;
			distance[0]=(int)fabs((double)startLocation.x-north.x)+(int)fabs((double)startLocation.y-north.y);
			distance[1]=(int)fabs((double)startLocation.x-south.x)+(int)fabs((double)startLocation.y-south.y);
			distance[2]=(int)fabs((double)startLocation.x-east.x)+(int)fabs((double)startLocation.y-east.y);
			distance[3]=(int)fabs((double)startLocation.x-west.x)+(int)fabs((double)startLocation.y-west.y);
			minDistance=distance[0];
			for(k=0;k<4;k++){
				if(minDistance>distance[k]){
					minDistance=distance[k];
				}
			}
			distanceSum+=minDistance;
			index=0;
			for(k=0;k<4;k++){
				if(minDistance==distance[k]){
					switch(k){
					case 0:*(temp+index)=north;index++;break;
					case 1:*(temp+index)=south;index++;break;
					case 2:*(temp+index)=east;index++;break;
					case 3:*(temp+index)=west;index++;break;
					default:break;
					}
				}
			}
			*(close+0)=(int)fabs((double)guest[i][j+2].x-temp[0].x)+(int)fabs((double)guest[i][j+2].y-temp[0].y);
			*(close+1)=(int)fabs((double)guest[i][j+2].x-temp[1].x)+(int)fabs((double)guest[i][j+2].y-temp[1].y);
			startLocation=temp[0];
			if(close[0]>close[1] && index==2){
				startLocation=temp[1];
			}
		}
		answer[i]=distanceSum;
		if(*(guest+i)=NULL){
			free(*(guest+i));
			*(guest+i)=NULL;
		}
	}
	if(guest!=NULL){
		free(guest);
		guest=NULL;
	}
	if(N!=NULL){
		free(N);
		N=NULL;
	}
	return answer;
}
void Output(int *answer,int T){
	int i;
	for(i=0;i<T;i++){
		printf("%d\n",*(answer+i));
	}
	if(answer!=NULL){
		free(answer);
		answer=NULL;
	}
}
