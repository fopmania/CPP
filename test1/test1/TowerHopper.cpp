#include "stdafx.h"
#include "TowerHopper.h"

#include <vector>
#include <map>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std;

vector<pair<bool, int>> jump;

int arr[] = { 4, 2, 0, 4, 2, 0 };

int arr_size = sizeof(arr) / sizeof(arr[0]);





void checkHopper(int k) {
	if (k + arr[k] >= arr_size) {
		jump[k].first = true;
		jump[k].second = 1;
	}
	else {
		for (int i = k + 1; i < k + arr[k]; i++) {
			if (jump[i].first) {
				if (jump[k].first) {
					jump[k].second = min(jump[i].second + 1, jump[k].second);
				}
				else {
					jump[k].first = true;
					jump[k].second = jump[i].second + 1;
				}
			}
		}
	}

}

int getMinHopping() {
	jump.resize(arr_size, make_pair(false, 0));
	for (int i = arr_size - 1; i >= 0; i--) {
		checkHopper(i);
	}

	if (jump[0].first)
		return jump[0].second;

	return -1;
}


void runTowerHoppper() {
	for (int i = 0; i < arr_size; i++) {
		cout << "[" << arr[i] << "] ";
	}
	cout << endl;
	
	cout << "\n getMinHopping : " << getMinHopping() << endl;


	for (pair<bool, int> p : jump) {
		cout << "[" << p.first << ":"<< p.second  << "] ";
	}
	cout << endl;

	vector<int> vt(arr, arr + arr_size);
	std::make_heap(vt.begin(), vt.end());

	for (int v : vt) {
		cout << "[" << v << "] ";
	}
	std::cout << "\ninitial max heap   : " << vt.front() << '\n';


}
