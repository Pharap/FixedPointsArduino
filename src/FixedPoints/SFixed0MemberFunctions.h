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

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::SFixed(const RawType & value)
	: value(static_cast<InternalType>(value))
{
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::SFixed(void)
	: value(0)
{
}

// Here the comma operator is used to circumvent an unused parameter warning
template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::SFixed(const IntegerType & integer, const FractionType & fraction)
	: value((integer, fraction))
{
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::SFixed(const double & value)
	: value(static_cast<InternalType>(value * static_cast<double>(Scale)))
{
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::SFixed(const float & value)
	: value(static_cast<InternalType>(value * static_cast<float>(Scale)))
{
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::SFixed(const long double & value)
	: value(static_cast<InternalType>(value * static_cast<long double>(Scale)))
{
}

//
// Getters
//

template<  unsigned Fraction >
constexpr typename SFixed<0, Fraction>::InternalType SFixed<0, Fraction>::getInternal(void) const
{
	return this->value;
}

template<  unsigned Fraction >
constexpr typename SFixed<0, Fraction>::IntegerType SFixed<0, Fraction>::getInteger(void) const
{
	static_assert(false, "UNDEFINED BEHAVIOUR");
	//return (static_cast<IntegerType>(this->value >> IntegerShift) & IntegerMask) | ((this->value < 0) ? ~IntegerMask : 0);
}

template<  unsigned Fraction >
constexpr typename SFixed<0, Fraction>::FractionType SFixed<0, Fraction>::getFraction(void) const
{
	return static_cast<FractionType>(this->value >> FractionShift) & FractionMask;
}

//
// Cast Operators
//

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::operator IntegerType(void) const
{
	return this->getInteger();
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::operator float(void) const
{
	return (1.0F / Scale) *
	static_cast<InternalType>
	((this->value & IdentityMask) |
	((this->value < 0) ? ~IdentityMask : 0));
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::operator double(void) const
{
	return (1.0 / Scale) *
	static_cast<InternalType>
	((this->value & IdentityMask) |
	((this->value < 0) ? ~IdentityMask : 0));
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction>::operator long double(void) const
{
	return (1.0L / Scale) *
	static_cast<InternalType>
	((this->value & IdentityMask) |
	((this->value < 0) ? ~IdentityMask : 0));
}

template<  unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
constexpr SFixed<0, Fraction>::operator SFixed<IntegerOut, FractionOut>(void) const
{	
	using OutputType = SFixed<IntegerOut, FractionOut>;
	using OutputInternalType = typename OutputType::InternalType;
	using OutputShiftType = typename OutputType::ShiftType;
	
	using InputType = SFixed<0, Fraction>;
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

template<  unsigned Fraction >
constexpr SFixed<0, Fraction> SFixed<0, Fraction>::fromInternal(const typename SFixed<0, Fraction>::InternalType & value)
{
	return SFixed<0, Fraction>(RawType(value));
}

template<  unsigned Fraction >
constexpr SFixed<0, Fraction> SFixed<0, Fraction>::operator -(void) const
{
	return SFixed<0, Fraction>::fromInternal(-this->value);
}

//
// Compound Assignment Operators
//

template<  unsigned Fraction >
SFixed<0, Fraction> & SFixed<0, Fraction>::operator +=(const SFixed<0, Fraction> & other)
{
	this->value += other.value;
	return *this;
}

template<  unsigned Fraction >
SFixed<0, Fraction> & SFixed<0, Fraction>::operator -=(const SFixed<0, Fraction> & other)
{
	this->value -= other.value;
	return *this;
}

template<  unsigned Fraction >
SFixed<0, Fraction> & SFixed<0, Fraction>::operator *=(const SFixed<0, Fraction> & other)
{
	using InternalType = typename SFixed<0, Fraction>::InternalType;
	using PrecisionType = typename SFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) * static_cast<PrecisionType>(other.value)) >> Fraction;
	this->value = static_cast<InternalType>(temp);
	return *this;
}

template<  unsigned Fraction >
SFixed<0, Fraction> & SFixed<0, Fraction>::operator /=(const SFixed<0, Fraction> & other)
{
	using InternalType = typename SFixed<0, Fraction>::InternalType;
	using PrecisionType = typename SFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) << Fraction) / static_cast<PrecisionType>(other.value);
	this->value = static_cast<InternalType>(temp);
	return *this;
}

FIXED_POINTS_END_NAMESPACE