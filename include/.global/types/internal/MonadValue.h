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
	// Template of Hypothetical value.
	template< typename TValue >
	class HypotheticalValue final
	{
	// Friendship interface.
	public:
		friend inline void swap( HypotheticalValue& left, HypotheticalValue& right ) { left.Swap( right ); };

	// Public lifetime management.
	public:
		inline HypotheticalValue() noexcept = default;
		inline HypotheticalValue( const HypotheticalValue& other ) noexcept;
		inline HypotheticalValue( HypotheticalValue&& other ) noexcept;
		inline ~HypotheticalValue() noexcept;

		explicit inline HypotheticalValue( TValue value ) noexcept;


		inline HypotheticalValue& operator = ( const HypotheticalValue& other ) noexcept	{ return Black::CopyAndSwap( *this, other ); };
		inline HypotheticalValue& operator = ( HypotheticalValue&& other ) noexcept		{ return Black::CopyAndSwap( *this, std::move( other ) ); };

		inline HypotheticalValue& operator = ( TValue value ) noexcept				{ return Black::CopyAndSwap( *this, std::move( value ) ); };

	// Public interface.
	public:
		// Clear the value. No value stored after clearing.
		inline void Clear();

		// Perform the swap of states with other one.
		inline void Swap( HypotheticalValue& other );

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

		// Within movable context this type instructs the Hypothetical to move or pass the value out.
		using ForwardingValue = HypotheticalForwardingValue<TValue>;

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
