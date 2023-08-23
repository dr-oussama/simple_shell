#include "main.h"

int _getline_helper(char **lnpt, size_t *n)
{
	if (*lnpt == NULL || *n == 0)
	{
		*n = 128;
		*lnpt = malloc(*n);
		if (*lnpt == NULL)
			return (-1);
	}
	return (0);
}

ssize_t _getline(char **lnpt, size_t *n, FILE *strm)
{
	ssize_t bRead = 0;
	size_t pstn = 0, newSize;
	static char buf[READ_BUF_SIZE];
	static size_t bSize, bufP;
	char *newBuffer;

	if (lnpt == NULL || n == NULL || strm == NULL
		|| _getline_helper(lnpt, n) == -1)
		return (-1);
	while (1)
	{
		if (bufP >= bSize)
		{
			bRead = read(strm->_fileno, buf, READ_BUF_SIZE);
			if (bRead <= 0 && pstn == 0)
				return (-1);
			else if (bRead <= 0)
				break;
			bSize = bRead;
			bufP = 0;
		}
		if (pstn >= *n - 1)
		{
			newSize = *n * 2;
			newBuffer = realloc(*lnpt, newSize);
			if (newBuffer == NULL)
				return (-1);
			*lnpt = newBuffer;
			*n = newSize;
		}
		(*lnpt)[pstn++] = buf[bufP++];
		if ((*lnpt)[pstn - 1] == '\n')
			break;
	}
	(*lnpt)[pstn] = '\0';
	return (pstn);
}
