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
constexpr SFixed<Integer, Fraction>::SFixed(const RawType & value)
	: value(static_cast<InternalType>(value))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(void)
	: value(0)
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const IntegerType & integer, const FractionType & fraction)
	: value((static_cast<InternalType>(integer) << FractionSize) | fraction)
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const unsigned char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const signed char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const unsigned short int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned short int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const signed short int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed short int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const unsigned int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const signed int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const unsigned long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const signed long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const unsigned long long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned long long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const signed long long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed long long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const double & value)
	: value(static_cast<InternalType>(value * static_cast<double>(Scale)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const float & value)
	: value(static_cast<InternalType>(value * static_cast<float>(Scale)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const long double & value)
	: value(static_cast<InternalType>(value * static_cast<long double>(Scale)))
{
}

//
// Getters
//

template< unsigned Integer, unsigned Fraction >
constexpr typename SFixed<Integer, Fraction>::InternalType SFixed<Integer, Fraction>::getInternal(void) const
{
	return this->value;
}

template< unsigned Integer, unsigned Fraction >
constexpr typename SFixed<Integer, Fraction>::IntegerType SFixed<Integer, Fraction>::getInteger(void) const
{
	return (static_cast<IntegerType>(this->value >> IntegerShift) & IntegerMask) | ((this->value < 0) ? ~IntegerMask : 0);
}

template< unsigned Integer, unsigned Fraction >
constexpr typename SFixed<Integer, Fraction>::FractionType SFixed<Integer, Fraction>::getFraction(void) const
{
	return static_cast<FractionType>(this->value >> FractionShift) & FractionMask;
}

//
// Cast Operators
//

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::operator IntegerType(void) const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::operator float(void) const
{
	return (1.0F / Scale) *
	static_cast<InternalType>
	((this->value & IdentityMask) |
	((this->value < 0) ? ~IdentityMask : 0));
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::operator double(void) const
{
	return (1.0 / Scale) *
	static_cast<InternalType>
	((this->value & IdentityMask) |
	((this->value < 0) ? ~IdentityMask : 0));
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::operator long double(void) const
{
	return (1.0L / Scale) *
	static_cast<InternalType>
	((this->value & IdentityMask) |
	((this->value < 0) ? ~IdentityMask : 0));
}

template< unsigned Integer, unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
constexpr SFixed<Integer, Fraction>::operator SFixed<IntegerOut, FractionOut>(void) const
{	
	using OutputType = SFixed<IntegerOut, FractionOut>;
	using OutputInternalType = typename OutputType::InternalType;
	using OutputShiftType = typename OutputType::ShiftType;
	
	using InputType = SFixed<Integer, Fraction>;
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
constexpr SFixed<Integer, Fraction> SFixed<Integer, Fraction>::fromInternal(const typename SFixed<Integer, Fraction>::InternalType & value)
{
	return SFixed<Integer, Fraction>(RawType(value));
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> SFixed<Integer, Fraction>::operator -(void) const
{
	return SFixed<Integer, Fraction>::fromInternal(-this->value);
}

//
// Member Operators
//

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> & SFixed<Integer, Fraction>::operator ++(void)
{
	this->value += (1 << FractionSize);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> & SFixed<Integer, Fraction>::operator --(void)
{
	this->value -= (1 << FractionSize);
	return *this;
}

//
// Compound Assignment Operators
//

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> & SFixed<Integer, Fraction>::operator +=(const SFixed<Integer, Fraction> & other)
{
	this->value += other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> & SFixed<Integer, Fraction>::operator -=(const SFixed<Integer, Fraction> & other)
{
	this->value -= other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> & SFixed<Integer, Fraction>::operator *=(const SFixed<Integer, Fraction> & other)
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename SFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) * static_cast<PrecisionType>(other.value)) >> Fraction;
	this->value = static_cast<InternalType>(temp);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> & SFixed<Integer, Fraction>::operator /=(const SFixed<Integer, Fraction> & other)
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename SFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) << Fraction) / static_cast<PrecisionType>(other.value);
	this->value = static_cast<InternalType>(temp);
	return *this;
}

FIXED_POINTS_END_NAMESPACE