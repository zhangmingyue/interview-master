#include <stdio.h>
#include <vector>
#include "qh_vector.h"


int main(int argc, char* argv[])
{

	qh::vector<int> num_vect(10);

	assert(10 == num_vect.capacity());

	num_vect.push_back(1);

	int* begin = num_vect.begin();
	while (begin != num_vect.end())
	{
		printf("%d,",*begin);
		begin++;
	}
	printf("\n");
	assert(20 == num_vect.capacity());
	assert(11 == num_vect.size());

	num_vect.reserve();
	assert(11 == num_vect.capacity());
	assert(false == num_vect.empty());

	num_vect.resize(5);
	begin = num_vect.begin();
	while (begin != num_vect.end())
	{
		printf("%d,",*begin);
		begin++;
	}
	printf("\n");

	num_vect[2] = 1;
	assert(1 == num_vect[2]);

	num_vect.pop_back();
	assert(5 == num_vect.capacity());
	assert(4 == num_vect.size());
	begin = num_vect.begin();
	while (begin != num_vect.end())
	{
		printf("%d,",*begin);
		begin++;
	}
	printf("\n");

	qh::vector<int> num_vect121;
	num_vect121 = num_vect;
	begin = num_vect121.begin();
	while (begin != num_vect121.end())
	{
		printf("%d,",*begin);
		begin++;
	}
	printf("\n");

	num_vect.clear();
	assert(true == num_vect.empty());

#ifdef WIN32
	system("pause");
#endif

	return 0;
}

