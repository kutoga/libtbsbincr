


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;






static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __builtin_bswap32 (__bsx);
}
static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
typedef long unsigned int size_t;







typedef __time_t time_t;







struct timespec
{
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};





typedef __pid_t pid_t;




struct sched_param
{
  int sched_priority;
};



typedef unsigned long int __cpu_mask;






typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;


extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
     __attribute__ ((__nothrow__ , __leaf__));
extern cpu_set_t *__sched_cpualloc (size_t __count) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void __sched_cpufree (cpu_set_t *__set) __attribute__ ((__nothrow__ , __leaf__));











extern int sched_setparam (__pid_t __pid, const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getparam (__pid_t __pid, struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_setscheduler (__pid_t __pid, int __policy,
          const struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getscheduler (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_yield (void) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_max (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_min (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) __attribute__ ((__nothrow__ , __leaf__));













typedef __clock_t clock_t;







struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  const char *tm_zone;




};












typedef __clockid_t clockid_t;






typedef __timer_t timer_t;







struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
struct sigevent;
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;

typedef __locale_t locale_t;











extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));


extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));





extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));




extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));




extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));






extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));


extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));




extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));



extern int daylight;
extern long int timezone;





extern int stime (const time_t *__when) __attribute__ ((__nothrow__ , __leaf__));
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);



extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__));






extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);


extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));


extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));





extern int timespec_get (struct timespec *__ts, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;




  unsigned char __pad1[7];


  unsigned long int __pad2;


  unsigned int __flags;
};




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
struct __pthread_mutex_s
{
  int __lock ;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;



  int __kind;
 




  short __spins; short __elision;
  __pthread_list_t __list;
 
};




struct __pthread_cond_s
{
  __extension__ union
  {
    __extension__ unsigned long long int __wseq;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __wseq32;
  };
  __extension__ union
  {
    __extension__ unsigned long long int __g1_start;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __g1_start32;
  };
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;




typedef long int __jmp_buf[8];




enum
{
  PTHREAD_CREATE_JOINABLE,

  PTHREAD_CREATE_DETACHED

};



enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP

  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL





};




enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};





enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
enum
{
  PTHREAD_INHERIT_SCHED,

  PTHREAD_EXPLICIT_SCHED

};



enum
{
  PTHREAD_SCOPE_SYSTEM,

  PTHREAD_SCOPE_PROCESS

};



enum
{
  PTHREAD_PROCESS_PRIVATE,

  PTHREAD_PROCESS_SHARED

};
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};


enum
{
  PTHREAD_CANCEL_ENABLE,

  PTHREAD_CANCEL_DISABLE

};
enum
{
  PTHREAD_CANCEL_DEFERRED,

  PTHREAD_CANCEL_ASYNCHRONOUS

};





extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));





extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));







extern int pthread_join (pthread_t __th, void **__thread_return);
extern int pthread_detach (pthread_t __th) __attribute__ ((__nothrow__ , __leaf__));



extern pthread_t pthread_self (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));







