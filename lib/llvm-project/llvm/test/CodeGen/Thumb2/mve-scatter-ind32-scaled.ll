; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=thumbv8.1m.main-arm-none-eabi -mattr=+mve.fp -enable-arm-maskedgatscat %s -o 2>/dev/null - | FileCheck %s

; VLDRH.u32 Qd, [base, offs, #uxtw #1]
define arm_aapcs_vfpcc void @ext_scaled_i16_i32(i16* %base, <4 x i32>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: ext_scaled_i16_i32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrw.u32 q1, [r1]
; CHECK-NEXT:    vstrh.32 q0, [r0, q1, uxtw #1]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i32>, <4 x i32>* %offptr, align 4
  %ptrs = getelementptr inbounds i16, i16* %base, <4 x i32> %offs
  %t = trunc <4 x i32> %input to <4 x i16>
  call void @llvm.masked.scatter.v4i16.v4p0i16(<4 x i16> %t, <4 x i16*> %ptrs, i32 2, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs, uxtw #2]
define arm_aapcs_vfpcc void @scaled_i32_i32(i32* %base, <4 x i32>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: scaled_i32_i32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrw.u32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i32>, <4 x i32>* %offptr, align 4
  %ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs
  call void @llvm.masked.scatter.v4i32.v4p0i32(<4 x i32> %input, <4 x i32*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs, uxtw #2]
define arm_aapcs_vfpcc void @scaled_f32_i32(i32* %base, <4 x i32>* %offptr, <4 x float> %input) {
; CHECK-LABEL: scaled_f32_i32:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrw.u32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i32>, <4 x i32>* %offptr, align 4
  %i32_ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs
  %ptrs = bitcast <4 x i32*> %i32_ptrs to <4 x float*>
  call void @llvm.masked.scatter.v4f32.v4p0f32(<4 x float> %input, <4 x float*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.zext, uxtw #2]
define arm_aapcs_vfpcc void @unsigned_scaled_b_i32_i16(i32* %base, <4 x i16>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: unsigned_scaled_b_i32_i16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrh.u32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i16>, <4 x i16>* %offptr, align 2
  %offs.zext = zext <4 x i16> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.zext
  call void @llvm.masked.scatter.v4i32.v4p0i32(<4 x i32> %input, <4 x i32*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.sext, uxtw #2]
define arm_aapcs_vfpcc void @signed_scaled_i32_i16(i32* %base, <4 x i16>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: signed_scaled_i32_i16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrh.s32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i16>, <4 x i16>* %offptr, align 2
  %offs.sext = sext <4 x i16> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.sext
  call void @llvm.masked.scatter.v4i32.v4p0i32(<4 x i32> %input, <4 x i32*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.zext, uxtw #2]
define arm_aapcs_vfpcc void @a_unsigned_scaled_f32_i16(i32* %base, <4 x i16>* %offptr, <4 x float> %input) {
; CHECK-LABEL: a_unsigned_scaled_f32_i16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrh.u32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i16>, <4 x i16>* %offptr, align 2
  %offs.zext = zext <4 x i16> %offs to <4 x i32>
  %i32_ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.zext
  %ptrs = bitcast <4 x i32*> %i32_ptrs to <4 x float*>
  call void @llvm.masked.scatter.v4f32.v4p0f32(<4 x float> %input, <4 x float*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.sext, uxtw #2]
define arm_aapcs_vfpcc void @b_signed_scaled_f32_i16(i32* %base, <4 x i16>* %offptr, <4 x float> %input) {
; CHECK-LABEL: b_signed_scaled_f32_i16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrh.s32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i16>, <4 x i16>* %offptr, align 2
  %offs.sext = sext <4 x i16> %offs to <4 x i32>
  %i32_ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.sext
  %ptrs = bitcast <4 x i32*> %i32_ptrs to <4 x float*>
  call void @llvm.masked.scatter.v4f32.v4p0f32(<4 x float> %input, <4 x float*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VLDRH.u32 Qd, [base, offs.sext, uxtw #1]
define arm_aapcs_vfpcc void @ext_signed_scaled_i16_i16(i16* %base, <4 x i16>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: ext_signed_scaled_i16_i16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrh.s32 q1, [r1]
; CHECK-NEXT:    vstrh.32 q0, [r0, q1, uxtw #1]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i16>, <4 x i16>* %offptr, align 2
  %offs.sext = sext <4 x i16> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i16, i16* %base, <4 x i32> %offs.sext
  %t = trunc <4 x i32> %input to <4 x i16>
  call void @llvm.masked.scatter.v4i16.v4p0i16(<4 x i16> %t, <4 x i16*> %ptrs, i32 2, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRH.32 Qd, [base, offs.sext, uxtw #1]
define arm_aapcs_vfpcc void @ext_unsigned_scaled_i16_i16(i16* %base, <4 x i16>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: ext_unsigned_scaled_i16_i16:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrh.u32 q1, [r1]
; CHECK-NEXT:    vstrh.32 q0, [r0, q1, uxtw #1]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i16>, <4 x i16>* %offptr, align 2
  %offs.zext = zext <4 x i16> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i16, i16* %base, <4 x i32> %offs.zext
  %t = trunc <4 x i32> %input to <4 x i16>
  call void @llvm.masked.scatter.v4i16.v4p0i16(<4 x i16> %t, <4 x i16*> %ptrs, i32 2, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.zext, uxtw #2]
define arm_aapcs_vfpcc void @unsigned_scaled_b_i32_i8(i32* %base, <4 x i8>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: unsigned_scaled_b_i32_i8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrb.u32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i8>, <4 x i8>* %offptr, align 1
  %offs.zext = zext <4 x i8> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.zext
  call void @llvm.masked.scatter.v4i32.v4p0i32(<4 x i32> %input, <4 x i32*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.sext, uxtw #2]
define arm_aapcs_vfpcc void @signed_scaled_i32_i8(i32* %base, <4 x i8>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: signed_scaled_i32_i8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrb.s32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i8>, <4 x i8>* %offptr, align 1
  %offs.sext = sext <4 x i8> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.sext
  call void @llvm.masked.scatter.v4i32.v4p0i32(<4 x i32> %input, <4 x i32*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.zext, uxtw #2]
define arm_aapcs_vfpcc void @a_unsigned_scaled_f32_i8(i32* %base, <4 x i8>* %offptr, <4 x float> %input) {
; CHECK-LABEL: a_unsigned_scaled_f32_i8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrb.u32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i8>, <4 x i8>* %offptr, align 1
  %offs.zext = zext <4 x i8> %offs to <4 x i32>
  %i32_ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.zext
  %ptrs = bitcast <4 x i32*> %i32_ptrs to <4 x float*>
  call void @llvm.masked.scatter.v4f32.v4p0f32(<4 x float> %input, <4 x float*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VSTRW.32 Qd, [base, offs.sext, uxtw #2]
define arm_aapcs_vfpcc void @b_signed_scaled_f32_i8(i32* %base, <4 x i8>* %offptr, <4 x float> %input) {
; CHECK-LABEL: b_signed_scaled_f32_i8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrb.s32 q1, [r1]
; CHECK-NEXT:    vstrw.32 q0, [r0, q1, uxtw #2]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i8>, <4 x i8>* %offptr, align 1
  %offs.sext = sext <4 x i8> %offs to <4 x i32>
  %i32_ptrs = getelementptr inbounds i32, i32* %base, <4 x i32> %offs.sext
  %ptrs = bitcast <4 x i32*> %i32_ptrs to <4 x float*>
  call void @llvm.masked.scatter.v4f32.v4p0f32(<4 x float> %input, <4 x float*> %ptrs, i32 4, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VLDRH.z32 Qd, [base, offs.sext, uxtw #1]
define arm_aapcs_vfpcc void @ext_signed_scaled_i16_i8(i16* %base, <4 x i8>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: ext_signed_scaled_i16_i8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrb.s32 q1, [r1]
; CHECK-NEXT:    vstrh.32 q0, [r0, q1, uxtw #1]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i8>, <4 x i8>* %offptr, align 1
  %offs.sext = sext <4 x i8> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i16, i16* %base, <4 x i32> %offs.sext
  %t = trunc <4 x i32> %input to <4 x i16>
  call void @llvm.masked.scatter.v4i16.v4p0i16(<4 x i16> %t, <4 x i16*> %ptrs, i32 2, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

; VLDRH.z32 Qd, [base, offs.zext, uxtw #1]
define arm_aapcs_vfpcc void @ext_unsigned_scaled_i16_i8(i16* %base, <4 x i8>* %offptr, <4 x i32> %input) {
; CHECK-LABEL: ext_unsigned_scaled_i16_i8:
; CHECK:       @ %bb.0: @ %entry
; CHECK-NEXT:    vldrb.u32 q1, [r1]
; CHECK-NEXT:    vstrh.32 q0, [r0, q1, uxtw #1]
; CHECK-NEXT:    bx lr
entry:
  %offs = load <4 x i8>, <4 x i8>* %offptr, align 1
  %offs.zext = zext <4 x i8> %offs to <4 x i32>
  %ptrs = getelementptr inbounds i16, i16* %base, <4 x i32> %offs.zext
  %t = trunc <4 x i32> %input to <4 x i16>
  call void @llvm.masked.scatter.v4i16.v4p0i16(<4 x i16> %t, <4 x i16*> %ptrs, i32 2, <4 x i1> <i1 true, i1 true, i1 true, i1 true>)
  ret void
}

declare void @llvm.masked.scatter.v4i8.v4p0i8(<4 x i8>, <4 x i8*>, i32, <4 x i1>)
declare void @llvm.masked.scatter.v4i16.v4p0i16(<4 x i16>, <4 x i16*>, i32, <4 x i1>)
declare void @llvm.masked.scatter.v4f16.v4p0f16(<4 x half>, <4 x half*>, i32, <4 x i1>)
declare void @llvm.masked.scatter.v4i32.v4p0i32(<4 x i32>, <4 x i32*>, i32, <4 x i1>)
declare void @llvm.masked.scatter.v4f32.v4p0f32(<4 x float>, <4 x float*>, i32, <4 x i1>)
