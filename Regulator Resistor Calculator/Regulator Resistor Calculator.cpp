// Regulator Resistor Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "defines.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
	std::fstream valuesfile;
	std::vector<float> values(RESISTOR_VALUES_FILE, std::fstream::in | std::fstream::out);
	if (!valuesfile.is_open())
	{
		std::cerr << "ERROR: Missing resistor values file (values.txt)!\n" << "A blank values.txt file has been created.";
		valuesfile << "";
		return EXIT_FAILURE;
	}
	if (valuesfile.peek() == EOF)
	{
		std::cerr << "ERROR: Resistor values file (values.txt) is empty!\n" << "Fill in the available resitor values and try again.";
		return EXIT_FAILURE;
	}
	else
	{
		std::string value;
		while (valuesfile >> value)
		{
			try
			{
				values.push_back(std::stof(value));
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what();
			}
		}
	}
	

	float vout;
	while (true)
	{
		std::cout << "Enter desired output voltage: ";
		if (std::cin >> vout)
		{
			break;
		}
		else
		{
			std::cout << "Invalid input!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	double r2;
	while (true)
	{
		std::cout << "Enter value for R2 [" << TPS7A49_DEFAULT_R2 << "]: ";
		if (std::cin >> r2)
		{
			if (r2 == NULL)
			{
				r2 = TPS7A49_DEFAULT_R2;
			}
			if (TPS7A49_VFB / r2 < 5e-6)
			{
				std::cout << "Resistive network current too low! Try entering a lower value.\n";
			}
			else
			{
				break;
			}
		}
		else
		{
			std::cout << "Invalid input!\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	double r1 = r2 * (12 / TPS7A49_VFB - 1);
	float singleresistorhigher = 0;
	float singleresistorlower = 0;
	for (auto& value : values)
	{
		float ratio = value / r1;
		float ratiohigh = singleresistorhigher / r1;
		float ratiolow = singleresistorlower / r1;
		if (ratio == 1)
		{
			singleresistorhigher = r1;
			singleresistorlower = r1;
			break;
		}
		else if (ratio > 1 && ratio < ratiohigh)
		{
			singleresistorhigher = value;
		}
		else if (ratio > ratiolow)
		{
			singleresistorlower = value;
		}
	}
	float dualresistorhigher[2];
	float dualresistorlower[2];
	for (auto& value1 : values)
	{
		for (auto& value2 : values)
		{
			float rtot = 1 / (1 / value1 + 1 / value2);

		}
	}
	return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
