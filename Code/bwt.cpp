bwt calculate_bwt(vector<edge>* automa, string* labels){
	int underlying_order[n];
	vector<inequality> maximal_order;
	vector<vector<int> > chain_decomposition;
	int order[n];
	vector<vector<string> > adjacency_matrix;
	bwt bwt_vec;
	bwt_vec.build();

	find_underlying_order(automa, underlying_order, labels);

	//DEBUG
	/*cout << "underlying_order: " << endl;
	for(int i=0; i<n; i++){
		cout << underlying_order[i] << endl;
	}*/

	maximal_order = find_maximal_order(automa, underlying_order, labels);

	//DEBUG
	/*cout << "maximal_order: " << endl;
	for(inequality in: maximal_order){
		cout << in.u << " " << in.v << endl;
	}*/

	chain_decomposition = find_chain_decomposition(automa, maximal_order, order);

	//DEBUG
	/*cout << "chain_decomposition: " << endl;
	int c=0;
	for(vector<int> row: chain_decomposition){
		c++;
		cout << "chain " << c << ": ";
		for(int i: row){
			cout << i << " ";
		}
		cout << endl;
	}*/

	//DEBUG
	/*cout << "order: " << endl;
	for(int i=0; i<n; i++){
		cout << order[i] << endl;
	}*/

	adjacency_matrix = find_adjacency_matrix(automa, order);

	//DEBUG
	/*cout << "adjacency_matrix: " << endl;
	for(int i=0; i<n; i++){
		cout << "| " ;
		for(int j=0; j<n; j++){
			if(adjacency_matrix[i][j]==""){
				cout << "  | ";
			}else{
				cout << adjacency_matrix[i][j] << " | ";
			}
		}
		cout << endl;
	}*/

	int index1=-1, c1=0;
	
	for (vector<int> row1: chain_decomposition){
		c1++;
		for (int i: row1){
			index1++;
			for (int u: fs){
				if(u == i){
					bwt_vec.final[index1] = true;
				}
			}
			int index2=-1, c2=0;
			for (vector<int> row2: chain_decomposition){
				c2++;
				for (int j: row2){
					UNUSED(j);
					index2++;
					if (adjacency_matrix[index1][index2]!=""){
						bwt_vec.out_1[index1].push_back(c2);
						bwt_vec.out_2[index1].push_back(adjacency_matrix[index1][index2]);
						bwt_vec.in[index2].push_back(c1);
					}
				}
			}
		}
	}

	return bwt_vec;
}
