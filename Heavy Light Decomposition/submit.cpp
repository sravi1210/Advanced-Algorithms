#include <bits/stdc++.h>
using namespace std;
#define faster()   ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);cerr.tie(NULL);int tab;auto geti=[&](){cin>>tab;return tab;};

class Tree {
	private:
		int ind;
		int countNode;
		int chain;
		int mdepth;
		vector<vector<int>> tree;
		vector<int> depth;
		vector<vector<int>> parent;
		vector<int> subTree;
		map<pair<int,int>, int> index;    //((node, node), index)
		map<int, pair<int,int>> rindex;  //(index, (node, node))
		map<int, int> cost;       //(index, cost)
		vector<int> baseTree;
		vector<int> position;  //index of nodes in baseTree
		vector<int> segTree;
		vector<int> chainNo;
		vector<int> chainHead;
		vector<int> posInSegTree; //position of edges in segTree
		vector<int> posInBaseTree; //edges at index in baseTree;
	public:
		Tree(int n, vector<vector<int>> edges){
			ind = 1;
			chain = 0;
			mdepth = 14;
			countNode = n;
			depth = vector<int>(n, 0);
			subTree = vector<int>(n, 0);
			chainNo = vector<int>(n, 0);
			position = vector<int>(n, 0);
			baseTree = vector<int>(n, -1);
			segTree = vector<int>(6*n, -1);
			posInSegTree = vector<int>(n-1, -1);
			posInBaseTree = vector<int>(n, -1);

			for(int i=0;i<n;i++){
				vector<int> temp;
				tree.push_back(temp);
			}

			for(int i=0;i<n-1;i++){
				int x = edges[i][0];
				int y = edges[i][1];
				int c = edges[i][2];
				tree[x].push_back(y);
				tree[y].push_back(x);
				int a = min(x, y);
				int b = max(x, y);
				index[{a, b}] = i;
				rindex[i] = {a,  b};
				cost[i] = c;
			}
			for(int i=0;i<n;i++){
				vector<int> temp;
				for(int j=0;j<=mdepth;j++){
					temp.push_back(-1);
				}
				parent.push_back(temp);
			}

			for(int i=0;i<=mdepth;i++){
				chainHead.push_back(-1);
				if(i==0){
					chainHead[i] = 0;
				}
			}
		}


		void dfs(int curr, int pa){
			int size = tree[curr].size();
			int curr_depth = 0;
			if(pa != -1){
				curr_depth = 1 + depth[pa];
			}
			depth[curr] = curr_depth;
			parent[curr][0] = pa;
			
			for(int i=0;i<size;i++){
				int child = tree[curr][i];
				if(child != pa){
					dfs(child, curr);
					subTree[curr] += subTree[child];
				}
			}
			subTree[curr] += 1;
			return;
		}

		void hld(int curr, int pa){
			int size = tree[curr].size();
			int mnode = -1;
			int mcost = -1;
			int nodes = -1;
			for(int i=0;i<size;i++){
				int child = tree[curr][i];
				if(child != pa){
					int a = min(curr, child);
					int b = max(curr, child);
					int ccost = cost[index[{a, b}]];
					if(nodes < subTree[child]){
					    nodes = subTree[child];
						mnode = child;
						mcost = ccost;
					}
				}
			}
			if(mnode == -1)return;
			baseTree[ind] = mcost;
			position[mnode] = ind;
			posInBaseTree[ind] = index[{min(mnode, curr), max(mnode, curr)}];  //edge id at this position
			ind++;
			chainNo[mnode] = chain;
			hld(mnode, curr);

			for(int i=0;i<size;i++){
				int child = tree[curr][i];
				if(child != pa && child != mnode){
					chain++;
					if(chainHead[chain] == -1){
						chainHead[chain] = child;
					}
					chainNo[child] = chain;
					int a = min(child, curr);
					int b = max(child, curr);
					int ccost = cost[index[{a, b}]];
					baseTree[ind] = ccost;
					position[child] = ind;
					posInBaseTree[ind] = index[{a, b}];
					ind++;
					hld(child, curr);
				}
			}
			return;
		}

		void make_sgt(int s, int e, int ref){
			if(s == e){
				segTree[ref] = baseTree[s];
				posInSegTree[posInBaseTree[s]] = ref;
				return;
			}
			int m = (s+e)/2;
			int c1 = 2*ref;
			int c2 = c1+1;
			make_sgt(s, m, c1);
			make_sgt(m+1, e, c2);
			segTree[ref] = max(segTree[c1], segTree[c2]);
			return;
		}

