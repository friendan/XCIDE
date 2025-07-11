//@模块名称  lua模块
//@版本  1.0.0
//@日期  2022-02-17
//@作者  白喵
//@QQ   154460336
//@模块备注 封装自开源项目lua脚本引擎
// homepage: http://www.lua.org/
//@依赖  module_base.h

#ifdef  _WIN64
//@lib "lib/x64/lua.lib"
#else
//@lib "lib/x86/lua.lib"
#endif

#ifndef lua_h
#define lua_h

#include <stdarg.h>
#include <stdio.h>


#include "luaconf.h"
//@隐藏{
extern "C" {
//@隐藏}
//@分组{ 基本接口
#define LUA_VERSION_MAJOR	"5"
#define LUA_VERSION_MINOR	"4"
#define LUA_VERSION_RELEASE	"4"

#define LUA_VERSION_NUM			504
#define LUA_VERSION_RELEASE_NUM		(LUA_VERSION_NUM * 100 + 4)

#define LUA_VERSION	"Lua " LUA_VERSION_MAJOR "." LUA_VERSION_MINOR
#define LUA_RELEASE	LUA_VERSION "." LUA_VERSION_RELEASE
#define LUA_COPYRIGHT	LUA_RELEASE "  Copyright (C) 1994-2022 Lua.org, PUC-Rio"
#define LUA_AUTHORS	"R. Ierusalimschy, L. H. de Figueiredo, W. Celes"


    /* mark for precompiled code ('<esc>Lua') */
#define LUA_SIGNATURE	"\x1bLua"

/* option for multiple returns in 'lua_pcall' and 'lua_call' */
#define LUA_MULTRET	(-1)


/*
** Pseudo-indices
** (-LUAI_MAXSTACK is the minimum valid index; we keep some free empty
** space after that to help overflow detection)
*/
#define LUA_REGISTRYINDEX	(-LUAI_MAXSTACK - 1000)
#define lua_upvalueindex(i)	(LUA_REGISTRYINDEX - (i))


/* thread status */
#define LUA_OK		0
#define LUA_YIELD	1
#define LUA_ERRRUN	2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM	4
#define LUA_ERRERR	5


    typedef struct lua_State lua_State;


    /*
    ** basic types
    */
#define LUA_TNONE		(-1)

#define LUA_TNIL		0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		3
#define LUA_TSTRING		4
#define LUA_TTABLE		5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		8

#define LUA_NUMTYPES		9



    /* minimum Lua stack available to a C function */
#define LUA_MINSTACK	20


/* predefined values in the registry */
#define LUA_RIDX_MAINTHREAD	1
#define LUA_RIDX_GLOBALS	2
#define LUA_RIDX_LAST		LUA_RIDX_GLOBALS


/* type of numbers in Lua */
    typedef LUA_NUMBER lua_Number;


    /* type for integer functions */
    typedef LUA_INTEGER lua_Integer;

    /* unsigned integer type */
    typedef LUA_UNSIGNED lua_Unsigned;

    /* type for continuation-function contexts */
    typedef LUA_KCONTEXT lua_KContext;


    /*
    ** Type for C functions registered with Lua
    */
    typedef int (*lua_CFunction) (lua_State* L);

    /*
    ** Type for continuation functions
    */
    typedef int (*lua_KFunction) (lua_State* L, int status, lua_KContext ctx);


    /*
    ** Type for functions that read/write blocks when loading/dumping Lua chunks
    */
    typedef const char* (*lua_Reader) (lua_State* L, void* ud, size_t* sz);

    typedef int (*lua_Writer) (lua_State* L, const void* p, size_t sz, void* ud);


    /*
    ** Type for memory-allocation functions
    */
    typedef void* (*lua_Alloc) (void* ud, void* ptr, size_t osize, size_t nsize);


    /*
    ** Type for warning functions
    */
    typedef void (*lua_WarnFunction) (void* ud, const char* msg, int tocont);




    /*
    ** generic extra include file
    */
#if defined(LUA_USER_H)
#include LUA_USER_H
#endif


    /*
    ** RCS ident string
    */
    //@隐藏{
        extern const char lua_ident[];
    //@隐藏}
    


    /*
    ** state manipulation
    */
    lua_State*   lua_newstate(lua_Alloc f, void* ud);
    void         lua_close(lua_State* L);
    lua_State*   lua_newthread(lua_State* L);
    int          lua_resetthread(lua_State* L);

    lua_CFunction  lua_atpanic(lua_State* L, lua_CFunction panicf);


    lua_Number  lua_version(lua_State* L);


    /*
    ** basic stack manipulation
    */
    int     lua_absindex(lua_State* L, int idx);
    int     lua_gettop(lua_State* L);
    void    lua_settop(lua_State* L, int idx);
    void    lua_pushvalue(lua_State* L, int idx);
    void    lua_rotate(lua_State* L, int idx, int n);
    void    lua_copy(lua_State* L, int fromidx, int toidx);
    int     lua_checkstack(lua_State* L, int n);

    void    lua_xmove(lua_State* from, lua_State* to, int n);


    /*
    ** access functions (stack -> C)
    */

    int               lua_isnumber(lua_State* L, int idx);
    int               lua_isstring(lua_State* L, int idx);
    int               lua_iscfunction(lua_State* L, int idx);
    int               lua_isinteger(lua_State* L, int idx);
    int               lua_isuserdata(lua_State* L, int idx);
    int               lua_type(lua_State* L, int idx);
    const char*   lua_typename(lua_State* L, int tp);

    lua_Number  lua_tonumberx(lua_State* L, int idx, int* isnum);
    lua_Integer  lua_tointegerx(lua_State* L, int idx, int* isnum);
    int               lua_toboolean(lua_State* L, int idx);
    const char*   lua_tolstring(lua_State* L, int idx, size_t* len);
    lua_Unsigned  lua_rawlen(lua_State* L, int idx);
    lua_CFunction  lua_tocfunction(lua_State* L, int idx);
    void*   lua_touserdata(lua_State* L, int idx);
    lua_State*   lua_tothread(lua_State* L, int idx);
    const void*   lua_topointer(lua_State* L, int idx);


    /*
    ** Comparison and arithmetic functions
    */

#define LUA_OPADD	0	/* ORDER TM, ORDER OP */
#define LUA_OPSUB	1
#define LUA_OPMUL	2
#define LUA_OPMOD	3
#define LUA_OPPOW	4
#define LUA_OPDIV	5
#define LUA_OPIDIV	6
#define LUA_OPBAND	7
#define LUA_OPBOR	8
#define LUA_OPBXOR	9
#define LUA_OPSHL	10
#define LUA_OPSHR	11
#define LUA_OPUNM	12
#define LUA_OPBNOT	13

    void    lua_arith(lua_State* L, int op);

#define LUA_OPEQ	0
#define LUA_OPLT	1
#define LUA_OPLE	2

    int     lua_rawequal(lua_State* L, int idx1, int idx2);
    int     lua_compare(lua_State* L, int idx1, int idx2, int op);


    /*
    ** push functions (C -> stack)
    */
    void          lua_pushnil(lua_State* L);
    void          lua_pushnumber(lua_State* L, lua_Number n);
    void          lua_pushinteger(lua_State* L, lua_Integer n);
    const char*   lua_pushlstring(lua_State* L, const char* s, size_t len);
    const char*   lua_pushstring(lua_State* L, const char* s);
    const char*   lua_pushvfstring(lua_State* L, const char* fmt,
        va_list argp);
    const char*   lua_pushfstring(lua_State* L, const char* fmt, ...);
    void    lua_pushcclosure(lua_State* L, lua_CFunction fn, int n);
    void    lua_pushboolean(lua_State* L, int b);
    void    lua_pushlightuserdata(lua_State* L, void* p);
    int     lua_pushthread(lua_State* L);


    /*
    ** get functions (Lua -> stack)
    */
    int   lua_getglobal(lua_State* L, const char* name);
    int   lua_gettable(lua_State* L, int idx);
    int   lua_getfield(lua_State* L, int idx, const char* k);
    int   lua_geti(lua_State* L, int idx, lua_Integer n);
    int   lua_rawget(lua_State* L, int idx);
    int   lua_rawgeti(lua_State* L, int idx, lua_Integer n);
    int   lua_rawgetp(lua_State* L, int idx, const void* p);

    void    lua_createtable(lua_State* L, int narr, int nrec);
    void*   lua_newuserdatauv(lua_State* L, size_t sz, int nuvalue);
    int     lua_getmetatable(lua_State* L, int objindex);
    int    lua_getiuservalue(lua_State* L, int idx, int n);


    /*
    ** set functions (stack -> Lua)
    */
    void    lua_setglobal(lua_State* L, const char* name);
    void    lua_settable(lua_State* L, int idx);
    void    lua_setfield(lua_State* L, int idx, const char* k);
    void    lua_seti(lua_State* L, int idx, lua_Integer n);
    void    lua_rawset(lua_State* L, int idx);
    void    lua_rawseti(lua_State* L, int idx, lua_Integer n);
    void    lua_rawsetp(lua_State* L, int idx, const void* p);
    int     lua_setmetatable(lua_State* L, int objindex);
    int     lua_setiuservalue(lua_State* L, int idx, int n);


    /*
    ** 'load' and 'call' functions (load and run Lua code)
    */
    void    lua_callk(lua_State* L, int nargs, int nresults,
        lua_KContext ctx, lua_KFunction k);
#define lua_call(L,n,r)		lua_callk(L, (n), (r), 0, NULL)

    int     lua_pcallk(lua_State* L, int nargs, int nresults, int errfunc,
        lua_KContext ctx, lua_KFunction k);
#define lua_pcall(L,n,r,f)	lua_pcallk(L, (n), (r), (f), 0, NULL)

    int     lua_load(lua_State* L, lua_Reader reader, void* dt,
        const char* chunkname, const char* mode);

    int   lua_dump(lua_State* L, lua_Writer writer, void* data, int strip);


    /*
    ** coroutine functions
    */
    int    lua_yieldk(lua_State* L, int nresults, lua_KContext ctx,
        lua_KFunction k);
    int    lua_resume(lua_State* L, lua_State* from, int narg,
        int* nres);
    int    lua_status(lua_State* L);
    int   lua_isyieldable(lua_State* L);

#define lua_yield(L,n)		lua_yieldk(L, (n), 0, NULL)


    /*
    ** Warning-related functions
    */
    void   lua_setwarnf(lua_State* L, lua_WarnFunction f, void* ud);
    void   lua_warning(lua_State* L, const char* msg, int tocont);


    /*
    ** garbage-collection function and options
    */

#define LUA_GCSTOP		0
#define LUA_GCRESTART		1
#define LUA_GCCOLLECT		2
#define LUA_GCCOUNT		3
#define LUA_GCCOUNTB		4
#define LUA_GCSTEP		5
#define LUA_GCSETPAUSE		6
#define LUA_GCSETSTEPMUL	7
#define LUA_GCISRUNNING		9
#define LUA_GCGEN		10
#define LUA_GCINC		11

    int   lua_gc(lua_State* L, int what, ...);


    /*
    ** miscellaneous functions
    */

    int     lua_error(lua_State* L);

    int     lua_next(lua_State* L, int idx);

    void    lua_concat(lua_State* L, int n);
    void    lua_len(lua_State* L, int idx);

    size_t  lua_stringtonumber(lua_State* L, const char* s);

    lua_Alloc  lua_getallocf(lua_State* L, void** ud);
    void        lua_setallocf(lua_State* L, lua_Alloc f, void* ud);

    void   lua_toclose(lua_State* L, int idx);
    void   lua_closeslot(lua_State* L, int idx);


    /*
    ** {==============================================================
    ** some useful macros
    ** ===============================================================
    */

#define lua_getextraspace  L)	((void *(  char *(L) - LUA_EXTRASPACE))

#define lua_tonumber(L,i)	lua_tonumberx(L,(i),NULL)
#define lua_tointeger(L,i)	lua_tointegerx(L,(i),NULL)

#define lua_pop(L,n)		lua_settop(L, -(n)-1)

#define lua_newtable(L)		lua_createtable(L, 0, 0)

#define lua_register  L,n,f(lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))

#define lua_pushcfunction(L,f)	lua_pushcclosure(L, (f), 0)

#define lua_isfunction(L,n)	(lua_type(L, (n)) == LUA_TFUNCTION)
#define lua_istable(L,n)	(lua_type(L, (n)) == LUA_TTABLE)
#define lua_islightuserdata(L,n)	(lua_type(L, (n)) == LUA_TLIGHTUSERDATA)
#define lua_isnil(L,n)		(lua_type(L, (n)) == LUA_TNIL)
#define lua_isboolean(L,n)	(lua_type(L, (n)) == LUA_TBOOLEAN)
#define lua_isthread(L,n)	(lua_type(L, (n)) == LUA_TTHREAD)
#define lua_isnone(L,n)		(lua_type(L, (n)) == LUA_TNONE)
#define lua_isnoneornil(L, n)	(lua_type(L, (n)) <= 0)

#define lua_pushliteral(L, s)	lua_pushstring(L, "" s)

#define lua_pushglobaltable(L)  ((void)lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS))

#define lua_tostring(L,i)	lua_tolstring(L, (i), NULL)


#define lua_insert(L,idx)	lua_rotate(L, (idx), 1)

#define lua_remove(L,idx)	(lua_rotate(L, (idx), -1), lua_pop(L, 1))

#define lua_replace(L,idx)	(lua_copy(L, -1, (idx)), lua_pop(L, 1))

    /* }============================================================== */


    /*
    ** {==============================================================
    ** compatibility macros
    ** ===============================================================
    */
#if defined(LUA_COMPAT_APIINTCASTS)

#define lua_pushunsigned  L,n)	lua_pushinteger(L, (lua_Integer(n))
#define lua_tounsignedx(L,i,is)	((lua_Unsigned)lua_tointegerx(L,i,is))
#define lua_tounsigned(L,i)	lua_tounsignedx(L,(i),NULL)

#endif

#define lua_newuserdata(L,s)	lua_newuserdatauv(L,s,1)
#define lua_getuservalue(L,idx)	lua_getiuservalue(L,idx,1)
#define lua_setuservalue(L,idx)	lua_setiuservalue(L,idx,1)

#define LUA_NUMTAGS		LUA_NUMTYPES

    /* }============================================================== */

    /*
    ** {======================================================================
    ** Debug API
    ** =======================================================================
    */


    /*
    ** Event codes
    */
#define LUA_HOOKCALL	0
#define LUA_HOOKRET	1
#define LUA_HOOKLINE	2
#define LUA_HOOKCOUNT	3
#define LUA_HOOKTAILCALL 4


    /*
    ** Event masks
    */
#define LUA_MASKCALL	(1 << LUA_HOOKCALL)
#define LUA_MASKRET	(1 << LUA_HOOKRET)
#define LUA_MASKLINE	(1 << LUA_HOOKLINE)
#define LUA_MASKCOUNT	(1 << LUA_HOOKCOUNT)
	//@隐藏{
    typedef struct lua_Debug lua_Debug;  /* activation record */
	//@隐藏}

    /* Functions to be called by the debugger in specific events */
    typedef void   (*lua_Hook) (lua_State* L, lua_Debug* ar);


    int   lua_getstack(lua_State* L, int level, lua_Debug* ar);
    int   lua_getinfo(lua_State* L, const char* what, lua_Debug* ar);
    const char*   lua_getlocal(lua_State* L, const lua_Debug* ar, int n);
    const char*   lua_setlocal(lua_State* L, const lua_Debug* ar, int n);
    const char*   lua_getupvalue(lua_State* L, int funcindex, int n);
    const char*   lua_setupvalue(lua_State* L, int funcindex, int n);

    void*   lua_upvalueid(lua_State* L, int fidx, int n);
    void    lua_upvaluejoin(lua_State* L, int fidx1, int n1,
        int fidx2, int n2);

    void   lua_sethook(lua_State* L, lua_Hook func, int mask, int count);
    lua_Hook  lua_gethook(lua_State* L);
    int   lua_gethookmask(lua_State* L);
    int   lua_gethookcount(lua_State* L);

    int   lua_setcstacklimit(lua_State* L, unsigned int limit);

    struct lua_Debug {
        int event;
        const char* name;	/* (n) */
        const char* namewhat;	/* (n) 'global', 'local', 'field', 'method' */
        const char* what;	/* (S) 'Lua', 'C', 'main', 'tail' */
        const char* source;	/* (S) */
        size_t srclen;	/* (S) */
        int currentline;	/* (l) */
        int linedefined;	/* (S) */
        int lastlinedefined;	/* (S) */
        unsigned char nups;	/* (u) number of upvalues */
        unsigned char nparams;/* (u) number of parameters */
        char isvararg;        /* (u) */
        char istailcall;	/* (t) */
        unsigned short ftransfer;   /* (r) index of first value transferred */
        unsigned short ntransfer;   /* (r) number of transferred values */
        char short_src[LUA_IDSIZE]; /* (S) */
        /* private part */
        struct CallInfo* i_ci;  /* active function */
    };

    /* }====================================================================== */
//@分组}
//@分组{ 基本库
    /******************************************************************************
    * Copyright (C) 1994-2022 Lua.org, PUC-Rio.
    *
    * Permission is hereby granted, free of charge, to any person obtaining
    * a copy of this software and associated documentation files (the
    * "Software"), to deal in the Software without restriction, including
    * without limitation the rights to use, copy, modify, merge, publish,
    * distribute, sublicense, and/or sell copies of the Software, and to
    * permit persons to whom the Software is furnished to do so, subject to
    * the following conditions:
    *
    * The above copyright notice and this permission notice shall be
    * included in all copies or substantial portions of the Software.
    *
    * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
    ******************************************************************************/
    /* version suffix for environment variable names */
#define LUA_VERSUFFIX          "_" LUA_VERSION_MAJOR "_" LUA_VERSION_MINOR


    int   luaopen_base(lua_State* L);

#define LUA_COLIBNAME	"coroutine"
    int   luaopen_coroutine(lua_State* L);

#define LUA_TABLIBNAME	"table"
    int   luaopen_table(lua_State* L);

#define LUA_IOLIBNAME	"io"
    int   luaopen_io(lua_State* L);

#define LUA_OSLIBNAME	"os"
    int   luaopen_os(lua_State* L);

#define LUA_STRLIBNAME	"string"
    int   luaopen_string(lua_State* L);

#define LUA_UTF8LIBNAME	"utf8"
    int   luaopen_utf8(lua_State* L);

#define LUA_MATHLIBNAME	"math"
    int   luaopen_math(lua_State* L);

#define LUA_DBLIBNAME	"debug"
    int   luaopen_debug(lua_State* L);

#define LUA_LOADLIBNAME	"package"
    int   luaopen_package(lua_State* L);
//@分组}
//@分组{ 辅助接口
    /* open all previous libraries */
    void   luaL_openlibs(lua_State* L);


    /* global table */
#define LUA_GNAME	"_G"


    typedef struct luaL_Buffer luaL_Buffer;


    /* extra error code for 'luaL_loadfilex' */
#define LUA_ERRFILE     (LUA_ERRERR+1)


/* key, in the registry, for table of loaded modules */
#define LUA_LOADED_TABLE	"_LOADED"


/* key, in the registry, for table of preloaded loaders */
#define LUA_PRELOAD_TABLE	"_PRELOAD"


    struct luaL_Reg {
        const char* name;
        lua_CFunction func;
    };


#define LUAL_NUMSIZES	(sizeof(lua_Integer)*16 + sizeof(lua_Number))

    void   luaL_checkversion_(lua_State* L, lua_Number ver, size_t sz);
#define luaL_checkversion(L)  	  luaL_checkversion_(L, LUA_VERSION_NUM, LUAL_NUMSIZES)

    int   luaL_getmetafield(lua_State* L, int obj, const char* e);
    int   luaL_callmeta(lua_State* L, int obj, const char* e);
    const char*   luaL_tolstring(lua_State* L, int idx, size_t* len);
    int   luaL_argerror(lua_State* L, int arg, const char* extramsg);
    int   luaL_typeerror(lua_State* L, int arg, const char* tname);
    const char*   luaL_checklstring(lua_State* L, int arg,
        size_t* l);
    const char*   luaL_optlstring(lua_State* L, int arg,
        const char* def, size_t* l);
    lua_Number  luaL_checknumber(lua_State* L, int arg);
    lua_Number  luaL_optnumber(lua_State* L, int arg, lua_Number def);

    lua_Integer  luaL_checkinteger(lua_State* L, int arg);
    lua_Integer  luaL_optinteger(lua_State* L, int arg,
        lua_Integer def);

    void   luaL_checkstack(lua_State* L, int sz, const char* msg);
    void   luaL_checktype(lua_State* L, int arg, int t);
    void   luaL_checkany(lua_State* L, int arg);

    int     luaL_newmetatable(lua_State* L, const char* tname);
    void    luaL_setmetatable(lua_State* L, const char* tname);
    void*   luaL_testudata(lua_State* L, int ud, const char* tname);
    void*   luaL_checkudata(lua_State* L, int ud, const char* tname);

    void   luaL_where(lua_State* L, int lvl);
    int   luaL_error(lua_State* L, const char* fmt, ...);

    int   luaL_checkoption(lua_State* L, int arg, const char* def,
        const char* const lst[]);

    int   luaL_fileresult(lua_State* L, int stat, const char* fname);
    int   luaL_execresult(lua_State* L, int stat);


    /* predefined references */
#define LUA_NOREF       (-2)
#define LUA_REFNIL      (-1)

    int   luaL_ref(lua_State* L, int t);
    void   luaL_unref(lua_State* L, int t, int ref);

    int   luaL_loadfilex(lua_State* L, const char* filename,
        const char* mode);

#define luaL_loadfile(L,f)	luaL_loadfilex(L,f,NULL)

    int   luaL_loadbufferx(lua_State* L, const char* buff, size_t sz,
        const char* name, const char* mode);
    int   luaL_loadstring(lua_State* L, const char* s);

    lua_State*   luaL_newstate(void);

    lua_Integer  luaL_len(lua_State* L, int idx);

    void   luaL_addgsub(luaL_Buffer* b, const char* s,
        const char* p, const char* r);
    const char*   luaL_gsub(lua_State* L, const char* s,
        const char* p, const char* r);

    void   luaL_setfuncs(lua_State* L, const luaL_Reg* l, int nup);

    int   luaL_getsubtable(lua_State* L, int idx, const char* fname);

    void   luaL_traceback(lua_State* L, lua_State* L1,
        const char* msg, int level);

    void   luaL_requiref(lua_State* L, const char* modname,
        lua_CFunction openf, int glb);

    /*
    ** ===============================================================
    ** some useful macros
    ** ===============================================================
    */


#define luaL_newlibtable(L,l)	  lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)

#define luaL_newlib(L,l)    (luaL_checkversion(L), luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))

#define luaL_argcheck(L, cond,arg,extramsg)		  (void(luai_likely(cond) || luaL_argerror(L, (arg), (extramsg))))

#define luaL_argexpected(L,cond,arg,tname)		  (void(luai_likely(cond) || luaL_typeerror(L, (arg), (tname))))

#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d)	(luaL_optlstring(L, (n), (d), NULL))

#define luaL_typename(L,i)	lua_typename(L, lua_type(L,(i)))

#define luaL_dofile(L, fn) 	(luaL_loadfile(L, fn) || lua_pcall(L, 0, LUA_MULTRET, 0))

#define luaL_dostring(L, s) 	(luaL_loadstring(L, s) || lua_pcall(L, 0, LUA_MULTRET, 0))

#define luaL_getmetatable(L,n)	(lua_getfield(L, LUA_REGISTRYINDEX, (n)))

#define luaL_opt(L,f,n,d)	(lua_isnoneornil(L,(n)) ? (d) : f(L,(n)))

#define luaL_loadbuffer(L,s,sz,n)	luaL_loadbufferx(L,s,sz,n,NULL)


    /*
    ** Perform arithmetic operations on lua_Integer values with wrap-around
    ** semantics, as the Lua core does.
    */
#define luaL_intop(op,v1,v2)  	  (lua_Integer(  lua_Unsigned(v1) op   lua_Unsigned(v2)))


    /* push the value used to represent failure/error */
#define luaL_pushfail(L)	lua_pushnil(L)


/*
** Internal assertions for in-house debugging
*/
//@隐藏{
#if !defined(lua_assert)

#if defined LUAI_ASSERT
#include <assert.h>
#define lua_assert(c)		assert(c)
#else
#define lua_assert(c)		((void)0)
#endif

#endif
//@隐藏}



/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/
//@隐藏{
    struct luaL_Buffer {
        char* b;  /* buffer address */
        size_t size;  /* buffer size */
        size_t n;  /* number of characters in buffer */
        lua_State* L;
        union {
            LUAI_MAXALIGN;  /* ensure maximum alignment for buffer */
            char b[LUAL_BUFFERSIZE];  /* initial buffer */
        } init;
    };
//@隐藏}

#define luaL_bufflen(bf)	((bf)->n)
#define luaL_buffaddr(bf)	((bf)->b)


#define luaL_addchar(B,c)     (void((B)->n < (B)->size || luaL_prepbuffsize((B), 1)),    ((B)->b[(B)->n++] = (c)))

#define luaL_addsize(B,s)	((B)->n += (s))

#define luaL_buffsub(B,s)	((B)->n -= (s))

    void   luaL_buffinit(lua_State* L, luaL_Buffer* B);
    char*   luaL_prepbuffsize(luaL_Buffer* B, size_t sz);
    void   luaL_addlstring(luaL_Buffer* B, const char* s, size_t l);
    void   luaL_addstring(luaL_Buffer* B, const char* s);
    void   luaL_addvalue(luaL_Buffer* B);
    void   luaL_pushresult(luaL_Buffer* B);
    void   luaL_pushresultsize(luaL_Buffer* B, size_t sz);
    char*   luaL_buffinitsize(lua_State* L, luaL_Buffer* B, size_t sz);

#define luaL_prepbuffer(B)	luaL_prepbuffsize(B, LUAL_BUFFERSIZE)

    /* }====================================================== */



    /*
    ** {======================================================
    ** File handles for IO library
    ** =======================================================
    */

    /*
    ** A file handle is a userdata with metatable 'LUA_FILEHANDLE' and
    ** initial structure 'luaL_Stream' (it may contain other fields
    ** after that initial structure).
    */

#define LUA_FILEHANDLE          "FILE*"


    struct luaL_Stream {
        FILE* f;  /* stream (NULL for incompletely created streams) */
        lua_CFunction closef;  /* to close stream (NULL for closed streams) */
    };

    /* }====================================================== */

    /*
    ** {==================================================================
    ** "Abstraction Layer" for basic report of messages and errors
    ** ===================================================================
    */

    /* print a string */
#if !defined(lua_writestring)
#define lua_writestring(s,l)   fwrite((s), sizeof(char), (l), stdout)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline  (lua_writestring("\n", 1), fflush(stdout))
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror(s,p)         (fprintf(stderr, (s), (p)), fflush(stderr))
#endif

/* }================================================================== */


/*
** {============================================================
** Compatibility with deprecated conversions
** =============================================================
*/
#if defined(LUA_COMPAT_APIINTCASTS)

#define luaL_checkunsigned(L,a)	((lua_Unsigned)luaL_checkinteger(L,a))
#define luaL_optunsigned(L,a,d)		  (lua_Unsigned)luaL_optinteger(L,a,(lua_Integer(d)))

#define luaL_checkint(L,n)	((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L,n,d)	((int)luaL_optinteger(L, (n), (d)))

#define luaL_checklong(L,n)	((long)luaL_checkinteger(L, (n)))
#define luaL_optlong(L,n,d)	((long)luaL_optinteger(L, (n), (d)))

#endif
//@分组}
/* }============================================================ */
//@隐藏{
}
//@隐藏}

#endif
