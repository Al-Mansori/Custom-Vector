#include<iostream>
#include<vector>
#include<fstream>
#include<set>
#include<sstream>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

template<class T>
class MySet {
protected:
	vector<T>vs;
	vector<T>intersection;
	T* Data = nullptr;


public:
	MySet() = default;
	void removeDoblecet() {
		for (int i = 0; i < vs.size(); ++i) {
			T temp = vs[i];
			for (int j = i + 1; j < vs.size(); ++j) {
				if (vs[j] == temp) {
					vs.erase(vs.begin() + j);
				}
			}
		}

	}
	void takeDoblecet() {
		for (int i = 0; i < vs.size(); ++i) {
			T temp = vs[i];
			for (int j = i + 1; j < vs.size(); ++j) {
				if (vs[j] == temp) {
					intersection.push_back(temp);
				}
			}

		}
	}

	void addToSet(T s) {
		vs.push_back(s);
		removeDoblecet();
	}
	void removeFromSet(T s) {
		vs.erase(find_if(vs.begin(), vs.end(), [s](auto& a) {return a == s; }));


	}
	void clearSet() {
		vs.clear();
	}

	bool find(T s) {
		return std::find(vs.begin(), vs.end(), s) != vs.end();
	}

	int sizeSet() {

		return vs.size();


	}
	void printSet() {
		removeDoblecet();
		for (auto i : vs) {
			cout << i << " ";
		}
		cout << endl;
	}
	T* begin() {
		T* newBlock = (T*)malloc((sizeSet()) * sizeof(T));
		for (size_t i = 0; i < sizeSet(); i++)
			new(&newBlock[i])  T(vs[i]);


		Data = move(newBlock);
		newBlock = nullptr;
		return Data;
	}
};



int main() {
	MySet<string>s;
	s.addToSet("hi");
	s.addToSet("hi");
	s.addToSet("mohammed");
	s.addToSet("hielo");
	s.printSet();
	s.removeFromSet("hi");
	s.printSet();
	cout << s.sizeSet();
	cout<<"  \n\n" << s.find("hielo")<<endl;
	cout << "\n\n" << s.find("hi");
	//cout << s.begin();
}