#include <stdio.h>
#include <string.h>

//***************************************************************************************************************************
// 전역변수 선언
//***************************************************************************************************************************

#define MAX 10000000
int Test ;
int SqNumber ;
int top ;
int Size ;
int buffer [MAX] ;
int Sort [MAX] ;
int Sort_Index2 [MAX] ;
int Stack [MAX] ;

//***************************************************************************************************************************
// 함수 선언
//***************************************************************************************************************************

void Insert	(int loc, int elem, int Sort[], int Sort_Index2[]) ;
void IsWeak () ;
void push (int token) ;
int pop () ;

//***************************************************************************************************************************
// main
//***************************************************************************************************************************

int main (void) {
	FILE *fptr = NULL ;
	fptr = fopen ("Key.txt", "r") ;

	fscanf(fptr, "%d", &Test) ;

	for ( int i = 0 ; i < Test ; i++ ) {
		top = -1 ;
		Size = 0 ;
		memset (Sort, 0, MAX) ;
		memset (Sort_Index2, 0, MAX) ;
		memset (Stack, 0, MAX) ;
		memset (buffer, 0, MAX) ;
		fscanf(fptr, "%d", &SqNumber) ;

		int Size2 = SqNumber ;
		for ( int j = 0 ; j < SqNumber ; j++ ) {
			fscanf(fptr, "%d", &buffer[j]) ;
			Sort_Index2 [j + 1] = j ;
			Insert ( j, buffer[j], Sort, Sort_Index2 ) ;
		}

		for ( int j = 1 ; j <= SqNumber - 2 ; j++ ) {
			int temp = Sort[1] ;
			Sort[1] = Sort[Size2] ;
			Sort[Size2] = temp ;
			temp = Sort_Index2[1] ;
			Sort_Index2[1] = Sort_Index2[Size2] ;
			Sort_Index2[Size2] = temp ;
			Size2-- ;
			int index = 1 ;

			while (1) {
				if (Size2 == 2) {
					break;
				}
				if ( Sort[index] <= Sort[index+1] ) {
						temp = Sort[index] ;
						Sort [index] = Sort [index+1] ;
						Sort [index+1] = temp ;
						temp = Sort_Index2[index] ;
						Sort_Index2[index] = Sort_Index2[index+1] ;
						Sort_Index2[index+1] = temp ;
				}
				if ( Sort[index] >= Sort [(index) * 2] && (Sort [(index)*2] <= Sort[(index)*2 + 1])) {
					temp = Sort[index] ;
					Sort[index] = Sort[(index) * 2] ;
					Sort[(index) * 2] = temp ;
					temp = Sort_Index2[index] ;
					Sort_Index2[index] = Sort_Index2[index*2] ;
					Sort_Index2[index*2] = temp ;
					index = index * 2 ;
				}
				else if (Sort[index] >= Sort[(index) * 2 + 1] && (Sort[(index)*2] >= Sort[(index)*2+1])) {
					temp = Sort[index] ;
					Sort[index] = Sort[(index)*2+1] ;
					Sort[(index)*2+1] = temp ;
					temp = Sort_Index2 [index] ;
					Sort_Index2 [index] = Sort_Index2 [(index)*2+1] ;
					Sort_Index2 [(index)*2+1] = temp ;
					index = index*2 + 1 ;
				}
				if ((((index)*2) >= Size2) || ((Sort[index] <= Sort[(index)*2] && Sort[index] <= Sort [(index)*2+1])))
					break ;
			}
		}
		if ( Sort[1] < Sort[2] ) {
			int temp = Sort[1] ;
			Sort[1] = Sort[2] ;
			Sort[2] = temp ;
			temp = Sort_Index2 [1] ;
			Sort_Index2 [1] = Sort_Index2 [2] ;
			Sort_Index2 [2] = temp ;
		}
		IsWeak () ;
	}

	fclose (fptr) ;
	return 0 ;
}

//***************************************************************************************************************************
// Insert
//***************************************************************************************************************************

void Insert	(int loc, int elem, int Sort[], int Sort_Index2[]) {

	int temp ;
	Size++ ;
	Sort[Size] = elem ;
	Sort_Index2[Size] = loc ;
	int now = Size ;
	int now2 = Size ;
	while (Sort[now/2] > elem) {
		Sort[now] = Sort[now / 2] ;
		Sort_Index2[now] = Sort_Index2[now / 2] ;
		now /= 2 ;
	}
	Sort[now] = elem ;
	Sort_Index2[now] = loc ;
}

//***************************************************************************************************************************
// IsWeak
//***************************************************************************************************************************

void IsWeak() {
	int Count = 1 ;
	int first, last ;

	if ( Sort_Index2 [1] + 1 == Sort_Index2 [2] ) {
		push (Sort_Index2 [1]) ;
		push (Sort_Index2 [2]) ;
	}
	else if ( Sort_Index2 [2] + 1 == Sort_Index2 [1] ) {
		push (Sort_Index2 [2]) ;
		push (Sort_Index2 [1]) ;
	}
	else {
		push (Sort_Index2 [1]) ;
		push (Sort_Index2 [1]) ;
		push (Sort_Index2 [2]) ;
		push (Sort_Index2 [2]) ;
		Count = 2 ;
	}

	for ( int i = 3 ; i <= SqNumber ; i++ ) {
		if ( pop() == Sort_Index2 [i] - 1 ) {
			push (Sort_Index2 [i]) ;
			while ( Count != 1 ) {
				last = pop() ;
				first = pop() ;
				if ( pop() == first - 1 ) {
					push (last) ;
					Count-- ;
				}
				else if ( pop() == last + 1 ) {
					push (first) ;
					top++ ;
					Count-- ;
				}
				else {
					top = top + 4 ;
					break ;
				}
			}
		}
		else if ( pop() == Sort_Index2 [i] + 1 ) {
			push (Sort_Index2 [i]) ;
			top++ ;
			while ( Count != 1 ) {
				last = pop() ;
				first = pop() ;
				if ( pop() == first - 1 ) {
					push (last) ;
					Count-- ;
				}
				else if ( pop() == last + 1 ) {
					push (first) ;
					top++ ;
					Count-- ;
				}
				else {
					top = top + 4 ;
					break ;
				}
			}
		}
		else {
			top = top + 2 ;
			push (Sort_Index2 [i]) ;
			push (Sort_Index2 [i]) ;
			Count++ ;
		}
	}

	if ( Count < 4 )
		printf ("NO\n") ;
	else
		printf ("YES\n") ;

}

//***************************************************************************************************************************
// push
//***************************************************************************************************************************

void push (int token) {
	if (top >= MAX-1)
		fprintf(stderr, "스택이 가득 차 에러 발생!") ;

	Stack [++top] = token ;
}

//***************************************************************************************************************************
// pop
//***************************************************************************************************************************

int pop () {
	if (top == -1)
		fprintf(stderr, "스택이 비어 있으므로 pop 불가!") ;

	return Stack[top--] ;
}
