#include "Sorter.h"
#include "Finance.h"
#include "Menu.h"
void Sorter::sortif(std::vector<Finance>& finances, const std::function<bool(Finance, Finance)>& compare)
{
	Finance temp=finances[0];
	for (size_t i{}; i < finances.size(); i++)
	{
		for (size_t j{}; j < finances.size() - 1; j++)
		{
			if (direction == compare(finances[j], finances[j + 1]))
			{
				temp = finances[j];
				finances[j] = finances[j + 1];
				finances[j + 1] = temp;
			}
		}
	}
}
void Sorter::sort(std::vector<Finance>& finances)
{
	sortif(finances, comparators[sortby]);
}
void Sorter::ShiftDir()
{
	direction = !direction;
}
void Sorter::sortmenu() {
	sortby = (Sortbys)mainmenu({ "Amount","Category","About","Time" }, "Select sorting method");
}
Sorter::Sorter(const bool& dir, const Sortbys& sortby)
{
	this->direction = dir;
	this->sortby = sortby;
}
Sorter::Sorter() { direction = false; sortby = TIME; }