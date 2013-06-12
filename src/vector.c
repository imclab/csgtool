#include "vector.h"
#if defined __SSEE_4_1__
#include <smmintrin.h>
#endif

float3 *clone_f3(float3 f) {
	float3 *clone = malloc(sizeof(float3));
	if(clone) {
		(*clone)[0] = f[0];
		(*clone)[1] = f[1];
		(*clone)[2] = f[2];
	}
	return clone;
}

float3 *f3_normalize(float3 *v) {
	float mag = sqrt((*v)[0] * (*v)[0] +
					 (*v)[1] * (*v)[1] +
					 (*v)[2] * (*v)[2]);
	(*v)[0] /= mag;
	(*v)[1] /= mag;
	(*v)[2] /= mag;
	return v;
}

float3 *f3_scale(float3 *v, float c) {
	(*v)[0] *= c;
	(*v)[1] *= c;
	(*v)[2] *= c;
	return v;
}

#if defined __SSE__4_1
float f3_dot(float3 v1, float3 v2) {
	float result;
	float arr[4] = { v1[0], v1[1], v1[2], 0.0 };
	float arr2[4] = { v2[0], v2[1], v2[2], 0.0 };

    __m128 a = _mm_load_ps(arr);
    __m128 b = _mm_load_ps(arr2);
	const int mask = 0xff;
	__m128 sse_result = _mm_dp_ps(a, b, mask);

	_mm_store_ss(&result, sse_result);
	return result;
}
#else
float f3_dot(float3 v1, float3 v2) {
  return (v1[0] * v2[0] +
		  v1[1] * v2[1] +
		  v1[2] * v2[2]);
}
#endif

float3 *f3_cross(float3 *result, float3 v1, float3 v2) {
		(*result)[0] = v1[1]*v2[2] - v1[2]*v2[1];
		(*result)[1] = v1[2]*v2[0] - v1[0]*v2[2];
		(*result)[2] = v1[0]*v2[1] - v1[1]*v2[0];
		return result;
}

float3 *f3_sub(float3 *result, float3 v1, float3 v2) {
	(*result)[0] = v1[0] - v2[0];
	(*result)[1] = v1[1] - v2[1];
	(*result)[2] = v1[2] - v2[2];
	return result;
}

float3 *f3_interpolate(float3 *result, float3 start, float3 v, float alpha) {
	for(int i = 0; i < 3; i++) {
		(*result)[i] += (v[i] - start[i]) * alpha;
	}
	return result;
}
