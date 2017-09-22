#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct point {
	double x, y;
};

vector<point> fill(string line) {
	//we have a line. now split line by spaces to have a new vector.
	line = line.substr(2);
	string buf;
	stringstream ss(line);
	vector<string> tokens;
	vector<point> row; //to return.
	vector<point> temp;

	while (ss >> buf) {
		tokens.push_back(buf);
	}

	//replace each colon with a space to seperate again.
	for (int i = 0; i < tokens.size(); i++) {
		replace(tokens.at(i).begin(), tokens.at(i).end(), ':', ' ');

		string colBuf;
		stringstream ss2(tokens.at(i));
		vector<string> line;

		while (ss2 >> colBuf) {
			line.push_back(colBuf);
		}

		double x = atoi(line.at(0).c_str());
		double y = atoi(line.at(1).c_str());

		point p;
		p.x = x;
		p.y = y;
		temp.push_back(p);
	}

	int count = 0;

	//fill an empty row.
	for(int i = 1; i < 68; i++){
		point p;
		p.x = i;
		p.y = 0;
		row.push_back(p);
	}

	for (int i = 0; i < temp.size(); i++) {
		point nonZero;
		nonZero.x = temp.at(i).x; //the index into row.
		nonZero.y = 0.18257;
		row[nonZero.x-1] = nonZero;
	}

	return row;

//	cout << "Printing row to add" << endl;
//	for(int i = 0; i < row.size(); i++){
//		cout << row.at(i).x << " " << row.at(i).y << endl;
//	}
}

int main() {

	string path = "Dataset/phishing.test";
	ifstream pipein(path.c_str());

	vector<string> tempLines;
	vector<vector<point> > matrix;
	vector<int> labels;

	for (string line; getline(pipein, line);) {
		tempLines.push_back(line);
		if (line.at(0) == '+') {
			labels.push_back(1);
		} else {
			labels.push_back(-1);
		}
	}

	for (int i = 0; i < tempLines.size(); i++) {
		vector<point> row = fill(tempLines.at(i));
		matrix.push_back(row);
	}

	//printing matrix / label vector
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << "(" << matrix.at(i).at(j).x << "," << matrix.at(i).at(j).y
					<< "), ";
		}
		cout << endl;
	}

	cout << matrix[6].size() << endl;

//	for (int i = 0; i < labels.size(); i++) {
//		cout << labels.at(i) << endl;
//	}

	return 0;
}
