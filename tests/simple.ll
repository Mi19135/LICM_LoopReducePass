; simple.ll
; test za LICM simple pass

define void @foo() {
entry:
  br label %loop

loop:
  %i = phi i32 [0, %entry], [%next, %loop]
  %a = add i32 %i, 1
  %cmp = icmp slt i32 %i, 10
  %next = add i32 %i, 1
  br i1 %cmp, label %loop, label %exit

exit:
  ret void
}
