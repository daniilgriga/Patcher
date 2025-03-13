#ifndef TOOLS_H
#define TOOLS_H

#include "colors.h"
#include "errors.h"

#define PATCHER_ERR_CHECK_RET_STATUS(status)                                                                    \
        {                                                                                                       \
            enum PatcherErrors temp = status;                                                                   \
            if (temp != NO_ERRORS)                                                                              \
            {                                                                                                   \
                fprintf (stderr, "\n" RED_TEXT ("ERROR <%d>:") " %s, " PURPLE_TEXT ("%s: %s: line %d.") "\n",   \
                         temp, PatcherErrorsMessenger(temp), __FILE__, __FUNCTION__, __LINE__);                 \
                return temp;                                                                                    \
            }                                                                                                   \
        }

#define PATCHER_ERROR_MESSAGE(status)                                                                           \
        {                                                                                                       \
            enum PatcherErrors temp = status;                                                                   \
            if (temp != NO_ERRORS)                                                                              \
            {                                                                                                   \
                fprintf (stderr, "\n" RED_TEXT ("ERROR <%d>:") " %s, " PURPLE_TEXT ("%s: %s: line %d.") "\n",   \
                         temp, PatcherErrorsMessenger(temp), __FILE__, __FUNCTION__, __LINE__);                 \
            }                                                                                                   \
        }

const char* PatcherErrorsMessenger (enum PatcherErrors status);

#endif // TOOLS_H
