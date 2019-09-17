#pragma once

struct Vector3f {
	float x, y, z;

	Vector3f() {
		x = y = z = 0;
	}
	Vector3f(float X, float Y, float Z) {
		x = X;
		y = Y;
		z = Z;
	}
};

struct Vector4f {
	float x, y, z, w;

	Vector4f() {
		x = y = z = w = 0;
	}
	Vector3f(float X, float Y, float Z, float W) {
		x = X;
		y = Y;
		z = Z;
		w = W;
	}
}