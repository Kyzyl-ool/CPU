#include "stack.h"

#define CPU_REGISTERS_AMOUNT 128
#define SIGN "KZL 1.0"
#define INVALID_ADDRESS -1
#define	POISON 999999999999999.9999999999999

enum CMD {
		CMD_INVALID = -1,
		CMD_NULL,
		CMD_PUSH,
		CMD_PUSHR,
		CMD_POP,
		CMD_POPR,
		CMD_MUL,
		CMD_ADD,
		CMD_RET,
		CMD_JMP,
		CMD_JE,
		CMD_JNE,
		CMD_JA,
		CMD_JAE,
		CMD_JB,
		CMD_JBE,
		CMD_END,
		CMD_CALL,
		CMD_DIV,
		CMD_SQRT,
		CMD_JED,
		CMD_JNED,
		CMD_JAD,
		CMD_JAED,
		CMD_JBD,
		CMD_JBED,
		CMD_DUB,
		CMD_MEOW};
typedef enum CMD CMD_t;

enum CPU_ERROR_CODES
{
	CPU_OK = 0,
	CPU_STACK_ERROR,
	CPU_INVALID_CURRENT_COMMAND,
	CPU_AMOUNT_OF_COMMANDS_ERROR,
	CPU_CURRENT_COMMAND_ERROR,
	CPU_ACTIVE_MARK_ERROR,
	CPU_INVALID_CODE_OF_THE_TASK,
};
typedef enum CPU_ERROR_CODES CPU_ERROR_CODES;


typedef double CPU_register_t;
typedef struct CPU
{
	stack* s;
	stack* addresses;
	CMD_t* commands;
	int amount_of_commands;
	int current_command;
	char active;
	
	CPU_register_t registers[CPU_REGISTERS_AMOUNT];
	int call_addresses[CPU_REGISTERS_AMOUNT];
	
	stack* call_stack;
}CPU;

CPU* CPU_Construct();
void CPU_Destroy(CPU* cpu);
int CPU_load_to_the_commands_from_file(CPU* cpu, char* assembled_file_name);
int CPU_Do(CPU* cpu);
void CPU_print_dump(CPU* cpu, const char* CPU_dump_file);
int CPU_Check(CPU* cpu);
char* CPU_error_message(CPU_ERROR_CODES error_code);
void CPU_help(CPU_ERROR_CODES error_code);

int CPU_push(CPU* cpu);
int CPU_pop(CPU* cpu);
int CPU_mul(CPU* cpu);
int CPU_add(CPU* cpu);
int CPU_ret(CPU* cpu);
int CPU_jmp(CPU* cpu);
int CPU_je(CPU* cpu);
int CPU_jne(CPU* cpu);
int CPU_ja(CPU* cpu);
int CPU_jae(CPU* cpu);
int CPU_jb(CPU* cpu);
int CPU_jbe(CPU* cpu);
int CPU_end(CPU* cpu);
int CPU_call(CPU* cpu);
int CPU_pushr(CPU* cpu);
int CPU_popr(CPU* cpu);
int CPU_meow(CPU* cpu);
int CPU_sqrt(CPU* cpu);
int CPU_div(CPU* cpu);
int CPU_dub(CPU* cpu);

int CPU_jed(CPU* cpu);
int CPU_jned(CPU* cpu);
int CPU_jad(CPU* cpu);
int CPU_jaed(CPU* cpu);
int CPU_jbd(CPU* cpu);
int CPU_jbed(CPU* cpu);
