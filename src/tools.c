#include <string.h>
#include <stdlib.h>

char	*strjoin(char *str1, char *str2)
{
	size_t	len;
	size_t	len2;
	char	*new;
	char	*tmp;

	len = (str1) ? strlen(str1) : 0;
	len2 = (str2) ? strlen(str2) : 0;
	if ((new = (char *)malloc(sizeof(char) * (len + len2 + 1))))
	{
		tmp = new;
		if (str1)
			tmp = stpncpy(new, str1, len + 1);
		if (str2)
			stpncpy(tmp, str2, len2 + 1);
	}
	return (new);
}

void	strdel(char **str)
{
	free(*str);
	*str = NULL;
}

int		same_square(int *s1, int *s2)
{
	if (s1[0] == s2[0] && s1[1] == s2[1])
		return (1);
	return (0);
}
