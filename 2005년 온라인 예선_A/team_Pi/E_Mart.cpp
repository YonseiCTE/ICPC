#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 100000
int Test_Num ;
int Kind ;
int Weight [MAX] ;
int Cost [MAX] ;
int Choice_Price ;
double Efficient_Marchandise [MAX] ;
char File_Name [MAX] ;

//***************************************************************************************************************************
// main
//***************************************************************************************************************************

int main (void) {

	while ( 1 ) {
		FILE *fptr = NULL ;
		printf ("열고자 하는 파일 이름을 입력 하세요(확장자 포함!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;
		if ( fptr == NULL ) {
			fprintf ( stderr, "그런 파일은 없습니다.\n" ) ;
			exit (1) ;
		}

		fscanf ( fptr, "%d", &Test_Num ) ;

		for ( int i = 0 ; i < Test_Num ; i++ ) {
			fscanf ( fptr, "%d", &Kind ) ;
			
			// 맛살 종류마다 무게, 가격을 데이터화
			for ( int j = 0 ; j < Kind ; j++ ) {
				fscanf ( fptr, "%d", &Weight [j] ) ;
				fscanf ( fptr, "%d", &Cost [j] ) ;
			}
			// 각 맛살마다 효율성을 데이터화
			for ( int j = 0 ; j < Kind ; j++ )
				Efficient_Marchandise [j] =  ((double) Cost [j]) /  ((double) Weight [j]) ;
			// 가장 효율적인 가격의 맛살을 찾는다.
			int k = 0 ;
			Choice_Price = Cost [k] ;
			for ( int j = 0 ; j < Kind - 1 ; j++ ) {
				if ( Efficient_Marchandise [k] > Efficient_Marchandise [j+1] ) {
					Choice_Price = Cost [j+1] ;
					k = j+1 ;
				}
				else if ( Efficient_Marchandise [k] == Efficient_Marchandise [j+1] ) {
					if ( Cost [k] > Cost [j+1] ) {
						Choice_Price = Cost [j+1] ;
						k = j+1 ;
					}
				}
			}
			// 솔루션 출력
			printf ( "%d\n", Choice_Price ) ;

		}

		printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
		scanf ("%d", &Test_Num) ;
		fclose (fptr) ;
		if ( Test_Num == 1 )
			break ;
	}
	return 0 ;
}