#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ASM.h"
#include "CPU.h"
#include "files.h"

const int TMP_SIZE = 128;

int ASM_assembly_code(const char* code_name, const char* assembled_code_name, int* addresses)
{
	char* code = readfile(code_name);
	int amount_of_commands = amount_of_strings(code);
	char** commands = make_array_of_strings_beginnings(code);
	
	if (!strcmp(commands[0], SIGN))
	{
		printf("Invalid signature.\n");
		return -1;
	}
	
	FILE* fo = fopen(assembled_code_name, "w");
	
	int addr = 0;
	replace_in_array(code, '\n', '\0');
	for (int i = 1; i < amount_of_commands; i++)
	{
		replace_in_array(commands[i], ' ', '\n');
		char** tmp = make_array_of_strings_beginnings_with_sep(commands[i], '\n');
		int len = amount_of_char(commands[i], '\n') + 1;
		replace_in_array(commands[i], '\n', '\0');
		
		for (int j = 0; j < len; j++)
		{
			int cmd = word_to_command(tmp[j]);
			if (cmd != -1)
			{
				if (cmd == CMD_CALL || cmd == CMD_JMP || cmd == CMD_JA || cmd == CMD_JAE || cmd == CMD_JB || cmd == CMD_JBE || cmd == CMD_JE || cmd == CMD_JNE || cmd == CMD_JAD || cmd == CMD_JAED || cmd == CMD_JBD || cmd == CMD_JBED || cmd == CMD_JED || cmd == CMD_JNED)
				{
					int ilabel = 0;
					if (tmp[1][0] == ':')
					{
						sscanf(&tmp[1][1], "%d", &ilabel);
						fprintf(fo, "%d %d ", cmd, addresses[ilabel]); addr+=2; j++;
					}
					else
					{
						sscanf(tmp[1], "%d", &ilabel);
						fprintf(fo, "%d %d ", cmd, ilabel); addr+=2; j++;
					}
				}
				else
				{
					fprintf(fo, "%d ", cmd); addr++;
				}
			}
			else
			{
				if (tmp[j][0] != ':')
				{
					fprintf(fo, "%s ", tmp[j]); addr++;
				}
				else
				{
					int ilabel = 0;
					sscanf(&tmp[j][1], "%d", &ilabel);
					addresses[ilabel] = addr;
				}
			}
		}
	}
	fclose(fo);
	return 0;
}

int word_to_command(char* word)
{
	if (!(strcmp(word, "push"))) return CMD_PUSH;
	if (!(strcmp(word, "pushr"))) return CMD_PUSHR;
	if (!(strcmp(word, "pop"))) return CMD_POP;
	if (!(strcmp(word, "popr"))) return CMD_POPR;
	if (!(strcmp(word, "mul"))) return CMD_MUL;
	if (!(strcmp(word, "add"))) return CMD_ADD;
	if (!(strcmp(word, "ret"))) return CMD_RET;
	if (!(strcmp(word, "jmp"))) return CMD_JMP;
	if (!(strcmp(word, "je"))) return CMD_JE;
	if (!(strcmp(word, "jne"))) return CMD_JNE;
	if (!(strcmp(word, "ja"))) return CMD_JA;
	if (!(strcmp(word, "jae"))) return CMD_JAE;
	if (!(strcmp(word, "jb"))) return CMD_JB;
	if (!(strcmp(word, "jbe"))) return CMD_JBE;
	if (!(strcmp(word, "end"))) return CMD_END;
	if (!(strcmp(word, "call"))) return CMD_CALL;
	if (!(strcmp(word, "div"))) return CMD_DIV;
	if (!(strcmp(word, "sqrt"))) return CMD_SQRT;
	if (!(strcmp(word, "jed"))) return CMD_JED;
	if (!(strcmp(word, "jned"))) return CMD_JNED;
	if (!(strcmp(word, "jad"))) return CMD_JAD;
	if (!(strcmp(word, "jaed"))) return CMD_JAED;
	if (!(strcmp(word, "jbd"))) return CMD_JBD;
	if (!(strcmp(word, "jbed"))) return CMD_JBED;
	if (!(strcmp(word, "dub"))) return CMD_DUB;
	if (!(strcmp(word, "meow"))) return CMD_MEOW;
	return -1;
}
