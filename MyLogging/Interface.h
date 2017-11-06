#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

#ifndef WIN32
#define KLOG_PREDICT_BRANCH_NOT_TAKEN(x) (__builtin_expect(x, 0))
#else
#define KLOG_PREDICT_BRANCH_NOT_TAKEN(x) x
#endif

#ifdef USE_LOG

#define LOG(pri) (logging::Logger( \
	(pri), \
        __FILE__, \
        __LINE__ \
    ).Reference())

#define LOG_IF(pri, expr) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(!(!(expr)))) ? \
    (void) 0 : \
    logging::LogMessageVoidify() & (logging::ExpressionLogger( \
	(pri), \
            __FILE__, \
            __LINE__, \
            #expr \
    ).Reference())


#define LOG_CHECK(expr) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(!(expr))) ? \
    (void) 0 : \
    logging::LogMessageVoidify() & logging::CheckLogger( \
        LOG_FATAL, \
        __FILE__, \
        __LINE__, \
        #expr \
    ).Reference()

#ifndef NDEBUG
#define DLOG(pri) LOG(pri)
#define DLOG_IF(pri, expr) LOG_IF(pri, expr)
#define DLOG_CHECK(expr) LOG_CHECK(expr)
#else // NDEBUG
#define DLOG(pri) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(0)) ? \
	(void) 0 : logging::LogMessageVoidify() & LOG(pri)
#define DLOG_IF(pri, expr) DLOG(pri)
#define DLOG_CHECK(expr) DLOG(LOG_FATAL)
#endif // NDEBUG

#else // USE_LOG

#define LOG(pri) !(KLOG_PREDICT_BRANCH_NOT_TAKEN(0)) ? \
    (void) 0 : \
    logging::LogMessageVoidify() & (logging::Logger( \
	(pri), \
        __FILE__, \
        __LINE__ \
    ).Reference())
#define LOG_IF(pri, expr) LOG(pri)
#define LOG_CHECK(expr) LOG(KLOG_FATAL)

#define DLOG(pri) LOG(pri)
#define DLOG_IF(pri, expr) LOG(pri)
#define DLOG_CHECK(expr) LOG(KLOG_FATAL)

#endif /// USE_KLOG

#endif
