

define void @foo_nested() {
entry:
  br label %outer

outer:
  %i = phi i32 [0, %entry], [%i_next, %exit_inner]
  %cmp_outer = icmp slt i32 %i, 3
  br i1 %cmp_outer, label %inner, label %exit_outer

inner:
  %j = phi i32 [0, %outer], [%j_next, %inner]
  %a = add i32 5, 10       ; invariant
  %j_next = add i32 %j, 1
  %cmp_inner = icmp slt i32 %j, 2
  br i1 %cmp_inner, label %inner, label %exit_inner

exit_inner:
  %i_next = add i32 %i, 1
  br label %outer

exit_outer:
  ret void
}
