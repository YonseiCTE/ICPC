/*#include <iostream>
#include <cstdlib>		// length
#include <algorithm>	// sort*/
#include "classMERGE.h"
//using namespace std;

//				Define				//
#define DEBUG0 0
#define DEBUG1 0
#define DEBUG2 0
//				Define end			//

//				Body : main			//
int main(int argc, char* argv){
	int T;
	cout << "Tastcase : ";		cin >> T;
	cout << endl;
	int *outputs = new int[T+1];
	int cnt = 0;
	while(cnt++ != T){
		int N, K;	// T -> 1~20, N -> 1~10000, K -> 1~1000
		int min = 1000000, max = -1000000;	// -100,0000 ~ 100,0000
		int ans = 0;
		cout << "Sensor number : ";	cin >> N;
		cout << "Center number : ";	cin >> K;
		int* Nx = new int[N+1];

		cout << "Grid бщ" << endl;
		for(int i=1; i<=N; i++){		// input grids, and get min, max
			cin >> Nx[i];
			if(Nx[i] < min) min = Nx[i];
			if(Nx[i] > max) max = Nx[i];
		}

		sort(Nx+1, Nx+N+1);		// sort by descending order

		cout << endl;
		if(DEBUG0) outputarray(Nx, N);	// sort check
		if(DEBUG1) cout << min << " " << max << endl; // min, max

		// calculation part
		MERGE mg(N);
		for(int i=1; i<=N; i++){
			if(i==1){
				mg.increaseSN();		
			}
			else if(i==N){
				mg.Mleft(Nx[i]-Nx[i-1]);
			}
			else{
				int c1=0, c2=0;
				while(compare(Nx[i], Nx[i+1+c1]) == 1){
					c1++;
				}
				while(compare(Nx[i-1-c2], Nx[i]) == 1){
					c2++;
				}

				int a=Nx[i]-Nx[i-1-c2];	// left side
				int b=Nx[i+1+c1]-Nx[i];	// right side

				if( compare(a, b) ){	// Mleft when a<=b
					mg.Mleft(a);
				}
				else{	// Mright, leftE when a>b
					mg.increaseSN();
					mg.leftE(a);
				}// end if
				if(c1+c2>0) i += c1 + c2;
			}// end if
		}// end for

		if(DEBUG2) cout << endl << mg.getSN() << " " << mg.getR();
		if( mg.getSN() == K ) ans = mg.getR();
		else if( mg.getSN() > K ){
			while( mg.getSN() != K )
				mg.getE();
			ans = mg.getR();
		}
		else {		// mg.getSN() < K
			while( mg.getSN() != K )
				mg.getM();
			ans = mg.getR();
		}
		outputs[cnt] = ans;
		cout << endl;
	}

	cout << "Results бщ" << endl;
	for(int i=1; i<=T; i++)
		cout << outputs[i] << endl;
	return 0;
}
//				Body end			//