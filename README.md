# linux-Shell
shell with input/output redirection. So, the
commands in which |, < and > symbols are used should be supported.
eg:
ls > file.txt
man fork | grep child > file.txt
The command can have any number of | symbols, such as
command1 | command 2 | command3 > file.txt

//Note: It does not run CD commands
