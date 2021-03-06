// lab002.cpp: определяет точку входа для консольного приложения.
// Выводит все числа от 1 до n, делящиеся нацело на сумму своих цифр. 
// n передается через аргумент командной строки 

#include "stdafx.h"

int SumDigits(int i)  // вычисляет сумму цифр положительного числа i
{
	int sum = 0;

	// цикл продолжается до тех пор, пока число не станет равным 0
	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}



int main(int argc, char* argv[])
{
	int i, sumDigs, n;
	bool found = false; // найдено хотя бы одно число с нужным свойством
	
	
	if (argc < 2)
	{
		printf("Diapazone border is set to 1000. Another border you may set in command prompt argument\n");
		n = 1000;
	}
	else
	{
		n = std::stoi(argv[1]);
		if (n < 1)
		{
			printf("Wrong diapazone border!\n");
			return 1;
		}
	}

	for (i = 1; i <= n; ++i)
	{
		sumDigs = SumDigits(i);
		if ((i % sumDigs) == 0)
		{
			if (found)
			{
				printf(", ");
			}			
			found = true;
			printf("%d", i);
		}
	}
	
	printf("\n");
	
	return 0;
}

