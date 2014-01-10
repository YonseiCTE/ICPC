#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 100
int Test_Num ;
int Delivery_Num ;
int Dummy_M ;
int Dummy_N ;
int Distance ;
int top ;
int Delivery [MAX + 1][4] ;
int Stack [MAX * 2] ;
char File_Name [MAX] ;

//***************************************************************************************************************************
// 함수 선언
//***************************************************************************************************************************

void Change_Next_Coordinate (int j) ;
void Change_Current_Next_Coordinate ( int j, int k ) ;
void push ( int token ) ;
int pop () ;

//***************************************************************************************************************************
// main
//***************************************************************************************************************************

int main (void) {

	while (1) {
		FILE *fptr = NULL ;
		printf ("열고자 하는 파일 이름을 입력 하세요(확장자 포함!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;

		if ( fptr == NULL ) {
			printf ("그런 파일은 없습니다.\n") ;
			exit(1) ;
		}
		fscanf ( fptr, "%d", &Test_Num ) ;

		for ( int i = 0 ; i < Test_Num ; i++ ) {
			fscanf ( fptr, "%d", &Delivery_Num ) ;
			fscanf ( fptr, "%d", &Delivery [MAX][0] ) ;
			fscanf ( fptr, "%d", &Delivery [MAX][1] ) ;
			top = -1 ;

			for ( int j = 0 ; j < Delivery_Num ; j++ ) {
				fscanf ( fptr, "%d", &Delivery[j][0] ) ;
				fscanf ( fptr, "%d", &Delivery[j][1] ) ;
				Delivery [j][2] = -1 ;
				Delivery [j][3] = -1 ;
			}

			int Change_Flag = 0 ;
			// 첫 번째 배달지와 두 번째 배달지를 비교 한다.
			// 같을 경우
			if ( Delivery [0][0] == Delivery [1][0] && Delivery [0][1] == Delivery [1][1] ) {
				push (0) ;
				Change_Flag = 1 ;
			}
			// 다를 경우
			else
				Change_Current_Next_Coordinate (0, 1) ;

			for ( int j = 1 ; j < Delivery_Num - 1 ; j++ ) {
				if ( Change_Flag ) {
					if ( Delivery [j][0] == Delivery [j+1][0] && Delivery [j][1] == Delivery [j+1][1] ) {
						push (j) ;

						if ( j == Delivery_Num - 2 ) {
							if ( top == Delivery_Num - 2 ) {
								push ( Delivery [MAX][0] ) ;
								push ( Delivery [MAX][1] ) ;
								Change_Current_Next_Coordinate ( MAX, j ) ;
								Delivery [MAX][1] = pop () ;
								Delivery [MAX][0] = pop () ;
								Delivery [j+1][0] = Delivery [j][0] ;
								Delivery [j+1][1] = Delivery [j][1] ;
								while ( top > -1 ) {
									Change_Flag = pop () ;
									Delivery [Change_Flag][0] = Delivery [j][0] ;
									Delivery [Change_Flag][1] = Delivery [j][1] ;
								}
							}
						}
					}
					else {
						Change_Current_Next_Coordinate ( j, j+1 ) ;
						if ( j == Delivery_Num - 2 ) {
							if ( Delivery [j][2] != -1 ) {
								int distance1 = abs ( Delivery [MAX][0] - Delivery [j+1][0] ) + abs ( Delivery [MAX][1] - Delivery [j+1][1] ) ;
								int distance2 = abs ( Delivery [MAX][0] - Delivery [j+1][2] ) + abs ( Delivery [MAX][1] - Delivery [j+1][3] ) ;

								if ( distance1 > distance2 ) {
									Delivery [j+1][0] = Delivery [j+1][2] ;
									Delivery [j+1][1] = Delivery [j+1][3] ;
								}

								distance1 = abs ( Delivery [j][0] - Delivery [j+1][0] ) + abs ( Delivery [j][1] - Delivery [j+1][1] ) ;
								distance2 = abs ( Delivery [j][2] - Delivery [j+1][0] ) + abs ( Delivery [j][3] - Delivery [j+1][1] ) ;

								if ( distance1 > distance2 ) {
									Delivery [j][0] = Delivery [j][2] ;
									Delivery [j][1] = Delivery [j][3] ;
								}
							}
							while ( top > -1 ) {
								Change_Flag = pop () ;
								Delivery [Change_Flag][0] = Delivery [j][0] ;
								Delivery [Change_Flag][1] = Delivery [j][1] ;
							}
						}
						Change_Flag = 0 ;
					}
				}
				else {
					if ( Delivery [j][2] == -1 ) {
						Change_Next_Coordinate (j) ;
					}
					else {
						int distance1 = abs ( Delivery [j][0] - Delivery [j+1][0] ) + abs ( Delivery [j][1] - Delivery [j+1][1] ) ;
						int distance2 = abs ( Delivery [j][2] - Delivery [j+1][0] ) + abs ( Delivery [j][3] - Delivery [j+1][1] ) ;

						if ( distance1 > distance2 ) {
							Delivery [j][0] = Delivery [j][2] ;
							Delivery [j][1] = Delivery [j][3] ;
						}
						if ( Delivery [j-1][2] != -1 ) {
							distance1 = abs ( Delivery [j-1][0] - Delivery [j][0] ) + abs ( Delivery [j-1][1] - Delivery [j][1] ) ;
							distance2 = abs ( Delivery [j-1][2] - Delivery [j][0] ) + abs ( Delivery [j-1][3] - Delivery [j][1] ) ;
							if ( distance1 > distance2 ) {
								Delivery [j-1][0] = Delivery [j-1][2] ;
								Delivery [j-1][1] = Delivery [j-1][3] ;
							}
						}
						while ( top > -1 ) {
							distance1 = pop () ;
							Delivery [distance1][0] = Delivery [j-1][0] ;
							Delivery [distance1][1] = Delivery [j-1][1] ;
						}
						Change_Next_Coordinate (j) ;
					}
				}
			}

			Distance = abs ( Delivery [MAX][0] - Delivery [0][0] ) + abs ( Delivery [MAX][1] - Delivery [0][1] ) ;
			for ( int j = 1 ; j < Delivery_Num ; j++ )
				Distance += abs ( Delivery [j-1][0] - Delivery [j][0] ) + abs ( Delivery [j-1][1] - Delivery [j][1] ) ;

			printf ( "%d\n", Distance ) ;
		}

		fclose (fptr) ;

		printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
		scanf ("%d", &top) ;
		fclose (fptr) ;
		if ( top == 1)
			break ;
	}

	return 0 ;
}

//***************************************************************************************************************************
// Change_Next_Coordinate
//***************************************************************************************************************************

void Change_Next_Coordinate (int j) {
	// 거리가 '1'일 경우
	if ( abs (Delivery [j][0] - Delivery [j+1][0]) + abs (Delivery [j][1] - Delivery [j+1][1]) == 1 ) {
		if ( Delivery [j][0] == Delivery [j+1][0] ) {
			if ( Delivery [j][1] > Delivery [j+1][1] )
				Delivery [j+1][1] += 1 ;
			else
				Delivery [j+1][1] -= 1 ;
		}
		else {
			if ( Delivery [j][0] > Delivery [j+1][0] )
				Delivery [j+1][0] += 1 ;
			else
				Delivery [j+1][0] -= 1 ;
		}
	}
	// 거리가 '2' 이상일 경우
	else {
		if ( Delivery [j][0] == Delivery [j+1][0] ) {
			if ( Delivery [j][1] > Delivery [j+1][1] )
				Delivery [j+1][1] += 1 ;
			else
				Delivery [j+1][1] -= 1 ;
		}
		else if ( Delivery [j][1] == Delivery [j+1][1] ) {
			if ( Delivery [j][0] > Delivery [j+1][0] )
				Delivery [j+1][0] += 1 ;
			else
				Delivery [j+1][0] -= 1 ;
		}
		else {
			if (Delivery [j][0] > Delivery [j+1][0]) {
				Delivery [j+1][2] = Delivery [j+1][0] + 1 ;
				Delivery [j+1][3] = Delivery [j+1][1] ;
				if ( Delivery [j][1] > Delivery [j+1][1] )
					Delivery [j+1][1] += 1 ;
				else
					Delivery [j+1][1] -= 1 ;
			}
			else {
				Delivery [j+1][2] = Delivery [j+1][0] - 1 ;
				Delivery [j+1][3] = Delivery [j+1][1] ;
				if ( Delivery [j][1] > Delivery [j+1][1] )
					Delivery [j+1][1] += 1 ;
				else
					Delivery [j+1][1] -= 1 ;
			}
		}
	}
}

//***************************************************************************************************************************
// Change_Current_Next_Coordinate
//***************************************************************************************************************************

void Change_Current_Next_Coordinate ( int j, int k ) {
	// 거리가 '1'일 경우
	if ( abs (Delivery [j][0] - Delivery [k][0]) + abs (Delivery [j][1] - Delivery [k][1]) == 1 ) {
		Delivery [j][2] = Delivery [k][0] ;
		Delivery [j][3] = Delivery [k][1] ;
		Delivery [k][2] = Delivery [j][0] ;
		Delivery [k][3] = Delivery [j][1] ;
	}
	// 거리가 '2'일 경우
	else if ( abs (Delivery [j][0] - Delivery [k][0]) + abs (Delivery [j][1] - Delivery [k][1]) == 2 ) {
		if ( Delivery [j][0] == Delivery [k][0] ) {
			if ( Delivery [j][1] > Delivery [k][1] ) {
				Delivery [j][1] = Delivery [k][1] + 1 ;
				Delivery [k][1] = Delivery [k][1] + 1 ;
			}
			else {
				Delivery [k][1] = Delivery [j][1] + 1 ;
				Delivery [j][1] = Delivery [j][1] + 1 ;
			}
		}
		else if ( Delivery [j][1] == Delivery [k][1] ) {
			if ( Delivery [j][0] > Delivery [k][0] ) {
				Delivery [j][0] = Delivery [k][0] + 1 ;
				Delivery [k][0] = Delivery [k][0] + 1 ;
			}
			else {
				Delivery [k][0] = Delivery [j][0] + 1 ;
				Delivery [j][0] = Delivery [j][0] + 1 ;
			}
		}
		else {
			push (Delivery [j][1]) ;
			Delivery [j][1] = Delivery [k][1] ;
			push (Delivery [k][0]) ;
			Delivery [k][0] = Delivery [j][0] ;
			Delivery [j][2] = pop () ;
			Delivery [j][3] = pop () ;
			top += 2 ;
			Delivery [k][2] = pop () ;
			Delivery [k][3] = pop () ;
		}
	}
	// 거리가 '3' 이상일 경우
	else {
		if ( Delivery [j][0] == Delivery [k][0] ) {
			if ( Delivery [j][1] > Delivery [k][1] ) {
				Delivery [j][1] -= 1 ;
				Delivery [k][1] += 1 ;
			}
			else {
				Delivery [j][1] += 1 ;
				Delivery [k][1] -= 1 ;
			}
		}
		else if ( Delivery [j][1] == Delivery [k][1] ) {
			if ( Delivery [j][0] > Delivery [k][0] ) {
				Delivery [j][0] -= 1 ;
				Delivery [k][0] += 1 ;
			}
			else {
				Delivery [j][0] += 1 ;
				Delivery [k][0] -= 1 ;
			}
		}
		else {
			if (Delivery [j][0] > Delivery [k][0]) {
				Delivery [j][2] = Delivery [j][0] - 1 ;
				Delivery [j][3] = Delivery [j][1] ;
				push ( Delivery [j][1] ) ;
				if ( Delivery [j][1] > Delivery [k][1] )
					Delivery [j][1] -= 1 ;
				else
					Delivery [j][1] += 1 ;
				Delivery [k][2] = Delivery [k][0] + 1 ;
				Delivery [k][3] = Delivery [k][1] ;
				if ( pop () > Delivery [k][1] )
					Delivery [k][1] += 1 ;
				else
					Delivery [k][1] -= 1 ;
			}
			else {
				Delivery [j][2] = Delivery [j][0] + 1 ;
				Delivery [j][3] = Delivery [j][1] ;
				push ( Delivery [j][1] ) ;
				if ( Delivery [j][1] > Delivery [k][1] )
					Delivery [j][1] -= 1 ;
				else
					Delivery [j][1] += 1 ;
				Delivery [k][2] = Delivery [k][0] - 1 ;
				Delivery [k][3] = Delivery [k][1] ;
				if ( pop () > Delivery [k][1] )
					Delivery [k][1] += 1 ;
				else
					Delivery [k][1] -= 1 ;
			}
		}
	}
}

//***************************************************************************************************************************
// push
//***************************************************************************************************************************

void push ( int token ) {
	if ( top >= MAX * 2 ) {
		fprintf (stderr, "Push error!!\n") ;
		exit (1) ;
	}

	Stack [++top] = token ;
}

//***************************************************************************************************************************
// pop
//***************************************************************************************************************************

int pop () {
	if ( top < 0 ) {
		fprintf (stderr, "Pop error!!\n" ) ;
		exit (2) ;
	}

	return Stack [top--] ;
}