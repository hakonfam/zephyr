; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --function-signature --scrub-attributes
; RUN: opt -S -passes=attributor -aa-pipeline='basic-aa' -attributor-disable=false -attributor-max-iterations-verify -attributor-max-iterations=1 < %s | FileCheck %s
; PR36543

; Don't promote arguments of musttail callee

%T = type { i32, i32, i32, i32 }

define internal i32 @test(%T* %p) {
; CHECK-LABEL: define {{[^@]+}}@test
; CHECK-SAME: (%T* nocapture nofree readonly [[P:%.*]])
; CHECK-NEXT:    [[A_GEP:%.*]] = getelementptr [[T:%.*]], %T* [[P]], i64 0, i32 3
; CHECK-NEXT:    [[B_GEP:%.*]] = getelementptr [[T]], %T* [[P]], i64 0, i32 2
; CHECK-NEXT:    [[A:%.*]] = load i32, i32* [[A_GEP]]
; CHECK-NEXT:    [[B:%.*]] = load i32, i32* [[B_GEP]]
; CHECK-NEXT:    [[V:%.*]] = add i32 [[A]], [[B]]
; CHECK-NEXT:    ret i32 [[V]]
;
  %a.gep = getelementptr %T, %T* %p, i64 0, i32 3
  %b.gep = getelementptr %T, %T* %p, i64 0, i32 2
  %a = load i32, i32* %a.gep
  %b = load i32, i32* %b.gep
  %v = add i32 %a, %b
  ret i32 %v
}

define i32 @caller(%T* %p) {
; CHECK-LABEL: define {{[^@]+}}@caller
; CHECK-SAME: (%T* nocapture nofree readonly [[P:%.*]])
; CHECK-NEXT:    [[V:%.*]] = musttail call i32 @test(%T* nocapture nofree readonly [[P]])
; CHECK-NEXT:    ret i32 [[V]]
;
  %v = musttail call i32 @test(%T* %p)
  ret i32 %v
}

; Don't promote arguments of musttail caller

define i32 @foo(%T* %p, i32 %v) {
; CHECK-LABEL: define {{[^@]+}}@foo
; CHECK-SAME: (%T* nocapture nofree readnone [[P:%.*]], i32 [[V:%.*]])
; CHECK-NEXT:    ret i32 0
;
  ret i32 0
}

define internal i32 @test2(%T* %p, i32 %p2) {
  %a.gep = getelementptr %T, %T* %p, i64 0, i32 3
  %b.gep = getelementptr %T, %T* %p, i64 0, i32 2
  %a = load i32, i32* %a.gep
  %b = load i32, i32* %b.gep
  %v = add i32 %a, %b
  %ca = musttail call i32 @foo(%T* undef, i32 %v)
  ret i32 %ca
}

define i32 @caller2(%T* %g) {
; CHECK-LABEL: define {{[^@]+}}@caller2
; CHECK-SAME: (%T* nocapture nofree readnone [[G:%.*]])
; CHECK-NEXT:    ret i32 0
;
  %v = call i32 @test2(%T* %g, i32 0)
  ret i32 %v
}

; In the version above we can remove the call to foo completely.
; In the version below we keep the call and verify the return value
; is kept as well.

define i32 @bar(%T* %p, i32 %v) {
; CHECK-LABEL: define {{[^@]+}}@bar
; CHECK-SAME: (%T* nocapture nofree nonnull writeonly dereferenceable(4) [[P:%.*]], i32 [[V:%.*]])
; CHECK-NEXT:    [[I32PTR:%.*]] = getelementptr [[T:%.*]], %T* [[P]], i64 0, i32 0
; CHECK-NEXT:    store i32 [[V]], i32* [[I32PTR]]
; CHECK-NEXT:    ret i32 0
;
  %i32ptr = getelementptr %T, %T* %p, i64 0, i32 0
  store i32 %v, i32* %i32ptr
  ret i32 0
}

define internal i32 @test2b(%T* %p, i32 %p2) {
; CHECK-LABEL: define {{[^@]+}}@test2b
; CHECK-SAME: (%T* nocapture nofree readonly [[P:%.*]], i32 [[P2:%.*]])
; CHECK-NEXT:    [[A_GEP:%.*]] = getelementptr [[T:%.*]], %T* [[P]], i64 0, i32 3
; CHECK-NEXT:    [[B_GEP:%.*]] = getelementptr [[T]], %T* [[P]], i64 0, i32 2
; CHECK-NEXT:    [[A:%.*]] = load i32, i32* [[A_GEP]]
; CHECK-NEXT:    [[B:%.*]] = load i32, i32* [[B_GEP]]
; CHECK-NEXT:    [[V:%.*]] = add i32 [[A]], [[B]]
; CHECK-NEXT:    [[CA:%.*]] = musttail call i32 @bar(%T* undef, i32 [[V]])
; CHECK-NEXT:    ret i32 [[CA]]
;
  %a.gep = getelementptr %T, %T* %p, i64 0, i32 3
  %b.gep = getelementptr %T, %T* %p, i64 0, i32 2
  %a = load i32, i32* %a.gep
  %b = load i32, i32* %b.gep
  %v = add i32 %a, %b
  %ca = musttail call i32 @bar(%T* undef, i32 %v)
  ret i32 %ca
}

define i32 @caller2b(%T* %g) {
; CHECK-LABEL: define {{[^@]+}}@caller2b
; CHECK-SAME: (%T* nocapture nofree readonly [[G:%.*]])
; CHECK-NEXT:    [[V:%.*]] = call i32 @test2b(%T* nocapture nofree readonly [[G]], i32 undef)
; CHECK-NEXT:    ret i32 0
;
  %v = call i32 @test2b(%T* %g, i32 0)
  ret i32 %v
}
