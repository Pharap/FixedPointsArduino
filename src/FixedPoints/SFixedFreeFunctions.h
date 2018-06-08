// Copyright 2017-2018 Pharap
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

FIXED_POINTS_BEGIN_NAMESPACE

//
// multiply
//

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer * 2, Fraction * 2> multiply(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	static_assert(((Integer + 1) * 2 + Fraction * 2) <= FIXED_POINTS_DETAILS::BitSize<intmax_t>::Value, "Multiplication cannot be performed, the result type would be too large");	

	using ResultType = SFixed<Integer * 2, Fraction * 2>;
	using InternalType = typename ResultType::InternalType;
	return ResultType::fromInternal(static_cast<InternalType>(static_cast<InternalType>(left.getInternal()) * static_cast<InternalType>(right.getInternal())));
}

//
// Basic Logic Operations
//

template< unsigned Integer, unsigned Fraction >
constexpr bool operator ==(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	return (left.getInternal() == right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator !=(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	return (left.getInternal() != right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	return (left.getInternal() < right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	return (left.getInternal() > right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <=(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	return (left.getInternal() <= right.getInternal());
}

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >=(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	return (left.getInternal() >= right.getInternal());
}

//
// Inter-size Logic Operations
//

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator ==(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator == has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) == static_cast<CompareType>(right));
}

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator !=(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator != has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) != static_cast<CompareType>(right));
}

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator <(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator < has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) < static_cast<CompareType>(right));
}

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator >(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator > has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) > static_cast<CompareType>(right));
}

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator <=(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator <= has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) <= static_cast<CompareType>(right));
}

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator >=(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator >= has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) >= static_cast<CompareType>(right));
}

//
// Basic Arithmetic Operations
//

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator +(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	return SFixed<Integer, Fraction>::fromInternal(static_cast<InternalType>(left.getInternal() + right.getInternal()));
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator -(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	return SFixed<Integer, Fraction>::fromInternal(static_cast<InternalType>(left.getInternal() - right.getInternal()));
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator *(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	static_assert(((Integer + 1) * 2 + Fraction * 2) <= FIXED_POINTS_DETAILS::BitSize<intmax_t>::Value, "Multiplication cannot be performed, the intermediary type would be too large");	
	
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename SFixed<Integer * 2, Fraction * 2>::InternalType;
	return SFixed<Integer, Fraction>::fromInternal(static_cast<InternalType>((static_cast<PrecisionType>(left.getInternal()) * static_cast<PrecisionType>(right.getInternal())) >> Fraction));
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator /(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right)
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename SFixed<Integer * 2, Fraction * 2>::InternalType;
	return SFixed<Integer, Fraction>::fromInternal(static_cast<InternalType>((static_cast<PrecisionType>(left.getInternal()) << Fraction) / right.getInternal()));
}

//
// Inter-size Arithmetic Operations
//

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator +(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator + has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) + static_cast<CompareType>(right));
}

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator -(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator - has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) - static_cast<CompareType>(right));
}

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator *(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator * has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) * static_cast<CompareType>(right));
}


