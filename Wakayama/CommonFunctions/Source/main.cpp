/**
 * main.cpp
 *
 * Copyright (c) 2016 HIROMOTO,Masaki
 *
 */
#include "main.hpp"

using namespace hiro;

int test_1_Degree(void);
int test_1_Degree(void)
{

	std::cout << "=========================" << "\n";
	{
		Degree deg( 10, 20, 30.1 );

		deg.print();
		{
			int degHoge = deg.getDegrees();
			std::cout << "( " << degHoge << " )" << "\n";
		}
		deg.setDegrees( 20 );
		deg.print();
	}
	{
		Degree deg;
		deg.print();
	}
	std::cout << "=========================" << "\n";
	return EXIT_SUCCESS;
}

int test_2_TotalStation(void);
int test_2_TotalStation(void)
{
	std::cout << "=========================" << "\n";
	{
		TotalStation tStation( 1071.1234, 20.123 );

		tStation.print();
		{
			double tStationHoge = tStation.getLength();
			std::cout << "( " << tStationHoge << " )" << "\n";
		}
		{
			double tStationHoge = tStation.getAzimuth();
			std::cout << "( " << tStationHoge << " )" << "\n";
		}
		tStation.setLength( 20 );
		tStation.print();
	}
	{
		TotalStation tStation;
		tStation.print();
	}
	std::cout << "=========================" << "\n";
	return EXIT_SUCCESS;
}



int main(int argc, char *argv[])
{
	test_1_Degree();
	test_2_TotalStation();
    return EXIT_SUCCESS;
}
