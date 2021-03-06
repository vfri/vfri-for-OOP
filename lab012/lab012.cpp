// lab012.cpp: определяет точку входа для консольного приложения.
// преобразует число из записи в позиционной системы с одним основанием в систему с другим. Число должно помещаться в integer

#include "stdafx.h"

void ValidDigit(int direction, char& symbol, int& digit, int radix, int& inValid) 
{   // direction = 1 -- сделать из цифры однозначное число, direction = 0 -- сделать из однозначного числа цифру
	std::string digSetUpper = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string digSetLower = "0123456789abcdefghijklmnopqrstuvwxyz";
	std::string digitsUpper = digSetUpper.substr(0, radix);
	std::string digitsLower = digSetLower.substr(0, radix);


	int digUppValue = digitsUpper.find(symbol);
	int digLowValue = digitsLower.find(symbol);

	inValid = 0;

	if (direction == 1)
	{
		
		if (digUppValue != std::string::npos)
		{
			digit = digUppValue;
		}
		else if (digLowValue != std::string::npos)
		{
			digit = digLowValue;
		}
		else
		{
			inValid = 1;
		}
	}
	else
	{
		if ((digit >= 0) && (digit < radix))
		{
			symbol = digitsUpper.at(digit);
		}
		else
		{
			inValid = 1;
		}
	}
}

int StringToInt(const std::string& str, int radix, int& wasError)
{
	int result = 0;
	int signum = 1;
	int bound = std::numeric_limits<int>::max();
		
	size_t pos = 0;
	
	if (str.at(0) == '-')
	{
		signum = -1;
		bound = std::numeric_limits<int>::min();
		pos++;
	}
		
	int digValue = 0;
			
	while (pos < str.length())
	{
		char symbol = str.at(pos);
		ValidDigit(1, symbol, digValue, radix, wasError);
		if (wasError == 1)
		{
			break;
		}
		int quotient = std::abs((bound - signum * digValue) / radix);
		int rest = std::abs((bound - signum * digValue) % radix);
		if ((result < quotient) || ((result == quotient) && (rest == 0)))
		{
			result = result * radix + digValue;
		}
		else
		{
			wasError = 2; // переполнение
			return bound;
		}
		pos++;
	}
	
	return result * signum;
}

std::string IntToString(int n, int radix, int& wasError)
{
	std::string numberImage = std::string();
	int signum = 1;
	int mediaResult = n;
	int currDigit;
	char nextSymbol = '#';
	
	while (mediaResult != 0)
	{
		if (n > 0)
		{
			currDigit = mediaResult % radix;
			mediaResult = (mediaResult - currDigit) / radix;
		}
		if (n < 0)
		{
			currDigit = (-mediaResult) % radix;
			mediaResult = (mediaResult + currDigit) / radix;
		}
		ValidDigit(0, nextSymbol, currDigit, radix, wasError);
		numberImage.insert(0, 1, nextSymbol);
	}
	if (n == 0)
	{
		numberImage.insert(0, 1, '0');
	}
	if (n < 0)
	{
		numberImage.insert(0, 1, '-');
	}
	numberImage.push_back('\n');
	return numberImage;
}


int main(int argc, char* argv[])
{
	std::cout << "Transform given integer value form one number system to other\n" << std::endl;
	std::cout << "Radices of value from 2 to 36. Digits from 10 to 35 are letters form A to Z\n" << std::endl;

	if (argc < 4)
	{
		std::cout << "The program must have three arguments: 1) present radix; 2) new radix; 3) value to transform" << std::endl;
		return 0; // недостаточно аргументов
	}

	int sourceNotation = std::strtoul(argv[1], nullptr, 10);
	if ((sourceNotation < 2) || (sourceNotation > 36))
	{
		std::cout << "Invalid source notation! Number between 2 and 36 expected" << std::endl;
		return 1;
	}
	int destiNotation = std::strtoul(argv[2], nullptr, 10);
	if ((destiNotation < 2) || (destiNotation > 36))
	{
		std::cout << "Invalid destination notation! Number between 2 and 36 expected" << std::endl;
		return 1;
	}
	
	std::string testString = argv[3];
		
		
	int error = 0;
	int amount = StringToInt(testString, sourceNotation, error);
	if (error == 1)
	{
		std::cout << "Illegal symbols in number image!" << std::endl;
		return 1;
	}
	if (error == 2)
	{
		std::cout << "Given number " << argv[3] << " is out of integer range!" << std::endl;
		return 1;
	}

	std::string newImage = IntToString(amount, destiNotation, error);
	std::cout << argv[3] << " in radix " << sourceNotation << " is " << newImage.c_str() << "(in radix " << destiNotation << ")" << std::endl;

		
	return 0;
}

