 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 
 #define H_ARRAYSIZE(a) \
 	((sizeof(a) / sizeof(*(a))) / \
 	static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

int myCharToInt(const char* input, int*** outarray)
{
	int moutain_count = *input - '0';

	(*outarray) = (int**)malloc(sizeof(int*)*moutain_count);

	for(int i = 0;i < moutain_count;i++)
	{
		(*outarray)[i] = (int*)malloc(sizeof(int)*3);
	}

	for(int i = 0;i < moutain_count;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			(*outarray)[i][j] = 0;
		}
	}

	int k =1;
	for(int i = 0;i < moutain_count;i++)
	{
		for(int j = 0;j < 3;j++)
		{
			(*outarray)[i][j] = input[2*k] - '0';
			k++;
		}
	}

	return moutain_count;
}

 int resolve(const char* input)
 {
	 int moutain_count = 0;
	 int** moutain_attribute = NULL;

	 int horizontal_distance = 0;

	 int vertical_distance = 0;

	 moutain_count = myCharToInt(input, &moutain_attribute);

	 horizontal_distance = moutain_attribute[moutain_count-1][1];

	 for (int i = 0; i < moutain_count; i++)
	 {
		 vertical_distance += (moutain_attribute[i][2] * 2);
	 }

	 if (1 == moutain_count)
	 {
		 return horizontal_distance + vertical_distance;
	 }

	 for (int i = 0; i < moutain_count; i++)
	 {
		 if ((i +1) <= (moutain_count - 1) && moutain_attribute[i][1] >= moutain_attribute[i+1][0] &&
			 moutain_attribute[i][1] <= moutain_attribute[i+1][1])
		 {
			 vertical_distance -= ((moutain_attribute[i][2] <= moutain_attribute[i+1][2]?moutain_attribute[i][2]:moutain_attribute[i+1][2])*2);
		 }
	 }

	 for (int i = 0; i < moutain_count; i++)
	 {
		 if (moutain_attribute[i])
		 {
			 free(moutain_attribute[i]);
		 }
	 }
	 free(moutain_attribute);
	 
	 return (horizontal_distance+vertical_distance);
 }

int main(int argc, char* argv[]) 
{
	const char* input[] = {
		"3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
		"1\n1,2,1\n",
		"2\n1,2,1\n2,3,2",
		"3\n1,2,1\n2,3,2\n3,6,1",
		"4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
		"5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
		"1\n0,1,1",
		"2\n0,1,1\n2,4,3",
		"3\n0,1,1\n2,4,3\n3,5,1",
		"4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
		"5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
		//TODO please add more test case here
		//"2\n2,4,3\n0,1,1"
	};
	int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
	for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
	{
		assert(resolve(input[i]) == expectedSteps[i]);
	}
	return 0;
}
