#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*CommandHandler)(const char *data);

typedef struct {
  char *name;
  CommandHandler handler;
} Command;

typedef struct {
  Command *commands;
  size_t length;
  size_t capacity;
} CommandRouter;

void init(CommandRouter *cr) {
  cr->capacity = 1;
  cr->length = 0;
  cr->commands = malloc(cr->capacity * sizeof(Command));
}

Command createCommand(char *name, CommandHandler ch) {
  Command command = {name, ch};
  return command;
}

void checkForRealloc(CommandRouter *cr) {
  if (cr->length == cr->capacity) {
    cr->capacity *= 2;
    cr->commands = realloc(cr->commands, cr->capacity * sizeof(Command));
  }
}

void registerCommand(CommandRouter *cr, char *name, CommandHandler ch) {
  checkForRealloc(cr);
  cr->commands[cr->length++] = createCommand(name, ch);
}

void executeCommand(CommandRouter *cr, char *name, char *data) {
  for (int i = 0; i < cr->length; i++) {
    if (strcmp(name, cr->commands[i].name) == 0) {
      cr->commands[i].handler(data);
    }
  }
}
