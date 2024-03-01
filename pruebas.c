#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[], char **env)
{
	size_t	i;

	i = -1;
	argv++;
	argc--;
	while(env[++i])
		printf("%s\n", env[i]);
	env = (char **)malloc(sizeof(char *) * (i + 2));
	return (0);
}