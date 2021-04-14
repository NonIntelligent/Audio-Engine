#include "Camera.h"
#include <math.h>

Mat4d Camera::perspective() {
	float fn = far + near;
	float deltaPlane = far - near;
	float aspectRatio = viewport[0] / viewport[1];
	float t = tan(toRad(fov_y) / 2.0);
	
	// http://www.songho.ca/opengl/gl_projectionmatrix.html

	Mat4d frustrum;
	frustrum.setAsZero();
	frustrum.matrix[0][0] = 1.f / (aspectRatio * t);
	frustrum.matrix[1][1] = 1.f / t;
	frustrum.matrix[2][2] = -fn / deltaPlane;
	frustrum.matrix[2][3] = -2.f * far * near / deltaPlane;
	frustrum.matrix[3][2] = -1.f;

	return frustrum;
}

Mat4d Camera::lookAt() {
	Mat4d view;

	//Vec3d eye; Vec3d::add(&eye, &pos, &target);
	Vec3d camRight;
	Vec3d camDirection;
	Vec3d camUp;
	Vec3d dotPos;

	Vec3d::sub(camDirection, pos, target);
	camDirection.normalise();
	Vec3d::cross(camRight, up, camDirection);
	camRight.normalise();
	Vec3d::cross(camUp, camDirection, camRight);

	dotPos.x = -Vec3d::dot(camRight, pos);
	dotPos.y = -Vec3d::dot(camUp, pos);
	dotPos.z =  Vec3d::dot(camDirection, pos);

	view.setAsIdentity();
	view.setRowData(0, camRight);
	view.setRowData(1, camUp);
	view.setRowData(2, Vec3d{-camDirection.x, -camDirection.y, -camDirection.z});
	view.setColData(3, dotPos);


	return view;
}

void Camera::setPos(double x, double y, double z) {
	pos.set(x, y, z);
}
