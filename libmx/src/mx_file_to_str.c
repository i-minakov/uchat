#include "libmx.h"

char *mx_file_to_str(const char *file) {
	if (!file) return NULL;
	char buff[1];
	long arr = 0;
	int open_file = open(file, O_RDONLY);
	if (open_file < 0) return NULL;
	int read_file = read(open_file, buff, sizeof(buff));
	if (read_file <= 0) return NULL;
	while (read_file > 0) {
		arr++;
		read_file = read(open_file, buff, sizeof(buff));
	}
	close(open_file);

	char *p = mx_strnew(arr);
	
	int i = 0;
	open_file = open(file, O_RDONLY);
	read_file = read(open_file, buff, sizeof(buff));
	while (read_file > 0) {
		p[i] = buff[0];
		read_file = read(open_file, buff, sizeof(buff));
		i++;
	}
	close(open_file);
	return p;
}
