-- Collatz in Ada with Recursion
-- Will Darragh

with Ada.Text_IO; use Ada.Text_IO;

procedure collatz_r is

	-- MAX NUMBER
	N : Integer := 10;

	length : Integer;

	subtype loop_range is Integer range 1 .. N;

function collatz_length(n : Integer) return Integer is
	
	x : Integer;

begin

	x := n;

	if ( x = 1 ) then
		return 0;
	else

		if ( x mod 2) = 0 then
			x := x/2;
		else
			x := 3*x + 1;
		end if;

		return (1 + collatz_length(x));
		
	end if;
	
end;

begin

	for n in loop_range loop

		length := collatz_length(n);

		Put_Line( Integer'Image(n) & "    " & Integer'Image(length) );

	end loop;

end collatz_r;
