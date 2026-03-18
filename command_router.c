#include "command_router.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Command {
  char *name;
  CommandHandler handler;
};

struct CommandRouter {
  struct Command *commands;
  size_t length;
  size_t capacity;
};

CommandRouter *initRouter() {
  CommandRouter *cr = malloc(sizeof(*cr));

  cr->capacity = 1;
  cr->length = 0;
  cr->commands = malloc(cr->capacity * sizeof(struct Command));

  return cr;
}

struct Command createCommand(const char *name, CommandHandler ch) {
  char *copy = malloc((strlen(name) + 1) * sizeof(char));
  strcpy(copy, name);

  struct Command command = {copy, ch};
  return command;
}

void checkForRealloc(CommandRouter *cr) {
  if (cr->length == cr->capacity) {
    cr->capacity *= 2;
    cr->commands = realloc(cr->commands, cr->capacity * sizeof(struct Command));
  }
}

void registerCommand(CommandRouter *cr, const char *name, CommandHandler ch) {
  checkForRealloc(cr);
  cr->commands[cr->length++] = createCommand(name, ch);
}

void executeCommand(CommandRouter *cr, const char *name, const char *data) {
  for (size_t i = 0; i < cr->length; i++) {
    if (strcmp(name, cr->commands[i].name) == 0) {
      cr->commands[i].handler(data);
    }
  }
}

void pop(CommandRouter *cr, size_t index) {
  if (index >= cr->length) {
    printf("Index %zu is out of bounds", index);
    return;
  }

  free(cr->commands[index].name);

  for (size_t i = index; i < cr->length - 1; i++) {
    cr->commands[i] = cr->commands[i + 1];
  }

  cr->length--;
}

void freeRouter(CommandRouter *cr) {
  for (size_t i = 0; i < cr->length; i++) {
    free(cr->commands[i].name);
  }

  free(cr->commands);
  free(cr);
}