template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator /(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >
{
	using LeftType = SFixed<IntegerLeft, FractionLeft>;
	using RightType = SFixed<IntegerRight, FractionRight>;

	static_assert(LeftType::InternalSize != RightType::InternalSize, "operator / has ambiguous result");
	
	using CompareType = FIXED_POINTS_DETAILS::LargerType<LeftType, RightType>;
	
	return (static_cast<CompareType>(left) / static_cast<CompareType>(right));
}

//
// Literal-type Operators
// Generated by macro to make maintenance easier
//

#define LOGIC_OPERATOR( type, op )\
	template< unsigned Integer, unsigned Fraction >\
	constexpr bool operator op (const SFixed<Integer, Fraction> & left, const type & right)\
	{\
		return (left op SFixed<Integer, Fraction>(right));\
	}\
	\
	template< unsigned Integer, unsigned Fraction >\
	constexpr bool operator op (const type & left, const SFixed<Integer, Fraction> & right)\
	{\
		return (SFixed<Integer, Fraction>(left) op right);\
	}

#define ARITHMETIC_OPERATOR( type, op )\
	template< unsigned Integer, unsigned Fraction >\
	constexpr SFixed<Integer, Fraction> operator op (const SFixed<Integer, Fraction> & left, const type & right)\
	{\
		return (left op SFixed<Integer, Fraction>(right));\
	}\
	\
	template< unsigned Integer, unsigned Fraction >\
	constexpr SFixed<Integer, Fraction> operator op (const type & left, const SFixed<Integer, Fraction> & right)\
	{\
		return (SFixed<Integer, Fraction>(left) op right);\
	}
	
#define LOGIC_OPERATORS( type )\
	LOGIC_OPERATOR( type, == )\
	LOGIC_OPERATOR( type, != )\
	LOGIC_OPERATOR( type, < )\
	LOGIC_OPERATOR( type, <= )\
	LOGIC_OPERATOR( type, > )\
	LOGIC_OPERATOR( type, >= )
			
#define ARITHMETIC_OPERATORS( type ) \
	ARITHMETIC_OPERATOR( type, + )\
	ARITHMETIC_OPERATOR( type, - )\
	ARITHMETIC_OPERATOR( type, * )\
	ARITHMETIC_OPERATOR( type, / )
		
#define OPERATORS( type ) \
	LOGIC_OPERATORS( type )\
	ARITHMETIC_OPERATORS( type )

OPERATORS( float )
OPERATORS( double )
OPERATORS( long double )

OPERATORS( char )
OPERATORS( unsigned char )
OPERATORS( signed char )
OPERATORS( unsigned short int )
OPERATORS( signed short int )
OPERATORS( unsigned int )
OPERATORS( signed int )
OPERATORS( unsigned long int )
OPERATORS( signed long int )
OPERATORS( unsigned long long int )
OPERATORS( signed long long int )

// Prevent Macro-bleed:

#undef OPERATORS
#undef ARITHMETIC_OPERATORS
#undef LOGIC_OPERATORS
#undef ARITHMETIC_OPERATOR
#undef LOGIC_OPERATOR


//
// Literal-type Operators
// Generated by macro to make maintenance easier
//

#define LOGIC_OPERATOR( type, op )\
	template< unsigned Fraction >\
	constexpr bool operator op (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return (left op SFixed<0, Fraction>(right));\
	}\
	\
	template< unsigned Fraction >\
	constexpr bool operator op (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return (SFixed<0, Fraction>(left) op right);\
	}

#define DELETED_LOGIC_OPERATOR_EQ( type )\
	template< unsigned Fraction >\
	constexpr bool operator == (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return false;\
	}\
	\
	template< unsigned Fraction >\
	constexpr bool operator == (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return false;\
	}

#define DELETED_LOGIC_OPERATOR_NE( type )\
	template< unsigned Fraction >\
	constexpr bool operator != (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return true;\
	}\
	\
	template< unsigned Fraction >\
	constexpr bool operator != (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return true;\
	}

#define DELETED_LOGIC_OPERATOR_LT( type )\
	template< unsigned Fraction >\
	constexpr bool operator < (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return true;\
	}\
	\
	template< unsigned Fraction >\
	constexpr bool operator < (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return false;\
	}

#define DELETED_LOGIC_OPERATOR_LTE( type )\
	template< unsigned Fraction >\
	constexpr bool operator <= (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return true;\
	}\
	\
	template< unsigned Fraction >\
	constexpr bool operator <= (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return false;\
	}

#define DELETED_LOGIC_OPERATOR_GT( type )\
	template< unsigned Fraction >\
	constexpr bool operator > (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return false;\
	}\
	\
	template< unsigned Fraction >\
	constexpr bool operator > (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return true;\
	}

#define DELETED_LOGIC_OPERATOR_GTE( type )\
	template< unsigned Fraction >\
	constexpr bool operator >= (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return false;\
	}\
	\
	template< unsigned Fraction >\
	constexpr bool operator >= (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return true;\
	}

#define ARITHMETIC_OPERATOR( type, op )\
	template< unsigned Fraction >\
	constexpr SFixed<0, Fraction> operator op (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return (left op SFixed<0, Fraction>(right));\
	}\
	\
	template< unsigned Fraction >\
	constexpr SFixed<0, Fraction> operator op (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return (SFixed<0, Fraction>(left) op right);\
	}

#define DELETED_ARITHMETIC_OPERATOR( type, op )\
	template< unsigned Fraction >\
	constexpr SFixed<0, Fraction> operator op (const SFixed<0, Fraction> & left, const type & right)\
	{\
		return 0;\
	}\
	\
	template< unsigned Fraction >\
	constexpr SFixed<0, Fraction> operator op (const type & left, const SFixed<0, Fraction> & right)\
	{\
		return 0;\
	}
	
#define LOGIC_OPERATORS( type ) \
	LOGIC_OPERATOR( type, == )\
	LOGIC_OPERATOR( type, != )\
	LOGIC_OPERATOR( type, < )\
	LOGIC_OPERATOR( type, <= )\
	LOGIC_OPERATOR( type, > )\
	LOGIC_OPERATOR( type, >= )
			
#define ARITHMETIC_OPERATORS( type ) \
	ARITHMETIC_OPERATOR( type, + )\
	ARITHMETIC_OPERATOR( type, - )\
	ARITHMETIC_OPERATOR( type, * )\
	ARITHMETIC_OPERATOR( type, / )
	
#define DELETED_LOGIC_OPERATORS( type ) \
	DELETED_LOGIC_OPERATOR_EQ( type )\
	DELETED_LOGIC_OPERATOR_NE( type )\
	DELETED_LOGIC_OPERATOR_LT( type )\
	DELETED_LOGIC_OPERATOR_LTE( type )\
	DELETED_LOGIC_OPERATOR_GT( type )\
	DELETED_LOGIC_OPERATOR_GTE( type )
			
#define DELETED_ARITHMETIC_OPERATORS( type ) \
	DELETED_ARITHMETIC_OPERATOR( type, + )\
	DELETED_ARITHMETIC_OPERATOR( type, - )\
	DELETED_ARITHMETIC_OPERATOR( type, * )\
	DELETED_ARITHMETIC_OPERATOR( type, / )
		
#define OPERATORS( type ) \
	LOGIC_OPERATORS( type )\
	ARITHMETIC_OPERATORS( type )
		
#define DELETED_OPERATORS( type ) \
	DELETED_LOGIC_OPERATORS( type )\
	DELETED_ARITHMETIC_OPERATORS( type )

OPERATORS( float )
OPERATORS( double )
OPERATORS( long double )

DELETED_OPERATORS( char )
DELETED_OPERATORS( unsigned char )
DELETED_OPERATORS( signed char )
DELETED_OPERATORS( unsigned short int )
DELETED_OPERATORS( signed short int )
DELETED_OPERATORS( unsigned int )
DELETED_OPERATORS( signed int )
DELETED_OPERATORS( unsigned long int )
DELETED_OPERATORS( signed long int )
DELETED_OPERATORS( unsigned long long int )
DELETED_OPERATORS( signed long long int )

// Prevent Macro-bleed:

#undef DELETED_OPERATORS
#undef OPERATORS

#undef DELETED_ARITHMETIC_OPERATORS
#undef DELETED_LOGIC_OPERATORS

#undef ARITHMETIC_OPERATORS
#undef LOGIC_OPERATORS

#undef DELETED_ARITHMETIC_OPERATOR
#undef ARITHMETIC_OPERATOR

#undef DELETED_LOGIC_OPERATOR_EQ
#undef DELETED_LOGIC_OPERATOR_NE
#undef DELETED_LOGIC_OPERATOR_LT
#undef DELETED_LOGIC_OPERATOR_LTE
#undef DELETED_LOGIC_OPERATOR_GT
#undef DELETED_LOGIC_OPERATOR_GTE

#undef LOGIC_OPERATOR

FIXED_POINTS_END_NAMESPACE