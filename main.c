/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahlsweh <lahlsweh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 10:13:05 by lahlsweh          #+#    #+#             */
/*   Updated: 2025/04/10 17:06:35 by lahlsweh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	display(void);
void	direct_leak(void);
void	write_stack_buffer_overflow(void);
void	read_stack_buffer_overflow(void);
void	segfault(void);
void	write_heap_use_after_free(void);
void	read_heap_use_after_free(void);
void	double_free(void);
void	stack_overflow(void);
void	conditional_jump(void);

int	main(int argc, char **argv)
{
	display();
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
		else if (argv[1][0] == '9')
			conditional_jump();
	}
	return (0);
}

void	display(void)
{
	printf("\nAvailable modes :\n");
	printf("1 : Test direct leak\n");
	printf("2 : Test WRITE stack buffer overflow\n");
	printf("3 : Test  READ stack buffer overflow\n");
	printf("4 : Test SEGFAULT\n");
	printf("5 : Test WRITE heap use after free\n");
	printf("6 : Test  READ heap use after free\n");
	printf("7 : Test double free\n");
	printf("8 : Test stack overflow\n");
	printf("9 : Test conditional jump\n\n");
	return ;
}

void	direct_leak(void)
{
	char	*str;

	printf("test 1: direct_leak() ...\n");
	str = (char *)malloc(10 * sizeof(char));
	return ;
}

void	write_stack_buffer_overflow(void)
{
	char	str[10];
	int		i;

	printf("test 2 : write_stack_buffer_overflow() ...\n");
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

	printf("test 3 : read_stack_buffer_overflow() ...\n");
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
	int	*ptr;

	printf("test 4 : segfault() ...\n");
	ptr = NULL;
	*ptr = 20;
	return ;
}

void	write_heap_use_after_free(void)
{
	char	*str;

	printf("test 5 : write_heap_use_after_free() ...\n");
	str = (char *)malloc(10 * sizeof(char));
	str[5] = 'a';
	free(str);
	str[5] = 'z';
	return ;
}

void	read_heap_use_after_free(void)
{
	char	*str;

	printf("test 6 : read_heap_use_after_free() ...\n");
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

	printf("test 7: double_free() ...\n");
	str = (char *)malloc(10 * sizeof(char));
	free(str);
	free(str);
	return ;
}

void	stack_overflow(void)
{
	int	breaker;

	printf("test 8 : stack_overflow() ...\n");
	breaker = 5;
	write(1, "1", 1);
	while (breaker == 5)
		stack_overflow();
	return ;
}

void	conditional_jump(void)
{
	char	str[10];
	int		i;

	printf("test 9 : conditional_jump() ...\n");
	str[5] = 'c';
	i = 0;
	while (str[i] != 'c')
		i++;
	return ;
}
