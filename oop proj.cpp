#include <iostream>
using namespace std;
#include "ConsoleFunctions.h"

#include <string>
#include <io.h>
#include <fcntl.h>
#include <windows.h>



class PlayingCard
{
private:
	int rank;
	int suit;
	char color;

public:
	static const int Diamond = 0;
	static const int Heart = 1;
	static const int Spade = 2;
	static const int Club = 3;

	PlayingCard(int rank = 0, int suit = 0)
	{
		if (rank >= 0 && rank <= 14)
		{
			if (suit >= 0 && suit <= 3)
			{
				this->rank = rank;
				this->suit = suit;
				if (suit >= 0 && suit <= 1)
					color = 'r';
				else
					color = 'b';
			}
			else
				cout << "Suit is invalid" << endl;
		}
		else
			cout << "Rank is invalid" << endl;
	}

	void display(int x, int y)
	{
		ConsoleFunctions dis;

		string num;
		if (rank == 1)
			num = "A";
		else if (rank == 11)
			num = "J";
		else if (rank == 12)
			num = "Q";
		else if (rank == 13)
			num = "K";
		else
			num = to_string(rank);

		wstring Symbol;
		if (suit == 0)
		{
			Symbol = L"\u2666";

		}

		else if (suit == 1)
		{
			Symbol = L"\u2665";

		}

		else if (suit == 2)
		{
			Symbol = L"\u2660";

		}

		else if (suit == 3)
		{
			Symbol = L"\u2663";

		}


		if (color == 'r')
			dis.SetColor(12, 15);
		else if (color == 'b')
			dis.SetColor(0, 15);


		dis.SetCursorAt(x, y);
		cout << num; _setmode(_fileno(stdout), _O_U16TEXT);
		wcout << Symbol; _setmode(_fileno(stdout), _O_TEXT); cout << "    ";



		y++;
		for (int i = y; i < y + 6; i++)
		{
			dis.SetCursorAt(x, i);
			cout << "      ";
		}
		dis.SetCursorAt(x, (y + 6));
		cout << "    "; _setmode(_fileno(stdout), _O_U16TEXT);
		wcout << Symbol; _setmode(_fileno(stdout), _O_TEXT); cout << num;

	}

};

class PileofCards {
private:
	PlayingCard* pile;
	int top;
	int size;
public:
	PileofCards(int size)
	{
		this->size = size;
		pile = new PlayingCard[size];
		top = -1;
	}
	~PileofCards()
	{
		delete[]pile;
		pile = NULL;
	}
	PlayingCard Peek()
	{
		return pile[top];
	}
	PlayingCard Remove() 
	{
		return pile[top];
		top--;
	

	}
	void Add(PlayingCard pc)
	{
		pile[top + 1] = pc;
		top++;
		
	}
	bool IsEmpty()
	{
		if (top == -1)
		{
			cout << "Pile is empty" << endl;
			return true;
		}
		else
		{
			return false;
		}

	}

	bool IsFull()
	{
		if (top == size - 1)  // as top can never equal size
		{
			cout << "Pile is full" << endl;
			return true;

		}
		else
			return false;

	}
};
class Deck
{
private:
	PlayingCard * deck[52];
	int size;
public:
	Deck()
	{
		int j = 0;
		size = 52;
		for (int i = 1; i <= 13; i++)
		{
			deck[j] = new PlayingCard(i, PlayingCard::Spade);
			j++;
		}

		for (int i = 1; i <= 13; i++)
		{
			deck[j] = new PlayingCard(i, PlayingCard::Diamond);
			j++;
		}
		for (int i = 1; i <= 13; i++)
		{
			deck[j] = new PlayingCard(i, PlayingCard::Heart);
			j++;
		}
		for (int i = 1; i <= 13; i++)
		{
			deck[j] = new PlayingCard(i, PlayingCard::Club);
			j++;
		}

	}
	int getSize()
	{
		return size;
	}
	bool IsEmpty()
	{
		
		if (size == 0)
			return true;
		return false;
	}
	PlayingCard Remove(int i)
	{
		PlayingCard *temp = deck[i];
		for (int j = i; j < size - 1; j++)
		{
			deck[j] = deck[j + 1];
		}
		size--;
		
		return *temp;
	}
	~Deck()
	{
		for (int i = 0; i < 52; i++)
		{
			delete deck[i];
		}
	}
};

int main()
{
	PlayingCard A(1, PlayingCard::Spade);
	PlayingCard B(2, PlayingCard::Spade);
	PlayingCard C(4, PlayingCard::Heart);
	PlayingCard D(5, PlayingCard::Club);
	PlayingCard E(3, PlayingCard::Diamond);
	PlayingCard temp(3, PlayingCard::Club);
	PileofCards pile1(5);
	/****** Adding cards in pile ********/
	pile1.Add(A);
	pile1.Add(B);
	pile1.Add(C);
	pile1.Add(D);
	pile1.Add(E);
	/*Note for Testing:
	The 6th card temp, in the statement below, should not be added to the
	pile, as at this point pile is full.
	Write a statement in IsFull function to display an error message if pile is
	full.
	*/
	if (!pile1.IsFull())
	{
		pile1.Add(temp);
	}
	/****** Removing Cards from pile *****/
	if (!pile1.IsEmpty())
	{
		temp = pile1.Remove();
	}
	/* Here you will need to see which card is removed from the pile.
	For this you need to write display function for class PlayingCard to
	view a card. */
	//temp.display(0, 0);

	/* According to this scenario, the above statement should display the card
	3 of Diamond, as this is the card removed from the top of the pile*/
	temp = pile1.Remove(); //5 of Club should be removed
	//temp.display(0, 10);
	temp = pile1.Remove(); //4 of Heart should be removed
	//temp.display(0, 20);
	temp = pile1.Remove(); //2 of Spade should be removed
	//temp.display(0, 30);
	temp = pile1.Remove(); //3 of Spade should be removed
	//temp.display(0, 40);
	temp = pile1.Remove(); //Now the pile is empty
	/*Write a print statement in IsEmpty funtion to display an error message when
	pile is empty*/
	A.display(0, 10);
	C.display(0, 20);
	D.display(0, 30);
	E.display(0, 40);
	//Deck D1;
	//PlayingCard A(0, 0);
	//int y = 0;
	//A = D1.Remove(0);
	//A.display(0, y);
	//y = y + 10;

	//A = D1.Remove(0);
	//A.display(0, 10);
	//y = y + 10;
	//A = D1.Remove(0);
	//A.display(0, 20); // three cards removed
	//y = y + 10;
	//while (!D1.IsEmpty())
	//{
	//	A = D1.Remove(0);
	//	A.display(0, y);
	//	y = y + 10;
	//}
	system("pause");
	return 0;
}

