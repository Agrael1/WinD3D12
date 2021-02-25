module;

#if !defined(_XM_AVX2_INTRINSICS_) && defined(__AVX2__) && !defined(_XM_NO_INTRINSICS_)
#define _XM_AVX2_INTRINSICS_
#endif

#if !defined(_XM_FMA3_INTRINSICS_) && defined(_XM_AVX2_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
#define _XM_FMA3_INTRINSICS_
#endif

#if !defined(_XM_F16C_INTRINSICS_) && defined(_XM_AVX2_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
#define _XM_F16C_INTRINSICS_
#endif

#if !defined(_XM_F16C_INTRINSICS_) && defined(__F16C__) && !defined(_XM_NO_INTRINSICS_)
#define _XM_F16C_INTRINSICS_
#endif

#if defined(_XM_FMA3_INTRINSICS_) && !defined(_XM_AVX_INTRINSICS_)
#define _XM_AVX_INTRINSICS_
#endif

#if defined(_XM_F16C_INTRINSICS_) && !defined(_XM_AVX_INTRINSICS_)
#define _XM_AVX_INTRINSICS_
#endif

#if !defined(_XM_AVX_INTRINSICS_) && defined(__AVX__) && !defined(_XM_NO_INTRINSICS_)
#define _XM_AVX_INTRINSICS_
#endif

#if defined(_XM_AVX_INTRINSICS_) && !defined(_XM_SSE4_INTRINSICS_)
#define _XM_SSE4_INTRINSICS_
#endif

#if defined(_XM_SSE4_INTRINSICS_) && !defined(_XM_SSE3_INTRINSICS_)
#define _XM_SSE3_INTRINSICS_
#endif

#if defined(_XM_SSE3_INTRINSICS_) && !defined(_XM_SSE_INTRINSICS_)
#define _XM_SSE_INTRINSICS_
#endif

#if !defined(_XM_ARM_NEON_INTRINSICS_) && !defined(_XM_SSE_INTRINSICS_) && !defined(_XM_NO_INTRINSICS_)
#if (defined(_M_IX86) || defined(_M_X64) || __i386__ || __x86_64__) && !defined(_M_HYBRID_X86_ARM64) && !defined(_M_ARM64EC)
#define _XM_SSE_INTRINSICS_
#elif defined(_M_ARM) || defined(_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC) || __arm__ || __aarch64__
#define _XM_ARM_NEON_INTRINSICS_
#elif !defined(_XM_NO_INTRINSICS_)
#error DirectX Math does not support this target
#endif
#endif // !_XM_ARM_NEON_INTRINSICS_ && !_XM_SSE_INTRINSICS_ && !_XM_NO_INTRINSICS_

#if defined(_XM_SSE_INTRINSICS_) && defined(_MSC_VER) && (_MSC_VER >= 1920) && !defined(__clang__) && !defined(_XM_SVML_INTRINSICS_) && !defined(_XM_DISABLE_INTEL_SVML_)
#define _XM_SVML_INTRINSICS_
#endif

#if !defined(_XM_NO_XMVECTOR_OVERLOADS_) && (defined(__clang__) || defined(__GNUC__))
#define _XM_NO_XMVECTOR_OVERLOADS_
#endif

#pragma warning(push)
#pragma warning(disable:4514 4820)
// C4514/4820: Off by default noise
#include <math.h>
#include <float.h>
#pragma warning(pop)

#ifndef _XM_NO_INTRINSICS_

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4987)
// C4987: Off by default noise
#include <intrin.h>
#pragma warning(pop)
#endif

#if (defined(__clang__) || defined(__GNUC__)) && (__x86_64__ || __i386__)
#include <cpuid.h>
#endif

#ifdef _XM_SSE_INTRINSICS_
#include <xmmintrin.h>
#include <emmintrin.h>

#ifdef _XM_SSE3_INTRINSICS_
#include <pmmintrin.h>
#endif

#ifdef _XM_SSE4_INTRINSICS_
#include <smmintrin.h>
#endif

#ifdef _XM_AVX_INTRINSICS_
#include <immintrin.h>
#endif

#elif defined(_XM_ARM_NEON_INTRINSICS_)
#if defined(_MSC_VER) && !defined(__clang__) && (defined(_M_ARM64) || defined(_M_HYBRID_X86_ARM64) || defined(_M_ARM64EC))
#include <arm64_neon.h>
#else
#include <arm_neon.h>
#endif
#endif
#endif // !_XM_NO_INTRINSICS_

#include "sal.h"
#include <assert.h>

#pragma warning(push)
#pragma warning(disable : 4005 4668)
// C4005/4668: Old header issue
#include <stdint.h>
#pragma warning(pop)

export module DirectXMath;

export{
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
}