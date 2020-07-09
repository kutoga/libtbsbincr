#ifndef __INTERNAL_TBS_PLATFORM_H__
#define __INTERNAL_TBS_PLATFORM_H__

#include <tbs/platform.h>
#include <tbs/log.h>


#ifdef _TBS_IS_LINUX
#include <unistd.h>
#include <sys/mman.h>

static inline void __tbs_encr_linux_mprotect(void *begin, size_t length, int access) {

    /* Copied from https://stackoverflow.com/questions/12947388/is-there-a-way-to-modify-the-code-of-a-function-in-a-linux-c-program-at-runtime */
    int pagesize;
    pagesize = sysconf( _SC_PAGE_SIZE );
    int len = length;
    do {
        char *p = (char *)begin;
        p = (char *) ((size_t) p & ~(pagesize - 1));
        _tbs_log_trace("Do mprotect for page %p", p);
        mprotect(p, pagesize, access);

        len -= pagesize - ((char *)begin - p);
        begin = p + pagesize;
    } while (len > 0);
}
#endif

static inline void __attribute__((always_inline)) tbs_page_set_rwx(void *begin, size_t length) {
    _tbs_log_trace("Change the memory region %p (%lu bytes) to rwx", begin, (unsigned long)length);
    
#ifdef _TBS_IS_LINUX
    __tbs_encr_linux_mprotect(begin, length, PROT_READ | PROT_WRITE | PROT_EXEC);
#else
    DWORD dummy;
    VirtualProtect(begin, length, PAGE_EXECUTE_READWRITE, &dummy);
#endif

    _tbs_log_trace("Changed the memory region %p to rwx", begin);
}

static inline void __attribute__((always_inline)) tbs_page_set_rx(void *begin, size_t length) {
    _tbs_log_trace("Change the memory region %p (%lu bytes) to r_x", begin, (unsigned long)length);

#ifdef _TBS_IS_LINUX
    __tbs_encr_linux_mprotect(begin, length, PROT_READ | PROT_EXEC);
#else
    DWORD dummy;
    VirtualProtect(begin, length, PAGE_EXECUTE_READ, &dummy);
#endif

    _tbs_log_trace("Changed the memory region %p  to r_x", begin);
}

#endif
