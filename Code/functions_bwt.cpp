//------------------------------
// Calcolo ordine fondamentale
//------------------------------

//Calcolo albero di copertura orientato

void spanning_tree(vector<edge>* automa, vector<edge>* tree){
	bool app[n];

	for (int i=0; i<n; i++){
  		app[i] = false;
  	}
  	
  	stack<int> st;
  	st.push(s);
  	app[s] = true;

  	do{
  		int u = st.top();
  		st.pop();
  		for (edge e: automa[u]){
	  		int v = e.v;
	    	if (!app[v]){
	    		app[v] = true;
	    		edge en;
	    		en.v = v;
	    		en.label = e.label;
				tree[u].push_back(en);
				st.push(v);
	    	}
	    }
  	}while(!st.empty());
}

//Calcolo dei prefissi e quindi ordinamento tramite merge-insertion sort

void previsit(int node, vector<edge>* tree, string* labels, string* prefixes){

	if (!tree[node].empty()){
		for (edge e: tree[node]){
			prefixes[e.v] = labels[e.v] + prefixes[node];
			previsit(e.v, tree, labels, prefixes);
		}
	}

	return;
}

void prefix_sorting(vector<edge>* tree, string* labels, int* underlying_order){
	string prefixes[n];
	prefixes[s]="";

	previsit(s, tree, labels, prefixes);

	merge_insertion_sort_prefix(prefixes, 0, n - 1, underlying_order);
}

//Funzione principale

void find_underlying_order(vector<edge>* automa, int* underlying_order, string* labels){
	vector<edge> tree[n];

	spanning_tree(automa, tree);

	for(int i=0; i<n; i++){
		underlying_order[i] = i;
	}

	prefix_sorting(tree, labels, underlying_order);
}

//------------------------------
// Calcolo ordine massimale
//------------------------------

//Funzione principale

