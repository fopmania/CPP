#include "stdafx.h"
#include "search_string.h"


#include <string.h>

struct word_info {
	char *word;
	int cnt;
};

void Most_frequent_word_in_an_array_of_strings() {
	char buf[1000][100];
	char result[100][100];
	int T, N;
	struct word_info  winfo[1000];

	do {
		scanf("%d", &T);
	} while (T < 1 || T > 100);

	for (int i = 0; i < T; i++) {
		do {
			scanf("%d", &N);
		} while (N < 1 || N > 1000);

		int k = 0;
		while (k< N)
		{
			scanf("%s", buf[k]);
			winfo[k].word = buf[k];
			winfo[k].cnt = 0;
			k++;
		}

		for (int n = 0; n < N; n++) {
			for (int n2 = 0; n2 < N; n2++) {
				if (strcmp(winfo[n].word, buf[n2]) == 0) {
					winfo[n].cnt++;
				}
			}
		}

		int max_freq = winfo[0].cnt;
		char *max_word = winfo[0].word;
		strcpy(result[i], winfo[0].word);
		for (int n = 1; n < N; n++) {
			if (max_freq <= winfo[n].cnt) {
				if (max_freq == winfo[n].cnt && strcmp(max_word, winfo[n].word) < 0)
					continue;
				max_word = winfo[n].word;
				max_freq = winfo[n].cnt;
				strcpy(result[i], winfo[n].word);
			}
		}
		//printf("%s  :  %d\n", winfo[result[i]].word, winfo[result[i]].cnt);
	}
	for (int i = 0; i < T; i++) {
		printf("%s\n", result[i]);
	}
}