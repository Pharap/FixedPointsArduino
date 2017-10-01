#pragma once

#include "Details.h"

FIXED_POINTS_BEGIN_NAMESPACE
namespace FIXED_POINTS_DETAILS
{
	template< unsigned Integer, unsigned Fraction >
	class SFixedBase
	{
	public:
		using IntegerType = FIXED_POINTS_DETAILS::LeastInt<Integer + 1>;
		using FractionType = FIXED_POINTS_DETAILS::LeastUInt<Fraction>;
		using InternalType = FIXED_POINTS_DETAILS::LeastInt<(Integer + 1) + Fraction>;

		constexpr const static unsigned long long Scale = 1ULL << Fraction;

	protected:
		class RawType
		{
		private:
			const InternalType value;

		public:
			constexpr inline explicit RawType(const InternalType & value) : value(value) {}
			constexpr inline explicit operator InternalType(void) const { return this->value; }
		};

	protected:
		InternalType value;

		constexpr SFixedBase(void) : value(0) {}
		constexpr SFixedBase(const RawType & value) : value(static_cast<InternalType>(value)) {}
		
	public:
		constexpr SFixedBase(const IntegerLiteral & value)
			: value(static_cast<InternalType>(static_cast<LargerType<IntegerLiteral, InternalType> >(value) <<  Fraction)) {}
			
		constexpr SFixedBase(const IntegerLiteralU & value)
			: value(static_cast<InternalType>(static_cast<LargerType<IntegerLiteralU, InternalType> >(value) <<  Fraction)) {}
			
		constexpr SFixedBase(const IntegerLiteralL & value)
			: value(static_cast<InternalType>(static_cast<LargerType<IntegerLiteralL, InternalType> >(value) <<  Fraction)) {}
			
		constexpr SFixedBase(const IntegerLiteralUL & value)
			: value(static_cast<InternalType>(static_cast<LargerType<IntegerLiteralUL, InternalType>>(value) <<  Fraction)) {}
			
		constexpr SFixedBase(const IntegerLiteralLL & value)
			: value(static_cast<InternalType>(static_cast<LargerType<IntegerLiteralLL, InternalType>>(value) <<  Fraction)) {}
			
		constexpr SFixedBase(const IntegerLiteralULL & value)
			: value(static_cast<InternalType>(static_cast<LargerType<IntegerLiteralULL, InternalType> >(value) <<  Fraction)) {}
			
		constexpr SFixedBase(const DecimalLiteral & value)
			: value(static_cast<InternalType>(value * Scale)) {}
			
		constexpr SFixedBase(const DecimalLiteralF & value)
			: value(static_cast<InternalType>(value * Scale)) {}
			
		constexpr SFixedBase(const DecimalLiteralL & value)
			: value(static_cast<InternalType>(value * Scale)) {}
	};
}
FIXED_POINTS_END_NAMESPACE