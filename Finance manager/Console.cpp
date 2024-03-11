#include "Console.h"
void SetColor(short text, short background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (background << 4));
}
void ResetColor()
{
	SetColor(WHITE, BLACK);
}
void SetCursorPosition(const COORD& coord) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetCursorPosition(short x, short y) //#include <Windows.h>
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {x,y});
}
WCHAR GetKey()
{
	INPUT_RECORD InputRecord;
	DWORD Writtten;
	HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	while (true)
	{
		ReadConsoleInputA(hStdIn, &InputRecord, 1, &Writtten);
		if (InputRecord.EventType == KEY_EVENT && InputRecord.Event.KeyEvent.bKeyDown) break;
	}
	char ASCII = InputRecord.Event.KeyEvent.uChar.AsciiChar;
	if (ASCII) return ASCII;
	return InputRecord.Event.KeyEvent.wVirtualKeyCode;
}