#include "prototypes.h"

/**
 * num_len - finds the length of a digit
 * @num: number to get length of
 * Return: digit length
 */
int num_len(int num)
{
	unsigned int number1;
	int length = 1;

	if (num < 0)
	{
		length = length + 1;
		number1 = num * -1;
	}
	else
	{
		number1 = num;
	}
	while (number1 > 9)
	{
		length = length + 1;
		number1 /= 10;
	}

	return (length);
}

/**
 * _itoa - convert number into string
 * @num: number to turn into string
 * Return: Always 0
 */
char *_itoa(int num)
{
	char *buffer;
	int length = num_len(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return (NULL);

	buffer[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length = length - 1;
	do {
		buffer[length] = (num1 % 10) + '0';
		num1 /= 10;
		length = length - 1;
	} while (num1 > 0);

	return (buffer);
}


/**
 * create_error - creates custom error messages
 * @args: argument vector
 * @err: error code
 * Return: error code
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env(args);
		break;
	case 1:
		error = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = error_2_syntax(args);
		else
			error = error_2_cd(args);
		break;
	case 126:
		error = error_126(args);
		break;
	case 127:
		error = error_127(args);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
