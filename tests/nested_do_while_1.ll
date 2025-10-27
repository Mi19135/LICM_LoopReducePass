; ModuleID = 'nested_do_while_1.cpp'
source_filename = "nested_do_while_1.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @_Z16foo_nested_whilev() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 0, ptr %2, align 4
  br label %6

6:                                                ; preds = %25, %0
  %7 = load i32, ptr %2, align 4
  %8 = icmp slt i32 %7, 3
  br i1 %8, label %9, label %28

9:                                                ; preds = %6
  store i32 15, ptr %3, align 4
  store i32 0, ptr %4, align 4
  br label %10

10:                                               ; preds = %22, %9
  store i32 14, ptr %5, align 4
  %11 = load i32, ptr %3, align 4
  %12 = load i32, ptr %5, align 4
  %13 = add nsw i32 %11, %12
  %14 = load i32, ptr %2, align 4
  %15 = add nsw i32 %13, %14
  %16 = load i32, ptr %4, align 4
  %17 = add nsw i32 %15, %16
  %18 = load i32, ptr %1, align 4
  %19 = add nsw i32 %18, %17
  store i32 %19, ptr %1, align 4
  %20 = load i32, ptr %4, align 4
  %21 = add nsw i32 %20, 1
  store i32 %21, ptr %4, align 4
  br label %22

22:                                               ; preds = %10
  %23 = load i32, ptr %4, align 4
  %24 = icmp slt i32 %23, 2
  br i1 %24, label %10, label %25, !llvm.loop !6

25:                                               ; preds = %22
  %26 = load i32, ptr %2, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, ptr %2, align 4
  br label %6, !llvm.loop !8

28:                                               ; preds = %6
  ret void
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
