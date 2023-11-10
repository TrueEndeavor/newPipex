#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
    int fd[2];
    int pid[3];
    int prev = open("in", O_RDONLY);
    int fd_out = open("out", O_CREAT | O_WRONLY, 0664);
    int num_cmds = 3;
    int child_index = 1;
    int status = 0;

    char *cmd1[] = {"/usr/bin/ls", NULL};
    char *cmd2[] = {"/usr/bin/wc", NULL};
    char *cmd3[] = {"/usr/bin/cat", NULL};

        dprintf(2, "OUT>[%d]\n", fd_out);
    while (child_index <= num_cmds) 
    {
        pipe(fd); 
        //close(fd[0]);
        dprintf(2, "PREV>[%d]\n", prev);    
        dprintf(2, "======>[%d, %d]\n", fd[0], fd[1]);
        pid[child_index - 1] = fork();
        if (pid[child_index - 1] == 0) 
        {
            dprintf(2, "------------------>[%d, %d]\n", fd[0], fd[1]);        
            close(fd[0]); // Close read end of the pipe
            dup2(prev, STDIN_FILENO); // Set standard input to the previous command's output
            if (child_index != num_cmds) 
            {
                dup2(fd[1], STDOUT_FILENO); // Set standard output to the pipe
            }
            if (child_index == num_cmds)
            {
                // Redirect standard output to the output file for Child Process 3
               // dup2(fd_out, STDOUT_FILENO);
               // close(fd_out); // Close the output file descriptor
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
            //close(fd[0]);
        }
        child_index++;
    }
    child_index = 1;
    // Wait for child processes to finish
    while(child_index <= num_cmds) 
    {
        if (waitpid(pid[child_index - 1], &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        child_index++;
    }
    printf("Exit Status: %d\n", status);
    return WEXITSTATUS(status);
}
