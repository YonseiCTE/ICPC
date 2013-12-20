
#include <iostream>

using namespace std;

#define DEBUG 0

///////////////////////////////

#define IS_LESS(v1, v2)  (v1 < v2)
 
void siftDown( int *a, int start, int count);
 
#define SWAP(r,s)  {int t=r; r=s; s=t; }
 
void heapsort( int *a, int count)
{
    int start, end;
 
    /* heapify */
    for (start = (count-2)/2; start >=0; start--) {
        siftDown( a, start, count);
    }
 
    for (end=count-1; end > 0; end--) {
        SWAP(a[end],a[0]);
        siftDown(a, 0, end);
    }
}
 
void siftDown( int *a, int start, int end)
{
    int root = start;
 
    while ( root*2+1 < end ) {
        int child = 2*root + 1;
        if ((child + 1 < end) && IS_LESS(a[child],a[child+1])) {
            child += 1;
        }
        if (IS_LESS(a[root], a[child])) {
            SWAP( a[child], a[root] );
            root = child;
        }
        else
            return;
    }
}

///////////////////////////////

int binarysearch( int *a, int key, int n)
{
  int left, right, i;

  left = 0;
  right = n;

  while ( left < right ) 
    {
      i = (left + right) / 2;
      
      if ( a[i] == key ) 
	return i;
      else if ( a[i] < key )
	left = i;
      else
	right = i;
    }

  return -1; // Not found
}


///////////////////////////////

#define SIZE 150000
int stack[SIZE*2];
int sp;

int checkkey(int *a, int n) 
{
  int i;
  int al,au;

  // Make it empty.
  sp = 0;

  for (i=0; i<n; i++)
    {
      // Push a[i] and combine all neighbor ranges
      al = a[i]; // push a[i],a[i]
      au = a[i];

      while ( 0 < sp ) 
	{
	  if ( stack[sp-1]+1 == al )
	    {
	      al = stack[sp-2];
	      sp = sp - 2;
	    } 
	  else if ( au == stack[sp-2]-1 ) 
	    {
	      au = stack[sp-1];
	      sp = sp - 2;
	    }
	  else
	    {
	      break;
	    }
	}

      stack[sp] = al;
      stack[sp+1] = au;
      sp = sp + 2;
    }

  if ( sp == 2) // if the stack holds only a single range.
    return 0;
  else
    return 1;

}

///////////////////////////////

int data[SIZE];
int temp[SIZE];

int main() 
{
  int data_size, k;


  // Read the number of test cases
  cin >> data_size;

  for (int i=0; i<data_size; i++) {

    // Read the number of data for each test case
    cin >> k;

    // Read data
    for (int j=0; j<k; j++)
      cin >> data[j];

    if ( DEBUG ) {
      for (int j=0; j<k; j++)
	cout << data[j] << " ";
      cout << endl;
    }

    // Do heap sort
    for (int j=0; j<k; j++)
      temp[j] = data[j];

    heapsort(temp, k);

    if ( DEBUG ) {
      for (int j=0; j<k; j++)
	cout << temp[j] << " ";
      cout << endl;
    }

    for (int j=0; j<k; j++)
      data[j] = binarysearch( temp, data[j], k ) + 1;

    if ( DEBUG ) {
      for (int j=0; j<k; j++)
	cout << data[j] << " ";
      cout << endl;
    }

    if ( checkkey ( data, k ) )
      cout << "YES";
    else
      cout << "NO";
    cout << endl;

  }

  return 0;
}
 
