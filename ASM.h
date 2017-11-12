//----------------------------------------------------------------------
//!Assemblies text code to CPU's numeric code
//!@param	file_name		File name
//!@param	assembled_code_name		Assembled file name
//!@return					Error code
//----------------------------------------------------------------------
int ASM_assembly_code(const char* code_name, const char* assembled_code_name, int* addresses);

//----------------------------------------------------------------------
//!Transtates word to numeric command for CPU
//!@param	word			Word
//!@return					Equal numeric command
//----------------------------------------------------------------------
int word_to_command(char* word);
