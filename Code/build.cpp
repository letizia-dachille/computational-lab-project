using namespace std;

int intsubstring(string line){
	string blank = " ";
	return(atoi((line.substr(0, line.find(blank))).c_str()));
}

string nextinline(string line){
	string blank = " ";
	return(line.substr(line.find(blank) + 1));
}

void build_automa(vector<edge>* automa){
	string line;
	int u;
	edge e;

	ifstream file(filename.c_str());

	getline (file, line);
	line = nextinline(line);
	m = intsubstring(line);
	line = nextinline(line);
	s = intsubstring(line);
	line = nextinline(line);
	nfs = intsubstring(line);

	for(int i=1; i<=nfs; i++){
		getline (file, line);
		fs.push_back(intsubstring(line));
	}

	for(int i=1; i<=m; i++){
		getline (file, line);
		u = intsubstring(line);
		line = nextinline(line);
		e.v = intsubstring(line);
		line = nextinline(line);
		e.label = (line.substr(0, line.find(" "))).c_str();
		automa[u].push_back(e);
	}

	file.close();
}

bwt build_bwt(){
	bwt bwt_vec;
	bwt_vec.build();
	string line;
	int c;

	ifstream file(filename.c_str());
	getline (file, line);
	for(int i=0; i<n; i++){
		getline (file, line);
		c = intsubstring(line);
		for(int j=1; j<=c; j++){
			line = nextinline(line);
			bwt_vec.out_1[i].push_back(atoi((line.substr(0, line.find(","))).c_str()));
			line = line.substr(line.find(",") + 1);
			bwt_vec.out_2[i].push_back((line.substr(0, line.find(" "))).c_str());
		}
	}
	for(int i=0; i<n; i++){
		getline (file, line);
		c = intsubstring(line);
		for(int j=1; j<=c; j++){
			line = nextinline(line);
			bwt_vec.in[i].push_back(intsubstring(line));
		}
	}
	for(int i=0; i<n; i++){
		getline (file, line);
		bwt_vec.final[i] = intsubstring(line);
	}

	file.close();

	return bwt_vec;
}

