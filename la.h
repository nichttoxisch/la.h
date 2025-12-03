#ifndef LA_H_
#define LA_H_

// la.h is a header-only, macro-driven linear-algebra helper that generates
// small fixed-size vector types and per-element operations for dims 2, 3, 4 and
// for several scalar types (float, double, long double, int, long int, unsigned
// int, unsigned long int). To get full function implementations, define
// LA_IMPLEMENTATION in exactly one C file before including la.h.
//
// Provided types:
// vec2f_t, vec3f_t, vec4f_t (float)
// vec2d_t, vec3d_t, vec4d_t (double)
// vec2ld_t, vec3ld_t, vec4ld_t (long double)
// vec2i_t, vec3i_t, vec4i_t (int)
// vec2li_t, vec3li_t, vec4li_t (long int)
// vec2u_t, vec3u_t, vec4u_t (unsigned int)
// vec2lu_t, vec3lu_t, vec4lu_t (unsigned long int)
// 
// Available operations (per type/dimension)
// fill: vecN*_fill(value) — fill all components
// add / sub / mul / div: per-element arithmetic
// max / min: per-element max/min
// pow: per-element exponentiation (see notes)
// lerp: linear interpolation (per-element)
// clamp: per-element clamp (see notes)
// dot: dot product -> scalar
// len_squared, len: squared length and length
// normalize: normalize with epsilon and fallback
// reflect: reflect vector a around normal n
// debug: print the vector with format-specific fmt

// EXAMPLE:
//
// int main() {
//   vec4f_t v = {1.0, 2.0, 3.0, 4.0};
//   vec4f_t b = vec4f_add(a, vec4f_fill(1.0f));
//   vec4i_debug(stdout, "b = ", b);
//   return 0;
// }
//

#include <stdio.h>

#define VEC_S(T, dim, suf)   \
  struct s_##vec##dim##suf { \
    T data[dim];             \
  }

#define VEC_T(T, dim, suf) vec##dim##suf##_t
#define VEC_TYPEDEF(T, dim, suf) typedef VEC_S(T, dim, suf) VEC_T(T, dim, suf)

#define VEC_FILL_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)               \
  vec##dim##suf##_fill(T a)
#define VEC_FILL_IMPL(T, dim, suf)  \
  VEC_FILL_DECL(T, dim, suf) {      \
    VEC_T(T, dim, suf) c;           \
    for (int i = 0; i < dim; i++) { \
      c.data[i] = a;                \
    }                               \
    return c;                       \
  }

#define VEC_ADD_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)              \
  vec##dim##suf##_add(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b)
#define VEC_ADD_IMPL(T, dim, suf)        \
  VEC_ADD_DECL(T, dim, suf) {            \
    VEC_T(T, dim, suf) c;                \
    for (int i = 0; i < dim; i++) {      \
      c.data[i] = a.data[i] + b.data[i]; \
    }                                    \
    return c;                            \
  }

#define VEC_SUB_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)              \
  vec##dim##suf##_sub(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b)
#define VEC_SUB_IMPL(T, dim, suf)        \
  VEC_SUB_DECL(T, dim, suf) {            \
    VEC_T(T, dim, suf) c;                \
    for (int i = 0; i < dim; i++) {      \
      c.data[i] = a.data[i] - b.data[i]; \
    }                                    \
    return c;                            \
  }

#define VEC_MUL_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)              \
  vec##dim##suf##_mul(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b)
#define VEC_MUL_IMPL(T, dim, suf)        \
  VEC_MUL_DECL(T, dim, suf) {            \
    VEC_T(T, dim, suf) c;                \
    for (int i = 0; i < dim; i++) {      \
      c.data[i] = a.data[i] * b.data[i]; \
    }                                    \
    return c;                            \
  }

#define VEC_DIV_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)              \
  vec##dim##suf##_div(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b)
#define VEC_DIV_IMPL(T, dim, suf)        \
  VEC_DIV_DECL(T, dim, suf) {            \
    VEC_T(T, dim, suf) c;                \
    for (int i = 0; i < dim; i++) {      \
      c.data[i] = a.data[i] / b.data[i]; \
    }                                    \
    return c;                            \
  }

#define MIN(a, b)           \
  ({                        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a < _b ? _a : _b;      \
  })

#define VEC_MIN_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)              \
  vec##dim##suf##_min(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b)
