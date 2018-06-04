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

#pragma once

#include "Details.h"

FIXED_POINTS_BEGIN_NAMESPACE

//
// Declaration
//

// Predeclaration
template< unsigned Integer, unsigned Fraction > class SFixed;

template< unsigned Fraction >
class SFixed<0, Fraction>
{
public:
	constexpr const static uintmax_t IntegerSize = 1;
	constexpr const static uintmax_t FractionSize = Fraction;
	constexpr const static uintmax_t LogicalSize = IntegerSize + FractionSize;
	constexpr const static uintmax_t Scale = UINTMAX_C(1) << FractionSize;

public:
	static_assert(LogicalSize <= FIXED_POINTS_DETAILS::BitSize<intmax_t>::Value, "Platform does not have a native type large enough for SFixed.");

public:
	using IntegerType = FIXED_POINTS_DETAILS::LeastInt<IntegerSize>;
	using FractionType = FIXED_POINTS_DETAILS::LeastUInt<FractionSize>;
	using InternalType = FIXED_POINTS_DETAILS::LeastInt<LogicalSize>;

	constexpr const static uintmax_t InternalSize = FIXED_POINTS_DETAILS::BitSize<InternalType>::Value;
	
	using ShiftType = FIXED_POINTS_DETAILS::LeastUInt<LogicalSize>;
	using MaskType = FIXED_POINTS_DETAILS::LeastUInt<LogicalSize>;
		
public:
	constexpr const static ShiftType IntegerShift = FractionSize;
	constexpr const static ShiftType FractionShift = 0;
	
	constexpr const static MaskType IntegerMask = FIXED_POINTS_DETAILS::IdentityMask<IntegerSize>::Value;
	constexpr const static MaskType FractionMask = FIXED_POINTS_DETAILS::IdentityMask<FractionSize>::Value;
	
	constexpr const static MaskType IdentityMask = (IntegerMask << IntegerShift) | (FractionMask << FractionShift);
	
	constexpr const static MaskType MidpointMask = FIXED_POINTS_DETAILS::MsbMask<FractionSize>::Value;
	constexpr const static MaskType LesserMidpointMask = MidpointMask - 1;

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

protected:
	constexpr SFixed(const RawType & value);

public:
	constexpr SFixed(void);
	constexpr SFixed(const IntegerType & integer, const FractionType & fraction);
	constexpr SFixed(const char & value) = delete;
	constexpr SFixed(const unsigned char & value) = delete;
	constexpr SFixed(const signed char & value) = delete;
	constexpr SFixed(const unsigned short int & value) = delete;
	constexpr SFixed(const signed short int & value) = delete;
	constexpr SFixed(const unsigned int & value) = delete;
	constexpr SFixed(const signed int & value) = delete;
	constexpr SFixed(const unsigned long int & value) = delete;
	constexpr SFixed(const signed long int & value) = delete;
	constexpr SFixed(const unsigned long long int & value) = delete;
	constexpr SFixed(const signed long long int & value) = delete;
	constexpr SFixed(const double & value);
	constexpr SFixed(const float & value);
	constexpr SFixed(const long double & value);

	constexpr InternalType getInternal(void) const;
	constexpr IntegerType getInteger(void) const;
	constexpr FractionType getFraction(void) const;

	constexpr explicit operator IntegerType(void) const;
	constexpr explicit operator float(void) const;
	constexpr explicit operator double(void) const;
	constexpr explicit operator long double(void) const;

	template< unsigned IntegerOut, unsigned FractionOut >
	constexpr explicit operator SFixed<IntegerOut, FractionOut>(void) const;

	constexpr static SFixed fromInternal(const InternalType & value);

	constexpr SFixed operator -(void) const;
	SFixed & operator +=(const SFixed & other);
	SFixed & operator -=(const SFixed & other);
	SFixed & operator *=(const SFixed & other);
	SFixed & operator /=(const SFixed & other);
	
public:
	constexpr const static SFixed Epsilon = SFixed::fromInternal(1);
	constexpr const static SFixed MinValue = SFixed::fromInternal(FIXED_POINTS_DETAILS::MsbMask<InternalSize>::Value);
	constexpr const static SFixed MaxValue = SFixed::fromInternal(~FIXED_POINTS_DETAILS::MsbMask<InternalSize>::Value);
	
	// Pi, E, Phi and Tau will never be representable by 0 integer fixed points
};

FIXED_POINTS_END_NAMESPACE

#include "SFixed0MemberFunctions.h"
#include "SFixed0FreeFunctions.h"