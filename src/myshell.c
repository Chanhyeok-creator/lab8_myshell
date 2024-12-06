#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_LINE 80
#define MAX_ARGS 10
#include "ls_command.h"

void execute_program(char *argv[]) {
    pid_t pid = fork();  // 새로운 프로세스 생성

    if (pid < 0) {
        perror("Fork failed");
        return;
    }
    else if (pid == 0) {
        // 자식 프로세스에서 명령어 실행
        if (execvp(argv[0], argv) == -1) {
            perror("Execution failed");
            exit(1);
        }
    }
    else {
        // 부모 프로세스에서 자식 프로세스 종료 대기
        wait(NULL);
    }
}

void cat_command(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File open failed");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);  // 파일 내용 출력
    }

    fclose(file);
}

int main() {
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];

    while (1) {
        // prompt
        printf("myshell> ");

        // read command
        fgets(input, MAX_LINE, stdin);
        input[strcspn(input, "\n")] = '\0';  // 개행 문자 제거

        // tokenize input
        token = strtok(input, " \n\t");
        int i = 0;
        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " \n\t");
        }
        argv[i] = NULL;

        if (argv[0] == NULL) {
            continue;
        }

        if (strcmp(argv[0], "exit") == 0) {
            printf("goodbye!\n");
            exit(0);
        }
        else if (strcmp(argv[0], "cd") == 0) {
            if (chdir(argv[1]) != 0) {
                perror("cd failed");
            }
        }
        else if (strcmp(argv[0], "pwd") == 0) {
            char cwd[MAX_LINE];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("getcwd failed");
            }
        }
        else if (strcmp(argv[0], "ls") == 0) {
            my_ls();  // ls 명령어 실행
        }
        else if (strcmp(argv[0], "cat") == 0) {
            if (argv[1] != NULL) {
                cat_command(argv[1]);  // cat 명령어 실행
            } else {
                printf("Usage: cat <filename>\n");
            }
        }
        else if (strcmp(argv[0], "hello") == 0) {
            print_hello();  // hello 출력
        }
        else {
            execute_program(argv);  // 다른 명령어 실행
        }
    }

    return 0;
}
