#!/usr/bin/sbcl --script

; Collatz in Lisp with Recursion
; Will Darragh

; MAX NUMBER
(defvar N 10)

(defun collatz (x)
	(if (= x 1 ) 
		0
		(progn (if (= (mod x 2) 0)
			(setq x (/ x 2))
			(setq x (+ (* 3 x) 1) ) )
		(+ (collatz x) 1) ) )
)

(loop for n from 1 to N do (format t "    ~d    ~d~%" n (collatz n) ) )
