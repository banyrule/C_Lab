#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
// #include <unistd.h>	// getopt() ����-�� ������
#include <string.h>		// ������� �������� ����� �������

/* ��������� �� ������ n */
int modular_increment(int *idx, int n)
{
	*idx = (*idx + 1) % n;
}

int main(int argc, char *argv[])
{
	char buff[1024];										// ������ ����� ������� �� ���������
	const size_t buff_size = sizeof(buff) / sizeof(*buff);	// ��  ��� �� �����
	size_t cur_size = 0;									// ������� ������ ���������
	
	char *key = (argc > 1) ? (argv[1]) : ("some semi-secret key");	// ����. ���� - ������ �������� cmd
	unsigned key_len = strlen(key);	
	unsigned idx = 0;	// ��������� �� ������ �����, � ������� ����� XOR'���

	FILE *fin = stdin;		// �� ����������� ���� ����� stdin
	FILE *fout = stdout;	// �� ����������� ����� ����� stdout

	//
	// �������� ��� �����: ����� ������������ getopt() ��� Win?
	//

	if (argc > 3)	// ������ ���� ���� -i ��� -o + ��� ��������
	{
		if (!strcmp(argv[2], "-i"))
			fin = fopen(argv[3], "r");
		else if (!strcmp(argv[2], "-o"))
			fout = fopen(argv[3], "w");
	}

	if (argc > 4)	// ������ e�� ���� ���� -i ��� -o + ��� ��������
	{
		if (!strcmp(argv[4], "-i"))
			fin = fopen(argv[5], "r");
		else if (!strcmp(argv[4], "-o"))
			fout = fopen(argv[5], "w");
	}
	
	_setmode(_fileno(fin), _O_BINARY);
	_setmode(_fileno(fout), _O_BINARY);

	while ((cur_size = fread(buff, 1, buff_size, fin)) > 0)
	{
		for (int i = 0; i < cur_size; ++i)
		{ 
			buff[i] ^= key[idx];
			modular_increment(&idx, key_len);
		}

		fwrite(buff, cur_size, 1, fout);
	}

	return 0;
}