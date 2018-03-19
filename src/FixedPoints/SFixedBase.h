// Copyright 2017 Pharap
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
		constexpr SFixedBase(const char & value)
			: value(static_cast<InternalType>(static_cast< LargerType<char, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const unsigned char & value)
			: value(static_cast<InternalType>(static_cast< LargerType<unsigned char, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const signed char & value)
			: value(static_cast<InternalType>(static_cast< LargerType<signed char, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const unsigned short int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<unsigned short int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const signed short int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<signed short int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const unsigned int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<unsigned int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const signed int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<signed int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const unsigned long int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<unsigned long int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const signed long int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<signed long int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const unsigned long long int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<unsigned long long int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const signed long long int & value)
			: value(static_cast<InternalType>(static_cast< LargerType<signed long long int, InternalType> >(value) << Fraction)) {}

		constexpr SFixedBase(const double & value)
			: value(static_cast<InternalType>(value * static_cast<double>(Scale))) {}

		constexpr SFixedBase(const float & value)
			: value(static_cast<InternalType>(value * static_cast<float>(Scale))) {}

		constexpr SFixedBase(const long double & value)
			: value(static_cast<InternalType>(value * static_cast<long double>(Scale))) {}
	};
}
FIXED_POINTS_END_NAMESPACE