#include "Menu.h"
	//конструктор
	Menu::Menu() {}
	//конструктор
	Menu::Menu(const std::vector<std::string>& options, const std::string question) {
		this->question = question;
		this->options = options;
	}
	//ще 1 конструктор
	void Menu::generate(const std::vector<std::string> options, const std::string question)
	{
		this->options = options;
		this->question = question;
	}
	//пише те шо зверху
	void Menu::drawQuestion()
	{
		size_t width = question.size() + 2 > getFrameWidth() ? question.size() + 2 : getFrameWidth();
		for (short y = 0; y < 3; y++)
		{
			for (short x = 0; x < width; x++)
			{
				if (x == 0 || x == width - 1 || y == 0 || y == 2) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
		SetCursorPosition(1, 1);
		std::cout << question;
	}
	//рамка
	void Menu::drawFrame() {
		size_t width = getFrameWidth() > question.size() ? getFrameWidth() : question.size() + 2;
		size_t height = getFrameHeight() + 2;
		drawQuestion();
		for (short y = 0; y < height; y++)
		{
			for (short x = 0; x < width; x++)
			{
				if (x == 0 || x == width - 1 || y == 2 || y == height - 1) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
	}
	//варіанти і все інше
	void Menu::drawOptions() {
		drawFrame();
		short startX = 3;
		short startY = 4;
		size_t max = getMaxItemSize();
		for (size_t i = 0; i < options.size(); i++)
		{
			SetCursorPosition(startX, startY + (short)i);
			if (activeOption == i) {
				SetColor(RED, WHITE);
			}
			else {
				SetColor(WHITE, BLACK);
			}
			std::string item = options[i];
			item.append(string(max - item.size(), ' '));
			cout << item;
		}
	}
	//вниз
	void Menu::down() {
		activeOption++;
		if (activeOption >= (long long)options.size()) {
			activeOption = 0;
		}
	}
	//вверх
	void Menu::up() {
		activeOption--;
		if (activeOption < 0) {
			activeOption = options.size() - 1;
		}
	}
	//повертає вибраний варіант
	size_t Menu::getSelectedOption() {
		return activeOption;
	}
	//визначає розмір
	size_t Menu::getMaxItemSize()  {
		size_t max = 0;
		for (string item : options)
		{
			if (item.size() > max) {
				max = item.size();
			}
		}
		return max;
	}
	//ширина
	size_t Menu::getFrameWidth()  {
		return getMaxItemSize() + 6;
	}
	//висота
	size_t Menu::getFrameHeight()  {
		return options.size() + 4;
	}


	//конструктор
	FinanceMenu::FinanceMenu(const std::vector<Finance>& finances, const long long& sum) {
		this->finances = finances;
		this->sum = sum;
	}
	//конструктор
	void FinanceMenu::generate(const std::vector<Finance>& options,const long long& sum)
	{
		this->finances = options;
		this->sum = sum;
	}
	//рамка
	void FinanceMenu::drawFrame() {
		size_t width = 87;
		size_t height = 29;
		for (short y = 3; y < height; y++)
		{
			for (short x = 25; x < width; x++)
			{
				if (x == 25 || x == width - 1 || y == 0 || y == height - 1) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE_FADE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
	}
	//4 категорії
	void FinanceMenu::drawTypes()
	{
		size_t width = 87;
		size_t height = 5;
		for (short y = 2; y < height; y++)
		{
			for (short x = 25; x < width; x++)
			{
				SetColor(WHITE, BLACK);
				if (x == 25 or x == width - 1 or y == 1 or y == height - 1 or x == 36 or x == 51 or x == 73) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE_FADE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
		SetCursorPosition(28, 3);
		std::cout << "Amount";
		SetCursorPosition(40, 3);
		std::cout << "Category";
		SetCursorPosition(60, 3);
		std::cout << "About";
		SetCursorPosition(78, 3);
		std::cout << "Time";
	}
	//теперішня сторінка
	void FinanceMenu::drawPageFrame()
	{
		size_t width = 87;
		size_t height = 31;
		for (short y = 28; y < height; y++)
		{
			for (short x = 25; x < width; x++)
			{
				SetColor(WHITE, BLACK);
				if (x == 25 or x == width - 1 or y == 26 or y == height - 1) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE_FADE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
		SetCursorPosition(38,29);
		std::cout << "<<";
		SetCursorPosition(71, 29);
		std::cout << ">>";
		SetCursorPosition(47, 29);
		std::cout << "Current page: " << activePage + 1 << '/' << finances.size() / 22 + 1;
	}
	//кнопки навігації
	void FinanceMenu::drawInstructions()
	{
		SetCursorPosition(5, 2);
		std::cout << "Main menu options";
		for (int i{}; i < 4; i++)
		{
			SetColor(GREEN, BLACK);
			SetCursorPosition(5, 4 + i * 2);
			shift::printUCC(keys[i]);
			SetColor(WHITE, BLACK);
			std::cout << "  ";
			std::cout << keynums[i];
		}
		SetColor(GREEN, BLACK);
		SetCursorPosition(5, 12);
		std::cout << "TAB ";
		SetColor(WHITE, BLACK);
		std::cout << " Switch sort";
		SetColor(GREEN, BLACK);
		SetCursorPosition(5, 14);
		std::cout << "ESC ";
		SetColor(WHITE, BLACK);
		std::cout << " Return";
		SetCursorPosition(95, 2);
		std::cout << "Functional options";
		for (int i{}; i < 7; i++)
		{
			SetCursorPosition(95, 4 + i * 2);
			SetColor(GREEN, BLACK);
			std::cout << "F" << i + 1 << "  ";
			SetColor(WHITE, BLACK);
			std::cout << funcnums[i];

		}
	}
	//варіанти і все інше
	void FinanceMenu::drawOptions() {
		drawFrame();
		drawTypes();
		drawInstructions();
		drawsum();
		short startX = 26;
		short startY = 5;
		for (size_t i = 23 * activePage; i < (finances.size() - activePage * 23 > 23 ? 23 + activePage * 23 : activePage * 23 + finances.size() % 23); i++)
		{
			SetCursorPosition(startX + 1, startY + (short)i % 23);
			if (activeOption == i % 23) {
				SetColor(BLACK, WHITE);
			}
			else {
				SetColor(RED - 2 * finances[i].gettype(), BLACK);
			}
			SetCursorPosition(31 - shift::getdigitcount(finances[i].getnum()) / 2, startY + (short)i % 23);
			cout << finances[i].getnum();
			SetCursorPosition(44 - (short)finances[i].getcategory().size() / 2, startY + (short)i % 23);
			if (finances[i].getcategory().size() > 13)
			{
				SetCursorPosition(38, startY + (short)i % 23);
				std::cout << finances[i].getcategory().substr(0, 10) << "...";
			}
			else cout << finances[i].getcategory();
			SetCursorPosition(62 - (short)finances[i].getabout().size() / 2, startY + (short)i % 23);
			if (finances[i].getabout().size() > 21)
			{
				SetCursorPosition(52, startY + (short)i % 23);
				cout << finances[i].getabout().substr(0, 18) << "...";
			}
			else cout << finances[i].getabout();
			SetCursorPosition(75, startY + (short)i % 23);
			cout << finances[i].getDtime();
		}
		drawPageFrame();
	}
	//малює суму
	void FinanceMenu::drawsum()
	{
		for (short y = 0; y < 3; y++)
		{
			for (short x = 25; x < 87; x++)
			{
				SetColor(WHITE, BLACK);
				if (x == 25 or x == 86 or y == 0 or y == 2) {
					SetCursorPosition(x, y);
					SetColor(ConsoleColor::WHITE, BLUE_FADE);
					cout << ' ';
				}
			}
		}
		SetColor(WHITE, BLACK);
		SetCursorPosition(44-(shift::getdigitcount(sum))/2,1);
		std::cout << "Your current balance: ";
		SetColor(sum >= 0 ? GREEN : RED, BLACK);
		std::cout << sum;
		SetColor(WHITE, BLACK);
	}
	//повертає вибраний варіант
	long long FinanceMenu::getSelectedOption()
	{
		return activeOption;
	}
	//вниз
	void FinanceMenu::down() {
		activeOption++;
		if (activeOption >= (finances.size() - activePage * 23 > 23 ? 23 : (long long)finances.size() % 23)) {
			right();
			activeOption = 0;
		}
	}
	//вверх
	void FinanceMenu::up() {
		activeOption--;
		if (activeOption < 0) {
			left();
			activeOption = (finances.size() - activePage * 23 > 23 ? 22 : finances.size() % 23 - 1);
		}
	}
	//вправо
	void FinanceMenu::right() {
		system("cls");
		activePage++;
		if (activePage > (long long)finances.size() / 23) {
			activePage = 0;
		}
	}
	//вліво
	void FinanceMenu::left() {
		system("cls");
		activePage--;
		if (activePage < 0) {
			activePage = finances.size() / 23;
		}
	}
	//повертає активну сторінку
	long long FinanceMenu::getActivePage()
	{
		return activePage;
	}
	//сума
	long long FinanceMenu::getsum()
	{
		return this->sum;
	}
	
//повертає нажату клавішу
WCHAR keymenu()
{
	WCHAR key;
	while (true)
	{
		SetColor(WHITE, BLACK);
		key = GetKey();
		if (key == -1) {
			Sleep(10);
			continue;
		}
		else return key;
	}
}
//малює квадрат
void drawnameframe(const size_t width, const size_t height, const size_t startX, const size_t startY, const ConsoleColor color)
{
	for (size_t y = startY; y < height; y++)
	{
		for (size_t x = startX; x < width; x++)
		{
			if (x == startX or x == width - 1 or y == startY or y == height - 1) {
				SetCursorPosition((short)x, (short)y);
				SetColor(ConsoleColor::WHITE, color);
				std::cout << ' ';
			}
		}
	}
	SetCursorPosition((short)startX + 1, (short)startY + 1);
	SetColor(WHITE, BLACK);
}
//квадрат з текстом посередині
void warnmessage(const std::string message, ConsoleColor color)
{
	system("cls");
	std::string mes = message + " Press Enter:";
	drawnameframe(75, 12, 35, 8, color);
	SetCursorPosition(55 - (short)message.size() / 2, 10);
	SetColor(color, BLACK);
	std::cout << message;
	WCHAR key = -1;
	while (true)
	{
		key = GetKey();
		if (key == ENTER or key == ESC) {
			SetColor(WHITE, BLACK);
			system("cls");
			return;
		}
	}
}
//меню в 1 функції
size_t mainmenu(const std::vector<std::string> mes, const std::string& question)
{
	Menu menu(mes, question);
	menu.drawOptions();
	while (true)
	{
		switch (keymenu())
		{
		case VK_UP:
		{
			menu.up();
			menu.drawOptions();
			break;
		}
		case VK_DOWN:
		{
			menu.down();
			menu.drawOptions();
			break;
		}
		case ENTER:
		{
			return menu.getSelectedOption();
		}
		}
	}
}
//перетворює строку в час
std::chrono::system_clock::time_point fromString(const std::string& dateStr, const std::string& format) {
	std::stringstream ss{ dateStr };
	std::chrono::system_clock::time_point tp;
	ss >> std::chrono::parse(format, tp);
	if (ss.fail()) {
		warnmessage("Wrong data!", RED);
	}
	return tp;
}
//ввести час
time_t EnterTime(const std::string& mes)
{
	system("cls");
	std::string tim;
	switch (mainmenu({ "Enter time","Current time" }, mes))
	{
	case 0:
		system("cls");
		drawnameframe(75, 11, 35, 8, GRAY);
		SetCursorPosition(36, 9);
		std::cout << "Enter time(in DD.MM.YYYY): ";
		std::getline(std::cin, tim);
		system("cls");
		return std::chrono::system_clock::to_time_t(fromString(tim, "%d.%m.%Y"));
	}
	return time(0);
}
//підтвердження
bool suretable(const std::string& message) {
	WCHAR key;
	bool sure = false;
	const size_t width = 76;
	const size_t height = 12;
	const short startX = 35;
	const short startY = 7;
	drawnameframe(width, height, startX, startY,ConsoleColor::TEAL_FADE);
	SetColor(WHITE, BLACK);
	SetCursorPosition((55 - (short)message.size() / 2), startY + 1);
	std::cout << message;
	SetCursorPosition((width + startX) / 2 - 5, height - 2);
	SetColor(RED, BLACK);
	std::cout << "No";
	SetColor(GREEN, BLACK);
	SetCursorPosition((width + startX) / 2 + 3, height - 2);
	std::cout << "Yes";
	while (true)
	{
		key = GetKey();
		if (key == -1) {
			Sleep(10);
			continue;
		}
		switch (key)
		{
		case VK_LEFT:
			SetCursorPosition((width + startX) / 2 + 3, height - 2);
			SetColor(GREEN, BLACK);
			std::cout << "Yes";
			SetCursorPosition((width + startX) / 2 - 5, height - 2);
			SetColor(BLACK, RED);
			std::cout << "No";
			sure = false;
			break;
		case VK_RIGHT:
			SetCursorPosition((width + startX) / 2 - 5, height - 2);
			SetColor(RED, BLACK);
			std::cout << "No";
			SetCursorPosition((width + startX) / 2 + 3, height - 2);
			SetColor(BLACK, GREEN);
			std::cout << "Yes";
			sure = true;
			break;
		case ENTER:
			SetColor(WHITE, BLACK);
			system("cls");
			return sure;
		}
	}
}
