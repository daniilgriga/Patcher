#ifndef TOOLS_H
#define TOOLS_H

#include "colors.h"
#include "errors.h"

#define PATCHER_ERROR_CHECK(status)                                                                               \
        {                                                                                                         \
            if (status != NO_ERRORS)                                                                              \
            {                                                                                                     \
                fprintf (stderr, "\n" RED_TEXT ("ERROR <%d>:") " %s, " PURPLE_TEXT ("%s: %s: line %d.") "\n", \
                         status, PatcherErrorsMessenger(status), __FILE__, __FUNCTION__, __LINE__);               \
            }                                                                                                     \
        }

const char* PatcherErrorsMessenger (enum PatcherErrors status);

#endif // TOOLS_H
