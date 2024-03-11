#include "Review.h"
//порівнює пари
bool greaterpair(const std::pair<long long, std::string>pair1, const std::pair<long long, std::string>pair2)
{
	return pair1.first > pair2.first;
}
//конструктор
Review::Review() {}
//конструктор
Review::Review(const std::string name, const time_t from, const time_t to)
{
	this->name = name;
	this->from = from;
	this->to = to;
}
//повертає загальний дохід
long long Review::GetTimeIncome(std::vector<Finance>& balance)
{
	long long sum = 0;
	for (auto& i : balance)
	{
		sum += i.getnum() * i.gettype();
	}
	return sum;
}
//повертає загальні витрати
long long Review::GetTimeSpendings(std::vector<Finance>& balance)
{
	long long sum = 0;
	for (auto& i : balance)
	{
		sum += i.getnum() * !i.gettype();
	}
	return sum;
}
//повертає баланс на початку
long long Review::GetStartBal(std::vector<Finance> finance, std::vector<Finance> herefinance)
{
	return GetCurrentBal(finance) - GetTimeIncome(herefinance) + GetTimeSpendings(herefinance);
}
//повертає баланс в кінці
long long Review::GetCurrentBal(std::vector<Finance> finance)
{
	return GetTimeIncome(finance) - GetTimeSpendings(finance);
}
//Сортує категорії і витрати
std::vector<std::pair<long long, std::string>> Review::CategorySorted(std::vector<Finance>& Incomes)
{
	bool found = false;
	std::vector<std::pair<long long, std::string>> CatSort;
	for (size_t i{}; i < Incomes.size(); i++)
	{
		if (!Incomes[i].gettype())
		{
			for (size_t j{}; j < CatSort.size(); j++)
			{
				if (Incomes[i].getcategory() == CatSort[j].second)
				{
					CatSort[j].first += Incomes[i].getnum();
					found = true;
				}
			}
			if (found) { found = false; continue; }
			CatSort.push_back({ Incomes[i].getnum(), Incomes[i].getcategory() });
			
		}
	}
	std::sort(CatSort.begin(), CatSort.end(), &greaterpair);
	return CatSort;
}
//записує звіт в файл
void Review::write(std::vector<Finance>finances, std::string user)
{
	drawnameframe(60, 5, 0, 0, YELLOW_FADE);
	std::cout << "Enter name of review: ";
	std::getline(std::cin, this->name);
	this->from = EnterTime("Enter start time");
	this->to = EnterTime("Enter end time");
	WriteFile(finances, user);
}
//показує звіт
void Review::show(const std::string& user)
{
	system("cls");
	std::vector<std::string> content;
	std::string buffer;
	std::ifstream in(balpath.string() + user + "/Reviews/" + name);
	while (std::getline(in, buffer))
	{
		content.push_back(buffer);
	}
	drawnameframe(80, content.size() + 2, 0, 0, ConsoleColor::GREEN);
	SetCursorPosition(85, 10);
	SetColor(GREEN, BLACK);
	std::cout << "ESC: ";
	SetColor(WHITE, BLACK);
	std::cout << "Leave";
	for (size_t i{}; i < content.size(); i++)
	{
		SetCursorPosition(1, (short)i + 1);
		std::cout << content[i];
	}
	shift::ScrollUp(30);
	while (true)
	{
		switch (keymenu())
		{
		case ESC:
			system("cls");
			return;
		case ENTER:
			system("cls");
			return;
		}
	}
	
}
//меню звітів
void Review::menu(std::vector<Finance>& finances, const std::string& user)
{
	Menu menu({ "New review","Read review","Delete review" }, "Review menu");
	while (true)
	{
		menu.drawOptions();
		switch (keymenu())
		{
		case VK_UP:
		{
			menu.up();
			break;
		}
		case VK_DOWN:
		{
			menu.down();
			break;
		}
		case ENTER:
		{
			system("cls");
			if (menu.getSelectedOption() == 0)
			{
				write(finances, user);
				warnmessage("Success!", GREEN);
				return;
			}
			std::vector<std::string> reviews;
			for (const auto& i : fs::directory_iterator(balpath.string() + user + "/Reviews"))
			{
				reviews.push_back(i.path().filename().string());
			}
			if (reviews.empty())
			{
				warnmessage("You have no reviews", BLUE);
				break;
			}
			this->name = reviews[mainmenu(reviews, "Select review")];
			if (menu.getSelectedOption() == 2)
			{
				fs::remove(balpath.string() + user + "/Reviews/" + name);
			}
			else
			{
				show(user);
			}

			break;
		}
		case ESC:
		{
			system("cls");
			return;
		}
		}
	}
};
//Записати весь звіт в файл
void Review::WriteFile(std::vector<Finance>& Finances, const std::string& user)
{
	std::vector<Finance> HereFins;
	for (auto& i : Finances)
	{
		if (i.gettime() >= from and i.gettime() <= to) { HereFins.push_back(i); }
	}
	std::ofstream res(balpath.string() + user + "/Reviews/" + name + ".txt");
	res << "Start time: " << shift::Datestr(from) << '\n';
	res << "End time: " << shift::Datestr(to) << '\n';
	res << "Total income: " << GetTimeIncome(HereFins) << '\n';
	res << "Total spendings: " << GetTimeSpendings(HereFins) << '\n';
	res << "Balance at start: " << GetStartBal(Finances, HereFins) << '\n';
	res << "Balance at end: " << GetCurrentBal(Finances) << '\n';
	res << "All Categories spent at at descending order:\n";
	for (const auto& i : CategorySorted(HereFins))
	{
		res << i.second << ":" << i.first << '\n';
	}
	res << "\nAll your incomes in this period:";
	for (auto& i : HereFins)
	{
		if (i.gettype())
		{
			res << "\nCategory: " << i.getcategory() << '\n';
			res << "Amount: " << i.getnum() << '\n';
			res << "About: " << i.getabout() << '\n';
			res << "Date: " << shift::Datestr(i.gettime()) << '\n';
		}
	}
	res << "\nAll your spendings in this period:";
	for (auto& i : HereFins)
	{
		if (!i.gettype())
		{
			res << "\nCategory: " << i.getcategory() << '\n';
			res << "Amount: " << i.getnum() << '\n';
			res << "About: " << i.getabout() << '\n';
			res << "Date: " << shift::Datestr(i.gettime()) << '\n';
		}
	}
	res.close();
}