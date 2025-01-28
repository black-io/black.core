#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	/**
		@brief	Hypothetical value.

		This template implements the behavior of hypothetical value. It considered hypothetical because of no one can clarify the state of value directly.
		One can't just retrieve the value from Hypothetical. Instead, only the function can be used to get access to the carried value.
		The function used to retrieve the value, once being called, can use or consume the value, depending on its signature.

		Additionally, the value carried by Hypothetical can be transformed or clarified. Or even forced to be set in case the Hypothetical is still empty.

		@tparam	TValue	Type of value to be carried by Hypothetical.
	*/
	template< typename TValue >
	class Hypothetical final
	{
	// Public inner types.
	public:
		// Type of value to be carried.
		using Value = TValue;

	// Friendship interface.
	public:
		friend inline void swap( Hypothetical& left, Hypothetical& right ) { left.Swap( right ); };

	// Public lifetime management.
	public:
		inline Hypothetical()							= default;
		inline Hypothetical( const Hypothetical& other )		: m_value{ other.m_value } {};
		inline Hypothetical( Hypothetical&& other ) noexcept	: m_value{ std::move( other.m_value ) } {};
		inline ~Hypothetical() noexcept				= default;

		explicit inline Hypothetical( Value value )	: m_value{ std::forward<Internal::HypotheticalForwardingValue<Value>>( value ) } {};


		inline Hypothetical<TValue>& operator = ( const Hypothetical<TValue>& other )		{ return Black::CopyAndSwap( *this, other ); };
		inline Hypothetical<TValue>& operator = ( Hypothetical<TValue>&& other ) noexcept	{ return Black::CopyAndSwap( *this, std::move( other ) ); };

		inline Hypothetical<TValue>& operator = ( Value value ) noexcept			{ return Black::CopyAndSwap( *this, std::move( value ) ); };

	// Public interface.
	public:
		// Clear the state of Hypothetical. No value considered stored after call.
		inline void Clear();

		// Perform the swap of states with other one.
		inline void Swap( Hypothetical<TValue>& other );

		/**
			@brief	Clarify the stored value.

			The result of call depends on fact this Hypothetical stores the value.
			In case of empty Hypothetical, the `value` will be used to construct the result.
			In case of stored value, it will be used to construct the result and the `value` will be ignored.

			@param	value	The value to be used in case the Hypothetical is empty.
			@return			The value returned is another Hypothetical, that definitely carried the value.
		*/
		[[ nodiscard ]]
		inline Hypothetical<TValue> OrUse( const Value& value ) const &;

		/**
			@brief	Clarify the stored value.

			The result of call depends on fact this Hypothetical stores the value.
			In case of empty Hypothetical, the `value` will be used to construct the result.
			In case of stored value, it will be used to construct the result and the `value` will be ignored.

			@param	value	The value to be used in case the Hypothetical is empty.
			@return			The value returned is another Hypothetical, that definitely carried the value.
		*/
		[[ nodiscard ]]
		inline Hypothetical<TValue> OrUse( Value value ) &&;

		/**
			@brief	Clarify the stored value.

			The result of call depends on fact this Hypothetical stores the value.
			In case of empty Hypothetical, the value will be retrieved from `getter`.
			In case of stored value, it will be used to construct the result and the `value` will be ignored.

			This overload introduces the optimization, where new value will be constructed only if no value is carried.

			@tparam	TFunction	Type of getter-function.
			@param	getter		The getter-function, that will be used to get the new value to be stored.
			@return				The value returned is another Hypothetical, that definitely carried the value.
		*/
		template< typename TFunction >
		[[ nodiscard ]]
		inline auto OrUse( TFunction&& getter ) const & -> std::enable_if_t<!std::is_same_v<std::decay_t<TValue>, std::decay_t<TFunction>>, Hypothetical<TValue>>;

		/**
			@brief	Clarify the stored value.

			The result of call depends on fact this Hypothetical stores the value.
			In case of empty Hypothetical, the value will be retrieved from `getter`.
			In case of stored value, it will be used to construct the result and the `value` will be ignored.

			This overload introduces the optimization, where new value will be constructed only if no value is carried.

			@tparam	TFunction	Type of getter-function.
			@param	getter		The getter-function, that will be used to get the new value to be stored.
			@return				The value returned is another Hypothetical, that definitely carried the value.
		*/
		template< typename TFunction >
		[[ nodiscard ]]
		inline auto OrUse( TFunction&& getter ) && -> std::enable_if_t<!std::is_same_v<std::decay_t<TValue>, std::decay_t<TFunction>>, Hypothetical<TValue>>;

		/**
			@brief	Transform the value, if carried.

			Allows to change the type of carried value. It often suitable when costly conversion should be performed on indeterminate value.
			The `function` will not be invoked in case of empty Hypothetical.

			@param	function	The function to transform the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another Hypothetical, which carries the transformed value.
			@retval	{}			Empty Hypothetical will be returned in case of empty Hypothetical being transformed.
		*/
		template< typename TFunction >
		[[ nodiscard ]]
		inline auto Transform( TFunction&& transformer ) const & -> Hypothetical<std::invoke_result_t<TFunction, Value>>;

		/**
			@brief	Transform the value, if carried.

			Allows to change the type of carried value. It often suitable when costly conversion should be performed on indeterminate value.
			The `function` will not be invoked in case of empty Hypothetical.

			@param	function	The function to transform the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another Hypothetical, which carries the transformed value.
			@retval	{}			Empty Hypothetical will be returned in case of empty Hypothetical being transformed.
		*/
		template< typename TFunction >
		[[ nodiscard ]]
		inline auto Transform( TFunction&& transformer ) && -> Hypothetical<std::invoke_result_t<TFunction, Value&&>>;

		/**
			@brief	Use carried value to feed the given function.

			In fact, this one allows to consume the carried value somehow.
			The `function` will not be invoked in case of empty Hypothetical. So the result of function also covered by Hypothetical, which now may be ignored.

			@param	consumer	The function to consume the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another Hypothetical, which carries the result of consumption.
			@retval	{}			Empty Hypothetical will be returned in case of empty Hypothetical being transformed.
		*/
		template< typename TFunction >
		[[ maybe_unused ]]
		inline auto AndThen( TFunction&& consumer ) const & -> Internal::HypotheticalOrVoid<TFunction, Value>;

		/**
			@brief	Use carried value to feed the given function.

			In fact, this one allows to consume the carried value somehow.
			The `function` will not be invoked in case of empty Hypothetical. So the result of function also covered by Hypothetical, which now may be ignored.

			@param	consumer	The function to consume the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another Hypothetical, which carries the result of consumption.
			@retval	{}			Empty Hypothetical will be returned in case of empty Hypothetical being transformed.
		*/
		template< typename TFunction >
		[[ maybe_unused ]]
		inline auto AndThen( TFunction&& consumer ) && -> Internal::HypotheticalOrVoid<TFunction, Value&&>;

	// Private state.
	private:
		Internal::HypotheticalValue<Value> m_value; // Storage for carried value.
	};
}
}
}
}
