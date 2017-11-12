#include "CPU.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "files.h"
#include <math.h>

const int group = 771;
const int STACK_SIZE = 1024;
const int COMMANDS_SIZE = 1024;

CPU* CPU_Construct()
{
	CPU* cpu = (CPU* )calloc(1, sizeof(CPU)); assert(cpu);
	assert(cpu);
	
	cpu->s = stack_Construct(STACK_SIZE); assert(cpu->s);
	cpu->call_stack = stack_Construct(STACK_SIZE); assert(cpu->call_stack);
	cpu->commands = (CMD_t* )calloc(COMMANDS_SIZE, sizeof(CMD_t)); assert(cpu->commands);
	cpu->addresses = stack_Construct(STACK_SIZE); assert(cpu->addresses);
	
	for (int i = 0; i < COMMANDS_SIZE; i++)
	{
		cpu->commands[i] = -1;
	}
	cpu->amount_of_commands = 0;
	cpu->current_command = 0;
	
	cpu->active = 0;
	
	for (int i = 0; i < CPU_REGISTERS_AMOUNT; i++)
	{
		cpu->registers[i] = POISON;
	}
	
	return cpu;
}

void CPU_Destroy(CPU* cpu)
{
	assert(cpu);
	
	stack_Destroy(cpu->addresses);
	free(cpu->commands);
	stack_Destroy(cpu->call_stack);
	stack_Destroy(cpu->s);
	free(cpu);
}

int CPU_load_to_the_commands_from_file(CPU* cpu, char* assembled_file_name)
{
	assert(cpu);
	//Проверить наличие файла
	FILE* code = 0;
	code = fopen(assembled_file_name, "r");
	assert(code);
	
	int i = 0;
	while (!feof(code))
	{
		fscanf(code, "%d", &cpu->commands[i]);
		i++;
	}
	cpu->amount_of_commands = i-1;
	fclose(code);
	return 0;
}

int CPU_Do(CPU* cpu)
{
	assert(cpu);
	cpu->active = 1;
	while (cpu->active)
	{
		//printf("command: %d\n", cpu->commands[cpu->current_command]);
		switch (cpu->commands[cpu->current_command])
		{
				case CMD_PUSH:
				{
					CPU_push(cpu);
					break;
				}
				case CMD_POP:
				{
					CPU_pop(cpu);
					break;
				}
				case CMD_MUL:
				{
					CPU_mul(cpu);
					break;
				}
				case CMD_ADD:
				{
					CPU_add(cpu);
					break;
				}
				case CMD_RET:
				{
					CPU_ret(cpu);
					break;
				}
				case CMD_JMP:
				{
					CPU_jmp(cpu);
					break;
				}
				case CMD_JE:
				{
					CPU_je(cpu);
					break;
				}
				case CMD_JNE:
				{
					CPU_jne(cpu);
					break;
				}
				case CMD_JA: 
				{
					CPU_ja(cpu);
					break;
				}
				case CMD_JAE:
				{
					CPU_jae(cpu);
					break;
				}
				case CMD_JB:
				{
					CPU_jb(cpu);
					break;
				}
				case CMD_JBE:
				{
					CPU_jbe(cpu);
					break;
				}
				case CMD_END:
				{
					CPU_end(cpu);
					break;
				}
				case CMD_CALL:
				{
					CPU_call(cpu);
					break;
				}
				case CMD_PUSHR:
				{
					CPU_pushr(cpu);
					break;
				}
				case CMD_POPR:
				{
					CPU_popr(cpu);
					break;
				}
				case CMD_SQRT:
				{
					CPU_sqrt(cpu);
					break;
				}
				case CMD_DIV:
				{
					CPU_div(cpu);
					break;
				}
				case CMD_JED:
				{
					CPU_jed(cpu);
					break;
				}
				case CMD_JNED:
				{
					CPU_jned(cpu);
					break;
				}
				case CMD_JAD:
				{
					CPU_jad(cpu);
					break;
				}
				case CMD_JAED:
				{
					CPU_jaed(cpu);
					break;
				}
				case CMD_JBD:
				{
					CPU_jbd(cpu);
					break;
				}
				case CMD_JBED:
				{
					CPU_jbed(cpu);
					break;
				}
				case CMD_DUB:
				{
					CPU_dub(cpu);
					break;
				}
				case CMD_MEOW:
				{
					CPU_meow(cpu);
					break;
				}
			default:
			{
				printf("Invalid code of the task: %d, address: %d\n", cpu->commands[cpu->current_command], cpu->current_command);
				return CPU_INVALID_CODE_OF_THE_TASK;
			}
		}
		cpu->current_command++;
	}
	return 0;
}

