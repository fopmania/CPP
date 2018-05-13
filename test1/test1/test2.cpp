#include <stdio.h>

int temp[100];
int match_num = 0;


void Comb(int n, int r, int q, int sum_num) {
	if (r == 0) {
		int sum = 0;
		for (int i = q - 1; i >= 0; i++) {
			sum += T[i];
		}
		if (sum == sum_num)
			return;
	}
	else if (n<r) {
		return;
	}
	else {
		temp[r - 1] = data[n - 1];
		Comb(n - 1, r - 1, q, sum_num);
		Comb(n - 1, r, q, sum_num);
	}
}

int main() {
	int T, N, V;
	do {
		scanf("%d", &T);
	} while (T < 1 || T > 100)
		do {
			scanf("%d", &N);
		} while (N < 1 || N > 100)
			scanf("%d", &V);


		int buf[N];
		int i = 0;
		while (i< N)
		{
			scanf("%d", &d[i++]);
		}

		Comb(N, 4, 4, V);
		if (sum_num == T)
			printf("1")
		else
			printf("0")


			//code
			return 0;
}