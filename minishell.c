/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 00:00:00 by reda              #+#    #+#             */
/*   Updated: 2025/09/16 00:00:00 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"

/*
 * Very basic minishell loop
 * 
 * This is the simplest possible shell:
 * 1. Display prompt
 * 2. Read user input with readline
 * 3. Handle basic commands (exit)
 * 4. Echo back what user typed
 * 5. Repeat
 */

int main(int ac, char **av)
{
	char *input;
	char **args;
	int i;
	
	(void)ac;
	(void)av;
	
	printf("Welcome !\n");	
	while (1)
	{
		input = readline("minishell$ --->>  ");
		if (input == NULL)
			return 0;
		
		/* Skip empty input */
		if (strlen(input) == 0)
		{
			free(input);
			continue;
		}
		
		add_history(input);
		
		/* Split input into arguments */
		args = ft_split(input, ' ');
		if (args && args[0])
		{
			/* Handle exit command */
			if (strcmp(args[0], "exit") == 0)
			{
				printf("Goodbye!\n");
				free_split_result(args);
				free(input);
				break;
			}
			
			/* Print what we parsed */
			printf("Command: '%s'\n", args[0]);
			printf("Arguments:\n");
			i = 0;
			while (args[i])
			{
				printf("  [%d]: '%s'\n", i, args[i]);
				i++;
			}
		}
		
		free_split_result(args);
		free(input);
	}
	return (0);
}