vector<inequality> find_maximal_order(vector<edge>* automa, int* underlying_order, string* labels){
	vector<inequality> maximal_order;
	graph_nodes G;
	int i,j, dim=0;

	//Costruzione nodi di G
	for (int u=0; u<n; u++){
		for (int v=0; v<n; v++){
			if(labels[u]==labels[v]){
				i=0;
				while(underlying_order[i]!=u){
					i++;
				}
				j=0;
				while(underlying_order[j]!=v){
					j++;
				}
				if(i<=j){
					G.u.push_back(u);
					G.v.push_back(v);
					G.flag.push_back(0);
					dim++;
				}
			}
		}
	}
	
	//Costruzione archi di G
	vector<int> adj_list[dim];

	for (int e1=0; e1<dim; e1++){
		for (int e2=0; e2<dim; e2++){
			int flag=0;
			for(edge e: automa[G.u[e1]]){
				if (e.v == G.u[e2]){
					flag++;
					break;
				}
			}
			for(edge e: automa[G.v[e1]]){
				if (e.v == G.v[e2]){
					flag++;
					break;
				}
			}
			if (flag == 2){
				adj_list[e1].push_back(e2);
			}
		}
	}

	//Prima contrassegnazione
	for (int u1=0; u1<n; u1++){
		for (edge e: automa[u1]){
			int u = e.v;
			for (int v1=0; v1<n; v1++){
				for (edge e1: automa[v1]){		
					int v = e1.v;
					if(labels[u]==labels[v]){
						i=0;
						while(underlying_order[i]!=u){
							i++;
						}
						j=0;
						while(underlying_order[j]!=v){
							j++;
						}
						if(i<=j){
							i=0;
							while(underlying_order[i]!=v1){
								i++;
							}
							j=0;
							while(underlying_order[j]!=u1){
								j++;
							}
							if(i<=j){
								for (int k=0; k<dim; k++){
									if (G.u[k] == u && G.v[k] == v){
										G.flag[k] = 1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	//Seconda contrassegnazione
	bool app[n];

	for (int i=0; i<n; i++){
  		app[i] = false;
  	}

  	stack<int> st;

  	for (int i=0; i<dim; i++){
  		if(G.flag[i] == 1){
  			st.push(i);
  			app[i] = true;
  		}
	}
  	while(!st.empty()){
  		i = st.top();
  		st.pop();
  		for (int v: adj_list[i]){
	    	if (!app[v]){
	    		app[v] = true;
	    		G.flag[i] = 1;
				st.push(i);
	    	}
	    }
  	}

  	//Rimozione coppie contrassegnate
  	inequality in;

  	for (int i=0; i<n; i++){
  		for (int j=i; j<n; j++){
  			int u = underlying_order[i];
  			int v = underlying_order[j];
  			int flag = 0;
  			for (int k=0; k<dim; k++){
  				if (G.u[k]==u && G.v[k]==v){
  					if (G.flag[k] == 0 && u!=v){
  						in.u = u;
  						in.v = v;
  						maximal_order.push_back(in);
  					}
  					flag = 1;
  				}
  			}
  			if(flag == 0  && u!=v){
  				in.u = u;
  				in.v = v;
  				maximal_order.push_back(in);
  			}
  		}
  	}

	return maximal_order;
}

//------------------------------
// Calcolo decomposizione in catene
//------------------------------

//Algoritmo di Hopcroft e Karp per l'abbinamento massimo

bool BFS_hk(vector<int>* G, int* pair, int* dist){
	queue<int> Q;

	for (int i=0; i<n; i++){
		if (pair[i]==2*n){
			dist[i]=0;
			Q.push(i);
		}else{
			dist[i]=MAXN;
		}
	}

	dist[2*n]=MAXN;

	while(!Q.empty()){
		int i=Q.front();
		Q.pop();
		if(dist[i]<dist[2*n]){
			for(int j: G[i]){
				if(dist[pair[j]] == MAXN){
					dist[pair[j]] = dist[i] + 1;
					Q.push(pair[j]);
				}
			}
		}
	}

	return dist[2*n]!=MAXN;
}

bool DFS_hk(vector<int>* G, int* pair, int* dist, int i){

	if (i!=2*n){
		for(int j: G[i]){
			if(dist[pair[j]] == dist[i] + 1){
				if(DFS_hk(G, pair, dist, pair[j]) == true){
					pair[j] = i;
					pair[i] = j;
					return true;
				}
			}
		}
		dist[i] = MAXN;
		return false;
	}

	return true;
}

void maximum_matching_hk(vector<int>* G, int* pair){
	int dist[2*n+1];

	for (int i=0; i<2*n; i++){
		pair[i] = 2*n;
	}
	while(BFS_hk(G, pair, dist)==true){
		for (int i=0; i<n; i++){
			if (pair[i] == 2*n){
				DFS_hk(G, pair, dist, i);
			}
		}
	}
}

//Funzione principale

vector<vector<int> > find_chain_decomposition(vector<edge>* automa, vector<inequality> maximal_order, int* order){
	vector<vector<int> > chain_decomposition;
	vector<int> G[2*n];
	int pair[2*n];

	//Costruzione grafo bipartito
	for(inequality in: maximal_order){
		G[in.u].push_back(in.v+n);
		G[in.v+n].push_back(in.u);
	}

	//Algoritmo di Hopcroft e Karp
	maximum_matching_hk(G, pair);

	//Ricostruzione G a partire dall'abbinamento individuato, con aggiunta coppie desiderate
	for(int i=0; i<2*n; i++){
		G[i].clear();
	}

	for(int i=0; i<n; i++){
		if (pair[i]!=2*n){
			G[i].push_back(pair[i]);
			G[pair[i]].push_back(i);
		}
		if (pair[i]!=i+n){
			G[i].push_back(i+n);
			G[i+n].push_back(i);
		}
	}

	//Calcolo componenti connesse
	stack<int> st;
	vector<int> chain;
	bool app[2*n];

	for (int i=0; i<2*n; i++){
		app[i] = false;
	}
	//Controllo quali nodi nella parte a destra del grafo hanno un solo arco incidente, 
	//infatti è da essi che partono le catene da individuare (le catene terminano poi nella parte a sinistra)
	for (int i=n; i<2*n; i++){
  		if(G[i].size() == 1){
  			st.push(i);
  		}
  	}

  	int c=-1;
	int c1=-1;

  	while(!st.empty()){
  		int i = st.top();
  		st.pop();
  		if(G[i].size() == 1 && i>=n){
  			c++;
  			chain_decomposition.push_back(chain);
  		}
  		app[i] = true;
	  	for (int u: G[i]){
		    if (!app[u]){
		    	app[u] = true;
		    	if(chain_decomposition[c].empty()){
		    		c1++;
			    	chain_decomposition[c].push_back(u);
			    	order[u] = c1;
		    	}else{
		    		if(chain_decomposition[c].back() != (u%n)){
			    		c1++;
			    		chain_decomposition[c].push_back(u%n);
			    		order[u%n] = c1;
			    	}
		    	}
		    	st.push(u);
		    }
		}
  	}

	return chain_decomposition;
}

//------------------------------
// Calcolo matrice di adiacenza
//------------------------------

//Funzione principale

vector<vector<string> > find_adjacency_matrix(vector<edge>* automa, int* order){
	vector<vector<string> > adjacency_matrix;
	vector<string> row;

	for (int i=0; i<n; i++){
		adjacency_matrix.push_back(row);
		for (int j=0; j<n; j++){
			adjacency_matrix[i].push_back("");
		}
	}

	for (int u=0; u<n; u++){
		for (edge e: automa[u]){
			int v=e.v;
			string label=e.label;
			adjacency_matrix[order[u]][order[v]] = label;
		}
	}

	return adjacency_matrix;
}
