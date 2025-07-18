/*==============================================================================
 * Created by Yaoyuan on 2019/3/9.
 * Copyright (C) 2019 Yaoyuan <ibireme@gmail.com>.
 *
 * Released under the MIT License:
 * https://github.com/ibireme/yyjson/blob/master/LICENSE
 *============================================================================*/

/** @file yyjson.h */

#ifndef YYJSON_H
#define YYJSON_H



/*==============================================================================
 * Header Files
 *============================================================================*/

//#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <float.h>



/*==============================================================================
 * Compile-time Options
 *============================================================================*/

/*
 Define as 1 to disable JSON reader if you don't need to parse JSON.
 
 This will disable these functions at compile-time:
    - yyjson_read_opts()
    - yyjson_read_file()
    - yyjson_read()
 
 This will reduce the binary size by about 60%.
 */
#ifndef YYJSON_DISABLE_READER
#endif

/*
 Define as 1 to disable JSON writer if you don't need to serialize JSON.
 
 This will disable these functions at compile-time:
    - yyjson_write()
    - yyjson_write_file()
    - yyjson_write_opts()
    - yyjson_val_write()
    - yyjson_val_write_file()
    - yyjson_val_write_opts()
    - yyjson_mut_write()
    - yyjson_mut_write_file()
    - yyjson_mut_write_opts()
    - yyjson_mut_val_write()
    - yyjson_mut_val_write_file()
    - yyjson_mut_val_write_opts()
 
 This will reduce the binary size by about 30%.
 */
#ifndef YYJSON_DISABLE_WRITER
#endif

/*
 Define as 1 to disable the fast floating-point number conversion in yyjson,
 and use libc's `strtod/snprintf` instead.
 
 This will reduce binary size by about 30%, but significantly slow down
 floating-point reading and writing speed.
 */
#ifndef YYJSON_DISABLE_FAST_FP_CONV
#endif

/*
 Define as 1 to disable non-standard JSON support at compile-time:
    - Reading and writing inf/nan literal, such as 'NaN', '-Infinity'.
    - Single line and multiple line comments.
    - Single trailing comma at the end of an object or array.
    - Invalid unicode in string value.
 
 This will also invalidate these run-time options:
    - YYJSON_READ_ALLOW_INF_AND_NAN
    - YYJSON_READ_ALLOW_COMMENTS
    - YYJSON_READ_ALLOW_TRAILING_COMMAS
    - YYJSON_READ_ALLOW_INVALID_UNICODE
    - YYJSON_WRITE_ALLOW_INF_AND_NAN
    - YYJSON_WRITE_ALLOW_INVALID_UNICODE
 
 This will reduce binary size by about 10%, and increase performance slightly.
 */
#ifndef YYJSON_DISABLE_NON_STANDARD
#endif

/*
 Define as 1 to disable unaligned memory access if target architecture does not
 support unaligned memory access (such as some embedded processors).
 
 If this value is not defined, yyjson will perform some automatic detection.
 The wrong definition of this option may cause some performance degradation,
 but will not cause run-time errors.
 */
#ifndef YYJSON_DISABLE_UNALIGNED_MEMORY_ACCESS
#endif

/* Define as 1 to export symbols when building this library as Windows DLL. */
#ifndef YYJSON_EXPORTS
#endif

/* Define as 1 to import symbols when using this library as Windows DLL. */
#ifndef YYJSON_IMPORTS
#endif

/* Define as 1 to include <stdint.h> for compiler which doesn't support C99. */
#ifndef YYJSON_HAS_STDINT_H
#endif

/* Define as 1 to include <stdbool.h> for compiler which doesn't support C99. */
#ifndef YYJSON_HAS_STDBOOL_H
#endif



/*==============================================================================
 * Compiler Macros
 *============================================================================*/

/** compiler version (MSVC) */
#ifdef _MSC_VER
#   define YYJSON_MSC_VER _MSC_VER
#else
#   define YYJSON_MSC_VER 0
#endif

/** compiler version (GCC) */
#ifdef __GNUC__
#   define YYJSON_GCC_VER __GNUC__
#else
#   define YYJSON_GCC_VER 0
#endif

/** C version (STDC) */
#if defined(__STDC__) && (__STDC__ >= 1) && defined(__STDC_VERSION__)
#   define YYJSON_STDC_VER __STDC_VERSION__
#else
#   define YYJSON_STDC_VER 0
#endif

/** C++ version */
#if defined(__cplusplus)
#   define YYJSON_CPP_VER __cplusplus
#else
#   define YYJSON_CPP_VER 0
#endif

/** compiler builtin check (since gcc 10.0, clang 2.6, icc 2021) */
#ifndef yyjson_has_builtin
#   ifdef __has_builtin
#       define yyjson_has_builtin(x) __has_builtin(x)
#   else
#       define yyjson_has_builtin(x) 0
#   endif
#endif

/** compiler attribute check (since gcc 5.0, clang 2.9, icc 17) */
#ifndef yyjson_has_attribute
#   ifdef __has_attribute
#       define yyjson_has_attribute(x) __has_attribute(x)
#   else
#       define yyjson_has_attribute(x) 0
#   endif
#endif

/** include check (since gcc 5.0, clang 2.7, icc 16, msvc 2017 15.3) */
#ifndef yyjson_has_include
#   ifdef __has_include
#       define yyjson_has_include(x) __has_include(x)
#   else
#       define yyjson_has_include(x) 0
#   endif
#endif

/** inline for compiler */
#ifndef yyjson_inline
#   if YYJSON_MSC_VER >= 1200
#       define yyjson_inline __forceinline
#   elif defined(_MSC_VER)
#       define yyjson_inline __inline
#   elif yyjson_has_attribute(always_inline) || YYJSON_GCC_VER >= 4
#       define yyjson_inline __inline__ __attribute__((always_inline))
#   elif defined(__clang__) || defined(__GNUC__)
#       define yyjson_inline __inline__
#   elif defined(__cplusplus) || YYJSON_STDC_VER >= 199901L
#       define yyjson_inline inline
#   else
#       define yyjson_inline
#   endif
#endif

/** noinline for compiler */
#ifndef yyjson_noinline
#   if YYJSON_MSC_VER >= 1400
#       define yyjson_noinline __declspec(noinline)
#   elif yyjson_has_attribute(noinline) || YYJSON_GCC_VER >= 4
#       define yyjson_noinline __attribute__((noinline))
#   else
#       define yyjson_noinline
#   endif
#endif

/** align for compiler */
#ifndef yyjson_align
#   if YYJSON_MSC_VER >= 1300
#       define yyjson_align(x) __declspec(align(x))
#   elif yyjson_has_attribute(aligned) || defined(__GNUC__)
#       define yyjson_align(x) __attribute__((aligned(x)))
#   elif YYJSON_CPP_VER >= 201103L
#       define yyjson_align(x) alignas(x)
#   else
#       define yyjson_align(x)
#   endif
#endif

/** likely for compiler */
#ifndef yyjson_likely
#   if yyjson_has_builtin(__builtin_expect) || YYJSON_GCC_VER >= 4
#       define yyjson_likely(expr) __builtin_expect(!!(expr), 1)
#   else
#       define yyjson_likely(expr) (expr)
#   endif
#endif

/** unlikely for compiler */
#ifndef yyjson_unlikely
#   if yyjson_has_builtin(__builtin_expect) || YYJSON_GCC_VER >= 4
#       define yyjson_unlikely(expr) __builtin_expect(!!(expr), 0)
#   else
#       define yyjson_unlikely(expr) (expr)
#   endif
#endif

/** function export */
#ifndef yyjson_api
#   if defined(_WIN32)
#       if defined(YYJSON_EXPORTS) && YYJSON_EXPORTS
#           define yyjson_api __declspec(dllexport)
#       elif defined(YYJSON_IMPORTS) && YYJSON_IMPORTS
#           define yyjson_api __declspec(dllimport)
#       else
#           define yyjson_api
#       endif
#   elif yyjson_has_attribute(visibility) || YYJSON_GCC_VER >= 4
#       define yyjson_api __attribute__((visibility("default")))
#   else
#       define yyjson_api
#   endif
#endif

/** inline function export */
#ifndef yyjson_api_inline
#   define yyjson_api_inline static yyjson_inline
#endif

/** stdint (C89 compatible) */
#if (defined(YYJSON_HAS_STDINT_H) && YYJSON_HAS_STDINT_H) || \
    YYJSON_MSC_VER >= 1600 || YYJSON_STDC_VER >= 199901L || \
    defined(_STDINT_H) || defined(_STDINT_H_) || \
    defined(__CLANG_STDINT_H) || defined(_STDINT_H_INCLUDED) || \
    yyjson_has_include(<stdint.h>)
#   include <stdint.h>
#elif defined(_MSC_VER)
#   if _MSC_VER < 1300
        typedef signed char         int8_t;
        typedef signed short        int16_t;
        typedef signed int          int32_t;
        typedef unsigned char       uint8_t;
        typedef unsigned short      uint16_t;
        typedef unsigned int        uint32_t;
        typedef signed __int64      int64_t;
        typedef unsigned __int64    uint64_t;
#   else
        typedef signed __int8       int8_t;
        typedef signed __int16      int16_t;
        typedef signed __int32      int32_t;
        typedef unsigned __int8     uint8_t;
        typedef unsigned __int16    uint16_t;
        typedef unsigned __int32    uint32_t;
        typedef signed __int64      int64_t;
        typedef unsigned __int64    uint64_t;
#   endif
#else
#   if UCHAR_MAX == 0xFFU
        typedef signed char     int8_t;
        typedef unsigned char   uint8_t;
#   else
#       error cannot find 8-bit integer type
#   endif
#   if USHRT_MAX == 0xFFFFU
        typedef unsigned short  uint16_t;
        typedef signed short    int16_t;
#   elif UINT_MAX == 0xFFFFU
        typedef unsigned int    uint16_t;
        typedef signed int      int16_t;
#   else
#       error cannot find 16-bit integer type
#   endif
#   if UINT_MAX == 0xFFFFFFFFUL
        typedef unsigned int    uint32_t;
        typedef signed int      int32_t;
#   elif ULONG_MAX == 0xFFFFFFFFUL
        typedef unsigned long   uint32_t;
        typedef signed long     int32_t;
#   elif USHRT_MAX == 0xFFFFFFFFUL
        typedef unsigned short  uint32_t;
        typedef signed short    int32_t;
#   else
#       error cannot find 32-bit integer type
#   endif
#   if defined(__INT64_TYPE__) && defined(__UINT64_TYPE__)
        typedef __INT64_TYPE__  int64_t;
        typedef __UINT64_TYPE__ uint64_t;
#   elif defined(__GNUC__) || defined(__clang__)
#       if !defined(_SYS_TYPES_H) && !defined(__int8_t_defined)
        __extension__ typedef long long             int64_t;
#       endif
        __extension__ typedef unsigned long long    uint64_t;
#   elif defined(_LONG_LONG) || defined(__MWERKS__) || defined(_CRAYC) || \
        defined(__SUNPRO_C) || defined(__SUNPRO_CC)
        typedef long long           int64_t;
        typedef unsigned long long  uint64_t;
#   elif (defined(__BORLANDC__) && __BORLANDC__ > 0x460) || \
        defined(__WATCOM_INT64__) || defined (__alpha) || defined (__DECC)
        typedef __int64             int64_t;
        typedef unsigned __int64    uint64_t;
#   else
#       error cannot find 64-bit integer type
#   endif
#endif

/** stdbool (C89 compatible) */
#if (defined(YYJSON_HAS_STDBOOL_H) && YYJSON_HAS_STDBOOL_H) || \
    (yyjson_has_include(<stdbool.h>) && !defined(__STRICT_ANSI__)) || \
    YYJSON_MSC_VER >= 1800 || YYJSON_STDC_VER >= 199901L
#   include <stdbool.h>
#elif !defined(__bool_true_false_are_defined)
#   define __bool_true_false_are_defined 1
#   if defined(__cplusplus)
#       if defined(__GNUC__) && !defined(__STRICT_ANSI__)
#           define _Bool bool
#           if __cplusplus < 201103L
#               define bool bool
#               define false false
#               define true true
#           endif
#       endif
#   else
#       define bool unsigned char
#       define true 1
#       define false 0
#   endif
#endif

/** char bit check */
#if defined(CHAR_BIT)
#   if CHAR_BIT != 8
#       error non 8-bit char is not supported
#   endif
#endif



/*==============================================================================
 * Compile Hint Begin
 *============================================================================*/