		void make_LCA(){
			int size = countNode;
			for(int h=1;h<=mdepth;h++){
				for(int i=0;i<size;i++){
					if(parent[i][h-1] != -1){
						parent[i][h] = parent[parent[i][h-1]][h-1];
					}
				}
			}
			return;
		}

		int find_LCA(int x, int y){
			if(depth[x] < depth[y]){
				swap(x, y);
			}
			
			int diff = depth[x] - depth[y];
			for(int h=mdepth;h>=0;h--){
				int val  = (1<<h);
				if((val & diff) == val){
					diff = (diff^val);
					x = parent[x][h];
				}
			}
			
			if(x == y){
				return x;
			}
			for(int h=0;h<=mdepth;h++){
				if(parent[x][h] == parent[y][h]){
					return parent[x][h];
				}
			}
			return -1;
		}

		int query_tree(int s, int e, int fs, int fe, int ref){
			if(s>=fs && e<=fe){
				return segTree[ref];
			}
			if(fe < s || fs > e || s > e){
				return -1;
			}
			int m = (s+e)/2;
			int c1 = 2*ref;
			int c2 = c1 + 1;
			int val1 = query_tree(s, m, fs, fe, c1);
			int val2 = query_tree(m+1, e, fs, fe, c2);
			int val = max(val1, val2);
			return val;
		}

		int query_up(int x, int y){
			if(x == y)return -1;
			int chainY = chainNo[y];
			int ans  = -1;
			while(true){
				int chainX = chainNo[x];
				if(chainX == chainY){
					if(x == y)break;
					int val = query_tree(0, countNode-1, position[y]+1, position[x], 1);
					ans = max(ans, val);
					break;
				}
				else{
					int head = chainHead[chainX];
					int val = query_tree(0, countNode-1, position[head]+1, position[x], 1);
					ans = max(ans, val);
					x = parent[head][0];
					int c = cost[index[{min(x, head), max(x, head)}]];
					ans = max(ans, c);
				}
			}
			return ans;
		}

		void query(int x, int y){
			int lca = find_LCA(x, y);
			int x_lca = query_up(x, lca);
			int y_lca = query_up(y, lca);
			int ans = max(x_lca, y_lca);
			cout<<ans<<endl;
			return;
		}

		void change(int ref, int c){
			int node = posInSegTree[ref];
			cost[ref] = c;
			segTree[node] = c;
			while(node > 0){
				node = (node%2==0)?node/2:(node/2)-1;
				int c1 = node*2;
				int c2 = node*2 + 1;
				segTree[node] = max(c1, c2);
			}
			return;
		}


		void printAll(){
			cout<<"chainNo ";
			printVec(chainNo);
			cout<<"position: ";
			printVec(position);
			cout<<"baseTree ";
			printVec(baseTree);
			cout<<"chainHead ";
			printVec(chainHead);
			cout<<"subTree ";
			printVec(subTree);
			cout<<"segTree ";
			printVec(segTree);
			return;
		}

		void printVec(vector<int> vec){
			int size = vec.size();
			for(int i=0;i<size;i++){
				cout<<vec[i]<<" ";
			}
			cout<<endl;
			return;
		}
};

int main(){
    faster();
    int t;
    cin>>t;
    while(t>0){
    	int n;
    	cin>>n;
    	if(n == 1){
    	    t--;
    	    continue;
    	}
    	vector<vector<int>>edges;
    	for(int i=0;i<n-1;i++){
    		int x, y, c;
    		cin>>x>>y>>c;
    		x--;y--;
    		vector<int> temp;
    		temp.push_back(x);
    		temp.push_back(y);
    		temp.push_back(c);
    		edges.push_back(temp);
    	}
    	
    	Tree tree(n, edges);
    	tree.dfs(0, -1);
    	tree.hld(0, -1);
    	tree.make_sgt(0, n-1, 1);
    	tree.make_LCA();
        // tree.printAll();
    	bool loop = true;
    	while(loop){
    		string s;
    		cin>>s;
    		if(s[0] == 'D'){
    			loop = false;
    			continue;
    		}
    		if(s[0] == 'Q'){
    			int a, b;
    			cin>>a>>b;
    			a--;b--;
    			tree.query(a, b);
    		}
    		else if(s[0] == 'C'){
    			int ref, ct;
    			cin>>ref>>ct;
    			ref--;
    			tree.change(ref, ct);
    		}
    	}
    	t--;
    }
    return 0;
}