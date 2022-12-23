#include <iostream>
#include <string>
#include <stdexcept>
#include <regex>
using namespace std;

class MonthError : public std::exception
{
private:
	std::string error_message;
public:
	MonthError(std::string message)
		: exception(message.c_str()), error_message(message)
	{}

	virtual const char* what() const throw()
	{
		return error_message.c_str();
	}
};

class DayError : public std::exception
{
private:
	std::string error_message;
public:
	DayError(std::string message)
		: exception(message.c_str()), error_message(message)
	{}
	virtual const char* what() const throw()
	{
		return error_message.c_str();
	}
};

void thirty(string s, string temp) {
	if (s.size() == 1 && isdigit(s[0])) {
		temp += " " + s;
	}
	else if (s.size() == 2 && isdigit(s[0]) && isdigit(s[1])) {
		if (s[0] == '3') {
			if (s[1] == '0') {
				temp += " " + s;
			}
			else
				throw DayError("Day Error");
		}
		else if (s[0] < '3') {
			temp += " " + s;
		}
		else
			throw DayError("Day Error");
	}
	else {
		throw DayError("Day Error");
	}
	cout << temp;
}
void thirtyOne(string s, string temp) {
	if (s.size() == 1 && isdigit(s[0])) {
		temp += " " + s;
	}
	else if (s.size() == 2 && isdigit(s[0]) && isdigit(s[1])) {
		if (s[0] == '3') {
			if (s[1] <= '1') {
				temp += " " + s;
			}
			else
				throw DayError("Day Error");
		}
		else if (s[0] < '3') {
			temp += " " + s;
		}
		else
			throw DayError("Day Error");
	}
	else {
		throw DayError("Day Error");
	}
	cout << temp;
}
void February(string s, string temp) {
	if (s.size() == 1 && isdigit(s[0])) {
		temp += " " + s;
	}
	else if (s.size() == 2 && isdigit(s[0]) && isdigit(s[1])) {
		if (s[0] == '2')
			temp += " " + s;

		else if (s[0] < '2') {
			temp += " " + s;
		}
		else
			throw DayError("Day Error");
	}
	else {
		throw DayError("Day Error");
	}
	cout << temp;
}


void convertDate(string s) {
	string temp;
	if (s[0] == '0') {
		s.erase(0, 1);
	}
	//31
	if (s[0] == '1' && s[1] == '0' && s[2] == '/') {
		temp = "October";
		s.erase(0, 3);
		thirtyOne(s, temp);
	}
	//30
	else if (s[0] == '1' && s[1] == '1' && s[2] == '/') {
		temp = "November";
		s.erase(0, 3);
		thirtyOne(s, temp);
	}
	//31
	else if (s[0] == '1' && s[1] == '2' && s[2] == '/') {
		temp = "December";
		s.erase(0, 3);
		thirtyOne(s, temp);
	}
	//31
	else if (s[0] == '1' && s[1] == '/') {
		temp = "January";
		s.erase(0, 2);
		thirtyOne(s, temp);
	}
	//29
	else if (s[0] == '2' && s[1] == '/') {
		temp = "February";
		s.erase(0, 2);
		February(s, temp);
	}
	//31
	else if (s[0] == '3' && s[1] == '/') {
		s.erase(0, 2);
		temp = "March";
		thirtyOne(s, temp);
	}
	//30
	else if (s[0] == '4' && s[1] == '/') {
		s.erase(0, 2);
		temp = "April";
		thirtyOne(s, temp);
	}
	//31
	else if (s[0] == '5' && s[1] == '/') {
		s.erase(0, 2);
		temp = "May";
		thirtyOne(s, temp);
	}
	//30
	else if (s[0] == '6' && s[1] == '/') {
		s.erase(0, 2);
		temp = "June";
		thirtyOne(s, temp);
	}
	//31
	else if (s[0] == '7' && s[1] == '/') {
		s.erase(0, 2);
		temp = "July";
		thirtyOne(s, temp);
	}
	//31
	else if (s[0] == '8' && s[1] == '/') {
		s.erase(0, 2);
		temp = "August";
		thirtyOne(s, temp);
	}
	//30
	else if (s[0] == '9' && s[1] == '/') {
		s.erase(0, 2);
		temp = "September";
		thirtyOne(s, temp);
	}
	else {
		throw MonthError("not valid month");
	}
}



int main()
{
	string s; cout << "Enter month/day converts dates from numerical month/day format to alphabetic : "; cin >> s;
	try
	{
		convertDate(s);
	}
	catch (MonthError& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (DayError& e)
	{
		std::cout << e.what() << std::endl;
	}
}