! Collatz Conjecture
! Recursive Version

program collatz

integer :: i, val, length

! MAX NUMBER
do i = 1, 10
   val = i
   length = 0
   call collatz_length(i, val, length)
   print *, i, length
enddo

end program collatz


recursive subroutine collatz_length( i, val, length )

integer :: i, val, length

!print *, i, val, length

if ( val == 1 ) then
   return
else
   if ( mod(val,2) == 0 ) then
      val = val/2
   else
      val = 3*val+1
   endif
   length = length+1
   call collatz_length(i, val, length)
endif

end subroutine collatz_length
