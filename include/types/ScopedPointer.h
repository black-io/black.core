#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	// Scoped pointer implementation.
	template< typename TStoredValue, typename TDeleter = std::default_delete<TStoredValue> >
	class ScopedPointer final : private Black::NonTransferable
	{
		static_assert( !Black::IS_REFERENCE<TStoredValue>, "The type stored by scoped pointer have to not be the reference type." );

	// Construction and assignment.
	public:
		inline explicit ScopedPointer( TStoredValue* value ) : m_value{ value } {};

		template< typename TCustomDeleter >
		inline explicit ScopedPointer( TStoredValue* value, TCustomDeleter deleter ) : m_value{ value, std::forward<TCustomDeleter>( deleter ) } {};


		ScopedPointer()	= delete;

	// Public interface.
	public:
		// Reset the pointer.
		inline void Reset()								{ m_value.reset(); };

		// Change the stored pointer.
		inline void Reset( TStoredValue* new_value )	{ m_value.reset( new_value ); };

		// Release the pointer from scope. Released memory will no longer controlled by scoped pointer.
		inline TStoredValue* Release()					{ return m_value.release(); };


		// Get the stored value.
		inline TStoredValue* GetValue() const			{ return m_value.get(); };

		// Get the deleter instance.
		inline TDeleter& GetDeleter()					{ return m_value.get_deleter(); };

		// Get the deleter instance.
		inline const TDeleter& GetDeleter() const		{ return m_value.get_deleter(); };

		// Check that the value stored is `nullptr`.
		inline const bool IsNull() const				{ return m_value == nullptr; };


		inline TStoredValue& operator * () const		{ EXPECTS( !IsNull() ); return *GetValue(); };
		inline TStoredValue* operator -> () const		{ EXPECTS( !IsNull() ); return GetValue(); };

		inline explicit operator const bool () const	{ return !IsNull(); };
		inline const bool operator ! () const			{ return IsNull(); };

	// Private state.
	private:
		std::unique_ptr<TStoredValue, TDeleter>	m_value;	// Stored value.
	};
}
}
}


namespace std
{
	// Prohibit the swapping of scoped pointers.
	template< typename TLeftValue, typename TLeftDeleter, typename TRightValue, typename TRightDeleter >
	void swap( Black::ScopedPointer<TLeftValue, TLeftDeleter>& left, Black::ScopedPointer<TRightValue, TRightDeleter>& right );
}
