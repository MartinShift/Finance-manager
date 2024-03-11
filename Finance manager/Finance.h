#pragma once
#pragma warning(disable : 4996)
#include "Shift.h"

const fs::path balpath = fs::current_path().string() + '\\';
class Finance {
protected:
	long long num;
	std::string category;
	std::string about;
	time_t time; 
	bool type;
public:
	Finance(const long long& sum, const std::string& category, const std::string& about, const time_t& time, const bool& type);
	void setnum(const long long& num);
	void setcategory(const std::string& category);
	void setabout(const std::string& about);
	void settime(const time_t& time);
	void settype(const bool& type);
	long long getnum();
	std::string getabout();
	std::string getcategory();
	time_t gettime();
	std::string getDtime();
	bool gettype();
	friend std::ostream& operator<<(std::ostream& out, const Finance& income);
	bool greatertime(Finance fin2);
	bool greatermoney(Finance fin2);
	bool greatercategory(Finance fin2);
	bool greaterabout(Finance fin2);
};