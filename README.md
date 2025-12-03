# la.h

la.h is a header-only, macro-driven linear-algebra helper that generates
small fixed-size vector types and per-element operations for dims 2, 3, 4 and
for several scalar types (float, double, long double, int, long int, unsigned
int, unsigned long int). To get full function implementations, define
LA_IMPLEMENTATION in exactly one C file before including la.h.

## Provided types
vec2f_t, vec3f_t, vec4f_t (float)
vec2d_t, vec3d_t, vec4d_t (double)
vec2ld_t, vec3ld_t, vec4ld_t (long double)
vec2i_t, vec3i_t, vec4i_t (int)
vec2li_t, vec3li_t, vec4li_t (long int)
vec2u_t, vec3u_t, vec4u_t (unsigned int)
vec2lu_t, vec3lu_t, vec4lu_t (unsigned long int) 

## Available operations (per type/dimension)
fill: vecN*_fill(value) — fill all components
add / sub / mul / div: per-element arithmetic
max / min: per-element max/min
pow: per-element exponentiation (see notes)
lerp: linear interpolation (per-element)
clamp: per-element clamp (see notes)
dot: dot product -> scalar
len_squared, len: squared length and length
normalize: normalize with epsilon and fallback
reflect: reflect vector a around normal n
debug: print the vector with format-specific fmt
## Exampe

```c
vec4f_t v = {1.0, 2.0, 3.0, 4.0};
vec4f_t b = vec4f_add(a, vec4f_fill(1.0f));
vec4i_debug(stdout, "b = ", b);
```

Look into main.c for more examples
