#include <stdio.h>
#include <stdlib.h>

//***************************************************************************************************************************
// �������� ����
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
		printf ("������ �ϴ� ���� �̸��� �Է� �ϼ���(Ȯ���� ����!) : ex) testcase1.txt\n") ;
		scanf ( "%s", File_Name ) ;
		fptr = fopen ( File_Name, "r" ) ;

		fscanf ( fptr, "%d", &Test_Num ) ;

		for ( int i = 0 ; i < Test_Num ; i++ ) {
			// �浿�� ���縦 ��ġ
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
			// �ַ�� ���
			for ( int k = j - 1 ; k >= 0 ; k-- ) {
				if ( k != j - 1 && Gildong [k] == Gildong [k+1] ) {}
				else
					printf ("%c", Gildong [k]) ;
			}
			printf ("\n") ;
		}


		printf ("�����Ͻ÷��� '1'�� �Է��ϼ��� (��� �Ϸ��� �ƹ� Ű�� �����ÿ�)\n") ;
		scanf ("%d", &Test_Num) ;
		fclose (fptr) ;
		if ( Test_Num == 1 )
			break ;
	}

	return 0 ;
}