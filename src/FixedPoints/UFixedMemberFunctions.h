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
// Constructors
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const RawType & value)
	: value(static_cast<InternalType>(value))
{
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::UFixed(const RawType & value)
	: value(static_cast<InternalType>(value))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(void)
	: value(0)
{
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::UFixed(void)
	: value(0)
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const IntegerType & integer, const FractionType & fraction)
	: value((static_cast<InternalType>(integer) << FractionSize) | fraction)
{
}

// The comma operator and void cast are used to circumvent an unused parameter warning
template< unsigned Fraction >
constexpr UFixed<0, Fraction>::UFixed(const IntegerType & integer, const FractionType & fraction)
	: value(((void)integer, fraction))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned short int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned short int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed short int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed short int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned long long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned long long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed long long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed long long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const double & value)
	: value(static_cast<InternalType>(value * static_cast<double>(Scale)))
{
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::UFixed(const double & value)
	: value(static_cast<InternalType>(value * static_cast<double>(Scale)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const float & value)
	: value(static_cast<InternalType>(value * static_cast<float>(Scale)))
{
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::UFixed(const float & value)
	: value(static_cast<InternalType>(value * static_cast<float>(Scale)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const long double & value)
	: value(static_cast<InternalType>(value * static_cast<long double>(Scale)))
{
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::UFixed(const long double & value)
	: value(static_cast<InternalType>(value * static_cast<long double>(Scale)))
{
}

//
// Getters
//

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixed<Integer, Fraction>::InternalType UFixed<Integer, Fraction>::getInternal(void) const
{
	return this->value;
}

template< unsigned Fraction >
constexpr typename UFixed<0, Fraction>::InternalType UFixed<0, Fraction>::getInternal(void) const
{
	return this->value;
}

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixed<Integer, Fraction>::IntegerType UFixed<Integer, Fraction>::getInteger(void) const
{
	return static_cast<IntegerType>(this->value >> IntegerShift) & IntegerMask;
}

template< unsigned Fraction >
constexpr typename UFixed<0, Fraction>::IntegerType UFixed<0, Fraction>::getInteger(void) const
{
	return 0;
}

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixed<Integer, Fraction>::FractionType UFixed<Integer, Fraction>::getFraction(void) const
{
	return static_cast<FractionType>(this->value >> FractionShift) & FractionMask;
}

template< unsigned Fraction >
constexpr typename UFixed<0, Fraction>::FractionType UFixed<0, Fraction>::getFraction(void) const
{
	return static_cast<FractionType>(this->value) & FractionMask;
}

//
// Cast Operators
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator IntegerType(void) const
{
	return this->getInteger();
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::operator IntegerType(void) const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator float(void) const
{
	return ((this->value & IdentityMask) * (1.0F / Scale));
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::operator float(void) const
{
	return ((this->value & IdentityMask) * (1.0F / Scale));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator double(void) const
{
	return ((this->value & IdentityMask) * (1.0 / Scale));
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::operator double(void) const
{
	return ((this->value & IdentityMask) * (1.0 / Scale));
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction>::operator long double(void) const
{
	return ((this->value & IdentityMask) * (1.0L / Scale));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator long double(void) const
{
	return ((this->value & IdentityMask) * (1.0L / Scale));
}

template< unsigned Integer, unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
constexpr UFixed<Integer, Fraction>::operator UFixed<IntegerOut, FractionOut>(void) const
{
	using OutputType = UFixed<IntegerOut, FractionOut>;
	using OutputInternalType = typename OutputType::InternalType;
	using OutputShiftType = typename OutputType::ShiftType;
	
	using InputType = UFixed<Integer, Fraction>;
	using InputShiftType = typename InputType::ShiftType;
	
	return
	(FractionOut > FractionSize) ?
		OutputType::fromInternal(static_cast<OutputInternalType>(static_cast<OutputShiftType>(this->value) << ((FractionOut > FractionSize) ? (FractionOut - FractionSize) : 0))) :
	(FractionSize > FractionOut) ?
		OutputType::fromInternal(static_cast<OutputInternalType>(static_cast<InputShiftType>(this->value) >> ((FractionSize > FractionOut) ? (FractionSize - FractionOut) : 0))) :
		OutputType::fromInternal(this->value);
}

template< unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
constexpr UFixed<0, Fraction>::operator UFixed<IntegerOut, FractionOut>(void) const
{
	using OutputType = UFixed<IntegerOut, FractionOut>;
	using OutputInternalType = typename OutputType::InternalType;
	using OutputShiftType = typename OutputType::ShiftType;
	
	using InputType = UFixed<0, Fraction>;
	using InputShiftType = typename InputType::ShiftType;
	
	return
	(FractionOut > FractionSize) ?
		OutputType::fromInternal(static_cast<OutputInternalType>(static_cast<OutputShiftType>(this->value) << ((FractionOut > FractionSize) ? (FractionOut - FractionSize) : 0))) :
	(FractionSize > FractionOut) ?
		OutputType::fromInternal(static_cast<OutputInternalType>(static_cast<InputShiftType>(this->value) >> ((FractionSize > FractionOut) ? (FractionSize - FractionOut) : 0))) :
		OutputType::fromInternal(this->value);
}

//
// Static Functions
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> UFixed<Integer, Fraction>::fromInternal(const typename UFixed<Integer, Fraction>::InternalType & value)
{
	return UFixed<Integer, Fraction>(RawType(value));
}

template< unsigned Fraction >
constexpr UFixed<0, Fraction> UFixed<0, Fraction>::fromInternal(const typename UFixed<0, Fraction>::InternalType & value)
{
	return UFixed<0, Fraction>(RawType(value));
}

//
// Member Operators
//

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator ++(void)
{
	this->value += (1 << FractionSize);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator --(void)
{
	this->value -= (1 << FractionSize);
	return *this;
}

//
// Compound Assignment Operators
//

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator +=(const UFixed<Integer, Fraction> & other)
{
	this->value += other.value;
	return *this;
}

template< unsigned Fraction >
UFixed<0, Fraction> & UFixed<0, Fraction>::operator +=(const UFixed<0, Fraction> & other)
{
	this->value += other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator -=(const UFixed<Integer, Fraction> & other)
{
	this->value -= other.value;
	return *this;
}

template< unsigned Fraction >
UFixed<0, Fraction> & UFixed<0, Fraction>::operator -=(const UFixed<0, Fraction> & other)
{
	this->value -= other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator *=(const UFixed<Integer, Fraction> & other)
{
	using InternalType = typename UFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename UFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) * static_cast<PrecisionType>(other.value)) >> FractionSize;
	this->value = static_cast<InternalType>(temp);
	return *this;
}

template< unsigned Fraction >
UFixed<0, Fraction> & UFixed<0, Fraction>::operator *=(const UFixed<0, Fraction> & other)
{
	using InternalType = typename UFixed<0, Fraction>::InternalType;
	using PrecisionType = typename UFixed<0, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) * static_cast<PrecisionType>(other.value)) >> FractionSize;
	this->value = static_cast<InternalType>(temp);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator /=(const UFixed<Integer, Fraction> & other)
{
	using InternalType = typename UFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename UFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) << FractionSize) / static_cast<PrecisionType>(other.value);
	this->value = static_cast<InternalType>(temp);
	return *this;
}

template< unsigned Fraction >
UFixed<0, Fraction> & UFixed<0, Fraction>::operator /=(const UFixed<0, Fraction> & other)
{
	using InternalType = typename UFixed<0, Fraction>::InternalType;
	using PrecisionType = typename UFixed<0, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) << FractionSize) / static_cast<PrecisionType>(other.value);
	this->value = static_cast<InternalType>(temp);
	return *this;
}

FIXED_POINTS_END_NAMESPACE