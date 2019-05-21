## Blog post creator for my website

A small and simple tool to create a file with a title and date
for my blog.

## Compiling

```
gcc main.c utils.c
```

## How to use

```
./a.out "Your blogpost name"
```

## Current state

The tool works but some things are hard coded: the created file
will be opened with vscode.
The destination of the file is also hard coded.
If you want to use this tool, you should modify the code directly,
which is bad.
