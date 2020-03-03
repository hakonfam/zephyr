; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-- -mattr=+sse4.1 | FileCheck %s --check-prefixes=ALL,SSE
; RUN: llc < %s -mtriple=x86_64-- -mattr=+avx    | FileCheck %s --check-prefixes=ALL,AVX,AVX1
; RUN: llc < %s -mtriple=x86_64-- -mattr=+avx2   | FileCheck %s --check-prefixes=ALL,AVX,AVX2

define <16 x i8> @undef_index(i8 %x) nounwind {
; ALL-LABEL: undef_index:
; ALL:       # %bb.0:
; ALL-NEXT:    retq
  %ins = insertelement <16 x i8> undef, i8 %x, i64 undef
  ret <16 x i8> %ins
}

define <16 x i8> @undef_scalar(<16 x i8> %x, i32 %index) nounwind {
; ALL-LABEL: undef_scalar:
; ALL:       # %bb.0:
; ALL-NEXT:    retq
  %ins = insertelement <16 x i8> %x, i8 undef, i32 %index
  ret <16 x i8> %ins
}

define <16 x i8> @arg_i8_v16i8(i8 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i8_v16i8:
; SSE:       # %bb.0:
; SSE-NEXT:    movd %edi, %xmm0
; SSE-NEXT:    pxor %xmm1, %xmm1
; SSE-NEXT:    pshufb %xmm1, %xmm0
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i8_v16i8:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovd %edi, %xmm0
; AVX1-NEXT:    vpxor %xmm1, %xmm1, %xmm1
; AVX1-NEXT:    vpshufb %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i8_v16i8:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovd %edi, %xmm0
; AVX2-NEXT:    vpbroadcastb %xmm0, %xmm0
; AVX2-NEXT:    retq
  %ins = insertelement <16 x i8> undef, i8 %x, i32 %y
  ret <16 x i8> %ins
}

