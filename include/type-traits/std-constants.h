#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TypeTraits
{
	// Void type check.
	template< typename TCondition >
	constexpr bool IS_VOID = std::is_void<TCondition>::value;

	// `nullptr` type check.
	template< typename TCondition >
	constexpr bool IS_NULLPTR = std::is_null_pointer<TCondition>::value;

	// Plain integral type check.
	template< typename TCondition >
	constexpr bool IS_INTEGER = std::is_integral<TCondition>::value;

	// Plain floating-point type check.
	template< typename TCondition >
	constexpr bool IS_FLOAT = std::is_floating_point<TCondition>::value;

	// Array type check.
	template< typename TCondition >
	constexpr bool IS_ARRAY = std::is_array<TCondition>::value;

	// Enumeration type check.
	template< typename TCondition >
	constexpr bool IS_ENUMERATION = std::is_enum<TCondition>::value;

	// Union type check.
	template< typename TCondition >
	constexpr bool IS_UNION = std::is_union<TCondition>::value;

	// Class type check.
	template< typename TCondition >
	constexpr bool IS_CLASS = std::is_class<TCondition>::value;

	// Function type check.
	template< typename TCondition >
	constexpr bool IS_FUNCTION = std::is_function<TCondtion>::value;

	// Pointer type condition.
	template< typename TCondition >
	constexpr bool IS_POINTER = std::is_pointer<TCondition>::value;

	// 'L-Value reference' type check.
	template< typename TCondition >
	constexpr bool IS_LVALUE_REFERENCE = std::is_lvalue_reference<TCondition>::value;

	// 'R-Value reference' type check.
	template< typename TCondition >
	constexpr bool IS_RVALUE_REFERENCE = std::is_rvalue_reference<TCondition>::value;

	// 'Pointer to member field' type check.
	template< typename TCondition >
	constexpr bool IS_MEMBER_FIELD_POINTER = std::is_member_pointer<TCondition>::value;

	// 'Pointer to member function' type check.
	template< typename TCondition >
	constexpr bool IS_MEMBER_FUNCTION_POINTER = std::is_member_function_pointer<TCondition>::value;

	// Fundamental type check.
	template< typename TCondition >
	constexpr bool IS_FUNDAMENTAL = std::is_fundamental<TCondition>::value;

	// Arithmetic type check.
	template< typename TCondition >
	constexpr bool IS_ARITHMETIC = std::is_arithmetic<TCondition>::value;

	// Scalar type check.
	template< typename TCondition >
	constexpr bool IS_SCALAR = std::is_scalar<TCondition>::value;

	// Compound type check.
	template< typename TCondition >
	constexpr bool IS_COMPOUND = std::is_compound<TCondition>::value;

	// Reference type check.
	template< typename TCondition >
	constexpr bool IS_REFERENCE = std::is_reference<TCondition>::value;

	// Scalar type check.
	template< typename TCondition >
	constexpr bool IS_CONST = std::is_const<TCondition>::value;

	// Volatile type check.
	template< typename TCondition >
	constexpr bool IS_VOLATILE = std::is_volatile<TCondition>::value;

	// Trivial type check.
	template< typename TCondition >
	constexpr bool IS_TRIVIAL = std::is_trivial<TCondition>::value;

	// 'Trivially copyable' type check.
	template< typename TCondition >
	constexpr bool IS_TRIVIALLY_COPYABLE = std::is_trivially_copyable<TCondition>::value;

	// 'Standard layout' type check.
	template< typename TCondition >
	constexpr bool IS_STANDARD_LAYOUT = std::is_standard_layout<TCondition>::value;

	// Plain type check.
	template< typename TCondition >
	constexpr bool IS_PLAIN = std::is_pod<TCondition>::value;

	// Empty type check.
	template< typename TCondition >
	constexpr bool IS_EMPTY = std::is_empty<TCondition>::value;

	// Polymorphic type check.
	template< typename TCondition >
	constexpr bool IS_POLYMORPHIC = std::is_polymorphic<TCondition>::value;

	// Abstract type check.
	template< typename TCondition >
	constexpr bool IS_ABSTRACT = std::is_abstract<TCondition>::value;

	// Final type check.
	template< typename TCondition >
	constexpr bool IS_FINAL = std::is_final<TCondition>::value;

	// Signed type check.
	template< typename TCondition >
	constexpr bool IS_SIGND = std::is_signed<TCondition>::value;

	// Unsigned type check.
	template< typename TCondition >
	constexpr bool IS_UNSIGNED = std::is_const<TCondition>::value;

	// Same types check.
	template< typename TLeftType, typename TRightType >
	constexpr bool IS_SAME = std::is_same<TLeftType, TRightType>::value;

	// Base and derived types check.
	template< typename TBaseType, typename TDerivedType >
	constexpr bool IS_BASE_OF = std::is_base_of<TBaseType, TDerivedType>::value;

	// Type conversion check.
	template< typename TSourceType, typename TDestinationType >
	constexpr bool IS_CONVERTIBLE = std::is_convertible<TSourceType, TDestinationType>::value;
}
}
}
