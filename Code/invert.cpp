void invert_bwt(bwt bwt_vec, vector<edge>* automa){

	//Ricostruzione funzione pi
	int n_chain = 0;
	int in_degree[n];

	for(int i=0; i<n; i++){
		for(int j: bwt_vec.out_1[i]){
			if (j > n_chain){
				n_chain = j;
			}
		}
	}

	int n_edges_in_chain[n_chain+1];
	int chain_decomposition[n];

	for(int i=0; i<n_chain+1; i++){
		n_edges_in_chain[i]=0;
	}
	for(int i=0; i<n; i++){
		for(int j: bwt_vec.out_1[i]){
			n_edges_in_chain[j]++;
		}
	}
	for(int i=0; i<n; i++){
		in_degree[i]=0;
		for(int j: bwt_vec.in[i]){
			UNUSED(j);
			in_degree[i]++;
		}
	}

	int j = 0;

	for(int i=1; i<n_chain+1; i++){
		int c = 0;
		while(c < n_edges_in_chain[i]){
			c = c + in_degree[j];
			chain_decomposition[j]=i;
			j++;
		}
	}
	
	//Ricostruzione funzione lambda
	int n_labels = 0;
	vector<string> poss_labels;
	vector<int> n_edges_per_label_in_chain[n_chain+1];

	for(int i=0; i<n; i++){
		for(string j: bwt_vec.out_2[i]){
			int flag=0;
			for(string u: poss_labels){
				if(u==j){
					flag = 1;
					break;
				}
			}
			if (flag==0){
				n_labels++;
				poss_labels.push_back(j);
			}
		}
	}
	for(string u: poss_labels){
		for (int k = 1; k < n_chain+1; k++){
			n_edges_per_label_in_chain[k].push_back(0);
		}
	}
	for(int i=0; i<n; i++){
		int u=0;
		for(string j: bwt_vec.out_2[i]){
			int k=0;
			for(string u: poss_labels){
				if(u==j){
					break;
				}else{
					k++;
				}
			}
			n_edges_per_label_in_chain[bwt_vec.out_1[i][u]][k]++;
			u++;
		}
	}

	poss_labels = merge_insertion_sort_invert(poss_labels, 0, n_labels-1, n_edges_per_label_in_chain, n_chain);

	string labels[n];

	int node = 0;
	for (int j=1; j<n_chain+1; j++){
		int i=0;
		for (int k: n_edges_per_label_in_chain[j]){
			int c=0;
			while(c < k){
				if(in_degree[node]==0){
					labels[node]="";
				}else{
					c = c + in_degree[node];
					labels[node]=poss_labels[i];
				}
				node++;
			}
			i++;
		}
	}

	vector<int> in_app[n];

	for(int i=0; i<n; i++){
		for(int j: bwt_vec.in[i]){
			in_app[i].push_back(j);
		}
	}
	
	//Costruzione automa
	bool flag;
	m = 0;

	for(int i=0; i<n; i++){
		int k=-1;
		for(int j: bwt_vec.out_1[i]){
			k++;
			flag = false;
			//coppia (k,c)=(j,bwt_vec.out_2[i][k])
			//pi(vi)=chain_decomposition[i]
			for(int u=0; u<n; u++){
				if(chain_decomposition[u]==j && labels[u]==bwt_vec.out_2[i][k]){
				int c=0;
					for(int v: in_app[u]){
						if(chain_decomposition[i]==v){
							//(i,j)=(i,u)
							edge e;
							e.v=u;
							e.label=labels[u];
							automa[i].push_back(e);
							m++;
							in_app[u][c]=0;
							flag = true;
							break;
						}
						c++;
					}
				}
				if(flag){
					break;
				}
			}
		}
	}

	//Individuazione sorgente
	for(int i=0; i<n; i++){
		if(labels[i]==""){
			s = i;
			break;
		}
	}

	//Individuazione stati finali
	fs.clear();
	nfs = 0;
	
	for(int i=0; i<n; i++){
		if(bwt_vec.final[i]){
			fs.push_back(i);
			nfs++;
		}
	}
}
