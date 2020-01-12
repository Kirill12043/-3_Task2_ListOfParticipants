#pragma once

#include<vector>
#include<iostream>
#include <fstream>
using namespace std;


class Tabel
{
	vector<string> names;
	vector<vector<int>> presents;
public:
  Tabel();

  void loadnames(string fnames);
  
  void updatePresense(vector<vector<int>> tp);

  string getName(int pos);
  int getNameNumber();
  
  int getLessonsNumber();
  int isStudentPresent(int pos, int daynum);
  int getPluces(int pos);
};