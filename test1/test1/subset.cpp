#include "stdafx.h"
#include "subset.h"
#include <vector>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> subsets(vector<int> &nums) {
	// write your code here
	vector<vector<int> > S;
	vector<int>temp;
	S.push_back(temp);
	int len = nums.size();
	if (!len) {
		return S;
	}

	//std::sort(dat, dat + 5, [](char *a, char *b) { return strcmp(a, b) < 0; });

	std::sort(nums.begin(), nums.end());
	for (int i = 0; i < len; i++) {
		int t = S.size();
		for (int j = 0; j < t; j++) {
			std::vector<int> temp = S[j];
			temp.push_back(nums[i]);
			S.push_back(temp);
		}
	}


	return S;
}


void run_subset() {
	vector<int> vec_set = { 1, 2, 3 };

	vector<vector<int>> r = subsets(vec_set);

	printf("[\n");
	for (vector<int> vec_it : r) {
		printf("[");
		for (int i = 0; i < vec_it.size(); i++) {
			printf("%d", vec_it[i]);
			if (i < vec_it.size() - 1) {
				printf(" ,");
			}
		}
		printf("]\n");
		
	}
	printf("]\n");

}



//=============================================
