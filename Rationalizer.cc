#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

struct number{
	int sign;
	int type;
	string wholePart;
	string rootPart;
};

string trimWhiteSpace(string cur){
	string result;
	for(auto c: cur){
		if (c != ' '){ result += c; }
	}
	return result;
}

string trimSign(string cur){
	string result;
	for(auto c: cur){
		if (c != '+' && c != '-'){ result += c; }
	}
	return result;
}

int findSub(string &src, string val){
	auto found = src.find(val, 0);
	if (found != string::npos){
		return found + val.length(); 
	}
	return -1;
}

pair<string, string> splitFrac(string &s){
	string denominator;
	string numerator;
	stack<int> seperators;
	bool doneNum = false;
	for (int i = 0; i < s.length(); i++){
		if (s[i] == '(' ){ seperators.push(i);}
		else if (s[i] == ')'){
			int j = seperators.top();
			seperators.pop();

			if (seperators.empty() && !doneNum){ 
				numerator = numerator + s.substr(j, i - j + 1); 
				doneNum = true; 
			}
			else if (seperators.empty() && doneNum){
				denominator = denominator + s.substr(j, i - j + 1);
			}
		}
	}
	return{numerator, denominator};
}

vector<string> parseFrac(string numerator){
	vector<string> result;
	int startIndex = 1;
	for (int i = 1; i < numerator.length(); i++){
		if (numerator[i] == '+' || numerator[i] == '-'){
			string cur = numerator.substr(startIndex, i - startIndex);
			result.push_back(cur);
			startIndex = i;
		}
	}
	if (startIndex < numerator.length()){
		result.push_back(trimWhiteSpace(numerator.substr(startIndex, numerator.length() - startIndex - 1)));
	}
	return result; 
}

number parseComponent(string &comp){
	number result;
	if (comp[0] == '-'){ result.sign = -1; }
	else { result.sign = 1; }

	int startIndex = findSub(comp, "sqrt");
	if (startIndex == -1){
		result.type = 0;
	}
	if (startIndex > 1){
		result.type = 2;
		result.wholePart = trimSign(comp.substr(0, startIndex - 1));
	}
	else { result.type = 1; }
	result.rootPart = trimSign(comp.substr(startIndex, comp.length()));

	return result;

}


void rationalize(string s){
	pair<string, string> splits = splitFrac(s);
	//cout << splits.first << endl;
	//cout << splits.second << endl;
	vector<string> numerator = parseFrac(trimWhiteSpace(splits.first));
	vector<string> denominator = parseFrac(trimWhiteSpace(splits.second));

	vector<number> numParts;
	vector<number> denParts;
	for (auto i : numerator){
		numParts.push_back(parseComponent(i));
	}
	for (auto i : denominator){
		denParts.push_back(parseComponent(i));
	}

	for (auto i: numParts){
		cout << "Type is " << i.type << endl;
		cout << i.wholePart << endl;
		cout << i.rootPart << endl;
		cout << endl << endl; 
	}

}
	


int main(){
	string s = "(10*(sqrt(5/3)) + 5 + 3)/ (((10*sqrt(4))/(4/7)) + 4+7)";
	rationalize(s);

}