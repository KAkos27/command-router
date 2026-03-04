#ifndef COMMAND_ROUTER_H
#define COMMAND_ROUTER_H

#include <stddef.h>

typedef void (*CommandHandler)(const char *data);

typedef struct CommandRouter CommandRouter;

CommandRouter *initRouter();
void registerCommand(CommandRouter *cr, const char *name, CommandHandler ch);
void executeCommand(CommandRouter *cr, const char *name, const char *data);
void freeRouter(CommandRouter *cr);

#endif
