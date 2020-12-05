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
		@brief	Scoped smart pointer implementation.
		The 'scoped' means the smart pointer will be utilized only in those scope, where it was constructed.
		The scoped pointer can't be transferred between scopes. It can't be copied or even moved between instances.
		Moreover, the `std::swap` function is prohibited for scoped pointers.
		However, all that restrictions guaranties the controlled memory will be freed once the scope finished.

		The scoped pointer is designed to be generally used as local variable. It does not designed to be used in dynamic memory.
		The scoped pointer may be constructed using only the value to be stored, or the pointer also may consume the optional deleter to call it
		in order to free the stored memory.

		@tparam	TStoredValue	Type of pointer to be stored in.
		@tparam	TDeleter		Type of deleter to be used in order to free stored memory.
	*/
	template< typename TStoredValue, typename TDeleter = std::default_delete<TStoredValue> >
	class ScopedPointer final : private Black::NonTransferable
	{
	// Construction and assignment.
	public:
		static_assert( !std::is_reference_v<TStoredValue>, "Invalid type of scoped pointer, references are not allowed." );

		ScopedPointer()	= delete;

		inline explicit ScopedPointer( TStoredValue* value ) : m_value{ value } {};

		template< typename TCustomDeleter >
		inline explicit ScopedPointer( TStoredValue* value, TCustomDeleter&& deleter ) : m_value{ value, std::forward<TCustomDeleter>( deleter ) } {};

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
		inline const bool IsEmpty() const				{ return m_value == nullptr; };


		inline TStoredValue& operator * () const		{ EXPECTS( !IsEmpty() ); return *GetValue(); };
		inline TStoredValue* operator -> () const		{ EXPECTS( !IsEmpty() ); return GetValue(); };

		inline explicit operator const bool () const	{ return !IsEmpty(); };
		inline const bool operator ! () const			{ return IsEmpty(); };

	// Private state.
	private:
		std::unique_ptr<TStoredValue, TDeleter>	m_value;	// Stored value.
	};
}
}
}
}