int CPU_push(CPU* cpu)
{
	assert(cpu);
	cpu->current_command++;
	stack_Push(cpu->s, cpu->commands[cpu->current_command]);
	return CPU_Check(cpu);
}

int CPU_pushr(CPU* cpu)
{
	assert(cpu);
	cpu->current_command++;
	cpu->registers[cpu->commands[cpu->current_command]] = stack_Pop(cpu->s);
	return CPU_Check(cpu);
}

int CPU_pop(CPU* cpu)
{
	assert(cpu);
	stack_Pop(cpu->s);
	
	
	return CPU_Check(cpu);
}

int CPU_mul(CPU* cpu)
{
	assert(cpu);
	stack_elem res = stack_Pop(cpu->s)*stack_Pop(cpu->s);
	stack_Push(cpu->s, res);
	
	return CPU_Check(cpu);
}

int CPU_add(CPU* cpu)
{
	assert(cpu);
	stack_elem res = stack_Pop(cpu->s) + stack_Pop(cpu->s);
	stack_Push(cpu->s, res);
	return CPU_Check(cpu);
}

int CPU_jmp(CPU* cpu)
{
	assert(cpu);
	cpu->current_command++;
	cpu->current_command = cpu->commands[cpu->current_command] - 1;
	
	return CPU_Check(cpu);
}

int CPU_ret(CPU* cpu)
{
	assert(cpu);
	cpu->current_command = stack_Pop(cpu->call_stack);
	return CPU_Check(cpu);
}

int CPU_je(CPU* cpu)
{
	assert(cpu);
	if (stack_Get(cpu->s, 1) == stack_Get(cpu->s, 2))
		CPU_jmp(cpu);
	else
		cpu->current_command++;
	return CPU_Check(cpu);
}

int CPU_jne(CPU* cpu)
{
	assert(cpu);
	if (stack_Get(cpu->s, 1) != stack_Get(cpu->s, 2))
		CPU_jmp(cpu);
	else
		cpu->current_command++;
	return CPU_Check(cpu);
}

int CPU_ja(CPU* cpu)
{
	assert(cpu);
	if (stack_Get(cpu->s, 1) >= stack_Get(cpu->s, 2))
		CPU_jmp(cpu);
	else
		cpu->current_command++;
	return CPU_Check(cpu);
}

int CPU_jae(CPU* cpu)
{
	assert(cpu);
	if (stack_Get(cpu->s, 1) > stack_Get(cpu->s, 2))
		CPU_jmp(cpu);
	else
		cpu->current_command++;
	return CPU_Check(cpu);
}

int CPU_jb(CPU* cpu)
{
	assert(cpu);
	if (stack_Get(cpu->s, 1) <= stack_Get(cpu->s, 2))
		CPU_jmp(cpu);
	else
		cpu->current_command++;
	return CPU_Check(cpu);
}

int CPU_jbe(CPU* cpu)
{
	assert(cpu);
	if (stack_Get(cpu->s, 1) < stack_Get(cpu->s, 2))
		CPU_jmp(cpu);
	else
		cpu->current_command++;
	return CPU_Check(cpu);
}

int CPU_end(CPU* cpu)
{
	assert(cpu);
	cpu->active = 0;
	
	return CPU_Check(cpu);
}

int CPU_call(CPU* cpu)
{
	assert(cpu);
	stack_Push(cpu->call_stack, cpu->current_command + 1);
	CPU_jmp(cpu);
	return CPU_Check(cpu);
}

int CPU_popr(CPU* cpu)
{
	assert(cpu);
	
	cpu->current_command++;
	stack_Push(cpu->s, cpu->registers[cpu->commands[cpu->current_command]]);
	return CPU_Check(cpu);
}

int CPU_meow(CPU* cpu)
{
	assert(cpu);
	printf("\a");
	return CPU_Check(cpu);
}

int CPU_div(CPU* cpu)
{
	assert(cpu);
	stack_Push(cpu->s, stack_Pop(cpu->s) / stack_Pop(cpu->s));
	return CPU_Check(cpu);
}

int CPU_sqrt(CPU* cpu)
{
	assert(cpu);
	stack_Push(cpu->s, sqrt(stack_Pop(cpu->s)));
	return CPU_Check(cpu);
}

int CPU_jed(CPU* cpu)
{
	CPU_je(cpu);
	stack_Pop(cpu->s); stack_Pop(cpu->s);
	return CPU_Check(cpu);
}

int CPU_jned(CPU* cpu)
{
	CPU_jne(cpu);
	stack_Pop(cpu->s); stack_Pop(cpu->s);
	return CPU_Check(cpu);
}

