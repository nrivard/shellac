#include "shellac.h"
#include <stdbool.h>
#include "string.h"

#define PARAM_SIZE 10

typedef struct {
    // up to 10 params: name, addr, 8 additional values
    // ex: write 1, 2, 3, 4 starting at address $001000
    //      wr 001000 01 02 03 04
    char *params[PARAM_SIZE];
    int numParams;
} Input;

typedef struct {
    char *name;
    char *usage;
    bool (*function)(char *args[], int count);
} Command;

bool command_read(char *args[], int count);
bool command_write(char *args[], int count);
bool command_transfer(char *args[], int count);
bool command_execute(char *args[], int count);

static Command commands[] = {
    {"rd", "rd <addr> (<length>)", &command_read},
    {"wr", "wr <addr> <value1> (<value2>...<value8>)", &command_write},
    {"tx", "tx <addr>", &command_transfer},
    {"ex", "ex <addr>", &command_execute}
};

char *command_read_input(char *buffer, int size) {
    return NULL;
}

void command_tokenize(char *buffer, Input *input) {
    input->numParams = 0;
    while (input->numParams < PARAM_SIZE) {
        input->params[input->numParams++] = buffer;
        while (1) {
            char *dest = buffer++;
            if (*dest == ' ') {
                *dest = '\0';
                break;
            } else if (*dest == '\n') {
                *dest = '\0';
                return;
            }
        }
    }
}

 bool command_parse(Input *input, Command *command) {
    char *cmdName = input->params[0];
    int size = sizeof(commands) / sizeof(Command);
    for (int i = 0; i < size; i++) {
        Command curr = commands[i];
        if (strcmp(curr.name, cmdName) == 0) {
            *command = curr;
            return true;
        }
    }
    return false;
}

bool command_read(char *args[], int count) {
    if (count < 1) {
        return false;
    }

    char *addr = (char *)strtoul(args[0], NULL, 16);
    int len = count > 1 ? strtoul(args[1], NULL, 16) : 1;

    // printf("Reading %d bytes from %p", len, addr);
    for (int i = 0; i < len; i++) {
        if ((i % 8) == 0) {
            // printf("\n%p:  ", &addr[i]);
        }

        // printf("%02X ", (unsigned int)(addr[i] & 0xFF));
    }

    return true;
}

bool command_write(char *args[], int count) {
    if (count < 2 || count > 9) {
        return false;
    }

    char *addr = (char *)strtoul(args++[0], NULL, 16);

    // printf("Writing %d bytes to %p", count - 1, addr);
    for (int i = 0; i < count - 1; i++) {
        *addr++ = 0xFF & strtoul(args[i], NULL, 16);
    }

    return true;
}

bool command_transfer(char *args[], int count) {
    // printf("transferring\n");
    return false;
}

bool command_execute(char *args[], int count) {
    // printf("executing\n");
    return false;
}

void shellac_send_string(ShellacConfig *config, char *str) {
    while (*str) {
        config->putc(*str++);
    }
}

void shellac_main(ShellacConfig *config) {
    char buffer[0x80];
    Input input;
    Command command;

    for(;;) {
        config->putc('>');
        if (!command_read_input(buffer, sizeof(buffer))) {
            shellac_send_string(config, "FATAL: couldn't read user input!\n");
            return;
        }

        command_tokenize(buffer, &input);

        if (!command_parse(&input, &command)) {
            // printf("Invalid command: \"%s\"\n", input.params[0]);
            continue;
        }

        if (!command.function(&input.params[1], input.numParams - 1)) {
            shellac_send_string(config, "Invalid command!\n");
            shellac_send_string(config, "usage: ");
            shellac_send_string(config, command.usage);
        }

        shellac_send_string(config, "\n");
    }
}
