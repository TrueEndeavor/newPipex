#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int execute_commands() 
{
    int fd[2];
    int pid[3];
    int prev = open("in", O_RDONLY);
    int fd_out = open("out", O_CREAT, 00664);
    int num_cmds = 3;
    int child_index = 1;
    int status = 0;

    char *cmd1[] = {"/usr/bin/ls", NULL};
    char *cmd2[] = {"/usr/bin/wc", NULL};
    char *cmd3[] = {"/usr/bin/wc", NULL};

    while (child_index <= num_cmds) 
    {
        pipe(fd); 
        pid[child_index - 1] = fork();
        if (pid[child_index - 1] == 0) 
        {
            close(fd[0]); // Close read end of the pipe
            dup2(prev, STDIN_FILENO); // Set standard input to the previous command's output
            if (child_index != num_cmds) 
            {
                dup2(fd[1], STDOUT_FILENO); // Set standard output to the pipe
            }
            close(fd[1]); // Close write end of the pipe

            if (child_index == 1) 
            {
                execv(cmd1[0], cmd1);
            } else if (child_index == 2) 
            {
                execv(cmd2[0], cmd2);
            } else 
            {
                execv(cmd3[0], cmd3);
            }
            perror("execv");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            close(fd[1]); // Close write end of the pipe in the parent
            prev = fd[0]; // Update the previous read end of the pipe
        }
        child_index++;
    }
    child_index = 1;
    // Wait for child processes to finish
    while(child_index <= num_cmds; i++) 
    {
        if (waitpid(pid[i], &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }

    return WEXITSTATUS(status);
}

int main() {
    int status = execute_commands();
    printf("Exit Status: %d\n", status);
    return status;
}
