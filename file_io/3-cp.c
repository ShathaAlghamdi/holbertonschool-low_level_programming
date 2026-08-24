#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * close_file - closes a file descriptor
 * @fd: file descriptor
 */
void close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * copy_file - copies data from one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source file name
 * @file_to: destination file name
 */
void copy_file(int fd_from, int fd_to, char *file_from, char *file_to)
{
	char buffer[1024];
	ssize_t rd, wr;

	rd = read(fd_from, buffer, 1024);
	while (rd > 0)
	{
		wr = write(fd_to, buffer, rd);
		if (wr == -1 || wr != rd)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", file_to);
			close_file(fd_from);
			close_file(fd_to);
			exit(99);
		}
		rd = read(fd_from, buffer, 1024);
	}

	if (rd == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", file_from);
		close_file(fd_from);
		close_file(fd_to);
		exit(98);
	}
}

/**
 * main - copies the content of one file to another
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", argv[2]);
		close_file(fd_from);
		exit(99);
	}

	copy_file(fd_from, fd_to, argv[1], argv[2]);

	close_file(fd_from);
	close_file(fd_to);

	return (0);
}
