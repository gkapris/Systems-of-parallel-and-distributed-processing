#include <stdio.h>
#include <time.h>

int main()
{
	srand(time(NULL));
	int i;
	float total_trap, y1, y2;
	printf("Enter number of trapezoids: \n");
	scanf("%f", &total_trap);

	float step = 3 / total_trap;
	int x1 = 1;
	int x2 = 1 + step;
	float total_surf = 0;
	for(i=0; i<total_trap; i++){
		y1 = 3 * x1 * x1 + 1;
		y2 = 3 * x2 * x2 + 1;
		total_surf += (y2 + y1) * (x2 - x1) / 2;
		x1 += step;
		x2 += step;
	}

	printf("Total surface is: %f \n", total_surf);

	return 0;
}
