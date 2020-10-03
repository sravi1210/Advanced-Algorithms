#include <bits/stdc++.h>
using namespace std;

void findEven(vector<int> &evenLP, string input, int n){
	int l=0,r=-1;
	for(int i=0;i<n;i++){
		int k = (i>r)?0:min(evenLP[l+r-i-1], r-i+1);

		while(i-k-1>0 && i+k<n && input[i-k-1]==input[i+k]){
			k++;
		}

		evenLP[i] = k;
		k--;
		if(i+k>r){
			l = i-k-1;
			r = i+k;
		}
	}
	return;
}

void findOdd(vector<int> &oddLP, string input, int n){
	int l=0,r=-1; // left-right of the current pallindromic substring found.
	for(int i=0;i<n;i++){      // looping through considering the ith to be the center of a pallindrome.
		int k = (i>r)?1:(min(oddLP[l+r-i], r-i+1));   // finding k to do the brute method, where (i+j) = (l+r) gives j = (l+r-i) ie. the position symmetric to i in (l, r) or r-i+1 if it exceeds boundary. In case of i>r take k = 1 and perform brute.
		
		while(i-k>=0 && i+k<n && input[i-k]==input[i+k]){
			k++;
		}

		oddLP[i] = k;
		k--;
		if(i+k > r){
			l = i-k;
			r = i+k;
		}
	}
	return;
}	


int main(){
	// Algorithm to find the longest pallindromic substring in a given string in O(N), ie linear time complexity.
	string input;
	cin>>input;

	int n = input.length();

	vector<int> oddLP(n, 1);
	vector<int> evenLP(n, 1);

	findOdd(oddLP, input, n);
	findEven(evenLP, input, n);

	int ans = 1;
	for(int i=0;i<n;i++){
		ans = max(ans, max((2*oddLP[i]-1), (2*evenLP[i])));
	}

	cout<<"Longest Pallindrome Is Of Length: "<<ans<<endl;

	return 0;
}