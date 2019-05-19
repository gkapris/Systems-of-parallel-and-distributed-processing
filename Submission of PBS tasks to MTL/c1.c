#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Hello World!\n");

	char hostname[1024];
	hostname[1023] = '\0';
	gethostname(hostname, 1023);
	printf("Hostname: %s\n", hostname);

	int vl = 0;
	vl = sysconf(_SC_NPROCESSORS_CONF);
	printf("Number of processors: %d\n", vl);

	return 0;
}
