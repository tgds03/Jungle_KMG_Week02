#include "stdafx.h"

const FMatrix FMatrix::Identity = FMatrix({
	1.f, 0.f, 0.f, 0.f,
	0.f, 1.f, 0.f, 0.f,
	0.f, 0.f, 1.f, 0.f,
	0.f, 0.f, 0.f, 1.f,
});

FMatrix::FMatrix(float m[4][4]) {
	memcpy(this->m, m, sizeof(float) * 4 * 4);
}

FMatrix::FMatrix(FVector4 r[4]) {
	this->m[0][0] = r[0].x; this->m[0][1] = r[0].y; this->m[0][2] = r[0].z; this->m[0][3] = r[0].w;
	this->m[1][0] = r[1].x; this->m[1][1] = r[1].y; this->m[1][2] = r[1].z; this->m[1][3] = r[1].w;
	this->m[2][0] = r[2].x; this->m[2][1] = r[2].y; this->m[2][2] = r[2].z; this->m[2][3] = r[2].w;
	this->m[3][0] = r[3].x; this->m[3][1] = r[3].y; this->m[3][2] = r[3].z; this->m[3][3] = r[3].w;

}

FMatrix::FMatrix(const std::initializer_list<float>& m) {
	if ( m.size() != 16 ) {
		assert(0);
		return;
	}
	int i = 0;
	for (auto f: m) {
		this->m[i/4][i%4] = f;
		++i;
	}
}

FMatrix::FMatrix(const FMatrix& other)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = other.m[i][j];  // ���� ����
		}
	}
}

FMatrix FMatrix::operator+(const FMatrix& rhs) const {
	float m[4][4] = {
		{this->m[0][0] + rhs.m[0][0], this->m[0][1] + rhs.m[0][1], this->m[0][2] + rhs.m[0][2], this->m[0][3] + rhs.m[0][3]},
		{this->m[1][0] + rhs.m[1][0], this->m[1][1] + rhs.m[1][1], this->m[1][2] + rhs.m[1][2], this->m[1][3] + rhs.m[1][3]},
		{this->m[2][0] + rhs.m[2][0], this->m[2][1] + rhs.m[2][1], this->m[2][2] + rhs.m[2][2], this->m[2][3] + rhs.m[2][3]},
		{this->m[3][0] + rhs.m[3][0], this->m[3][1] + rhs.m[3][1], this->m[3][2] + rhs.m[3][2], this->m[3][3] + rhs.m[3][3]},
	};
	return FMatrix(m);
}

FMatrix FMatrix::operator-(const FMatrix& rhs) const {
	float m[4][4] = {
		{this->m[0][0] - rhs.m[0][0], this->m[0][1] - rhs.m[0][1], this->m[0][2] - rhs.m[0][2], this->m[0][3] - rhs.m[0][3]},
		{this->m[1][0] - rhs.m[1][0], this->m[1][1] - rhs.m[1][1], this->m[1][2] - rhs.m[1][2], this->m[1][3] - rhs.m[1][3]},
		{this->m[2][0] - rhs.m[2][0], this->m[2][1] - rhs.m[2][1], this->m[2][2] - rhs.m[2][2], this->m[2][3] - rhs.m[2][3]},
		{this->m[3][0] - rhs.m[3][0], this->m[3][1] - rhs.m[3][1], this->m[3][2] - rhs.m[3][2], this->m[3][3] - rhs.m[3][3]},
	};
	return FMatrix(m);
}

FMatrix FMatrix::operator*(const float& rhs) const {
	float m[4][4] = {
		{this->m[0][0] * rhs, this->m[0][1] * rhs, this->m[0][2] * rhs, this->m[0][3] * rhs},
		{this->m[1][0] * rhs, this->m[1][1] * rhs, this->m[1][2] * rhs, this->m[1][3] * rhs},
		{this->m[2][0] * rhs, this->m[2][1] * rhs, this->m[2][2] * rhs, this->m[2][3] * rhs},
		{this->m[3][0] * rhs, this->m[3][1] * rhs, this->m[3][2] * rhs, this->m[3][3] * rhs},
	};
	return FMatrix(m);
}

