#pragma GCC diagnostic error "-std=c++11"
#include <bits/stdc++.h>
#include <string>
#include <unordered_map>
#include <windows.h>
using namespace std;
using namespace chrono;

mt19937_64 twister(time(NULL));
uniform_int_distribution<int> randomnum(0,2147483647);
#define rand() randomnum(twister)

//MARKOV
//wenge is juruo

const int LENGTH=1000;

const int NUMBER=1;

const int threshold=1;

string _PT[55];

vector<string> text;

unordered_multimap<string,string> text_map[55];

string get_word(int dist) {
	auto range=text_map[dist].equal_range(_PT[dist]);
	auto l=range.first;
	auto r=range.second;
	int n=text_map[dist].count(_PT[dist]);
	//cout<<n<<endl;
	int index=rand()%n;
	for(auto i=l; i!=r; i++) {
		if(index<=0) {
			auto j=*i;
			string s=j.second;
			return s;
		}
		index--;
	}
}

string retrieve_word() {
	multiset<string> sample;
	//int k=0;
	while(1) {
		for(int i=1; i<=NUMBER; i++) {
			string s=get_word(i);
			sample.insert(s);
			if(sample.count(s)>=threshold) {
				return s;
			}
		}
		//k++;
	}
}

bool is_punc(string s){
	if(s=="\xe3\x80\x82"||s=="\xef\xbc\x8c"||s=="\xe3\x80\x81"||s=="\xef\xbc\x9f"||s=="\xef\xbc\x81"||s=="\xef\xbc\x9a")return true;
	else return false; 
}

bool is_ban(string s){
	if(s=="\xe2\x80\x9c"||s=="\xe2\x80\x9d")return true;
	else return false;
} 

int main() {
	auto start=system_clock::now();

	system("NewWCRF.exe");
	ifstream in;
	in.open("data/result.utf8");

	if(!in.is_open()) {
		cout<<"fail";
		return 0;
	}
	cout<<"read\n";

	string s;
	while(in>>s) {
		text.push_back(s);
	}

	cout<<"word to graph\n";

	for(int i=0; i<text.size()-NUMBER; i++) {
		for(int j=1; j<=NUMBER; j++) {
			if(text[i]==text[i+j]/*&&rand()%10!=0*/) {
				//cout<<1;
				continue;
			}
			text_map[j].insert(make_pair(text[i],text[i+j]));
		}
	}

	cout<<"generating...\n";

	{
		int p=rand()%(text.size()-NUMBER);
		for(int i=1; i<=NUMBER; i++) {
			_PT[i]=text[p+i];
		}
	}
	ofstream out("res.txt");
	int check1=0,check2=0;
	for(int i=1; i<=LENGTH; i++) {
		cout<<" \n"<<i<<"/"<<LENGTH<<": ";
		string s="";
		
		check2=check1;

		//s=retrieve_word();
		///*
		{
			int j=0;
			while(1) {
				s=retrieve_word();
				check1=is_punc(s);
				j++;
				if(!(check1&&check2))break;
			}
			cout<<j;
		}
		//*/

		
		if(!is_ban(s)){
			out<<s;
		}
		
		for(int i=NUMBER; i>1; i--) {
			_PT[i]=_PT[i-1];
		}
		_PT[1]=s;
	}

	cout<<"OK\n";
	//Sleep(1000);


	auto end=system_clock::now();
	auto duration=duration_cast<microseconds>(end-start);
	cout<<"Spent "<<double(duration.count())
	    *microseconds::period::num/microseconds::period::den<<" seconds."<<endl;
	system("pause");
	return 0;
}
