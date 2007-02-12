#include <stdio.h>
#include <string.h>

typedef struct {
	unsigned short NextOffset;
	unsigned short Unknown2;
	unsigned short X1;
	unsigned short Y1;
	unsigned short X2;
	unsigned short Y2;
	unsigned short Width;
	unsigned short Height;
	unsigned short Unknown9;
	unsigned short Unknown10;
	unsigned short TextOffset;
	unsigned short Unknown12;
	unsigned int Flags; // 28
	unsigned short Unknown15;
	unsigned short Unknown16;
	short UnknownIndex;
	unsigned short Type;
	unsigned short Unknown19;
	unsigned short Unknown20;
	unsigned short Unknown21;
	unsigned short Unknown22;
	unsigned short Unknown23;
	unsigned short Unknown24;
	unsigned short Unknown25;
	unsigned short Unknown26;
	unsigned short Unknown27;
	unsigned short DialogWidth_MouseX1;
	unsigned short DialogWidth_MouseY1;
	unsigned short MouseX2;
	unsigned short MouseY2;
	unsigned short Unknown32;
	unsigned short Unknown33; // 66
	unsigned short ChildOffset;
	unsigned short Unknown35;
	unsigned short TextX1;
	unsigned short TextY1;
	unsigned short TextX2;
	unsigned short TextY2;
	unsigned short Unknown40;
	unsigned short Unknown41;
	unsigned short Unknown42;
	unsigned short Unknown43; // 86
} Level12;

typedef struct {
	unsigned short NextOffset;
	unsigned short Unknown2;
	unsigned short Flags;
	unsigned short Unknown4;
	unsigned short Unknown5;
	unsigned short TextOffset;
	unsigned short Unknown7;
	unsigned short Unknown8;
	unsigned short Unknown9;
	unsigned short X;
	unsigned short Y;
	unsigned short Unknown12;
	unsigned short Unknown13;
	unsigned short Unknown14;
	unsigned short Unknown15;
} Level3;


char buf[64 * 1024];


void DoLevel3(Level3 *l3)
{
	printf("-------------- Level 3 ------------------\n");
}

void print(char *s)
{
	while (*s) {
		if (*s >= 0x20) {
			fputc(*s, stdout);
		} else {
			printf("<%d>", *s);
		}
		++s;
	}
	fputc('\n', stdout);
}

void DoLevel12(Level12 *l, int level)
{
	char tmp[4096];

	printf("---------------Level %d ------------------\n", level);
	printf("X1,Y1 = %d,%d\n", l->X1, l->Y1);
	printf("X2,Y2 = %d,%d\n", l->X2, l->Y2);
	printf("Width,Height = %d,%d\n", l->Width, l->Height);
//	printf("l->ChildOffset: %X\n", l->ChildOffset);
//	printf("l->NextOffset: %X\n", l->NextOffset);
	if (l->Flags) {
		printf("Flags = %X\n", l->Flags);
	}
	if (l->TextOffset) {
		sprintf(tmp, "Text: %s", buf + l->TextOffset);
		print(tmp);
	}

	if (l->ChildOffset) {
		if (level == 1) {
			DoLevel12((Level12*)(buf + l->ChildOffset), level + 1);
		} else {
			DoLevel3((Level3*)(buf + l->ChildOffset));
		}
	}
	if (l->NextOffset) {
		DoLevel12((Level12*)(buf + l->NextOffset), level);
	}
}


int main(int argc, char *argv[])
{
	FILE *fd = fopen(argv[1], "rb");

	char *ptr = buf;


	fread(buf, 1, sizeof(buf), fd);
	fclose(fd);

	DoLevel12((Level12 *)buf, 1);

	return 0;
}
