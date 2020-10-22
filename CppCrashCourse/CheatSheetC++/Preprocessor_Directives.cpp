#include <iostream>
#include <string>

using namespace std;

/*
*	C++ PREPROCESSOR DIRECTIVES
* 
*	C++ Preprocessor are a feature in C++ which the preprocessor actually examine the code before any actual 
	compilation is done
	We tell the preprocessor to perform some preprocessing using PREPROCESSOR DIRECTIVES
*	Those preprocessor directives start with a hash sign (#) followed by our commands
*	Those preprocessor directives doesn't need to be terminated by a semicolon (;), instead it automatically
*	terminated by a newline character. To extend our directives more than one line, use backslash (\)
* 
*	
*/



/*
*	MACRO DEFINITIONS
*
*	Macros are just fragment of the code which we give it a name. Think of it like a string stored in the variable
*	We call the code by its variable name. Think of it like:
* 
*	code myCode = 'cout << "Hello World" << endl; ';
* 
*	The preprocessor will scan over our source code before compilation. Once it encounters any macro name, it will
*	replace that macro name into the actual code. We do this by macro definition
* 
*	
*	Syntax:
*		#define identifier replacement
*	
*	(identifier is macro name, replacement is the actual code fragment it refers to)
* 
*	
* 
*	
*	Identifier can also be a function with parameter. Those are called function-like macros. Those macro names
*	is similar to the function which has parameters. In the actual code we can use those parameters to be replaced
* 
*	Syntax:
*		#define identifier( param1, param2 ) replacement
* 
*	which in replacement code we can actually use param1 and param2
* 
* 
* 
* 
*	We can undefine macro by using #undef, which then we can define the same macro again (although unnecessary in
*	this compiler)
* 
*	Syntax:
*		#undef identifier
* 
* 
* 
*	Hash signs # actually has quite a special meaning when used in the replacement (code fragment).
*		>	Single # useds as replacement in argument would mean the argument were to be treated as string
*			In other words, it encloses the argument in double quotes
*		>	Double # concatenates 2 arguments with no space in between. Think of it like + sign for arguments
* 
*	See example:
*/






void PD_macroDefinition() {
	//	Object-like macro definition
	#define TOPRINT "Hello World"

	cout << TOPRINT << endl;



	//	Function-like macro definition. The right part is the actual code being replaced
	#define GETMAX(a,b) (a > b? a: b)

	cout << GETMAX(5, 100) << endl;



	#define SIZE 10
	int size = SIZE;			//10
	#undef SIZE
	// int size = SIZE;			now is error
	#define SIZE 20
	size = SIZE;			//20



	#define STRING(x) #x
	string s = STRING(Hello World);			//	"Hello World"


	#define CONCAT(x,y) x ## y
	cout << "Hello World" << CONCAT(en, dl);	//	cout << "Hello World" << endl;
}

















/*
*	CONDITIONAL INCLUSIONS
* 
*	Conditional inclusions allow us to include code fragments based on some conditions, especially based on 
*	macro definitions
* 
*	#ifdef identifier				//	If identifier is defined by macro definition before
*	#ifndef identifier				//	If identifier is not defined by any macro definition before
*	#endif							//	Ends the if statement
* 
*	#if <condition>					//	If the condition is true
*	#elif <condition>
*	#else						
* 
* 
* 
*	This is usually used to prevent header files being included multiple times in a source file. Although now
*	the better way is to use #pragma once
*/

#ifdef DEFINED
	#undef DEFINED
#endif


#ifndef NOTDEFINED
	#define NOTDEFINED "I am defined now!"
	#define NUMBER 69
#endif


#if NUMBER>500
	#undef NUMBER
	#define NUMBER 500
#elif NUMBER<50
	#undef NUMBER
	#define NUMBER 50
#else
	#undef NUMBER
	#define NUMBER 250
#endif


























/*
*	LINE CONTROL
* 
*	Line control is simply a preprocessor directive that allow us to manipulate the error message when it gets
*	thrown by its line number and the filename in the error message thrown by compiler
* 
*	Syntax:
*		#line <line_number> <filename>
* 
*/

void PD_lineControl() {
	


	#line 10 "This is the file"
										// <- THis is consider as line 10
	//int a = "Error";

	//Uncomment above to throw an error. The error message shall show file name as "THis is the file" at line 11

}




















/*
*	ERROR DIRECTIVES
* 
*	As the name implies, it will generate a compiler error the moment it mets this preprocessor directive
* 
*	Syntax:
*		#error <errorMessage>
*
*/


//	Change to ifndef to throw error upon compiling
#ifdef NOERROR
	#error ERROR! NOERROR macro is not defined!
#endif





















/*
*	SOURCE FILE INCLUSION
* 
*	Source file inclusion just replace this preprocessor directive directly with the content or header of the file
*	specified
* 
*	Syntax:
*		#include <>
*		#include ""
* 
*	Where in the <> or "" we put in the file name we want to include. Usually, <> is for C++ native implemented
*	files, and "" is for our own files. When "" fails to find any matching file, it falls back to <> to continue
*	searching
*
*/





//	As for #pragma, it is really compiler and platform specific. Refer to manual for that



