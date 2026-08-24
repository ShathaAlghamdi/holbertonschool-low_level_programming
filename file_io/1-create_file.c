#include "main.h"

/**
 * create_file - creates a file
 * @filename: name of the file
 * @text_content: content to write
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd;
	ssize_t written;
	size_t length = 0;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	if (text_content != NULL)
	{
		while (text_content[length] != '\0')
			length++;

		written = write(fd, text_content, length);

		if (written == -1 || written != (ssize_t)length)
		{
			close(fd);
			return (-1);
		}
	}

	close(fd);

	return (1);
}
