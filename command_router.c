#include "command_router.h"
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
  struct Command command = {strdup(name), ch};
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
  for (int i = 0; i < cr->length; i++) {
    if (strcmp(name, cr->commands[i].name) == 0) {
      cr->commands[i].handler(data);
    }
  }
}
