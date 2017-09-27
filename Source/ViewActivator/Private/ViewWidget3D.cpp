#include "ViewWidget3D.h"

#include "ViewActivatorPlugin.h"

namespace CubeToSphere
{
	static const FVector Origin[6] =
	{
		FVector(-1.0, -1.0, -1.0),
		FVector(1.0, -1.0, -1.0),
		FVector(1.0, -1.0, 1.0),
		FVector(-1.0, -1.0, 1.0),
		FVector(-1.0, 1.0, -1.0),
		FVector(-1.0, -1.0, 1.0)
	};

	static const FVector Right[6] =
	{
		FVector(2.0, 0.0, 0.0),
		FVector(0.0, 0.0, 2.0),
		FVector(-2.0, 0.0, 0.0),
		FVector(0.0, 0.0, -2.0),
		FVector(2.0, 0.0, 0.0),
		FVector(2.0, 0.0, 0.0)
	};

	static const FVector Up[6] =
	{
		FVector(0.0, 2.0, 0.0),
		FVector(0.0, 2.0, 0.0),
		FVector(0.0, 2.0, 0.0),
		FVector(0.0, 2.0, 0.0),
		FVector(0.0, 0.0, 2.0),
		FVector(0.0, 0.0, -2.0)
	};
};

void UViewWidget3D::ConstructSphere()
{
	const double Step = 1.0f / static_cast<double>(Divisions);
	const FVector Step3(Step, Step, Step);

	TArray<FVector> Vertices;
	for (auto face = 0; face < 6; ++face)
	{
		const FVector Origin = CubeToSphere::Origin[face];
		const FVector Right = CubeToSphere::Right[face];
		const FVector Up = CubeToSphere::Up[face];
		for (auto j = 0; j < Divisions + 1; ++j)
		{
			const FVector J3(j, j, j);
			for (auto i = 0; i < Divisions + 1; ++i)
			{
				const FVector I3(i, i, i);
				const FVector P = Origin + Step3 * (I3 * Right + J3 * Up);
				const FVector PSqr = P * P;
				const FVector N
				(
					P.X * FMath::Sqrt(1.0f - 0.5f * (PSqr.Y + PSqr.Z) + PSqr.Y * PSqr.Z) / 3.0f,
					P.Y * FMath::Sqrt(1.0f - 0.5f * (PSqr.Z + PSqr.X) + PSqr.Z * PSqr.X) / 3.0f,
					P.Z * FMath::Sqrt(1.0f - 0.5f * (PSqr.X + PSqr.Y) + PSqr.X * PSqr.Y) / 3.0f
				);
				Vertices.Add(N);
			}
		}
	}

	TArray<int32> Faces;
	const uint32 K = Divisions + 1;
	for (auto face = 0; face < 6; ++face)
	{
		for (auto j = 0; j < Divisions; ++j)
		{
			const bool bIsBottom = j < (Divisions / 2);
			for (auto i = 0; i < Divisions; ++i)
			{
				const bool bIsLeft = i < (Divisions / 2);
				const int32 A = (face * K + j) * K + i;
				const int32 B = (face * K + j) * K + i + 1;
				const int32 C = (face * K + j + 1) * K + i;
				const int32 D = (face * K + j + 1) * K + i + 1;
				if (bIsBottom ^ bIsLeft)
				{
					Faces.Add(A);
					Faces.Add(B);
					Faces.Add(D);
					Faces.Add(B);
					Faces.Add(C);
					Faces.Add(D);
				}
				else
				{
					Faces.Add(A);
					Faces.Add(B);
					Faces.Add(C);
					Faces.Add(A);
					Faces.Add(C);
					Faces.Add(D);
				}
			}
		}
	}
}

bool UViewWidget3D::RaycastSphere(FHitResult& OutHitResult, FVector InStart, FVector InEnd, FSphere& InSphere)
{
	FVector E = InSphere.Center - InStart;
	float RadiusSq = InSphere.W * InSphere.W;
	float ESq = E.SizeSquared(); // I think
	FVector Direction = (InEnd - InStart);
	Direction.Normalize();
	float A = FVector::DotProduct(E, Direction);
	float BSq = ESq - (A * A);
	float F = FMath::Sqrt(RadiusSq - BSq);
	float T = A - F;
	if (RadiusSq - (ESq - A * A) < 0.0f)
		return false;
	else if (ESq < RadiusSq)
		T = A + F;

	OutHitResult.Location = InStart + Direction * T;
	OutHitResult.Normal = (OutHitResult.Location - InSphere.Center);
	OutHitResult.Normal.Normalize();

	return true;
}

void UViewWidget3D::NativeConstruct()
{
	Super::NativeConstruct();

	Divisions = 32;
}