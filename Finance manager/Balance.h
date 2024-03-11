#pragma once
#include "Finance.h"
#include "FileCryptor.h"
#include "Sorter.h"
#include "Review.h"
class Balance
{
private:
	std::vector<Finance>finances;
	std::vector<std::string>categories;
	Review reviewmanager;
	Sorter sorter;
	std::string username;
public:
	Balance();
	long long sum();
	void writepass(std::string name, fs::path path);
	bool Login();
	bool Register();
	std::string categorymenu();
	void addfinance(const Finance& finance);
	void delfinance(const size_t& idx);
	void editfinance(const size_t& idx);
	void createfinance(bool type);
	void transfer();
	void savebal();
	void loadbal();
	size_t start();
	void run();
};