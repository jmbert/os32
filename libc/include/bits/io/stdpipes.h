#include <fs.h>

#ifndef __STDIN
#define __STDIN 0
#endif

#ifndef __STDOUT
#define __STDOUT 1
#endif

#ifndef __STDERR
#define __STDERR 3
#endif

#ifndef _GET_STDIN
#define _GET_STDIN() _GET_FILE(__STDIN)
#endif

#ifndef _GET_STDOUT
#define _GET_STDOUT() _GET_FILE(__STDOUT)
#endif

#ifndef _GET_STDERR
#define _GET_STDERR() _GET_FILE(__STDERR)
#endif