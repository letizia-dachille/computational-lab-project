//------------------------------
// Sort richiamato nella funzione prefix_sorting
//------------------------------

void insertion_sort_prefix(string* prefixes, int partial_n, int* underlying_order) {
	string prox;
	int i, j, prox_order;

	for (i = 0 ; i < partial_n ; i++){
		prox = prefixes[i];
		prox_order = underlying_order[i];
		j = i;
		while ((j > 0) && (prefixes[j-1] > prox)){
			prefixes[j] = prefixes[j-1];
			underlying_order[j] = underlying_order[j-1];
			j--;
		}
		prefixes[j] = prox;
		underlying_order[j] = prox_order;
	} 

	return;
}

void merge_prefix(string* prefixes, int sx, int c, int dx, int* underlying_order){
	int i, j, k;
	string app[dx - sx + 1];
	int app_order[dx - sx + 1];
	i = sx ; j = c + 1 ; k = 0;

	while ((i <= c) && (j <= dx)){
		if (prefixes[i] <= prefixes[j]){
			app[k] = prefixes[i];
			app_order[k] = underlying_order[i];
			i++;
		}
		else {
			app[k] = prefixes[j];
			app_order[k] = underlying_order[j];
			j++;
		}
		k++;
	}
	for ( ; i <= c ; i++ , k++){
		app[k] = prefixes[i];
		app_order[k] = underlying_order[i];
	}
	for ( ; j <= dx ; j++ , k++){
		app[k] = prefixes[j];
		app_order[k] = underlying_order[j];
	}
	for (i = sx ; i <= dx ; i++){
		prefixes[i] = app[i - sx];
		underlying_order[i] = app_order[i - sx];
	}

	return;
}

void merge_insertion_sort_prefix(string* prefixes, int sx, int dx, int* underlying_order) {
	int c;

	if (dx - sx > (43 - 1)){
		c = (sx + dx)/2;
		merge_insertion_sort_prefix(prefixes, sx, c, underlying_order);
		merge_insertion_sort_prefix(prefixes, c+1, dx, underlying_order);
		merge_prefix(prefixes, sx, c, dx, underlying_order);
	}
	else{
		insertion_sort_prefix(&prefixes[sx], (dx - sx + 1), underlying_order);
	}
	
	return;
}

//------------------------------
// Sort richiamato nella funzione invert_bwt
//------------------------------

vector<string> insertion_sort_invert(vector<string> poss_labels, int sx, int partial_n, vector<int>* n_edges_per_label_in_chain, int n_chain) {
	string prox;
	int i, j;
	int prox_n[n_chain+1];

	for (i = sx ; i < partial_n ; i++){
		prox = poss_labels[i];
		for(int counter=1; counter<n_chain+1; counter++){
			prox_n[counter] = n_edges_per_label_in_chain[counter][i];
		}
		j = i;
		while ((j > sx) && (poss_labels[j-1] > prox)){
			poss_labels[j] = poss_labels[j-1];
			for(int counter=1; counter<n_chain+1; counter++){
				n_edges_per_label_in_chain[counter][j] = n_edges_per_label_in_chain[counter][j-1];
			}
			j--;
		}
		poss_labels[j] = prox;
		for(int counter=1; counter<n_chain+1; counter++){
			n_edges_per_label_in_chain[counter][j] = prox_n[counter];
		}
	} 

	return poss_labels;
}

vector<string> merge_invert(vector<string> poss_labels, int sx, int c, int dx, vector<int>* n_edges_per_label_in_chain, int n_chain){
	int i, j, k;
	string app[dx - sx + 1];
	int app_n[n_chain+1][dx - sx + 1];
	i = sx ; j = c + 1 ; k = 0;

	while ((i <= c) && (j <= dx)){
		if (poss_labels[i] <= poss_labels[j]){
			app[k] = poss_labels[i];
			for(int counter=1; counter<n_chain+1; counter++){
				app_n[counter][k] = n_edges_per_label_in_chain[counter][i];
			}
			i++;
		}
		else {
			app[k] = poss_labels[j];
			for(int counter=1; counter<n_chain+1; counter++){
				app_n[counter][k] = n_edges_per_label_in_chain[counter][j];
			}
			j++;
		}
		k++;
	}
	for ( ; i <= c ; i++ , k++){
		app[k] = poss_labels[i];
		for(int counter=1; counter<n_chain+1; counter++){
			app_n[counter][k] = n_edges_per_label_in_chain[counter][i];
		}
	}
	for ( ; j <= dx ; j++ , k++){
		app[k] = poss_labels[j];
		for(int counter=1; counter<n_chain+1; counter++){
			app_n[counter][k] = n_edges_per_label_in_chain[counter][j];
		}
	}
	for (i = sx ; i <= dx ; i++){
		poss_labels[i] = app[i - sx];
		for(int counter=1; counter<n_chain+1; counter++){
			n_edges_per_label_in_chain[counter][i] = app_n[counter][i - sx];
		}
	}

	return poss_labels;
}

vector<string> merge_insertion_sort_invert(vector<string> poss_labels, int sx, int dx, vector<int>* n_edges_per_label_in_chain, int n_chain){
	int c;
	
	if (dx - sx > (43 - 1)){
		c = (sx + dx)/2;
		poss_labels = merge_insertion_sort_invert(poss_labels, sx, c, n_edges_per_label_in_chain, n_chain);
		poss_labels = merge_insertion_sort_invert(poss_labels, c+1, dx, n_edges_per_label_in_chain, n_chain);
		poss_labels = merge_invert(poss_labels, sx, c, dx, n_edges_per_label_in_chain, n_chain);
	}
	else{
		poss_labels = insertion_sort_invert(poss_labels, sx, (dx - sx + 1), n_edges_per_label_in_chain, n_chain);
	}
	
	return poss_labels;
}
