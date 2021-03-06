#include "Matrix4f.h"
#include <cmath>
#include "../../Constants.h"
#include "../../Services/Properties.h"

namespace Pressure {

	/* CONSTRUCTORS */
	Matrix4f::Matrix4f() {
		identity();
	}

	Matrix4f::Matrix4f(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3) {
		set(col0, col1, col2, col3);
	}

	/* IDENTITY */
	Matrix4f& Matrix4f::identity() {
		// [1 0 0 0]
		// [0 1 0 0]
		// [0 0 1 0]
		// [0 0 0 1]

		// Col0
		val[0 + 0 * 4] = 1.f;
		val[1 + 0 * 4] = 0.f;
		val[2 + 0 * 4] = 0.f;
		val[3 + 0 * 4] = 0.f;

		// Col1
		val[0 + 1 * 4] = 0.f;
		val[1 + 1 * 4] = 1.f;
		val[2 + 1 * 4] = 0.f;
		val[3 + 1 * 4] = 0.f;

		// Col2
		val[0 + 2 * 4] = 0.f;
		val[1 + 2 * 4] = 0.f;
		val[2 + 2 * 4] = 1.f;
		val[3 + 2 * 4] = 0.f;

		// Col3
		val[0 + 3 * 4] = 0.f;
		val[1 + 3 * 4] = 0.f;
		val[2 + 3 * 4] = 0.f;
		val[3 + 3 * 4] = 1.f;

		return *this;
	}

	const float* Matrix4f::getArray() {
		return &val[0];
	}

	/* GETTERS */
	float Matrix4f::get(int col, int row) const {
		if (col < 0 || col > 3 || row < 0 || row > 3)
			return -1;
		return val[row + col * 4];
	}

	float Matrix4f::get(int element) const {
		if (element < 0 || element > 15)
			return -1;
		return val[element];
	}

	/* SETTERS */
	Matrix4f& Matrix4f::set(int col, int row, float value) {
		if (col < 0 || col > 3 || row < 0 || row > 3)
			return *this;
		val[row + col * 4] = value;
		return *this;
	}

	Matrix4f& Matrix4f::set(int element, float value) {
		if (element < 0 || element > 15)
			return *this;
		val[element] = value;
		return *this;
	}

	Matrix4f& Matrix4f::set(const Matrix4f& m) {
		for (int i = 0; i < 4 * 4; i++) {
			set(i, m.get(i));
		} return *this;
	}

	Matrix4f& Matrix4f::set(const Vector4f& col0, const Vector4f& col1, const Vector4f& col2, const Vector4f& col3) {
		// Col0
		val[0 + 0 * 4] = col0.getX();
		val[1 + 0 * 4] = col0.getY();
		val[2 + 0 * 4] = col0.getZ();
		val[3 + 0 * 4] = col0.getW();

		// Col1
		val[0 + 1 * 4] = col1.getX();
		val[1 + 1 * 4] = col1.getY();
		val[2 + 1 * 4] = col1.getZ();
		val[3 + 1 * 4] = col1.getW();

		// Col2
		val[0 + 2 * 4] = col2.getX();
		val[1 + 2 * 4] = col2.getY();
		val[2 + 2 * 4] = col2.getZ();
		val[3 + 2 * 4] = col2.getW();

		// Col3
		val[0 + 3 * 4] = col3.getX();
		val[1 + 3 * 4] = col3.getY();
		val[2 + 3 * 4] = col3.getZ();
		val[3 + 3 * 4] = col3.getW();

		return *this;
	}

	Matrix4f& Matrix4f::setColumn(int col, const Vector4f& v) {
		if (col < 0 || col > 4)
			return *this;
		val[0 + col * 4] = v.getX();
		val[1 + col * 4] = v.getY();
		val[2 + col * 4] = v.getZ();
		val[3 + col * 4] = v.getW();
		return *this;
	}

