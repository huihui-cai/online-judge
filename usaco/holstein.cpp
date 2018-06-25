/*
ID: lxh36422
PROG: holstein
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
using namespace std;

vector<int> target;
vector<int> finalRes;

void sum(const vector<vector<int> >& input, const vector<int>& pos, vector<int>& sumVec) {
	sumVec.resize(target.size());

	for (int i = 0; i < pos.size(); ++i) {
		int x = pos[i];
		for (int j = 0; j < input[x].size(); ++j) {
			sumVec[j] += input[x][j];
		}
	}
}

bool lessEqual(const vector<int>& input1, const vector<int>& input2) {
	if (input1.size() != input2.size()) {
		return false;
	}
	for (int i = 0; i < input1.size(); ++i) {
		if (input1[i] > input2[i]) {
			return false;
		}
	}
	return true;
}

void dump_vec(const vector<int>& input) {
	for (int i = 0; i < input.size(); i++) {
		cout << input[i] << " ";
	}
	cout << endl;
}

void dfsFind(const vector<vector<int> >& input, int i, vector<int>& current) {
	if (i > input.size() ) {
		return;
	}

	vector<int> sumResult;
	sum(input, current, sumResult);
	//dump_vec(current);
	//dump_vec(sumResult);
	if (lessEqual(target, sumResult)) {
		if (finalRes.size() == 0 || current.size() < finalRes.size()) {
			finalRes = current;
		}
	} else {
		for (int j = i; j < input.size(); ++j) {
			current.push_back(j);
			dfsFind(input, j + 1, current);
			current.pop_back();
		}
	}
}

int main() {
	ifstream fin("holstein.in");
	ofstream fout ("holstein.out");
	vector<vector<int> > input;
	int V, G;

	fin >> V;
	target.resize(V);
	for (int i = 0; i < V; ++i) {
		fin >> target[i];
	}

	fin >> G;
	input.resize(G);
	for (int i = 0; i < G; ++i) {
		input[i].resize(V);
		for (int j = 0; j < V; ++j) {
			fin >> input[i][j];
		}
	}

	//for (int i = 0; i < input.size(); ++i) {
	//	for (int j = 0; j < input[i].size(); ++j) {
	//		cout << input[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	vector<int> current;
	//for (int i = 0; i < input.size(); ++i) {
		dfsFind(input, 0, current);
	//}

	fout << finalRes.size();
	for (int i = 0; i < finalRes.size(); ++i) {
		fout << " " << finalRes[i] + 1;
	}
	fout << endl;
	fin.close();
	fout.close();
	return 0;
}

