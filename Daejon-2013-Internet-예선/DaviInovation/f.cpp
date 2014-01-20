#include <iostream>

typedef struct _yo // 팀 정보
{
	int p_point[100];
	int logs;
	int total;
	int last;
}Teams;

using namespace std;

int main(void)
{
	int count;
	Teams Team[100];
	cin >> count;
	
	for (int i=0;i<count;i++)
	{
		int n = 0,k = 0,t = 0,m = 0; // 카운트 위한 변수
		int temp_ID=0,temp_j=0,temp_s=0;
		cin >> n >> k >> t >> m;
		
		int rank=n;
			
		for (int j=0;j<n;j++)
		{
			Team[j].logs=0; //로그 개수 초기화
			Team[j].last=0;
			for(int number = 0;number<k;number++) //문제 점수 초기화
			{
				Team[j].p_point[number]=0;
			}
		}
		
		for (int j=0;j<m;j++)
		{
			cin >> temp_ID >> temp_j >> temp_s;
			Team[temp_ID-1].logs++;
			
			if(Team[temp_ID-1].p_point[temp_j-1] < temp_s)
				Team[temp_ID-1].p_point[temp_j-1] = temp_s;
			
			Team[temp_ID-1].last=j;
		}
		
		for(int j=0;j<n;j++) //calculate total point
		{
			int temp_total=0;
			
			for (int l=0;l<k;l++)
			{
				temp_total+=Team[j].p_point[l];
			}
			
			Team[j].total=temp_total;
		}
		
		for (int j=0;j<n;j++) //find my rank
		{
			if(j==(t-1)) //if checking myself. pass it
				continue;
			
			else
			{
				if (Team[t-1].total>Team[j].total)
				{
					rank--;
				}
				
				else if (Team[t-1].total==Team[j].total)
				{
					if(Team[t-1].logs<Team[j].logs)
					{
						rank--;
					}
					
					else if(Team[t-1].logs== Team[j].logs)
					{
						if (Team[t-1].last<Team[j].last)
						{
							rank--;
						}
					}
				}
			}
			
		}
		
		cout <<rank<<endl;
	}
	
	return 0;
}