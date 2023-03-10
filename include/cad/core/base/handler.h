#pragma once
#include "./cad_object.hpp"

namespace cad
{
	class Database;

	namespace base {
		class CAD_API Handler :public ICadObject
		{
			friend class Database;

		private:
			size_t _handle;
#if !NDEBUG
			types::String _hexHandle;
#endif

		protected:
			constexpr void setHandle(size_t val) noexcept {	_handle = val;
#if !NDEBUG
				_hexHandle = types::String::fromIntegral(val, 16);
#endif
			}

			static size_t getAvailableHandle(Database* db)noexcept;
			static void callAddingToDb(Handler* handler, Database* db)noexcept { handler->addingToDb(db); }

			virtual void addingToDb(Database* db)noexcept;
			virtual void deletingFromDb(Database* db)noexcept {}

		public:
			constexpr Handler()noexcept { setHandle(0); }
			constexpr Handler(const Handler& val)noexcept  { setHandle(0); }
			size_t handle()const noexcept { return _handle; }

			constexpr Handler(Handler&& val)noexcept = default;

			constexpr Handler& operator=(const Handler& other)noexcept { return *this; }
			constexpr Handler& operator=(Handler&& other)noexcept { return *this; }
		};
	}
}
