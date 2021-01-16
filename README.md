# Simplified Cut Command

## Langauge:
* C

## What Is it?
- A simplied version of the Linux cut command recreated in C
- The program takes in 3 argument parameters:
	* the input delimiter (single char)
	* the output delimiter (single char)
	* the fields numbers to cut (between 1-100, each number must be specified SEPARATELY)
- No cut command flags/options are supported
- Input can be provided using either stdin or through a file passed to stdin

##How To Use
Use the following commands to run the program:
```
git clone https://github.com/alina-tariq/cutcommand-C.git
cd cutCommand-C
```
If using a Mac:
```
clang cutcmd.c cutcmdfuncs.c
```
