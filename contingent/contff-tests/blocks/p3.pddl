

(define (problem BW-rand-3)
(:domain blocksworld)
(:objects b1 b2 )
(:init
(unknown (on-table b1))
(unknown (on-table b2))
(unknown (clear b1))
(unknown (clear b2))
(unknown (on b1 b2))
(unknown (on b2 b1))
(oneof
(clear b1)
(clear b2)
)

)
(:goal
(on b1 b2)
)
)

