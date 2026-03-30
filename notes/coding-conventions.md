1.  - Common Rules

    1.  \*\* General

- No tab character , 1 tab = 4 spaces
- No trailing space
- The maximum width of a code line should not exceed 80 characters
- Avoid global variables or else justify their usage
- Avoid extern variables or else justify their usage
- No unconditional jumps:
  - break is used only in switch statement
  - continue is avoided
  - goto is avoided
  - return is used only one time at end of function
- No recursions
- Restricted size and complexity of function
- Maximum of 6 function parameters.
- Local (file–scope) objects (variables or functions) that do not need
  external linkage shall be declared as static
- Function parameter should be checked

2.  \*\* Variables Naming Convention and rules

    1.  **\*** Global Variable:

g\_\[VariableName\]: camel case for VariableName.

2.  **\*** Static Variable:

s\_\[VariableName\]: camel case for variableName.

3.  **\*** Local Variable:

Local variables used inside function should be defined at the beginning
of function (after assert() block), unless variable is only used inside
​#wrapper.

*Exception:* By using local variables declared at the C code blocks the
compiler can optimize the stack usage and/or register allocation. To be
analyzed case by case. If special optimizations are requested, this rule
can be ignored with remarks in comment.

One local variable get its own line but not add several local variables
into one line like

uint32<sub>t</sub> a, b, c; *\* Wrong format. \**

Local variables must be initialized.

3.  \*\* Comments

Always use "*\*\**" for multiline or standalone comments.

Examples:

int i;

for (;;)

{

``` example
i++; /\* Increase i. \*/
```

}

- Doxygen style:  
  =/\*\*=  
  `* @param=\\
   =*/`

  4.  \*\* Hard Coding Numbers

All hard coding unsigned numbers should be postfixed with 'U'. MISRA
2012 Rule 7.2: A 'u' or 'U' suffix shall be applied to all integer
constants that are represented in an unsigned type

Examples:

Hex: 0x1234ABCDU

Dec: 1234U

5.  \*\* Preprocessor

- Comments should be appended after the \#endif:

​#if I<sub>AMAMACRO</sub>

​#endif *\* I<sub>AMAMACRO</sub> \**

- Add a blank line at the end of file.
- Header files guard macro

​#ifndef <u>HEADER<sub>FILENAME</sub></u>

​#define <u>HEADER<sub>FILENAME</sub></u>

​#endif *\* <u>HEADER<sub>FILENAME</sub></u> \**

2.  - General comment style

Add macros, enumeration types, structure types, inside:

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

​\* Definitions

​\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

**Add global variables definition inside:**

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

​\* Variables

​\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

**Add static API prototype in C file inside:**

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

​\* Prototypes

​\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

**Add function implementation inside:**

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

​\* Code

​\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

**Add public API in header files inside:**

/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

​\* API

​\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

- For header file, the sequence is:
  - Definitions
  - API
- For C file, the sequence is:
  - Definitions
  - Prototypes
  - Variables
  - Codes

| Before                         | After                            |
|--------------------------------|----------------------------------|
| ​#ifdef \#ifdef \#endif \#endif | ​#ifdef \# ifdef \# endif \#endif |

No indentation at declarations in header files.  
Fork original -\> pull request  
Describe each pair .h/.c.
