#include "../includes/philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*res;

	res = malloc(bytes);
	if(res == NULL)
		error(MALLOC_ERR);
	return (res);
}

int ft_isnbr(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int ft_atoi(char *str)
{
    int i;
    int res;
    int sign;

    i = 0;
    sign = 1;
    res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
    if(str[i] == '-')
    {
        sign = -1;
        i++;
    }
    while(str[i])
    {
        res = res  * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void ft_putend_fl(char *msg,int fd)
{
	if(!msg || fd < 0)
		return ;
	if(msg)
	{
		write(fd, msg, ft_strlen(msg));
		write(fd, "\n", 1);
	}
}
