#!/usr/bin/sbcl --script

; Collatz in Lisp
; Will Darragh

; MAX NUMBER
(defvar N 10)

(defvar collatz_length 0)

(defun collatz (x)
	(setq collatz_length 0)
	(loop while (not (= x 1) )
		do (if (= (mod x 2) 0 )
			(setq x (/ x 2) )
			(setq x (+ (* 3 x) 1) ) )
		(incf collatz_length)
	)
	collatz_length
)

(loop for n from 1 to N do (format t "    ~d    ~d~%" n (collatz n) ) )
