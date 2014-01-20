#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 100
int Test_Num ;
int KTX [MAX] ;
int Bypass [2] ;
int Number_KTX ;
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
			fscanf ( fptr, "%d", &Number_KTX ) ;
			Bypass [0] = Bypass [1] = -1 ;
			// 각 등급을 가진 열차의 순서를 데이터화
			for ( int j = 0 ; j < Number_KTX ; j++ ) {
				fscanf ( fptr, "%d", &KTX [j] ) ;
			}
			// 등급 순서대로 목적지 도착이 가능한지 확인
			int first = 1 ;  // 맨 처음 보내야 할 등급의 열차
			int j = 0 ;
			for ( ; j < Number_KTX ; j++ ) {
				// 다음으로 보내야 할 열차라면
				if ( KTX [j] == first ) {
					first++ ;		// 보내버리고 다음 보내야 할 열차로 first에 대입

					// 만약 통로 안에 열차가 있다면
					if ( Bypass [0] != -1 || Bypass [1] != -1 ) {

						// 통로 둘다 열차가 있을 경우
						if ( Bypass [0] != -1 && Bypass [1] != -1 ) {

							// index 0 번째 통로의 열차의 등급이 더 낮을 경우
							if ( Bypass [0] > Bypass [1] ) {

								// index 1 번째 통로의 열차가 다음으로 보내야 할 열차라면
								if ( Bypass [1] == first ) {

									Bypass [1] = -1 ;	// index 1 번째 통로가 비었음을 표시
									first++ ;			// 보내버리고 다음 보내야 할 열차로 first에 대입

									// 만약 index 0 번째 통로의 열차도 다음으로 보내야 할 열차라면
									if ( Bypass [0] == first ) {

										Bypass [0] = -1 ;	// index 0 번째 통로가 비었음을 표시
										first++ ;			// 보내버리고 다음 보내야 할 열차로 first에 대입
									}
								}
							}

							// index 1 번째 통로의 열차의 등급이 더 낮을 경우
							else {

								// index 0 번째 통로의 열차가 다음으로 보내야 할 열차라면
								if ( Bypass [0] == first ) {

									Bypass [0] = -1 ;	// index 0 번째 통로가 비었음을 표시
									first++ ;			// 보내버리고 다음 보내야 할 열차로 first에 대입

									// 만약 index 1 번째 통로의 열차도 다음으로 보내야 할 열차라면
									if ( Bypass [1] == first ) {

										Bypass [1] = -1 ;	// index 1 번째 통로가 비었음을 표시
										first++ ;			// 보내버리고 다음 보내야 할 열차로 first에 대입
									}
								}
							}
						}

						// 통로 index 0 번째만 열차가 있는 경우
						else if ( Bypass [0] != -1 ) {

							// 만약 index 0 번째 안의 열차가 다음으로 보내야 할 열차라면
							if ( Bypass [0] == first ) {

								first++ ;			// 보내버리고 다음 보내야 할 열차로 first에 대입
								Bypass [0] = -1 ;	// index 0 번째 통로가 비었음을 표시
							}
						}

						// 통로 index 1 번째만 열차가 있는 경우
						else {

							// 만약 index 1 번째 통로의 열차가 다음으로 보내야 할 열차라면
							if ( Bypass [1] == first ) {

								first++ ;			// 보내버리고 다음 보내야 할 열차로 first에 대입
								Bypass [1] = -1 ;	// index 1 번째 통로가 비었음을 표시
							}
						}
					}
				}

				// 다음으로 보내야 할 열차가 아니라면
				else {

					// index 0 번째 통로가 비었다면
					if ( Bypass [0] == -1 )
						Bypass [0] = KTX [j] ;		// 그곳에 열차를 이동
					// index 1 번째 통로가 비었다면
					else if ( Bypass [1] == -1 )
						Bypass [1] = KTX [j] ;		// 그곳에 열차를 이동
					// 통로가 꽉 찼다면
					else
						break ;		// 솔루션 해결 불가능!
				}
			}

			// 솔루션 출력
			if ( j == Number_KTX )
				printf ("YES\n") ;
			else
				printf ("NO\n") ;
		}

		printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
		scanf ("%d", &Test_Num) ;
		fclose (fptr) ;
		if ( Test_Num == 1 )
			break ;
	}

	return 0 ;
}