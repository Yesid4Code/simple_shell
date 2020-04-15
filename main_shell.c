#include "headershell.h"

/**
 * main - Read, Search and execute the input
 * @argc: count arguments
 * @argv: array of arguments
 *
 * Return: Always 0 success
 */
int main(int argc, char *argv[])
{
	char *line = NULL, **input; /*command typing by user */
	size_t len = 0;
	ssize_t read; /*chars read by getline() */

	(void)argc, (void)argv;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9); /*Display prompt */

		/* ||READING PHASE|| */
		read = getline(&line, &len, stdin);
		if (read == EOF) /* If getline could not read the line*/
		{
			write(STDOUT_FILENO, "\n", 1);
			continue; /* Return to display prompt*/
		}
		/* Receive the command type by the user */
		input = get_input(line);
		if (input == NULL)
		{
			free(input);
			continue;
		}
		/* ||SEARCHING PATH PHASE|| */
		if (**input != '/')
		{
			input[0] = _strdup(pathtoexecute(input));
			if (!input[0])
			{
				free(input), free(line);
				continue;
			}
			execute(input); /* ||EXECUTE PHASE|| */
		}
		else
			execute(input);
	}
	free(input), free(line);
	return (0);
}
