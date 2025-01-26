#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
namespace Internal
{
	// Template of monad value.
	template< typename TValue >
	class MonadValue final
	{
	// Friendship interface.
	public:
		friend inline void swap( MonadValue& left, MonadValue& right ) { left.Swap( right ); };

	// Public lifetime management.
	public:
		inline MonadValue() noexcept = default;
		inline MonadValue( const MonadValue& other ) noexcept;
		inline MonadValue( MonadValue&& other ) noexcept;
		inline ~MonadValue() noexcept;

		explicit inline MonadValue( TValue value ) noexcept;


		inline MonadValue& operator = ( const MonadValue& other ) noexcept	{ return Black::CopyAndSwap( *this, other ); };
		inline MonadValue& operator = ( MonadValue&& other ) noexcept		{ return Black::CopyAndSwap( *this, std::move( other ) ); };

		inline MonadValue& operator = ( TValue value ) noexcept				{ return Black::CopyAndSwap( *this, std::move( value ) ); };

	// Public interface.
	public:
		// Clear the value. No value stored after clearing.
		inline void Clear();

		// Perform the swap of states with other one.
		inline void Swap( MonadValue& other );

		// Get the reference to stored value.
		inline TValue& GetValue() &;

		// Get the reference to stored value.
		inline const TValue& GetValue() const &;

		// Get the stored value. Becomes empty after this call.
		inline TValue GetValue() &&;

		// Get the reference to stored value or default one if no value stored.
		inline TValue& GetValue( TValue& default_value ) &;

		// Get the reference to stored value or default one if no value stored.
		inline const TValue& GetValue( const TValue& default_value ) const &;

		// Get the stored value or default one if no value stored. Becomes empty after this call.
		inline TValue GetValue( TValue&& default_value ) &&;

		// Whether the value is empty.
		inline const bool IsEmpty() const { return m_storage == nullptr; };

		// Whether the value is stored.
		inline const bool HasValue() const { return m_storage != nullptr; };

	// Private inner types.
	private:
		// Storage for carried value. Can store even references.
		struct ValueStorage final
		{
			TValue value;
		};

		// Raw memory buffer for value storage.
		using ValueBuffer = std::byte[ sizeof( ValueStorage ) ];

		// Within movable context this type instructs the monad to move or pass the value out.
		using ForwardingValue = MonadForwardingValue<TValue>;

	// Private interface.
	private:
		// Allocate the storage for given new value.
		void AllocateStorage( TValue value );

		// Dispose the storage. Any stored value will be destroyed as well.
		void DisposeStorage();

	// Private state.
	private:
		alignas( ValueStorage ) ValueBuffer	m_buffer;				// Buffer for value storage.
		ValueStorage*						m_storage = nullptr;	// Pointer to allocated value storage.
	};
}
}
}
}
}
