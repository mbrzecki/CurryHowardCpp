#pragma once

#include <variant>
#include <tuple>
#include <functional>


class FALSE {
public:
	template<typename statement>
	statement operator()() { return statement();};	
private:
	FALSE() {};
};


template<unsigned int i>
class STATEMENT {
public:
	friend class FALSE;
private:
	STATEMENT() {}
};

typedef STATEMENT<1> P;
typedef STATEMENT<2> Q;
typedef STATEMENT<3> R;
typedef STATEMENT<4> S;


template<typename... Ts> using AND = std::tuple<Ts...>;
template<typename... Ts> using OR = std::variant<Ts...>;
template<typename ARG, typename RET> using COND = std::function<RET(ARG)>;
template<typename LEFT, typename RIGHT> using EQUIV = AND<COND<LEFT,RIGHT>,COND<RIGHT,LEFT>>;
template<typename STATEMENT> using NEG = std::function<FALSE(STATEMENT)>;


template<typename... T>
struct match : T... { 
	using T::operator()...;

	template<typename... STATEMENTs>
	auto operator()(OR<STATEMENTs...> disjunction) {
		return std::visit(*this, disjunction);
	}	
};
template<typename... Ts> match(Ts...)->match<Ts...>;
