#include <stdio.h>
#include <stdlib.h>

//***********************************************************************
// 전역변수 선언
//***********************************************************************

#define MAX 10000
int Test_Num ;
int Team_Num ;
int Problem_Num ;
int My_Team ;
int Log_Entry ;
int Submit ;
int Team_Log ;
int Problem_Log ;
int Score_Log ;
int My_Rank ;
int Team_Score [MAX] ;
int Team_Submit [MAX] ;
int Team_Problem [MAX][100] ;
int Last_Submit [MAX] ;
char File_Name [MAX] ;

//***********************************************************************
// main
//***********************************************************************

int main (void) {

	FILE *fptr = NULL ;
	while (1) {

		printf ("열고자 하는 파일 이름을 입력 하세요(확장자 포함!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;

		if ( fptr == NULL ) {
			printf ("그런 파일은 없습니다.\n") ;
			exit(1) ;
		}

		fscanf ( fptr, "%d", &Test_Num ) ;

		for ( int i = 0 ; i < Test_Num ; i++ ) {
			fscanf ( fptr, "%d", &Team_Num ) ;
			if ( Team_Num < 3 )
				fprintf ( stderr, "테스트 %d번째 팀의 수가 해당 범위내에 있지 않습니다.", i+1 ) ;
			fscanf ( fptr, "%d", &Problem_Num ) ;
			if ( Problem_Num > 100 )
				fprintf ( stderr, "테스트 %d번째 문제의 수가 해당 범위내에 있지 않습니다.", i+1 ) ;
			fscanf ( fptr, "%d", &My_Team ) ;
			if ( My_Team > Team_Num )
				fprintf ( stderr, "테스트 %d번째 당신의 팀 ID는 해당 범위내에 있지 않습니다.", i+1 ) ;
			fscanf ( fptr, "%d", &Log_Entry ) ;
			if ( Log_Entry < 3 || Log_Entry > 10000 )
				fprintf ( stderr, "테스트 %d번째 로그 엔트리의 수가 해당 범위내에 있지 않습니다.\n", i+1 ) ;

			// 모든 팀의 최종 점수 & 각 문제 당 점수 & 제출 개수 & 마지막 제출 순위를 '0'으로 초기화
			for ( int j = 0 ; j < Team_Num ; j++ ) {
				Team_Score [j] = 0 ;
				Team_Submit [j] = 0 ;
				Last_Submit [j] = 0 ;
				for ( int k = 0 ; k < Problem_Num ; k++ )
					Team_Problem [j][k] = 0 ;
			}
			// 각 로그의 정보를 데이터화
			for ( int j = 0 ; j < Log_Entry ; j++ ) {
				Submit = j + 1 ;
				fscanf ( fptr, "%d", &Team_Log ) ;
				fscanf ( fptr, "%d", &Problem_Log ) ;
				fscanf ( fptr, "%d", &Score_Log ) ;
				if ( Team_Problem [Team_Log-1][Problem_Log-1] < Score_Log )
					Team_Problem [Team_Log-1][Problem_Log-1] = Score_Log ;
				Team_Submit [Team_Log-1] += 1 ;
				Last_Submit [Team_Log-1] = Submit ;
			}
			// 각 팀의 최종 점수를 데이터화
			for ( int j = 0 ; j < Team_Num ; j++ ) {
				for ( int k = 0 ; k < Problem_Num ; k++ )
					Team_Score [j] += Team_Problem [j][k] ;
			}
			// 사용자의 팀 순위 계산
			My_Rank = Team_Num ;						// 순위를 꼴찌로 초기화
			// 한번 이상 문제를 풀었을 경우 순위 계산
			if ( Last_Submit [My_Team-1] != 0 ) {
				for ( int j = 0 ; j < Team_Num ; j++ ) {
					// 자신의 팀과 만나면 jump
					if ( j == My_Team-1 ) {}
					else {
						// 상대 팀보다 점수가 높으면 '1'순위 증가
						if ( Team_Score [j] < Team_Score [My_Team - 1] )
							My_Rank-- ;
						// 상대 팀과 점수가 같다면
						else if ( Team_Score [j] == Team_Score [My_Team - 1] ) {
							// 제출한 프로젝트가 적을시 '1'순위 증가
							if ( Team_Submit [j] > Team_Submit [My_Team - 1] )
								My_Rank-- ;
							// 제출한 프로젝트가 같다면
							else if ( Team_Submit [j] == Team_Submit [My_Team - 1] ) {
								// 마지막에 제출한 순서가 더 작을시 '1'순위 증가
								if ( Last_Submit [j] > Last_Submit [My_Team - 1] )
									My_Rank-- ;
							}
						}
					}
				}
				// 팀의 순위 출력
				printf ("%d\n", My_Rank) ;
			}
			// 한 문제도 제출 하지 않았을 경우 무조건 꼴찌로 출력
			else {
				printf ("%d\n", My_Rank) ;
			}
		}

		printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
		scanf ("%d", &Team_Num) ;
		fclose (fptr) ;
		if ( Team_Num == 1)
			break ;

	}

	return 0 ;
}