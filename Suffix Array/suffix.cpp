/* 
	O(N * log(N) * log(N)) method for creating suffix Array.

	Example :- banana - {banana, anana, nana, ana, na, a}
	5 - a
	1 - anana
	3 - ana
	0 - banana
	2 - nana
	4 - na
	
	After they are sorted a pattern can be searched using binary search in O(N * log(N))
*/

#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

void make_suffix_tree(vector<pair<pair<int,int>,int>> &sTree, string s, int n){

	// For first 2 characters.
	for(int i=0;i<n;i++){
		int index = i;
		int rank = s[i] - 'a';
		int nextRank = (i==n-1)?-1:s[i+1]-'a';
		sTree.push_back({{rank, nextRank}, index});
	}
	sort(sTree.begin(), sTree.end());

	vector<int> indices(n);

	// For first 4 characters, then first 8 characters and so on.
	for(int k=4;k<2*n;k*=2){

		// Set the new Rank for the sTree.
		int rank = 0;
		vector<int> tRank(n, 0);
		for(int i=0;i<n;i++){
			if(i-1 >= 0){
				if(sTree[i].F.F == sTree[i-1].F.F && sTree[i].F.S == sTree[i-1].F.S){
					tRank[i] = rank;
				}
				else{
					rank++;
					tRank[i] = rank;
				}
			}
			else{
				tRank[i] = rank;
			}
			indices[sTree[i].S] = i; 
		}
		for(int i=0;i<n;i++){
			sTree[i].F.F = tRank[i];
		}

		// Set the Next Rank for the sTree.
		for(int i=0;i<n;i++){
			int nextRank = sTree[i].S + (k/2);
			sTree[i].F.S = (nextRank < n)?(sTree[indices[nextRank]].F.F):-1;
		}

		sort(sTree.begin(), sTree.end());
	}
	return;
}

int main(){
	string input;
	cin>>input;

	int n = input.length();

	vector<pair<pair<int,int>,int>> sTree;   // ((Rank, Next_Rank), Index)

	make_suffix_tree(sTree, input, n);

	for(int i=0;i<n;i++){
		cout<<sTree[i].S<<" ";
	}
	cout<<endl;
	return 0;
}