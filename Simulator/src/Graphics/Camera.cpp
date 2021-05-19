#include "Camera.h"
#include <math.h>

Mat4f Camera::perspective() {
	float fn = far + near;
	float deltaPlane = far - near;
	float aspectRatio = viewport[0] / viewport[1];
	float t = tan(toRad(fov_y) / 2.0);
	
	// http://www.songho.ca/opengl/gl_projectionmatrix.html

	Vec3f xyz;
	Vec3f::add(xyz, xyz, xyz);

	Mat4f frustrum;
	frustrum.setAsZero();
	frustrum.matrix[0][0] = 1.f / (aspectRatio * t);
	frustrum.matrix[1][1] = 1.f / t;
	frustrum.matrix[2][2] = -fn / deltaPlane;
	frustrum.matrix[2][3] = -2.f * far * near / deltaPlane;
	frustrum.matrix[3][2] = -1.f;

	return frustrum;
}

Mat4f Camera::lookAt() {
	Mat4f view;

	//Vec3 eye; Vec3::add(&eye, &pos, &target);
	Vec3f camRight;
	Vec3f camDirection;
	Vec3f camUp;
	Vec3f dotPos;

	Vec3f::sub(camDirection, pos, target);
	camDirection.normalise();
	Vec3f::cross(camRight, up, camDirection);
	camRight.normalise();
	Vec3f::cross(camUp, camDirection, camRight);

	dotPos.x = -Vec3f::dot(camRight, pos);
	dotPos.y = -Vec3f::dot(camUp, pos);
	dotPos.z =  Vec3f::dot(camDirection, pos);

	view.setAsIdentity();
	view.setRowData(0, camRight);
	view.setRowData(1, camUp);
	view.setRowData(2, Vec3f{-camDirection.x, -camDirection.y, -camDirection.z});
	view.setColData(3, dotPos);


	return view;
}

void Camera::setPos(double x, double y, double z) {
	pos.set(x, y, z);
}
