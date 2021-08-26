#include "curry_howard_iso.hpp"

// Modus Ponens: If p then q; p; therefore q
typedef COND<AND<COND<P,Q>, P>,Q> ModusPonens;

ModusPonens proof_mp = [](AND<COND<P,Q>, P> premises)->Q {
    COND<P,Q> premise1 = std::get<0>(premises);
    P premise2 = std::get<1>(premises);
    return premise1(premise2);
};

// Modus Tollens: If p then q; not q; therefore not p
typedef COND<AND<COND<P,Q>,NEG<Q>>,NEG<P>> ModusTollens;

ModusTollens proof_mt = [](AND<COND<P,Q>,NEG<Q>> premises)->NEG<P> {
    COND<P,Q> premise1 = std::get<0>(premises);
    NEG<Q> premise2 = std::get<1>(premises);   

    return [&](P p)->FALSE {
        return premise2(premise1(p));
    };
};


// De Morgan's Theorem (1): If  not  (p or q)); is equiv. (not p and not q)
typedef EQUIV<NEG<OR<P,Q>>,AND<NEG<P>,NEG<Q>>> DeMorganTheorem1;

auto proof_demorg1_left = [](NEG<OR<P,Q>> premise)->AND<NEG<P>,NEG<Q>> {
    NEG<P> not_p = [&](P p)->FALSE{
        OR<P,Q> p_or_q(p);
        return premise(p_or_q);
    };
     NEG<Q> not_q = [&](Q q)->FALSE{
        OR<P,Q> p_or_q(q);
        return premise(p_or_q);
    };  
    return AND<NEG<P>,NEG<Q>>(not_p, not_q);
};
auto proof_demorg1_right = [](AND<NEG<P>,NEG<Q>> premise)->NEG<OR<P,Q>> {
	NEG<P> np = std::get<0>(premise);
    NEG<Q> nq = std::get<1>(premise);

    return match{
		[&](P p)->FALSE {return np(p);},
		[&](Q q)->FALSE {return nq(q);}
	};
};


DeMorganTheorem1 proof_dm1 = AND(proof_demorg1_left,  proof_demorg1_right);

