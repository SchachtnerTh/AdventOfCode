#ifndef INTCOMP_H
#define INTCOMP_H

#define DEBUG 0

class intcomp {
	private:
	static const char RELATIVE = '2';
	static const char IMMEDIATE = '1';
	static const char POSITION = '0';

	long *program;
	long *work_program;
	long iIntCount;
	long *p_ptr;	// program pointer
	long input;
	long output;
	long relbase;
	bool program_running;
	
	void fill_program(char *prg);
	int input_and_store_integer(long *ptr);
	void output_integer_from_address(long *ptr);
	long getParam(int op, long position);
	long getParamAddr(int op, long position);
	int do_operation();
	void print_program(char type);
		
	public:
	static const int WAIT_FOR_INPUT = -2;
	intcomp(char *program);
	~intcomp();
	int execute_program(int print_style);
	void execute_program_params(int noun, int verb, char print_style);
	void reset_program();
	void get_input(long inp);
	int get_output();
	void add_to_relative_base(long offset);
};
#endif
