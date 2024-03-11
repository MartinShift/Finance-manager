#pragma once
#include "Menu.h"
bool greaterpair(const std::pair<long long, std::string>pair1, const std::pair<long long, std::string>pair2);
class Review
{
private:
	std::string name;
	time_t from;
	time_t to;
public:
	Review();
	Review(const std::string name, const time_t from, const time_t to);
	long long GetTimeIncome(std::vector<Finance>& balance);
	long long GetTimeSpendings(std::vector<Finance>& balance);
	long long GetStartBal(std::vector<Finance> finance, std::vector<Finance> herefinance);
	long long GetCurrentBal(std::vector<Finance> finance);
	std::vector<std::pair<long long, std::string>> CategorySorted(std::vector<Finance>& Incomes);
	void write(std::vector<Finance>finances, std::string user);
	void show(const std::string& user);
	void menu(std::vector<Finance>& finances, const std::string& user);
	void WriteFile(std::vector<Finance>& Finances, const std::string& user);
};