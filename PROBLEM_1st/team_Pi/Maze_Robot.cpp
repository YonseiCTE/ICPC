#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 502
int Test_Num ;
int S_M ;
int S_N ;
int T_M ;
int T_N ;
int Map_M ;
int Map_N ;
int energy ;
int Current_M ;
int Current_N ;
int Stack_M [500 * 500] ;
int Stack_N [500 * 500] ;
int top ;
int have_energy [MAX][MAX] ;
char Maze_Map [MAX][MAX] ;
char Go_Where [MAX][MAX] ;
char File_Name [MAX] ;

//***************************************************************************************************************************
// 함수 선언
//***************************************************************************************************************************

int Path_Check () ;
int Break_Wall () ;
void push () ;
int pop_M () ;
int pop_N () ;

//***************************************************************************************************************************
// main
//***************************************************************************************************************************

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
		fscanf ( fptr, "%d", &energy ) ;
		fscanf ( fptr, "%d", &Map_M ) ;
		fscanf ( fptr, "%d", &Map_N ) ;
		top = -1 ;

		// Copy Maze_Map & Setting
		for ( int j = 0 ; j <= Map_M + 1 ; j++ ) {
			Maze_Map [j][0] = '=' ;
			Maze_Map [j][Map_N + 1] = '=' ;
		}
		for ( int j = 1 ; j <= Map_N ; j++ ) {
			Maze_Map [0][j] = '=' ;
			Maze_Map [Map_M + 1][j] = '=' ;
		}
		for ( int j = 1 ; j <= Map_M ; j++ ) {
			for ( int k = 1 ; k <=Map_N ; k++ ) {
				fscanf ( fptr, " %c", &Maze_Map [j][k] ) ;
				have_energy [j][k] = -1 ;

				if ( Maze_Map [j][k] == 'S' ) {
					S_M = j ;
					S_N = k ;
					Current_M = S_M ;
					Current_N = S_N ;
					have_energy [j][k] = energy ;
				}
				else if ( Maze_Map [j][k] == 'T' ) {
					T_M = j ;
					T_N = k ;
				}
			}
		}

		// Find path & stdout "y" or "n"
		while (1) {

			if ( abs (T_M - Current_M) + abs (T_N - Current_N) - 1 <= energy ) {
				printf ("y\n") ;
				break ;
			}

			if ( Path_Check () ) {
				if ( Go_Where [Current_M][Current_N] == 'E' ) {
					push () ;
					have_energy [Current_M][Current_N+1] = have_energy [Current_M][Current_N] ;
					Current_N++ ;
				}
				else if ( Go_Where [Current_M][Current_N] == 'S' ) {
					push () ;
					have_energy [Current_M+1][Current_N] = have_energy [Current_M][Current_N] ;
					Current_M++ ;
				}
				else if ( Go_Where [Current_M][Current_N] == 'W' ) {
					push () ;
					have_energy [Current_M][Current_N-1] = have_energy [Current_M][Current_N] ;
					Current_N-- ;
				}
				else if ( Go_Where [Current_M][Current_N] == 'N' ) {
					push () ;
					have_energy [Current_M-1][Current_N] = have_energy [Current_M][Current_N] ;
					Current_M-- ;
				}
			}
			else {

				if ( !Break_Wall () ) {
					if ( top == -1 ) {
						printf ("n\n") ;
						break ;
					}
					Current_M = pop_M () ;
					Current_N = pop_N () ;
					energy = have_energy [Current_M][Current_N] ;
				}
			}
		}
	}

	printf ("종료하시려면 '1'을 입력하세요 (계속 하려면 아무 키나 누르시오)\n") ;
	scanf ("%d", &top) ;
	fclose (fptr) ;
	if ( top == 1)
		break ;
	}
	return 0 ;
}

//***************************************************************************************************************************
// Path_Check
//***************************************************************************************************************************

int Path_Check () {

	// Search
	//*******************************************************************************************************************
	// 동쪽 길이 열려 있는 경우
	//*******************************************************************************************************************

	if ( Maze_Map [Current_M][Current_N+1] == '.' ) {
		if ( have_energy [Current_M][Current_N+1] < have_energy [Current_M][Current_N] ) {
			Go_Where [Current_M][Current_N] = 'E' ;
			return 1 ;
		}
	} // if 'E'

	//*******************************************************************************************************************
	// 남쪽 길이 열려 있는 경우
	//*******************************************************************************************************************

	if ( Maze_Map [Current_M+1][Current_N] == '.' ) {
		if ( have_energy [Current_M+1][Current_N] < have_energy [Current_M][Current_N] ) {
			Go_Where [Current_M][Current_N] = 'S' ;
			return 1 ;
		}
	} // if 'S'

	//*******************************************************************************************************************
	// 서쪽 길이 열려 있는 경우
	//*******************************************************************************************************************

	if ( Maze_Map [Current_M][Current_N-1] == '.' ) {
		if ( have_energy [Current_M][Current_N-1] < have_energy [Current_M][Current_N] ) {
			Go_Where [Current_M][Current_N] = 'W' ;
			return 1 ;
		}
	} // if 'W'

	//*******************************************************************************************************************
	// 북쪽 길이 열려 있는 경우
	//*******************************************************************************************************************

	if ( Maze_Map [Current_M-1][Current_N] == '.' ) {
		if ( have_energy [Current_M-1][Current_N] < have_energy [Current_M][Current_N] ) {
			Go_Where [Current_M][Current_N] = 'N' ;
			return 1 ;
		}
	} // if 'N'

	return 0 ;
}

//***************************************************************************************************************************
// Break_Wall
//***************************************************************************************************************************

