#include <stdio.h>
#include <math.h>

//***************************************************************************************************************************
// �������� ����
//***************************************************************************************************************************

#define MAX 10000
int First_Choice ;
int Second_Choice ;
int Distance ;
int Bee_House [MAX][2] ;
char File_Name [MAX] ;

//***************************************************************************************************************************
// �Լ� ����
//***************************************************************************************************************************

void Build_Bee_House () ;
void Calculate_Distance () ;

//***************************************************************************************************************************
// main
//***************************************************************************************************************************

int main (void) {

	// ������ �ʱ�ȭ
	Build_Bee_House () ;

	while ( 1 ) {
		FILE *fptr = NULL ;
		printf ("������ �ϴ� ���� �̸��� �Է� �ϼ���(Ȯ���� ����!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;

		while ( 1 ) {
			if ( fptr == NULL ) {
				fprintf ( stderr, "�׷� ������ �����ϴ�...\n" ) ;
				break ;
			}

			// �� ���� ���� �Է� �޴´�.
			fscanf ( fptr, "%d%d", &First_Choice, &Second_Choice ) ;

			// ���� '0 0'�� �����ٸ� �� ������ ���̹Ƿ� ����
			if ( First_Choice == 0 && Second_Choice == 0 ) {
				printf ("�����Ͻ÷��� '1'�� �Է��ϼ��� (��� �Ϸ��� �ƹ� Ű�� �����ÿ�)\n") ;
				scanf ("%d", &First_Choice) ;
				fclose (fptr) ;
				break ;
			}
			
			// �� ������ �Ÿ��� ���
			Calculate_Distance () ;
			// �ַ�� ���
			printf ( "%d\n", Distance ) ;

			// ���α׷��� ������� �ʵ��� First_Choice�� '0'���� ����
			First_Choice = 0 ;
		}

		// ������ '0 0' ���� ���� �� '1'�� �Է��ߴٸ� ����
		if ( First_Choice == 1 )
			break ;
	}
	return 0 ;
}

//***************************************************************************************************************************
// Build_Bee_House
//***************************************************************************************************************************

void Build_Bee_House () {
	
	// ���ʰ� �Ǵ� 1 ~ 7�� ���� ���� �ʱ�ȭ ��Ų��.
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

	// idea.txt�� ���� �ϼ���
	// ��Ģ�� ���� ��� ���� �ʱ�ȭ ��Ų��.
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

	// ��� �Ŀ� ���� ������ idea.txt�� ���� �ϼ���
	if ( Bee_House [First_Choice][1] == Bee_House [Second_Choice][1] ) {
		Distance = abs ( Bee_House [First_Choice][0] - Bee_House [Second_Choice][0] ) ;
		Distance /= 2 ;
	}
	else {
		Distance = abs ( Bee_House [First_Choice][1] - Bee_House [Second_Choice][1] ) ;
		Distance += ( abs ( Bee_House [First_Choice][0] - Bee_House [Second_Choice][0] )  - Distance ) / 2 ;
	}
}