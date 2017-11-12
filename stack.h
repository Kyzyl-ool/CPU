#define POISON 999999999999999.9999999999999
#define KANAR 771

typedef double stack_elem;

enum stack_error_codes
{
	STACK_OK = 0,
	STACK_TAIL_IS_NOT_POISON,
	STACK_ELEMENT_IS_POISON, 
	STACK_HASHSUM_ERROR,
	ERROR_POP_FROM_EMPTY_STACK, 
	ERROR_PUSH_TO_FULL_STACK,
	STACK_CURRENT_MORE_THAN_LENGTH,
	STACK_GET_FROM_INVALID_INDEX,
};
typedef enum stack_error_codes stack_error_code;

typedef struct stack
{
	int kanar1;
	int current;
	int amount_of_elements;
	stack_elem* elements;
	int hashsum;
	int kanar2;
	
}stack;

stack* 		stack_Construct(int amount_of_elements);
int 		stack_Destroy(stack* s);
int 		stack_Push(stack* s, stack_elem value);
stack_elem	stack_Pop(stack* s);
int			stack_calc_hashsum(stack* s);
stack_error_code	stack_check(stack* s);
char*		stack_error_message(stack_error_code error_code);
void		stack_help(stack_error_code error_code);
void		stack_print_dump(stack* s);
int  		terminate_message(int error);
stack_elem	stack_Get(stack* s, int n);
void 		stack_dump(stack* s, const char* dump_name);