int Break_Wall () {
	int Break_Num = 1 ;
	int Is_Find = 0 ;

	if ( Maze_Map [Current_M][Current_N+1] == '*' || Maze_Map [Current_M][Current_N-1] == '*' || Maze_Map [Current_M+1][Current_N] == '*'
		 || Maze_Map [Current_M-1][Current_N] == '*' ) {

	while ( Break_Num <= energy ) {

		if ( Current_M - Break_Num - 1 <= 0 ) {
			int j = 2 ;
			int flag = 0 ;

			for ( int i = 1 ; i <= Current_M ; i++ ) {
				if ( Maze_Map [i][Current_N - Current_M + Break_Num + j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N - Current_M + Break_Num + j]
					     && Current_N - Current_M + Break_Num + j <= Map_N) {
						push () ;
						Current_N = Current_N - Current_M + Break_Num + j ;
						Current_M = i ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break ;
					}
				}
				if ( Maze_Map [i][Current_N + Current_M - Break_Num - j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N + Current_M - Break_Num - j]
					     && Current_N + Current_M - Break_Num - j >= 1) {
						push () ;
						Current_N = Current_N + Current_M - Break_Num - j ;
						Current_M = i ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break ;
					}
				}
				j++ ;
			}

			if ( flag ) {
				Is_Find = 1 ;
				break ;
			}
		}
		else {
			if ( Maze_Map [Current_M - Break_Num - 1][Current_N] == '.' ) {
				if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [Current_M - Break_Num - 1][Current_N]) {
					push () ;
					Current_M = Current_M - Break_Num - 1 ;
					energy -= Break_Num ;
					have_energy [Current_M][Current_N] = energy ;
					Is_Find = 1 ;
					break ;
				}
			}

			int j = 1 ;
			int flag = 0 ;

			for ( int i = Current_M - Break_Num ; i <= Current_M ; i++ ) {
				if ( Maze_Map [i][Current_N + j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N + j]
					     && Current_N + j <= Map_N ) {
						push () ;
						Current_M = i ;
						Current_N += j ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break;
					}
				}
				if ( Maze_Map [i][Current_N - j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N - j]
					     && Current_N - j >= 1 ) {
						push () ;
						Current_M = i ;
						Current_N -= j ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break ;
					}
				}
				j++ ;
			}

			if ( flag ) {
				Is_Find = 1 ;
				break ;
			}
		}

		if ( Current_M + Break_Num + 1 >= Map_M + 1) {
			int j = 1 ;
			int flag = 0 ;

			for ( int i = Map_M ; i > Current_M ; i-- ) {
				if ( Maze_Map [i][Current_N - Map_M + Current_M + Break_Num + j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N - Map_M + Current_M + Break_Num + j]
					     && Current_N - Map_M + Current_M + Break_Num + j <= Map_N ) {
						push () ;
						Current_N = Current_N - Map_M + Current_M + Break_Num + j ;
						Current_M = i ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break ;
					}
				}
				if ( Maze_Map [i][Current_N + Map_M - Current_M - Break_Num - j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N + Map_M - Current_M - Break_Num - j]
					     && Current_N + Map_M - Current_M - Break_Num - j >= 1 ) {
						push () ;
						Current_N = Current_N + Map_M - Current_M - Break_Num - j ;
						Current_M = i ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break ;
					}
				}
				j++ ;
			}

			if ( flag ) {
				Is_Find = 1 ;
				break ;
			}
		}
		else {
			if ( Maze_Map [Current_M + Break_Num + 1][Current_N] == '.' ) {
				if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [Current_M + Break_Num + 1][Current_N] ) {
					push () ;
					Current_M = Current_M + Break_Num + 1 ;
					energy -= Break_Num ;
					have_energy [Current_M][Current_N] = energy ;
					Is_Find = 1 ;
					break ;
				}
			}

			int j = 1 ;
			int flag = 0 ;

			for ( int i = Current_M + Break_Num ; i > Current_M ; i-- ) {
				if ( Maze_Map [i][Current_N + j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N + j]
					     && Current_N + j <= Map_N ) {
						push () ;
						Current_M = i ;
						Current_N += j ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break ;
					}
				}
				if ( Maze_Map [i][Current_N - j] == '.' ) {
					if ( have_energy [Current_M][Current_N] - Break_Num > have_energy [i][Current_N - j]
					     && Current_N - j >= 1 ) {
						push () ;
						Current_M = i ;
						Current_N -= j ;
						energy -= Break_Num ;
						have_energy [Current_M][Current_N] = energy ;
						flag = 1 ;
						break ;
					}
				}
				j++ ;
			}

			if ( flag ) {
				Is_Find = 1 ;
				break ;
			}
		}

		Break_Num++ ;
	}
	}

	if ( Is_Find ) {
		return 1 ;
	}
	else {
		return 0 ;
	}
}

//***************************************************************************************************************************
// push
//***************************************************************************************************************************

void push () {
	if ( top == 500 * 500 - 1 )
		fprintf ( stderr, "Push error!!\n" ) ;

	Stack_M [++top] = Current_M ;
	Stack_N [top] = Current_N ;
}

//***************************************************************************************************************************
// pop_M
//***************************************************************************************************************************

int pop_M () {
	if ( top < 0 )
		fprintf ( stderr, "Pop error!!\n" ) ;

	return Stack_M [top] ;
}

//***************************************************************************************************************************
// pop_N
//***************************************************************************************************************************

int pop_N () {
	if ( top < 0 )
		fprintf ( stderr, "Pop error!!\n" ) ;

	return Stack_N [top--] ;
}