#include <string.h>
#include <stdlib.h>

char	*strjoin(char *str1, char *str2)
{
	size_t	len;
	char	*new;
	char	*tmp;

	len = (str1) ? strlen(str1) : 0;
	len += (str2) ? strlen(str2) : 0;
	if ((new = (char *)malloc(sizeof(char) * (len + 1))))
	{
		tmp = new;
		if (str1)
			tmp = strcpy(new, str1);
		if (str2)
			strcpy(tmp, str2);
	}
	return (new);
}

void	strdel(char **str)
{
	free(*str);
	*str = NULL;
}
