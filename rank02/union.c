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
		l = 1;
		while(l < 3)
		{
			q = 0;
			while(argv[l][q])
			{
				if (!used[(unsigned char)argv[l][q]])
				{
					write(1, &argv[l][q], 1);
					used[(unsigned char)argv[l][q]] = 1;
				}
				q++;
			}
			l++;
		}
	}
	write(1, "\n", 1);
	return(0);
}
