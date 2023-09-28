#ifndef ERROR__
#define ERROR__
#include <stdlib.h>
#include <stdio.h>

#define SIGOBJECT 1
#define SIGUNUSED 2
#define SIGOBJPAREN 3
#define SIGBOUND 4
#define SIGEMPTY 5
#define SIGTYPE 6

#define WARNING_MAGENTA(...)\
  "\033[1;35m" __VA_ARGS__"," "\033[1;0m"
#define WARN(...) WARNING_MAGENTA(__VA_ARGS__)

#define LOGMSG(SIG, ARG, ...)			\
  ____fixederr___(SIG, __LINE__, __func__, __FILE__,\
   magcol__(name__, #ARG, #__VA_ARGS__))

#define ASSERT_OBJ_TYPE(OBJ)	       				\
  ____fixederr___						\
  (_Generic((OBJ), cp__: 0, default: SIGOBJECT),		\
   __LINE__, __func__, __FILE__, "ARRAY("WARN(#OBJ)", (...))");

/* if 1 expand expression else if 0, log error */
#define ASSERT_ARG_1(SIG, ARG, ...) CHOOSE_1(__VA_ARGS__)
#define ASSERT_ARG_0(SIG, ARG, ...)\
  LOGMSG(SIG, ARG, __VA_ARGS__)

/* ARG_VARGS helps in expansion and error checking. expands to expression, ARG,	\
   when true, else expands to the post arguments for logging error */
#define ARG_VARGS_1(ARG, ...) ARG
#define ARG_VARGS_0(ARG, ...) __VA_ARGS__

/*__attribute__((always_inline)) static inline				\
const string_t magcol__(const string_t const name, string_t const restrict arg, string_t varargs);
*/
typedef char * string_t;
const char *errmsg__[6] = {\
  "function must be called with an object pointer to type 'list' as its first argument",\
  "empty parenthesis is not suppported in array type",
  "array forbids parenthesis as or around its first argument",
  "array members must be bounded by parenthesis",
  "passing an empty argument to array",
  "argument is of  unknown type"
};
#define ERR_RED(...) "\033[1;31m" __VA_ARGS__ "\033[1;0m"

static string_t magcol__(string_t const name, string_t const arg, string_t varargs){

  static char buffer[1024];
  sprintf(buffer, "%s(%s%s%s%s)", name,				\
	    "\033[1;35m", arg, "\033[1;0m" ",", varargs);
  return buffer;
  }
/*__attribute__((always_inline)) extern inline			     */
void ____fixederr___(int const sig, size_t const line__, const char * restrict const func__, string_t const restrict file__, string_t const restrict prototype__){
  if ((sig - 1) < 0)
    return;

  fprintf(stderr, "%s: %s `%s`:\n%s:%zd: %s %s\n  %zu | %s\n",	\
	  file__, "In function", func__,		\
	  file__, line__, ERR_RED("error:"), errmsg__[sig - 1],	\
	  line__, prototype__			\
	  );
  abort();
}
			  /* copy.c: In function ‘main’:
copy.c:125:21: error: static assertion failed: "hi"
125 | #define LOGMSG(...) static_assert(0, "hi") */
#endif /* ERROR__ */
