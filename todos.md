
# Feedback
here_doc der process of read should be in a one child process
so that get next line and cat for example run parallel 
and return velues arent all correct shoult be more like:

# GNU BASH MAN:
3.7.5 Exit Status
The exit status of an executed command is the value returned by the waitpid system call or equivalent function. Exit statuses fall between 0 and 255, though, as explained below, the shell may use values above 125 specially. Exit statuses from shell builtins and compound commands are also limited to this range. Under certain circumstances, the shell will use special values to indicate specific failure modes.

For the shell’s purposes, a command which exits with a zero exit status has succeeded. A non-zero exit status indicates failure. This seemingly counter-intuitive scheme is used so there is one well-defined way to indicate success and a variety of ways to indicate various failure modes. When a command terminates on a fatal signal whose number is N, Bash uses the value 128+N as the exit status.

If a command is not found, the child process created to execute it returns a status of 127. If a command is found but is not executable, the return status is 126.

If a command fails because of an error during expansion or redirection, the exit status is greater than zero.

The exit status is used by the Bash conditional commands (see Conditional Constructs) and some of the list constructs (see Lists of Commands).

All of the Bash builtins return an exit status of zero if they succeed and a non-zero status on failure, so they may be used by the conditional and list constructs. All builtins return an exit status of 2 to indicate incorrect usage, generally invalid options or missing arguments.

The exit status of the last command is available in the special parameter $? (see Special Parameters).



# Programming:
-[OK] undersand the subject/requirements
-[OK] think about the structor of the programm
-[OK] parse the input somehow
-[OK] set up forks
-[OK] set up pipe
-[OK] use the comand
-[OK] handel comand errors
-[OK] close all
-[OK] awk '{print $0}'
-[OK] handel absolut path

-[OK] split quots on " ' \" \' 



# Testers
-[OK]https://github.com/gmarcha/pipexMedic (for linux env)
-[OK]paco
./pipex infile "ls -l" "wc -l" outfile
< infile ls -l | wc -l >

./pipex input "awk '{print \$0}'" "awk -F=:efe '{count++} END {printf \"lines: %d\", count}'" out

End tests:


gst | cat | cat |cat -e| cat
./pipex 


        < test.txt ls -l | cat -e | cat -e | cat -e > test2.txt
./ pipex test.txt "ls -l" "cat -e" "cat -e" "cat -e" test2.txt

        < test.txt ls -l | cat -e > test2.txt
./ pipex test.txt "ls -l" "cat -e" test2.txt

# allowed functions
malloc, free		(memory)
open, close, access (files)
unlink, 			(rm file)
read, write, 		(to fds)

dup, dup2, pipe,	(chage fds)
fork, 				(make a chiled proces)
wait, waitpid 		(wait for chiled to finish)
execve 				(run cmd)
exit 				(exit)
perror, strerror,	(error codes)

# git commit cheat chett

feat: A new feature
fix: A bug fix
docs: Documentation only changes
style: Changes that do not affect the meaning of the code (white-space, formatting, missing semi-colons, etc)
refactor: A code change that neither fixes a bug nor adds a feature
perf: A code change that improves performance
test: Adding missing tests
build: build system like akefile or ci/cl