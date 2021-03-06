#pragma once
#include "../Math.h"
#include <GLFW\glfw3.h>
#include "../../DllExport.h"

namespace Pressure {

	struct PRESSURE_API Matrix4f {

		/* COMPONENTS */
		// Formatted val[row + column * 4]
		float val[4 * 4];

		/* CONSTRUCTORS */
		Matrix4f();
		Matrix4f(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3);

		/* IDENTITY */
		Matrix4f& identity();

		/* GETTERS */
		const float* getArray();
		float get(int col, int row) const;
		float get(int element) const;


		/* SETTERS */
		Matrix4f& set(int col, int row, float value);
		Matrix4f& set(int element, float value);
		Matrix4f& set(const Matrix4f& m);
		Matrix4f& set(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3);
		Matrix4f& setColumn(int col, const Vector4f& v);

		/* ADDITION */
		Matrix4f& add(const Matrix4f& m);
		Matrix4f& add(const Matrix4f& m, Matrix4f& dest) const;

		/* MULTIPLICATION */
		Matrix4f& mul(const Matrix4f& m);
		Matrix4f& mul(const Matrix4f& m, Matrix4f& dest) const;

		/* MATRIX SPECIFIC FUNCTIONS */
		Matrix4f& createTransformationMatrix(const Vector2f& translation, const Vector2f& scale);
		Matrix4f& createTransformationMatrix(const Vector3f& translation, const Vector3f& rotation, const float scale);
		Matrix4f& createProjectionMatrix(GLFWwindow* window);
		Matrix4f& createViewMatrix(Vector3f& position, float pitch, float yaw, float roll);
		Matrix4f& translate(const Vector3f& offset, Matrix4f& dest) const;
		Matrix4f& translate(const Vector3f& offset);
		Vector4f& transform(const Vector4f& v, Vector4f& dest) const;
		Vector4f& transform(const Vector4f& v);
		Matrix4f& rotate(const float angle, const Vector3f& axis, Matrix4f& dest) const;
		Matrix4f& rotate(const float angle, const Vector3f& axis);
		Matrix4f& scale(const Vector3f& scale, Matrix4f& dest) const;
		Matrix4f& scale(const Vector3f& scale);
		Matrix4f& scale(const float xyz, Matrix4f& dest) const;
		Matrix4f& scale(const float xyz);
		Matrix4f& invert();
		Matrix4f& invert(Matrix4f& dest) const;

		/* EQUALITY CHECK */
		bool equals(const Matrix4f& m) const;

		/* OPERATOR OVERLOADING */
		bool operator==(const Matrix4f& other) const;
		bool operator!=(const Matrix4f& other) const;

	};

}
