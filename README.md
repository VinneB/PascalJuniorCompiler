# PascalJuniorCompiler
A Pascal Junior to x86 compiler I built my Spring Semester of my Junior Year for CS4121: Programming Languages.

## Dependencies: Flex, Bison, fp-compiler (optional)
To install dependencies on a unix machine, run 
`sudo <pkg mngr> flex bison fp-compiler`

For example, on Ubuntu you would run
`sudo apt flex bison fp-compiler`

## Setup
1. Run make at the top level of the repo
2. Run `chmod u+x compile_script.sh`

## Usage 

The 'compile_script.sh' shell script is a utility which will compile and process output for you, rather than require manual usage of pjc and gcc. The format for using the script is
`./compile_script.sh <pascal file name without .pas> <diff boolean>`.

The `<pascal file without .pas>` can be any test file in the input directory. Make sure you do not incude '.pas' i.e. '1.func' instead of '1.func.pas'. 

If you do not have the fp-compiler installed, ensure that `diff boolean` is 0. Otherwise, if it is 1, then it will use the GNU Pascal compiler 'fp' to compile the pascal program and show it's result in comparison with our custom 'pjc' compiler.

### Example:

`./compile_script.sh 1.func 1`