/* extern "C" begin */
#ifdef __cplusplus
extern "C" {
#endif

/* warning suppress begin */
#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-function"
#   pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#   if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#   pragma GCC diagnostic push
#   endif
#   pragma GCC diagnostic ignored "-Wunused-function"
#   pragma GCC diagnostic ignored "-Wunused-parameter"
#elif defined(_MSC_VER)
#   pragma warning(push)
#   pragma warning(disable:4800) /* 'int': forcing value to 'true' or 'false' */
#endif



/*==============================================================================
 * Version
 *============================================================================*/

/** The major version of yyjson. */
#define YYJSON_VERSION_MAJOR  0

/** The minor version of yyjson. */
#define YYJSON_VERSION_MINOR  5

/** The patch version of yyjson. */
#define YYJSON_VERSION_PATCH  1

/** The version of yyjson in hex: (major << 16) | (minor << 8) | (patch). */
#define YYJSON_VERSION_HEX    0x000501

/** The version string of yyjson. */
#define YYJSON_VERSION_STRING "0.5.1"

/** The version of yyjson in hex, same as `YYJSON_VERSION_HEX`. */
yyjson_api uint32_t yyjson_version(void);



/*==============================================================================
 * JSON Types
 *============================================================================*/

/** Type of JSON value (3 bit). */
typedef uint8_t yyjson_type;
#define YYJSON_TYPE_NONE        ((uint8_t)0)        /* _____000 */
#define YYJSON_TYPE_RAW         ((uint8_t)1)        /* _____001 */
#define YYJSON_TYPE_NULL        ((uint8_t)2)        /* _____010 */
#define YYJSON_TYPE_BOOL        ((uint8_t)3)        /* _____011 */
#define YYJSON_TYPE_NUM         ((uint8_t)4)        /* _____100 */
#define YYJSON_TYPE_STR         ((uint8_t)5)        /* _____101 */
#define YYJSON_TYPE_ARR         ((uint8_t)6)        /* _____110 */
#define YYJSON_TYPE_OBJ         ((uint8_t)7)        /* _____111 */

/** Subtype of JSON value (2 bit). */
typedef uint8_t yyjson_subtype;
#define YYJSON_SUBTYPE_NONE     ((uint8_t)(0 << 3)) /* ___00___ */
#define YYJSON_SUBTYPE_FALSE    ((uint8_t)(0 << 3)) /* ___00___ */
#define YYJSON_SUBTYPE_TRUE     ((uint8_t)(1 << 3)) /* ___01___ */
#define YYJSON_SUBTYPE_UINT     ((uint8_t)(0 << 3)) /* ___00___ */
#define YYJSON_SUBTYPE_SINT     ((uint8_t)(1 << 3)) /* ___01___ */
#define YYJSON_SUBTYPE_REAL     ((uint8_t)(2 << 3)) /* ___10___ */

/** Mask and bits of JSON value. */
#define YYJSON_TYPE_MASK        ((uint8_t)0x07)     /* _____111 */
#define YYJSON_TYPE_BIT         ((uint8_t)3)
#define YYJSON_SUBTYPE_MASK     ((uint8_t)0x18)     /* ___11___ */
#define YYJSON_SUBTYPE_BIT      ((uint8_t)2)
#define YYJSON_RESERVED_MASK    ((uint8_t)0xE0)     /* 111_____ */
#define YYJSON_RESERVED_BIT     ((uint8_t)3)
#define YYJSON_TAG_MASK         ((uint8_t)0xFF)     /* 11111111 */
#define YYJSON_TAG_BIT          ((uint8_t)8)

/** Padding size for JSON reader. */
#define YYJSON_PADDING_SIZE     4



/*==============================================================================
 * Allocator
 *============================================================================*/

/**
 A memory allocator.
 
 Typically you don't need to use it, unless you want to customize your own
 memory allocator.
 */
typedef struct yyjson_alc {
    /** Same as libc's malloc(), should not be NULL. */
   // void *(*malloc)(void *ctx, size_t size);
    void* (*yyjson_malloc)(void* ctx, size_t size);
    /** Same as libc's realloc(), should not be NULL. */
    //void *(*realloc)(void *ctx, void *ptr, size_t size);
    void* (*yyjson_realloc)(void* ctx, void* ptr, size_t size);
    /** Same as libc's free(), should not be NULL. */
    //void (*free)(void *ctx, void *ptr);
    void (*yyjson_free)(void* ctx, void* ptr);
    /** A context for malloc/realloc/free, can be NULL. */
    void *ctx;
} yyjson_alc;

/**
 A pool allocator uses fixed length pre-allocated memory.
 
 This allocator may used to avoid malloc()/memmove() calls. The pre-allocated
 memory should be held by the caller. The upper limit of memory required to
 read JSON can be calculated using the yyjson_read_max_memory_usage() function,
 but the memory required to write JSON cannot be calculated directly.
 
 This is not a general-purpose allocator, and should only be used to read or
 write single JSON document.
 
 @param alc The allocator to be initialized.
    If this parameter is NULL, the function will fail and return false.
    If `buf` or `size` is invalid, this parameter is left unmodified.
 @param buf The buffer memory for this allocator.
    If this parameter is NULL, the function will fail and return false.
 @param size The size of `buf`, in bytes.
    If this parameter is less than 8 words (32/64 bytes on 32/64-bit OS), the
    function will fail and return false.
 @return true if the `alc` has been successfully initialized.
 
 @par Example
 @code
    // parse JSON with stack memory
    char buf[1024];
    yyjson_alc alc;
    yyjson_alc_pool_init(&alc, buf, 1024);
    
    const char *json = "{\"name\":\"Helvetica\",\"size\":16}"
    yyjson_doc *doc = yyjson_read_opts(json, strlen(json), 0, &alc, NULL);
    // the memory of `doc` is on the stack
 @endcode
 */
yyjson_api bool yyjson_alc_pool_init(yyjson_alc *alc, void *buf, size_t size);



/*==============================================================================
 * JSON Structure
 *============================================================================*/

/**
 An immutable document for reading JSON.
 This document holds memory for all its JSON values and strings. When it is no
 longer used, the user should call yyjson_doc_free() to free its memory.
 */
typedef struct yyjson_doc yyjson_doc;

/**
 An immutable value for reading JSON.
 A JSON Value has the same lifetime as its document. The memory is held by its
 document and and cannot be freed alone.
 */
typedef struct yyjson_val yyjson_val;

/**
 A mutable document for building JSON.
 This document holds memory for all its JSON values and strings. When it is no
 longer used, the user should call yyjson_mut_doc_free() to free its memory.
 */
typedef struct yyjson_mut_doc yyjson_mut_doc;

/**
 A mutable value for building JSON.
 A JSON Value has the same lifetime as its document. The memory is held by its
 document and and cannot be freed alone.
 */
typedef struct yyjson_mut_val yyjson_mut_val;



/*==============================================================================
 * JSON Reader API
 *============================================================================*/

/** Run-time options for JSON reader. */
typedef uint32_t yyjson_read_flag;

/** Default option (RFC 8259 compliant):
    - Read positive integer as uint64_t.
    - Read negative integer as int64_t.
    - Read floating-point number as double with round-to-nearest mode.
    - Read integer which cannot fit in uint64_t or int64_t as double.
    - Report error if real number is infinity.
    - Report error if string contains invalid UTF-8 character or BOM.
    - Report error on trailing commas, comments, inf and nan literals. */
static const yyjson_read_flag YYJSON_READ_NOFLAG                = 0 << 0;

/** Read the input data in-situ.
    This option allows the reader to modify and use input data to store string
    values, which can increase reading speed slightly.
    The caller should hold the input data before free the document.
    The input data must be padded by at least `YYJSON_PADDING_SIZE` bytes.
    For example: "[1,2]" should be "[1,2]\0\0\0\0", length should be 5. */
static const yyjson_read_flag YYJSON_READ_INSITU                = 1 << 0;

/** Stop when done instead of issuing an error if there's additional content
    after a JSON document. This option may be used to parse small pieces of JSON
    in larger data, such as `NDJSON`. */
static const yyjson_read_flag YYJSON_READ_STOP_WHEN_DONE        = 1 << 1;

/** Allow single trailing comma at the end of an object or array,
    such as [1,2,3,] {"a":1,"b":2,} (non-standard). */
static const yyjson_read_flag YYJSON_READ_ALLOW_TRAILING_COMMAS = 1 << 2;

/** Allow C-style single line and multiple line comments (non-standard). */
static const yyjson_read_flag YYJSON_READ_ALLOW_COMMENTS        = 1 << 3;

/** Allow inf/nan number and literal, case-insensitive,
    such as 1e999, NaN, inf, -Infinity (non-standard). */
static const yyjson_read_flag YYJSON_READ_ALLOW_INF_AND_NAN     = 1 << 4;

/** Read number as raw string (value with YYJSON_TYPE_RAW type),
    inf/nan literal is also read as raw with `ALLOW_INF_AND_NAN` flag. */
static const yyjson_read_flag YYJSON_READ_NUMBER_AS_RAW         = 1 << 5;

/** Allow reading invalid unicode when parsing string values (non-standard).
    Invalid characters will be allowed to appear in the string values, but
    invalid escape sequences will still be reported as errors.
    This flag does not affect the performance of correctly encoded strings.
    
    @warning Strings in JSON values may contain incorrect encoding when this
    option is used, you need to handle these strings carefully to avoid security
    risks. */
static const yyjson_read_flag YYJSON_READ_ALLOW_INVALID_UNICODE = 1 << 6;



/** Result code for JSON reader. */
typedef uint32_t yyjson_read_code;

/** Success, no error. */
static const yyjson_read_code YYJSON_READ_SUCCESS                       = 0;

/** Invalid parameter, such as NULL string or invalid file path. */
static const yyjson_read_code YYJSON_READ_ERROR_INVALID_PARAMETER       = 1;

/** Memory allocation failure occurs. */
static const yyjson_read_code YYJSON_READ_ERROR_MEMORY_ALLOCATION       = 2;

/** Input JSON string is empty. */
static const yyjson_read_code YYJSON_READ_ERROR_EMPTY_CONTENT           = 3;

/** Unexpected content after document, such as "[1]#". */
static const yyjson_read_code YYJSON_READ_ERROR_UNEXPECTED_CONTENT      = 4;

/** Unexpected ending, such as "[123". */
static const yyjson_read_code YYJSON_READ_ERROR_UNEXPECTED_END          = 5;

/** Unexpected character inside the document, such as "[#]". */
static const yyjson_read_code YYJSON_READ_ERROR_UNEXPECTED_CHARACTER    = 6;

/** Invalid JSON structure, such as "[1,]". */
static const yyjson_read_code YYJSON_READ_ERROR_JSON_STRUCTURE          = 7;

/** Invalid comment, such as unclosed multi-line comment. */
static const yyjson_read_code YYJSON_READ_ERROR_INVALID_COMMENT         = 8;

/** Invalid number, such as "123.e12", "000". */
static const yyjson_read_code YYJSON_READ_ERROR_INVALID_NUMBER          = 9;

/** Invalid string, such as invalid escaped character inside a string. */
static const yyjson_read_code YYJSON_READ_ERROR_INVALID_STRING          = 10;

/** Invalid JSON literal, such as "truu". */
static const yyjson_read_code YYJSON_READ_ERROR_LITERAL                 = 11;

/** Failed to open a file. */
static const yyjson_read_code YYJSON_READ_ERROR_FILE_OPEN               = 12;

/** Failed to read a file. */
static const yyjson_read_code YYJSON_READ_ERROR_FILE_READ               = 13;

/** Error information for JSON reader. */
typedef struct yyjson_read_err {
    /** Error code, see `yyjson_read_code` for all possible values. */
    yyjson_read_code code;
    /** Error message, constant, no need to free (NULL if success). */
    const char *msg;
    /** Error byte position for input data (0 if success). */
    size_t pos;
} yyjson_read_err;



/**
 Read JSON with options.
 
 This function is thread-safe when:
 1. The `dat` is not modified by other threads.
 2. The `alc` is thread-safe or NULL.
 
 @param dat The JSON data (UTF-8 without BOM), null-terminator is not required.
    If this parameter is NULL, the function will fail and return NULL.
    The `dat` will not be modified without the flag `YYJSON_READ_INSITU`, so you
    can pass a `const char *` string and case it to `char *` if you don't use
    the `YYJSON_READ_INSITU` flag.
 @param len The length of JSON data in bytes.
    If this parameter is 0, the function will fail and return NULL.
 @param flg The JSON read options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON reader.
    Pass NULL to use the libc's default allocator.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return A new JSON document, or NULL if an error occurs.
    When it's no longer needed, it should be freed with yyjson_doc_free().
 */
yyjson_api yyjson_doc *yyjson_read_opts(char *dat,
                                        size_t len,
                                        yyjson_read_flag flg,
                                        const yyjson_alc *alc,
                                        yyjson_read_err *err);

/**
 Read a JSON file.
 
 This function is thread-safe when:
 1. The file is not modified by other threads.
 2. The `alc` is thread-safe or NULL.
 
 @param path The JSON file's path.
    If this path is NULL or invalid, the function will fail and return NULL.
 @param flg The JSON read options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON reader.
    Pass NULL to use the libc's default allocator.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return A new JSON document, or NULL if an error occurs.
    When it's no longer needed, it should be freed with yyjson_doc_free().
 
 @warning On 32-bit operating system, files larger than 2GB may fail to read.
 */
yyjson_api yyjson_doc *yyjson_read_file(const char *path,
                                        yyjson_read_flag flg,
                                        const yyjson_alc *alc,
                                        yyjson_read_err *err);

/**
 Read a JSON string.
 
 This function is thread-safe.
 
 @param dat The JSON data (UTF-8 without BOM), null-terminator is not required.
    If this parameter is NULL, the function will fail and return NULL.
 @param len The length of JSON data in bytes.
    If this parameter is 0, the function will fail and return NULL.
 @param flg The JSON read options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @return A new JSON document, or NULL if an error occurs.
    When it's no longer needed, it should be freed with yyjson_doc_free().
 */
yyjson_api_inline yyjson_doc *yyjson_read(const char *dat,
                                          size_t len,
                                          yyjson_read_flag flg) {
    flg &= ~YYJSON_READ_INSITU; /* const string cannot be modified */
    return yyjson_read_opts((char *)dat, len, flg, NULL, NULL);
}

/**
 Returns the size of maximum memory usage to read a JSON data.
 
 You may use this value to avoid malloc() or calloc() call inside the reader
 to get better performance, or read multiple JSON with one piece of memory.
 
 @param len The length of JSON data in bytes.
 @param flg The JSON read options.
 @return The maximum memory size to read this JSON, or 0 if overflow.
 
 @par Example
 @code
    // read multiple JSON with same pre-allocated memory
    
    char *dat1, *dat2, *dat3; // JSON data
    size_t len1, len2, len3; // JSON length
    size_t max_len = MAX(len1, MAX(len2, len3));
    yyjson_doc *doc;
    
    // use one allocator for multiple JSON
    size_t size = yyjson_read_max_memory_usage(max_len, 0);
    void *buf = malloc(size);
    yyjson_alc alc;
    yyjson_alc_pool_init(&alc, buf, size);
    
    // no more alloc() or realloc() call during reading
    doc = yyjson_read_opts(dat1, len1, 0, &alc, NULL);
    yyjson_doc_free(doc);
    doc = yyjson_read_opts(dat2, len2, 0, &alc, NULL);
    yyjson_doc_free(doc);
    doc = yyjson_read_opts(dat3, len3, 0, &alc, NULL);
    yyjson_doc_free(doc);
    
    free(buf);
 @endcode
 @see yyjson_alc_pool_init()
 */
yyjson_api_inline size_t yyjson_read_max_memory_usage(size_t len,
                                                      yyjson_read_flag flg) {
    /*
     1. The max value count is (json_size / 2 + 1),
        for example: "[1,2,3,4]" size is 9, value count is 5.
     2. Some broken JSON may cost more memory during reading, but fail at end,
        for example: "[[[[[[[[".
     3. yyjson use 16 bytes per value, see struct yyjson_val.
     4. yyjson use dynamic memory with a growth factor of 1.5.
     
     The max memory size is (json_size / 2 * 16 * 1.5 + padding).
     */
    size_t mul = (size_t)12 + !(flg & YYJSON_READ_INSITU);
    size_t pad = 256;
    size_t max = (size_t)(~(size_t)0);
    if (flg & YYJSON_READ_STOP_WHEN_DONE) len = len < 256 ? 256 : len;
    if (len >= (max - pad - mul) / mul) return 0;
    return len * mul + pad;
}



/*==============================================================================
 * JSON Writer API
 *============================================================================*/

/** Run-time options for JSON writer. */
typedef uint32_t yyjson_write_flag;

/** Default option:
    - Write JSON minify.
    - Report error on inf or nan number.
    - Report error on invalid UTF-8 string.
    - Do not escape unicode or slash. */
static const yyjson_write_flag YYJSON_WRITE_NOFLAG                  = 0 << 0;

/** Write JSON pretty with 4 space indent. */
static const yyjson_write_flag YYJSON_WRITE_PRETTY                  = 1 << 0;

/** Escape unicode as `uXXXX`, make the output ASCII only. */
static const yyjson_write_flag YYJSON_WRITE_ESCAPE_UNICODE          = 1 << 1;

/** Escape '/' as '\/'. */
static const yyjson_write_flag YYJSON_WRITE_ESCAPE_SLASHES          = 1 << 2;

/** Write inf and nan number as 'Infinity' and 'NaN' literal (non-standard). */
static const yyjson_write_flag YYJSON_WRITE_ALLOW_INF_AND_NAN       = 1 << 3;

/** Write inf and nan number as null literal.
    This flag will override `YYJSON_WRITE_ALLOW_INF_AND_NAN` flag. */
static const yyjson_write_flag YYJSON_WRITE_INF_AND_NAN_AS_NULL     = 1 << 4;

/** Allow invalid unicode when encoding string values (non-standard).
    Invalid characters in string value will be copied byte by byte.
    If `YYJSON_WRITE_ESCAPE_UNICODE` flag is also set, invalid character will be
    escaped as `U+FFFD` (replacement character).
    This flag does not affect the performance of correctly encoded strings. */
static const yyjson_read_flag YYJSON_WRITE_ALLOW_INVALID_UNICODE    = 1 << 5;



/** Result code for JSON writer */
typedef uint32_t yyjson_write_code;

/** Success, no error. */
static const yyjson_write_code YYJSON_WRITE_SUCCESS                     = 0;

/** Invalid parameter, such as NULL document. */
static const yyjson_write_code YYJSON_WRITE_ERROR_INVALID_PARAMETER     = 1;

/** Memory allocation failure occurs. */
static const yyjson_write_code YYJSON_WRITE_ERROR_MEMORY_ALLOCATION     = 2;

/** Invalid value type in JSON document. */
static const yyjson_write_code YYJSON_WRITE_ERROR_INVALID_VALUE_TYPE    = 3;

/** NaN or Infinity number occurs. */
static const yyjson_write_code YYJSON_WRITE_ERROR_NAN_OR_INF            = 4;

/** Failed to open a file. */
static const yyjson_write_code YYJSON_WRITE_ERROR_FILE_OPEN             = 5;

/** Failed to write a file. */
static const yyjson_write_code YYJSON_WRITE_ERROR_FILE_WRITE            = 6;

/** Invalid unicode in string. */
static const yyjson_write_code YYJSON_WRITE_ERROR_INVALID_STRING        = 7;

/** Error information for JSON writer. */
typedef struct yyjson_write_err {
    /** Error code, see `yyjson_write_code` for all possible values. */
    yyjson_write_code code;
    /** Error message, constant, no need to free (NULL if success). */
    const char *msg;
} yyjson_write_err;



/*==============================================================================
 * JSON Document Writer API
 *============================================================================*/

/**
 Write a document to JSON string with options.
 
 This function is thread-safe when:
 The `alc` is thread-safe or NULL.
 
 @param doc The JSON document.
    If this doc is NULL or has no root, the function will fail and return false.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free() or alc->free().
 */
yyjson_api char *yyjson_write_opts(const yyjson_doc *doc,
                                   yyjson_write_flag flg,
                                   const yyjson_alc *alc,
                                   size_t *len,
                                   yyjson_write_err *err);

/**
 Write a document to JSON file with options.
 
 This function is thread-safe when:
 1. The file is not accessed by other threads.
 2. The `alc` is thread-safe or NULL.

 @param path The JSON file's path.
    If this path is NULL or invalid, the function will fail and return false.
    If this file is not empty, the content will be discarded.
 @param doc The JSON document.
    If this doc is NULL or has no root, the function will fail and return false.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return true if successful, false if an error occurs.
 
 @warning On 32-bit operating system, files larger than 2GB may fail to write.
 */
yyjson_api bool yyjson_write_file(const char *path,
                                  const yyjson_doc *doc,
                                  yyjson_write_flag flg,
                                  const yyjson_alc *alc,
                                  yyjson_write_err *err);

/**
 Write a document to JSON string.
 
 This function is thread-safe.
 
 @param doc The JSON document.
    If this doc is NULL or has no root, the function will fail and return false.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @return A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free().
 */
yyjson_api_inline char *yyjson_write(const yyjson_doc *doc,
                                     yyjson_write_flag flg,
                                     size_t *len) {
    return yyjson_write_opts(doc, flg, NULL, len, NULL);
}



/**
 Write a document to JSON string with options.
 
 This function is thread-safe when:
 1. The `doc` is not modified by other threads.
 2. The `alc` is thread-safe or NULL.

 @param doc The mutable JSON document.
    If this doc is NULL or has no root, the function will fail and return false.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free() or alc->free().
 */
yyjson_api char *yyjson_mut_write_opts(const yyjson_mut_doc *doc,
                                       yyjson_write_flag flg,
                                       const yyjson_alc *alc,
                                       size_t *len,
                                       yyjson_write_err *err);

/**
 Write a document to JSON file with options.
 
 This function is thread-safe when:
 1. The file is not accessed by other threads.
 2. The `doc` is not modified by other threads.
 3. The `alc` is thread-safe or NULL.
 
 @param path The JSON file's path.
    If this path is NULL or invalid, the function will fail and return false.
    If this file is not empty, the content will be discarded.
 @param doc The mutable JSON document.
    If this doc is NULL or has no root, the function will fail and return false.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return true if successful, false if an error occurs.
 
 @warning On 32-bit operating system, files larger than 2GB may fail to write.
 */
yyjson_api bool yyjson_mut_write_file(const char *path,
                                      const yyjson_mut_doc *doc,
                                      yyjson_write_flag flg,
                                      const yyjson_alc *alc,
                                      yyjson_write_err *err);

/**
 Write a document to JSON string.
 
 This function is thread-safe when:
 The `doc` is not is not modified by other threads.
 
 @param doc The JSON document.
    If this doc is NULL or has no root, the function will fail and return false.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @return A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free().
 */
yyjson_api_inline char *yyjson_mut_write(const yyjson_mut_doc *doc,
                                         yyjson_write_flag flg,
                                         size_t *len) {
    return yyjson_mut_write_opts(doc, flg, NULL, len, NULL);
}



/*==============================================================================
 * JSON Value Writer API
 *============================================================================*/

/**
 Write a value to JSON string with options.
 
 This function is thread-safe when:
 The `alc` is thread-safe or NULL.
 
 @param val The JSON root value.
    If this parameter is NULL, the function will fail and return NULL.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free() or alc->free().
 */
yyjson_api char *yyjson_val_write_opts(const yyjson_val *val,
                                       yyjson_write_flag flg,
                                       const yyjson_alc *alc,
                                       size_t *len,
                                       yyjson_write_err *err);

/**
 Write a value to JSON file with options.
 
 This function is thread-safe when:
 1. The file is not accessed by other threads.
 2. The `alc` is thread-safe or NULL.
 
 @param path The JSON file's path.
    If this path is NULL or invalid, the function will fail and return false.
    If this file is not empty, the content will be discarded.
 @param val The JSON root value.
    If this parameter is NULL, the function will fail and return NULL.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return true if successful, false if an error occurs.
 
 @warning On 32-bit operating system, files larger than 2GB may fail to write.
 */
yyjson_api bool yyjson_val_write_file(const char *path,
                                      const yyjson_val *val,
                                      yyjson_write_flag flg,
                                      const yyjson_alc *alc,
                                      yyjson_write_err *err);

/**
 Write a value to JSON string.
 
 This function is thread-safe.
 
 @param val The JSON root value.
    If this parameter is NULL, the function will fail and return NULL.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @return A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free().
 */
yyjson_api_inline char *yyjson_val_write(const yyjson_val *val,
                                         yyjson_write_flag flg,
                                         size_t *len) {
    return yyjson_val_write_opts(val, flg, NULL, len, NULL);
}

/**
 Write a value to JSON string with options.
 
 This function is thread-safe when:
 1. The `val` is not modified by other threads.
 2. The `alc` is thread-safe or NULL.
 
 @param val The mutable JSON root value.
    If this parameter is NULL, the function will fail and return NULL.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return  A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free() or alc->free().
 */
yyjson_api char *yyjson_mut_val_write_opts(const yyjson_mut_val *val,
                                           yyjson_write_flag flg,
                                           const yyjson_alc *alc,
                                           size_t *len,
                                           yyjson_write_err *err);

/**
 Write a value to JSON file with options.
 
 This function is thread-safe when:
 1. The file is not accessed by other threads.
 2. The `val` is not modified by other threads.
 3. The `alc` is thread-safe or NULL.
 
 @param path The JSON file's path.
    If this path is NULL or invalid, the function will fail and return false.
    If this file is not empty, the content will be discarded.
 @param val The mutable JSON root value.
    If this parameter is NULL, the function will fail and return NULL.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param alc The memory allocator used by JSON writer.
    Pass NULL to use the libc's default allocator.
 @param err A pointer to receive error information.
    Pass NULL if you don't need error information.
 @return true if successful, false if an error occurs.
 
 @warning On 32-bit operating system, files larger than 2GB may fail to write.
 */
yyjson_api bool yyjson_mut_val_write_file(const char *path,
                                          const yyjson_mut_val *val,
                                          yyjson_write_flag flg,
                                          const yyjson_alc *alc,
                                          yyjson_write_err *err);

/**
 Write a value to JSON string.
 
 This function is thread-safe when:
 The `val` is not is not modified by other threads.
 
 @param val The JSON root value.
    If this parameter is NULL, the function will fail and return NULL.
 @param flg The JSON write options.
    Multiple options can be combined with `|` operator. 0 means no options.
 @param len A pointer to receive output length in bytes.
    Pass NULL if you don't need length information.
 @return A new JSON string, or NULL if an error occurs.
    This string is encoded as UTF-8 with a null-terminator.
    When it's no longer needed, it should be freed with free().
 */
yyjson_api_inline char *yyjson_mut_val_write(const yyjson_mut_val *val,
                                             yyjson_write_flag flg,
                                             size_t *len) {
    return yyjson_mut_val_write_opts(val, flg, NULL, len, NULL);
}



/*==============================================================================
 * JSON Document API
 *============================================================================*/

/** Returns the root value of this JSON document.
    Returns NULL if `doc` is NULL. */
yyjson_api_inline yyjson_val *yyjson_doc_get_root(yyjson_doc *doc);

/** Returns read size of input JSON data.
    Returns 0 if `doc` is NULL.
    For example: the read size of "[1,2,3]" is 7 bytes.  */
yyjson_api_inline size_t yyjson_doc_get_read_size(yyjson_doc *doc);

/** Returns total value count in this JSON document.
    Returns 0 if `doc` is NULL.
    For example: the value count of "[1,2,3]" is 4. */
yyjson_api_inline size_t yyjson_doc_get_val_count(yyjson_doc *doc);

/** Release the JSON document and free the memory.
    After calling this function, the `doc` and all values from the `doc` are no
    longer available. This function will do nothing if the `doc` is NULL. */
yyjson_api_inline void yyjson_doc_free(yyjson_doc *doc);



/*==============================================================================
 * JSON Value Type API
 *============================================================================*/

/** Returns whether the JSON value is raw.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_raw(yyjson_val *val);

/** Returns whether the JSON value is `null`.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_null(yyjson_val *val);

/** Returns whether the JSON value is `true`.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_true(yyjson_val *val);

/** Returns whether the JSON value is `false`.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_false(yyjson_val *val);

/** Returns whether the JSON value is bool (true/false).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_bool(yyjson_val *val);

/** Returns whether the JSON value is unsigned integer (uint64_t).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_uint(yyjson_val *val);

/** Returns whether the JSON value is signed integer (int64_t).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_sint(yyjson_val *val);

/** Returns whether the JSON value is integer (uint64_t/int64_t).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_int(yyjson_val *val);

/** Returns whether the JSON value is real number (double).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_real(yyjson_val *val);

/** Returns whether the JSON value is number (uint64_t/int64_t/double).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_num(yyjson_val *val);

/** Returns whether the JSON value is string.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_str(yyjson_val *val);

/** Returns whether the JSON value is array.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_arr(yyjson_val *val);

/** Returns whether the JSON value is object.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_obj(yyjson_val *val);

/** Returns whether the JSON value is container (array/object).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_is_ctn(yyjson_val *val);



/*==============================================================================
 * JSON Value Content API
 *============================================================================*/

/** Returns the JSON value's type.
    Returns YYJSON_TYPE_NONE if `val` is NULL. */
yyjson_api_inline yyjson_type yyjson_get_type(yyjson_val *val);

/** Returns the JSON value's subtype.
    Returns YYJSON_SUBTYPE_NONE if `val` is NULL. */
yyjson_api_inline yyjson_subtype yyjson_get_subtype(yyjson_val *val);

/** Returns the JSON value's tag.
    Returns 0 if `val` is NULL. */
yyjson_api_inline uint8_t yyjson_get_tag(yyjson_val *val);

/** Returns the JSON value's type description.
    The return value should be one of these strings: "raw", "null", "string",
    "array", "object", "true", "false", "uint", "sint", "real", "unknown". */
yyjson_api_inline const char *yyjson_get_type_desc(yyjson_val *val);

/** Returns the content if the value is raw.
    Returns NULL if `val` is NULL or type is not raw. */
yyjson_api_inline const char *yyjson_get_raw(yyjson_val *val);

/** Returns the content if the value is bool.
    Returns NULL if `val` is NULL or type is not bool. */
yyjson_api_inline bool yyjson_get_bool(yyjson_val *val);

/** Returns the content and cast to uint64_t.
    Returns 0 if `val` is NULL or type is not integer(sint/uint). */
yyjson_api_inline uint64_t yyjson_get_uint(yyjson_val *val);

/** Returns the content and cast to int64_t.
    Returns 0 if `val` is NULL or type is not integer(sint/uint). */
yyjson_api_inline int64_t yyjson_get_sint(yyjson_val *val);

/** Returns the content and cast to int.
    Returns 0 if `val` is NULL or type is not integer(sint/uint). */
yyjson_api_inline int yyjson_get_int(yyjson_val *val);

/** Returns the content if the value is real number, or 0.0 on error.
    Returns 0.0 if `val` is NULL or type is not real(double). */
yyjson_api_inline double yyjson_get_real(yyjson_val *val);

/** Returns the content if the value is string.
    Returns NULL if `val` is NULL or type is not string. */
yyjson_api_inline const char *yyjson_get_str(yyjson_val *val);

/** Returns the content length (string length, array size, object size.
    Returns 0 if `val` is NULL or type is not string/array/object. */
yyjson_api_inline size_t yyjson_get_len(yyjson_val *val);

/** Returns whether the JSON value is equals to a string.
    Returns false if input is NULL or type is not string. */
yyjson_api_inline bool yyjson_equals_str(yyjson_val *val, const char *str);

/** Returns whether the JSON value is equals to a string.
    The `str` should be a UTF-8 string, null-terminator is not required.
    Returns false if input is NULL or type is not string. */
yyjson_api_inline bool yyjson_equals_strn(yyjson_val *val, const char *str,
                                          size_t len);

/** Returns whether two JSON values are equal (deep compare).
    Returns false if input is NULL. */
yyjson_api_inline bool yyjson_equals(yyjson_val *lhs, yyjson_val *rhs);



/*==============================================================================
 * JSON Array API
 *============================================================================*/

/** Returns the number of elements in this array.
    Returns 0 if `arr` is NULL or type is not array. */
yyjson_api_inline size_t yyjson_arr_size(yyjson_val *arr);

/** Returns the element at the specified position in this array.
    Returns NULL if array is NULL/empty or the index is out of bounds.
    @warning This function takes a linear search time if array is not flat.
        For example: [1,{},3] is flat, [1,[2],3] is not flat. */
yyjson_api_inline yyjson_val *yyjson_arr_get(yyjson_val *arr, size_t idx);

/** Returns the first element of this array.
    Returns NULL if `arr` is NULL/empty or type is not array. */
yyjson_api_inline yyjson_val *yyjson_arr_get_first(yyjson_val *arr);

/** Returns the last element of this array.
    Returns NULL if `arr` is NULL/empty or type is not array.
    @warning This function takes a linear search time if array is not flat.
        For example: [1,{},3] is flat, [1,[2],3] is not flat.*/
yyjson_api_inline yyjson_val *yyjson_arr_get_last(yyjson_val *arr);



/*==============================================================================
 * JSON Array Iterator API
 *============================================================================*/

/**
 A JSON array iterator.
 
 @par Example
 @code
    yyjson_val *val;
    yyjson_arr_iter iter;
    yyjson_arr_iter_init(arr, &iter);
    while ((val = yyjson_arr_iter_next(&iter))) {
        your_func(val);
    }
 @endcode
 */
typedef struct yyjson_arr_iter yyjson_arr_iter;

/**
 Initialize an iterator for this array.
 
 @param arr The array to be iterated over.
    If this parameter is NULL or not an array, `iter` will be set to empty.
 @param iter The iterator to be initialized.
    If this parameter is NULL, the function will fail and return false.
 @return true if the `iter` has been successfully initialized.
 
 @note The iterator does not need to be destroyed.
 */
yyjson_api_inline bool yyjson_arr_iter_init(yyjson_val *arr,
                                            yyjson_arr_iter *iter);

/**
 Returns whether the iteration has more elements.
 If `iter` is NULL, this function will return false.
 */
yyjson_api_inline bool yyjson_arr_iter_has_next(yyjson_arr_iter *iter);

/**
 Returns the next element in the iteration, or NULL on end.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_val *yyjson_arr_iter_next(yyjson_arr_iter *iter);

/**
 Macro for iterating over an array.
 It works like iterator, but with a more intuitive API.
 
 @par Example
 @code
    size_t idx, max;
    yyjson_val *val;
    yyjson_arr_foreach(arr, idx, max, val) {
        your_func(idx, val);
    }
 @endcode
 */
#define yyjson_arr_foreach(arr, idx, max, val) \
    for ((idx) = 0, \
        (max) = yyjson_arr_size(arr), \
        (val) = yyjson_arr_get_first(arr); \
        (idx) < (max); \
        (idx)++, \
        (val) = unsafe_yyjson_get_next(val))



/*==============================================================================
 * JSON Object API
 *============================================================================*/

/** Returns the number of key-value pairs in this object.
    Returns 0 if `obj` is NULL or type is not object. */
yyjson_api_inline size_t yyjson_obj_size(yyjson_val *obj);

/** Returns the value to which the specified key is mapped.
    Returns NULL if this object contains no mapping for the key.
    Returns NULL if `obj/key` is NULL, or type is not object.
    
    The `key` should be a null-terminated UTF-8 string.
    
    @warning This function takes a linear search time. */
yyjson_api_inline yyjson_val *yyjson_obj_get(yyjson_val *obj, const char *key);

/** Returns the value to which the specified key is mapped.
    Returns NULL if this object contains no mapping for the key.
    Returns NULL if `obj/key` is NULL, or type is not object.
    
    The `key` should be a UTF-8 string, null-terminator is not required.
    The `key_len` should be the length of the key, in bytes.
    
    @warning This function takes a linear search time. */
yyjson_api_inline yyjson_val *yyjson_obj_getn(yyjson_val *obj, const char *key,
                                              size_t key_len);



/*==============================================================================
 * JSON Object Iterator API
 *============================================================================*/

/**
 A JSON object iterator.
 
 @par Example
 @code
    yyjson_val *key, *val;
    yyjson_obj_iter iter;
    yyjson_obj_iter_init(obj, &iter);
    while ((key = yyjson_obj_iter_next(&iter))) {
        val = yyjson_obj_iter_get_val(key);
        your_func(key, val);
    }
 @endcode
 
 If the ordering of the keys is known at compile-time, you can use this method
 to speed up value lookups:
 @code
    // {"k1":1, "k2": 3, "k3": 3}
    yyjson_val *key, *val;
    yyjson_obj_iter iter;
    yyjson_obj_iter_init(obj, &iter);
    yyjson_val *v1 = yyjson_obj_iter_get(&iter, "k1");
    yyjson_val *v3 = yyjson_obj_iter_get(&iter, "k3");
 @endcode
 @see yyjson_obj_iter_get() and yyjson_obj_iter_getn()
 */
typedef struct yyjson_obj_iter yyjson_obj_iter;

/**
 Initialize an iterator for this object.
 
 @param obj The object to be iterated over.
    If this parameter is NULL or not an object, `iter` will be set to empty.
 @param iter The iterator to be initialized.
    If this parameter is NULL, the function will fail and return false.
 @return true if the `iter` has been successfully initialized.
 
 @note The iterator does not need to be destroyed.
 */
yyjson_api_inline bool yyjson_obj_iter_init(yyjson_val *obj,
                                            yyjson_obj_iter *iter);

/**
 Returns whether the iteration has more elements.
 If `iter` is NULL, this function will return false.
 */
yyjson_api_inline bool yyjson_obj_iter_has_next(yyjson_obj_iter *iter);

/**
 Returns the next key in the iteration, or NULL on end.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_val *yyjson_obj_iter_next(yyjson_obj_iter *iter);

/**
 Returns the value for key inside the iteration.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_val *yyjson_obj_iter_get_val(yyjson_val *key);

/**
 Iterates to a specified key and returns the value.
 
 This function does the same thing as yyjson_obj_get(), but is much faster
 if the ordering of the keys is known at compile-time and you are using the same
 order to look up the values. If the key exists in this object, then the
 iterator will stop at the next key, otherwise the iterator will not change and
 NULL is returned.
 
 @param iter The object iterator, should not be NULL.
 @param key The key, should be a UTF-8 string with null-terminator.
 @return The value to which the specified key is mapped.
    NULL if this object contains no mapping for the key or input is invalid.
 
 @warning This function takes a linear search time if the key is not nearby.
 */
yyjson_api_inline yyjson_val *yyjson_obj_iter_get(yyjson_obj_iter *iter,
                                                  const char *key);

/**
 Iterates to a specified key and returns the value.

 This function does the same thing as yyjson_obj_getn(), but is much faster
 if the ordering of the keys is known at compile-time and you are using the same
 order to look up the values. If the key exists in this object, then the
 iterator will stop at the next key, otherwise the iterator will not change and
 NULL is returned.
 
 @param iter The object iterator, should not be NULL.
 @param key The key, should be a UTF-8 string, null-terminator is not required.
 @param key_len The the length of `key`, in bytes.
 @return The value to which the specified key is mapped.
    NULL if this object contains no mapping for the key or input is invalid.
 
 @warning This function takes a linear search time if the key is not nearby.
 */
yyjson_api_inline yyjson_val *yyjson_obj_iter_getn(yyjson_obj_iter *iter,
                                                   const char *key,
                                                   size_t key_len);

/**
 Macro for iterating over an object.
 It works like iterator, but with a more intuitive API.
 
 @par Example
 @code
    size_t idx, max;
    yyjson_val *key, *val;
    yyjson_obj_foreach(obj, idx, max, key, val) {
        your_func(key, val);
    }
 @endcode
 */
#define yyjson_obj_foreach(obj, idx, max, key, val) \
    for ((idx) = 0, \
        (max) = yyjson_obj_size(obj), \
        (key) = (obj) ? unsafe_yyjson_get_first(obj) : NULL, \
        (val) = (key) + 1; \
        (idx) < (max); \
        (idx)++, \
        (key) = unsafe_yyjson_get_next(val), \
        (val) = (key) + 1)



/*==============================================================================
 * Mutable JSON Document API
 *============================================================================*/

/** Returns the root value of this JSON document.
    Returns NULL if `doc` is NULL. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_doc_get_root(yyjson_mut_doc *doc);

/** Sets the root value of this JSON document.
    Pass NULL to clear root value of the document. */
yyjson_api_inline void yyjson_mut_doc_set_root(yyjson_mut_doc *doc,
                                               yyjson_mut_val *root);

/** Release the JSON document and free the memory.
    After calling this function, the `doc` and all values from the `doc` are no
    longer available. This function will do nothing if the `doc` is NULL.  */
yyjson_api void yyjson_mut_doc_free(yyjson_mut_doc *doc);

/** Creates and returns a new mutable JSON document, returns NULL on error.
    If allocator is NULL, the default allocator will be used. */
yyjson_api yyjson_mut_doc *yyjson_mut_doc_new(const yyjson_alc *alc);

/** Copies and returns a new mutable document from input, returns NULL on error.
    This makes a `deep-copy` on the immutable document.
    If allocator is NULL, the default allocator will be used. */
yyjson_api yyjson_mut_doc *yyjson_doc_mut_copy(yyjson_doc *doc,
                                               const yyjson_alc *alc);

/** Copies and returns a new mutable document from input, returns NULL on error.
    This makes a `deep-copy` on the mutable document.
    If allocator is NULL, the default allocator will be used. */
yyjson_api yyjson_mut_doc *yyjson_mut_doc_mut_copy(yyjson_mut_doc *doc,
                                                   const yyjson_alc *alc);

/** Copies and returns a new mutable value from input, returns NULL on error.
    This makes a `deep-copy` on the immutable value.
    The memory was managed by mutable document. */
yyjson_api yyjson_mut_val *yyjson_val_mut_copy(yyjson_mut_doc *doc,
                                               yyjson_val *val);

/** Copies and return a new mutable value from input, returns NULL on error,
    This makes a `deep-copy` on the mutable value.
    The memory was managed by mutable document.
    
    @warning This function is recursive and may cause a stack overflow
        if the object level is too deep. */
yyjson_api yyjson_mut_val *yyjson_mut_val_mut_copy(yyjson_mut_doc *doc,
                                                   yyjson_mut_val *val);



/*==============================================================================
 * Mutable JSON Value Type API
 *============================================================================*/

/** Returns whether the JSON value is raw.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_raw(yyjson_mut_val *val);

/** Returns whether the JSON value is `null`.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_null(yyjson_mut_val *val);

/** Returns whether the JSON value is `true`.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_true(yyjson_mut_val *val);

/** Returns whether the JSON value is `false`.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_false(yyjson_mut_val *val);

/** Returns whether the JSON value is bool (true/false).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_bool(yyjson_mut_val *val);

/** Returns whether the JSON value is unsigned integer (uint64_t).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_uint(yyjson_mut_val *val);

/** Returns whether the JSON value is signed integer (int64_t).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_sint(yyjson_mut_val *val);

/** Returns whether the JSON value is integer (uint64_t/int64_t).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_int(yyjson_mut_val *val);

/** Returns whether the JSON value is real number (double).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_real(yyjson_mut_val *val);

/** Returns whether the JSON value is number (uint/sint/real).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_num(yyjson_mut_val *val);

/** Returns whether the JSON value is string.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_str(yyjson_mut_val *val);

/** Returns whether the JSON value is array.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_arr(yyjson_mut_val *val);

/** Returns whether the JSON value is object.
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_obj(yyjson_mut_val *val);

/** Returns whether the JSON value is container (array/object).
    Returns false if `val` is NULL. */
yyjson_api_inline bool yyjson_mut_is_ctn(yyjson_mut_val *val);



/*==============================================================================
 * Mutable JSON Value Content API
 *============================================================================*/

/** Returns the JSON value's type.
    Returns YYJSON_TYPE_NONE if `val` is NULL. */
yyjson_api_inline yyjson_type yyjson_mut_get_type(yyjson_mut_val *val);

/** Returns the JSON value's subtype.
    Returns YYJSON_SUBTYPE_NONE if `val` is NULL. */
yyjson_api_inline yyjson_subtype yyjson_mut_get_subtype(yyjson_mut_val *val);

/** Returns the JSON value's tag.
    Returns 0 if `val` is NULL. */
yyjson_api_inline uint8_t yyjson_mut_get_tag(yyjson_mut_val *val);

/** Returns the JSON value's type description.
    The return value should be one of these strings: "raw", "null", "string",
    "array", "object", "true", "false", "uint", "sint", "real", "unknown". */
yyjson_api_inline const char *yyjson_mut_get_type_desc(yyjson_mut_val *val);

/** Returns the content if the value is raw.
    Returns NULL if `val` is NULL or type is not raw. */
yyjson_api_inline const char *yyjson_mut_get_raw(yyjson_mut_val *val);

/** Returns the content if the value is bool.
    Returns NULL if `val` is NULL or type is not bool. */
yyjson_api_inline bool yyjson_mut_get_bool(yyjson_mut_val *val);

/** Returns the content and cast to uint64_t.
    Returns 0 if `val` is NULL or type is not integer(sint/uint). */
yyjson_api_inline uint64_t yyjson_mut_get_uint(yyjson_mut_val *val);

/** Returns the content and cast to int64_t.
    Returns 0 if `val` is NULL or type is not integer(sint/uint). */
yyjson_api_inline int64_t yyjson_mut_get_sint(yyjson_mut_val *val);

/** Returns the content and cast to int.
    Returns 0 if `val` is NULL or type is not integer(sint/uint). */
yyjson_api_inline int yyjson_mut_get_int(yyjson_mut_val *val);

/** Returns the content if the value is real number.
    Returns 0.0 if `val` is NULL or type is not real(double). */
yyjson_api_inline double yyjson_mut_get_real(yyjson_mut_val *val);

/** Returns the content if the value is string.
    Returns NULL if `val` is NULL or type is not string. */
yyjson_api_inline const char *yyjson_mut_get_str(yyjson_mut_val *val);

/** Returns the content length (string length, array size, object size.
    Returns 0 if `val` is NULL or type is not string/array/object. */
yyjson_api_inline size_t yyjson_mut_get_len(yyjson_mut_val *val);

/** Returns whether the JSON value is equals to a string.
    The `str` should be a null-terminated UTF-8 string.
    Returns false if input is NULL or type is not string. */
yyjson_api_inline bool yyjson_mut_equals_str(yyjson_mut_val *val,
                                             const char *str);

/** Returns whether the JSON value is equals to a string.
    The `str` should be a UTF-8 string, null-terminator is not required.
    Returns false if input is NULL or type is not string. */
yyjson_api_inline bool yyjson_mut_equals_strn(yyjson_mut_val *val,
                                              const char *str, size_t len);

/** Returns whether two JSON values are equal (deep compare).
    Returns false if input is NULL.
    
    @warning This function is recursive and may cause a stack overflow
        if the object level is too deep. */
yyjson_api_inline bool yyjson_mut_equals(yyjson_mut_val *lhs,
                                         yyjson_mut_val *rhs);



/*==============================================================================
 * Mutable JSON Value Creation API
 *============================================================================*/

/** Creates and returns a raw value, returns NULL on error.
    The `str` should be a null-terminated UTF-8 string.
    
    @warning The input string is not copied, you should keep this string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_raw(yyjson_mut_doc *doc,
                                                 const char *str);

/** Creates and returns a raw value, returns NULL on error.
    The `str` should be a UTF-8 string, null-terminator is not required.
    
    @warning The input string is not copied, you should keep this string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_rawn(yyjson_mut_doc *doc,
                                                  const char *str,
                                                  size_t len);

/** Creates and returns a raw value, returns NULL on error.
    The `str` should be a null-terminated UTF-8 string.
    The input string is copied and held by the document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_rawcpy(yyjson_mut_doc *doc,
                                                    const char *str);

/** Creates and returns a raw value, returns NULL on error.
    The `str` should be a UTF-8 string, null-terminator is not required.
    The input string is copied and held by the document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_rawncpy(yyjson_mut_doc *doc,
                                                     const char *str,
                                                     size_t len);

/** Creates and returns a null value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_null(yyjson_mut_doc *doc);

/** Creates and returns a true value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_true(yyjson_mut_doc *doc);

/** Creates and returns a false value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_false(yyjson_mut_doc *doc);

/** Creates and returns a bool value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_bool(yyjson_mut_doc *doc,
                                                  bool val);

/** Creates and returns an unsigned integer value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_uint(yyjson_mut_doc *doc,
                                                  uint64_t num);

/** Creates and returns a signed integer value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_sint(yyjson_mut_doc *doc,
                                                  int64_t num);

/** Creates and returns a signed integer value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_int(yyjson_mut_doc *doc,
                                                 int64_t num);

/** Creates and returns an real number value, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_real(yyjson_mut_doc *doc,
                                                  double num);

/** Creates and returns a string value, returns NULL on error.
    The `str` should be a null-terminated UTF-8 string.
    @warning The input string is not copied, you should keep this string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_str(yyjson_mut_doc *doc,
                                                 const char *str);

/** Creates and returns a string value, returns NULL on error.
    The `str` should be a UTF-8 string, null-terminator is not required.
    @warning The input string is not copied, you should keep this string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_strn(yyjson_mut_doc *doc,
                                                  const char *str,
                                                  size_t len);

/** Creates and returns a string value, returns NULL on error.
    The `str` should be a null-terminated UTF-8 string.
    The input string is copied and held by the document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_strcpy(yyjson_mut_doc *doc,
                                                    const char *str);

/** Creates and returns a string value, returns NULL on error.
    The `str` should be a UTF-8 string, null-terminator is not required.
    The input string is copied and held by the document. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_strncpy(yyjson_mut_doc *doc,
                                                     const char *str,
                                                     size_t len);



/*==============================================================================
 * Mutable JSON Array API
 *============================================================================*/

/** Returns the number of elements in this array.
    Returns 0 if `arr` is NULL or type is not array. */
yyjson_api_inline size_t yyjson_mut_arr_size(yyjson_mut_val *arr);

/** Returns the element at the specified position in this array.
    Returns NULL if array is NULL/empty or the index is out of bounds.
    @warning This function takes a linear search time. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_get(yyjson_mut_val *arr,
                                                     size_t idx);

/** Returns the first element of this array.
    Returns NULL if `arr` is NULL/empty or type is not array. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_get_first(yyjson_mut_val *arr);

/** Returns the last element of this array.
    Returns NULL if `arr` is NULL/empty or type is not array. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_get_last(yyjson_mut_val *arr);



/*==============================================================================
 * Mutable JSON Array Iterator API
 *============================================================================*/

/**
 A mutable JSON array iterator.
 
 @warning You should not modify the array while iterating over it, but you can
    use yyjson_mut_arr_iter_remove() to remove current value.
 
 @par Example
 @code
    yyjson_mut_val *val;
    yyjson_mut_arr_iter iter;
    yyjson_mut_arr_iter_init(arr, &iter);
    while ((val = yyjson_mut_arr_iter_next(&iter))) {
        your_func(val);
        if (your_val_is_unused(val)) {
            yyjson_mut_arr_iter_remove(&iter);
        }
    }
 @endcode
 */
typedef struct yyjson_mut_arr_iter yyjson_mut_arr_iter;

/**
 Initialize an iterator for this array.
 
 @param arr The array to be iterated over.
    If this parameter is NULL or not an array, `iter` will be set to empty.
 @param iter The iterator to be initialized.
    If this parameter is NULL, the function will fail and return false.
 @return true if the `iter` has been successfully initialized.
 
 @note The iterator does not need to be destroyed.
 */
yyjson_api_inline bool yyjson_mut_arr_iter_init(yyjson_mut_val *arr,
    yyjson_mut_arr_iter *iter);

/**
 Returns whether the iteration has more elements.
 If `iter` is NULL, this function will return false.
 */
yyjson_api_inline bool yyjson_mut_arr_iter_has_next(
    yyjson_mut_arr_iter *iter);

/**
 Returns the next element in the iteration, or NULL on end.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_iter_next(
    yyjson_mut_arr_iter *iter);

/**
 Removes and returns current element in the iteration.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_iter_remove(
    yyjson_mut_arr_iter *iter);

/**
 Macro for iterating over an array.
 It works like iterator, but with a more intuitive API.
 
 @warning You should not modify the array while iterating over it.
 
 @par Example
 @code
    size_t idx, max;
    yyjson_mut_val *val;
    yyjson_mut_arr_foreach(arr, idx, max, val) {
        your_func(idx, val);
    }
 @endcode
 */
#define yyjson_mut_arr_foreach(arr, idx, max, val) \
    for ((idx) = 0, \
        (max) = yyjson_mut_arr_size(arr), \
        (val) = yyjson_mut_arr_get_first(arr); \
        (idx) < (max); \
        (idx)++, \
        (val) = (val)->next)



/*==============================================================================
 * Mutable JSON Array Creation API
 *============================================================================*/

/**
 Creates and returns an empty mutable array.
 @param doc A mutable document, used for memory allocation only.
 @return The new array. NULL if input is NULL or memory allocation failed.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr(yyjson_mut_doc *doc);

/**
 Creates and returns a new mutable array with the given boolean values.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of boolean values.
 @param count The value count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const bool vals[3] = { true, false, true };
    yyjson_mut_val *arr = yyjson_mut_arr_with_bool(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_bool(
    yyjson_mut_doc *doc, const bool *vals, size_t count);

/**
 Creates and returns a new mutable array with the given sint numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of sint numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const int64_t vals[3] = { -1, 0, 1 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_sint64(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint(
    yyjson_mut_doc *doc, const int64_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given uint numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of uint numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const uint64_t vals[3] = { 0, 1, 0 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_uint(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint(
    yyjson_mut_doc *doc, const uint64_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given real numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of real numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const double vals[3] = { 0.1, 0.2, 0.3 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_real(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_real(
    yyjson_mut_doc *doc, const double *vals, size_t count);

/**
 Creates and returns a new mutable array with the given int8 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of int8 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const int8_t vals[3] = { -1, 0, 1 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_sint8(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint8(
    yyjson_mut_doc *doc, const int8_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given int16 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of int16 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const int16_t vals[3] = { -1, 0, 1 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_sint16(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint16(
    yyjson_mut_doc *doc, const int16_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given int32 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of int32 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const int32_t vals[3] = { -1, 0, 1 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_sint32(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint32(
    yyjson_mut_doc *doc, const int32_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given int64 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of int64 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const int64_t vals[3] = { -1, 0, 1 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_sint64(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint64(
    yyjson_mut_doc *doc, const int64_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given uint8 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of uint8 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const uint8_t vals[3] = { 0, 1, 0 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_uint8(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint8(
    yyjson_mut_doc *doc, const uint8_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given uint16 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of uint16 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const uint16_t vals[3] = { 0, 1, 0 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_uint16(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint16(
    yyjson_mut_doc *doc, const uint16_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given uint32 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of uint32 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const uint32_t vals[3] = { 0, 1, 0 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_uint32(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint32(
    yyjson_mut_doc *doc, const uint32_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given uint64 numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of uint64 numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
     const uint64_t vals[3] = { 0, 1, 0 };
     yyjson_mut_val *arr = yyjson_mut_arr_with_uint64(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint64(
    yyjson_mut_doc *doc, const uint64_t *vals, size_t count);

/**
 Creates and returns a new mutable array with the given float numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of float numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const float vals[3] = { -1.0f, 0.0f, 1.0f };
    yyjson_mut_val *arr = yyjson_mut_arr_with_float(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_float(
    yyjson_mut_doc *doc, const float *vals, size_t count);

/**
 Creates and returns a new mutable array with the given double numbers.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of double numbers.
 @param count The number count. If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const double vals[3] = { -1.0, 0.0, 1.0 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_double(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_double(
    yyjson_mut_doc *doc, const double *vals, size_t count);

/**
 Creates and returns a new mutable array with the given strings, these strings
 will not be copied.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of UTF-8 null-terminator strings.
    If this array contains NULL, the function will fail and return NULL.
 @param count The number of values in `vals`.
    If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @warning The input strings are not copied, you should keep these strings
    unmodified for the lifetime of this JSON document. If these strings will be
    modified, you should use yyjson_mut_arr_with_strcpy() instead.
 
 @par Example
 @code
    const char *vals[3] = { "a", "b", "c" };
    yyjson_mut_val *arr = yyjson_mut_arr_with_str(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_str(
    yyjson_mut_doc *doc, const char **vals, size_t count);

/**
 Creates and returns a new mutable array with the given strings and string
 lengths, these strings will not be copied.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of UTF-8 strings, null-terminator is not required.
    If this array contains NULL, the function will fail and return NULL.
 @param lens A C array of string lengths, in bytes.
 @param count The number of strings in `vals`.
    If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @warning The input strings are not copied, you should keep these strings
    unmodified for the lifetime of this JSON document. If these strings will be
    modified, you should use yyjson_mut_arr_with_strncpy() instead.
 
 @par Example
 @code
    const char *vals[3] = { "a", "bb", "c" };
    const size_t lens[3] = { 1, 2, 1 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_strn(doc, vals, lens, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_strn(
    yyjson_mut_doc *doc, const char **vals, const size_t *lens, size_t count);

/**
 Creates and returns a new mutable array with the given strings, these strings
 will be copied.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of UTF-8 null-terminator strings.
    If this array contains NULL, the function will fail and return NULL.
 @param count The number of values in `vals`.
    If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const char *vals[3] = { "a", "b", "c" };
    yyjson_mut_val *arr = yyjson_mut_arr_with_strcpy(doc, vals, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_strcpy(
    yyjson_mut_doc *doc, const char **vals, size_t count);

/**
 Creates and returns a new mutable array with the given strings and string
 lengths, these strings will be copied.
 
 @param doc A mutable document, used for memory allocation only.
    If this parameter is NULL, the function will fail and return NULL.
 @param vals A C array of UTF-8 strings, null-terminator is not required.
    If this array contains NULL, the function will fail and return NULL.
 @param lens A C array of string lengths, in bytes.
 @param count The number of strings in `vals`.
    If this value is 0, an empty array will return.
 @return The new array. NULL if input is invalid or memory allocation failed.
 
 @par Example
 @code
    const char *vals[3] = { "a", "bb", "c" };
    const size_t lens[3] = { 1, 2, 1 };
    yyjson_mut_val *arr = yyjson_mut_arr_with_strn(doc, vals, lens, 3);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_strncpy(
    yyjson_mut_doc *doc, const char **vals, const size_t *lens, size_t count);



/*==============================================================================
 * Mutable JSON Array Modification API
 *============================================================================*/

/**
 Inserts a value into an array at a given index.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param val The value to be inserted. Returns false if it is NULL.
 @param idx The index to which to insert the new value.
    Returns false if the index is out of range.
 @return Whether successful.
 @warning This function takes a linear search time.
 */
yyjson_api_inline bool yyjson_mut_arr_insert(yyjson_mut_val *arr,
                                             yyjson_mut_val *val, size_t idx);

/**
 Inserts a value at the end of the array.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param val The value to be inserted. Returns false if it is NULL.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_append(yyjson_mut_val *arr,
                                             yyjson_mut_val *val);

/**
 Inserts a value at the head of the array.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param val The value to be inserted. Returns false if it is NULL.
 @return    Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_prepend(yyjson_mut_val *arr,
                                              yyjson_mut_val *val);

/**
 Replaces a value at index and returns old value.
 @param arr The array to which the value is to be replaced.
    Returns false if it is NULL or not an array.
 @param idx The index to which to replace the value.
    Returns false if the index is out of range.
 @param val The new value to replace. Returns false if it is NULL.
 @return Old value, or NULL on error.
 @warning This function takes a linear search time.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_replace(yyjson_mut_val *arr,
                                                         size_t idx,
                                                         yyjson_mut_val *val);

/**
 Removes and returns a value at index.
 @param arr The array from which the value is to be removed.
    Returns false if it is NULL or not an array.
 @param idx The index from which to remove the value.
    Returns false if the index is out of range.
 @return Old value, or NULL on error.
 @warning This function takes a linear search time.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_remove(yyjson_mut_val *arr,
                                                        size_t idx);

/**
 Removes and returns the first value in this array.
 @param arr The array from which the value is to be removed.
    Returns false if it is NULL or not an array.
 @return The first value, or NULL on error.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_remove_first(
    yyjson_mut_val *arr);

/**
 Removes and returns the last value in this array.
 @param arr The array from which the value is to be removed.
    Returns false if it is NULL or not an array.
 @return The last value, or NULL on error.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_remove_last(
    yyjson_mut_val *arr);

/**
 Removes all values within a specified range in the array.
 @param arr The array from which the value is to be removed.
    Returns false if it is NULL or not an array.
 @param idx The start index of the range (0 is the first).
 @param len The number of items in the range (can be 0).
 @return Whether successful.
 @warning This function takes a linear search time.
 */
yyjson_api_inline bool yyjson_mut_arr_remove_range(yyjson_mut_val *arr,
                                                   size_t idx, size_t len);

/**
 Removes all values in this array.
 @param arr The array from which all of the values are to be removed.
    Returns false if it is NULL or not an array.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_clear(yyjson_mut_val *arr);

/**
 Rotates values in this array for the given number of times.
 For example: [1,2,3,4,5] rotate 2 is [3,4,5,1,2].
 @param arr The array to be rotated.
 @param idx Index (or times) to rotate.
 @warning This function takes a linear search time.
 */
yyjson_api_inline bool yyjson_mut_arr_rotate(yyjson_mut_val *arr,
                                             size_t idx);



/*==============================================================================
 * Mutable JSON Array Modification Convenience API
 *============================================================================*/

/**
 Adds a value at the end of the array.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param val The value to be inserted. Returns false if it is NULL.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_val(yyjson_mut_val *arr,
                                              yyjson_mut_val *val);

/**
 Adds a `null` value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_null(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr);

/**
 Adds a `true` value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_true(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr);

/**
 Adds a `false` value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_false(yyjson_mut_doc *doc,
                                                yyjson_mut_val *arr);

/**
 Adds a bool value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param val The bool value to be added.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_bool(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               bool val);

/**
 Adds an unsigned integer value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param num The number to be added.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_uint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               uint64_t num);

/**
 Adds a signed integer value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param num The number to be added.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_sint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               int64_t num);

/**
 Adds a integer value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param num The number to be added.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_int(yyjson_mut_doc *doc,
                                              yyjson_mut_val *arr,
                                              int64_t num);

/**
 Adds a double value at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param num The number to be added.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_real(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               double num);

/**
 Adds a string value at the end of the array (no copy).
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param str A null-terminated UTF-8 string.
 @return Whether successful.
 @warning The input string is not copied, you should keep this string unmodified
    for the lifetime of this JSON document.
 */
yyjson_api_inline bool yyjson_mut_arr_add_str(yyjson_mut_doc *doc,
                                              yyjson_mut_val *arr,
                                              const char *str);

/**
 Adds a string value at the end of the array (no copy).
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param str A UTF-8 string, null-terminator is not required.
 @param len The length of the string, in bytes.
 @return Whether successful.
 @warning The input string is not copied, you should keep this string unmodified
    for the lifetime of this JSON document.
 */
yyjson_api_inline bool yyjson_mut_arr_add_strn(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               const char *str,
                                               size_t len);

/**
 Adds a string value at the end of the array (copied).
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param str A null-terminated UTF-8 string.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_strcpy(yyjson_mut_doc *doc,
                                                 yyjson_mut_val *arr,
                                                 const char *str);

/**
 Adds a string value at the end of the array (copied).
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @param str A UTF-8 string, null-terminator is not required.
 @param len The length of the string, in bytes.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_arr_add_strncpy(yyjson_mut_doc *doc,
                                                  yyjson_mut_val *arr,
                                                  const char *str,
                                                  size_t len);

/**
 Creates and adds a new array at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @return The new array, or NULL on error.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_add_arr(yyjson_mut_doc *doc,
                                                         yyjson_mut_val *arr);

/**
 Creates and adds a new object at the end of the array.
 @param doc The `doc` is only used for memory allocation.
 @param arr The array to which the value is to be inserted.
    Returns false if it is NULL or not an array.
 @return The new object, or NULL on error.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_add_obj(yyjson_mut_doc *doc,
                                                         yyjson_mut_val *arr);



/*==============================================================================
 * Mutable JSON Object API
 *============================================================================*/

/** Returns the number of key-value pairs in this object.
    Returns 0 if `obj` is NULL or type is not object. */
yyjson_api_inline size_t yyjson_mut_obj_size(yyjson_mut_val *obj);

/** Returns the value to which the specified key is mapped.
    Returns NULL if this object contains no mapping for the key.
    Returns NULL if `obj/key` is NULL, or type is not object.
    
    The `key` should be a null-terminated UTF-8 string.
    
    @warning This function takes a linear search time. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_get(yyjson_mut_val *obj,
                                                     const char *key);

/** Returns the value to which the specified key is mapped.
    Returns NULL if this object contains no mapping for the key.
    Returns NULL if `obj/key` is NULL, or type is not object.
    
    The `key` should be a UTF-8 string, null-terminator is not required.
    The `key_len` should be the length of the key, in bytes.
    
    @warning This function takes a linear search time. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_getn(yyjson_mut_val *obj,
                                                      const char *key,
                                                      size_t key_len);



/*==============================================================================
 * Mutable JSON Object Iterator API
 *============================================================================*/

/**
 A mutable JSON object iterator.
 
 @warning You should not modify the object while iterating over it, but you can
    use yyjson_mut_obj_iter_remove() to remove current value.
 
 @par Example
 @code
    yyjson_mut_val *key, *val;
    yyjson_mut_obj_iter iter;
    yyjson_mut_obj_iter_init(obj, &iter);
    while ((key = yyjson_mut_obj_iter_next(&iter))) {
        val = yyjson_mut_obj_iter_get_val(key);
        your_func(key, val);
        if (your_val_is_unused(key, val)) {
            yyjson_mut_obj_iter_remove(&iter);
        }
    }
 @endcode
 
 If the ordering of the keys is known at compile-time, you can use this method
 to speed up value lookups:
 @code
    // {"k1":1, "k2": 3, "k3": 3}
    yyjson_mut_val *key, *val;
    yyjson_mut_obj_iter iter;
    yyjson_mut_obj_iter_init(obj, &iter);
    yyjson_mut_val *v1 = yyjson_mut_obj_iter_get(&iter, "k1");
    yyjson_mut_val *v3 = yyjson_mut_obj_iter_get(&iter, "k3");
 @endcode
 @see yyjson_mut_obj_iter_get() and yyjson_mut_obj_iter_getn()
 */
typedef struct yyjson_mut_obj_iter yyjson_mut_obj_iter;

/**
 Initialize an iterator for this object.
 
 @param obj The object to be iterated over.
    If this parameter is NULL or not an array, `iter` will be set to empty.
 @param iter The iterator to be initialized.
    If this parameter is NULL, the function will fail and return false.
 @return true if the `iter` has been successfully initialized.
 
 @note The iterator does not need to be destroyed.
 */
yyjson_api_inline bool yyjson_mut_obj_iter_init(yyjson_mut_val *obj,
    yyjson_mut_obj_iter *iter);

/**
 Returns whether the iteration has more elements.
 If `iter` is NULL, this function will return false.
 */
yyjson_api_inline bool yyjson_mut_obj_iter_has_next(
    yyjson_mut_obj_iter *iter);

/**
 Returns the next key in the iteration, or NULL on end.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_next(
    yyjson_mut_obj_iter *iter);

/**
 Returns the value for key inside the iteration.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_get_val(
    yyjson_mut_val *key);

/**
 Removes and returns current key-value pair in the iteration.
 If `iter` is NULL, this function will return NULL.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_remove(
    yyjson_mut_obj_iter *iter);

/**
 Iterates to a specified key and returns the value.
 
 This function does the same thing as yyjson_mut_obj_get(), but is much faster
 if the ordering of the keys is known at compile-time and you are using the same
 order to look up the values. If the key exists in this object, then the
 iterator will stop at the next key, otherwise the iterator will not change and
 NULL is returned.
 
 @param iter The object iterator, should not be NULL.
 @param key The key, should be a UTF-8 string with null-terminator.
 @return The value to which the specified key is mapped.
    NULL if this object contains no mapping for the key or input is invalid.
 
 @warning This function takes a linear search time if the key is not nearby.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_get(
    yyjson_mut_obj_iter *iter, const char *key);

/**
 Iterates to a specified key and returns the value.
 
 This function does the same thing as yyjson_mut_obj_getn(), but is much faster
 if the ordering of the keys is known at compile-time and you are using the same
 order to look up the values. If the key exists in this object, then the
 iterator will stop at the next key, otherwise the iterator will not change and
 NULL is returned.
 
 @param iter The object iterator, should not be NULL.
 @param key The key, should be a UTF-8 string, null-terminator is not required.
 @param key_len The the length of `key`, in bytes.
 @return The value to which the specified key is mapped.
    NULL if this object contains no mapping for the key or input is invalid.
 
 @warning This function takes a linear search time if the key is not nearby.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_getn(
    yyjson_mut_obj_iter *iter, const char *key, size_t key_len);

/**
 Macro for iterating over an object.
 It works like iterator, but with a more intuitive API.
 
 @warning You should not modify the object while iterating over it.
 
 @par Example
 @code
    size_t idx, max;
    yyjson_val *key, *val;
    yyjson_obj_foreach(obj, idx, max, key, val) {
        your_func(key, val);
    }
 @endcode
 */
#define yyjson_mut_obj_foreach(obj, idx, max, key, val) \
    for ((idx) = 0, \
        (max) = yyjson_mut_obj_size(obj), \
        (key) = (max) ? ((yyjson_mut_val *)(obj)->uni.ptr)->next->next : NULL, \
        (val) = (key) ? (key)->next : NULL; \
        (idx) < (max); \
        (idx)++, \
        (key) = (val)->next, \
        (val) = (key)->next)



/*==============================================================================
 * Mutable JSON Object Creation API
 *============================================================================*/

/** Creates and returns a mutable object, returns NULL on error. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj(yyjson_mut_doc *doc);

/**
 Creates and returns a mutable object with keys and values, returns NULL on
 error. The keys and values are not copied. The strings should be a
 null-terminated UTF-8 string.
 
 @warning The input string is not copied, you should keep this string
    unmodified for the lifetime of this JSON document.
 
 @par Example
 @code
    const char *keys[2] = { "id", "name" };
    const char *vals[2] = { "01", "Harry" };
    yyjson_mut_val *obj = yyjson_mut_obj_with_str(doc, keys, vals, 2);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_with_str(yyjson_mut_doc *doc,
                                                          const char **keys,
                                                          const char **vals,
                                                          size_t count);

/**
 Creates and returns a mutable object with key-value pairs and pair count,
 returns NULL on error. The keys and values are not copied. The strings should
 be a null-terminated UTF-8 string.
 
 @warning The input string is not copied, you should keep this string
    unmodified for the lifetime of this JSON document.
 
 @par Example
 @code
    const char *kv_pairs[4] = { "id", "01", "name", "Harry" };
    yyjson_mut_val *obj = yyjson_mut_obj_with_kv(doc, kv_pairs, 2);
 @endcode
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_with_kv(yyjson_mut_doc *doc,
                                                         const char **kv_pairs,
                                                         size_t pair_count);



/*==============================================================================
 * Mutable JSON Object Modification API
 *============================================================================*/

/**
 Adds a key-value pair at the end of the object.
 This function allows duplicated key in one object.
 @param obj The object to which the new key-value pair is to be added.
 @param key The key, should be a string which is created by yyjson_mut_str(),
    yyjson_mut_strn(), yyjson_mut_strcpy() or yyjson_mut_strncpy().
 @param val The value to add to the object.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_obj_add(yyjson_mut_val *obj,
                                          yyjson_mut_val *key,
                                          yyjson_mut_val *val);
/**
 Sets a key-value pair at the end of the object.
 This function may remove all key-value pairs for the given key before add.
 @param obj The object to which the new key-value pair is to be added.
 @param key The key, should be a string which is created by yyjson_mut_str(),
    yyjson_mut_strn(), yyjson_mut_strcpy() or yyjson_mut_strncpy().
 @param val The value to add to the object. If this value is null, the behavior
    is same as yyjson_mut_obj_remove().
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_obj_put(yyjson_mut_val *obj,
                                          yyjson_mut_val *key,
                                          yyjson_mut_val *val);

/**
 Inserts a key-value pair to the object at the given position.
 This function allows duplicated key in one object.
 @param obj The object to which the new key-value pair is to be added.
 @param key The key, should be a string which is created by yyjson_mut_str(),
    yyjson_mut_strn(), yyjson_mut_strcpy() or yyjson_mut_strncpy().
 @param val The value to add to the object.
 @param idx The index to which to insert the new pair.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_obj_insert(yyjson_mut_val *obj,
                                             yyjson_mut_val *key,
                                             yyjson_mut_val *val,
                                             size_t idx);

/**
 Removes all key-value pair from the object with given key.
 @param obj The object from which the key-value pair is to be removed.
 @param key The key, should be a string value.
 @return The first matched value, or NULL if no matched value.
 @warning This function takes a linear search time.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove(yyjson_mut_val *obj,
                                                        yyjson_mut_val *key);

/**
 Removes all key-value pair from the object with given key.
 @param obj The object from which the key-value pair is to be removed.
 @param key The key, should be a UTF-8 string with null-terminator.
 @return The first matched value, or NULL if no matched value.
 @warning This function takes a linear search time.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_key(
    yyjson_mut_val *obj, const char *key);

/**
 Removes all key-value pair from the object with given key.
 @param obj The object from which the key-value pair is to be removed.
 @param key The key, should be a UTF-8 string, null-terminator is not required.
 @param key_len The length of the key.
 @return The first matched value, or NULL if no matched value.
 @warning This function takes a linear search time.
 */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_keyn(
    yyjson_mut_val *obj, const char *key, size_t key_len);

/**
 Removes all key-value pairs in this object.
 @param obj The object from which all of the values are to be removed.
 @return Whether successful.
 */
yyjson_api_inline bool yyjson_mut_obj_clear(yyjson_mut_val *obj);

/**
 Replaces value from the object with given key.
 If the key is not exist, or the value is NULL, it will fail.
 @param obj The object to which the value is to be replaced.
 @param key The key, should be a string value.
 @param val The value to replace into the object.
 @return Whether successful.
 @warning This function takes a linear search time.
 */
yyjson_api_inline bool yyjson_mut_obj_replace(yyjson_mut_val *obj,
                                              yyjson_mut_val *key,
                                              yyjson_mut_val *val);

/**
 Rotates key-value pairs in the object for the given number of times.
 For example: {"a":1,"b":2,"c":3,"d":4} rotate 1 is {"b":2,"c":3,"d":4,"a":1}.
 @param obj The object to be rotated.
 @param idx Index (or times) to rotate.
 @return Whether successful.
 @warning This function takes a linear search time.
 */
yyjson_api_inline bool yyjson_mut_obj_rotate(yyjson_mut_val *obj,
                                             size_t idx);



/*==============================================================================
 * Mutable JSON Object Modification Convenience API
 *============================================================================*/

/** Adds a `null` value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_null(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *key);

/** Adds a `true` value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_true(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *key);

/** Adds a `false` value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_false(yyjson_mut_doc *doc,
                                                yyjson_mut_val *obj,
                                                const char *key);

/** Adds a bool value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_bool(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *key, bool val);

/** Adds an unsigned integer value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_uint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *key, uint64_t val);

/** Adds a signed integer value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_sint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *key, int64_t val);

/** Adds an int value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_int(yyjson_mut_doc *doc,
                                              yyjson_mut_val *obj,
                                              const char *key, int64_t val);

/** Adds a double value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_real(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *key, double val);

/** Adds a string value at the end of the object.
    The `key` and `val` should be null-terminated UTF-8 strings.
    This function allows duplicated key in one object.
    
    @warning The key/value string are not copied, you should keep these strings
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_str(yyjson_mut_doc *doc,
                                              yyjson_mut_val *obj,
                                              const char *key, const char *val);

/** Adds a string value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    The `val` should be a UTF-8 string, null-terminator is not required.
    The `len` should be the length of the `val`, in bytes.
    This function allows duplicated key in one object.
    
    @warning The key/value string are not copied, you should keep these strings
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_strn(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *key,
                                               const char *val, size_t len);

/** Adds a string value at the end of the object.
    The `key` and `val` should be null-terminated UTF-8 strings.
    The value string is copied.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_strcpy(yyjson_mut_doc *doc,
                                                 yyjson_mut_val *obj,
                                                 const char *key,
                                                 const char *val);

/** Adds a string value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    The `val` should be a UTF-8 string, null-terminator is not required.
    The `len` should be the length of the `val`, in bytes.
    This function allows duplicated key in one object.
    
    @warning The key/value string are not copied, you should keep these strings
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_strncpy(yyjson_mut_doc *doc,
                                                  yyjson_mut_val *obj,
                                                  const char *key,
                                                  const char *val, size_t len);

/** Adds a JSON value at the end of the object.
    The `key` should be a null-terminated UTF-8 string.
    This function allows duplicated key in one object.
    
    @warning The key string are not copied, you should keep the string
        unmodified for the lifetime of this JSON document. */
yyjson_api_inline bool yyjson_mut_obj_add_val(yyjson_mut_doc *doc,
                                              yyjson_mut_val *obj,
                                              const char *key,
                                              yyjson_mut_val *val);

/** Removes all key-value pairs for the given key.
    Returns the first value to which the specified key is mapped or NULL if this
    object contains no mapping for the key.
    The `key` should be a null-terminated UTF-8 string.
    
    @warning This function takes a linear search time. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_str(
    yyjson_mut_val *obj, const char *key);

/** Removes all key-value pairs for the given key.
    Returns the first value to which the specified key is mapped or NULL if this
    object contains no mapping for the key.
    The `key` should be a UTF-8 string, null-terminator is not required.
    The `len` should be the length of the key, in bytes.
    
    @warning This function takes a linear search time. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_strn(
    yyjson_mut_val *obj, const char *key, size_t len);



/*==============================================================================
 * JSON Pointer API
 * https://tools.ietf.org/html/rfc6901
 *============================================================================*/

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a null-terminated UTF-8 string.
    
    Returns NULL if there's no matched value.
    Returns NULL if `val/ptr` is NULL or `val` is not object. */
yyjson_api_inline yyjson_val *yyjson_get_pointer(yyjson_val *val,
                                                 const char *ptr);

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a UTF-8 string, null-terminator is not required.
    The `len` should be the length of the `ptr`, in bytes.
    
    Returns NULL if there's no matched value.
    Returns NULL if `val/ptr` is NULL or `val` is not object. */
yyjson_api_inline yyjson_val *yyjson_get_pointern(yyjson_val *val,
                                                  const char *ptr,
                                                  size_t len);

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a null-terminated UTF-8 string.
    
    Returns NULL if there's no matched value. */
yyjson_api_inline yyjson_val *yyjson_doc_get_pointer(yyjson_doc *doc,
                                                     const char *ptr);

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a UTF-8 string, null-terminator is not required.
    The `len` should be the length of the `ptr`, in bytes.
 
    Returns NULL if there's no matched value. */
yyjson_api_inline yyjson_val *yyjson_doc_get_pointern(yyjson_doc *doc,
                                                     const char *ptr,
                                                      size_t len);

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a null-terminated UTF-8 string.
    
    Returns NULL if there's no matched value. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_get_pointer(yyjson_mut_val *val,
                                                         const char *ptr);

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a UTF-8 string, null-terminator is not required.
    The `len` should be the length of the `ptr`, in bytes.
    
    Returns NULL if there's no matched value. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_get_pointern(yyjson_mut_val *val,
                                                          const char *ptr,
                                                          size_t len);

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a null-terminated UTF-8 string.
    
    Returns NULL if there's no matched value. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_doc_get_pointer(
    yyjson_mut_doc *doc, const char *ptr);

