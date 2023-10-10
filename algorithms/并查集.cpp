#include<stdio.h>

int n, m;
int p[15000];
int vis[15000];

int find(int x) {
	if (x == p[x]) {
		return x;

	}
	else {
		p[x] = find(p[x]);
		return p[x];
	}
}

void un(int x, int y) {

	int xx = find(x);
	int yy = find(y);

	if (xx != yy) {
		p[yy] = xx;
	}
}

int main() {

	FILE* fp = NULL;
	fp = fopen("virus.in", "r");
	if (fp == NULL) {
		printf("open fail.\n");
	}

	fscanf(fp, "%d\n", &m);
	fscanf(fp, "%d\n", &n);

	for (int i = 1; i <= 2 * m; i++)
		p[i] = i;

	for (int i = 1; i <= n; i++) {

		char c;
		int a, b;
		fscanf(fp, "%c %d %d\n", &c, &a, &b);

		if (c == 'S') {
			un(a, b);
		}
		else if (c == 'H') {
			un(a + m, b);
			un(a, b + m);
		}
	}

	fclose(fp);

	int count = 0;
	for (int i = 1; i <= m; i++) {

		int t = find(i);

		if (!vis[t]) {
			vis[t] = 1;
			count++;
		}
	}

	fp = fopen("virus.out", "w+");
	fprintf(fp, "%d\n", count);
	fclose(fp);
	return 0;
}
