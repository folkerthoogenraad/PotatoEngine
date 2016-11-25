#pragma once

namespace ftec {

	template <typename T>
	struct collisionresult {
		bool collided;
		T result;

		collisionresult() : collided(false)
		{ }
		collisionresult(bool r) : collided(r)
		{ }
		collisionresult(T t) : collided(true), result(t) { }
		collisionresult(T t, bool collided) : collided(collided), result(t) { }

		T* operator->() {
			return &result;
		}
		operator bool() { return collided; }
		bool operator!() { return !collided; }
		T& operator*() { return result; }
	};
}