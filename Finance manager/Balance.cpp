#include "Balance.h"
//конструктор
Balance::Balance() {}
//записує пароль
void Balance::writepass(std::string name, fs::path path)
{
	std::ofstream out(path, std::ios::out);
	out << name << '\n';
	out.close();
}
//вхід
bool Balance::Login()
{
	std::string login;
	std::string password;
	FileCryptor crypter;
	drawnameframe(75, 11, 35, 8, GRAY);
	std::cout << "Enter name: ";
	std::getline(std::cin, login);
	system("cls");
	if (!fs::exists(balpath.string() + login))
	{
		warnmessage("No such login exists!", RED);
		return false;
	}
	if (login == "")
	{
		warnmessage("Username cannot be empty!", RED);
		return false;
	}
	drawnameframe(75, 11, 35, 8, GRAY);
	std::cout << "Enter password: ";
	SetColor(WHITE, WHITE);
	std::getline(std::cin, password);
	SetColor(WHITE, BLACK);
	crypter.decrypt(balpath.string() + login + "/password.txt");
	std::ifstream pass(balpath.string() + login + "/password.txt");
	std::string buffer;
	std::getline(pass, buffer);
	system("cls");
	if (password == buffer)
	{
		this->username = login;
		loadbal();
		warnmessage("Success!", GREEN);
	}
	else warnmessage("Incorrect password!", RED);
	pass.close();
	crypter.crypt(balpath.string() + login + "/password.txt");
	return password == buffer;
}
//реєстрація
bool Balance::Register()
{
	std::string login;
	std::string password[2];
	FileCryptor crypter;
	drawnameframe(75, 11, 35, 8, GRAY);
	std::cout << "Enter name: ";
	std::getline(std::cin, login);
	if (fs::exists(balpath.string() + login))
	{
		warnmessage("This account already exists!", RED);
		return false;
	}
	if (login == "")
	{
		warnmessage("Username cannot be empty!", RED);
		return false;
	}
	system("cls");
	for (int i{}; i < 2; i++)
	{
		drawnameframe(75, 11, 35, 8, GRAY);
		std::cout << (i % 2 == 0 ? "Enter" : "Confirm") << " password: ";
		std::getline(std::cin, password[i]);
		system("cls");
	}
	if (password[0] == password[1])
	{
		username = login;
		fs::create_directory(balpath.string() + login);
		writepass(password[0], balpath.string() + username + "/password.txt");
		crypter.crypt(balpath.string() + username + "/password.txt");
		fs::create_directory(balpath.string() + username + "/Reviews");
		std::ofstream(balpath.string() + username + "/Incomes.txt");
		std::ofstream(balpath.string() + username + "/Spendings.txt");
		warnmessage("Success!", GREEN);
		loadbal();
	}
	else warnmessage("Passwords don't match!", RED);
	system("cls");
	return password[0] == password[1];
}
//меню категорій
std::string Balance::categorymenu()
{
	std::string buffer;
	system("cls");
	std::vector<std::string> copy = categories;
	copy.insert(copy.begin(), "Enter category");
	size_t num = mainmenu(copy, "Select category");
	switch (num)
	{
	case 0:
	{
		system("cls");
		drawnameframe(60, 3, 0, 0, YELLOW_FADE);
		SetCursorPosition(1, 1);
		std::cout << "Enter category: ";
		std::getline(std::cin, buffer);
		for (const auto& i : categories)
		{
			if (shift::tolower(i) == shift::tolower(buffer))
			{
				warnmessage("this category already exists!", RED);
				return "";
			}
		}
		if (buffer.empty())
		{
			warnmessage("category can't be empty!", RED);
			return "";
		}

		categories.push_back(buffer);
		return buffer;
	}

	}
	system("cls");
	return copy[num];
}
//теперішня сума
long long Balance::sum()
{
	long long sum = 0;
	for (auto &i : finances)
	{
		sum += i.getnum() * (i.gettype() ? 1: -1);
	}
	return sum;
}
//добавити фінанс
void Balance::addfinance(const Finance& finance)
{
	finances.push_back(finance);
}
//видалити фінанс
void Balance::delfinance(const size_t& idx)
{
	finances.erase(finances.begin() + idx);
}
//змінити фінанс
void Balance::editfinance(const size_t& idx)
{
	std::string buffer;
	Menu menu({ "Amount: " + std::to_string(finances[idx].getnum()),"Category: " + finances[idx].getcategory(),"About: " + finances[idx].getabout(),"Time: " + finances[idx].getDtime() }, "Select what to edit");
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
			drawnameframe(75, 11, 35, 8, GREEN_FADE);
			std::cout << "Enter new data: ";
			std::getline(std::cin, buffer);
			system("cls");
			switch (menu.getSelectedOption())
			{
			case AMOUNT:
				finances[idx].setnum(shift::findnums(buffer));
				break;
			case CATEGORY:
				finances[idx].setcategory(buffer);
				break;
			case ABOUT:
				finances[idx].setabout(buffer);
				break;
			case TIME:
				auto temptime = fromString(buffer, "%d.%m.%Y");
				finances[idx].settime(chrono::system_clock::to_time_t(temptime));

				break;
			}
			menu.generate({ "Amount: " + std::to_string(finances[idx].getnum()),"Category: " + finances[idx].getcategory(),"About: " + finances[idx].getabout(),"Time: " + finances[idx].getDtime() }, "Select what to edit");
			break;
		}
		case ESC:
		{
			system("cls");
			return;
		}
		}
	}
}
//створити дохід/витрату
void Balance::createfinance(bool type)
{
	long long num;
	std::string category;
	std::string about;
	drawnameframe(60, 3, 0, 0, YELLOW_FADE);
	std::cout << "Enter amount: ";
	std::cin >> num;
	std::cin.ignore(99999, '\n');
	if (num < 0)
	{
		warnmessage("Amount can't be empty!", RED);
		return;
	}
	category = categorymenu();
	if (category == "")
	{
		return;
	}
	drawnameframe(60, 3, 0, 0, YELLOW_FADE);
	std::cout << "Write something about it(optional): ";
	std::getline(std::cin, about);
	auto Stime = EnterTime("Enter time");
	if (Stime == 0)
	{
		return;
	}
	addfinance({ num, category, about, Stime,type });
}
//надіслати комусь гроші
void Balance::transfer()
{
	long long num;
	std::string about;
	drawnameframe(60, 3, 0, 0, YELLOW_FADE);
	std::cout << "Enter amount: ";
	std::cin >> num;
	std::cin.ignore(99999, '\n');
	std::vector<std::string>users;
	for (const auto& i : fs::directory_iterator(balpath))
	{
		users.push_back(i.path().filename().string());
	}
	system("cls");
	std::string to = users[mainmenu(users, "Select receiver")];
	std::ofstream out(balpath.string() + to + "/Incomes.txt", std::ios::app);
	Finance temp(num, "Transfer", username, time(0), true);
	out << temp;
	out.close();
	addfinance({ num, "Transfer", to, time(0), false });
	system("cls");
}
//зберегти рахунок у файл
void Balance::savebal()
{
	std::ofstream Inc(balpath.string() + username + "/Incomes.txt", std::ios::out);
	std::ofstream Dec(balpath.string() + username + "/Spendings.txt", std::ios::out);
	for (int i{}; i < finances.size(); i++)
	{
		finances[i].gettype() ? Inc << finances[i] : Dec << finances[i];
	}
	Inc.close();
	Dec.close();
}
//завантажити рахунок з файла
void Balance::loadbal()
{
	categories.clear();
	finances.clear();
	std::vector<std::string> buffer;
	std::string temp;
	std::ifstream Inc(balpath.string() + username + "/Incomes.txt");
	std::ifstream Dec(balpath.string() + username + "/Spendings.txt");
	for (int i{}; std::getline(Inc, temp); i++)
	{
		buffer.push_back(temp);
		if (i % 4 == 3)
		{
			addfinance({ stol(buffer[0]),buffer[1],buffer[2], stol(buffer[3]),true });
			categories.push_back(buffer[1]);
			buffer.clear();
		}
	}
	for (int i{}; std::getline(Dec, temp); i++)
	{
		buffer.push_back(temp);
		if (buffer[i % 4].empty()) break;
		if (i % 4 == 3)
		{
			addfinance({ stol(buffer[0]),buffer[1],buffer[2], stol(buffer[3]),false });
			categories.push_back(buffer[1]);
			buffer.clear();
		}
	}
	if (!categories.empty())
		categories = shift::delcopyvec(categories);
}
//стартове меню
size_t Balance::start()
{
	while (true)
	{
		
		switch (mainmenu({ "Login","Register","Exit" }, "Welcome!"))
		{
		case LOGIN:
			system("cls");
			if (Login())
			{
				return 0;
			}
			break;

		case REGISTER:
			system("cls");
			if (Register())
			{
				return 0;
			}
			break;
		case EXIT:
		return EXIT;
		}	
	}
}
//запустити рахунок
void Balance::run()
{
	bool exit = false;
	while (true)
	{
		switch (start())
		{
		case EXIT:
			return;
		}
		if (!finances.empty())
			sorter.sort(finances);
		FinanceMenu menu(finances,sum());
		
		while (true)
		{
			menu.drawOptions();
			switch (keymenu())
			{
			case VK_UP: // вверх по меню
			{
				menu.up();
				break;
			}
			case VK_DOWN: // вниз по меню
			{
				menu.down();
				break;
			}
			case VK_RIGHT: // вліво по меню
			{
				menu.right();
				break;
			}
			case VK_LEFT: // вправо по меню
			{
				menu.left();
				break;
			}
			case VK_F1: // створити дохід
			{
				system("cls");
				createfinance(true);
				system("cls");
				menu.generate(finances,sum());
				break;
			}
			case VK_F2: // створити витрату
			{
				system("cls");
				createfinance(false);
				system("cls");
				menu.generate(finances,sum());
				break;
			}
			case VK_F3: // видалити фінанс
			{
				system("cls");
				if (suretable("Delete?"))
					delfinance(menu.getSelectedOption()+menu.getActivePage()*23);
				menu.generate(finances,sum());
				break;
			}
			case VK_F4: // змінити фінанс
			{
				system("cls");
				editfinance(menu.getSelectedOption());
				menu.generate(finances,sum());
				break;
			}
			case VK_F5: // меню сортувань
			{
				system("cls");
				sorter.sortmenu();
				sorter.sort(finances);
				system("cls");
				menu.generate(finances,sum());
				break;
			}
			case VK_F6: // написати звіт
			{
				system("cls");
				reviewmanager.menu(finances, username);
				system("cls");
				break;
			}
			case VK_F7: // надіслати гроші
			{
				system("cls");
				transfer();
				break;
			}
			case VK_TAB: // змінити напрямок сортування
			{
				system("cls");
				sorter.ShiftDir();
				if (!finances.empty())
					sorter.sort(finances);
				menu.generate(finances,sum());
				break;
			}
			case ESC: // вихід
			{
				system("cls");
				savebal();
				exit = true;
				break;
			}
			}
			if (exit) { exit = false; break; }
		}
	}
}
