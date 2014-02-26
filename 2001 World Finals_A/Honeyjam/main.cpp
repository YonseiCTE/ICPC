#include"classes.h"

/*	input style	: Gates Traffic Problem
	3				;the number of cities / 0 == end program / ~25
	1 2 2 10 3 15	;(City number) (destination count) (Pairs : dest number, amount of passengers(~500) ) ¡¤¡¤¡¤
	2 1 3 10		;		¡¨			¡¨					¡¨
	3 2 1 12 2 20	;		¡¨			¡¨					¡¨
	1		; configuration number / 0 == end this test case / ~20
	1 2 3	; north	( Arrival Gates )
	2 3 1	; south (Departure Gates)
	2		;
	2 3 1	;	
	3 2 1	;
	0		; ( end this test case )
*/

/*	variables
	N		: cities numver 1 ~ 25 / if not end this program
	outputs : outputs ( class Linked )
	*cursor : a pointer ( class Linked )
	tempX	: temporary
	*TD		: Traffic Data ( class TrafficData )
		¡æ n		: city number
		¡æ K		: Number of Pairs
		¡æ *P		: ( class Pair) / passengers 0~500
	Conf	: Configuration Data ( class Configuration )
		¡æ CN		: Configuration Number	1 ~ 20 / if not end this test case
		¡æ maxindex : Count the configuration data inputted
		¡æ **A		: Arrivals array
		¡æ **D		: Departure array
		¡æ *loads	: Loads ( Results and Calculated data )
*/

int main(int argc, char* argv){
	int N;
	Linked outputs = Linked();
	Linked *cursor;		// cursor
	cursor = &outputs;
	int tempn, tempK, temp1, temp2, *temp3;
	while( true ){
		cin >> N;
		if(N == 0) break;
		TrafficData *TD = new TrafficData[N+1];	// class TrafficData
		for(int i=1; i<=N; i++){
			cin >> tempn >> tempK;
			TD[i] = TrafficData(tempn, tempK);
			for(int j=1; j<=TD[i].K; j++){
				cin >> temp1 >> temp2;
				TD[i].setPair(j, temp1, temp2);
			}
		}	
		Configuration conf = Configuration(N);	// class Configuration
		for(int i=1; i<=20; i++){
			cin >> temp1;	// cn
			if(temp1 == 0) { i--; break; }
			temp3 = new int[N+1];
			conf.CN[i] = temp1;
			for(int j=1; j<=N; j++){
				cin >> temp3[j];
			}
			conf.addConfig(i, N, temp3, 'A');
			for(int j=1; j<=N; j++){
				cin >> temp3[j];
			}
			conf.addConfig(i, N, temp3, 'D');

			for(int j=1; j<=N; j++)
				conf.calculate(i, TD[j].K, TD[j]);

			cursor->set(i, temp1, conf.loads[i]);	
		}
		cursor->sort();	// sort
		cursor->next = new Linked();
		cursor = cursor->next;
	}		
	outputs.print();

	return 0;
}