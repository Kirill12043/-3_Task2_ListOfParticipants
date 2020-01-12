#include <vector>
#include <iostream>
#include "recogniser.h"
#include "tabel.h"
using namespace std;

int count_percent(int pct, int maxv){
  return pct*100/maxv;
}

int get_mark(int a){
if(a>50&&a<=70) return 3;
	if(a>70&&a<=90) return 4;
	if(a>90) return 5;
	return 2;
}


int main(){
  Recognizer t;
  vector<vector<int>> data;

  t.load("table_1.jpg");
  data = t.recognise();

  Tabel a;
  a.loadnames("list_of_surnames_1.txt"); 
  std::ofstream outpt;
  if (!data.empty()) {
     a.updatePresense(data); 
     outpt.open("test_1.txt", std::ofstream::out | std::ofstream::trunc);
     for (int j = 0; j < a.getNameNumber(); ++j) {
	outpt << j << ". "<<a.getName(j)<<" ";
	for (int k = 0; k < a.getLessonsNumber(); ++k) {
	   if (a.isStudentPresent(j,k) == 1) outpt << "+|";
	   else outpt << " |";
	}
     int pct = count_percent(a.getPluces(j), a.getLessonsNumber());
     outpt <<" "<< pct <<"%"<< " РћС†РµРЅРєР°: "<< get_mark(pct)<<"\n";
     }
   outpt.close();
   }

}