#include "lexer.h"
#include "minishell.h"
#include "utils.h"

void	process_line(char *line/*Takes the shell struct*/)
{
	t_token	*tokens;

	lexer(line, &tokens);
	//! For testing purposes
	//? t_token	*current;
	//? current = tokens;
	//? int idx = 0;
	//? while (current) {
	//? 	printf("token[%d]: %s\t%u\n", idx, current->value, current->type);
	//? 	idx++;
	//? 	current = current->next;
	//? }
	//? free_tokens(tokens);
	// TODO: parser
}

void	interactive_mode(/*Takes the shell struct*/)
{

}

void	script_mode(int fd/*Takes the shell struct*/)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(line);
		free(line);
	}
}

int main(int ac, char **av)
{
	// init & process the envs

	if (isatty(STDIN_FILENO))
		interactive_mode(/*Takes the shell struct*/);
	else
		script_mode(STDIN_FILENO/*Takes the shell struct*/);
	return (0);
}

