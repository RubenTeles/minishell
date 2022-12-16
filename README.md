# MiniShell


https://user-images.githubusercontent.com/75394884/208167703-aaf2df36-63bc-4ab2-bc17-9df6a26c85b4.mp4


### What is a shell?
A shell is a user interface for accessing the services of an operating system. Put simply, a shell is the outermost layer of communication between the user and operating system. Allowing us to navigate and execute tasks in human-readable language.

### Project
In this project, we implemented many features that recreate a **BASH**. 
Those include running executables from absolute or relative path, like `/usr/bin/ls` or `ls`, which are fetched from the environment PATH. It handles **pipe** redirection with as many commands as needed. It supports usage of quotes and single quotes -- including nested ones -- and environment variable expansion `$`.
A few of the functions are "built-in", meaning we don't call the executable, but rather our own functions from inside the shell itself.

#### Signals:
 `Ctrl-C` `Ctrl-\` and `Ctrl-D` to quit the program, in the same way as **bash**.

#### "Built-In":
`echo`, `pwd`, `cd`, `env`, `export`, `unset` and `exit`.

#### Bonus:
`&&`, `||` with `()` and the wildcard `*` 

#### Extras:
* **name**: Show allways the PATH, like **bash**.
* **quotes**: If there are quotes to close, it will wait until closing.
* **wildcard `*`**: Works in all directories.

```diff
# Requirements: GNU Readline Library
# To install the readline library, open the terminal window and write
sudo apt-get install libreadline-dev

# Clone the project and access the folder
git clone https://github.com/RubenTeles/minishell && cd minishell/

# Compile the program
make

# Run the program
./minishell

# Write any shell command like
echo "hello minishell"

# Quit the program
exit

# Well done!
```