	/* ADDITION */
	Matrix4f& Matrix4f::add(const Matrix4f& m) {
		for (int i = 0; i < 4 * 4; i++) {
			set(i, (val[i] + m.get(i)));
		} return *this;
	}

	Matrix4f& Matrix4f::add(const Matrix4f& m, Matrix4f& dest) const {
		for (int i = 0; i < 4 * 4; i++) {
			dest.set(i, (val[i] + m.get(i)));
		} return dest;
	}

	/* MULTIPLICATION */
	Matrix4f& Matrix4f::mul(const Matrix4f& m) {
		return mul(m, *this);
	}

	Matrix4f& Matrix4f::mul(const Matrix4f& m, Matrix4f& dest) const {
		float nm00 = get(0, 0) * m.get(0, 0) + get(1, 0) * m.get(0, 1) + get(2, 0) * m.get(0, 2) + get(3, 0) * m.get(0, 3);
		float nm01 = get(0, 1) * m.get(0, 0) + get(1, 1) * m.get(0, 1) + get(2, 1) * m.get(0, 2) + get(3, 1) * m.get(0, 3);
		float nm02 = get(0, 2) * m.get(0, 0) + get(1, 2) * m.get(0, 1) + get(2, 2) * m.get(0, 2) + get(3, 2) * m.get(0, 3);
		float nm03 = get(0, 3) * m.get(0, 0) + get(1, 3) * m.get(0, 1) + get(2, 3) * m.get(0, 2) + get(3, 3) * m.get(0, 3);

		float nm10 = get(0, 0) * m.get(1, 0) + get(1, 0) * m.get(1, 1) + get(2, 0) * m.get(1, 2) + get(3, 0) * m.get(1, 3);
		float nm11 = get(0, 1) * m.get(1, 0) + get(1, 1) * m.get(1, 1) + get(2, 1) * m.get(1, 2) + get(3, 1) * m.get(1, 3);
		float nm12 = get(0, 2) * m.get(1, 0) + get(1, 2) * m.get(1, 1) + get(2, 2) * m.get(1, 2) + get(3, 2) * m.get(1, 3);
		float nm13 = get(0, 3) * m.get(1, 0) + get(1, 3) * m.get(1, 1) + get(2, 3) * m.get(1, 2) + get(3, 3) * m.get(1, 3);

		float nm20 = get(0, 0) * m.get(2, 0) + get(1, 0) * m.get(2, 1) + get(2, 0) * m.get(2, 2) + get(3, 0) * m.get(2, 3);
		float nm21 = get(0, 1) * m.get(2, 0) + get(1, 1) * m.get(2, 1) + get(2, 1) * m.get(2, 2) + get(3, 1) * m.get(2, 3);
		float nm22 = get(0, 2) * m.get(2, 0) + get(1, 2) * m.get(2, 1) + get(2, 2) * m.get(2, 2) + get(3, 2) * m.get(2, 3);
		float nm23 = get(0, 3) * m.get(2, 0) + get(1, 3) * m.get(2, 1) + get(2, 3) * m.get(2, 2) + get(3, 3) * m.get(2, 3);

		float nm30 = get(0, 0) * m.get(3, 0) + get(1, 0) * m.get(3, 1) + get(2, 0) * m.get(3, 2) + get(3, 0) * m.get(3, 3);
		float nm31 = get(0, 1) * m.get(3, 0) + get(1, 1) * m.get(3, 1) + get(2, 1) * m.get(3, 2) + get(3, 1) * m.get(3, 3);
		float nm32 = get(0, 2) * m.get(3, 0) + get(1, 2) * m.get(3, 1) + get(2, 2) * m.get(3, 2) + get(3, 2) * m.get(3, 3);
		float nm33 = get(0, 3) * m.get(3, 0) + get(1, 3) * m.get(3, 1) + get(2, 3) * m.get(3, 2) + get(3, 3) * m.get(3, 3);

		dest.set(0, 0, nm00);
		dest.set(0, 1, nm01);
		dest.set(0, 2, nm02);
		dest.set(0, 3, nm03);

		dest.set(1, 0, nm10);
		dest.set(1, 1, nm11);
		dest.set(1, 2, nm12);
		dest.set(1, 3, nm13);

		dest.set(2, 0, nm20);
		dest.set(2, 1, nm21);
		dest.set(2, 2, nm22);
		dest.set(2, 3, nm23);

		dest.set(3, 0, nm30);
		dest.set(3, 1, nm31);
		dest.set(3, 2, nm32);
		dest.set(3, 3, nm33);
		return dest;
	}

