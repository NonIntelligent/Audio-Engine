#pragma once

constexpr double PI = 3.141592653589793;
constexpr float PI_f = 3.1415926f;
double toRad(double degrees);
float toRadf(float degrees);
double toDegrees(double radians);
float toDegreesf(float radians);
// Returns an integer based on the sign of the value. (1 = +, 0 = 0, -1 = -).
template<typename T> int getSign(T val) {
	// https://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
	return (T(0) < val) - (val < T(0));
};

struct Vec3d {
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;

	Vec3d() {
	};

	Vec3d(double x, double y, double z) : x(x), y(y), z(z) {
	};

	void set(double x, double y, double z);

	// Adds the components of a and b then stores the value in result.
	static void add(Vec3d &result, const Vec3d &a, const Vec3d &b);

	// Subtracts the components of a and b then stores the value in result.
	static void sub(Vec3d &result, const Vec3d &a, const Vec3d &b);

	// Multiplies each component of a by k then stores each value in result.
	static void scale(Vec3d &result, const Vec3d &a, double k);

	// Adds each component of a * k to result.
	static void increment(Vec3d &result, const Vec3d &a, double k);

	// Computes the dot product of a and b.
	static float dot(const Vec3d &a, const Vec3d &b);

	// Computes the cross product of a and b and replaces result.
	static void cross(Vec3d &result, const Vec3d &a, const Vec3d &b);

	// Normalises the vector.
	void normalise();

	// Multiplies each component by -1.
	void negate();

	// Provides the magnitude of the vector squared.
	float lengthSquare() const;

	// Is each component equivalent.
	bool compare(Vec3d &a) const;

};

struct Mat3d {
	double matrix[3][3];

	Mat3d() {
		setAsIdentity();
	};

	/*
	Replace the data of the matrix at the specified row given an array.
	@param index The row index to replace (0-3)
	*/
	void setRowData(int index, const double* array);
	/* Replace entire row data given a vector.
	@overload
	*/
	void setRowData(int index, const Vec3d &vec);

	/*
	Replace the data of the matrix at the specified column given an array.
	@param index The column index to replace (0-3)
	*/
	void setColData(int index, const double* array);
	/* Replace entire column data given a vector.
	@overload
	*/
	void setColData(int index, const Vec3d &vec);

	// Returns the entire row as a vector.
	Vec3d getRowAsVec(int index) const;

	// Returns the entire column as a vector.
	Vec3d getColAsVec(int index) const;

	// Set matrix as identity.
	void setAsIdentity();

	// Set all values to 0.
	void setAsZero();

	// Calculate the determinant of this matrix.
	float determinant() const;

	// Transpose this matrix.
	void transpose();

	// Add each corresponding value of matrix a with b and store in result.
	static void add(Mat3d &result, const Mat3d &a, const Mat3d &b);

	// Subtract each corresponding value of matrix a with b and store in result.
	static void sub(Mat3d &result, Mat3d &a, Mat3d &b);

	// Scale each value in matrix a by b and store in result.
	static void scale(Mat3d &result, const Mat3d &a, float b);

	// Multiply matrix a and b in the order (a * b) and store in result.
	// Result cannot be the same as input b.
	static void mult(Mat3d &result, const Mat3d &a, const Mat3d &b);

	// Multiply matrix a and vector b in the order (a * b) and store in result.
	// Result cannot be the same as input b.
	static void mult(Vec3d &result, const Mat3d &a, const Vec3d &b);

	// Calculate the inverse of matrix a and stores in result.
	static bool inverse(Mat3d &result, const Mat3d &a);

	// Creates a rotation matrix and multiplies as (rotation * result).
	static void rotate(Mat3d &result, const Vec3d &axis, double angle);

	// Creates a rotation matrix and multiplies as (rotation * result).
	static void rotate(Mat3d &result, const Vec3d &axis, const Vec3d &angles);

};

struct Vec4d {
	double x = 0.f;
	double y = 0.f;
	double z = 0.f;
	double w = 1.f;

	Vec4d() {
	};

