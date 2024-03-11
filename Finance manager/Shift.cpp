#include "Shift.h"
//tolower string
std::string shift::tolower(const std::string& str)
{
	std::string res;
	for (const auto& i : str)
	{
		res += i >= 65 and i <= 90 ? i + 32 : i;
	}
	return res;
}
//toupper string
std::string shift::toupper(const std::string& str)
{
	std::string res;
	for (const auto& i : str)
	{
		res += i >= 97 and i <= 122 ? i - 32 : i;
	}
	return res;
}
//find numbers in string(no exceptions)
long long shift::findnums(const std::string& mes)
{
	long long num = 0;
	long long count = 0;
	for (long long i{ (long long)mes.size() - 1 }; i >= 0; i--)
	{
		if (mes[i] >= 48 and mes[i] <= 57)
		{
			num += ((size_t)mes[i] - 48) * (size_t)pow(10, count);
			count++;
		}
	}
	return count == 0 ? -1 : num;
}
//random number
int shift::randomize(const int& start, const int& end)
{
	return 1 + start + rand() % end - start;
}
//get subvector
template<typename t>
std::vector<t> shift::subvector(const std::vector<t>& arr, size_t from, size_t to)
{
	std::vector<t> res;
	for (size_t i{ from }; i <= to; i++)
	{
		res.push_back(arr[i]);
	}
	return res;
}
//compare vectors
template<typename t>
std::string shift::veccompare(const std::vector<t>& arr1, const std::vector<t>& arr2)
{
	if (arr1.size() > arr2.size())
	{
		return "bigger";
	}
	else if (arr1.size() < arr2.size())
	{
		return "lower";
	}
	else
	{
		long long sum = 0;
		for (size_t i{}; i < arr1.size(); i++)
		{
			sum += arr1[i] > arr2[i] ? 1 : -1;
		}
		return sum > 0 ? "bigger" : sum == 0 ? "same" : "lower";
	}
}
//get number digit count
int shift::getdigitcount(long long num)
{
	int sum = 0;
	for (; num; num /= 10)sum++;
	return sum;
}
//delete copies in vector
std::vector<std::string> shift::delcopyvec(std::vector<std::string> vec)
{
	std::vector<std::string> copy = vec;
	std::sort(copy.begin(), copy.end());
	for (size_t i = 0; i < copy.size() - 1; i++)
	{
		if (copy[i] == copy[i + 1])
		{
			copy.erase(copy.begin() + i);
			i = 0;
		}
	}
	return copy;
}
//time_t to string
std::string shift::Datestr(time_t clock)
{
	auto dtime = std::chrono::system_clock::from_time_t(clock);
	std::stringstream ss;
	ss << format("{:%d.%m.%Y}", dtime);
	return ss.str();
}
//print unicode charachters
void shift::printUCC(wchar_t mes)
{
	bool setmodetype;
	setmodetype = _setmode(_fileno(stdout), _O_U16TEXT);
	std::wcout << mes;
	setmodetype = _setmode(_fileno(stdout), _O_TEXT);

}
//compare vector
template<typename t>
bool operator <(const std::vector<t>& arr1, const std::vector<t>& arr2)
{
	return shift::veccompare(arr1, arr2) == "lower";
}
template<typename t>
bool operator ==(const std::vector<t>& arr1, const std::vector<t>& arr2)
{
	return shift::veccompare(arr1, arr2) == "same";
}
template<typename t>
bool operator >(const std::vector<t>& arr1, const std::vector<t>& arr2)
{
	return shift::veccompare(arr1, arr2) == "bigger";
}
//print vector
template<typename t>
std::ostream& operator <<(std::ostream& out, const std::vector<t>& arr)
{
	for (const auto& i : arr)
	{
		out << i << ' ';
	}
	out << '\n';
	return out;
}
//get current x position
short wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return csbi.dwCursorPosition.X;
}
//get console y position
short wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return csbi.dwCursorPosition.Y;
}
//get current console position
COORD shift::currentpos()
{
	return { wherex(),wherey() };
}
//Scroll to up console
void shift::ScrollUp(const int& interval)
{
	for (short i{ shift::currentpos().Y }; i >= 0; i--)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { currentpos().X, i });
		Sleep(interval);
	}
}
//Print coord
std::ostream& operator <<(std::ostream& out, const COORD& coord)
{
	out << coord.X << ',' << coord.Y;
	return out;
}