	Matrix4f& Matrix4f::createTransformationMatrix(const Vector2f& translation, const Vector2f& scale) {
		identity();
		translate(Vector3f(translation, 0.f));
		this->scale(Vector3f(scale, 1.f));
		return *this;
	}

	/* MATRIX SPECIFIC FUNCTIONS */
	Matrix4f& Matrix4f::createTransformationMatrix(const Vector3f& translation, const Vector3f& rotation, const float scale) {
		identity();
		translate(translation);
		rotate((float)Math::toRadians(rotation.getX()), Vector3f(1, 0, 0));
		rotate((float)Math::toRadians(rotation.getY()), Vector3f(0, 1, 0));
		rotate((float)Math::toRadians(rotation.getZ()), Vector3f(0, 0, 1));
		this->scale(scale);
		return *this;
	}

	Matrix4f& Matrix4f::createProjectionMatrix(GLFWwindow* window) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		float aspectRatio = (float)width / (float)height;
		float y_scale = 1.f / tanf((float)Math::toRadians(std::stof(Properties::get("fov")) / 2.f));
		float x_scale = y_scale / aspectRatio;
		float frustum_length = PRESSURE_FAR_PLANE - PRESSURE_NEAR_PLANE;

		identity();
		set(0, 0, x_scale);
		set(1, 1, y_scale);
		set(2, 2, -((PRESSURE_FAR_PLANE + PRESSURE_NEAR_PLANE) / frustum_length));
		set(2, 3, -1.f);
		set(3, 2, -((2 * PRESSURE_FAR_PLANE * PRESSURE_NEAR_PLANE) / frustum_length));
		set(3, 3, 0.f);
		return *this;
	}

	Matrix4f& Matrix4f::createViewMatrix(Vector3f& position, float pitch, float yaw, float roll) {
		identity();
		rotate((float)Math::toRadians(pitch), Vector3f(1, 0, 0));
		rotate((float)Math::toRadians(yaw), Vector3f(0, 1, 0));
		rotate((float)Math::toRadians(roll), Vector3f(0, 0, 1));
		Vector3f cameraPos(position);
		Vector3f negativeCameraPos;
		cameraPos.negate(negativeCameraPos);
		translate(negativeCameraPos);
		return *this;
	}

	Matrix4f& Matrix4f::translate(const Vector3f& offset, Matrix4f& dest) const {
		dest.set(3, 0, (get(0, 0) * offset.getX() + get(1, 0) * offset.getY() + get(2, 0) * offset.getZ() + get(3, 0)));
		dest.set(3, 1, (get(0, 1) * offset.getX() + get(1, 1) * offset.getY() + get(2, 1) * offset.getZ() + get(3, 1)));
		dest.set(3, 2, (get(0, 2) * offset.getX() + get(1, 2) * offset.getY() + get(2, 2) * offset.getZ() + get(3, 2)));
		dest.set(3, 3, (get(0, 3) * offset.getX() + get(1, 3) * offset.getY() + get(2, 3) * offset.getZ() + get(3, 3)));
		return dest;
	}

	Matrix4f& Matrix4f::translate(const Vector3f& offset) {
		return translate(offset, *this);
	}

	Vector4f& Matrix4f::transform(const Vector4f& v, Vector4f& dest) const {
		return dest.set(
			get(0, 0) * v.getX() + get(1, 0) * v.getY() + get(2, 0) * v.getZ() + get(3, 0) * v.getW(),
			get(0, 1) * v.getX() + get(1, 1) * v.getY() + get(2, 1) * v.getZ() + get(3, 1) * v.getW(),
			get(0, 2) * v.getX() + get(1, 2) * v.getY() + get(2, 2) * v.getZ() + get(3, 2) * v.getW(),
			get(0, 3) * v.getX() + get(1, 3) * v.getY() + get(2, 3) * v.getZ() + get(3, 3) * v.getW()
		);
	}

	Vector4f& Matrix4f::transform(const Vector4f& v) {
		return transform(v, Vector4f());
	}

	//Matrix4f& Matrix4f::rotate(const float angle, const Vector3f& axis, Matrix4f& dest) const {
	//	dest.identity();
	//	float r = Math::toRadians(angle);
	//	float c = cos(r);
	//	float s = sin(r);
	//	float omc = 1.f - c;

	//	float x = axis.getX();
	//	float y = axis.getY();
	//	float z = axis.getZ();

	//	dest.set(0 + 0 * 4, x * x * omc + c);
	//	dest.set(0 + 1 * 4, y * x * omc + z * s);
	//	dest.set(0 + 2 * 4, x * z * omc - y * s);

	//	dest.set(1 + 0 * 4, x * y * omc - z * s);
	//	dest.set(1 + 1 * 4, y * y * omc + c);
	//	dest.set(1 + 2 * 4, y * z * omc + x * s);

	//	dest.set(2 + 0 * 4, x * z * omc + y * s);
	//	dest.set(2 + 1 * 4, y * z * omc - x * s);
	//	dest.set(2 + 2 * 4, z * z * omc + c);

	//	return dest;
	//}

	Matrix4f& Matrix4f::rotate(const float angle, const Vector3f& axis, Matrix4f& dest) const {
		float x = axis.getX();
		float y = axis.getY();
		float z = axis.getZ();
		float s = std::sinf(angle);
		float c = std::cosf(angle);
		float C = 1.f - c;
		float xx = x * x, xy = x * y, xz = x * z;
		float yy = y * y, yz = y * z;
		float zz = z * z;
		float rm00 = xx * C + c;
		float rm01 = xy * C + z * s;
		float rm02 = xz * C - y * s;
		float rm10 = xy * C - z * s;
		float rm11 = yy * C + c;
		float rm12 = yz * C + x * s;
		float rm20 = xz * C + y * s;
		float rm21 = yz * C - x * s;
		float rm22 = zz * C + c;
		float nm00 = get(0, 0) * rm00 + get(1, 0) * rm01 + get(2, 0) * rm02;
		float nm01 = get(0, 1) * rm00 + get(1, 1) * rm01 + get(2, 1) * rm02;
		float nm02 = get(0, 2) * rm00 + get(1, 2) * rm01 + get(2, 2) * rm02;
		float nm03 = get(0, 3) * rm00 + get(1, 3) * rm01 + get(2, 3) * rm02;
		float nm10 = get(0, 0) * rm10 + get(1, 0) * rm11 + get(2, 0) * rm12;
		float nm11 = get(0, 1) * rm10 + get(1, 1) * rm11 + get(2, 1) * rm12;
		float nm12 = get(0, 2) * rm10 + get(1, 2) * rm11 + get(2, 2) * rm12;
		float nm13 = get(0, 3) * rm10 + get(1, 3) * rm11 + get(2, 3) * rm12;
		dest.set(2, 0, get(0, 0) * rm20 + get(1, 0) * rm21 + get(2, 0) * rm22);
		dest.set(2, 1, get(0, 1) * rm20 + get(1, 1) * rm21 + get(2, 1) * rm22);
		dest.set(2, 2, get(0, 2) * rm20 + get(1, 2) * rm21 + get(2, 2) * rm22);
		dest.set(2, 3, get(0, 3) * rm20 + get(1, 3) * rm21 + get(2, 3) * rm22);
		dest.set(0, 0, nm00);
		dest.set(0, 1, nm01);
		dest.set(0, 2, nm02);
		dest.set(0, 3, nm03);
		dest.set(1, 0, nm10);
		dest.set(1, 1, nm11);
		dest.set(1, 2, nm12);
		dest.set(1, 3, nm13);
		dest.set(3, 0, get(3, 0));
		dest.set(3, 1, get(3, 1));
		dest.set(3, 2, get(3, 2));
		dest.set(3, 3, get(3, 3));
		return dest;
	}

	Matrix4f& Matrix4f::rotate(const float angle, const Vector3f& axis) {
		return rotate(angle, axis, *this);
	}

	Matrix4f & Matrix4f::scale(const Vector3f& scale, Matrix4f& dest) const {
		dest.set(0, 0, get(0, 0) * scale.x);
		dest.set(0, 1, get(0, 1) * scale.x);
		dest.set(0, 2, get(0, 2) * scale.x);
		dest.set(0, 3, get(0, 3) * scale.x);
		dest.set(1, 0, get(1, 0) * scale.y);
		dest.set(1, 1, get(1, 1) * scale.y);
		dest.set(1, 2, get(1, 2) * scale.y);
		dest.set(1, 3, get(1, 3) * scale.y);
		dest.set(2, 0, get(2, 0) * scale.z);
		dest.set(2, 1, get(2, 1) * scale.z);
		dest.set(2, 2, get(2, 2) * scale.z);
		dest.set(2, 3, get(2, 3) * scale.z);
		dest.set(3, 0, get(3, 0));
		dest.set(3, 1, get(3, 1));
		dest.set(3, 2, get(3, 2));
		dest.set(3, 3, get(3, 3));
		return dest;
	}

	Matrix4f& Matrix4f::scale(const Vector3f& scale) {
		return this->scale(scale, *this);
	}

	Matrix4f& Matrix4f::scale(const float xyz, Matrix4f& dest) const {
		return scale(Vector3f(xyz), dest);
	}

	Matrix4f& Matrix4f::scale(const float xyz) {
		return scale(xyz, *this);
	}

	Matrix4f& Matrix4f::invert() {
		return invert(*this);
	}



	Matrix4f& Matrix4f::invert(Matrix4f& dest) const {
		float inv[16];

		inv[0] = val[5] * val[10] * val[15] -
			val[5] * val[11] * val[14] -
			val[9] * val[6] * val[15] +
			val[9] * val[7] * val[14] +
			val[13] * val[6] * val[11] -
			val[13] * val[7] * val[10];

		inv[4] = -val[4] * val[10] * val[15] +
			val[4] * val[11] * val[14] +
			val[8] * val[6] * val[15] -
			val[8] * val[7] * val[14] -
			val[12] * val[6] * val[11] +
			val[12] * val[7] * val[10];

		inv[8] = val[4] * val[9] * val[15] -
			val[4] * val[11] * val[13] -
			val[8] * val[5] * val[15] +
			val[8] * val[7] * val[13] +
			val[12] * val[5] * val[11] -
			val[12] * val[7] * val[9];

		inv[12] = -val[4] * val[9] * val[14] +
			val[4] * val[10] * val[13] +
			val[8] * val[5] * val[14] -
			val[8] * val[6] * val[13] -
			val[12] * val[5] * val[10] +
			val[12] * val[6] * val[9];

		inv[1] = -val[1] * val[10] * val[15] +
			val[1] * val[11] * val[14] +
			val[9] * val[2] * val[15] -
			val[9] * val[3] * val[14] -
			val[13] * val[2] * val[11] +
			val[13] * val[3] * val[10];

		inv[5] = val[0] * val[10] * val[15] -
			val[0] * val[11] * val[14] -
			val[8] * val[2] * val[15] +
			val[8] * val[3] * val[14] +
			val[12] * val[2] * val[11] -
			val[12] * val[3] * val[10];

		inv[9] = -val[0] * val[9] * val[15] +
			val[0] * val[11] * val[13] +
			val[8] * val[1] * val[15] -
			val[8] * val[3] * val[13] -
			val[12] * val[1] * val[11] +
			val[12] * val[3] * val[9];

		inv[13] = val[0] * val[9] * val[14] -
			val[0] * val[10] * val[13] -
			val[8] * val[1] * val[14] +
			val[8] * val[2] * val[13] +
			val[12] * val[1] * val[10] -
			val[12] * val[2] * val[9];

		inv[2] = val[1] * val[6] * val[15] -
			val[1] * val[7] * val[14] -
			val[5] * val[2] * val[15] +
			val[5] * val[3] * val[14] +
			val[13] * val[2] * val[7] -
			val[13] * val[3] * val[6];

		inv[6] = -val[0] * val[6] * val[15] +
			val[0] * val[7] * val[14] +
			val[4] * val[2] * val[15] -
			val[4] * val[3] * val[14] -
			val[12] * val[2] * val[7] +
			val[12] * val[3] * val[6];

		inv[10] = val[0] * val[5] * val[15] -
			val[0] * val[7] * val[13] -
			val[4] * val[1] * val[15] +
			val[4] * val[3] * val[13] +
			val[12] * val[1] * val[7] -
			val[12] * val[3] * val[5];

		inv[14] = -val[0] * val[5] * val[14] +
			val[0] * val[6] * val[13] +
			val[4] * val[1] * val[14] -
			val[4] * val[2] * val[13] -
			val[12] * val[1] * val[6] +
			val[12] * val[2] * val[5];

		inv[3] = -val[1] * val[6] * val[11] +
			val[1] * val[7] * val[10] +
			val[5] * val[2] * val[11] -
			val[5] * val[3] * val[10] -
			val[9] * val[2] * val[7] +
			val[9] * val[3] * val[6];

		inv[7] = val[0] * val[6] * val[11] -
			val[0] * val[7] * val[10] -
			val[4] * val[2] * val[11] +
			val[4] * val[3] * val[10] +
			val[8] * val[2] * val[7] -
			val[8] * val[3] * val[6];

		inv[11] = -val[0] * val[5] * val[11] +
			val[0] * val[7] * val[9] +
			val[4] * val[1] * val[11] -
			val[4] * val[3] * val[9] -
			val[8] * val[1] * val[7] +
			val[8] * val[3] * val[5];

		inv[15] = val[0] * val[5] * val[10] -
			val[0] * val[6] * val[9] -
			val[4] * val[1] * val[10] +
			val[4] * val[2] * val[9] +
			val[8] * val[1] * val[6] -
			val[8] * val[2] * val[5];

		float det = val[0] * inv[0] + val[1] * inv[4] + val[2] * inv[8] + val[3] * inv[12];

		if (det == 0)
			return dest.identity();

		det = 1.0f / det;

		for (int i = 0; i < 16; i++)
			dest.val[i] = inv[i] * det;

		return dest;
	}

	/* EQUALITY  CHECK */
	bool Matrix4f::equals(const Matrix4f& m) const {
		bool result = true;
		for (int i = 0; i < 4 * 4; i++) {
			if (get(i) != m.get(i)) {
				result = false;
				break;
			}
		} return result;
	}

	/* OPERATOR OVERLOADING */
	bool Matrix4f::operator==(const Matrix4f& other) const {
		return equals(other);
	}

	bool Matrix4f::operator!=(const Matrix4f& other) const {
		return !equals(other);
	}

}