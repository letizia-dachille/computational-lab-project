bwt calculate_bwt(vector<edge>* automa, string* labels){
	int underlying_order[n];
	vector<inequality> maximal_order;
	vector<vector<int> > chain_decomposition;
	int order[n];
	vector<vector<string> > adjacency_matrix;
	bwt bwt_vec;
	bwt_vec.build();

	find_underlying_order(automa, underlying_order, labels);

	maximal_order = find_maximal_order(automa, underlying_order, labels);

	chain_decomposition = find_chain_decomposition(automa, maximal_order, order);

	adjacency_matrix = find_adjacency_matrix(automa, order);

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
