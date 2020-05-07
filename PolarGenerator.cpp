#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class PolarGenerator 
{
	public: 
		bool nincsTarolt = true;
		double tarolt;
		

	void PolGen()
	{
		nincsTarolt = true;
	}

	double kovetkezo()
	{
		if (nincsTarolt)
		{
			double u1, u2, v1, v2, w;
			do 
			{
				u1 = ((double) rand() / (RAND_MAX));
				u2 = ((double) rand() / (RAND_MAX));
				
				v1 = 2 * u1 - 1;
				v2 = 2 * u2 - 1;
				
				w = v1 * v1 + v2 * v2;

			} while (w > 1);

			double r = sqrt ((-2 * log (w)) / w);

			tarolt = r * v2;
            nincsTarolt = !nincsTarolt;

			return r * v1;
		}
		else 
		{
			nincsTarolt = !nincsTarolt;
            return tarolt;
		}
	}
};

int main(int argc, const char **argv)
{
	PolarGenerator g;
	srand (time(NULL));
	for (int i = 0; i < 10; ++i)
	{
		cout << g.kovetkezo() << endl;
	}
	
	return 0;
}