/** Get a JSON value with JSON Pointer (RFC 6901).
    The `ptr` should be a UTF-8 string, null-terminator is not required.
    The `len` should be the length of the `ptr`, in bytes.
    
    Returns NULL if there's no matched value. */
yyjson_api_inline yyjson_mut_val *yyjson_mut_doc_get_pointern(
    yyjson_mut_doc *doc, const char *ptr, size_t len);



/*==============================================================================
 * JSON Merge-Patch API
 * https://tools.ietf.org/html/rfc7386
 *============================================================================*/

/** Creates and returns a merge-patched JSON value (RFC 7386).
    The memory of the returned value is allocated by the `doc`.
    Returns NULL if the patch could not be applied.
    
    @warning This function is recursive and may cause a stack overflow if the
        object level is too deep. */
yyjson_api yyjson_mut_val *yyjson_merge_patch(yyjson_mut_doc *doc,
                                              yyjson_val *orig,
                                              yyjson_val *patch);

/** Creates and returns a merge-patched JSON value (RFC 7386).
    The memory of the returned value is allocated by the `doc`.
    Returns NULL if the patch could not be applied.
    
    @warning This function is recursive and may cause a stack overflow if the
        object level is too deep. */
yyjson_api yyjson_mut_val *yyjson_mut_merge_patch(yyjson_mut_doc *doc,
                                                  yyjson_mut_val *orig,
                                                  yyjson_mut_val *patch);



