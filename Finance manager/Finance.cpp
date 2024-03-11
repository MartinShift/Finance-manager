#include "Finance.h"
//конструктор
Finance::Finance(const long long& sum, const std::string& category, const std::string& about, const time_t& time, const bool& type)
{
	this->num = sum;
	this->category = category;
	this->about = about;
	this->time = time;
	this->type = type;
}
//призначити дані фінансам
void Finance::setnum(const long long& num)
{
	this->num = num;
}
void Finance::setcategory(const std::string& category)
{
	this->category = category;
}
void Finance::setabout(const std::string& about)
{
	this->about = about;
}
void Finance::settime(const time_t& time)
{
	this->time = time;
}
void Finance::settype(const bool& type)
{
	this->type = type;
}
//повертає дані
long long Finance::getnum()
{
	return num;
}
std::string Finance::getabout()
{
	return about;
}
std::string Finance::getcategory()
{
	return category;
}
time_t Finance::gettime()
{
	return time;
}
std::string Finance::getDtime()
{
	return shift::Datestr(time);
}
bool Finance::gettype()
{
	return type;
}
//виводить весь фінанс
std::ostream& operator<<(std::ostream& out, const Finance& income)
{
	out << income.num << '\n';
	out << income.category << '\n';
	out << income.about << '\n';
	out << income.time << '\n';
	return out;
}
//порівняння по даним
bool Finance::greatertime(Finance fin2)
{
	return this->time > fin2.time;
}
bool Finance::greatermoney(Finance fin2)
{
	return this->num > fin2.num;
}
bool Finance::greatercategory(Finance fin2)
{
	return this->category > fin2.category;
}
bool Finance::greaterabout(Finance fin2)
{
	return this->about > fin2.about;
}
