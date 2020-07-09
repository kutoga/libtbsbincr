#ifndef __TBS_PLATFORM_H__
#define __TBS_PLATFORM_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32
#define _TBS_IS_LINUX
#else
/* 
 * Include winsock2, because it MUST be included before windows.h (ugly)
 * That is also the reason why it is done here.
 */
#include <winsock2.h>
#include <windows.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
