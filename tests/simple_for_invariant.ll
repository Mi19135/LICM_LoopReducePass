define void @foo() {
entry:
  br label %loop

loop:
  %i = phi i32 [0, %entry], [%i_next, %loop]
  %a = add i32 1, 2      ; invariant
  %b = add i32 %a, 3     ; invariant
  %i_next = add i32 %i, 1
  %cmp = icmp slt i32 %i, 5
  br i1 %cmp, label %loop, label %exit

exit:
  ret void
}
