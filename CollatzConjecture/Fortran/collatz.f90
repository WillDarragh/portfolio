! Collatz Conjecture
! Will Darragh

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
   
   val = i
   length = 0
   do while ( val /= 1 )
        if ( mod(val,2) == 0 ) then
           val = val/2
        else
           val = 3*val + 1
        endif
        length = length+1
   enddo

end subroutine collatz_length
