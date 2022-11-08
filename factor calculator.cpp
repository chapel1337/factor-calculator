#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::cin; using std::string; using std::vector; using std::ws; using std::getline; using std::to_string;

// written by chapel1337
// made on 11/7/2022
// not much to say about this

bool linux{ false };

#ifdef __linux__
	linux = true;
#elif _WIN32
	#include <conio.h>
	#include <windows.h>

	void sleep(int time)
	{
		Sleep(time * 1000);
	}
#endif

// ------- \\

void goTo(string function);

void clear()
{
	if (linux)
	{
		system("clear");
	}
	else
	{
		system("cls");
	}
}

void title(string title)
{
	if (linux) return;

	SetConsoleTitleA(("factor calcator - " + title).c_str());
}

void title()
{
	if (linux) return;

	SetConsoleTitleA("factor calculator");
}

void title(string title, int i)
{
	if (linux) return;

	SetConsoleTitleA(("factor calculator - " + title + to_string(i)).c_str());
}

void setTextColor(int color)
{
	if (linux) return;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
	if (linux) return;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void invalidInput(string message, string function)
{
	clear();

	cout << "invalid input: " << message << '\n';

	sleep(2);
	goTo(function);
}

// ------- \\

vector<int> findFactors(int number, bool displayFactors)
{
	clear();

	vector<int> numberFactors{};
	vector<int> numbers{};

	for (int i{ 1 }; i <= 100; ++i)
	{
		if (number / i * i == number)
		{
			numberFactors.push_back(i);
			numbers.push_back(number / i);
		}
	}

	if (displayFactors)
	{
		cout << "factors of " << number << ": ";

		if (numberFactors.size() == 2)
		{
			cout << "none \n\n";
		}
		else
		{
			for (int i{ 0 }; i < numberFactors.size(); ++i)
			{
				setTextColor(6);
				if (i == numberFactors.size() - 1)
				{
					cout << i;
				}
				else
				{
					cout << i << ", ";
				}
				resetTextColor();
			}

			cout << "\n\n";

			for (int i{ 0 }; i < numberFactors.size(); ++i)
			{
				cout << numberFactors[i] << " * " << numbers[i] << " = " << number << '\n';
			}

			cout << '\n';
		}

		cin.get();
		cin.ignore();

		goTo("menu");
	}

	return numberFactors;
}

void findFactorsMenu()
{
	clear();
	title("factors of number");

	int number{};

	cout << "input a number: \n\n";

	cout << "> ";
	cin >> number;

	findFactors(number, true);
}

// ------- \\

void findCF(int number1, int number2, bool type) // greatest = true, least = false
{
	clear();

	vector<int> number1Factors{ findFactors(number1, false) };
	vector<int> number2Factors{ findFactors(number2, false) };
	vector<int> commonFactors{};

	cout << "first number (" << number1 << "): ";
	for (int i{ 0 }; i < number1Factors.size(); ++i)
	{
		if (i == number1Factors.size() - 1)
		{
			cout << i;
		}
		else
		{
			cout << i << ", ";
		}
	}

	cout << '\n';

	cout << "second number (" << number2 << "): ";
	for (int i{ 0 }; i < number2Factors.size(); ++i)
	{
		if (i == number2Factors.size() - 1)
		{
			cout << i;
		}
		else
		{
			cout << i << ", ";
		}
	}

	cout << "\n\n";

	cout << "common factors: \n";

	for (int i{ 0 }; i < number1Factors.size(); ++i)
	{
		for (int o{ 0 }; o < number2Factors.size(); ++o)
		{
			if (number1Factors[i] == number2Factors[o])
			{
				if (i == number1Factors.size() - 1)
				{
					cout << number1Factors[i];
				}
				else
				{
					cout << number1Factors[i] << ", ";
				}

				commonFactors.push_back(number1Factors[i]);
			}
		}
	}

	if (type)
	{
		cout << "\n\nthe greatest common factor is ";

		setTextColor(6);
		cout << commonFactors[commonFactors.size() - 1] << "\n\n";
		resetTextColor();
	}
	else
	{
		cout << "\n\nthe least common factor is " << commonFactors[0] << "\n\n";
	}

	cin.get();
	cin.ignore();

	goTo("menu");
}

void findCFMenu(bool type)
{
	clear();
	title("common factors of number");

	string response{};
	int number1{};
	int number2{};

	cout << "input a number: \n\n";

	cout << "> ";
	cin >> number1;

	clear();

	cout << "first number: " << number1 << "\n\n";

	cout << "input another number: \n\n";

	cout << "> ";
	cin >> number2;

	clear();

	cout << "first number: " << number1 << '\n';
	cout << "second number: " << number2 << "\n\n";

	cout << "are you satisfied with these numbers?\n\n";

	cout << "> ";
	cin >> response;

	if (response == "yes" || response == "y")
	{
		findCF(number1, number2, type);
	}
	else if (response == "no" || response == "n")
	{
		goTo("menu");
	}
	else
	{
		invalidInput("please specify yes or no", "menu");
	}
}

// ------- \\

void quit()
{
	clear();

	for (int i{ 3 }; i > 0; --i)
	{
		title("exiting in ", i);

		cout << "okay, exiting in " << i;

		sleep(1);
		clear();
	}

	exit(1);
}

void menu()
{
	clear();
	title("menu");

	char response{};

	cout << "factor calculator\n\n";

	cout << "1. find factors of number\n";
	cout << "2. find GCF of numbers\n";
	cout << "3. find LCF of numbers\n";
	cout << "4. quit\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		findFactorsMenu();
	break;

	case '2':
		findCFMenu(true);
		break;

	case '3':
		findCFMenu(false);
		break;

	case '4':
		quit();
		break;
	}

	invalidInput("please specify 1, 2, 3, or 4", "menu");
}

// ------- \\

void goTo(string function)
{
	if (function == "menu")
	{
		menu();
	}
}

int main()
{
	title("credits");

	setTextColor(6);
	cout << "written by chapel1337\n";
	cout << "made on 11/7/2022\n";
	resetTextColor();

	sleep(2);

	Beep(200, 325);
	menu();
}

// ------- \\