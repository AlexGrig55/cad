#pragma once


namespace cad
{
	class BaseCadObject
	{
		size_t					_handle;
		const BaseCadObject*	_parent;

	public:
		BaseCadObject(): _handle(0), _parent(nullptr) {}

		virtual ~BaseCadObject() {}

		constexpr auto handle()const noexcept			{ return _handle; }
		constexpr const auto parent()const noexcept		{ return _parent; }
	};
}
