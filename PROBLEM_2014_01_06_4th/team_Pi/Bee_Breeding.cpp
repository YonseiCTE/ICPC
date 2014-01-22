#include <stdio.h>
#include <math.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 10000
int First_Choice ;
int Second_Choice ;
int Distance ;
int Bee_House [MAX][2] ;
char File_Name [MAX] ;

//***************************************************************************************************************************
// 함수 선언
//***************************************************************************************************************************

void Build_Bee_House () ;
void Calculate_Distance () ;

//***************************************************************************************************************************
// main
//***************************************************************************************************************************

int main (void) {

	// 벌꿀집 초기화
	Build_Bee_House () ;

	while ( 1 ) {
		FILE *fptr = NULL ;
		printf ("열고자 하는 파일 이름을 입력 하세요(확장자 포함!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;

		while ( 1 ) {
			if ( fptr == NULL ) {
				fprintf ( stderr, "그런 파일은 없습니다...\n" ) ;
				break ;
			}

			// 두 벌꿀 집을 입력 받는다.
			fscanf ( fptr, "%d%d", &First_Choice, &Second_Choice ) ;

			// 만약 '0 0'을 만난다면 그 파일의 끝이므로 종료
			if ( First_Choice == 0 && Second_Choice == 0 ) {
				printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
				scanf ("%d", &First_Choice) ;
				fclose (fptr) ;
				break ;
			}
			
			// 두 지점의 거리를 계산
			Calculate_Distance () ;
			// 솔루션 출력
			printf ( "%d\n", Distance ) ;

			// 프로그램이 종료되지 않도록 First_Choice를 '0'으로 지정
			First_Choice = 0 ;
		}

		// 파일의 '0 0' 끝을 만난 후 '1'을 입력했다면 종료
		if ( First_Choice == 1 )
			break ;
	}
	return 0 ;
}

//***************************************************************************************************************************
// Build_Bee_House
//***************************************************************************************************************************

void Build_Bee_House () {
	
	// 기초가 되는 1 ~ 7번 집을 직접 초기화 시킨다.
	Bee_House [1][0] = 0 ;
	Bee_House [1][1] = 0 ;

	Bee_House [2][0] = -2 ;
	Bee_House [2][1] = 0 ;

	Bee_House [3][0] = -1 ;
	Bee_House [3][1] = -1 ;

	Bee_House [4][0] = 1 ;
	Bee_House [4][1] = -1 ;

	Bee_House [5][0] = 2 ;
	Bee_House [5][1] = 0 ;

	Bee_House [6][0] = 1 ;
	Bee_House [6][1] = 1 ;

	Bee_House [7][0] = -1 ;
	Bee_House [7][1] = 1 ;

	int Move_Num = 1 ;
	int Flag = 0 ;

	// idea.txt를 참고 하세요
	// 규칙을 따라 모든 집을 초기화 시킨다.
	for ( int i = 8 ; i <= MAX ; ) {
		Bee_House [i][0] = Bee_House [i-1][0] - 2 ;
		Bee_House [i][1] = Bee_House [i-1][1] ;
		i++ ;

		for ( int j = 0 ; j < Move_Num ; j++ ) {
			Bee_House [i][0] = Bee_House [i-1][0] - 1 ;
			Bee_House [i][1] = Bee_House [i-1][1] - 1 ;

			if ( i == 10000 ) {
				Flag = 1 ;
				break;
			}

			i++ ;
		}

		if ( Flag == 1 )
			break ;
		Move_Num++ ;

		for ( int j = 0 ; j < Move_Num ; j++ ) {
			Bee_House [i][0] = Bee_House [i-1][0] + 1 ;
			Bee_House [i][1] = Bee_House [i-1][1] - 1 ;

			if ( i == 10000 ) {
				Flag = 1 ;
				break;
			}

			i++ ;
		}

		if ( Flag == 1 )
			break ;

		for ( int j = 0 ; j < Move_Num ; j++ ) {
			Bee_House [i][0] = Bee_House [i-1][0] + 2 ;
			Bee_House [i][1] = Bee_House [i-1][1] ;

			if ( i == 10000 ) {
				Flag = 1 ;
				break;
			}

			i++ ;
		}

		if ( Flag == 1 )
			break ;

		for ( int j = 0 ; j < Move_Num ; j++ ) {
			Bee_House [i][0] = Bee_House [i-1][0] + 1 ;
			Bee_House [i][1] = Bee_House [i-1][1] + 1 ;

			if ( i == 10000 ) {
				Flag = 1 ;
				break;
			}

			i++ ;
		}

		if ( Flag == 1 )
			break ;

		for ( int j = 0 ; j < Move_Num ; j++ ) {
			Bee_House [i][0] = Bee_House [i-1][0] - 1 ;
			Bee_House [i][1] = Bee_House [i-1][1] + 1 ;

			if ( i == 10000 ) {
				Flag = 1 ;
				break;
			}

			i++ ;
		}

		if ( Flag == 1 )
			break ;

		for ( int j = 0 ; j < Move_Num ; j++ ) {
			Bee_House [i][0] = Bee_House [i-1][0] - 2 ;
			Bee_House [i][1] = Bee_House [i-1][1] ;

			if ( i == 10000 ) {
				Flag = 1 ;
				break;
			}

			i++ ;
		}

		if ( Flag == 1 )
			break ;

	}
}

//***************************************************************************************************************************
// Calculate_Distance
//***************************************************************************************************************************

void Calculate_Distance () {

	// 계산 식에 대한 설명은 idea.txt를 참고 하세요
	if ( Bee_House [First_Choice][1] == Bee_House [Second_Choice][1] ) {
		Distance = abs ( Bee_House [First_Choice][0] - Bee_House [Second_Choice][0] ) ;
		Distance /= 2 ;
	}
	else {
		Distance = abs ( Bee_House [First_Choice][1] - Bee_House [Second_Choice][1] ) ;
		Distance += ( abs ( Bee_House [First_Choice][0] - Bee_House [Second_Choice][0] )  - Distance ) / 2 ;
	}
}