/*==============================================================================
 * JSON Structure (Implementation)
 *============================================================================*/

/** Payload of a JSON value (8 bytes). */
typedef union yyjson_val_uni {
    uint64_t    u64;
    int64_t     i64;
    double      f64;
    const char *str;
    void       *ptr;
    size_t      ofs;
} yyjson_val_uni;

/**
 Immutable JSON value, 16 bytes.
 */
struct yyjson_val {
    uint64_t tag; /**< type, subtype and length */
    yyjson_val_uni uni; /**< payload */
};

struct yyjson_doc {
    /** Root value of the document (nonnull). */
    yyjson_val *root;
    /** Allocator used by document (nonnull). */
    yyjson_alc alc;
    /** The total number of bytes read when parsing JSON (nonzero). */
    size_t dat_read;
    /** The total number of value read when parsing JSON (nonzero). */
    size_t val_read;
    /** The string pool used by JSON values (nullable). */
    char *str_pool;
};



/*==============================================================================
 * Unsafe JSON Value API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_type unsafe_yyjson_get_type(void *val) {
    uint8_t tag = (uint8_t)((yyjson_val *)val)->tag;
    return (yyjson_type)(tag & YYJSON_TYPE_MASK);
}

yyjson_api_inline yyjson_subtype unsafe_yyjson_get_subtype(void *val) {
    uint8_t tag = (uint8_t)((yyjson_val *)val)->tag;
    return (yyjson_subtype)(tag & YYJSON_SUBTYPE_MASK);
}

yyjson_api_inline uint8_t unsafe_yyjson_get_tag(void *val) {
    uint8_t tag = (uint8_t)((yyjson_val *)val)->tag;
    return (uint8_t)(tag & YYJSON_TAG_MASK);
}

yyjson_api_inline bool unsafe_yyjson_is_raw(void *val) {
    return unsafe_yyjson_get_type(val) == YYJSON_TYPE_RAW;
}

yyjson_api_inline bool unsafe_yyjson_is_null(void *val) {
    return unsafe_yyjson_get_type(val) == YYJSON_TYPE_NULL;
}

yyjson_api_inline bool unsafe_yyjson_is_bool(void *val) {
    return unsafe_yyjson_get_type(val) == YYJSON_TYPE_BOOL;
}

yyjson_api_inline bool unsafe_yyjson_is_num(void *val) {
    return unsafe_yyjson_get_type(val) == YYJSON_TYPE_NUM;
}

yyjson_api_inline bool unsafe_yyjson_is_str(void *val) {
    return unsafe_yyjson_get_type(val) == YYJSON_TYPE_STR;
}

yyjson_api_inline bool unsafe_yyjson_is_arr(void *val) {
    return unsafe_yyjson_get_type(val) == YYJSON_TYPE_ARR;
}

yyjson_api_inline bool unsafe_yyjson_is_obj(void *val) {
    return unsafe_yyjson_get_type(val) == YYJSON_TYPE_OBJ;
}

yyjson_api_inline bool unsafe_yyjson_is_ctn(void *val) {
    uint8_t mask = YYJSON_TYPE_ARR & YYJSON_TYPE_OBJ;
    return (unsafe_yyjson_get_tag(val) & mask) == mask;
}

yyjson_api_inline bool unsafe_yyjson_is_uint(void *val) {
    const uint8_t patt = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
    return unsafe_yyjson_get_tag(val) == patt;
}

yyjson_api_inline bool unsafe_yyjson_is_sint(void *val) {
    const uint8_t patt = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
    return unsafe_yyjson_get_tag(val) == patt;
}

yyjson_api_inline bool unsafe_yyjson_is_int(void *val) {
    const uint8_t mask = YYJSON_TAG_MASK & (~YYJSON_SUBTYPE_SINT);
    const uint8_t patt = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
    return (unsafe_yyjson_get_tag(val) & mask) == patt;
}

yyjson_api_inline bool unsafe_yyjson_is_real(void *val) {
    const uint8_t patt = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_REAL;
    return unsafe_yyjson_get_tag(val) == patt;
}

yyjson_api_inline bool unsafe_yyjson_is_true(void *val) {
    const uint8_t patt = YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_TRUE;
    return unsafe_yyjson_get_tag(val) == patt;
}

yyjson_api_inline bool unsafe_yyjson_is_false(void *val) {
    const uint8_t patt = YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_FALSE;
    return unsafe_yyjson_get_tag(val) == patt;
}

yyjson_api_inline bool unsafe_yyjson_arr_is_flat(yyjson_val *val) {
    size_t ofs = val->uni.ofs;
    size_t len = (size_t)(val->tag >> YYJSON_TAG_BIT);
    return len * sizeof(yyjson_val) + sizeof(yyjson_val) == ofs;
}

yyjson_api_inline const char *unsafe_yyjson_get_raw(void *val) {
    return ((yyjson_val *)val)->uni.str;
}

yyjson_api_inline bool unsafe_yyjson_get_bool(void *val) {
    uint8_t tag = unsafe_yyjson_get_tag(val);
    return (bool)((tag & YYJSON_SUBTYPE_MASK) >> YYJSON_TYPE_BIT);
}

yyjson_api_inline uint64_t unsafe_yyjson_get_uint(void *val) {
    return ((yyjson_val *)val)->uni.u64;
}

yyjson_api_inline int64_t unsafe_yyjson_get_sint(void *val) {
    return ((yyjson_val *)val)->uni.i64;
}

yyjson_api_inline int unsafe_yyjson_get_int(void *val) {
    return (int)((yyjson_val *)val)->uni.i64;
}

yyjson_api_inline double unsafe_yyjson_get_real(void *val) {
    return ((yyjson_val *)val)->uni.f64;
}

yyjson_api_inline const char *unsafe_yyjson_get_str(void *val) {
    return ((yyjson_val *)val)->uni.str;
}

yyjson_api_inline size_t unsafe_yyjson_get_len(void *val) {
    return (size_t)(((yyjson_val *)val)->tag >> YYJSON_TAG_BIT);
}

yyjson_api_inline void unsafe_yyjson_set_len(void *val, size_t len) {
    uint64_t tag = ((yyjson_val *)val)->tag & YYJSON_TAG_MASK;
    tag |= (uint64_t)len << YYJSON_TAG_BIT;
    ((yyjson_val *)val)->tag = tag;
}

yyjson_api_inline yyjson_val *unsafe_yyjson_get_first(yyjson_val *ctn) {
    return ctn + 1;
}

yyjson_api_inline yyjson_val *unsafe_yyjson_get_next(yyjson_val *val) {
    bool is_ctn = unsafe_yyjson_is_ctn(val);
    size_t ctn_ofs = val->uni.ofs;
    size_t ofs = (is_ctn ? ctn_ofs : sizeof(yyjson_val));
    return (yyjson_val *)(void *)((uint8_t *)val + ofs);
}

yyjson_api_inline bool unsafe_yyjson_equals_strn(void *val, const char *str,
                                                 size_t len) {
    uint64_t tag = ((uint64_t)len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
    return ((yyjson_val *)val)->tag == tag &&
    memcmp(((yyjson_val *)val)->uni.str, str, len) == 0;
}

yyjson_api_inline bool unsafe_yyjson_equals_str(void *val, const char *str) {
    return unsafe_yyjson_equals_strn(val, str, strlen(str));
}



/*==============================================================================
 * JSON Document API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_val *yyjson_doc_get_root(yyjson_doc *doc) {
    return doc ? doc->root : NULL;
}

yyjson_api_inline size_t yyjson_doc_get_read_size(yyjson_doc *doc) {
    return doc ? doc->dat_read : 0;
}

yyjson_api_inline size_t yyjson_doc_get_val_count(yyjson_doc *doc) {
    return doc ? doc->val_read : 0;
}

yyjson_api_inline void yyjson_doc_free(yyjson_doc *doc) {
    if (doc) {
        yyjson_alc alc = doc->alc;
        if (doc->str_pool) alc.yyjson_free(alc.ctx, doc->str_pool);
        alc.yyjson_free(alc.ctx, doc);
    }
}



/*==============================================================================
 * JSON Value Type API (Implementation)
 *============================================================================*/

