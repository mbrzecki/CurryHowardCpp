

module Laws =
    type False private () = do ()

    type Or<'p, 'q> =
        |Left of 'p
        |Right of 'q

    type And<'p, 'q> = 'p * 'q

    type Cond<'p, 'q> = 'p -> 'q

    type Equiv<'p, 'q> = And<Cond<'p,'q>, Cond<'q,'p>>

    type Neg<'p> = Cond<'p, False>

    // De Morgan's Theorem (1): If  not  (p or q)); is equiv. (not p and not q)
    type DeMorganTheorem1<'p, 'q> = Equiv<Neg<Or<'p,'q>>,And<Neg<'p>,Neg<'q>>>

    let proof : DeMorganTheorem1<'p, 'q> =
        let proof_demorg1_left =
            fun (notOrPQ:Neg<Or<'p,'q>>) ->
                let notP p = notOrPQ (Left p) 
                let notQ q = notOrPQ (Right q) 
                notP, notQ
        let proof_demorg1_right = 
            fun ((notP:Neg<'p>), (notQ:Neg<'q>)) ->
                let notOrPQ =
                    function
                    |Left p -> notP p
                    |Right q-> notQ q
                notOrPQ
        proof_demorg1_left, proof_demorg1_right