#ifndef __TBS_ENCR_PLATFORM_H__
#define __TBS_ENCR_PLATFORM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef WIN32
/* Include winsock2, because it MUST be included before windows.h (ugly) */
#include <winsock2.h>
#include <windows.h>
#else
#include <unistd.h>
#include <sys/mman.h>
#endif

#include <tbs/log/core.h>
#include <tbs/util.h>

#ifndef WIN32
static inline void __tbs_encr_linux_mprotect(void *begin, size_t length, int access) {

    /* TODO: Make smaller and put to another function. */

    /* Copied from https://stackoverflow.com/questions/12947388/is-there-a-way-to-modify-the-code-of-a-function-in-a-linux-c-program-at-runtime */
    int pagesize;
    pagesize = sysconf( _SC_PAGE_SIZE );
    int len = length;
    do {
        char *p = (char *)begin;
        p = (char *) ((size_t) p & ~(pagesize - 1));
        tbs_log_trace("Do mprotect for page %p", p);
        mprotect(p, pagesize, access);

        //len -= pagesize;
        len -= pagesize - ((char *)begin - p);
        begin = p + pagesize;
    } while (len > 0);
}
#endif

static inline void __attribute__((always_inline)) tbs_encr_rwx(void *begin, size_t length) {
    tbs_log_trace("Change the memory region %p (%u bytes) to rwx", begin, (unsigned int)length);
    
#ifdef WIN32
    DWORD dummy;
    VirtualProtect(begin, length, PAGE_EXECUTE_READWRITE, &dummy);
#else
    __tbs_encr_linux_mprotect(begin, length, PROT_READ | PROT_WRITE | PROT_EXEC);
#endif

    tbs_log_trace("Changed the memory region %p to rwx", begin);
}

static inline void __attribute__((always_inline)) tbs_encr_rx(void *begin, size_t length) {
    tbs_log_trace("Change the memory region %p (%u bytes) to r_x", begin, (unsigned int)length);
    
#ifdef WIN32
    DWORD dummy;
    VirtualProtect(begin, length, PAGE_EXECUTE_READ, &dummy);
#else
    __tbs_encr_linux_mprotect(begin, length, PROT_READ | PROT_EXEC);
#endif

    tbs_log_trace("Change the memory region %p  to r_x", begin);
}

#ifdef __cplusplus
}
#endif

#endif /* __TBS_ENCR_PLATFORM_H__ */