	Vec4d(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {};

	void set(double x, double y, double z, double w);

	// Adds the components of a and b then stores the value in result.
	static void add(Vec4d &result, const Vec4d &a, const Vec4d &b);

	// Subtracts the components of a and b then stores the value in result.
	static void sub(Vec4d &result, const Vec4d &a, const Vec4d &b);

	// Multiplies each component of a by k then stores each value in result.
	static void scale(Vec4d &result, const Vec4d &a, float k);

	// Adds each component of a * k to result.
	static void increment(Vec4d &result, const Vec4d &a, float k);

	// Computes the dot product of a and b.
	static float dot(const Vec4d &a, const Vec4d &b);

	// Normalises the vector.
	void normalise();

	// Multiplies each component by -1.
	void negate();

	// Provides the magnitude of the vector squared.
	float lengthSquare() const;

	// Compares the values between both vectors for equality
	bool compare(const Vec4d &a) const;
};

struct Mat4d {
	double matrix[4][4];

	Mat4d() {
		setAsIdentity();
	};

	/*
	Replace the data of the matrix at the specified row given an array.
	@param index The row index to replace (0-3)
	*/
	void setRowData(int index, const double* array);
	/* Replace entire row data given a vector.
	@overload
	*/
	void setRowData(int index, const Vec4d &vec);
	/* Replace the first 3 values in the row given a vector.
	@overload
	*/
	void setRowData(int index, const Vec3d &vec);

	/*
	Replace the data of the matrix at the specified column given an array.
	@param index The column index to replace (0-3)
	*/
	void setColData(int index, const double* array);
	/* Replace entire column data given a vector.
	@overload
	*/
	void setColData(int index, const Vec4d &vec);
	/* Replace the first 3 column values given a vector.
	@overload
	*/
	void setColData(int index, const Vec3d &vec);

	// Returns the first 3 components as row vector.
	Vec3d getRowAsVec3(int index) const;

	// Returns the entire row as a vector.
	Vec4d getRowAsVec4(int index) const;

	// Returns the first 3 components as a column vector.
	Vec3d getColAsVec3(int index) const;
	// Returns the entire column as a vector.
	Vec4d getColAsVec4(int index) const;

	// Returns a 3x3 matrix that exclude the given row and column.
	Mat3d get3x3Matrix(int row, int col) const;

	// Set matrix as identity.
	void setAsIdentity();

	// Set all values to 0.
	void setAsZero();

	// Calculate the determinant of this matrix.
	float determinant() const;

	// Transpose this matrix.
	void transpose();

	// Copies the data in the matrix into the given 1D array in row-major order.
	void data(double arr[16]) const;

	// Copies the data in the matrix into the given 1D array in col-major order.
	void dataColMaj(double arr[16]) const;

	// Add each corresponding value of matrix a with b and store in result.
	static void add(Mat4d &result, const Mat4d &a, const Mat4d &b);

	// Subtract each corresponding value of matrix a with b and store in result.
	static void sub(Mat4d &result, const Mat4d &a, const Mat4d &b);

	// Scale each value in matrix a by b and store in result.
	static void scale(Mat4d &result, const Mat4d &a, double b);

	// Multiply matrix a and b in the order (a * b) and store in result.
	// Result cannot be the same as input b.
	static void mult(Mat4d &result, const Mat4d &a, const Mat4d &b);

	// Multiply matrix a and vector b in the order (a * b) and store in result.
	// Result cannot be the same as input b.
	static void mult(Vec4d &result, const Mat4d &a, const Vec4d &b);

	// Calculate the inverse of matrix a and stores in result.
	static bool inverse(Mat4d &result, const Mat4d &a);

	// Creates a rotation matrix and multiplies as (rotation * result).
	static void rotate(Mat4d &result, const Vec3d &axis, double angle);

	// Creates a rotation matrix and multiplies as (rotation * result).
	static void rotate(Mat4d &result, const Vec3d &axis, const Vec3d &angles);

	// Creates a translation matrix and multiplies as (translation * result).
	static void translate(Mat4d &result, const Vec3d &translate);

	// Creates a scale matrix and multiplies as (scale * result).
	static void scaleVec(Mat4d &result, const Vec3d &scalar);
};
