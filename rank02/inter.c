#include <unistd.h>

int main (int argc, char **argv)
{
	int l;
	int q;
	int used[255];

	if (argc == 3)
	{
		l = 0;
		while(l < 255)
			used[l++] = 0;
		l = 2;
		while(l > 0)
		{
			q = 0;
			while(argv[l][q])
			{
				if (l == 2 && !used[(unsigned char)argv[l][q]])
				{
					used[(unsigned char)argv[l][q]] = 1;
				}
				if (l == 1 && used[(unsigned char)argv[l][q]])
				{
					write(1, &argv[l][q], 1);
					used[(unsigned char)argv[l][q]] = 2;
				}
				q++;
			}
			l--;
		}
	}
	write(1, "\n", 1);
	return(0);
}
