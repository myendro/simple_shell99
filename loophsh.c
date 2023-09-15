#include "shell.h"

/**
 * loophsh - Main loop for the simple shell
 * @environ: The environment variable
 *
 * Return: 0 on success, -1 on failure
 */
int loophsh(char **environ)
{
	info_t info = INFO_INIT; /* Initialize the info_t structure */

	info.environ = environ; /* Set the environment variable */

	/* Set up the signal handler for Ctrl+C (SIGINT) */
	signal(SIGINT, sigintHandler);

	/* Main shell loop */
	while (1)
	{
		/* Display shell prompt */
		if (isatty(STDIN_FILENO)) /* Check if the shell is interactive */
			_puts("$ ");

		/* Read input from the user */
		if (get_input(&info) == -1)
			break; /* Exit the loop on error or EOF */

		/* Process the input */
		if (hsh(&info, environ) == -1)
			break; /* Exit the loop on error */
	}

	/* Free allocated memory and resources */
	free_info(&info, 1);

	return (0); /* Exit the shell with success status */
}
