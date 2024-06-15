#ifndef CONSOLEFUNCTION_H
#define CONSOLEFUNCTION_H

#include "ConsoleFunctions.h"
#include <string.h>
ConsoleFunctions::ConsoleFunctions()
{
	//mode = 0;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &original_mode);
	SetConsoleMode(hOut, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);// | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS ); //| ENABLE_QUICK_EDIT_MODE
	SetConsoleMode(hIn, ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);// | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT);
	GetConsoleScreenBufferInfo(hOut, &csbi);
	original_attributes = csbi.wAttributes;
}

void ConsoleFunctions::setConsoleTitle(const char* title)
{
	int len = strlen(title);
	wchar_t* str = new wchar_t[len + 1];

	for (int i = 0; i < len; i++)
		str[i] = title[i];
	str[len] = '\0';

	SetConsoleTitle(LPCWSTR(str));
	//SetConsoleTitle(TEXT("some title"));
}

void ConsoleFunctions::SetCursorAt(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hOut, coord);
}

char ConsoleFunctions::ReadFrom(int x, int y)
{
	//char* str = new char[10];  //Buffer of 10 char size
	char str[10];
	DWORD nLength = 1;     //The number of chars to read, we need to read one character only!
	COORD readFromCoord;   //Co-ordinates from where to read
	readFromCoord.X = x;
	readFromCoord.Y = y;
	DWORD num_read = 0;      //Will be set to no. of charaters actually read

	ReadConsoleOutputCharacter(hOut, (LPTSTR)str, nLength, readFromCoord, (LPDWORD)&num_read);

	return str[0];
}

void ConsoleFunctions::DetectEvent()
{
	DWORD count = 0;
	GetNumberOfConsoleInputEvents(hIn, &count);
	if (count > 0)
	{
		DWORD nLength = 1;     //The number of records to read, we need to read one record only!
		DWORD num_read = 0;      //Will be set to no. of input records actually read
		ReadConsoleInput(hIn, &InRec, nLength, &num_read);
		FlushConsoleInputBuffer(hIn);
		//cout << "Num Read " << (int)num_read << " now";
	}
}

bool ConsoleFunctions::getMousePosition(point& p)
{
	//cout << InRec.EventType;
	//if(InRec.EventType == MOUSE_EVENT)
	//	cout<<InRec.Event.MouseEvent.dwEventFlags;

	if (InRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
	{
		p.x = InRec.Event.MouseEvent.dwMousePosition.X;
		p.y = InRec.Event.MouseEvent.dwMousePosition.Y;

		return true;
	}
	return false;

}

bool ConsoleFunctions::IsMouseLeftClickEvent(point& p)
{
	if (InRec.EventType == MOUSE_EVENT && InRec.Event.MouseEvent.dwEventFlags == 0 && InRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
	{
		p.x = InRec.Event.MouseEvent.dwMousePosition.X;
		p.y = InRec.Event.MouseEvent.dwMousePosition.Y;
		InRec.Event.MouseEvent.dwButtonState = 0;

		return true;
	}
	return false;
}

bool ConsoleFunctions::IsMouseRightClickEvent(point& p)
{
	if (InRec.EventType == MOUSE_EVENT && InRec.Event.MouseEvent.dwEventFlags == 0 && InRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
	{
		p.x = InRec.Event.MouseEvent.dwMousePosition.X;
		p.y = InRec.Event.MouseEvent.dwMousePosition.Y;
		InRec.Event.MouseEvent.dwButtonState = 0;
		return true;
	}
	return false;
}

bool ConsoleFunctions::IsKeyPressEvent(char& key)
{
	if (InRec.EventType == KEY_EVENT && InRec.Event.KeyEvent.bKeyDown)
	{
		//cout << (int)InRec.Event.KeyEvent.wRepeatCount;
		key = InRec.Event.KeyEvent.uChar.AsciiChar;
		InRec.EventType = 0;
		return true;
	}
	return false;
}



bool ConsoleFunctions::IsKeyReleaseEvent(char& key)
{
	if (InRec.EventType == KEY_EVENT && !InRec.Event.KeyEvent.bKeyDown)
	{

		key = InRec.Event.KeyEvent.uChar.AsciiChar;
		return true;
	}
	return false;
}

int ConsoleFunctions::getTextColor()
{
	GetConsoleScreenBufferInfo(hOut, &csbi);
	int a = csbi.wAttributes;
	return a % 16;
}

int ConsoleFunctions::getBackColor()
{
	GetConsoleScreenBufferInfo(hOut, &csbi);
	int a = csbi.wAttributes;
	return (a / 16) % 16;
}

void ConsoleFunctions::SetColor(ConsoleColor textcol, ConsoleColor backcol)
{
	SetColor(int(textcol), int(backcol));
}

void ConsoleFunctions::SetColor(int textcol, int backcol)
{
	bool textcolorprotect = true; //for future use
	/*doesn't let textcolor be the same as backgroung color if true*/
	if (textcolorprotect)
	{
		if ((textcol % 16) == (backcol % 16))textcol++;
	}
	textcol %= 16;
	backcol %= 16;
	unsigned short wAttributes = (unsigned)textcol | ((unsigned)backcol << 4);
	SetConsoleTextAttribute(hOut, wAttributes);

}

void ConsoleFunctions::getConsoleWindowSize(int& rows, int& columns)
{
	//CHECK
	GetConsoleScreenBufferInfo(hOut, &csbi);
	//columns = csbi.dwMaximumWindowSize.X;
	//columns = csbi.dwSize.X-1;
	//rows = csbi.dwSize.Y-1;
	columns = csbi.srWindow.Right;
	rows = csbi.srWindow.Bottom;
	//columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	//rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

}

void ConsoleFunctions::setConsoleWindowAndBufferSize(int rows, int columns)
{
	COORD new_size;
	new_size.Y = rows + 1;
	new_size.X = columns + 1;
	//SetConsoleActiveScreenBuffer(hOut);
	//SetConsoleScreenBufferSize(hOut, new_size);

	SMALL_RECT rect;  rect.Left = 0; rect.Top = 0; rect.Right = columns; rect.Bottom = rows;
	//SetConsoleScreenBufferSize(hOut, new_size);

	SetConsoleWindowInfo(hOut, true, &rect);
	SetConsoleScreenBufferSize(hOut, new_size);

}

void cls(HANDLE hConsole, WORD original_attributes)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes =
		fill.Attributes = original_attributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
void ConsoleFunctions::clearConsole()
{
	SetConsoleMode(hOut, original_mode);
	SetConsoleTextAttribute(hOut, original_attributes);
	cls(hOut, original_attributes);

}


void ConsoleFunctions::writeStringOnConsole(char* str)
{
	DWORD Written;
	int len = strlen(str);
	wchar_t* mystr = new wchar_t[len + 1];

	for (int i = 0; i < len; i++)
		mystr[i] = str[i];
	mystr[len] = '\0';
	WriteConsole(hOut, mystr, len, &Written, NULL);
}

void ConsoleFunctions::writeCharOnConsole(char c)
{
	DWORD Written;
	//int len = strlen(str);
	wchar_t* mystr = new wchar_t[1];
	mystr[0] = c;
	//mystr[len] = '\0';
	WriteConsole(hOut, mystr, 1, &Written, NULL);

}

ConsoleFunctions::~ConsoleFunctions()
{
	SetConsoleMode(hOut, original_mode);
	SetConsoleTextAttribute(hOut, original_attributes);
}




#endif