int CPU_jad(CPU* cpu)
{
	CPU_ja(cpu);
	stack_Pop(cpu->s); stack_Pop(cpu->s);
	return CPU_Check(cpu);
}

int CPU_jaed(CPU* cpu)
{
	CPU_jae(cpu);
	stack_Pop(cpu->s); stack_Pop(cpu->s);
	return CPU_Check(cpu);
}

int CPU_jbd(CPU* cpu)
{
	CPU_jb(cpu);
	stack_Pop(cpu->s); stack_Pop(cpu->s);
	return CPU_Check(cpu);
}

int CPU_jbed(CPU* cpu)
{
	CPU_jbe(cpu);
	stack_Pop(cpu->s); stack_Pop(cpu->s);
	return CPU_Check(cpu);
}

int CPU_dub(CPU* cpu)
{
	assert(cpu);
	stack_Push(cpu->s, stack_Get(cpu->s, 1));
	return CPU_Check(cpu);
}

int CPU_Check(CPU* cpu)
{
	if (stack_check(cpu->s) != 0) return CPU_STACK_ERROR;
	if (cpu->commands[cpu->current_command] == -1 && cpu->active) return CPU_INVALID_CURRENT_COMMAND;
	if (cpu->amount_of_commands < 0) return CPU_AMOUNT_OF_COMMANDS_ERROR;
	if (cpu->current_command < 0) return CPU_CURRENT_COMMAND_ERROR;
	if (cpu->active && cpu->commands[cpu->current_command] != CMD_END) return CPU_ACTIVE_MARK_ERROR;
	return CPU_OK;
}

void CPU_print_dump(CPU* cpu, const char* CPU_dump_file)
{
	FILE* dump = fopen(CPU_dump_file, "w");
	
	fprintf(dump, "CPU DUMP (%s)\n\nSignature: %s\n\n", CPU_error_message(CPU_Check(cpu)), SIGN);
	stack_dump(cpu->s, CPU_dump_file);
	fprintf(dump, "Amount of commands: %d\n current command: %d\n\nActive: %d\nCommands: [", cpu->amount_of_commands, cpu->current_command, cpu->active);
	for (int i = 0; i < cpu->amount_of_commands; i++)
	{
		fprintf(dump, "%d ", cpu->commands[i]);
	}
	fprintf(dump, "]\n\n");
	
	
	fprintf(dump, "Registers: {\n");
	for (int i = 0; i < CPU_REGISTERS_AMOUNT; i++)
	{
		if (cpu->registers[i] != POISON)
			fprintf(dump, "	register %d: %lg\n", i, cpu->registers[i]);
	}
	fprintf(dump, "}\n\n");
	
	fprintf(dump, "call_stack [%p] (%s): {\n", cpu->call_stack, stack_error_message(stack_check(cpu->call_stack)));
	fprintf(dump, "	call_stack -> current = %d\n", cpu->call_stack->current);
	for (int j = 0; j < STACK_SIZE; j++)
	{
		if (cpu->call_stack->elements[j] != POISON)
		{
			fprintf(dump, "	call_stack->elements[%d] = %d\n", j, (int)cpu->call_stack->elements[j]);
		}
	}
	fprintf(dump, "}\n\n");
	
	
	fprintf(dump,
	"stack \"s\" (%s) [%p] {\n"
	"	current = %d\n\n", stack_error_message(stack_check(cpu->s)), cpu->s, cpu->s->current);
	
	for (int j = 0; j < cpu->s->current; j++) fprintf(dump, "	elements[%d]: %lg\n", j, cpu->s->elements[j]);
	fprintf(dump, "}\n");
		
	fclose(dump);
}

char* CPU_error_message(CPU_ERROR_CODES error_code)
{
	switch (error_code)
	{
		#define RET_CODE_(code) case code: return #code;
		RET_CODE_ (CPU_OK)
		RET_CODE_ (CPU_STACK_ERROR)
		RET_CODE_ (CPU_INVALID_CURRENT_COMMAND)
		RET_CODE_ (CPU_AMOUNT_OF_COMMANDS_ERROR)
		RET_CODE_ (CPU_CURRENT_COMMAND_ERROR)
		RET_CODE_ (CPU_ACTIVE_MARK_ERROR)
		RET_CODE_ (CPU_INVALID_CODE_OF_THE_TASK)
		default: return "CPU_UNKNOWN_ERROR";
		#undef RET_CODE_
	}
}

void CPU_help(CPU_ERROR_CODES error_code)
{
	printf("%s\n", CPU_error_message(error_code));
}