define <8 x i16> @arg_i16_v8i16(i16 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i16_v8i16:
; SSE:       # %bb.0:
; SSE-NEXT:    movd %edi, %xmm0
; SSE-NEXT:    pshuflw {{.*#+}} xmm0 = xmm0[0,0,2,3,4,5,6,7]
; SSE-NEXT:    pshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i16_v8i16:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovd %edi, %xmm0
; AVX1-NEXT:    vpshuflw {{.*#+}} xmm0 = xmm0[0,0,2,3,4,5,6,7]
; AVX1-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i16_v8i16:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovd %edi, %xmm0
; AVX2-NEXT:    vpbroadcastw %xmm0, %xmm0
; AVX2-NEXT:    retq
  %ins = insertelement <8 x i16> undef, i16 %x, i32 %y
  ret <8 x i16> %ins
}

define <4 x i32> @arg_i32_v4i32(i32 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i32_v4i32:
; SSE:       # %bb.0:
; SSE-NEXT:    movd %edi, %xmm0
; SSE-NEXT:    pshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i32_v4i32:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovd %edi, %xmm0
; AVX1-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i32_v4i32:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovd %edi, %xmm0
; AVX2-NEXT:    vpbroadcastd %xmm0, %xmm0
; AVX2-NEXT:    retq
  %ins = insertelement <4 x i32> undef, i32 %x, i32 %y
  ret <4 x i32> %ins
}

define <2 x i64> @arg_i64_v2i64(i64 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i64_v2i64:
; SSE:       # %bb.0:
; SSE-NEXT:    movq %rdi, %xmm0
; SSE-NEXT:    pshufd {{.*#+}} xmm0 = xmm0[0,1,0,1]
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i64_v2i64:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovq %rdi, %xmm0
; AVX1-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,1,0,1]
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i64_v2i64:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovq %rdi, %xmm0
; AVX2-NEXT:    vpbroadcastq %xmm0, %xmm0
; AVX2-NEXT:    retq
  %ins = insertelement <2 x i64> undef, i64 %x, i32 %y
  ret <2 x i64> %ins
}

define <4 x float> @arg_f32_v4f32(float %x, i32 %y) nounwind {
; SSE-LABEL: arg_f32_v4f32:
; SSE:       # %bb.0:
; SSE-NEXT:    shufps {{.*#+}} xmm0 = xmm0[0,0,0,0]
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_f32_v4f32:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpermilps {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_f32_v4f32:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vbroadcastss %xmm0, %xmm0
; AVX2-NEXT:    retq
  %ins = insertelement <4 x float> undef, float %x, i32 %y
  ret <4 x float> %ins
}

define <2 x double> @arg_f64_v2f64(double %x, i32 %y) nounwind {
; SSE-LABEL: arg_f64_v2f64:
; SSE:       # %bb.0:
; SSE-NEXT:    movddup {{.*#+}} xmm0 = xmm0[0,0]
; SSE-NEXT:    retq
;
; AVX-LABEL: arg_f64_v2f64:
; AVX:       # %bb.0:
; AVX-NEXT:    vmovddup {{.*#+}} xmm0 = xmm0[0,0]
; AVX-NEXT:    retq
  %ins = insertelement <2 x double> undef, double %x, i32 %y
  ret <2 x double> %ins
}

define <16 x i8> @load_i8_v16i8(i8* %p, i32 %y) nounwind {
; SSE-LABEL: load_i8_v16i8:
; SSE:       # %bb.0:
; SSE-NEXT:    movzbl (%rdi), %eax
; SSE-NEXT:    movd %eax, %xmm0
; SSE-NEXT:    pxor %xmm1, %xmm1
; SSE-NEXT:    pshufb %xmm1, %xmm0
; SSE-NEXT:    retq
;
; AVX1-LABEL: load_i8_v16i8:
; AVX1:       # %bb.0:
; AVX1-NEXT:    movzbl (%rdi), %eax
; AVX1-NEXT:    vmovd %eax, %xmm0
; AVX1-NEXT:    vpxor %xmm1, %xmm1, %xmm1
; AVX1-NEXT:    vpshufb %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: load_i8_v16i8:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vpbroadcastb (%rdi), %xmm0
; AVX2-NEXT:    retq
  %x = load i8, i8* %p
  %ins = insertelement <16 x i8> undef, i8 %x, i32 %y
  ret <16 x i8> %ins
}

define <8 x i16> @load_i16_v8i16(i16* %p, i32 %y) nounwind {
; SSE-LABEL: load_i16_v8i16:
; SSE:       # %bb.0:
; SSE-NEXT:    movzwl (%rdi), %eax
; SSE-NEXT:    movd %eax, %xmm0
; SSE-NEXT:    pshuflw {{.*#+}} xmm0 = xmm0[0,0,2,3,4,5,6,7]
; SSE-NEXT:    pshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; SSE-NEXT:    retq
;
; AVX1-LABEL: load_i16_v8i16:
; AVX1:       # %bb.0:
; AVX1-NEXT:    movzwl (%rdi), %eax
; AVX1-NEXT:    vmovd %eax, %xmm0
; AVX1-NEXT:    vpshuflw {{.*#+}} xmm0 = xmm0[0,0,2,3,4,5,6,7]
; AVX1-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    retq
;
; AVX2-LABEL: load_i16_v8i16:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vpbroadcastw (%rdi), %xmm0
; AVX2-NEXT:    retq
  %x = load i16, i16* %p
  %ins = insertelement <8 x i16> undef, i16 %x, i32 %y
  ret <8 x i16> %ins
}

define <4 x i32> @load_i32_v4i32(i32* %p, i32 %y) nounwind {
; SSE-LABEL: load_i32_v4i32:
; SSE:       # %bb.0:
; SSE-NEXT:    movd {{.*#+}} xmm0 = mem[0],zero,zero,zero
; SSE-NEXT:    pshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; SSE-NEXT:    retq
;
; AVX-LABEL: load_i32_v4i32:
; AVX:       # %bb.0:
; AVX-NEXT:    vbroadcastss (%rdi), %xmm0
; AVX-NEXT:    retq
  %x = load i32, i32* %p
  %ins = insertelement <4 x i32> undef, i32 %x, i32 %y
  ret <4 x i32> %ins
}

define <2 x i64> @load_i64_v2i64(i64* %p, i32 %y) nounwind {
; SSE-LABEL: load_i64_v2i64:
; SSE:       # %bb.0:
; SSE-NEXT:    movq {{.*#+}} xmm0 = mem[0],zero
; SSE-NEXT:    pshufd {{.*#+}} xmm0 = xmm0[0,1,0,1]
; SSE-NEXT:    retq
;
; AVX-LABEL: load_i64_v2i64:
; AVX:       # %bb.0:
; AVX-NEXT:    vmovddup {{.*#+}} xmm0 = mem[0,0]
; AVX-NEXT:    retq
  %x = load i64, i64* %p
  %ins = insertelement <2 x i64> undef, i64 %x, i32 %y
  ret <2 x i64> %ins
}

define <4 x float> @load_f32_v4f32(float* %p, i32 %y) nounwind {
; SSE-LABEL: load_f32_v4f32:
; SSE:       # %bb.0:
; SSE-NEXT:    movss {{.*#+}} xmm0 = mem[0],zero,zero,zero
; SSE-NEXT:    shufps {{.*#+}} xmm0 = xmm0[0,0,0,0]
; SSE-NEXT:    retq
;
; AVX-LABEL: load_f32_v4f32:
; AVX:       # %bb.0:
; AVX-NEXT:    vbroadcastss (%rdi), %xmm0
; AVX-NEXT:    retq
  %x = load float, float* %p
  %ins = insertelement <4 x float> undef, float %x, i32 %y
  ret <4 x float> %ins
}

define <2 x double> @load_f64_v2f64(double* %p, i32 %y) nounwind {
; SSE-LABEL: load_f64_v2f64:
; SSE:       # %bb.0:
; SSE-NEXT:    movddup {{.*#+}} xmm0 = mem[0,0]
; SSE-NEXT:    retq
;
; AVX-LABEL: load_f64_v2f64:
; AVX:       # %bb.0:
; AVX-NEXT:    vmovddup {{.*#+}} xmm0 = mem[0,0]
; AVX-NEXT:    retq
  %x = load double, double* %p
  %ins = insertelement <2 x double> undef, double %x, i32 %y
  ret <2 x double> %ins
}

define <32 x i8> @arg_i8_v32i8(i8 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i8_v32i8:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    andl $31, %esi
; SSE-NEXT:    movb %dil, (%rsp,%rsi)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i8_v32i8:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovd %edi, %xmm0
; AVX1-NEXT:    vpxor %xmm1, %xmm1, %xmm1
; AVX1-NEXT:    vpshufb %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i8_v32i8:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovd %edi, %xmm0
; AVX2-NEXT:    vpbroadcastb %xmm0, %ymm0
; AVX2-NEXT:    retq
  %ins = insertelement <32 x i8> undef, i8 %x, i32 %y
  ret <32 x i8> %ins
}

define <16 x i16> @arg_i16_v16i16(i16 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i16_v16i16:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    andl $15, %esi
; SSE-NEXT:    movw %di, (%rsp,%rsi,2)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i16_v16i16:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovd %edi, %xmm0
; AVX1-NEXT:    vpshuflw {{.*#+}} xmm0 = xmm0[0,0,2,3,4,5,6,7]
; AVX1-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i16_v16i16:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovd %edi, %xmm0
; AVX2-NEXT:    vpbroadcastw %xmm0, %ymm0
; AVX2-NEXT:    retq
  %ins = insertelement <16 x i16> undef, i16 %x, i32 %y
  ret <16 x i16> %ins
}

define <8 x i32> @arg_i32_v8i32(i32 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i32_v8i32:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    andl $7, %esi
; SSE-NEXT:    movl %edi, (%rsp,%rsi,4)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i32_v8i32:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovd %edi, %xmm0
; AVX1-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i32_v8i32:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovd %edi, %xmm0
; AVX2-NEXT:    vpbroadcastd %xmm0, %ymm0
; AVX2-NEXT:    retq
  %ins = insertelement <8 x i32> undef, i32 %x, i32 %y
  ret <8 x i32> %ins
}

define <4 x i64> @arg_i64_v4i64(i64 %x, i32 %y) nounwind {
; SSE-LABEL: arg_i64_v4i64:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    andl $3, %esi
; SSE-NEXT:    movq %rdi, (%rsp,%rsi,8)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_i64_v4i64:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovq %rdi, %xmm0
; AVX1-NEXT:    vmovddup {{.*#+}} xmm0 = xmm0[0,0]
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_i64_v4i64:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vmovq %rdi, %xmm0
; AVX2-NEXT:    vpbroadcastq %xmm0, %ymm0
; AVX2-NEXT:    retq
  %ins = insertelement <4 x i64> undef, i64 %x, i32 %y
  ret <4 x i64> %ins
}

define <8 x float> @arg_f32_v8f32(float %x, i32 %y) nounwind {
; SSE-LABEL: arg_f32_v8f32:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $edi killed $edi def $rdi
; SSE-NEXT:    andl $7, %edi
; SSE-NEXT:    movss %xmm0, (%rsp,%rdi,4)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_f32_v8f32:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vpermilps {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_f32_v8f32:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vbroadcastss %xmm0, %ymm0
; AVX2-NEXT:    retq
  %ins = insertelement <8 x float> undef, float %x, i32 %y
  ret <8 x float> %ins
}

define <4 x double> @arg_f64_v4f64(double %x, i32 %y) nounwind {
; SSE-LABEL: arg_f64_v4f64:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $edi killed $edi def $rdi
; SSE-NEXT:    andl $3, %edi
; SSE-NEXT:    movsd %xmm0, (%rsp,%rdi,8)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: arg_f64_v4f64:
; AVX1:       # %bb.0:
; AVX1-NEXT:    vmovddup {{.*#+}} xmm0 = xmm0[0,0]
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: arg_f64_v4f64:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vbroadcastsd %xmm0, %ymm0
; AVX2-NEXT:    retq
  %ins = insertelement <4 x double> undef, double %x, i32 %y
  ret <4 x double> %ins
}

define <32 x i8> @load_i8_v32i8(i8* %p, i32 %y) nounwind {
; SSE-LABEL: load_i8_v32i8:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    movb (%rdi), %al
; SSE-NEXT:    andl $31, %esi
; SSE-NEXT:    movb %al, (%rsp,%rsi)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: load_i8_v32i8:
; AVX1:       # %bb.0:
; AVX1-NEXT:    movzbl (%rdi), %eax
; AVX1-NEXT:    vmovd %eax, %xmm0
; AVX1-NEXT:    vpxor %xmm1, %xmm1, %xmm1
; AVX1-NEXT:    vpshufb %xmm1, %xmm0, %xmm0
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: load_i8_v32i8:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vpbroadcastb (%rdi), %ymm0
; AVX2-NEXT:    retq
  %x = load i8, i8* %p
  %ins = insertelement <32 x i8> undef, i8 %x, i32 %y
  ret <32 x i8> %ins
}

define <16 x i16> @load_i16_v16i16(i16* %p, i32 %y) nounwind {
; SSE-LABEL: load_i16_v16i16:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    movzwl (%rdi), %eax
; SSE-NEXT:    andl $15, %esi
; SSE-NEXT:    movw %ax, (%rsp,%rsi,2)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX1-LABEL: load_i16_v16i16:
; AVX1:       # %bb.0:
; AVX1-NEXT:    movzwl (%rdi), %eax
; AVX1-NEXT:    vmovd %eax, %xmm0
; AVX1-NEXT:    vpshuflw {{.*#+}} xmm0 = xmm0[0,0,2,3,4,5,6,7]
; AVX1-NEXT:    vpshufd {{.*#+}} xmm0 = xmm0[0,0,0,0]
; AVX1-NEXT:    vinsertf128 $1, %xmm0, %ymm0, %ymm0
; AVX1-NEXT:    retq
;
; AVX2-LABEL: load_i16_v16i16:
; AVX2:       # %bb.0:
; AVX2-NEXT:    vpbroadcastw (%rdi), %ymm0
; AVX2-NEXT:    retq
  %x = load i16, i16* %p
  %ins = insertelement <16 x i16> undef, i16 %x, i32 %y
  ret <16 x i16> %ins
}

define <8 x i32> @load_i32_v8i32(i32* %p, i32 %y) nounwind {
; SSE-LABEL: load_i32_v8i32:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    movl (%rdi), %eax
; SSE-NEXT:    andl $7, %esi
; SSE-NEXT:    movl %eax, (%rsp,%rsi,4)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX-LABEL: load_i32_v8i32:
; AVX:       # %bb.0:
; AVX-NEXT:    vbroadcastss (%rdi), %ymm0
; AVX-NEXT:    retq
  %x = load i32, i32* %p
  %ins = insertelement <8 x i32> undef, i32 %x, i32 %y
  ret <8 x i32> %ins
}

define <4 x i64> @load_i64_v4i64(i64* %p, i32 %y) nounwind {
; SSE-LABEL: load_i64_v4i64:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    movq (%rdi), %rax
; SSE-NEXT:    andl $3, %esi
; SSE-NEXT:    movq %rax, (%rsp,%rsi,8)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX-LABEL: load_i64_v4i64:
; AVX:       # %bb.0:
; AVX-NEXT:    vbroadcastsd (%rdi), %ymm0
; AVX-NEXT:    retq
  %x = load i64, i64* %p
  %ins = insertelement <4 x i64> undef, i64 %x, i32 %y
  ret <4 x i64> %ins
}

define <8 x float> @load_f32_v8f32(float* %p, i32 %y) nounwind {
; SSE-LABEL: load_f32_v8f32:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    movss {{.*#+}} xmm0 = mem[0],zero,zero,zero
; SSE-NEXT:    andl $7, %esi
; SSE-NEXT:    movss %xmm0, (%rsp,%rsi,4)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX-LABEL: load_f32_v8f32:
; AVX:       # %bb.0:
; AVX-NEXT:    vbroadcastss (%rdi), %ymm0
; AVX-NEXT:    retq
  %x = load float, float* %p
  %ins = insertelement <8 x float> undef, float %x, i32 %y
  ret <8 x float> %ins
}

define <4 x double> @load_f64_v4f64(double* %p, i32 %y) nounwind {
; SSE-LABEL: load_f64_v4f64:
; SSE:       # %bb.0:
; SSE-NEXT:    pushq %rbp
; SSE-NEXT:    movq %rsp, %rbp
; SSE-NEXT:    andq $-32, %rsp
; SSE-NEXT:    subq $64, %rsp
; SSE-NEXT:    # kill: def $esi killed $esi def $rsi
; SSE-NEXT:    movsd {{.*#+}} xmm0 = mem[0],zero
; SSE-NEXT:    andl $3, %esi
; SSE-NEXT:    movsd %xmm0, (%rsp,%rsi,8)
; SSE-NEXT:    movaps (%rsp), %xmm0
; SSE-NEXT:    movaps {{[0-9]+}}(%rsp), %xmm1
; SSE-NEXT:    movq %rbp, %rsp
; SSE-NEXT:    popq %rbp
; SSE-NEXT:    retq
;
; AVX-LABEL: load_f64_v4f64:
; AVX:       # %bb.0:
; AVX-NEXT:    vbroadcastsd (%rdi), %ymm0
; AVX-NEXT:    retq
  %x = load double, double* %p
  %ins = insertelement <4 x double> undef, double %x, i32 %y
  ret <4 x double> %ins
}

; Don't die trying to insert to an invalid index.

define i32 @PR44139(<16 x i64>* %p) {
; ALL-LABEL: PR44139:
; ALL:       # %bb.0:
; ALL-NEXT:    movl (%rdi), %eax
; ALL-NEXT:    leal 2147483647(%rax), %ecx
; ALL-NEXT:    testl %eax, %eax
; ALL-NEXT:    cmovnsl %eax, %ecx
; ALL-NEXT:    andl $-2147483648, %ecx # imm = 0x80000000
; ALL-NEXT:    addl %eax, %ecx
; ALL-NEXT:    # kill: def $eax killed $eax killed $rax
; ALL-NEXT:    xorl %edx, %edx
; ALL-NEXT:    divl %ecx
; ALL-NEXT:    retq
  %L = load <16 x i64>, <16 x i64>* %p
  %E1 = extractelement <16 x i64> %L, i64 0
  %tempvector = insertelement <16 x i64> undef, i64 %E1, i32 0
  %vector = shufflevector <16 x i64> %tempvector, <16 x i64> undef, <16 x i32> zeroinitializer
  %C3 = icmp sgt i64 9223372036854775807, -9223372036854775808
  %t0 = trunc <16 x i64> %vector to <16 x i32>
  %I4 = insertelement <16 x i64> %vector, i64 %E1, i1 %C3
  store <16 x i64> %I4, <16 x i64>* %p
  %elt = extractelement <16 x i32> %t0, i32 0
  %B = srem i32 %elt, -2147483648
  %B9 = udiv i32 %elt, %B
  ret i32 %B9
}
