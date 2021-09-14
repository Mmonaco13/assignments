#lang eopl
;;Matthew Monaco
;;I pledge my honor that I have abided by the Stevens Honor System.

;; Some basic logic operators, defined in terms of Scheme's built-in 
;; and,or,not 

;; Remember that Scheme uses prefix notation, so "x ^ y" is written "(and x y)"


;; Define (nand p q) which follows this truth table:
;; ((#t #t) #f)
;; ((#t #f) #t)
;; ((#f #t) #t)
;; ((#f #f) #t)


;; Type signature: (nand boolean boolean) -> boolean

(define (nand p q)
  (not (and p q))
)


;; Define if->then, it has the truth table
;; ((#t #t) #t)
;; ((#t #f) #f)
;; ((#f #t) #t)
;; ((#f #f) #t)

;; Type signature: (if->then boolean boolean) -> boolean

(define (if->then p q)
 (or (not p) (and p q))
)


;; Define (xor p q) exclusive or
;; ((#t #t) #f)
;; ((#t #f) #t)
;; ((#f #t) #t)
;; ((#f #f) #f)

;; Type signature: (xor boolean boolean) -> boolean

(define (xor p q)
  (not(eq? p q))
)


;; Define (nor p q)
;; ((#t #t) #f)
;; ((#t #f) #f)
;; ((#f #t) #f)
;; ((#f #f) #t)

;; Type signature: (nor boolean boolean) -> boolean
(define (nor p q)
  (and (not p) (not q))
)


;; Define (3majority p q r)
;; Create a function that returns #t when a majority of its three
;; arguments are #t
;; 
;; ((#t #t #t) #t)
;; ((#t #t #f) #t)
;; ((#t #f #t) #t)
;; ((#t #f #f) #f)
;; ((#f #t #t) #t)
;; ((#f #t #f) #f)
;; ((#f #f #t) #f)
;; ((#f #f #f) #f)

;; Type signature: (3majority boolean boolean boolean) -> boolean
(define (3majority p q r)
  (if (or (and p q) (and p r) (and q r))
      #t
      #f
  )

)


;; Define (isosceles p q r)
;; Create a function that returns #t when exactly two of its
;; arguments are #t

;; ((#t #t #t) #f)
;; ((#t #t #f) #t)
;; ((#t #f #t) #t)
;; ((#t #f #f) #f)
;; ((#f #t #t) #t)
;; ((#f #t #f) #f)
;; ((#f #f #t) #f)
;; ((#f #f #f) #f)

(define (isosceles p q r)
  (if (and (3majority p q r) (not(and p q r)) )
      #t
      #f
  )
)


;; Define (commutative? operator)
;; Returns #t iff the operator is commutative
;; i.e., in all cases (operator p q) is the same as (operator q p)
;; E.g. (commutative? nand) is #t since (nand p q) = (nand q p) in
;; all cases

;; Type signature: (commutative? operator) -> boolean
;; Where operator's type signature is (operator boolean boolean) -> boolean
(define (commutative? operator)
  (if (and(operator #t #f) (operator #f #t))
      #t
      #f
  )
)


;; January 2018
;; Samuel Kraus and Edward Minnix
;; Stevens Institute of Technology
;; CS 135  Discrete Structures