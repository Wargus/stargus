#include <stdio.h>
#include <string.h>

void print(char *str)
{
	char buf[4096];
	char *b = buf;
	static int count = 1;

	memset(buf, 0, sizeof(buf));

	while (*str) {
		if (*str < 20) {
			strcpy(b, "~color");
			b += 6;
			*b++ = *str++ + '0';
			*b++ = '~';
		} else if (*str == '"') {
			*b++ = '\\';
			*b++ = *str++;
		} else {
			*b++ = *str++;
		}
	}
	printf("%d %s\n", count++, buf);
}

int main(int argc, char *argv[])
{
	FILE *fd = fopen(argv[1], "rb");
	char *buf = (char *)malloc(1024*1024);
	char *ptr = buf;
	int *offset;
	int i;
	int num;

	fread(buf, 1, 1024*1024, fd);
	fclose(fd);

	num = *(short *)buf;
	offset = (int *)malloc(num * sizeof(int));

	for (i = 0; i < num; ++i) {
		offset[i] = ((short *)buf)[i + 1];
	}

	for (i = 0; i < num; ++i) {
		print(buf + offset[i]);
	}

	free(buf);
	free(offset);

	return 0;
}
