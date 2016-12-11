#pragma once

namespace ftec {

	template <typename T>
	struct CollisionResult {
		bool collided;
		T result;

		CollisionResult() : collided(false)
		{ }
		CollisionResult(bool b) : collided(b)
		{ }
		CollisionResult(T t) : collided(true), result(t) { }
		CollisionResult(T t, bool collided) : collided(collided), result(t) { }

		T* operator->() {
			return &result;
		}
		operator bool() { return collided; }
		bool operator!() { return !collided; }
		T& operator*() { return result; }
	};
}