#define VEC_MIN_IMPL(T, dim, suf)            \
  VEC_MIN_DECL(T, dim, suf) {                \
    VEC_T(T, dim, suf) c;                    \
    for (int i = 0; i < dim; i++) {          \
      c.data[i] = MIN(a.data[i], b.data[i]); \
    }                                        \
    return c;                                \
  }

#define MAX(a, b)           \
  ({                        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b;      \
  })

#define VEC_MAX_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)              \
  vec##dim##suf##_max(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b)
#define VEC_MAX_IMPL(T, dim, suf)            \
  VEC_MAX_DECL(T, dim, suf) {                \
    VEC_T(T, dim, suf) c;                    \
    for (int i = 0; i < dim; i++) {          \
      c.data[i] = MAX(a.data[i], b.data[i]); \
    }                                        \
    return c;                                \
  }

#define VEC_POW_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)              \
  vec##dim##suf##_pow(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) exp)
#define VEC_POW_IMPL(T, dim, suf)               \
  VEC_POW_DECL(T, dim, suf) {                   \
    for (int i = 0; i < dim; i++) {             \
      a.data[i] = powf(a.data[i], exp.data[i]); \
    }                                           \
    return a;                                   \
  }

#define VEC_LERP_DECL(T, dim, suf)                                 \
  VEC_T(T, dim, suf)                                               \
  vec##dim##suf##_lerp(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b, \
                       VEC_T(T, dim, suf) t)
#define VEC_LERP_IMPL(T, dim, suf)                                 \
  VEC_LERP_DECL(T, dim, suf) {                                     \
    for (int i = 0; i < dim; i++) {                                \
      a.data[i] = a.data[i] + t.data[i] * (b.data[i] - a.data[i]); \
    }                                                              \
    return a;                                                      \
  }

#define VEC_CLAMP_DECL(T, dim, suf)                                 \
  VEC_T(T, dim, suf)                                                \
  vec##dim##suf##_clamp(VEC_T(T, dim, suf) x, VEC_T(T, dim, suf) a, \
                        VEC_T(T, dim, suf) b)
#define VEC_CLAMP_IMPL(T, dim, suf)          \
  VEC_CLAMP_DECL(T, dim, suf) {              \
    for (int i = 0; i < dim; i++) {          \
      x.data[i] = MAX(x.data[i], a.data[i]); \
      x.data[i] = MIN(x.data[i], b.data[i]); \
    }                                        \
    return x;                                \
  }

#define VEC_DOT_DECL(T, dim, suf) \
  T vec##dim##suf##_dot(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) b)
#define VEC_DOT_IMPL(T, dim, suf)   \
  VEC_DOT_DECL(T, dim, suf) {       \
    T s = {0};                      \
    for (int i = 0; i < dim; i++) { \
      s += a.data[i] * b.data[i];   \
    }                               \
    return s;                       \
  }

#define VEC_LEN_SQUARED_DECL(T, dim, suf) \
  T vec##dim##suf##_len_squared(VEC_T(T, dim, suf) a)
