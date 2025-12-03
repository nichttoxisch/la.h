#include <stdio.h>

#define LA_IMPLEMENTATION
#include "la.h"

int main(void) {
  vec3f_t a = {.data = {1.0f, -2.0f, 3.0f}};
  vec3f_t b = vec3f_fill(2.0f);
  vec3f_t add = vec3f_add(a, b);
  vec3f_t sub = vec3f_sub(a, b);
  vec3f_t mul = vec3f_mul(a, b);
  vec3f_t divv = vec3f_div(a, b);
  vec3f_t vmin = vec3f_min(a, b);
  vec3f_t vmax = vec3f_max(a, b);
  vec3f_t expv = {.data = {2.0f, 3.0f, 1.0f}};
  vec3f_t powv = vec3f_pow(a, expv);
  vec3f_t t = vec3f_fill(0.5f);
  vec3f_t lerp = vec3f_lerp(a, b, t);
  vec3f_t x = {.data = {-5.0f, 0.5f, 10.0f}};
  vec3f_t clamp_lo = vec3f_fill(-1.0f);
  vec3f_t clamp_hi = vec3f_fill(4.0f);
  vec3f_t clamped = vec3f_clamp(x, clamp_lo, clamp_hi);
  float dot_ab = vec3f_dot(a, b);
  float len2 = vec3f_len_squared(a);
  float len = vec3f_len(a);
  vec3f_t fallback = vec3f_fill(0.0f);
  vec3f_t normalized = vec3f_normalize(a, 1e-6f, fallback);
  vec3f_t n = vec3f_fill(0.0f);
  n.data[1] = 1.0f;
  n = vec3f_normalize(n, 1e-6f, vec3f_fill(0.0f));
  vec3f_t reflected = vec3f_reflect(a, n);

  puts("=== vec3f_t tests ===");
  vec3f_debug(stdout, "a = ", a);
  vec3f_debug(stdout, "b = ", b);
  vec3f_debug(stdout, "add = ", add);
  vec3f_debug(stdout, "sub = ", sub);
  vec3f_debug(stdout, "mul = ", mul);
  vec3f_debug(stdout, "div = ", divv);
  vec3f_debug(stdout, "min = ", vmin);
  vec3f_debug(stdout, "max = ", vmax);
  vec3f_debug(stdout, "pow = ", powv);
  vec3f_debug(stdout, "lerp = ", lerp);
  vec3f_debug(stdout, "x = ", x);
  vec3f_debug(stdout, "clamped = ", clamped);
  printf("dot(a,b) = %.4f\n", dot_ab);
  printf("len_squared(a) = %.4f\n", len2);
  printf("len(a) = %.4f\n", len);
  vec3f_debug(stdout, "normalized = ", normalized);
  vec3f_debug(stdout, "reflected = ", reflected);

  vec4d_t da = {.data = {1.0, 2.0, 3.0, 4.0}};
  vec4d_t db = vec4d_fill(0.5);
  vec4d_t dadd = vec4d_add(da, db);
  vec4d_t dpow = vec4d_pow(da, (vec4d_t){.data = {2.0, 2.0, 0.5, 1.0}});
  double ddot = vec4d_dot(da, db);
  double dlen = vec4d_len(da);

  puts("\n=== vec4d_t tests ===");
  vec4d_debug(stdout, "da = ", da);
  vec4d_debug(stdout, "db = ", db);
  vec4d_debug(stdout, "dadd = ", dadd);
  vec4d_debug(stdout, "dpow = ", dpow);
  printf("ddot = %.6f, dlen = %.6f\n", ddot, dlen);

  vec2ld_t lda = {.data = {1.5L, -0.5L}};
  vec2ld_t ldb = vec2ld_fill(2.0L);
  vec2ld_t lmul = vec2ld_mul(lda, ldb);
  puts("\n=== vec2ld_t tests ===");
  vec2ld_debug(stdout, "lda = ", lda);
  vec2ld_debug(stdout, "ldb = ", ldb);
  vec2ld_debug(stdout, "lmul = ", lmul);

  vec3i_t ia = {.data = {2, -3, 4}};
  vec3i_t ib = vec3i_fill(2);
  vec3i_t iadd = vec3i_add(ia, ib);
  vec3i_t ipow = vec3i_pow(ia, (vec3i_t){.data = {3, 2, 1}});
  vec3i_t iclamp =
      vec3i_clamp((vec3i_t){.data = {10, -10, 0}},
                  (vec3i_t){.data = {0, -5, -1}}, (vec3i_t){.data = {5, 5, 5}});

  puts("\n=== vec3i_t tests ===");
  vec3i_debug(stdout, "ia = ", ia);
  vec3i_debug(stdout, "ib = ", ib);
  vec3i_debug(stdout, "iadd = ", iadd);
  vec3i_debug(stdout, "ipow = ", ipow);
  vec3i_debug(stdout, "iclamp = ", iclamp);

  vec4u_t ua = {.data = {8u, 4u, 2u, 1u}};
  vec4u_t ub = vec4u_fill(2u);
  vec4u_t udiv = vec4u_div(ua, ub);
  vec4u_t umin = vec4u_min(ua, ub);
  vec4u_t umax = vec4u_max(ua, ub);

  puts("\n=== vec4u_t tests ===");
  vec4u_debug(stdout, "ua = ", ua);
  vec4u_debug(stdout, "ub = ", ub);
  vec4u_debug(stdout, "udiv = ", udiv);
  vec4u_debug(stdout, "umin = ", umin);
  vec4u_debug(stdout, "umax = ", umax);

  puts("\nAll tests executed.");

  return 0;
}