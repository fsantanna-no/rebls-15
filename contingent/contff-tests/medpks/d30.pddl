(define (domain medicalPKS30)
 (:predicates 
 (dead)
    (stain ?i - STAIN) 
               (ill ?i - ILLNESS)
 
  )

 
(:action inspect-stain
   :parameters (?i - STAIN)
   :precondition (not (dead))
   :observe (stain ?i))
(:action medicate
  :parameters (?i - ILLNESS)
  :precondition (and (not (dead)) (not (ill i0)))
  :effect (and (when (ill ?i) (ill i0))
               (when (not (ill ?i)) (dead))))
(:action stain
                   :parameters ()
                   :precondition (not (dead))
                   :effect (and (when (ill i1) (stain s1))
 (when (ill i2) (stain s2))
 (when (ill i3) (stain s3))
 (when (ill i4) (stain s4))
 (when (ill i5) (stain s5))
 (when (ill i6) (stain s6))
 (when (ill i7) (stain s7))
 (when (ill i8) (stain s8))
 (when (ill i9) (stain s9))
 (when (ill i10) (stain s10))
 (when (ill i11) (stain s11))
 (when (ill i12) (stain s12))
 (when (ill i13) (stain s13))
 (when (ill i14) (stain s14))
 (when (ill i15) (stain s15))
 (when (ill i16) (stain s16))
 (when (ill i17) (stain s17))
 (when (ill i18) (stain s18))
 (when (ill i19) (stain s19))
 (when (ill i20) (stain s20))
 (when (ill i21) (stain s21))
 (when (ill i22) (stain s22))
 (when (ill i23) (stain s23))
 (when (ill i24) (stain s24))
 (when (ill i25) (stain s25))
 (when (ill i26) (stain s26))
 (when (ill i27) (stain s27))
 (when (ill i28) (stain s28))
 (when (ill i29) (stain s29))
 (when (ill i30) (stain s30))
))
)