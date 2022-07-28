/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:13:23 by shima             #+#    #+#             */
/*   Updated: 2022/07/28 14:20:05 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t pid, char c);
void	test_arg(int argc, char *argv[], pid_t *pid);
int		pid_atoi(const char *str);

int	main(int argc, char *argv[])
{
	size_t	i;
	pid_t	pid;

	test_arg(argc, argv, &pid);
	i = 0;
	while (argv[2][i])
	{
		send_char(pid, argv[2][i]);
		i++;
	}
	exit(0);
}

void	send_char(pid_t pid, char c)
{
	int	count;
	int	bit;

	count = 0;
	while (count < 8)
	{
		if (usleep(100) == -1)
			exit(1);
		if ((c << count & 128))
			bit = 1;
		else
			bit = 0;
		if (kill(pid, SIGUSR1 + bit) == -1)
			exit(1);
		count++;
	}
}

void	test_arg(int argc, char *argv[], pid_t *pid)
{
	if (argc != 3)
		exit(1);
	*pid = (pid_t)pid_atoi(argv[1]);
	if (*pid < 1 || *pid < 100 || *pid > 99998)
		exit(1);
}

int	pid_atoi(const char *str)
{
	unsigned long	num;
	size_t			i;

	num = 0;
	i = 0;
	if (!('1' <= str[0] && str[0] <= '9'))
		exit(1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			exit(1);
		num = num * 10 + str[i++] - '0';
	}
	return (num);
}
