-- Collatz in Ada
-- Will Darragh

with Ada.Text_IO; use Ada.Text_IO;

procedure collatz is


	-- MAX NUMBER
	N : Integer := 10;

	x, length : Integer;

	subtype loop_range is Integer range 1 .. N;

begin

	for n in loop_range loop

		x := n;
		length := 0;

		while x /= 1 loop

			if (x mod 2) = 0 then
				x := x/2;
			else
				x := 3*x + 1;
			end if;

			length := length + 1;

		end loop;

		Put_Line( Integer'Image(n) & "    " & Integer'Image(length) );

	end loop;

end collatz;
