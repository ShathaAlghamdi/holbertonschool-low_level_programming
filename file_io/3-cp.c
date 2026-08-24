#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * close_fd - closes a file descriptor
 * @fd: file descriptor
 *
 * Return: void
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copies the content of one file to another
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from;
	int fd_to;
	ssize_t bytes_read;
	ssize_t bytes_written;
	char buffer[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO,
			"Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	fd_to = open(argv[2],
		O_WRONLY | O_CREAT | O_TRUNC, 0664);

	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", argv[2]);
		close_fd(fd_from);
		exit(99);
	}

	bytes_read = read(fd_from, buffer, 1024);

	while (bytes_read > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);

		if (bytes_written == -1 ||
		    bytes_written != bytes_read)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n",
				argv[2]);

			close_fd(fd_from);
			close_fd(fd_to);
			exit(99);
		}

		bytes_read = read(fd_from, buffer, 1024);
	}

	if (bytes_read == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n",
			argv[1]);

		close_fd(fd_from);
		close_fd(fd_to);
		exit(98);
	}

	close_fd(fd_from);
	close_fd(fd_to);

	return (0);
}
