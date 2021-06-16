#include "ft_printf.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;
	int		e;

	e = 0;
	i = 0;
	while (s[i] != '\0')
		i++;
	if (!(str = malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	while (e < i)
	{
		str[e] = s[e];
		e++;
	}
	str[e] = '\0';
	return (str);
}