#define VEC_LEN_SQUARED_IMPL(T, dim, suf) \
  VEC_LEN_SQUARED_DECL(T, dim, suf) { return vec##dim##suf##_dot(a, a); }

#define VEC_LEN_DECL(T, dim, suf) T vec##dim##suf##_len(VEC_T(T, dim, suf) a)
#define VEC_LEN_IMPL(T, dim, suf) \
  VEC_LEN_DECL(T, dim, suf) { return sqrt(vec##dim##suf##_len_squared(a)); }

#define VEC_NORMALIZE_DECL(T, dim, suf)                  \
  VEC_T(T, dim, suf)                                     \
  vec##dim##suf##_normalize(VEC_T(T, dim, suf) a, T eps, \
                            VEC_T(T, dim, suf) fallback)
#define VEC_NORMALIZE_IMPL(T, dim, suf)                     \
  VEC_NORMALIZE_DECL(T, dim, suf) {                         \
    T l = vec##dim##suf##_len(a);                           \
    if (fabs(l) <= eps) return fallback;                    \
    return vec##dim##suf##_div(a, vec##dim##suf##_fill(l)); \
  }

#define VEC_REFLECT_DECL(T, dim, suf) \
  VEC_T(T, dim, suf)                  \
  vec##dim##suf##_reflect(VEC_T(T, dim, suf) a, VEC_T(T, dim, suf) n)
#define VEC_REFLECT_IMPL(T, dim, suf)                                         \
  VEC_REFLECT_DECL(T, dim, suf) {                                             \
    VEC_T(T, dim, suf) r = n;                                                 \
    r = vec##dim##suf##_mul(r,                                                \
                            vec##dim##suf##_fill(vec##dim##suf##_dot(n, a))); \
    r = vec##dim##suf##_mul(r, vec##dim##suf##_fill(2));                      \
    r = vec##dim##suf##_sub(a, r);                                            \
    return r;                                                                 \
  }

#define VEC_DEBUG_DECL(T, dim, suf) \
  void vec##dim##suf##_debug(FILE* f, const char* prefix, VEC_T(T, dim, suf) a)
#define VEC_DEBUG_IMPL(T, dim, suf, fmt)  \
  VEC_DEBUG_DECL(T, dim, suf) {           \
    fprintf(f, "%s", prefix);             \
    fprintf(f, "%s(", "vec" #dim #suf);   \
    for (int i = 0; i < dim; i++) {       \
      fprintf(f, fmt, a.data[i]);         \
      if (i != dim - 1) fprintf(f, ", "); \
    }                                     \
    fprintf(f, ")\n");                    \
  }

#define VEC_DECL(T, dim, suf)        \
  VEC_TYPEDEF(T, dim, suf);          \
  VEC_FILL_DECL(T, dim, suf);        \
  VEC_ADD_DECL(T, dim, suf);         \
  VEC_SUB_DECL(T, dim, suf);         \
  VEC_MUL_DECL(T, dim, suf);         \
  VEC_DIV_DECL(T, dim, suf);         \
  VEC_MAX_DECL(T, dim, suf);         \
  VEC_MIN_DECL(T, dim, suf);         \
  VEC_POW_DECL(T, dim, suf);         \
  VEC_LERP_DECL(T, dim, suf);        \
  VEC_CLAMP_DECL(T, dim, suf);       \
  VEC_DOT_DECL(T, dim, suf);         \
  VEC_LEN_SQUARED_DECL(T, dim, suf); \
  VEC_LEN_DECL(T, dim, suf);         \
  VEC_NORMALIZE_DECL(T, dim, suf);   \
  VEC_REFLECT_DECL(T, dim, suf);     \
  VEC_DEBUG_DECL(T, dim, suf);

#define VEC_IMPL(T, dim, suf, fmt)  \
  VEC_FILL_IMPL(T, dim, suf)        \
  VEC_ADD_IMPL(T, dim, suf)         \
  VEC_SUB_IMPL(T, dim, suf)         \
  VEC_MUL_IMPL(T, dim, suf)         \
  VEC_DIV_IMPL(T, dim, suf)         \
  VEC_MAX_IMPL(T, dim, suf)         \
  VEC_MIN_IMPL(T, dim, suf)         \
  VEC_POW_IMPL(T, dim, suf)         \
  VEC_LERP_IMPL(T, dim, suf)        \
  VEC_CLAMP_IMPL(T, dim, suf)       \
  VEC_DOT_IMPL(T, dim, suf)         \
  VEC_LEN_SQUARED_IMPL(T, dim, suf) \
  VEC_LEN_IMPL(T, dim, suf)         \
  VEC_NORMALIZE_IMPL(T, dim, suf)   \
  VEC_REFLECT_IMPL(T, dim, suf)     \
  VEC_DEBUG_IMPL(T, dim, suf, fmt)

#define VEC234_DECL(T, suf) \
  VEC_DECL(T, 2, suf)       \
  VEC_DECL(T, 3, suf)       \
  VEC_DECL(T, 4, suf)

#define VEC234_IMPL(T, suf, fmt) \
  VEC_IMPL(T, 2, suf, fmt)       \
  VEC_IMPL(T, 3, suf, fmt)       \
  VEC_IMPL(T, 4, suf, fmt)

VEC234_DECL(float, f)
VEC234_DECL(double, d)
VEC234_DECL(long double, ld)
VEC234_DECL(int, i)
VEC234_DECL(long int, li)
VEC234_DECL(unsigned int, u)
VEC234_DECL(unsigned long int, lu)

#endif  // LA_H_

#ifdef LA_IMPLEMENTATION

#include <tgmath.h>

VEC234_IMPL(float, f, "%.2f")
VEC234_IMPL(double, d, "%.2f")
VEC234_IMPL(long double, ld, "%.2Lf")
VEC234_IMPL(int, i, "%i")
VEC234_IMPL(long int, li, "%li")
VEC234_IMPL(unsigned int, u, "%u")
VEC234_IMPL(unsigned long int, lu, "%lu")

#endif  // LA_IMPLEMENTATION
