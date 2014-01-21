#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 101
int Test_Num ;
int Wire_Number ;
int Wire_Required ;
int Wire_Length [MAX] ;
int Wire_Price [MAX] ;
int Wire [MAX] ;
int Kind ;
char File_Name [MAX] ;

//***************************************************************************************************************************
// 함수 선언
//***************************************************************************************************************************

void Heap (int price, int length, int size ) ;

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
			// 각 정보들을 데이터화
			fscanf ( fptr, "%d", &Wire_Number ) ;
			Kind = 1 ;
			
			for ( int j = 1 ; j <= Wire_Number ; j++ )
				fscanf ( fptr, "%d", &Wire_Price [j] ) ;
			for ( int j = 1 ; j <= Wire_Number ; j++ )
				fscanf ( fptr, "%d", &Wire_Length [j] ) ;

			fscanf ( fptr, "%d", &Wire_Required ) ;

			// 힙소트를 이용하여 가격을 오름차순으로 정렬
			// 길이 또한 가격의 오름차순을 기준으로 정렬
			for ( int j = 1 ; j <= Wire_Number ; j++ )
				Heap ( Wire_Price [j], Wire_Length [j], j ) ;

			int temp ;
			int Size = Wire_Number ;

			for ( int j = 1 ; j <= Wire_Number - 2 ; j++ ) {
				temp = Wire_Price [Size] ;
				Wire_Price [Size] = Wire_Price [1] ;
				Wire_Price [1] = temp ;
				temp = Wire_Length [Size] ;
				Wire_Length [Size] = Wire_Length [1] ;
				Wire_Length [1] = temp ;
				Size-- ;
				int index = 1 ;

				while ( 1 ) {

					if ( Size == 2 ) {
						if ( Wire_Price [1] > Wire_Price [2] ) {
							temp = Wire_Price [2] ;
							Wire_Price [2] = Wire_Price [1] ;
							Wire_Price [1] = temp ;
							temp = Wire_Length [2] ;
							Wire_Length [2] = Wire_Length [1] ;
							Wire_Length [1] = temp ;
						}
						break ;
					}
					else if ( Wire_Price [index] < Wire_Price [index*2] && Wire_Price [index*2] >= Wire_Price [index*2+1] ) {
						temp = Wire_Price [index*2] ;
						Wire_Price [index*2] = Wire_Price [index] ;
						Wire_Price [index] = temp ;
						temp = Wire_Length [index*2] ;
						Wire_Length [index*2] = Wire_Length [index] ;
						Wire_Length [index] = temp ;
						index *= 2 ;
					}
					else if ( Wire_Price [index] < Wire_Price [index*2+1] && Wire_Price [index*2+1] >= Wire_Price [index*2] ) {
						temp = Wire_Price [index*2+1] ;
						Wire_Price [index*2+1] = Wire_Price [index] ;
						Wire_Price [index] = temp ;
						temp = Wire_Length [index*2+1] ;
						Wire_Length [index*2+1] = Wire_Length [index] ;
						Wire_Length [index] = temp ;
						index *= 2 + 1 ;
					}
					if ( (index*2 >= Size) || ((Wire_Price [index] >= Wire_Price [index*2]) && (Wire_Price [index] >= Wire_Price [index*2+1])) )
						break ;
				}
			}

			int Current_Length = Wire_Length [1] ;
			int Current_Price = Wire_Price [1] ;

			for ( int j = 2 ; j <= Wire_Number ; j++ ) {
				if ( Current_Length >= Wire_Required )
					break ;
				else {
					Current_Length += Wire_Length [j] ;
					Current_Price = Wire_Price [j] ;
				}
			}

			printf ( "%d\n", Current_Price ) ;
		}

		printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
		scanf ("%d", &Test_Num) ;
		fclose (fptr) ;
		if ( Test_Num == 1 )
			break ;
	}

	return 0 ;
}

//***************************************************************************************************************************
// Heap
//***************************************************************************************************************************

void Heap ( int price, int length, int size ) {

	int now = size ;

	while ( now != 1 && Wire_Price [now/2] < price ) {
		Wire_Price [now] = Wire_Price [now/2] ;
		Wire_Length [now] = Wire_Length [now/2] ;
		now /= 2 ;
	}

	Wire_Price [now] = price ;
	Wire_Length [now] = length ;
}