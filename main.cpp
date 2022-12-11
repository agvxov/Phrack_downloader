#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "dlbot.h"

#define DOMAIN "http://phrack.com/issues/"
#define ISSUES 69
//#define ISSUES_START 27
//#define ISSUES_START 46
#define ISSUES_START 64

using namespace std;

signed main(int argc, char* argv[]){
	string s;
	vector<vector<string>> v;

	//for(int i = 1; i <= ISSUES; i++){
	for(int i = ISSUES_START; i <= ISSUES; i++){
		vector<string> tempV;
		string d = DOMAIN + to_string(i) + "/1.html";
		cout << d << endl;

		s = bot::site_text(d.c_str());
		bot::findall(tempV, s, R"(issues/(.*\.html#article))");
		v.push_back(tempV);
	  //bot::site_findall(v, d.c_str(), R"(issues/\d*/\d*\.html#article)");
	}
//
//	for(int i = 0; i < v.size(); i++ ){
//		for(int h = 0; h < v[i].size(); h++){
//			cout << "\"" << v[i][h] << "\"" << endl;
//		}
//	}
//
//	return 0;

	//for(int i = 0; i < v.size(); i++){
	for(int i = 0; i < v.size(); i++){
		ofstream o;
		//o.open("PHRACK_issue_" + to_string(i + 1));
		o.open("PHRACK_issue_" + to_string(i + ISSUES_START));
		for(int h = 0; h < v[i].size(); h++){
			cout << "\"" << v[i][h] << "\"" << endl;
			string d = DOMAIN + v[i][h];
			o << bot::site_text(d.c_str());
		}
		o.close();
	}

	return 0;
}

/*
	MAIN TILL 27


*/
