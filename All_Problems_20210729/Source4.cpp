#include <iostream>
#include <algorithm>
#include<vector>
#include<iomanip>
using namespace std;
ostream& operator<<(ostream& out, vector<string>& v) {
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << setw((v[i].size()>4) ? 5 : 7) << setfill(' ') <<"";
	}
	cout << endl;
	return out;
}
int counT = 0;
void combinations(int n, string available, string current = "") {

	if (current.size() == n) {
		for (size_t i = 0; i < current.size(); i++)
		{
			cout << "" << "" << current[i] << "  ";
		}
		cout << endl;
	}
	else {
		for (size_t i = 0; i < available.size(); i++)
		{
			string new_current = current + available[i];
			combinations(n, available, new_current);
		}
	}

}

void combinations(int n, vector<string> available, vector<string> current = {}) {
	if (current.size() == 3) {
		cout << current;
	}
	else {
		for (size_t i = 0; i < available.size(); i++)
		{
			current.push_back(available[i]);
			vector<string> new_current = current;
			current.pop_back();
			combinations(n, available, new_current);
		}	
	}
}



int main() {
	vector<string>v{ "Red","Green","Yellw"};
	string s = "RGY";
	combinations(3, v);
	combinations(3, s);

}