FMatrix FMatrix::operator*(const FMatrix& rhs) const {
	return FMatrix({
		r1()*rhs.c1(), r1()*rhs.c2(), r1()*rhs.c3(), r1()*rhs.c4(),
		r2()*rhs.c1(), r2()*rhs.c2(), r2()*rhs.c3(), r2()*rhs.c4(),
		r3()*rhs.c1(), r3()*rhs.c2(), r3()*rhs.c3(), r3()*rhs.c4(),
		r4()*rhs.c1(), r4()*rhs.c2(), r4()*rhs.c3(), r4()*rhs.c4(),
	});
}

FMatrix& FMatrix::operator=(const FMatrix& other)
{
	if (this != &other) {  // �ڱ� �ڽ��� �����ϴ� ���?����
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = other.m[i][j];  // ���� ���� ����
			}
		}
	}
	return *this;
}

bool FMatrix::operator==(const FMatrix& other) const
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if(m[i][j] != other.m[i][j]) return false;  // ���� ���� ����
		}
	}
	return true;
}

bool FMatrix::operator!=(const FMatrix& other) const
{
	return !(*this == other);
}

//FVector4 FMatrix::operator*(const FVector4& rhs) const {
//	return FVector4(rhs.Dot(c1()), rhs.Dot(c2()), rhs.Dot(c3()), rhs.Dot(c4()));
//}

FVector4 operator*(const FVector4& lhs, const FMatrix& rhs) {
#ifdef _COL_MAJOR_SYSTEM
	return FVector4(lhs * rhs.r1(), lhs * rhs.r2(), lhs * rhs.r3(), lhs * rhs.r4());
#else
	return FVector4(lhs*rhs.c1(), lhs*rhs.c2(), lhs*rhs.c3(), lhs*rhs.c4());
#endif
};

FVector4 FMatrix::r1() const { return FVector4(m[0][0], m[0][1], m[0][2], m[0][3]); }

FVector4 FMatrix::r2() const { return FVector4(m[1][0], m[1][1], m[1][2], m[1][3]); }

FVector4 FMatrix::r3() const { return FVector4(m[2][0], m[2][1], m[2][2], m[2][3]); }

FVector4 FMatrix::r4() const { return FVector4(m[3][0], m[3][1], m[3][2], m[3][3]); }

FVector4 FMatrix::c1() const { return FVector4(m[0][0], m[1][0], m[2][0], m[3][0]); }

FVector4 FMatrix::c2() const { return FVector4(m[0][1], m[1][1], m[2][1], m[3][1]); }

FVector4 FMatrix::c3() const { return FVector4(m[0][2], m[1][2], m[2][2], m[3][2]); }

FVector4 FMatrix::c4() const { return FVector4(m[0][3], m[1][3], m[2][3], m[3][3]); }

FMatrix FMatrix::Transpose() const {
	return FMatrix({
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3],
	});
}

FMatrix FMatrix::Inverse() const
{
	FMatrix A = *this;
	FMatrix inv = FMatrix::Identity;
	// ���콺-���� �ҰŹ�
	for (int i = 0; i < 4; i++) {
		// �ǹ��� 0�̸� �� ��ȯ
		if (A[i][i] == 0) {
			int swapRow = i + 1;
			while (swapRow < 4 && fabs(A.m[swapRow][i]) < FLT_EPSILON) swapRow++;
			if (swapRow == 4)
			{
				return FMatrix::Identity; // �����?����
			}
			A = A.SwapRow(i, swapRow);
			inv = inv.SwapRow(i, swapRow);
		}

		// �ǹ��� 1�� �����?
		float pivot = A.m[i][i];
		for (int j = 0; j < 4; j++) {
			A.m[i][j] /= pivot;
			inv.m[i][j] /= pivot;
		}

		// �ٸ� ���� i���� 0���� �����?
		for (int k = 0; k < 4; k++) {
			if (i == k) continue;
			float factor = A.m[k][i];
			for (int j = 0; j < 4; j++) {
				A.m[k][j] -= factor * A.m[i][j];
				inv.m[k][j] -= factor * inv.m[i][j];
			}
		}
	}
	return inv;
}

