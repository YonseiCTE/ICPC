#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 80
int Test_Num ;
char File_Name [MAX] ;
char Gildong [MAX] ;
char Enemy [MAX] ;

//***************************************************************************************************************************
// main
//***************************************************************************************************************************

int main (void) {

	while ( 1 ) {
		FILE *fptr = NULL ;
		printf ("열고자 하는 파일 이름을 입력 하세요(확장자 포함!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;

		fscanf ( fptr, "%d", &Test_Num ) ;

		for ( int i = 0 ; i < Test_Num ; i++ ) {
			// 길동의 군사를 배치
			fscanf ( fptr, " %c", &Enemy [0] ) ;
			if ( Enemy [0] == 'A' )
				Gildong [0] = 'C' ;
			else if ( Enemy [0] == 'B' )
				Gildong [0] = 'A' ;
			else if ( Enemy [0] == 'C' )
				Gildong [0] = 'B' ;

			int j = 1 ;
			fscanf ( fptr, "%c", &Enemy[j] ) ;
			while ( Enemy [j] != '\n' ) {
				if ( Enemy [j] == 'A' )
					Gildong [j] = 'C' ;
				else if ( Enemy [j] == 'B' )
					Gildong [j] = 'A' ;
				else if ( Enemy [j] == 'C' )
					Gildong [j] = 'B' ;
				j++ ;
				fscanf ( fptr, "%c", &Enemy[j] ) ;
			}
			// 솔루션 출력
			for ( int k = j - 1 ; k >= 0 ; k-- ) {
				if ( k != j - 1 && Gildong [k] == Gildong [k+1] ) {}
				else
					printf ("%c", Gildong [k]) ;
			}
			printf ("\n") ;
		}


		printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
		scanf ("%d", &Test_Num) ;
		fclose (fptr) ;
		if ( Test_Num == 1 )
			break ;
	}

	return 0 ;
}