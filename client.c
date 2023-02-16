/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:12:15 by manujime          #+#    #+#             */
/*   Updated: 2023/02/16 15:07:12 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send(int pid, char c)
{
	int	bit_c;

	bit_c = 0;
	while (bit_c < 8)
	{
		if ((c & (1 << bit_c)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(50);
		bit_c++;
	}
}

void	ft_recon(int s)
{
	if (s == SIGUSR1)
		ft_printf("Correct pro");
}

int	main(int argc, char **argv)
{
	int					c;
	int					pid;
	struct sigaction	sign;

	c = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		sign.sa_handler = &ft_recon;
		sigaction(SIGUSR1, &sign, NULL);
		while (argv[2][c] != '\0')
		{
			ft_send(pid, argv[2][c]);
			c++;
		}
		ft_send(pid, argv[2][c]);
	}
	else
	{
		ft_printf("WRONG INPUT FORMAT\ntry with: ./client \"PID\" \"message\"");
	}
	return (0);
}
