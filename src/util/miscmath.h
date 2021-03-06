/*
 * This software is licensed under the terms of the MIT-License
 * See COPYING for further information.
 * ---
 * Copyright (c) 2011-2019, Lukas Weber <laochailan@web.de>.
 * Copyright (c) 2012-2019, Andrei Alexeyev <akari@alienslab.net>.
 */

#ifndef IGUARD_util_miscmath_h
#define IGUARD_util_miscmath_h

#include "taisei.h"

#define DEG2RAD (M_PI/180.0)
#define RAD2DEG (180.0/M_PI)
#define GOLDEN_RATIO 1.618033988749895

double lerp(double v0, double v1, double f) attr_const;
complex clerp(complex v0, complex v1, double f) attr_const;
intmax_t imin(intmax_t, intmax_t) attr_const;
intmax_t imax(intmax_t, intmax_t) attr_const;
uintmax_t umin(uintmax_t, uintmax_t) attr_const;
uintmax_t umax(uintmax_t, uintmax_t) attr_const;
intmax_t iclamp(intmax_t, intmax_t, intmax_t) attr_const;
double min(double, double) attr_const;
double max(double, double) attr_const;
double clamp(double, double, double) attr_const;
double smoothstep(double edge0, double edge1, double x) attr_const;
double smoothmin(double a, double b, double k);
double approach(double v, double t, double d) attr_const;
float fapproach(float v, float t, float d) attr_const;
void approach_p(double *v, double t, double d);
void fapproach_p(float *v, float t, float d);
double approach_asymptotic(double val, double target, double rate, double epsilon) attr_const;
float fapproach_asymptotic(float val, float target, float rate, float epsilon) attr_const;
complex capproach_asymptotic(complex val, complex target, double rate, double epsilon) attr_const;
void approach_asymptotic_p(double *val, double target, double rate, double epsilon);
void fapproach_asymptotic_p(float *val, float target, float rate, float epsilon);
void capproach_asymptotic_p(complex *val, complex target, double rate, double epsilon);
double psin(double) attr_const;
int sign(double) attr_const;
double swing(double x, double s) attr_const;
uint32_t topow2_u32(uint32_t x) attr_const;
uint64_t topow2_u64(uint64_t x) attr_const;
float ftopow2(float x) attr_const;
float smooth(float x) attr_const;
float smoothreclamp(float x, float old_min, float old_max, float new_min, float new_max) attr_const;
float sanitize_scale(float scale) attr_const;
uint64_t upow10(uint n) attr_const;
uint digitcnt(uint64_t x) attr_const;
float normpdf(float x, float sigma) attr_const;
void gaussian_kernel_1d(size_t size, float sigma, float kernel[size]) attr_nonnull(3);

// Compute (a*b)/c with 128-bit intermediate precision.
// If the final result would not fit into 64 bits, the return value is undefined.
uint64_t umuldiv64(uint64_t x, uint64_t multiplier, uint64_t divisor);

#define topow2(x) (_Generic((x), \
	uint32_t: topow2_u32, \
	uint64_t: topow2_u64, \
	default: topow2_u64 \
)(x))

#include <cglm/types.h>

typedef float         vec2_noalign[2];
typedef int          ivec2_noalign[2];
typedef float         vec3_noalign[3];
typedef int          ivec3_noalign[3];
typedef float         vec4_noalign[4];
typedef int          ivec4_noalign[4];
typedef vec3_noalign  mat3_noalign[3];
typedef vec4_noalign  mat4_noalign[4];

#endif // IGUARD_util_miscmath_h
