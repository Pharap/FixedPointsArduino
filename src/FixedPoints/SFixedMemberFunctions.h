FIXED_POINTS_BEGIN_NAMESPACE

//
// Constructors
//

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(void)
	: Base()
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const IntegerType & integer)
	: Base(RawType(static_cast<InternalType>(integer) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction>::SFixed(const IntegerType & integer, const FractionType & fraction)
	: Base(RawType((static_cast<InternalType>(integer) << FractionSize) | fraction))
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
	return (1.0f / Scale) *
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