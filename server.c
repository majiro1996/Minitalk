/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:34:35 by manujime          #+#    #+#             */
/*   Updated: 2023/02/16 11:23:08 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_display(int signal, siginfo_t *info, void *uap)
{
	static unsigned char	byte;
	static int				bit_c;

	(void)uap;
	if (signal == SIGUSR1)
		byte = byte | (1 << bit_c);
	bit_c++;
	if (bit_c == 8)
	{
		if (byte == '\0')
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
		}
		else
			ft_printf("%c", byte);
		byte = 0;
		bit_c = 0;
	}
}

int	main(void)
{
	struct sigaction	sign;

	sign.sa_sigaction = &ft_display;
	sign.sa_flags = SA_SIGINFO;
	sigemptyset(&sign.sa_mask);
	sigaddset(&sign.sa_mask, SIGUSR1);
	sigaddset(&sign.sa_mask, SIGUSR2);
	ft_printf("Welcome to minitalk\nUse this PID in your client: %d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sign, NULL);
		sigaction(SIGUSR2, &sign, NULL);
		pause();
	}
	return (0);
}
