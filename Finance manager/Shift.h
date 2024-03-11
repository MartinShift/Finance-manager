#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <conio.h>
#include <regex>
#include <chrono>
#include <thread>
#include <sstream>
#include <functional>
#include <io.h>
#include <fcntl.h>
namespace fs = std::filesystem;
using namespace std::chrono;
short wherex();
short wherey();
namespace shift
{
	std::string tolower(const std::string& str);
	std::string toupper(const std::string& str);
	long long findnums(const std::string& mes);
	int randomize(const int& start, const int& end);
	template<typename t>
	std::vector<t> subvector(const std::vector<t>& arr, size_t from, size_t to);
	template<typename t>
	std::string veccompare(const std::vector<t>& arr1, const std::vector<t>& arr2);
	int getdigitcount(long long num);
	std::vector<std::string> delcopyvec(std::vector<std::string> vec);
	std::string Datestr(time_t clock);
	void printUCC(wchar_t mes);
	COORD currentpos();
	void ScrollUp(const int & interval);
}
std::ostream& operator << (std::ostream& out, const COORD& coord);
template<typename t>
std::ostream& operator <<(std::ostream& out, const std::vector<t>& arr);
template<typename t>
bool operator >(const std::vector<t>& arr1, const std::vector<t>& arr2);
template<typename t>
bool operator ==(const std::vector<t>& arr1, const std::vector<t>& arr2);
template<typename t>
bool operator <(const std::vector<t>& arr1, const std::vector<t>& arr2);