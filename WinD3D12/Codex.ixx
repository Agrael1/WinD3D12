module;
#include <unordered_map>
#include <string>
#include <memory>
export module Codex;
export import Bindable;

export namespace ver
{
	//Codex is a container for super heavy items, like shaders (compiled esp), textures and other
	class Codex
	{
		//TODO: Coroutine buffer trimming
	public:
		template<typename T, typename ...Params> /*requires is_bindable<T>*/
			[[nodiscard]] static std::shared_ptr<T> Resolve(const Graphics& gfx, Params&& ...p)noexcept
			{
				return Get()._Resolve<T>(gfx, std::forward<Params>(p)...);
			}
	private:
		template<typename T, typename ...Params>
		std::shared_ptr<T> _Resolve(const Graphics& gfx, Params&& ...p)noexcept
		{
			const auto key = T::GenerateUID(std::forward<Params>(p)...);
			const auto i = binds.find(key);
			if (i == binds.end())
			{
				auto bind = std::make_shared<T>(gfx, std::forward<Params>(p)...);
				binds[key] = bind;
				return bind;
			}
			else
			{
				return std::static_pointer_cast<T>(i->second);
			}
		}
		static Codex& Get()
		{
			static Codex codex;
			return codex;
		}
	private:
		std::unordered_map<std::string, std::shared_ptr<Bindable>> binds;
	};
}