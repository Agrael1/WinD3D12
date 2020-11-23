#pragma once
#include <coroutine>
#include <ppltasks.h>

template<typename T>
class Future;

template<typename T>
struct Promise
{
	Promise() : val(), done(false) {}
	std::suspend_never initial_suspend() { return {}; }
	std::suspend_always final_suspend()noexcept {
		this->done = true;
		return {};
	}
	Future<T> get_return_object()
	{
		return Future<T>{ Handle<T>::from_promise(*this) };
	}
	void unhandled_exception() { abort(); }
	void return_value(T xval) {
		this->val = std::move(xval);
	}

	T val;
	bool done;
};

template<typename T>
using Handle = std::coroutine_handle<Promise<T>>;

template<typename T>
class [[nodiscard]] Future
{
public:
	explicit Future(Handle<T> handle)
		: m_handle(handle)
	{}
	~Future() {
		if (m_handle) {
			m_handle.destroy();
		}
	}
	using promise_type = Promise<T>;
	T operator()()
	{
		if (m_handle && m_handle.promise().done) {
			return m_handle.promise().val;
		}
		else {
			return {};
		}
	}

private:
	Handle<T> m_handle;
};