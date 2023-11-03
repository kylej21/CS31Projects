#include<iostream>
#include<string>
#include<cctype>
#include <cassert>

using namespace std;
//simply concatenate the string to itself at each element.
//O(n)
int reduplicate(string a[], int n){
    if(n<0){
        return -1;
    }
    for(int i=0;i<n;i++){
        a[i]+=a[i];
    }
    return n;
};
//loop through until a[i] is the target 
//O(n)
int locate(string a[], int n, string target){
    if(n<0){
        return -1;
    }
    for(int i=0;i<n;i++){
        if(a[i]==target){
            return i;
        }
    }
    return -1;
};
//for each element look at all the elements after it. 
//Count how many after are greater than it and if that number is 0 return that position
//unsure of effeciency maybe nlogn or something weird. < O(n)^2
int locationOfMax(const string a[], int n){
    if(n<0){
        return -1;
    }
    for(int i=0;i<n;i++){
        int numLess=0;
        for(int j=0;j<n;j++){
            if(i!=j){
                if(a[i]<a[j]){
                    numLess++;
                }

            }
        }
        if(numLess==0){
            return i;
        }
    }
    return -1;
};
//store the first element you are removing then set each element equal to the element on its left
//at the very end set the last element in the subarray to the first one we stored
int circleLeft(string a[], int n, int pos){
    if(pos > n-1){
        return -1;
    }
    if(n<0){
        return -1;
    }
    string temp = a[pos];
    for(int i=pos;i<n-1;i++){
        a[i]=a[i+1];
    }
    a[n-1]=temp;
    return pos;
};
//O(n)
//if the current element doesnt equal the last element increment consecs and change what the last element was.
//could maybe be written using just a[i]!=a[i-1]???
int enumerateRuns(const string a[], int n){
    if(n<0){
        return -1;
    }
    string current=a[0];
    int consecs=1;
    for(int i=1;i<n;i++){
        if(a[i]!=current){
            current=a[i];
            consecs++;
        }
    }
    return consecs;
};
//do intDiv and doubleDiv then compare. This tells me which loop to use regarding odd or even number of elements
//O(n/2) 
int flip(string a[], int n){
    if(n<0){
        return -1;
    }
    int intdiv=0;
    double dubdiv=0.0;
    intdiv=((n+1)/2.0)-1;
    dubdiv=((n+1)/2.0)-1;
    bool equal = intdiv==dubdiv ;
    if(equal){
        for(int i=0;i<intdiv;i++){
            string temp=a[i];
            a[i]=a[(n-i)-1];
            a[(n-i)-1]=temp;
        }
    }
    else{
        for(int i=0;i<=intdiv;i++){
            string temp=a[i];
            a[i]=a[(n-i)-1];
            a[(n-i)-1]=temp;
        }
    }
    return n;
};
//simply loop using n1 and n2 as the max iteration value until they are not equal O(n)
int locateDifference(const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2<0){
        return -1;
    }
    for(int i=0;i<n1 && i<n2;i++){
        if(a1[i]!=a2[i]){
            return i;
        }
    }
    if(n1>n2){
        return n2;
    }
    return n1;
};

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2<0){
        return -1;
    }
    if(n2==0){
        return 0;
    }
    //loop through a1 until I see the first item of a2, then loop until the end of either a2 or a1. 
    //If the loop finishes and correct remains true it is a sequence
    //O(n)^2
    for(int i=0;i<n1;i++){
        if(a1[i]==a2[0]){

            bool correct = true;
            for(int j=0;j<n2 && j<n1;j++){
                if(a1[i+j]!=a2[j]){
                    correct=false;
                }
            }
            if(correct){
                return i;
            }
        }
    }
    return -1;
};

//for every string in a1, loop through a2 to see if it exits. O(n)^2
int locateAny(const string a1[], int n1, const string a2[], int n2){
    for(int i=0;i<n1;i++){
        for(int j=0;j<n2;j++){
            if(a1[i]==a2[j]){
                return i;
            }
        }
    }
    return -1;
};

int divide(string a[], int n, string divider){
    //logically if sorted alphabetically then it doesnt matter what divider is it will be correctly ordered
    //apply bubble sort O(2n)
    //later parse through a to find first index larger than divider, or return n
    for(int i=0; i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i]>a[j]){
                string temp = a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(a[i]>=divider){
            return i;
        }
    }
    return n;
};

int main()
	{
	    string h[7] = { "nikki", "ron", "asa", "vivek", "", "chris", "donald" };
	    assert(locate(h, 7, "chris") == 5);
	    assert(locate(h, 7, "asa") == 2);
	    assert(locate(h, 2, "asa") == -1);
	    assert(locationOfMax(h, 7) == 3);

	    string g[4] = { "nikki", "ron", "chris", "tim" };
	    assert(locateDifference(h, 4, g, 4) == 2);
	    assert(circleLeft(g, 4, 1) == 1 && g[1] == "chris" && g[3] == "ron");

	    string c[4] = { "ma", "can", "tu", "do" };
	    assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

	    string e[4] = { "asa", "vivek", "", "chris" };
	    assert(subsequence(h, 7, e, 4) == 2);

	    string d[5] = { "ron", "ron", "ron", "chris", "chris" };
	    assert(enumerateRuns(d, 5) == 2);
	
	    string f[3] = { "vivek", "asa", "tim" };
	    assert(locateAny(h, 7, f, 3) == 2);
	    assert(flip(f, 3) == 3 && f[0] == "tim" && f[2] == "vivek");
	
	    assert(divide(h, 7, "donald") == 3);
	
	    cout << "All tests succeeded" << endl;
	}
