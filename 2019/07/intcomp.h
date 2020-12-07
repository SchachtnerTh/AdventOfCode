#ifndef INTCOMP_H
#define INTCOMP_H

#define DEBUG 0

class intcomp {
	private:
	static const char IMMEDIATE = '1';
	static const char POSITION = '0';

	int *program;
	int *work_program;
	int iIntCount;
	int *p_ptr;	// program pointer
	int input;
	int output;
	bool program_running;
	
	void fill_program(char *prg);
	int input_and_store_integer(int *ptr);
	void output_integer_from_address(int *ptr);
	int getParam(int op, int position);
	int do_operation();
	void print_program(char type);
		
	public:
	static const int WAIT_FOR_INPUT = -2;
	intcomp(char *program);
	~intcomp();
	int execute_program(int print_style);
	void execute_program_params(int noun, int verb, char print_style);
	void reset_program();
	void get_input(int inp);
	int get_output();
};
#endif