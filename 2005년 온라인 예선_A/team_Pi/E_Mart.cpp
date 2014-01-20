#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// �������� ����
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
		printf ("������ �ϴ� ���� �̸��� �Է� �ϼ���(Ȯ���� ����!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;
		if ( fptr == NULL ) {
			fprintf ( stderr, "�׷� ������ �����ϴ�.\n" ) ;
			exit (1) ;
		}

		fscanf ( fptr, "%d", &Test_Num ) ;

		for ( int i = 0 ; i < Test_Num ; i++ ) {
			fscanf ( fptr, "%d", &Kind ) ;
			
			// ���� �������� ����, ������ ������ȭ
			for ( int j = 0 ; j < Kind ; j++ ) {
				fscanf ( fptr, "%d", &Weight [j] ) ;
				fscanf ( fptr, "%d", &Cost [j] ) ;
			}
			// �� ���츶�� ȿ������ ������ȭ
			for ( int j = 0 ; j < Kind ; j++ )
				Efficient_Marchandise [j] =  ((double) Cost [j]) /  ((double) Weight [j]) ;
			// ���� ȿ������ ������ ������ ã�´�.
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
			// �ַ�� ���
			printf ( "%d\n", Choice_Price ) ;

		}

		printf ("�����Ͻ÷��� '1'�� �Է��ϼ��� (��� �Ϸ��� �ƹ� Ű�� �����ÿ�)\n") ;
		scanf ("%d", &Test_Num) ;
		fclose (fptr) ;
		if ( Test_Num == 1 )
			break ;
	}
	return 0 ;
}