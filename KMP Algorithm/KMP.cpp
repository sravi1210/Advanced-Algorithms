#include <bits/stdc++.h>

using namespace std;

void search(string text, string pattern, vector<int> &lps, int n, int m){
	int i=0,j=0;

	// Simply search if current position in pattern is equal to text[position] or not. If yes continue till j gets equal to m, and then set j = lps[j-1] and if not same then accordingly set j or otherwise increase i by 1.
	while(i < n){
		if(pattern[j] == text[i]){
			i++;
			j++;
		}
		if(j == m){
			cout<<"Match Is Found At Index: "<<i-j<<endl;
			j = lps[j-1];
		}
		else if(i < n && pattern[j] != text[i]){
			if(j != 0){
				j = lps[j-1];
			}
			else{
				i++;
			}
		}
	}
	return;
}

void makeLPS(string pattern, vector<int> &lps, int m){
	lps[0] = 0;
	int i = 1;
	int len = 0;

	// lps[i] = maximum length of proper prefix which is also a suffix of  pattern[0:i]
	while(i < m){
		if(pattern[i] == pattern[len]){
			len++;
			lps[i] = len;
			i++;
		}
		else{
			if(len != 0){
				len = lps[len-1];
			}
			else{
				lps[i] = len;
				i++;
			}
		}
	}
	return;
}

int main(){
	string text = "Geeks for Geeks";
	string pattern = "Geek";
	int n = text.length();
	int m = pattern.length();

	vector<int> lps(m, -1);

	makeLPS(pattern, lps, m);

	search(text, pattern, lps, n, m);

	return 0;
}