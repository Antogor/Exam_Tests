#include <unistd.h>

int main (int argc, char **argv)
{
	int used[255];
	int l = 0;
	int j = 0;

	if (argc == 3)
	{
		while(l < 255)
			used[l++] = 0;
		l = 1;
		while(l < 3)
		{
			j = 0;
			while(argv[l][j])
			{
				if (!used[(unsigned char)argv[l][j]])
				{
					write(1, &argv[l][j], 1);
					used[argv[l][j]] = 1;
				}
				j++;
			}
			l++;
		}
	}
	write(1,"\n", 1);
	return(0);
}
	

