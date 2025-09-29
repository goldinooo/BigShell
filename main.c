#include "minishell.h"


void	process_line(char *line/*Takes the shell struct*/)
{
	// TODO:
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
		// TODO: process line
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
