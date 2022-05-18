//g++ -std=c++11 -Wall --pedantic -Wno-vla-extension -Wc++11-extensions main.cpp -o main.o

#include <iostream>
#include <cstdlib>
#include <fstream> 		
#include <vector>
#include <stack>
#include <queue>
#include <string>

using namespace std;

const int MAXN = 100000;

//funzione per eliminare warning sulle variabili non utilizzate
#define UNUSED(x) (void)(x)

//inizializzazione variabili globali
int n, s, m, nfs;
vector<int> fs;
string filename;

#include "objects.cpp"
#include "build.cpp"
#include "save.cpp"
#include "sort.cpp"
#include "functions_bwt.cpp"
#include "bwt.cpp"
#include "invert.cpp"
#include "output.cpp"

int main(){
	int choice1, choice2;
	string n_file;

	cout << endl;
	cout << "----------------------------------------" << endl;
	cout << "Burrows-Wheeler Transform (BWT) of a DFA" << endl;
	cout << "----------------------------------------" << endl << endl;
	cout << "Choose one of the following: " << endl;
	cout << " 1 - DFA to BWT" << endl;
	cout << " 2 - BWT to DFA" << endl;
	cout << "~ ";
	cin >> choice1;

	if(choice1 == 1){

		cout << endl;
		cout << "Choose the input automaton: [0-4 / out]" << endl;
		cout << "- if you want to choose a custom automaton write it in the 'automaton_0.txt' file" << endl;
		cout << "  in folder 'Examples', see 'info.txt' for file format, 'automaton_out.txt' is reserved" << endl;
		cout << "  for program output -" << endl;
		cout << "~ ";
		cin >> n_file;

		string line;
		filename = "../Examples/automaton_" + n_file + ".txt";

		ifstream file(filename.c_str());
		getline (file, line);
		n = intsubstring(line);
		file.close();

		vector<edge> automa[n];
		build_automa(automa);

		string labels[n];
		for(int i=0; i<n; i++){
			labels[i] = "";
		}
		for(int i=0; i<n; i++){
			for(edge e: automa[i]){
				labels[e.v] = e.label;
			}
		}

		cout << endl;
		cout << "Do you want to print the automaton? [0 - no/1 - yes]" << endl;
		cout << "~ ";
		cin >> choice2;

		if(choice2 == 1){
			print_automaton(automa);
		}

		bwt bwt_vec = calculate_bwt(automa, labels);

		cout << "Do you want to print the bwt? [0 - no/1 - yes]" << endl;
		cout << "~ ";
		cin >> choice2;

		if(choice2 == 1){
			print_bwt(bwt_vec);
		}

		save_bwt(bwt_vec);

	}else if(choice1 == 2){

		cout << endl;
		cout << "Choose the input bwt: [0-4 / out]" << endl;
		cout << "- if you want to choose a custom bwt write it in the 'bwt_0.txt' file" << endl;
		cout << "  in folder 'Examples', see 'info.txt' for file format, 'bwt_out.txt' is reserved" << endl;
		cout << "  for program output -" << endl;
		cout << "~ ";
		cin >> n_file;

		string line;
		filename = "../Examples/bwt_" + n_file + ".txt";

		ifstream file(filename.c_str());
		getline (file, line);
		n = intsubstring(line);
		file.close();

		bwt bwt_vec = build_bwt();

		int n=0;
		for (int i: bwt_vec.final){
			UNUSED(i);
			n++;
		}

		cout << endl;
		cout << "Do you want to print the bwt? [0 - no/1 - yes]" << endl;
		cout << "~ ";
		cin >> choice2;

		if(choice2 == 1){
			print_bwt(bwt_vec);
		}

		vector<edge> inverted_automa[n];
		invert_bwt(bwt_vec, inverted_automa);

		cout << "Do you want to print the automaton? [0 - no/1 - yes]" << endl;
		cout << "~ ";
		cin >> choice2;

		if(choice2 == 1){
			print_automaton(inverted_automa);
		}

		save(inverted_automa);

	}

	return 0;
}
