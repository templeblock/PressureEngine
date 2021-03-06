#pragma once

#include <array>
#include "Plane.h"
#include "../Matrices/Matrix4f.h"
#include "AABB.h"

namespace Pressure {

	class ViewFrustum {

	private:
		std::array<Plane, 6> m_Planes;

	public:
		static ViewFrustum& Inst();

		void extractPlanes(const Matrix4f& projectionViewMatrix);

		bool pointInFrustum(const Vector3f& point) const;
		bool sphereInFrustum(const Vector3f center, const float radius) const;
		
		// Not working as intended.
		bool aabbInFrustum(const AABB& bounds) const;

	protected:
		ViewFrustum() { }
		ViewFrustum(const ViewFrustum& vm) = delete;
		ViewFrustum& operator=(const ViewFrustum& vm) = delete;

		static ViewFrustum* m_Inst;
	};

}