extern int pthread_attr_init (pthread_attr_t *__attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_destroy (pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getdetachstate (const pthread_attr_t *__attr,
     int *__detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getguardsize (const pthread_attr_t *__attr,
          size_t *__guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getschedparam (const pthread_attr_t *__restrict __attr,
           struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
           const struct sched_param *__restrict
           __param) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_getschedpolicy (const pthread_attr_t *__restrict
     __attr, int *__restrict __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getinheritsched (const pthread_attr_t *__restrict
      __attr, int *__restrict __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getscope (const pthread_attr_t *__restrict __attr,
      int *__restrict __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getstackaddr (const pthread_attr_t *__restrict
          __attr, void **__restrict __stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));





extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));


extern int pthread_attr_getstacksize (const pthread_attr_t *__restrict
          __attr, size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getstack (const pthread_attr_t *__restrict __attr,
      void **__restrict __stackaddr,
      size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));


extern int pthread_getschedparam (pthread_t __target_thread,
      int *__restrict __policy,
      struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));


extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     __attribute__ ((__nothrow__ , __leaf__));
extern int pthread_once (pthread_once_t *__once_control,
    void (*__init_routine) (void)) __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_setcancelstate (int __state, int *__oldstate);



extern int pthread_setcanceltype (int __type, int *__oldtype);


extern int pthread_cancel (pthread_t __th);




extern void pthread_testcancel (void);




typedef struct
{
  struct
  {
    __jmp_buf __cancel_jmp_buf;
    int __mask_was_saved;
  } __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__ ((__aligned__));
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};
extern void __pthread_register_cancel (__pthread_unwind_buf_t *__buf)
     ;
extern void __pthread_unregister_cancel (__pthread_unwind_buf_t *__buf)
  ;
extern void __pthread_unwind_next (__pthread_unwind_buf_t *__buf)
     __attribute__ ((__noreturn__))

     __attribute__ ((__weak__))

     ;



struct __jmp_buf_tag;
extern int __sigsetjmp (struct __jmp_buf_tag *__env, int __savemask) __attribute__ ((__nothrow__));





extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          const pthread_mutexattr_t *__mutexattr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
        const struct timespec *__restrict
        __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
      __restrict __mutex,
      int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
      int __prioceiling,
      int *__restrict __old_ceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));




extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
      __restrict __attr,
      int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict
          __attr, int *__restrict __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
       __restrict __attr,
       int *__restrict __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
          __restrict __attr,
          int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
     int *__robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));







extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
    const pthread_rwlockattr_t *__restrict
    __attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getkind_np (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pref)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
         const pthread_condattr_t *__restrict __cond_attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_destroy (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_signal (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
         pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       const struct timespec *__restrict __abstime)
     __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_condattr_init (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_getpshared (const pthread_condattr_t *
     __restrict __attr,
     int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_condattr_getclock (const pthread_condattr_t *
          __restrict __attr,
          __clockid_t *__restrict __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
     const pthread_barrierattr_t *__restrict
     __attr, unsigned int __count)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_getpshared (const pthread_barrierattr_t *
        __restrict __attr,
        int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_key_delete (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern void *pthread_getspecific (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern int pthread_setspecific (pthread_key_t __key,
    const void *__pointer) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) __attribute__ ((__nothrow__ , __leaf__));












struct _IO_FILE;
typedef struct _IO_FILE __FILE;



struct _IO_FILE;


typedef struct _IO_FILE FILE;




typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;




typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
typedef __builtin_va_list __gnuc_va_list;
struct _IO_jump_t; struct _IO_FILE;




typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
  __off64_t _offset;







  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;

  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));




typedef __gnuc_va_list va_list;
typedef __off_t off_t;
typedef __ssize_t ssize_t;






typedef _G_fpos_t fpos_t;



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));







extern FILE *tmpfile (void) ;
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;




extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;







extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);
extern int fflush_unlocked (FILE *__stream);
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;





extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;







extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);







extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;







extern void perror (const char *__s);





extern int sys_nerr;
extern const char *const sys_errlist[];




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));






typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;


typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;





typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef int int_least32_t;

typedef long int int_least64_t;






typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;

typedef unsigned long int uint_least64_t;
typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;

typedef struct t_tbs_keygen {
    void (*seed)(struct t_tbs_keygen *keygen, int seed);
    uint16_t (*next)(struct t_tbs_keygen *keygen);
    void (*data_cleanup)(struct t_tbs_keygen *keygen);
    void *data;
} tbs_keygen;

tbs_keygen tbs_keygen_default;



typedef struct tbs_crypto_algorithm {
    void (*initalize)(struct tbs_crypto_algorithm *alg);
    char (*encrypt)(struct tbs_crypto_algorithm *alg, char chr);
    char (*decrypt)(struct tbs_crypto_algorithm *alg, char chr);
    void (*data_cleanup)(struct tbs_crypto_algorithm *alg);
    void *data;
} tbs_crypto_algorithm;
typedef struct tbs_config {
    
   _Bool 
   thread_safe; 
   _Bool 
   re_encrypt; 
   _Bool 
   re_enetrant; tbs_keygen * keygen;
} tbs_config;







