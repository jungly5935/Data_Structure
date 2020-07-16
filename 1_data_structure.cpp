#pragma warning(disable:4996)
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	char check;
	int num = 0;
	float* big_o = NULL;

	FILE* input_fp, * output_fp;

	if ((input_fp = fopen("hw1.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw1.inp");
	}

	if ((output_fp = fopen("hw1.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "hw1.out");
	}

	//calloc(num,sizeof(float))
	if ((big_o = (float*)malloc(sizeof(float) * num)) == NULL)
	{
		fprintf(stderr, "memory allocation error\n");
	}



	while (1) {

		num = 0;
		while (1) {
			fscanf(input_fp, "%c", &check);
			if (check == '*') {
				break;
			}
			else if (check == '\n')
				break;
			else {
				num *= 10;
				num += check - 48;
			}
		}
		if (check == '*')
			break;


		int re = 1;

		switch (1) {



		case 1:
			fprintf(output_fp, "1)%d ", num);
		case 2:
			fprintf(output_fp, "2)%d ", (int)(log2(num)));
		case 3:
			fprintf(output_fp, "3)%d ", (num * (int)log2(num)));
		case 4:
			for (int i = 0; i < num; i++) {
				re *= 2;
			}
			fprintf(output_fp, "4)%d ", (int)re);
			re = 1;
		case 5:
			int n = num;
			for (int i = 0; i < n; i++) {
				re *= num;
				num--;
			}
			fprintf(output_fp, "5)%d\n", (int)re);
			re = 1;
		}

	}
	fprintf(output_fp, "*\n");

	fclose(input_fp);	fclose(output_fp);
	free(big_o);

	return 0;

}