#pragma once
#include "Finance.h"
#include "Menu.h"
enum Sortbys {
	AMOUNT, CATEGORY, ABOUT, TIME
};
const std::function<bool(Finance, Finance)> comparators[]{ &Finance::greatermoney,&Finance::greatercategory,&Finance::greaterabout,&Finance::greatertime };
class Sorter
{
private:
	bool direction;
	Sortbys sortby;
public:
	Sorter();
	Sorter(const bool& dir, const Sortbys& sortby);
	void sortif(std::vector<Finance>& finances, const std::function<bool(Finance, Finance)>& compare);
	void sort(std::vector<Finance>& finances);
	void ShiftDir();
	void sortmenu();
};