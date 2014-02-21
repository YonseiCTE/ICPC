#include <iostream>
#include <cstdlib>		// length
#include <algorithm>	// sort
using namespace std;

//				Declaration			//
int outputarray(int* array, int length);
int compare(int a, int b);
//				Declaration end		//

//				Class : MERGE		//
class MERGE{	// merge
private:
	int indexE, minE, indexM, maxM;
	int SN;				// SN : the number of sections
						// ¡æ increase when " Mright(int t) " called
	int *E, *M;			// arrays of sections
	int r;				// result
public:
	MERGE(int N);		// constructor

	// increase minE when add element
	int leftE(int t);	// left is empty

	// increase maxM, indexM when add element	/ add r
	int Mleft(int t);	// merge left

	int increaseSN(){
		SN++;	return 0;
	};// increase SN

	// get index : indexE,	increase indexE
	int getE();		// add		minimum empty's section to ans and get

	// get index : maxM,	decrease maxM
	int getM();		// subtrate maximum merged  section to ans and get

	int getR();		// get current result
	int getSN();	// get base Section Number	
};
MERGE::MERGE(int N)
	:indexE(1), minE(1)		// initialize section
	,indexM(N), maxM(N)		//		  ¡¨
	,SN(0), r(0)			//		  ¡¨
{
	E = new int[N+1];	M = new int[N+1];
	//E[0] = M[0] = 0;
}

// increase minE when add element
int MERGE::leftE(int t){
	E[indexE] = t;
	sort(E+minE,E+indexE);
	indexE++;
	return 0;
}

// increase maxM, indexM when add element		/add		r
int MERGE::Mleft(int t){
	r += t;
	M[indexM] = t;
	sort(M+indexM,M+maxM+1);	
	indexM--;
	return 0;
}

// get index : indexE,	increase indexE, minE	/add		r
int MERGE::getE(){
	if( minE <= indexE ){
		r += E[minE];	
		SN--;
		return E[minE++];
	}
	else return 0;
}

// get index : maxM,	decrease maxM,			/subtract	r
int MERGE::getM(){	
	if( maxM >= indexM ){
		r -= M[maxM];	
		SN++;
		return M[maxM--];
	}
	else return 0;
}

int MERGE::getR(){
	return r;
}
int MERGE::getSN(){
	return SN;
}
//				Class end			//

//				funtions			//
int outputarray(int* array, int length){ 
	for(int i=1; i<=length; i++)
		cout << array[i] << " ";
	return 0;
}

int compare(int a, int b){
	if(a>b) return 0;		// 0 -> right
	else if(a==b) return 1;	// 1 ¢Ù
	else return 2;			// 2 -> left	(a<b)
}
//				funtions end		//