yyjson_api_inline bool yyjson_is_raw(yyjson_val *val) {
    return val ? unsafe_yyjson_is_raw(val) : false;
}

yyjson_api_inline bool yyjson_is_null(yyjson_val *val) {
    return val ? unsafe_yyjson_is_null(val) : false;
}

yyjson_api_inline bool yyjson_is_true(yyjson_val *val) {
    return val ? unsafe_yyjson_is_true(val) : false;
}

yyjson_api_inline bool yyjson_is_false(yyjson_val *val) {
    return val ? unsafe_yyjson_is_false(val) : false;
}

yyjson_api_inline bool yyjson_is_bool(yyjson_val *val) {
    return val ? unsafe_yyjson_is_bool(val) : false;
}

yyjson_api_inline bool yyjson_is_uint(yyjson_val *val) {
    return val ? unsafe_yyjson_is_uint(val) : false;
}

yyjson_api_inline bool yyjson_is_sint(yyjson_val *val) {
    return val ? unsafe_yyjson_is_sint(val) : false;
}

yyjson_api_inline bool yyjson_is_int(yyjson_val *val) {
    return val ? unsafe_yyjson_is_int(val) : false;
}

yyjson_api_inline bool yyjson_is_real(yyjson_val *val) {
    return val ? unsafe_yyjson_is_real(val) : false;
}

