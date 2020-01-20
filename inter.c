#include <unistd.h>

int main (int argc, char **argv)
{
	int used[255];
	int l = 0;
	int j = 0;

	if (argc == 3)
	{
		while(l < 255)
		{
			used[l] = 0;
			l++;
		}
		l = 2;
		while(l > 0)
		{
			j = 0;
			while(argv[l][j])
			{
				if (l == 2 && !used[(unsigned char)argv[l][j]])
					used[(unsigned char)argv[l][j]] = 1;
				else if (l == 1 && used[(unsigned char)argv[l][j]] == 1)
				{
					write(1, &argv[l][j], 1);
					used[(unsigned char)argv[l][j]] = 2;
				}
				j++;
					
			}
			l--;
		}
	}
	write(1, "\n", 1);
	return (0);

}
