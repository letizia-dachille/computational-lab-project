using namespace std;

void print_automaton(vector<edge>* automa){
	cout << endl;
	cout << "-----" << endl;
	cout << " DFA " << endl;
	cout << "-----" << endl << endl;
	cout << "Initial state: " << s << endl << endl;
	cout << "List of final states: ";
	for(int i: fs){
		cout << i << " ";
	}
	cout << endl << endl;
	cout << "Transition function: " << endl;
	for(int i=0; i<n; i++){
		for (edge e: automa[i]){
			cout << i << " " << e.v << " " << e.label << endl;
		}
	}
	cout << endl;
	cout << "-----" << endl << endl;
}

void print_bwt(bwt bwt_vec){
	cout << endl;
	cout << "-----" << endl;
	cout << " BWT " << endl;
	cout << "-----" << endl << endl;
	cout << "OUT:" << endl;
	for(int i=0; i<n; i++){
		int k=-1;
		cout << "[" << i << "] ~ [";
		for(int j: bwt_vec.out_1[i]){
			UNUSED(j);
			k++;
			if(k==0){
				cout << "(" << bwt_vec.out_1[i][k] << "," <<  bwt_vec.out_2[i][k] << ")" ;
			}else{
				cout << ", (" << bwt_vec.out_1[i][k] << "," <<  bwt_vec.out_2[i][k] << ")" ;
			}
		}
		cout << "]" << endl;
	}
	cout << endl;
	cout << "IN:" << endl;
	for(int i=0; i<n; i++){
		int k=-1;
		cout << "[" << i << "] ~ [";
		for(int j: bwt_vec.in[i]){
			k++;
			if(k==0){
				cout << j;
			}else{
				cout << ", " << j;
			}
		}
		cout << "]" << endl;
	}
	cout << endl;
	cout << "FINAL:" << endl;
	for(int i=0; i<n; i++){
		cout << "[" << i << "] ~ "<< bwt_vec.final[i] << endl;
	}
	cout << endl;
	cout << "-----" << endl << endl;
}
