#include "pch.h"

#define init_() clock_t __time__mark__
#define start_() __time__mark__=clock()
#define get_time_diff() (clock()-__time__mark__)

using namespace BigInt;


int main() {
	Bigint a = 4558;
	cout << a.pow(486); // ~1.46 * 10^1778
	cout << endl;
	cout << 4_Bigint .pow(486) << endl;

	//system("pause");
	return 0;
}

