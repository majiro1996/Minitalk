/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:34:35 by manujime          #+#    #+#             */
/*   Updated: 2023/02/20 14:54:49 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/*The ft_display function handles the signal sent from the client,
with SIGUSR1 a 1 is charged into byte at the bit_c position,
-to do this it creates a mask with 1 (00000001) and moves the 1
bit_c positions to the left, then preforms a bitwise OR to byte-
with SIGUSR2 the position remains a 0, once the byte 
complete the character is printed and the variables reset,
if the character is \0 it prints \n and send a SIGUSR1 signal back
to the client to notice the message has been properly handled*/
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

/*The main function reates an object for the sigaction struct
assign ft_display to be called when a signal is received,
SA_SIGINFO is used to get the pid of the client in ft_display
adds the SIGUSR1 and SIGUSR2 signal to the mask to be blocked while 
the handler is running
it prints a message with it's own PID and waits for the client to send a signal.
*/
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
