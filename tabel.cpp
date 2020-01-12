#include <iostream>
#include "tabel.h"
using namespace std;



Tabel::Tabel()
{
}

void Tabel::loadnames(string fnames){
	std::ifstream fle;
	fle.open(fnames, std::ios_base::in);
	if (!fle.is_open()) throw - 1;
	std::string st;
	while (!fle.eof()) {
		char a;
		fle.get(a);
		if (a == ';' || a == ',') {
			names.push_back(st);
			st = "";
			continue;
		}
		if (a == '\n' || a == '\r') continue;
		st += a;
	}

}
  
void Tabel::updatePresense(vector<vector<int>> tp){
	presents = tp;
}

string Tabel::getName(int pos){
	return (pos< names.size()) ?  names[pos] : "";
}

int Tabel::getNameNumber(){
	return names.size();
}
  
int Tabel::getLessonsNumber(){
	if(presents.empty()) return -1;
	int maxpl = 0;
	for(int i = 0; i< presents.size();++i){
	   int g = 0;
		for(int j = 0; j < presents[0].size();++j){
		  if(isStudentPresent(i, j) == 1) g = j + 1;
		}
	   if(g > maxpl) maxpl = g;
	}
	return maxpl;
}
	
int Tabel::isStudentPresent(int pos, int daynum){
	return presents[pos][daynum];
}

int Tabel::getPluces(int pos){
	int a = 0;
	for(int i = 0; i < presents[pos].size();++i){
		if(presents[pos][i] == 1) ++a;
	}
	return a;
}


