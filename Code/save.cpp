void save(vector<edge>* automa){
	ofstream file("../Examples/automaton_out.txt");

	file << n << " " << m << " " << s << " " << nfs << " \n";
	for(int i: fs){
		file << i << " \n";
	}
	for(int i=0; i<n; i++){
		for (edge e: automa[i]){
			file << i << " " << e.v << " " << e.label << " \n";
		}
	}

	file.close();

	return;
}

void save_bwt(bwt bwt_vec){
	ofstream file("../Examples/bwt_out.txt");
	file << n << " \n";

	for(int i=0; i<n; i++){
		int k=0;
		for(int j: bwt_vec.out_1[i]){
			k++;
			UNUSED(j);
		}
		file << k << " ";
		for(int j=0; j<k; j++){
			file << bwt_vec.out_1[i][j] << "," << bwt_vec.out_2[i][j] << " ";
		}
		file << "\n";
	}
	for(int i=0; i<n; i++){
		int k=0;
		for(int j: bwt_vec.in[i]){
			UNUSED(j);
			k++;
		}
		file << k << " ";
		for(int j=0; j<k; j++){
			file << bwt_vec.in[i][j] << " ";
		}
		file << "\n";
	}
	for(int i=0; i<n; i++){
		file << bwt_vec.final[i] << " \n";
	}

	file.close();

	return;
}
