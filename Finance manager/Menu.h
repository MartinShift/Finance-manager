#pragma once
#include "console.h"
#include "Finance.h"
enum Settings
{
	SetWidth, SetHeight, Exit
};
enum TeacherOptions { CREATETEST, EXIT1 };
enum MainMenuOptions { STUDENT, TEACHER, EXIT };
enum StudentOptions { LOGIN, REGISTER };
const wchar_t keys[]{ L'\x2191',L'\x2193',L'\x2190',L'\x2192' };
const std::string keynums[]{ "Up","Down","Page left","Page right" };
const std::string funcnums[]{ "Create income","Create spending","Delete Finance","Change Finance","Sorting menu","Review menu","Transfer money"};
namespace fs = std::filesystem;
using namespace std;
class Menu {
protected:
	long long activeOption = 0;
	vector<string> options;
	string question;
public:
	Menu();
	Menu(const std::vector<std::string>& options, const std::string question);
	void generate(const std::vector<std::string> options, const std::string question);
	void drawQuestion();
	void drawFrame();
	void drawOptions();
	void down();
	void up();
	size_t getSelectedOption();
	size_t getMaxItemSize();
	size_t getFrameWidth();
	size_t getFrameHeight();
};
class FinanceMenu {
protected:
	long long sum;
	long long activeOption;
	long long activePage;
	std::vector<Finance> finances;
public:
	FinanceMenu(const std::vector<Finance>& finances,const long long&sum);
	void generate(const std::vector<Finance>& options,const long long& sum);
	void drawFrame();
	void drawTypes();
	void drawPageFrame();
	void drawInstructions();
	void drawOptions();
	void drawsum();
	long long getSelectedOption();
	long long getActivePage();
	long long getsum();
	void down();
	void up();
	void right();
	void left();
};
WCHAR keymenu();
void drawnameframe(const size_t width, const size_t height, const size_t startX, const size_t startY, const ConsoleColor color);
void warnmessage(const std::string message, ConsoleColor color);
size_t mainmenu(const std::vector<std::string> mes, const std::string& question);
std::chrono::system_clock::time_point fromString(const std::string& dateStr, const std::string& format);
time_t EnterTime(const std::string& mes);
bool suretable(const std::string& message);