yyjson_api_inline bool yyjson_is_num(yyjson_val *val) {
    return val ? unsafe_yyjson_is_num(val) : false;
}

yyjson_api_inline bool yyjson_is_str(yyjson_val *val) {
    return val ? unsafe_yyjson_is_str(val) : false;
}

yyjson_api_inline bool yyjson_is_arr(yyjson_val *val) {
    return val ? unsafe_yyjson_is_arr(val) : false;
}

yyjson_api_inline bool yyjson_is_obj(yyjson_val *val) {
    return val ? unsafe_yyjson_is_obj(val) : false;
}

yyjson_api_inline bool yyjson_is_ctn(yyjson_val *val) {
    return val ? unsafe_yyjson_is_ctn(val) : false;
}



/*==============================================================================
 * JSON Value Content API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_type yyjson_get_type(yyjson_val *val) {
    return val ? unsafe_yyjson_get_type(val) : YYJSON_TYPE_NONE;
}

yyjson_api_inline yyjson_subtype yyjson_get_subtype(yyjson_val *val) {
    return val ? unsafe_yyjson_get_subtype(val) : YYJSON_SUBTYPE_NONE;
}

yyjson_api_inline uint8_t yyjson_get_tag(yyjson_val *val) {
    return val ? unsafe_yyjson_get_tag(val) : 0;
}

yyjson_api_inline const char *yyjson_get_type_desc(yyjson_val *val) {
    switch (yyjson_get_tag(val)) {
        case YYJSON_TYPE_RAW  | YYJSON_SUBTYPE_NONE:  return "raw";
        case YYJSON_TYPE_NULL | YYJSON_SUBTYPE_NONE:  return "null";
        case YYJSON_TYPE_STR  | YYJSON_SUBTYPE_NONE:  return "string";
        case YYJSON_TYPE_ARR  | YYJSON_SUBTYPE_NONE:  return "array";
        case YYJSON_TYPE_OBJ  | YYJSON_SUBTYPE_NONE:  return "object";
        case YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_TRUE:  return "true";
        case YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_FALSE: return "false";
        case YYJSON_TYPE_NUM  | YYJSON_SUBTYPE_UINT:  return "uint";
        case YYJSON_TYPE_NUM  | YYJSON_SUBTYPE_SINT:  return "sint";
        case YYJSON_TYPE_NUM  | YYJSON_SUBTYPE_REAL:  return "real";
        default:                                      return "unknown";
    }
}

yyjson_api_inline const char *yyjson_get_raw(yyjson_val *val) {
    return yyjson_is_raw(val) ? unsafe_yyjson_get_raw(val) : NULL;
}

yyjson_api_inline bool yyjson_get_bool(yyjson_val *val) {
    return yyjson_is_bool(val) ? unsafe_yyjson_get_bool(val) : false;
}

yyjson_api_inline uint64_t yyjson_get_uint(yyjson_val *val) {
    return yyjson_is_int(val) ? unsafe_yyjson_get_uint(val) : 0;
}

yyjson_api_inline int64_t yyjson_get_sint(yyjson_val *val) {
    return yyjson_is_int(val) ? unsafe_yyjson_get_sint(val) : 0;
}

yyjson_api_inline int yyjson_get_int(yyjson_val *val) {
    return yyjson_is_int(val) ? unsafe_yyjson_get_int(val) : 0;
}

yyjson_api_inline double yyjson_get_real(yyjson_val *val) {
    return yyjson_is_real(val) ? unsafe_yyjson_get_real(val) : 0.0;
}

yyjson_api_inline const char *yyjson_get_str(yyjson_val *val) {
    return yyjson_is_str(val) ? unsafe_yyjson_get_str(val) : NULL;
}

yyjson_api_inline size_t yyjson_get_len(yyjson_val *val) {
    return val ? unsafe_yyjson_get_len(val) : 0;
}

yyjson_api_inline bool yyjson_equals_str(yyjson_val *val, const char *str) {
    if (yyjson_likely(val && str)) {
        return unsafe_yyjson_equals_str(val, str);
    }
    return false;
}

yyjson_api_inline bool yyjson_equals_strn(yyjson_val *val, const char *str,
                                          size_t len) {
    if (yyjson_likely(val && str)) {
        return unsafe_yyjson_equals_strn(val, str, len);
    }
    return false;
}

yyjson_api bool unsafe_yyjson_equals(yyjson_val *lhs, yyjson_val *rhs);

yyjson_api_inline bool yyjson_equals(yyjson_val *lhs, yyjson_val *rhs) {
    if (yyjson_unlikely(!lhs || !rhs))
        return false;
    
    return unsafe_yyjson_equals(lhs, rhs);
}



/*==============================================================================
 * JSON Array API (Implementation)
 *============================================================================*/

yyjson_api_inline size_t yyjson_arr_size(yyjson_val *arr) {
    return yyjson_is_arr(arr) ? unsafe_yyjson_get_len(arr) : 0;
}

