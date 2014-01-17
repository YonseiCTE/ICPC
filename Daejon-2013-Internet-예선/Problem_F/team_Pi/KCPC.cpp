#include <stdio.h>
#include <stdlib.h>

//***********************************************************************
// �������� ����
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

		printf ("������ �ϴ� ���� �̸��� �Է� �ϼ���(Ȯ���� ����!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;

		if ( fptr == NULL ) {
			printf ("�׷� ������ �����ϴ�.\n") ;
			exit(1) ;
		}

		fscanf ( fptr, "%d", &Test_Num ) ;

		for ( int i = 0 ; i < Test_Num ; i++ ) {
			fscanf ( fptr, "%d", &Team_Num ) ;
			if ( Team_Num < 3 )
				fprintf ( stderr, "�׽�Ʈ %d��° ���� ���� �ش� �������� ���� �ʽ��ϴ�.", i+1 ) ;
			fscanf ( fptr, "%d", &Problem_Num ) ;
			if ( Problem_Num > 100 )
				fprintf ( stderr, "�׽�Ʈ %d��° ������ ���� �ش� �������� ���� �ʽ��ϴ�.", i+1 ) ;
			fscanf ( fptr, "%d", &My_Team ) ;
			if ( My_Team > Team_Num )
				fprintf ( stderr, "�׽�Ʈ %d��° ����� �� ID�� �ش� �������� ���� �ʽ��ϴ�.", i+1 ) ;
			fscanf ( fptr, "%d", &Log_Entry ) ;
			if ( Log_Entry < 3 || Log_Entry > 10000 )
				fprintf ( stderr, "�׽�Ʈ %d��° �α� ��Ʈ���� ���� �ش� �������� ���� �ʽ��ϴ�.\n", i+1 ) ;

			// ��� ���� ���� ���� & �� ���� �� ���� & ���� ���� & ������ ���� ������ '0'���� �ʱ�ȭ
			for ( int j = 0 ; j < Team_Num ; j++ ) {
				Team_Score [j] = 0 ;
				Team_Submit [j] = 0 ;
				Last_Submit [j] = 0 ;
				for ( int k = 0 ; k < Problem_Num ; k++ )
					Team_Problem [j][k] = 0 ;
			}
			// �� �α��� ������ ������ȭ
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
			// �� ���� ���� ������ ������ȭ
			for ( int j = 0 ; j < Team_Num ; j++ ) {
				for ( int k = 0 ; k < Problem_Num ; k++ )
					Team_Score [j] += Team_Problem [j][k] ;
			}
			// ������� �� ���� ���
			My_Rank = Team_Num ;						// ������ ����� �ʱ�ȭ
			// �ѹ� �̻� ������ Ǯ���� ��� ���� ���
			if ( Last_Submit [My_Team-1] != 0 ) {
				for ( int j = 0 ; j < Team_Num ; j++ ) {
					// �ڽ��� ���� ������ jump
					if ( j == My_Team-1 ) {}
					else {
						// ��� ������ ������ ������ '1'���� ����
						if ( Team_Score [j] < Team_Score [My_Team - 1] )
							My_Rank-- ;
						// ��� ���� ������ ���ٸ�
						else if ( Team_Score [j] == Team_Score [My_Team - 1] ) {
							// ������ ������Ʈ�� ������ '1'���� ����
							if ( Team_Submit [j] > Team_Submit [My_Team - 1] )
								My_Rank-- ;
							// ������ ������Ʈ�� ���ٸ�
							else if ( Team_Submit [j] == Team_Submit [My_Team - 1] ) {
								// �������� ������ ������ �� ������ '1'���� ����
								if ( Last_Submit [j] > Last_Submit [My_Team - 1] )
									My_Rank-- ;
							}
						}
					}
				}
				// ���� ���� ���
				printf ("%d\n", My_Rank) ;
			}
			// �� ������ ���� ���� �ʾ��� ��� ������ ����� ���
			else {
				printf ("%d\n", My_Rank) ;
			}
		}

		printf ("�����Ͻ÷��� '1'�� �Է��ϼ��� (��� �Ϸ��� �ƹ� Ű�� �����ÿ�)\n") ;
		scanf ("%d", &Team_Num) ;
		fclose (fptr) ;
		if ( Team_Num == 1)
			break ;

	}

	return 0 ;
}