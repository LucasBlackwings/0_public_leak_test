/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:13:05 by lahlsweh          #+#    #+#             */
/*   Updated: 2025/03/14 11:19:38 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	direct_leak(void);
void	write_stack_buffer_overflow(void);
void	read_stack_buffer_overflow(void);
void	segfault(void);
void	write_heap_use_after_free(void);
void	read_heap_use_after_free(void);
void	double_free(void);
void	stack_overflow(void);
void	newtest(void);

int	main(int argc, char **argv)
{
	printf("\nAvailable modes :\n\
1 : Rest direct leak\n\
2 : Test WRITE stack buffer overflow\n\
3 : Test  READ stack buffer overflow\n\
4 : Test SEGFAULT\n\
5 : Test WRITE heap use after free\n\
6 : Test  READ heap use after free\n\
7 : Test double free\n\
8 : Test stack overflow\n\n");
	if (argc == 2)
	{
		if (argv[1][0] == '1')
			direct_leak();
		else if (argv[1][0] == '2')
			write_stack_buffer_overflow();
		else if (argv[1][0] == '3')
			read_stack_buffer_overflow();
		else if (argv[1][0] == '4')
			segfault();
		else if (argv[1][0] == '5')
			write_heap_use_after_free();
		else if (argv[1][0] == '6')
			read_heap_use_after_free();
		else if (argv[1][0] == '7')
			double_free();
		else if (argv[1][0] == '8')
			stack_overflow();
	}
	return (0);
}

void	direct_leak(void)
{
	char *str;
	
	str = (char *)malloc(10 * sizeof(char));
	return ;
}

void	write_stack_buffer_overflow(void)
{
	char	str[10];
	int		i;

	i = 0;
	while (i < 15)
	{
		str[i] = '0';
		i++;
	}
	return ;
}

void	read_stack_buffer_overflow(void)
{
	char	str[10];
	int		i;

	i = 10;
	while (i >= -5)
	{
		write(1, &str[i], 1);
		i--;
	}
	return ;
}

void	segfault(void)
{
	int	*ptr = NULL;

	*ptr = 20;
	return ;
}

void	write_heap_use_after_free(void)
{
	char	*str;

	str = (char *)malloc(10 * sizeof(char));
	str[5] = 'a';
	free(str);
	str[5] = 'z';
	return ;
}

void	read_heap_use_after_free(void)
{
	char	*str;

	str = (char *)malloc(10 * sizeof(char));
	str[5] = 'a';
	printf("%c", str[5]);
	free(str);
	printf("%c", str[5]);
	return ;
}

void	double_free(void)
{
	char	*str;

	str = (char *)malloc(10 * sizeof(char));
	free(str);
	free(str);
	return ;
}

void	stack_overflow(void)
{
	int	breaker;

	breaker = 5;
	write(1, "1", 1);
	while (breaker == 5)
	{
		stack_overflow();
	}
	return ;
}