yyjson_api_inline yyjson_val *yyjson_arr_get(yyjson_val *arr, size_t idx) {
    if (yyjson_likely(yyjson_is_arr(arr))) {
        if (yyjson_likely(unsafe_yyjson_get_len(arr) > idx)) {
            yyjson_val *val = unsafe_yyjson_get_first(arr);
            if (unsafe_yyjson_arr_is_flat(arr)) {
                return val + idx;
            } else {
                while (idx-- > 0) val = unsafe_yyjson_get_next(val);
                return val;
            }
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_val *yyjson_arr_get_first(yyjson_val *arr) {
    if (yyjson_likely(yyjson_is_arr(arr))) {
        if (yyjson_likely(unsafe_yyjson_get_len(arr) > 0)) {
            return unsafe_yyjson_get_first(arr);
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_val *yyjson_arr_get_last(yyjson_val *arr) {
    if (yyjson_likely(yyjson_is_arr(arr))) {
        size_t len = unsafe_yyjson_get_len(arr);
        if (yyjson_likely(len > 0)) {
            yyjson_val *val = unsafe_yyjson_get_first(arr);
            if (unsafe_yyjson_arr_is_flat(arr)) {
                return val + (len - 1);
            } else {
                while (len-- > 1) val = unsafe_yyjson_get_next(val);
                return val;
            }
        }
    }
    return NULL;
}



/*==============================================================================
 * JSON Array Iterator API (Implementation)
 *============================================================================*/

struct yyjson_arr_iter {
    size_t idx; /**< current index, from 0 */
    size_t max; /**< maximum index, idx < max */
    yyjson_val *cur; /**< current value */
};

yyjson_api_inline bool yyjson_arr_iter_init(yyjson_val *arr,
                                            yyjson_arr_iter *iter) {
    if (yyjson_likely(yyjson_is_arr(arr) && iter)) {
        iter->idx = 0;
        iter->max = unsafe_yyjson_get_len(arr);
        iter->cur = unsafe_yyjson_get_first(arr);
        return true;
    }
    if (iter) memset(iter, 0, sizeof(yyjson_arr_iter));
    return false;
}

yyjson_api_inline bool yyjson_arr_iter_has_next(yyjson_arr_iter *iter) {
    return iter ? iter->idx < iter->max : false;
}

yyjson_api_inline yyjson_val *yyjson_arr_iter_next(yyjson_arr_iter *iter) {
    yyjson_val *val;
    if (iter && iter->idx < iter->max) {
        val = iter->cur;
        iter->cur = unsafe_yyjson_get_next(val);
        iter->idx++;
        return val;
    }
    return NULL;
}



/*==============================================================================
 * JSON Object API (Implementation)
 *============================================================================*/

yyjson_api_inline size_t yyjson_obj_size(yyjson_val *obj) {
    return yyjson_is_obj(obj) ? unsafe_yyjson_get_len(obj) : 0;
}

yyjson_api_inline yyjson_val *yyjson_obj_get(yyjson_val *obj,
                                             const char *key) {
    return yyjson_obj_getn(obj, key, key ? strlen(key) : 0);
}

yyjson_api_inline yyjson_val *yyjson_obj_getn(yyjson_val *obj,
                                              const char *_key,
                                              size_t key_len) {
    uint64_t tag = (((uint64_t)key_len) << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
    if (yyjson_likely(yyjson_is_obj(obj) && _key)) {
        size_t len = unsafe_yyjson_get_len(obj);
        yyjson_val *key = unsafe_yyjson_get_first(obj);
        while (len-- > 0) {
            if (key->tag == tag &&
                memcmp(key->uni.ptr, _key, key_len) == 0) {
                return key + 1;
            }
            key = unsafe_yyjson_get_next(key + 1);
        }
    }
    return NULL;
}



/*==============================================================================
 * JSON Object Iterator API (Implementation)
 *============================================================================*/

struct yyjson_obj_iter {
    size_t idx; /**< current key index, from 0 */
    size_t max; /**< maximum key index, idx < max */
    yyjson_val *cur; /**< current key */
    yyjson_val *obj; /**< the object being iterated */
};

yyjson_api_inline bool yyjson_obj_iter_init(yyjson_val *obj,
                                            yyjson_obj_iter *iter) {
    if (yyjson_likely(yyjson_is_obj(obj) && iter)) {
        iter->idx = 0;
        iter->max = unsafe_yyjson_get_len(obj);
        iter->cur = unsafe_yyjson_get_first(obj);
        iter->obj = obj;
        return true;
    }
    if (iter) memset(iter, 0, sizeof(yyjson_obj_iter));
    return false;
}

yyjson_api_inline bool yyjson_obj_iter_has_next(yyjson_obj_iter *iter) {
    return iter ? iter->idx < iter->max : false;
}

yyjson_api_inline yyjson_val *yyjson_obj_iter_next(yyjson_obj_iter *iter) {
    if (iter && iter->idx < iter->max) {
        yyjson_val *key = iter->cur;
        iter->idx++;
        iter->cur = unsafe_yyjson_get_next(key + 1);
        return key;
    }
    return NULL;
}

yyjson_api_inline yyjson_val *yyjson_obj_iter_get_val(yyjson_val *key) {
    return key ? key + 1 : NULL;
}

yyjson_api_inline yyjson_val *yyjson_obj_iter_get(yyjson_obj_iter *iter,
                                                  const char *key) {
    return yyjson_obj_iter_getn(iter, key, key ? strlen(key) : 0);
}

yyjson_api_inline yyjson_val *yyjson_obj_iter_getn(yyjson_obj_iter *iter,
                                                   const char *key,
                                                   size_t key_len) {
    if (iter && key) {
        size_t idx = iter->idx;
        size_t max = iter->max;
        yyjson_val *cur = iter->cur;
        if (yyjson_unlikely(idx == max)) {
            idx = 0;
            cur = unsafe_yyjson_get_first(iter->obj);
        }
        while (idx++ < max) {
            yyjson_val *next = unsafe_yyjson_get_next(cur + 1);
            if (unsafe_yyjson_get_len(cur) == key_len &&
                memcmp(cur->uni.str, key, key_len) == 0) {
                iter->idx = idx;
                iter->cur = next;
                return cur + 1;
            }
            cur = next;
            if (idx == iter->max && iter->idx < iter->max) {
                idx = 0;
                max = iter->idx;
                cur = unsafe_yyjson_get_first(iter->obj);
            }
        }
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Structure (Implementation)
 *============================================================================*/

/**
 Mutable JSON value, 24 bytes.
 The 'tag' and 'uni' field is same as immutable value.
 The 'next' field links all elements inside the container to be a cycle.
 */
struct yyjson_mut_val {
    uint64_t tag; /**< type, subtype and length */
    yyjson_val_uni uni; /**< payload */
    yyjson_mut_val *next; /**< the next value in circular linked list */
};

/**
 A memory chunk in string memory pool.
 */
typedef struct yyjson_str_chunk {
    struct yyjson_str_chunk *next;
    /* flexible array member here */
} yyjson_str_chunk;

/**
 A memory pool to hold all strings in a mutable document.
 */
typedef struct yyjson_str_pool {
    char *cur; /* cursor inside current chunk */
    char *end; /* the end of current chunk */
    size_t chunk_size; /* chunk size in bytes while creating new chunk */
    size_t chunk_size_max; /* maximum chunk size in bytes */
    yyjson_str_chunk *chunks; /* a linked list of chunks, nullable */
} yyjson_str_pool;

/**
 A memory chunk in value memory pool.
 */
typedef struct yyjson_val_chunk {
    struct yyjson_val_chunk *next;
    /* flexible array member here */
} yyjson_val_chunk;

/**
 A memory pool to hold all values in a mutable document.
 */
typedef struct yyjson_val_pool {
    yyjson_mut_val *cur; /* cursor inside current chunk */
    yyjson_mut_val *end; /* the end of current chunk */
    size_t chunk_size; /* chunk size in bytes while creating new chunk */
    size_t chunk_size_max; /* maximum chunk size in bytes */
    yyjson_val_chunk *chunks; /* a linked list of chunks, nullable */
} yyjson_val_pool;

struct yyjson_mut_doc {
    yyjson_mut_val *root; /**< root value of the JSON document, nullable */
    yyjson_alc alc; /**< a valid allocator, nonnull */
    yyjson_str_pool str_pool; /**< string memory pool */
    yyjson_val_pool val_pool; /**< value memory pool */
};

/* Ensures the capacity to at least equal to the specified byte length. */
yyjson_api bool unsafe_yyjson_str_pool_grow(yyjson_str_pool *pool,
                                            yyjson_alc *alc, size_t len);

/* Ensures the capacity to at least equal to the specified value count. */
yyjson_api bool unsafe_yyjson_val_pool_grow(yyjson_val_pool *pool,
                                            yyjson_alc *alc, size_t count);

yyjson_api_inline char *unsafe_yyjson_mut_strncpy(yyjson_mut_doc *doc,
                                                  const char *str, size_t len) {
    char *mem;
    yyjson_alc *alc = &doc->alc;
    yyjson_str_pool *pool = &doc->str_pool;
    
    if (!str) return NULL;
    if (yyjson_unlikely((size_t)(pool->end - pool->cur) <= len)) {
        if (yyjson_unlikely(!unsafe_yyjson_str_pool_grow(pool, alc, len + 1))) {
            return NULL;
        }
    }
    
    mem = pool->cur;
    pool->cur = mem + len + 1;
    memcpy((void *)mem, (const void *)str, len);
    mem[len] = '\0';
    return mem;
}

yyjson_api_inline yyjson_mut_val *unsafe_yyjson_mut_val(yyjson_mut_doc *doc,
                                                        size_t count) {
    yyjson_mut_val *val;
    yyjson_alc *alc = &doc->alc;
    yyjson_val_pool *pool = &doc->val_pool;
    if (yyjson_unlikely((size_t)(pool->end - pool->cur) < count)) {
        if (yyjson_unlikely(!unsafe_yyjson_val_pool_grow(pool, alc, count))) {
            return NULL;
        }
    }
    
    val = pool->cur;
    pool->cur += count;
    return val;
}



/*==============================================================================
 * Mutable JSON Document API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_mut_val *yyjson_mut_doc_get_root(yyjson_mut_doc *doc) {
    return doc ? doc->root : NULL;
}

yyjson_api_inline void yyjson_mut_doc_set_root(yyjson_mut_doc *doc,
                                               yyjson_mut_val *root) {
    if (doc) doc->root = root;
}



/*==============================================================================
 * Mutable JSON Value Type API (Implementation)
 *============================================================================*/

yyjson_api_inline bool yyjson_mut_is_raw(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_raw(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_null(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_null(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_true(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_true(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_false(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_false(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_bool(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_bool(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_uint(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_uint(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_sint(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_sint(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_int(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_int(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_real(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_real(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_num(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_num(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_str(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_str(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_arr(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_arr(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_obj(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_obj(val) : false;
}

yyjson_api_inline bool yyjson_mut_is_ctn(yyjson_mut_val *val) {
    return val ? unsafe_yyjson_is_ctn(val) : false;
}



/*==============================================================================
 * Mutable JSON Value Content API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_type yyjson_mut_get_type(yyjson_mut_val *val) {
    return yyjson_get_type((yyjson_val *)val);
}

yyjson_api_inline yyjson_subtype yyjson_mut_get_subtype(yyjson_mut_val *val) {
    return yyjson_get_subtype((yyjson_val *)val);
}

yyjson_api_inline uint8_t yyjson_mut_get_tag(yyjson_mut_val *val) {
    return yyjson_get_tag((yyjson_val *)val);
}

yyjson_api_inline const char *yyjson_mut_get_type_desc(yyjson_mut_val *val) {
    return yyjson_get_type_desc((yyjson_val *)val);
}

yyjson_api_inline const char *yyjson_mut_get_raw(yyjson_mut_val *val) {
    return yyjson_get_raw((yyjson_val *)val);
}

yyjson_api_inline bool yyjson_mut_get_bool(yyjson_mut_val *val) {
    return yyjson_get_bool((yyjson_val *)val);
}

yyjson_api_inline uint64_t yyjson_mut_get_uint(yyjson_mut_val *val) {
    return yyjson_get_uint((yyjson_val *)val);
}

yyjson_api_inline int64_t yyjson_mut_get_sint(yyjson_mut_val *val) {
    return yyjson_get_sint((yyjson_val *)val);
}

yyjson_api_inline int yyjson_mut_get_int(yyjson_mut_val *val) {
    return yyjson_get_int((yyjson_val *)val);
}

yyjson_api_inline double yyjson_mut_get_real(yyjson_mut_val *val) {
    return yyjson_get_real((yyjson_val *)val);
}

yyjson_api_inline const char *yyjson_mut_get_str(yyjson_mut_val *val) {
    return yyjson_get_str((yyjson_val *)val);
}

yyjson_api_inline size_t yyjson_mut_get_len(yyjson_mut_val *val) {
    return yyjson_get_len((yyjson_val *)val);
}

yyjson_api_inline bool yyjson_mut_equals_str(yyjson_mut_val *val,
                                             const char *str) {
    return yyjson_equals_str((yyjson_val *)val, str);
}

yyjson_api_inline bool yyjson_mut_equals_strn(yyjson_mut_val *val,
                                              const char *str, size_t len) {
    return yyjson_equals_strn((yyjson_val *)val, str, len);
}

yyjson_api bool unsafe_yyjson_mut_equals(yyjson_mut_val *lhs,
                                         yyjson_mut_val *rhs);

yyjson_api_inline bool yyjson_mut_equals(yyjson_mut_val *lhs,
                                         yyjson_mut_val *rhs) {
    if (yyjson_unlikely(!lhs || !rhs)) return false;
    return unsafe_yyjson_mut_equals(lhs, rhs);
}



/*==============================================================================
 * Mutable JSON Value Creation API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_mut_val *yyjson_mut_raw(yyjson_mut_doc *doc,
                                                 const char *str) {
    if (yyjson_likely(str)) return yyjson_mut_rawn(doc, str, strlen(str));
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_rawn(yyjson_mut_doc *doc,
                                                  const char *str,
                                                  size_t len) {
    if (yyjson_likely(doc && str)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = ((uint64_t)len << YYJSON_TAG_BIT) | YYJSON_TYPE_RAW;
            val->uni.str = str;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_rawcpy(yyjson_mut_doc *doc,
                                                    const char *str) {
    if (yyjson_likely(str)) return yyjson_mut_rawncpy(doc, str, strlen(str));
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_rawncpy(yyjson_mut_doc *doc,
                                                     const char *str,
                                                     size_t len) {
    if (yyjson_likely(doc && str)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        char *new_str = unsafe_yyjson_mut_strncpy(doc, str, len);
        if (yyjson_likely(val && new_str)) {
            val->tag = ((uint64_t)len << YYJSON_TAG_BIT) | YYJSON_TYPE_RAW;
            val->uni.str = new_str;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_null(yyjson_mut_doc *doc) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_NULL | YYJSON_SUBTYPE_NONE;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_true(yyjson_mut_doc *doc) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_TRUE;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_false(yyjson_mut_doc *doc) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_FALSE;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_bool(yyjson_mut_doc *doc,
                                                  bool _val) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_BOOL | (uint8_t)((uint8_t)_val << 3);
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_uint(yyjson_mut_doc *doc,
                                                  uint64_t num) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
            val->uni.u64 = num;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_sint(yyjson_mut_doc *doc,
                                                  int64_t num) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
            val->uni.i64 = num;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_int(yyjson_mut_doc *doc,
                                                 int64_t num) {
    return yyjson_mut_sint(doc, num);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_real(yyjson_mut_doc *doc,
                                                  double num) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_REAL;
            val->uni.f64 = num;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_str(yyjson_mut_doc *doc,
                                                 const char *str) {
    if (yyjson_likely(str)) return yyjson_mut_strn(doc, str, strlen(str));
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_strn(yyjson_mut_doc *doc,
                                                  const char *str,
                                                  size_t len) {
    if (yyjson_likely(doc && str)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = ((uint64_t)len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
            val->uni.str = str;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_strcpy(yyjson_mut_doc *doc,
                                                    const char *str) {
    if (yyjson_likely(str)) return yyjson_mut_strncpy(doc, str, strlen(str));
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_strncpy(yyjson_mut_doc *doc,
                                                     const char *str,
                                                     size_t len) {
    if (yyjson_likely(doc && str)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        char *new_str = unsafe_yyjson_mut_strncpy(doc, str, len);
        if (yyjson_likely(val && new_str)) {
            val->tag = ((uint64_t)len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
            val->uni.str = new_str;
            return val;
        }
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Array API (Implementation)
 *============================================================================*/

yyjson_api_inline size_t yyjson_mut_arr_size(yyjson_mut_val *arr) {
    return yyjson_mut_is_arr(arr) ? unsafe_yyjson_get_len(arr) : 0;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_get(yyjson_mut_val *arr,
                                                     size_t idx) {
    if (yyjson_likely(idx < yyjson_mut_arr_size(arr))) {
        yyjson_mut_val *val = (yyjson_mut_val *)arr->uni.ptr;
        while (idx-- > 0) val = val->next;
        return val->next;
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_get_first(
    yyjson_mut_val *arr) {
    if (yyjson_likely(yyjson_mut_arr_size(arr) > 0)) {
        return ((yyjson_mut_val *)arr->uni.ptr)->next;
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_get_last(
    yyjson_mut_val *arr) {
    if (yyjson_likely(yyjson_mut_arr_size(arr) > 0)) {
        return ((yyjson_mut_val *)arr->uni.ptr);
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Array Iterator API (Implementation)
 *============================================================================*/

struct yyjson_mut_arr_iter {
    size_t idx; /**< current index, from 0 */
    size_t max; /**< maximum index, idx < max */
    yyjson_mut_val *cur; /**< current value */
    yyjson_mut_val *pre; /**< previous value */
    yyjson_mut_val *arr; /**< the array being iterated */
};

yyjson_api_inline bool yyjson_mut_arr_iter_init(yyjson_mut_val *arr,
                                                yyjson_mut_arr_iter *iter) {
    if (yyjson_likely(yyjson_mut_is_arr(arr) && iter)) {
        iter->idx = 0;
        iter->max = unsafe_yyjson_get_len(arr);
        iter->cur = iter->max ? (yyjson_mut_val *)arr->uni.ptr : NULL;
        iter->pre = NULL;
        iter->arr = arr;
        return true;
    }
    if (iter) memset(iter, 0, sizeof(yyjson_mut_arr_iter));
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_iter_has_next(yyjson_mut_arr_iter *iter) {
    return iter ? iter->idx < iter->max : false;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_iter_next(
    yyjson_mut_arr_iter *iter) {
    if (iter && iter->idx < iter->max) {
        yyjson_mut_val *val = iter->cur;
        iter->pre = val;
        iter->cur = val->next;
        iter->idx++;
        return iter->cur;
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_iter_remove(
    yyjson_mut_arr_iter *iter) {
    if (yyjson_likely(iter && 0 < iter->idx && iter->idx <= iter->max)) {
        yyjson_mut_val *prev = iter->pre;
        yyjson_mut_val *cur = iter->cur;
        yyjson_mut_val *next = cur->next;
        if (yyjson_unlikely(iter->idx == iter->max)) iter->arr->uni.ptr = prev;
        iter->idx--;
        iter->max--;
        unsafe_yyjson_set_len(iter->arr, iter->max);
        prev->next = next;
        iter->cur = next;
        return cur;
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Array Creation API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr(yyjson_mut_doc *doc) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_ARR | YYJSON_SUBTYPE_NONE;
            return val;
        }
    }
    return NULL;
}

#define yyjson_mut_arr_with_func(func) \
    if (yyjson_likely(doc && ((0 < count && count < \
        (~(size_t)0) / sizeof(yyjson_mut_val) && vals) || count == 0))) { \
        yyjson_mut_val *arr = unsafe_yyjson_mut_val(doc, 1 + count); \
        if (yyjson_likely(arr)) { \
            arr->tag = ((uint64_t)count << YYJSON_TAG_BIT) | YYJSON_TYPE_ARR; \
            if (count > 0) { \
                size_t i; \
                for (i = 0; i < count; i++) { \
                    yyjson_mut_val *val = arr + i + 1; \
                    func \
                    val->next = val + 1; \
                } \
                arr[count].next = arr + 1; \
                arr->uni.ptr = arr + count; \
            } \
            return arr; \
        } \
    } \
    return NULL

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_bool(
    yyjson_mut_doc *doc, const bool *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_BOOL | (uint8_t)((uint8_t)vals[i] << 3);
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint(
    yyjson_mut_doc *doc, const int64_t *vals, size_t count) {
    return yyjson_mut_arr_with_sint64(doc, vals, count);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint(
    yyjson_mut_doc *doc, const uint64_t *vals, size_t count) {
    return yyjson_mut_arr_with_uint64(doc, vals, count);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_real(
    yyjson_mut_doc *doc, const double *vals, size_t count) {
    return yyjson_mut_arr_with_double(doc, vals, count);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint8(
    yyjson_mut_doc *doc, const int8_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
        val->uni.i64 = (int64_t)vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint16(
    yyjson_mut_doc *doc, const int16_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
        val->uni.i64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint32(
    yyjson_mut_doc *doc, const int32_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
        val->uni.i64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_sint64(
    yyjson_mut_doc *doc, const int64_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
        val->uni.i64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint8(
    yyjson_mut_doc *doc, const uint8_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
        val->uni.u64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint16(
    yyjson_mut_doc *doc, const uint16_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
        val->uni.u64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint32(
    yyjson_mut_doc *doc, const uint32_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
        val->uni.u64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_uint64(
    yyjson_mut_doc *doc, const uint64_t *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
        val->uni.u64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_float(
    yyjson_mut_doc *doc, const float *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_REAL;
        val->uni.f64 = (double)vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_double(
    yyjson_mut_doc *doc, const double *vals, size_t count) {
    yyjson_mut_arr_with_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_REAL;
        val->uni.f64 = vals[i];
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_str(
    yyjson_mut_doc *doc, const char **vals, size_t count) {
    yyjson_mut_arr_with_func({
        uint64_t len = (uint64_t)strlen(vals[i]);
        val->tag = (len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        val->uni.str = vals[i];
        if (yyjson_unlikely(!val->uni.str)) return NULL;
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_strn(
    yyjson_mut_doc *doc, const char **vals, const size_t *lens, size_t count) {
    if (yyjson_unlikely(count > 0 && !lens)) return NULL;
    yyjson_mut_arr_with_func({
        val->tag = ((uint64_t)lens[i] << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        val->uni.str = vals[i];
        if (yyjson_unlikely(!val->uni.str)) return NULL;
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_strcpy(
    yyjson_mut_doc *doc, const char **vals, size_t count) {
    size_t len;
    const char *str;
    yyjson_mut_arr_with_func({
        str = vals[i];
        if (!str) return NULL;
        len = strlen(str);
        val->tag = ((uint64_t)len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        val->uni.str = unsafe_yyjson_mut_strncpy(doc, str, len);
        if (yyjson_unlikely(!val->uni.str)) return NULL;
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_with_strncpy(
    yyjson_mut_doc *doc, const char **vals, const size_t *lens, size_t count) {
    size_t len;
    const char *str;
    if (yyjson_unlikely(count > 0 && !lens)) return NULL;
    yyjson_mut_arr_with_func({
        str = vals[i];
        len = lens[i];
        val->tag = ((uint64_t)len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        val->uni.str = unsafe_yyjson_mut_strncpy(doc, str, len);
        if (yyjson_unlikely(!val->uni.str)) return NULL;
    });
}

#undef yyjson_mut_arr_with_func



/*==============================================================================
 * Mutable JSON Array Modification API (Implementation)
 *============================================================================*/

yyjson_api_inline bool yyjson_mut_arr_insert(yyjson_mut_val *arr,
                                             yyjson_mut_val *val, size_t idx) {
    if (yyjson_likely(yyjson_mut_is_arr(arr) && val)) {
        size_t len = unsafe_yyjson_get_len(arr);
        if (yyjson_likely(idx <= len)) {
            unsafe_yyjson_set_len(arr, len + 1);
            if (len == 0) {
                val->next = val;
                arr->uni.ptr = val;
            } else {
                yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
                yyjson_mut_val *next = prev->next;
                if (idx == len) {
                    prev->next = val;
                    val->next = next;
                    arr->uni.ptr = val;
                } else {
                    while (idx-- > 0) {
                        prev = next;
                        next = next->next;
                    }
                    prev->next = val;
                    val->next = next;
                }
            }
            return true;
        }
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_append(yyjson_mut_val *arr,
                                             yyjson_mut_val *val) {
    if (yyjson_likely(yyjson_mut_is_arr(arr) && val)) {
        size_t len = unsafe_yyjson_get_len(arr);
        unsafe_yyjson_set_len(arr, len + 1);
        if (len == 0) {
            val->next = val;
        } else {
            yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
            yyjson_mut_val *next = prev->next;
            prev->next = val;
            val->next = next;
        }
        arr->uni.ptr = val;
        return true;
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_prepend(yyjson_mut_val *arr,
                                              yyjson_mut_val *val) {
    if (yyjson_likely(yyjson_mut_is_arr(arr) && val)) {
        size_t len = unsafe_yyjson_get_len(arr);
        unsafe_yyjson_set_len(arr, len + 1);
        if (len == 0) {
            val->next = val;
            arr->uni.ptr = val;
        } else {
            yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
            yyjson_mut_val *next = prev->next;
            prev->next = val;
            val->next = next;
        }
        return true;
    }
    return false;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_replace(yyjson_mut_val *arr,
                                                         size_t idx,
                                                         yyjson_mut_val *val) {
    if (yyjson_likely(yyjson_mut_is_arr(arr) && val)) {
        size_t len = unsafe_yyjson_get_len(arr);
        if (yyjson_likely(idx < len)) {
            if (yyjson_likely(len > 1)) {
                yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
                yyjson_mut_val *next = prev->next;
                while (idx-- > 0) {
                    prev = next;
                    next = next->next;
                }
                prev->next = val;
                val->next = next->next;
                if ((void *)next == arr->uni.ptr) arr->uni.ptr = val;
                return next;
            } else {
                yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
                val->next = val;
                arr->uni.ptr = val;
                return prev;
            }
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_remove(yyjson_mut_val *arr,
                                                        size_t idx) {
    if (yyjson_likely(yyjson_mut_is_arr(arr))) {
        size_t len = unsafe_yyjson_get_len(arr);
        if (yyjson_likely(idx < len)) {
            unsafe_yyjson_set_len(arr, len - 1);
            if (yyjson_likely(len > 1)) {
                yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
                yyjson_mut_val *next = prev->next;
                while (idx-- > 0) {
                    prev = next;
                    next = next->next;
                }
                prev->next = next->next;
                if ((void *)next == arr->uni.ptr) arr->uni.ptr = prev;
                return next;
            } else {
                return ((yyjson_mut_val *)arr->uni.ptr);
            }
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_remove_first(
    yyjson_mut_val *arr) {
    if (yyjson_likely(yyjson_mut_is_arr(arr))) {
        size_t len = unsafe_yyjson_get_len(arr);
        if (len > 1) {
            yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
            yyjson_mut_val *next = prev->next;
            prev->next = next->next;
            unsafe_yyjson_set_len(arr, len - 1);
            return next;
        } else if (len == 1) {
            yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
            unsafe_yyjson_set_len(arr, 0);
            return prev;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_remove_last(
    yyjson_mut_val *arr) {
    if (yyjson_likely(yyjson_mut_is_arr(arr))) {
        size_t len = unsafe_yyjson_get_len(arr);
        if (yyjson_likely(len > 1)) {
            yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
            yyjson_mut_val *next = prev->next;
            unsafe_yyjson_set_len(arr, len - 1);
            while (--len > 0) prev = prev->next;
            prev->next = next;
            next = (yyjson_mut_val *)arr->uni.ptr;
            arr->uni.ptr = prev;
            return next;
        } else if (len == 1) {
            yyjson_mut_val *prev = ((yyjson_mut_val *)arr->uni.ptr);
            unsafe_yyjson_set_len(arr, 0);
            return prev;
        }
    }
    return NULL;
}

yyjson_api_inline bool yyjson_mut_arr_remove_range(yyjson_mut_val *arr,
                                                   size_t _idx, size_t _len) {
    if (yyjson_likely(yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *prev, *next;
        bool tail_removed;
        size_t len = unsafe_yyjson_get_len(arr);
        if (yyjson_unlikely(_idx + _len > len)) return false;
        if (yyjson_unlikely(_len == 0)) return true;
        unsafe_yyjson_set_len(arr, len - _len);
        if (yyjson_unlikely(len == _len)) return true;
        tail_removed = (_idx + _len == len);
        prev = ((yyjson_mut_val *)arr->uni.ptr);
        while (_idx-- > 0) prev = prev->next;
        next = prev->next;
        while (_len-- > 0) next = next->next;
        prev->next = next;
        if (yyjson_unlikely(tail_removed)) arr->uni.ptr = prev;
        return true;
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_clear(yyjson_mut_val *arr) {
    if (yyjson_likely(yyjson_mut_is_arr(arr))) {
        unsafe_yyjson_set_len(arr, 0);
        return true;
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_rotate(yyjson_mut_val *arr,
                                             size_t idx) {
    if (yyjson_likely(yyjson_mut_is_arr(arr) &&
                      unsafe_yyjson_get_len(arr) > idx)) {
        yyjson_mut_val *val = (yyjson_mut_val *)arr->uni.ptr;
        while (idx-- > 0) val = val->next;
        arr->uni.ptr = (void *)val;
        return true;
    }
    return false;
}



/*==============================================================================
 * Mutable JSON Array Modification Convenience API (Implementation)
 *============================================================================*/

yyjson_api_inline bool yyjson_mut_arr_add_val(yyjson_mut_val *arr,
                                              yyjson_mut_val *val) {
    return yyjson_mut_arr_append(arr, val);
}

yyjson_api_inline bool yyjson_mut_arr_add_null(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_null(doc);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_true(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_true(doc);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_false(yyjson_mut_doc *doc,
                                                yyjson_mut_val *arr) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_false(doc);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_bool(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               bool _val) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_bool(doc, _val);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_uint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               uint64_t num) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_uint(doc, num);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_sint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               int64_t num) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_sint(doc, num);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_int(yyjson_mut_doc *doc,
                                              yyjson_mut_val *arr,
                                              int64_t num) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_sint(doc, num);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_real(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               double num) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_real(doc, num);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_str(yyjson_mut_doc *doc,
                                              yyjson_mut_val *arr,
                                              const char *str) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_str(doc, str);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_strn(yyjson_mut_doc *doc,
                                               yyjson_mut_val *arr,
                                               const char *str, size_t len) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_strn(doc, str, len);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_strcpy(yyjson_mut_doc *doc,
                                                 yyjson_mut_val *arr,
                                                 const char *str) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_strcpy(doc, str);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_arr_add_strncpy(yyjson_mut_doc *doc,
                                                  yyjson_mut_val *arr,
                                                  const char *str, size_t len) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_strncpy(doc, str, len);
        return yyjson_mut_arr_append(arr, val);
    }
    return false;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_add_arr(yyjson_mut_doc *doc,
                                                         yyjson_mut_val *arr) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_arr(doc);
        return yyjson_mut_arr_append(arr, val) ? val : NULL;
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_arr_add_obj(yyjson_mut_doc *doc,
                                                         yyjson_mut_val *arr) {
    if (yyjson_likely(doc && yyjson_mut_is_arr(arr))) {
        yyjson_mut_val *val = yyjson_mut_obj(doc);
        return yyjson_mut_arr_append(arr, val) ? val : NULL;
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Object API (Implementation)
 *============================================================================*/

yyjson_api_inline size_t yyjson_mut_obj_size(yyjson_mut_val *obj) {
    return yyjson_mut_is_obj(obj) ? unsafe_yyjson_get_len(obj) : 0;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_get(yyjson_mut_val *obj,
                                                     const char *key) {
    return yyjson_mut_obj_getn(obj, key, key ? strlen(key) : 0);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_getn(yyjson_mut_val *obj,
                                                      const char *_key,
                                                      size_t key_len) {
    uint64_t tag = (((uint64_t)key_len) << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
    size_t len = yyjson_mut_obj_size(obj);
    if (yyjson_likely(len && _key)) {
        yyjson_mut_val *key = ((yyjson_mut_val *)obj->uni.ptr)->next->next;
        while (len-- > 0) {
            if (key->tag == tag &&
                memcmp(key->uni.ptr, _key, key_len) == 0) {
                return key->next;
            }
            key = key->next->next;
        }
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Object Iterator API (Implementation)
 *============================================================================*/

struct yyjson_mut_obj_iter {
    size_t idx; /**< current key index, from 0 */
    size_t max; /**< maximum key index, idx < max */
    yyjson_mut_val *cur; /**< current key */
    yyjson_mut_val *pre; /**< previous key */
    yyjson_mut_val *obj; /**< the object being iterated */
};

yyjson_api_inline bool yyjson_mut_obj_iter_init(yyjson_mut_val *obj,
                                                yyjson_mut_obj_iter *iter) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) && iter)) {
        iter->idx = 0;
        iter->max = unsafe_yyjson_get_len(obj);
        iter->cur = iter->max ? (yyjson_mut_val *)obj->uni.ptr : NULL;
        iter->pre = NULL;
        iter->obj = obj;
        return true;
    }
    if (iter) memset(iter, 0, sizeof(yyjson_mut_obj_iter));
    return false;
}

yyjson_api_inline bool yyjson_mut_obj_iter_has_next(yyjson_mut_obj_iter *iter) {
    return iter ? iter->idx < iter->max : false;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_next(
    yyjson_mut_obj_iter *iter) {
    if (iter && iter->idx < iter->max) {
        yyjson_mut_val *key = iter->cur;
        iter->pre = key;
        iter->cur = key->next->next;
        iter->idx++;
        return iter->cur;
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_get_val(
    yyjson_mut_val *key) {
    return key ? key->next : NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_remove(
    yyjson_mut_obj_iter *iter) {
    if (yyjson_likely(iter && 0 < iter->idx && iter->idx <= iter->max)) {
        yyjson_mut_val *prev = iter->pre;
        yyjson_mut_val *cur = iter->cur;
        yyjson_mut_val *next = cur->next->next;
        if (yyjson_unlikely(iter->idx == iter->max)) iter->obj->uni.ptr = prev;
        iter->idx--;
        iter->max--;
        unsafe_yyjson_set_len(iter->obj, iter->max);
        prev->next->next = next;
        iter->cur = next;
        return cur;
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_get(
    yyjson_mut_obj_iter *iter, const char *key) {
    return yyjson_mut_obj_iter_getn(iter, key, key ? strlen(key) : 0);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_iter_getn(
    yyjson_mut_obj_iter *iter, const char *key, size_t key_len) {
    if (iter && key) {
        size_t idx = 0;
        size_t max = iter->max;
        yyjson_mut_val *pre, *cur = iter->cur;
        while (idx++ < max) {
            pre = cur;
            cur = cur->next->next;
            if (unsafe_yyjson_get_len(cur) == key_len &&
                memcmp(cur->uni.str, key, key_len) == 0) {
                iter->idx += idx;
                if (iter->idx > max) iter->idx -= max + 1;
                iter->pre = pre;
                iter->cur = cur;
                return cur->next;
            }
        }
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Object Creation API (Implementation)
 *============================================================================*/

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj(yyjson_mut_doc *doc) {
    if (yyjson_likely(doc)) {
        yyjson_mut_val *val = unsafe_yyjson_mut_val(doc, 1);
        if (yyjson_likely(val)) {
            val->tag = YYJSON_TYPE_OBJ | YYJSON_SUBTYPE_NONE;
            return val;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_with_str(yyjson_mut_doc *doc,
                                                          const char **keys,
                                                          const char **vals,
                                                          size_t count) {
    if (yyjson_likely(doc && ((count > 0 && keys && vals) || (count == 0)))) {
        yyjson_mut_val *obj = unsafe_yyjson_mut_val(doc, 1 + count * 2);
        if (yyjson_likely(obj)) {
            obj->tag = ((uint64_t)count << YYJSON_TAG_BIT) | YYJSON_TYPE_OBJ;
            if (count > 0) {
                size_t i;
                for (i = 0; i < count; i++) {
                    yyjson_mut_val *key = obj + (i * 2 + 1);
                    yyjson_mut_val *val = obj + (i * 2 + 2);
                    uint64_t key_len = (uint64_t)strlen(keys[i]);
                    uint64_t val_len = (uint64_t)strlen(vals[i]);
                    key->tag = (key_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
                    val->tag = (val_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
                    key->uni.str = keys[i];
                    val->uni.str = vals[i];
                    key->next = val;
                    val->next = val + 1;
                }
                obj[count * 2].next = obj + 1;
                obj->uni.ptr = obj + (count * 2 - 1);
            }
            return obj;
        }
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_with_kv(yyjson_mut_doc *doc,
                                                         const char **pairs,
                                                         size_t count) {
    if (yyjson_likely(doc && ((count > 0 && pairs) || (count == 0)))) {
        yyjson_mut_val *obj = unsafe_yyjson_mut_val(doc, 1 + count * 2);
        if (yyjson_likely(obj)) {
            obj->tag = ((uint64_t)count << YYJSON_TAG_BIT) | YYJSON_TYPE_OBJ;
            if (count > 0) {
                size_t i;
                for (i = 0; i < count; i++) {
                    yyjson_mut_val *key = obj + (i * 2 + 1);
                    yyjson_mut_val *val = obj + (i * 2 + 2);
                    const char *key_str = pairs[i * 2 + 0];
                    const char *val_str = pairs[i * 2 + 1];
                    uint64_t key_len = (uint64_t)strlen(key_str);
                    uint64_t val_len = (uint64_t)strlen(val_str);
                    key->tag = (key_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
                    val->tag = (val_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
                    key->uni.str = key_str;
                    val->uni.str = val_str;
                    key->next = val;
                    val->next = val + 1;
                }
                obj[count * 2].next = obj + 1;
                obj->uni.ptr = obj + (count * 2 - 1);
            }
            return obj;
        }
    }
    return NULL;
}



/*==============================================================================
 * Mutable JSON Object Modification API (Implementation)
 *============================================================================*/

yyjson_api_inline void unsafe_yyjson_mut_obj_add(yyjson_mut_val *obj,
                                                 yyjson_mut_val *key,
                                                 yyjson_mut_val *val,
                                                 size_t len) {
    if (yyjson_likely(len)) {
        yyjson_mut_val *prev_val = ((yyjson_mut_val *)obj->uni.ptr)->next;
        yyjson_mut_val *next_key = prev_val->next;
        prev_val->next = key;
        val->next = next_key;
    } else {
        val->next = key;
    }
    key->next = val;
    obj->uni.ptr = (void *)key;
    unsafe_yyjson_set_len(obj, len + 1);
}

yyjson_api_inline yyjson_mut_val *unsafe_yyjson_mut_obj_remove(
    yyjson_mut_val *obj, const char *key, size_t key_len, uint64_t key_tag) {
    size_t obj_len = unsafe_yyjson_get_len(obj);
    if (obj_len) {
        yyjson_mut_val *pre_key = (yyjson_mut_val *)obj->uni.ptr;
        yyjson_mut_val *cur_key = pre_key->next->next;
        yyjson_mut_val *removed_item = NULL;
        size_t i;
        for (i = 0; i < obj_len; i++) {
            if (key_tag == cur_key->tag &&
                memcmp(key, cur_key->uni.ptr, key_len) == 0) {
                if (!removed_item) removed_item = cur_key->next;
                cur_key = cur_key->next->next;
                pre_key->next->next = cur_key;
                if (i + 1 == obj_len) obj->uni.ptr = pre_key;
                i--;
                obj_len--;
            } else {
                pre_key = cur_key;
                cur_key = cur_key->next->next;
            }
        }
        unsafe_yyjson_set_len(obj, obj_len);
        return removed_item;
    } else {
        return NULL;
    }
}

yyjson_api_inline bool unsafe_yyjson_mut_obj_replace(yyjson_mut_val *obj,
                                                     yyjson_mut_val *key,
                                                     yyjson_mut_val *val) {
    size_t key_len = unsafe_yyjson_get_len(key);
    size_t obj_len = unsafe_yyjson_get_len(obj);
    if (obj_len) {
        yyjson_mut_val *pre_key = (yyjson_mut_val *)obj->uni.ptr;
        yyjson_mut_val *cur_key = pre_key->next->next;
        size_t i;
        for (i = 0; i < obj_len; i++) {
            if (key->tag == cur_key->tag &&
                memcmp(key->uni.str, cur_key->uni.ptr, key_len) == 0) {
                cur_key->next->tag = val->tag;
                cur_key->next->uni.u64 = val->uni.u64;
                return true;
            } else {
                cur_key = cur_key->next->next;
            }
        }
    }
    return false;
}

yyjson_api_inline void unsafe_yyjson_mut_obj_rotate(yyjson_mut_val *obj,
                                                    size_t idx) {
    yyjson_mut_val *key = (yyjson_mut_val *)obj->uni.ptr;
    while (idx-- > 0) key = key->next->next;
    obj->uni.ptr = (void *)key;
}

yyjson_api_inline bool yyjson_mut_obj_add(yyjson_mut_val *obj,
                                          yyjson_mut_val *key,
                                          yyjson_mut_val *val) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) &&
                      yyjson_mut_is_str(key) && val)) {
        unsafe_yyjson_mut_obj_add(obj, key, val, unsafe_yyjson_get_len(obj));
        return true;
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_obj_put(yyjson_mut_val *obj,
                                          yyjson_mut_val *key,
                                          yyjson_mut_val *val) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) &&
                      yyjson_mut_is_str(key))) {
        unsafe_yyjson_mut_obj_remove(obj, key->uni.str,
                                     unsafe_yyjson_get_len(key), key->tag);
        if (yyjson_likely(val)) {
            unsafe_yyjson_mut_obj_add(obj, key, val,
                                      unsafe_yyjson_get_len(obj));
        }
        return true;
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_obj_insert(yyjson_mut_val *obj,
                                             yyjson_mut_val *key,
                                             yyjson_mut_val *val,
                                             size_t idx) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) &&
                      yyjson_mut_is_str(key) && val)) {
        size_t len = unsafe_yyjson_get_len(obj);
        if (yyjson_likely(len >= idx)) {
            if (len > idx) {
                void *ptr = obj->uni.ptr;
                unsafe_yyjson_mut_obj_rotate(obj, idx);
                unsafe_yyjson_mut_obj_add(obj, key, val, len);
                obj->uni.ptr = ptr;
            } else {
                unsafe_yyjson_mut_obj_add(obj, key, val, len);
            }
            return true;
        }
    }
    return false;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove(yyjson_mut_val *obj,
    yyjson_mut_val *key) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) && yyjson_mut_is_str(key))) {
        return unsafe_yyjson_mut_obj_remove(obj, key->uni.str,
                                            unsafe_yyjson_get_len(key),
                                            key->tag);
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_key(
    yyjson_mut_val *obj, const char *key) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) && key)) {
        size_t key_len = strlen(key);
        uint64_t tag = ((uint64_t)key_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        return unsafe_yyjson_mut_obj_remove(obj, key, key_len, tag);
    }
    return NULL;
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_keyn(
    yyjson_mut_val *obj, const char *key, size_t key_len) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) && key)) {
        uint64_t tag = ((uint64_t)key_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        return unsafe_yyjson_mut_obj_remove(obj, key, key_len, tag);
    }
    return NULL;
}

yyjson_api_inline bool yyjson_mut_obj_clear(yyjson_mut_val *obj) {
    if (yyjson_likely(yyjson_mut_is_obj(obj))) {
        unsafe_yyjson_set_len(obj, 0);
        return true;
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_obj_replace(yyjson_mut_val *obj,
                                              yyjson_mut_val *key,
                                              yyjson_mut_val *val) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) &&
                      yyjson_mut_is_str(key) && val)) {
        return unsafe_yyjson_mut_obj_replace(obj, key, val);
    }
    return false;
}

yyjson_api_inline bool yyjson_mut_obj_rotate(yyjson_mut_val *obj,
                                             size_t idx) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) &&
                      unsafe_yyjson_get_len(obj) > idx)) {
        unsafe_yyjson_mut_obj_rotate(obj, idx);
        return true;
    }
    return false;
}



/*==============================================================================
 * Mutable JSON Object Modification Convenience API (Implementation)
 *============================================================================*/

#define yyjson_mut_obj_add_func(func) \
    if (yyjson_likely(doc && yyjson_mut_is_obj(obj) && _key)) { \
        yyjson_mut_val *key = unsafe_yyjson_mut_val(doc, 2); \
        if (yyjson_likely(key)) { \
            size_t len = unsafe_yyjson_get_len(obj); \
            yyjson_mut_val *val = key + 1; \
            key->tag = YYJSON_TYPE_STR | YYJSON_SUBTYPE_NONE; \
            key->tag |= (uint64_t)strlen(_key) << YYJSON_TAG_BIT; \
            key->uni.str = _key; \
            func \
            unsafe_yyjson_mut_obj_add(obj, key, val, len); \
            return true; \
        } \
    } \
    return false

yyjson_api_inline bool yyjson_mut_obj_add_null(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *_key) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_NULL | YYJSON_SUBTYPE_NONE;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_true(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *_key) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_TRUE;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_false(yyjson_mut_doc *doc,
                                                yyjson_mut_val *obj,
                                                const char *_key) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_BOOL | YYJSON_SUBTYPE_FALSE;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_bool(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *_key,
                                               bool _val) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_BOOL | (uint8_t)((uint8_t)(_val) << 3);
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_uint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *_key,
                                               uint64_t _val) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_UINT;
        val->uni.u64 = _val;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_sint(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *_key,
                                               int64_t _val) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
        val->uni.i64 = _val;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_int(yyjson_mut_doc *doc,
                                              yyjson_mut_val *obj,
                                              const char *_key,
                                              int64_t _val) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_SINT;
        val->uni.i64 = _val;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_real(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *_key,
                                               double _val) {
    yyjson_mut_obj_add_func({
        val->tag = YYJSON_TYPE_NUM | YYJSON_SUBTYPE_REAL;
        val->uni.f64 = _val;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_str(yyjson_mut_doc *doc,
                                              yyjson_mut_val *obj,
                                              const char *_key,
                                              const char *_val) {
    if (yyjson_unlikely(!_val)) return false;
    yyjson_mut_obj_add_func({
        val->tag = ((uint64_t)strlen(_val) << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        val->uni.str = _val;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_strn(yyjson_mut_doc *doc,
                                               yyjson_mut_val *obj,
                                               const char *_key,
                                               const char *_val,
                                               size_t _len) {
    if (yyjson_unlikely(!_val)) return false;
    yyjson_mut_obj_add_func({
        val->tag = ((uint64_t)_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
        val->uni.str = _val;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_strcpy(yyjson_mut_doc *doc,
                                                 yyjson_mut_val *obj,
                                                 const char *_key,
                                                 const char *_val) {
    if (yyjson_unlikely(!_val)) return false;
    yyjson_mut_obj_add_func({
        size_t _len = strlen(_val);
        val->uni.str = unsafe_yyjson_mut_strncpy(doc, _val, _len);
        if (yyjson_unlikely(!val->uni.str)) return false;
        val->tag = ((uint64_t)_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_strncpy(yyjson_mut_doc *doc,
                                                  yyjson_mut_val *obj,
                                                  const char *_key,
                                                  const char *_val,
                                                  size_t _len) {
    if (yyjson_unlikely(!_val)) return false;
    yyjson_mut_obj_add_func({
        val->uni.str = unsafe_yyjson_mut_strncpy(doc, _val, _len);
        if (yyjson_unlikely(!val->uni.str)) return false;
        val->tag = ((uint64_t)_len << YYJSON_TAG_BIT) | YYJSON_TYPE_STR;
    });
}

yyjson_api_inline bool yyjson_mut_obj_add_val(yyjson_mut_doc *doc,
                                              yyjson_mut_val *obj,
                                              const char *_key,
                                              yyjson_mut_val *_val) {
    if (yyjson_unlikely(!_val)) return false;
    yyjson_mut_obj_add_func({
        val = _val;
    });
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_str(yyjson_mut_val *obj,
                                                            const char *key) {
    return yyjson_mut_obj_remove_strn(obj, key, key ? strlen(key) : 0);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_obj_remove_strn(
    yyjson_mut_val *obj, const char *_key, size_t _len) {
    if (yyjson_likely(yyjson_mut_is_obj(obj) && _key)) {
        yyjson_mut_val *key;
        yyjson_mut_obj_iter iter;
        yyjson_mut_val *val_removed = NULL;
        yyjson_mut_obj_iter_init(obj, &iter);
        while ((key = yyjson_mut_obj_iter_next(&iter)) != NULL) {
            if (unsafe_yyjson_get_len(key) == _len &&
                memcmp(key->uni.str, _key, _len) == 0) {
                if (!val_removed) val_removed = key->next;
                yyjson_mut_obj_iter_remove(&iter);
            }
        }
        return val_removed;
    }
    return NULL;
}



/*==============================================================================
 * JSON Pointer API (Implementation)
 *============================================================================*/

/* `val` not null, `ptr` start with '/', `len` > 0. */
yyjson_api yyjson_val *unsafe_yyjson_get_pointer(yyjson_val *val,
                                                 const char *ptr,
                                                 size_t len);

/* `val` not null, `ptr` start with '/', `len` > 0. */
yyjson_api yyjson_mut_val *unsafe_yyjson_mut_get_pointer(yyjson_mut_val *val,
                                                         const char *ptr,
                                                         size_t len);

yyjson_api_inline yyjson_val *yyjson_get_pointern(yyjson_val *val,
                                                  const char *ptr,
                                                  size_t len) {
    if (!val || !ptr) return NULL;
    if (len == 0) return val;
    if (*ptr != '/') return NULL;
    return unsafe_yyjson_get_pointer(val, ptr, len);
}

yyjson_api_inline yyjson_val *yyjson_get_pointer(yyjson_val *val,
                                                 const char *ptr) {
    if (!val || !ptr) return NULL;
    return yyjson_get_pointern(val, ptr, strlen(ptr));
}

yyjson_api_inline yyjson_val *yyjson_doc_get_pointern(yyjson_doc *doc,
                                                      const char *ptr,
                                                      size_t len) {
    return yyjson_get_pointern(doc ? doc->root : NULL, ptr, len);
}

yyjson_api_inline yyjson_val *yyjson_doc_get_pointer(yyjson_doc *doc,
                                                     const char *ptr) {
    return yyjson_get_pointer(doc ? doc->root : NULL, ptr);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_get_pointern(yyjson_mut_val *val,
                                                          const char *ptr,
                                                          size_t len) {
    if (!val || !ptr) return NULL;
    if (len == 0) return val;
    if (*ptr != '/') return NULL;
    return unsafe_yyjson_mut_get_pointer(val, ptr, len);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_get_pointer(yyjson_mut_val *val,
                                                         const char *ptr) {
    if (!val || !ptr) return NULL;
    return yyjson_mut_get_pointern(val, ptr, strlen(ptr));
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_doc_get_pointern(
    yyjson_mut_doc *doc, const char *ptr, size_t len) {
    return yyjson_mut_get_pointern(doc ? doc->root : NULL, ptr, len);
}

yyjson_api_inline yyjson_mut_val *yyjson_mut_doc_get_pointer(
    yyjson_mut_doc *doc, const char *ptr) {
    return yyjson_mut_get_pointer(doc ? doc->root : NULL, ptr);
}



/*==============================================================================
 * Compiler Hint End
 *============================================================================*/

#if defined(__clang__)
#   pragma clang diagnostic pop
#elif defined(__GNUC__)
#   if (__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#   pragma GCC diagnostic pop
#   endif
#elif defined(_MSC_VER)
#   pragma warning(pop)
#endif /* warning suppress end */

#ifdef __cplusplus
}
#endif /* extern "C" end */

#endif /* YYJSON_H */
