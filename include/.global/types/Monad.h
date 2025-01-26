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
		@brief	Template of regular monad.

		This template implements the canonical implementation of monad idiom.
		One can't just retrieve the value from monad. Instead, only the function can be used to get access to the carried value.
		The function used to retrieve the value, once being called, can use or consume the value, depending on its signature.

		Additionally, the value carried by monad can be transformed or clarified. Or even forced to be set in case the monad is still empty.

		@tparam	TValue	Type of value to be carried by monad.
	*/
	template< typename TValue >
	class Monad final
	{
	// Public inner types.
	public:
		// Type of value to be carried.
		using Value = TValue;

	// Friendship interface.
	public:
		friend inline void swap( Monad& left, Monad& right ) { left.Swap( right ); };

	// Public lifetime management.
	public:
		inline Monad()							= default;
		inline Monad( const Monad& other )		: m_value{ other.m_value } {};
		inline Monad( Monad&& other ) noexcept	: m_value{ std::move( other.m_value ) } {};
		inline ~Monad() noexcept				= default;

		explicit inline Monad( Value value )	: m_value{ std::forward<Internal::MonadForwardingValue<Value>>( value ) } {};


		inline Monad<TValue>& operator = ( const Monad<TValue>& other )		{ return Black::CopyAndSwap( *this, other ); };
		inline Monad<TValue>& operator = ( Monad<TValue>&& other ) noexcept	{ return Black::CopyAndSwap( *this, std::move( other ) ); };

		inline Monad<TValue>& operator = ( Value value ) noexcept			{ return Black::CopyAndSwap( *this, std::move( value ) ); };

	// Public interface.
	public:
		// Clear the state of monad. No value considered stored after call.
		inline void Clear();

		// Perform the swap of states with other one.
		inline void Swap( Monad<TValue>& other );

		/**
			@brief	Clarify the stored value.

			The result of call depends on fact this monad stores the value.
			In case of empty monad, the `value` will be used to construct the result.
			In case of stored value, it will be used to construct the result and the `value` will be ignored.

			@param	value	The value to be used in case the monad is empty.
			@return			The value returned is another monad, that definitely carried the value.
		*/
		[[ nodiscard ]]
		inline Monad<TValue> OrUse( const Value& value ) const &;

		/**
			@brief	Clarify the stored value.

			The result of call depends on fact this monad stores the value.
			In case of empty monad, the `value` will be used to construct the result.
			In case of stored value, it will be used to construct the result and the `value` will be ignored.

			@param	value	The value to be used in case the monad is empty.
			@return			The value returned is another monad, that definitely carried the value.
		*/
		[[ nodiscard ]]
		inline Monad<TValue> OrUse( Value value ) &&;

		/**
			@brief	Transform the value, if carried.

			Allows to change the type of carried value. It often suitable when costly conversion should be performed on indeterminate value.
			The `function` will not be invoked in case of empty monad.

			@param	function	The function to transform the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another monad, which carries the transformed value.
			@retval	{}			Empty monad will be returned in case of empty monad being transformed.
		*/
		template< typename TFunction >
		[[ nodiscard ]]
		inline auto Transform( TFunction&& transformer ) const & -> Monad<std::invoke_result_t<TFunction, Value>>;

		/**
			@brief	Transform the value, if carried.

			Allows to change the type of carried value. It often suitable when costly conversion should be performed on indeterminate value.
			The `function` will not be invoked in case of empty monad.

			@param	function	The function to transform the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another monad, which carries the transformed value.
			@retval	{}			Empty monad will be returned in case of empty monad being transformed.
		*/
		template< typename TFunction >
		[[ nodiscard ]]
		inline auto Transform( TFunction&& transformer ) && -> Monad<std::invoke_result_t<TFunction, Value&&>>;

		/**
			@brief	Use carried value to feed the given function.

			In fact, this one allows to consume the carried value somehow.
			The `function` will not be invoked in case of empty monad. So the result of function also covered by monad, which now may be ignored.

			@param	consumer	The function to consume the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another monad, which carries the result of consumption.
			@retval	{}			Empty monad will be returned in case of empty monad being transformed.
		*/
		template< typename TFunction >
		[[ maybe_unused ]]
		inline auto AndThen( TFunction&& consumer ) const & -> Internal::MonadOrVoid<TFunction, Value>;

		/**
			@brief	Use carried value to feed the given function.

			In fact, this one allows to consume the carried value somehow.
			The `function` will not be invoked in case of empty monad. So the result of function also covered by monad, which now may be ignored.

			@param	consumer	The function to consume the carried value.
			@tparam	TFunction	Type of transformation function.
			@return				The value returned is another monad, which carries the result of consumption.
			@retval	{}			Empty monad will be returned in case of empty monad being transformed.
		*/
		template< typename TFunction >
		[[ maybe_unused ]]
		inline auto AndThen( TFunction&& consumer ) && -> Internal::MonadOrVoid<TFunction, Value&&>;

	// Private state.
	private:
		Internal::MonadValue<Value> m_value; // Storage for carried value.
	};
}
}
}
}
