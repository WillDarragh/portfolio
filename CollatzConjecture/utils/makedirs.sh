#!/usr/bin/bash

languages=('C++' 'Java' 'C#' 'Fortran' 'Ada' 'Perl' 'Python' 'Ruby' 'Lisp' 'Julia')

for i in "${languages[@]}"; do
	echo  "$i"
	mkdir "$i"
	mkdir "$i/recursed"
done
