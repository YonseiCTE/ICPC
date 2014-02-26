#include<iostream>
#include<algorithm>
using namespace std;

//			Class				//
class Linked{
public:	
	int *CN, *Loads, index;
	Linked *next;
public:
	Linked() : next(NULL), index(0) {
		CN = new int[21]; Loads = new int[21];	
	}
	int set(int i, int cn, int loads) {
		CN[i] = cn;
		Loads[i] = loads;
		index++;		return 0;
	}
	int print(){
		if(next != NULL){
			cout << "Configuration Loads" << endl;
			for(int i=1; i<=index; i++){
				cout << "       " << CN[i] << "       " << ""
					<< Loads[i] << endl;
			}
			next->print();
		}
		return 0;
	}
	int sort(){	
		for(int i=index; i>1; i--){ // cout << "i : " << i << endl;
			for(int j=1; j<i; j++){ // cout << "j : " << j << " " << CN[j] << " " << CN[j+1];
			// cout << " " << (CN[j] > CN[j+1]) << endl;
				if(CN[j] > CN[j+1]){
					int temp = CN[j];
					CN[j] = CN[j+1];
					CN[j+1] = temp;

					temp = Loads[j];
					Loads[j] = Loads[j+1];
					Loads[j+1] = temp;
				}
			}
		}
		cout << endl;
		for(int i=index; i>1; i--){ // cout << "i : " << i << endl;
			for(int j=1; j<i; j++){ // cout << "j : " << j << " " << Loads[j] << " " << Loads[j+1];
			// cout << " " << (Loads[j] > Loads[j+1]) << endl;
				if(Loads[j] > Loads[j+1]){
					int temp = CN[j];
					CN[j] = CN[j+1];
					CN[j+1] = temp;

					temp = Loads[j];
					Loads[j] = Loads[j+1];
					Loads[j+1] = temp;
				}
			}
		}
		return 0;
	}
};

class Pair{
public:
	int C, P;	// city, passenger
	Pair() : C(0), P(0) {};
	Pair(int c, int p) : C(c), P(p) {};
	int set(int c, int p){ C=c; P=p; return 0; };
};

class TrafficData{
public:
	int n, K;
	Pair *P;
	TrafficData() : n(0), K(0), P() {};
	TrafficData(int n, int k) : n(n), K(k) {
		P = new Pair[K+1]; 
	}
	int setPair(int i, int pc, int pp){
		P[i].set(pc, pp);	return 0;
	}
};
class Configuration{
public:
	int *CN, maxindex, **A, **D, *loads;	// A : arrivals, D : Departure
public:
	Configuration(int n) : maxindex(1) { 
		CN = new int[21]; loads = new int[21];
		memset(loads, 0, sizeof(int)*21 );
		A = new int*[21]; D = new int*[21];
		for(int i=1; i<=20; i++) A[i] = new int[n+1];
		for(int i=1; i<=20; i++) D[i] = new int[n+1];
	}

	int addConfig(int index, int n, int *c, char AorD);
	int calculate(int index, int k, TrafficData TD);
	int findEle(int index, int target, char AorD);
};
//			Class end			//

int Configuration::addConfig(int index, int n, int *c, char AorD){
	if(AorD == 'A')
		for(int i=1; i<=n; i++)	// maxindex will add
			A[index][i] = c[i];
	else
		for(int i=1; i<=n; i++, maxindex++)
			D[index][i] = c[i];
	return 0;
}

int Configuration::calculate(int index, int k, TrafficData TD){
	int temp1, temp2;
	for(int i=1; i<=k; i++){
		temp1 = findEle(index, TD.n, 'A');
		temp2 = findEle(index, TD.P[i].C, 'D');
		loads[index] += TD.P[i].P * ( 1 + abs(temp1-temp2) );
	}
	return 0;
}

int Configuration::findEle(int index, int target, char AorD){
	if(AorD == 'A') {
		for(int i=1; i<=20; i++){
			if( A[index][i] == target )
				return i;
		}
	}
	else {
		for(int i=1; i<=20; i++){
			if( D[index][i] == target )
				return i;			
		}
	}
	return -1;
}