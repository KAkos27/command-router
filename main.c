#include "command_router.c"
#include <stdio.h>

void firstCommand(const char *data) { printf("first: %s\n", data); }
void secondCommand(const char *data) { printf("second: %s\n", data); }

int main() {
  CommandRouter cr;
  init(&cr);

  registerCommand(&cr, "first", firstCommand);
  registerCommand(&cr, "second", secondCommand);

  executeCommand(&cr, "second", "second with a");
  executeCommand(&cr, "first", "first with a");
  executeCommand(&cr, "second", "second with b");
  executeCommand(&cr, "second", "second with c");
  executeCommand(&cr, "first", "first with b");
  return 0;
}
