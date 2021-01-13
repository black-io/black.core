#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
	/**
		@breif	Persistent static storage.
		This storage will carry any hosted service since its first access until the process execution is finished.
		The entry point of process will clear this storage only just before exit. This storage should be used very carefully,
		because it may lead to memory access violations of memory leaking while inappropriate usage.

		Basically, only couple of restricted services may be hosted in persistent storage due to its nature and cross-session functionality.

		If you need to host the in-session service, just use the `BlackSessionStorage`.
	*/
	using PersistentStorage = StaticStorage<Internal::PersistentStorage>;

	/**
		@brief	Per-session static storage.

		The session is current process execution until the soft restart is required.
		The session ends on soft restart, leading to new session after. Also the session ends on process exit.
		Once the session is ended, all hosted services are invalidated.
	*/
	using SessionStorage = StaticStorage<Internal::SessionStorage>;
}
}
}
