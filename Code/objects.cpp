class edge{
	public:
		int v;
		string label;
};

class inequality{
	public:
		int u;
		int v;
};

class graph_nodes{
	public:
		vector<int> u;
		vector<int> v;
		vector<bool> flag;
};

class bwt{
	public:
		vector<vector<int> > out_1;
		vector<vector<string> > out_2;
		vector<vector<int> > in;
		vector<bool> final;
		void build();
};

void bwt::build(){
	vector<string> row1;
	vector<int> row2;

	for(int i=0; i<n; i++){
		out_1.push_back(row2);
		out_2.push_back(row1);
		in.push_back(row2);
		final.push_back(false);
	}
}