FVector FMatrix::GetScaledAxis(EAxis axis) const
{
	switch (axis)
	{
	case EAxis::X:
		return FVector(m[0][0], m[0][1], m[0][2]);
	case EAxis::Y:
		return FVector(m[1][0], m[1][1], m[1][2]);
	case EAxis::Z:
		return FVector(m[2][0], m[2][1], m[2][2]);
	default:
		return FVector(0.0f, 0.0f, 0.0f);
	}
}

std::string FMatrix::to_string() const
{
	std::string str;
	std::string sep(" ");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			str += std::to_string(m[i][j]);
			str += sep;
		}
		str += std::string("\n");
	}
	return str;
}

FMatrix FMatrix::MakeFrom(const FVector& u, const FVector& v, const FVector& w, const FVector& p = FVector::Zero) {
#ifdef _COL_MAJOR_SYSTEM
	return FMatrix({
		u.x, u.y, u.z, p.x,
		v.x, v.y, v.z, p.y,
		w.x, w.y, w.z, p.z,
		0.f, 0.f, 0.f, 1.f
	});
#else
	return FMatrix({
		u.x, v.x, w.x, 0.f,
		u.y, v.y, w.y, 0.f,
		u.z, v.z, w.z, 0.f,
		p.x, p.y, p.z , 1.f
	});
#endif
}

FMatrix FMatrix::Scale(float sx, float sy, float sz) {
	return MakeFrom(
		FVector(sx, 0, 0), 
		FVector(0, sy, 0), 
		FVector(0, 0, sz)
	);
}

FMatrix FMatrix::Scale(FVector xyz)
{
	return Scale(xyz.x, xyz.y, xyz.z);
}

FMatrix FMatrix::RotateX(float rx) {
	return MakeFrom(
		FVector(1.f, 0.f, 0.f),
		FVector(0.f, cosf(rx), -sinf(rx)),
		FVector(0.f, sinf(rx), cosf(rx))
	);
}
FMatrix FMatrix::RotateY(float ry) {
	return MakeFrom(
		FVector(cosf(ry), 0.f, sinf(ry)),
		FVector(0.f, 1.f, 0.f),
		FVector(-sinf(ry), 0.f, cosf(ry))
	);
}

FMatrix FMatrix::RotateZ(float rz) {
	return MakeFrom(
		FVector(cosf(rz), -sinf(rz), 0.f),
		FVector(sinf(rz), cosf(rz), 0.f),
		FVector(0.f, 0.f, 1.f)
	);
}

FMatrix FMatrix::RotateXYZ(FVector xyz)
{
	FMatrix mat = FMatrix::Identity;
	mat = mat * mat.RotateX(xyz.x);
	mat = mat * mat.RotateY(xyz.y);
	mat = mat * mat.RotateZ(xyz.z);
	
	return mat;
}

FMatrix FMatrix::Translate(float tx, float ty, float tz) {
	return MakeFrom(
		FVector(1.f, 0.f, 0.f),
		FVector(0.f, 1.f, 0.f),
		FVector(0.f, 0.f, 1.f),
		FVector(tx, ty, tz)
	);
}

FMatrix FMatrix::Translate(FVector xyz)
{
	return Translate(xyz.x, xyz.y, xyz.z);
}

FMatrix FMatrix::SwapRow(UINT r1, UINT r2)
{
	if (r1 > 3 || r2 > 3) return FMatrix::Identity;

	FMatrix swapped = *this;
	float tempRow[4] = { m[r1][0], m[r1][1], m[r1][2], m[r1][3] };

	swapped.m[r1][0] = m[r2][0];
	swapped.m[r1][1] = m[r2][1];
	swapped.m[r1][2] = m[r2][2];
	swapped.m[r1][3] = m[r2][3];

	swapped.m[r1][0] = tempRow[0];
	swapped.m[r1][1] = tempRow[1];
	swapped.m[r1][2] = tempRow[2];
	swapped.m[r1][3] = tempRow[3];

	return swapped;
}
