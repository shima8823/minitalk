/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:13:28 by shima             #+#    #+#             */
/*   Updated: 2022/07/28 14:20:26 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_info_char
{
	char	c;
	int		len;
};

struct s_info_char	g_info_c;

void	setting_signal(void);
void	sighandler(int sig, siginfo_t *info, void *ucontext);

int	main(void)
{
	g_info_c.c = 0;
	g_info_c.len = 0;
	ft_printf("PID: [%d]\n", (int)getpid());
	setting_signal();
	while (1)
		pause();
	exit(0);
}

void	sighandler(int sig, siginfo_t *info, void *ucontext)
{
	g_info_c.c <<= 1;
	if (sig == SIGUSR2)
		g_info_c.c += 1;
	g_info_c.len++;
	if (g_info_c.len == 8)
	{
		write(STDOUT_FILENO, &g_info_c.c, 1);
		g_info_c.c = 0;
		g_info_c.len = 0;
	}
}

void	setting_signal(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = sighandler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}
