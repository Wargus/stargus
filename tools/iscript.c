//
// iscript.bin parser
//
// Copyright 2007 Jimmy Salmon
//

#include <stdio.h>
#include <stdlib.h>


unsigned char *ReadFile(const char *fileName)
{
	FILE *fd;
	long fileSize;
	unsigned char *data = NULL;

	// Open
	fd = fopen(fileName, "rb");
	if (!fd) {
		perror("Could not open file");
		goto Cleanup;
	}

	// Get file size
	if (fseek(fd, 0, SEEK_END)) {
		fprintf(stderr, "fseek failed\n");
		goto Cleanup;
	}
	fileSize = ftell(fd);
	if (fseek(fd, 0, SEEK_SET)) {
		fprintf(stderr, "fseek failed\n");
		goto Cleanup;
	}

	// Read file
	data = (unsigned char *)malloc(fileSize);
	if (!data) {
		fprintf(stderr, "Out of memory\n");
		goto Cleanup;
	}
	fread(data, fileSize, 1, fd);

Cleanup:
	if (fd) {
		fclose(fd);
	}

	return data;
}


unsigned char ReadByte(const unsigned char **p)
{
	unsigned char c = *(*p);
	(*p) += 1;
	return c;
}

#if  defined(__i386__) || defined(__ia64__) || defined(WIN32) || \
   (defined(__alpha__) || defined(__alpha)) || \
    defined(__arm__) || \
   (defined(__mips__) && defined(__MIPSEL__)) || \
    defined(__SYMBIAN32__) || \
    defined(__x86_64__) || \
    defined(__LITTLE_ENDIAN__)
unsigned short ReadShort(const unsigned char **p)
{
	unsigned short s = *(const unsigned short *)(*p);
	(*p) += 2;
	return s;
}
#else
unsigned short ReadShort(const unsigned char **p)
{
	unsigned short s = *(const unsigned short *)(*p);
	s = (s << 8) | (s >> 8);
	(*p) += 2;
	return s;
}
#endif

void DoDecode(const unsigned char *data, unsigned short offset)
{
	const unsigned char *p;
	unsigned char c1, c2;
	unsigned short s1, s2;
	unsigned char opcode;
	int stop = 0;

	p = data + offset;
	while (!stop) {
		printf("\n%04hX ", (unsigned short)(p - data));
		opcode = ReadByte(&p);
		switch (opcode)
		{
			case 0x00:
				s1 = ReadShort(&p);
				printf("play frame from set: %hu", s1);
				break;

			case 0x03:
				c1 = ReadByte(&p);
				printf("shift position down: %u", (unsigned)c1);
				break;

			case 0x05:
				c1 = ReadByte(&p);
				printf("wait: %u", (unsigned)c1);
				break;

			case 0x06:
				c1 = ReadByte(&p);
				c2 = ReadByte(&p);
				printf("wait random time: %u, %u", (unsigned)c1, (unsigned)c2);
				break;

			case 0x07:
				s1 = ReadShort(&p);
				printf("goto: %04hX", s1);
				break;

			case 0x08:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("place active overlay: %hu, %hu", s1, s2);
				break;

			case 0x09:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("place active underlay: %hu, %hu", s1, s2);
				break;

			case 0x0D:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("0x0D unknown: %hu, %hu", s1, s2);
				break;

			case 0x10:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("place underlay under this anim level: %hu, %hu", s1, s2);
				break;

			case 0x11:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("place underlay under everything: %hu, %hu", s1, s2);
				break;

			case 0x15:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("0x15 unknown: %hu, %hu", s1, s2);
				break;

			case 0x16:
				printf("end animation and remove graphic");
				break;

			case 0x18:
				s1 = ReadShort(&p);
				printf("play sound: %hu", s1);
				break;

			case 0x19:
				c1 = ReadByte(&p);
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("random play sound: %u, %hu, %hu", (unsigned)c1, s1, s2);
				break;

			case 0x1A:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("random play sound: %hu, %hu", s1, s2);
				break;

			case 0x1C:
				s1 = ReadShort(&p);
				s2 = ReadShort(&p);
				printf("melee attack sound: %hu, %hu", s1, s2);
				break;

			case 0x1D:
				printf("shadow opcode");
				break;

			case 0x1E:
				c1 = ReadByte(&p);
				s1 = ReadShort(&p);
				printf("random goto offset: %u, %04hX", (unsigned)c1, s1);
				break;

			case 0x1F:
				c1 = ReadByte(&p);
				printf("turn counterclockwise: %u", (unsigned)c1);
				break;

			case 0x20:
				c1 = ReadByte(&p);
				printf("turn clockwise: %u", (unsigned)c1);
				break;

			case 0x21:
				printf("turn 1 frame clockwise");
				break;

			case 0x22:
				c1 = ReadByte(&p);
				printf("turn graphic in random direction: %u", (unsigned)c1);
				break;

			case 0x24:
				c1 = ReadByte(&p);
				printf("0x24 unknown: %u", (unsigned)c1);
				break;

			case 0x25:
				c1 = ReadByte(&p);
				printf("attack: %u", (unsigned)c1);
				break;

			case 0x27:
				printf("cast spell");
				break;

			case 0x29:
				c1 = ReadByte(&p);
				printf("move %u", (unsigned)c1);
				break;

			case 0x2A:
				printf("looping attack");
				break;

			case 0x2E:
				printf("unbreakable section begin");
				break;

			case 0x2F:
				printf("unbreakable section end");
				break;

			case 0x30:
				printf("ignore the rest?");
				stop = 1;
				break;

			case 0x31:
				c1 = ReadByte(&p);
				printf("projectile attack from angle: %u", (unsigned)c1);
				break;

			case 0x34:
				c1 = ReadByte(&p);
				printf("play specific frame: %u", (unsigned)c1);
				break;

			case 0x38:
				c1 = ReadByte(&p);
				printf("unknown 0x38 extractor?: %u", (unsigned)c1);
				break;

			case 0x3F:
				s1 = ReadShort(&p);
				printf("0x3F goto?: %04hX", s1);
				break;

			default:
				printf("unsupported opcode: %u", (unsigned)opcode);
				stop = 1;
				break;
		}
	}
	printf("\n");
}


int CheckForHeader(const unsigned char *p)
{
	// Check for 'SCPE'
	if (p[0] == 'S' && p[1] == 'C' && p[2] == 'P' && p[3] == 'E') {
		return 1;
	}
	return 0;
}

void DecodeAnimation(const unsigned char *data, unsigned short offset)
{
	const unsigned char *p;

	p = data + offset;

	if (CheckForHeader(p)) {
		int i;
		unsigned short number;

		p += 4;
		number = ReadShort(&p);
		printf("number: %hu\n", number);

		if (number < 16) {
			number = 16;
		}
		for (i = 0; i < number; ++i) {
			printf("%04hX\n", ReadShort(&p));
		}
	} else {
		DoDecode(data, offset);
	}
}


int main(int argc, char *argv[])
{
	unsigned char *data;
	unsigned short offset;

	if (argc != 2) {
		fprintf(stderr, "Usage: iscript hexoffset\n");
		return -1;
	}

	offset = (unsigned short)strtoul(argv[1], NULL, 16);

	data = ReadFile("iscript.bin");
	if (!data) {
		return -1;
	}

	DecodeAnimation(data, offset);

	free(data);

	return 0;
}

