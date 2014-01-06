#include<iostream>
#include<cmath>
#include<iomanip>	// cout control
#include<hash_map>	// hash_map
using namespace std;
using namespace stdext;	// hash_map namespace

#define Mdata 10000
#define DEBUG 1
#define DEBUG2 0
#define DEBUG3 0

typedef int* intp;

class p{
public:
	int r, c;
	p(int a, int b):r(a), c(b){};
	p():r(0), c(0){};
};

int getwidth(int data);
p go(int r, int c, int direction);	// go for insert data to map
// direction 0 := 270', 1 := 150, 2 := 90, 3 := 30, 4 := -30(300)
//			 5 := 270 + 270 + 210

int main(void){
	int width = getwidth(Mdata);						// width, height
	if( width % 2 == 0 ) width++;
	int height = width;
	if( DEBUG ) cout << "width : " << width << ' ' 
					<< "height : " << height << ' '
					<< "mid : " << width/2+1 << endl;;	// width, height, mid

	int midc, midr;			// map
	midc = midr = width/2+1;
	hash_map<int,p> map; 	

	map.insert( hash_map<int,p>::value_type( 1, p(midr, midc) ) );
	p temp = go( midr, midc, 0 );
	if( DEBUG ) cout << "r : " << temp.r << ' ' << "c : " << temp.c << endl;
	int count=1;
	for(int i=2; i<=Mdata; count++){
		for(int j=0; j<count; j++, i++){		// 1
			map.insert( hash_map<int,p>::value_type( i, temp ) );
			temp = go( temp.r, temp.c, 1 );			
		}
		for(int j=0; j<count; j++, i++){		// 2
			map.insert( hash_map<int,p>::value_type( i, temp ) );
			temp = go( temp.r, temp.c, 2 );			
		}
		for(int j=0; j<count; j++, i++){		// 3
			map.insert( hash_map<int,p>::value_type( i, temp ) );
			temp = go( temp.r, temp.c, 3 );			
		}
		for(int j=0; j<count; j++, i++){		// 4
			map.insert( hash_map<int,p>::value_type( i, temp ) );
			temp = go( temp.r, temp.c, 4 );			
		}
		for(int j=0; j<count+1; j++, i++){		// 5  count+1 ¿¡ ÁÖÀÇ
			map.insert( hash_map<int,p>::value_type( i, temp ) );
			temp = go( temp.r, temp.c, 5 );			
		}
		for(int j=0; j<count; j++, i++){		// 6
			map.insert( hash_map<int,p>::value_type( i, temp ) );
			temp = go( temp.r, temp.c, 6 );
		}
	}
	if( DEBUG ) cout << "size : " << map.size() << endl;	// map

	int a, b;
	hash_map<int,p>::iterator itera, iterb;	
	while( DEBUG3 ){	// check key has vaild value
		int i;
		cin >> i;
		if( i==0 ) break;
		itera=map.find(i);
		cout << "r : " << itera->second.r << " c : " << itera->second.c << endl;
	}
	while(true){
		cin >> a >> b;
		if(a==0 && b==0){ cout << "end" << endl; break; }
		if(a==0 || b==0){ cout << "Unvaild input" << endl; continue; }
		itera = map.find(a);
		iterb = map.find(b);
		p tempa = itera->second;
		p tempb = iterb->second;
		if(a==b){
			cout << "The distance between " << a << " and " << b <<
					" is " << 0 << '.' << endl;
		}
		else if(tempa.c == tempb.c && tempa.r != tempb.r ){
			cout << "The distance between " << a << " and " << b <<
					" is " << abs(tempa.r-tempb.r) << '.' << endl;
		}
		else if(tempa.r == tempb.r && tempa.c != tempb.c
			|| tempa.r + tempa.c == tempb.r + tempb.c){
			cout << "The distance between " << a << " and " << b <<
					" is " << abs(tempa.c-tempb.c) << '.' << endl;
		}
		else{	// move b.c to match with a.c
			int temp0 = tempa.c-tempb.c;
			int buf, buf2, t1, t2, i;	// buffer, buffer2, temp1, temp2, i
			p tp1, tp2;			// temp p 1, temp p 2
			if( temp0 > 0 ){	// b is left side than a, mode 0, 4
				for(i=0; i<temp0; i++){ // lower
					tp1 = go(tempb.r, tempb.c, 0);
				}
				for(i=0; i<temp0; i++){ // upper
					tp2 = go(tempb.r, tempb.c, 4);
				}
				buf = min( abs(tempa.r-tp1.r), abs(tempa.r-tp2.r) );
			}
			else{		// b is right .. , mode 1, 2
				for(i=0; i<abs(temp0); i++){ // lower
					tp1 = go(tempb.r, tempb.c, 1);
				}
				for(i=0; i<abs(temp0); i++){ // upper
					tp2 = go(tempb.r, tempb.c, 2);
				}
				buf = min( abs(tempa.r-tp1.r), abs(tempa.r-tp2.r) );
			}
			cout << "The distance between " << a << " and " << b <<
					" is " << buf + i
					<< '.' << endl;
		}
	}
	return 0;
}

int getwidth(int data){
	int capacity = Mdata;
		int c = 0;
		for(int i=0; ; i++){
			int temp = 6 * i;
			if( temp == 0 ) temp = 1;
			if( capacity - temp <= 0 ) break;
			capacity -= temp;
			c++;
			if( DEBUG2 ){
				cout << capacity << ' ';
				if( i % 10 == 0 ) cout << endl;
			}
		}	
		//	if MAX is 10000, c == 58	*/	
		return c*2 - 1;
}
p go(int r, int c, int direction){	// go
	int t1, t2;	// temp
	switch(direction){
		case 0: t1 = r-1, t2 = c+1; break;	// down, right
		case 1: t1 = r	, t2 = c-1; break;	// down, left
		case 2: t1 = r+1, t2 = c-1; break;	// up  , left
		case 3: t1 = r+1, t2 = c  ; break;	// up
		case 4: t1 = r	, t2 = c+1; break;  // up  , right
		case 5: t1 = r-1, t2 = c+1; break;	// same as 1
		case 6: t1 = r-1, t2 = c  ; break;	// down
		default: t1 = r,  t2 = c  ; break;	// stay
	}
	p returnv(t1, t2);
	return returnv;
}