typedef struct _tbs_section_config {
    const 
   _Bool 
   thread_safe; const 
   _Bool 
   re_encrypt; const 
   _Bool 
   re_enetrant; tbs_keygen *const keygen;
    const tbs_config *const settings;
} _tbs_section_config;

int main() {




   

   

   

   do { ({ const _tbs_section_config _tbs_0__config = ({ (((_tbs_section_config) { thread_safe: 
   1
   , re_encrypt: 
   1
   , re_enetrant: 
   1
   , keygen: &tbs_keygen_default, settings: 
   ((void *)0)
   , re_encrypt: 
   0 
   })); }); (void)&&_tbs_0__section_start; (void)&&_tbs_0__section_end; ({ static pthread_mutex_t _tbs_0__section_lock = 
   { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
   ; static int _tbs_0__access_count = 0; if (!(_tbs_0__config.settings ? _tbs_0__config.settings->re_encrypt : _tbs_0__config.re_encrypt)) { static 
   _Bool 
   _tbs_0__initialized = 
   0
   ; if (!_tbs_0__initialized) { if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { pthread_mutex_lock(&_tbs_0__section_lock); } if (!_tbs_0__initialized) { _tbs_0__initialized = 
   1
   ; do { do { ; } while (0);; } while (0); } if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { pthread_mutex_unlock(&_tbs_0__section_lock); } } } else if ((_tbs_0__config.settings ? _tbs_0__config.settings->re_enetrant : _tbs_0__config.re_enetrant)) { if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { pthread_mutex_lock(&_tbs_0__section_lock); } if (_tbs_0__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { pthread_mutex_unlock(&_tbs_0__section_lock); } } } else if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { pthread_mutex_lock(&_tbs_0__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_0__protected_exp_res = (({ do { _tbs_0__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_0__enc_exp_res = (({ do { { printf("hey\n"); }; } while (0); 
   ((void *)0)
   ; })); do { ; } while (0); do { _tbs_0__section_end: do { ; } while (0);; } while (0); _tbs_0__enc_exp_res; })); if ((_tbs_0__config.settings ? _tbs_0__config.settings->re_encrypt : _tbs_0__config.re_encrypt)) { if ((_tbs_0__config.settings ? _tbs_0__config.settings->re_enetrant : _tbs_0__config.re_enetrant)) { if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { pthread_mutex_lock(&_tbs_0__section_lock); } if (_tbs_0__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { pthread_mutex_unlock(&_tbs_0__section_lock); } } else if ((_tbs_0__config.settings ? _tbs_0__config.settings->thread_safe : _tbs_0__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_0__section_lock); } } _tbs_0__protected_exp_res; }); }); } while (0)

                         ;
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   do { ({ const _tbs_section_config _tbs_6__config = ({ (((_tbs_section_config) { thread_safe: 
   1
   , re_encrypt: 
   1
   , re_enetrant: 
   1
   , keygen: &tbs_keygen_default, settings: 
   ((void *)0)
   , })); }); (void)&&_tbs_6__section_start; (void)&&_tbs_6__section_end; ({ static pthread_mutex_t _tbs_6__section_lock = 
   { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
   ; static int _tbs_6__access_count = 0; if (!(_tbs_6__config.settings ? _tbs_6__config.settings->re_encrypt : _tbs_6__config.re_encrypt)) { static 
   _Bool 
   _tbs_6__initialized = 
   0
   ; if (!_tbs_6__initialized) { if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { pthread_mutex_lock(&_tbs_6__section_lock); } if (!_tbs_6__initialized) { _tbs_6__initialized = 
   1
   ; do { do { ; } while (0);; } while (0); } if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { pthread_mutex_unlock(&_tbs_6__section_lock); } } } else if ((_tbs_6__config.settings ? _tbs_6__config.settings->re_enetrant : _tbs_6__config.re_enetrant)) { if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { pthread_mutex_lock(&_tbs_6__section_lock); } if (_tbs_6__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { pthread_mutex_unlock(&_tbs_6__section_lock); } } } else if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { pthread_mutex_lock(&_tbs_6__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_6__protected_exp_res = (({ do { _tbs_6__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_6__enc_exp_res = (({ do { { printf("ho\n"); do { ({ const _tbs_section_config _tbs_1__config = ({ (((_tbs_section_config) { thread_safe: 
   1
   , re_encrypt: 
   1
   , re_enetrant: 
   1
   , keygen: &tbs_keygen_default, settings: 
   ((void *)0)
   , })); }); (void)&&_tbs_1__section_start; (void)&&_tbs_1__section_end; ({ static pthread_mutex_t _tbs_1__section_lock = 
   { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
   ; static int _tbs_1__access_count = 0; if (!(_tbs_1__config.settings ? _tbs_1__config.settings->re_encrypt : _tbs_1__config.re_encrypt)) { static 
   _Bool 
   _tbs_1__initialized = 
   0
   ; if (!_tbs_1__initialized) { if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { pthread_mutex_lock(&_tbs_1__section_lock); } if (!_tbs_1__initialized) { _tbs_1__initialized = 
   1
   ; do { do { ; } while (0);; } while (0); } if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { pthread_mutex_unlock(&_tbs_1__section_lock); } } } else if ((_tbs_1__config.settings ? _tbs_1__config.settings->re_enetrant : _tbs_1__config.re_enetrant)) { if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { pthread_mutex_lock(&_tbs_1__section_lock); } if (_tbs_1__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { pthread_mutex_unlock(&_tbs_1__section_lock); } } } else if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { pthread_mutex_lock(&_tbs_1__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_1__protected_exp_res = (({ do { _tbs_1__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_1__enc_exp_res = (({ do { { printf("go\n"); }; } while (0); 
   ((void *)0)
   ; })); do { ; } while (0); do { _tbs_1__section_end: do { ; } while (0);; } while (0); _tbs_1__enc_exp_res; })); if ((_tbs_1__config.settings ? _tbs_1__config.settings->re_encrypt : _tbs_1__config.re_encrypt)) { if ((_tbs_1__config.settings ? _tbs_1__config.settings->re_enetrant : _tbs_1__config.re_enetrant)) { if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { pthread_mutex_lock(&_tbs_1__section_lock); } if (_tbs_1__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { pthread_mutex_unlock(&_tbs_1__section_lock); } } else if ((_tbs_1__config.settings ? _tbs_1__config.settings->thread_safe : _tbs_1__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_1__section_lock); } } _tbs_1__protected_exp_res; }); }); } while (0); do { ({ const _tbs_section_config _tbs_5__config = ({ (((_tbs_section_config) { thread_safe: 
   1
   , re_encrypt: 
   1
   , re_enetrant: 
   1
   , keygen: &tbs_keygen_default, settings: 
   ((void *)0)
   , })); }); (void)&&_tbs_5__section_start; (void)&&_tbs_5__section_end; ({ static pthread_mutex_t _tbs_5__section_lock = 
   { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
   ; static int _tbs_5__access_count = 0; if (!(_tbs_5__config.settings ? _tbs_5__config.settings->re_encrypt : _tbs_5__config.re_encrypt)) { static 
   _Bool 
   _tbs_5__initialized = 
   0
   ; if (!_tbs_5__initialized) { if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { pthread_mutex_lock(&_tbs_5__section_lock); } if (!_tbs_5__initialized) { _tbs_5__initialized = 
   1
   ; do { do { ; } while (0);; } while (0); } if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { pthread_mutex_unlock(&_tbs_5__section_lock); } } } else if ((_tbs_5__config.settings ? _tbs_5__config.settings->re_enetrant : _tbs_5__config.re_enetrant)) { if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { pthread_mutex_lock(&_tbs_5__section_lock); } if (_tbs_5__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { pthread_mutex_unlock(&_tbs_5__section_lock); } } } else if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { pthread_mutex_lock(&_tbs_5__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_5__protected_exp_res = (({ do { _tbs_5__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_5__enc_exp_res = (({ do { printf("%d + %d = %d\n", ({ const _tbs_section_config _tbs_2__config = ({ (((_tbs_section_config) { thread_safe: 
   1
   , re_encrypt: 
   1
   , re_enetrant: 
   1
   , keygen: &tbs_keygen_default, settings: 
   ((void *)0)
   , })); }); (void)&&_tbs_2__section_start; (void)&&_tbs_2__section_end; ({ static pthread_mutex_t _tbs_2__section_lock = 
   { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
   ; static int _tbs_2__access_count = 0; if (!(_tbs_2__config.settings ? _tbs_2__config.settings->re_encrypt : _tbs_2__config.re_encrypt)) { static 
   _Bool 
   _tbs_2__initialized = 
   0
   ; if (!_tbs_2__initialized) { if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { pthread_mutex_lock(&_tbs_2__section_lock); } if (!_tbs_2__initialized) { _tbs_2__initialized = 
   1
   ; do { do { ; } while (0);; } while (0); } if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { pthread_mutex_unlock(&_tbs_2__section_lock); } } } else if ((_tbs_2__config.settings ? _tbs_2__config.settings->re_enetrant : _tbs_2__config.re_enetrant)) { if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { pthread_mutex_lock(&_tbs_2__section_lock); } if (_tbs_2__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { pthread_mutex_unlock(&_tbs_2__section_lock); } } } else if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { pthread_mutex_lock(&_tbs_2__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_2__protected_exp_res = (({ do { _tbs_2__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_2__enc_exp_res = ((1)); do { ; } while (0); do { _tbs_2__section_end: do { ; } while (0);; } while (0); _tbs_2__enc_exp_res; })); if ((_tbs_2__config.settings ? _tbs_2__config.settings->re_encrypt : _tbs_2__config.re_encrypt)) { if ((_tbs_2__config.settings ? _tbs_2__config.settings->re_enetrant : _tbs_2__config.re_enetrant)) { if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { pthread_mutex_lock(&_tbs_2__section_lock); } if (_tbs_2__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { pthread_mutex_unlock(&_tbs_2__section_lock); } } else if ((_tbs_2__config.settings ? _tbs_2__config.settings->thread_safe : _tbs_2__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_2__section_lock); } } _tbs_2__protected_exp_res; }); }), ({ const _tbs_section_config _tbs_3__config = ({ (((_tbs_section_config) { thread_safe: 
   1
   , re_encrypt: 
   1
   , re_enetrant: 
   1
   , keygen: &tbs_keygen_default, settings: 
   ((void *)0)
   , })); }); (void)&&_tbs_3__section_start; (void)&&_tbs_3__section_end; ({ static pthread_mutex_t _tbs_3__section_lock = 
   { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
   ; static int _tbs_3__access_count = 0; if (!(_tbs_3__config.settings ? _tbs_3__config.settings->re_encrypt : _tbs_3__config.re_encrypt)) { static 
   _Bool 
   _tbs_3__initialized = 
   0
   ; if (!_tbs_3__initialized) { if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { pthread_mutex_lock(&_tbs_3__section_lock); } if (!_tbs_3__initialized) { _tbs_3__initialized = 
   1
   ; do { do { ; } while (0);; } while (0); } if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { pthread_mutex_unlock(&_tbs_3__section_lock); } } } else if ((_tbs_3__config.settings ? _tbs_3__config.settings->re_enetrant : _tbs_3__config.re_enetrant)) { if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { pthread_mutex_lock(&_tbs_3__section_lock); } if (_tbs_3__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { pthread_mutex_unlock(&_tbs_3__section_lock); } } } else if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { pthread_mutex_lock(&_tbs_3__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_3__protected_exp_res = (({ do { _tbs_3__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_3__enc_exp_res = ((3)); do { ; } while (0); do { _tbs_3__section_end: do { ; } while (0);; } while (0); _tbs_3__enc_exp_res; })); if ((_tbs_3__config.settings ? _tbs_3__config.settings->re_encrypt : _tbs_3__config.re_encrypt)) { if ((_tbs_3__config.settings ? _tbs_3__config.settings->re_enetrant : _tbs_3__config.re_enetrant)) { if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { pthread_mutex_lock(&_tbs_3__section_lock); } if (_tbs_3__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { pthread_mutex_unlock(&_tbs_3__section_lock); } } else if ((_tbs_3__config.settings ? _tbs_3__config.settings->thread_safe : _tbs_3__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_3__section_lock); } } _tbs_3__protected_exp_res; }); }), ({ const _tbs_section_config _tbs_4__config = ({ (((_tbs_section_config) { thread_safe: 
   1
   , re_encrypt: 
   1
   , re_enetrant: 
   1
   , keygen: &tbs_keygen_default, settings: 
   ((void *)0)
   , })); }); (void)&&_tbs_4__section_start; (void)&&_tbs_4__section_end; ({ static pthread_mutex_t _tbs_4__section_lock = 
   { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
   ; static int _tbs_4__access_count = 0; if (!(_tbs_4__config.settings ? _tbs_4__config.settings->re_encrypt : _tbs_4__config.re_encrypt)) { static 
   _Bool 
   _tbs_4__initialized = 
   0
   ; if (!_tbs_4__initialized) { if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { pthread_mutex_lock(&_tbs_4__section_lock); } if (!_tbs_4__initialized) { _tbs_4__initialized = 
   1
   ; do { do { ; } while (0);; } while (0); } if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { pthread_mutex_unlock(&_tbs_4__section_lock); } } } else if ((_tbs_4__config.settings ? _tbs_4__config.settings->re_enetrant : _tbs_4__config.re_enetrant)) { if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { pthread_mutex_lock(&_tbs_4__section_lock); } if (_tbs_4__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { pthread_mutex_unlock(&_tbs_4__section_lock); } } } else if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { pthread_mutex_lock(&_tbs_4__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_4__protected_exp_res = (({ do { _tbs_4__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_4__enc_exp_res = ((1 + 3)); do { ; } while (0); do { _tbs_4__section_end: do { ; } while (0);; } while (0); _tbs_4__enc_exp_res; })); if ((_tbs_4__config.settings ? _tbs_4__config.settings->re_encrypt : _tbs_4__config.re_encrypt)) { if ((_tbs_4__config.settings ? _tbs_4__config.settings->re_enetrant : _tbs_4__config.re_enetrant)) { if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { pthread_mutex_lock(&_tbs_4__section_lock); } if (_tbs_4__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { pthread_mutex_unlock(&_tbs_4__section_lock); } } else if ((_tbs_4__config.settings ? _tbs_4__config.settings->thread_safe : _tbs_4__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_4__section_lock); } } _tbs_4__protected_exp_res; }); })); } while (0); 
   ((void *)0)
   ; })); do { ; } while (0); do { _tbs_5__section_end: do { ; } while (0);; } while (0); _tbs_5__enc_exp_res; })); if ((_tbs_5__config.settings ? _tbs_5__config.settings->re_encrypt : _tbs_5__config.re_encrypt)) { if ((_tbs_5__config.settings ? _tbs_5__config.settings->re_enetrant : _tbs_5__config.re_enetrant)) { if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { pthread_mutex_lock(&_tbs_5__section_lock); } if (_tbs_5__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { pthread_mutex_unlock(&_tbs_5__section_lock); } } else if ((_tbs_5__config.settings ? _tbs_5__config.settings->thread_safe : _tbs_5__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_5__section_lock); } } _tbs_5__protected_exp_res; }); }); } while (0); }; } while (0); 
   ((void *)0)
   ; })); do { ; } while (0); do { _tbs_6__section_end: do { ; } while (0);; } while (0); _tbs_6__enc_exp_res; })); if ((_tbs_6__config.settings ? _tbs_6__config.settings->re_encrypt : _tbs_6__config.re_encrypt)) { if ((_tbs_6__config.settings ? _tbs_6__config.settings->re_enetrant : _tbs_6__config.re_enetrant)) { if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { pthread_mutex_lock(&_tbs_6__section_lock); } if (_tbs_6__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { pthread_mutex_unlock(&_tbs_6__section_lock); } } else if ((_tbs_6__config.settings ? _tbs_6__config.settings->thread_safe : _tbs_6__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_6__section_lock); } } _tbs_6__protected_exp_res; }); }); } while (0)
      ;


            printf("%d + %d = %d\n",
                ({ const _tbs_section_config _tbs_7__config = ({
               
                (((_tbs_section_config) { thread_safe: 
               1
               , re_encrypt: 
               1
               , re_enetrant: 
               1
               , keygen: &tbs_keygen_default, settings: 
               ((void *)0)
               , }));
                }); (void)&&_tbs_7__section_start; (void)&&_tbs_7__section_end; ({ static pthread_mutex_t _tbs_7__section_lock = 
               { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
               ; static int _tbs_7__access_count = 0; if (!(_tbs_7__config.settings ? _tbs_7__config.settings->re_encrypt : _tbs_7__config.re_encrypt)) { static 
               _Bool 
               _tbs_7__initialized = 
               0
               ; if (!_tbs_7__initialized) { if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { pthread_mutex_lock(&_tbs_7__section_lock); } if (!_tbs_7__initialized) { _tbs_7__initialized = 
               1
               ; do { do { ; } while (0);; } while (0); } if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { pthread_mutex_unlock(&_tbs_7__section_lock); } } } else if ((_tbs_7__config.settings ? _tbs_7__config.settings->re_enetrant : _tbs_7__config.re_enetrant)) { if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { pthread_mutex_lock(&_tbs_7__section_lock); } if (_tbs_7__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { pthread_mutex_unlock(&_tbs_7__section_lock); } } } else if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { pthread_mutex_lock(&_tbs_7__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_7__protected_exp_res = (({ do { _tbs_7__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_7__enc_exp_res = ((1)); do { ; } while (0); do { _tbs_7__section_end: do { ; } while (0);; } while (0); _tbs_7__enc_exp_res; })); if ((_tbs_7__config.settings ? _tbs_7__config.settings->re_encrypt : _tbs_7__config.re_encrypt)) { if ((_tbs_7__config.settings ? _tbs_7__config.settings->re_enetrant : _tbs_7__config.re_enetrant)) { if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { pthread_mutex_lock(&_tbs_7__section_lock); } if (_tbs_7__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { pthread_mutex_unlock(&_tbs_7__section_lock); } } else if ((_tbs_7__config.settings ? _tbs_7__config.settings->thread_safe : _tbs_7__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_7__section_lock); } } _tbs_7__protected_exp_res; }); }), ({ const _tbs_section_config _tbs_8__config = ({
               
                (((_tbs_section_config) { thread_safe: 
                               1
                               , re_encrypt: 
                               1
                               , re_enetrant: 
                               1
                               , keygen: &tbs_keygen_default, settings: 
                               ((void *)0)
                               , }));
                }); (void)&&_tbs_8__section_start; (void)&&_tbs_8__section_end; ({ static pthread_mutex_t _tbs_8__section_lock = 
                               { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
                               ; static int _tbs_8__access_count = 0; if (!(_tbs_8__config.settings ? _tbs_8__config.settings->re_encrypt : _tbs_8__config.re_encrypt)) { static 
                               _Bool 
                               _tbs_8__initialized = 
                               0
                               ; if (!_tbs_8__initialized) { if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { pthread_mutex_lock(&_tbs_8__section_lock); } if (!_tbs_8__initialized) { _tbs_8__initialized = 
                               1
                               ; do { do { ; } while (0);; } while (0); } if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { pthread_mutex_unlock(&_tbs_8__section_lock); } } } else if ((_tbs_8__config.settings ? _tbs_8__config.settings->re_enetrant : _tbs_8__config.re_enetrant)) { if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { pthread_mutex_lock(&_tbs_8__section_lock); } if (_tbs_8__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { pthread_mutex_unlock(&_tbs_8__section_lock); } } } else if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { pthread_mutex_lock(&_tbs_8__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_8__protected_exp_res = (({ do { _tbs_8__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_8__enc_exp_res = ((3)); do { ; } while (0); do { _tbs_8__section_end: do { ; } while (0);; } while (0); _tbs_8__enc_exp_res; })); if ((_tbs_8__config.settings ? _tbs_8__config.settings->re_encrypt : _tbs_8__config.re_encrypt)) { if ((_tbs_8__config.settings ? _tbs_8__config.settings->re_enetrant : _tbs_8__config.re_enetrant)) { if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { pthread_mutex_lock(&_tbs_8__section_lock); } if (_tbs_8__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { pthread_mutex_unlock(&_tbs_8__section_lock); } } else if ((_tbs_8__config.settings ? _tbs_8__config.settings->thread_safe : _tbs_8__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_8__section_lock); } } _tbs_8__protected_exp_res; }); }), ({ const _tbs_section_config _tbs_9__config = ({
               
                (((_tbs_section_config) { thread_safe: 
                                               1
                                               , re_encrypt: 
                                               1
                                               , re_enetrant: 
                                               1
                                               , keygen: &tbs_keygen_default, settings: 
                                               ((void *)0)
                                               , }));
                }); (void)&&_tbs_9__section_start; (void)&&_tbs_9__section_end; ({ static pthread_mutex_t _tbs_9__section_lock = 
                                               { { 0, 0, 0, 0, 0, 0, 0, { 0, 0 } } }
                                               ; static int _tbs_9__access_count = 0; if (!(_tbs_9__config.settings ? _tbs_9__config.settings->re_encrypt : _tbs_9__config.re_encrypt)) { static 
                                               _Bool 
                                               _tbs_9__initialized = 
                                               0
                                               ; if (!_tbs_9__initialized) { if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { pthread_mutex_lock(&_tbs_9__section_lock); } if (!_tbs_9__initialized) { _tbs_9__initialized = 
                                               1
                                               ; do { do { ; } while (0);; } while (0); } if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { pthread_mutex_unlock(&_tbs_9__section_lock); } } } else if ((_tbs_9__config.settings ? _tbs_9__config.settings->re_enetrant : _tbs_9__config.re_enetrant)) { if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { pthread_mutex_lock(&_tbs_9__section_lock); } if (_tbs_9__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { pthread_mutex_unlock(&_tbs_9__section_lock); } } } else if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { pthread_mutex_lock(&_tbs_9__section_lock); do { do { ; } while (0);; } while (0); } const __auto_type _tbs_9__protected_exp_res = (({ do { _tbs_9__section_start: do { ; } while (0);; } while (0); const __auto_type _tbs_9__enc_exp_res = ((1 + 3)); do { ; } while (0); do { _tbs_9__section_end: do { ; } while (0);; } while (0); _tbs_9__enc_exp_res; })); if ((_tbs_9__config.settings ? _tbs_9__config.settings->re_encrypt : _tbs_9__config.re_encrypt)) { if ((_tbs_9__config.settings ? _tbs_9__config.settings->re_enetrant : _tbs_9__config.re_enetrant)) { if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { pthread_mutex_lock(&_tbs_9__section_lock); } if (_tbs_9__access_count++ == 0) { do { do { ; } while (0);; } while (0); } if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { pthread_mutex_unlock(&_tbs_9__section_lock); } } else if ((_tbs_9__config.settings ? _tbs_9__config.settings->thread_safe : _tbs_9__config.thread_safe)) { do { do { ; } while (0);; } while (0); pthread_mutex_unlock(&_tbs_9__section_lock); } } _tbs_9__protected_exp_res; }); }));

}
