#include <stdio.h>
#include "CPU.h"
#include "ASM.h"
#include <string.h>

//char* CPU_CODE_FILE = "CPU_SolveSquare.txt";
//char* CPU_CODE_FILE = "CPU_Factorial.txt";
char* CPU_CODE_FILE = "CPU_Rekurs.txt";
char* CPU_ASSEMBLED_CODE_FILE = "CPU_assembled_code.txt";

int main()
{
	int addresses[CPU_REGISTERS_AMOUNT] = {-1};
	
	ASM_assembly_code(CPU_CODE_FILE, CPU_ASSEMBLED_CODE_FILE, addresses);
	ASM_assembly_code(CPU_CODE_FILE, CPU_ASSEMBLED_CODE_FILE, addresses);
	
	CPU* cpu = CPU_Construct();
	CPU_load_to_the_commands_from_file(cpu, CPU_ASSEMBLED_CODE_FILE);
	CPU_Do(cpu);
	
	CPU_print_dump(cpu, "CPU_DUMP.txt");
	CPU_Destroy(cpu);
	return 0;
}
