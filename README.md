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

## How To Use
Use the following commands to copy the program:
```
git clone https://github.com/alina-tariq/cutcommand-C.git
cd cutCommand-C
```

If using a Mac compile with the following command:
```
clang -o cutcmd cutcmd.c cutcmdfuncs.c
```

If using Linux compile with the following command:
```
gcc -o cutcmd cutcmd.c cutcmdfuncs.c
```

To run the executable, the following format is needed:
* executable <input_delimiter> <output_delimiter> field1 field2 field3 ... field n

For example:
```
./cutcmd . ! 2 8 11 15
```
or
```
./cutcmd . ! 2 8 11 15 <inFile
```
