#pragma once
#include "IndexedTriangleList.h"
#include <optional>


class Sphere
{
public:
	static IndexedTriangleList MakeTesselated(ver::dv::VertexLayout layout, unsigned latDiv, unsigned longDiv)
	{
		namespace dx = DirectX;
		assert(latDiv >= 3);
		assert(longDiv >= 3);


		constexpr float radius = 1.0f;
		const auto base = dx::XMVectorSet(0.0f, 0.0f, radius, 0.0f);
		const float lattitudeAngle = dx::XM_PI / latDiv;
		const float longitudeAngle = 2.0f * dx::XM_PI / longDiv;

		ver::dv::VertexBuffer vb{ std::move(layout) };
		vb.Resize(longDiv * (latDiv - 1)+2);
		size_t index = 0;


		for (size_t iLat = 1; iLat < latDiv; iLat++)
		{
			const auto latBase = dx::XMVector3Transform(
				base,
				dx::XMMatrixRotationX(lattitudeAngle * iLat)
			);
			for (size_t iLong = 0; iLong < longDiv; iLong++)
			{
				dx::XMFLOAT3 calculatedPos;
				auto v = dx::XMVector3Transform(
					latBase,
					dx::XMMatrixRotationZ(longitudeAngle * iLong)
				);
				dx::XMStoreFloat3(&calculatedPos, v);
				vb[index++].Attr<ver::VType::Position3D>() = calculatedPos;
			}
		}

		// add the cap vertices
		const auto iNorthPole = (unsigned short)vb.Size();
		{
			dx::XMFLOAT3 northPos;
			dx::XMStoreFloat3(&northPos, base);
			vb[index++].Attr<ver::VType::Position3D>() = northPos;
		}
		const auto iSouthPole = (unsigned short)vb.Size();
		{
			dx::XMFLOAT3 southPos;
			dx::XMStoreFloat3(&southPos, dx::XMVectorNegate(base));
			vb[index++].Attr<ver::VType::Position3D>() = southPos;
		}

		const auto calcIdx = [latDiv, longDiv](unsigned iLat, unsigned iLong)->uint16_t
		{ return uint16_t(iLat * longDiv + iLong); };
		std::vector<unsigned short> indices;
		for (unsigned short iLat = 0; iLat < latDiv - 2; iLat++)
		{
			for (unsigned short iLong = 0; iLong < longDiv - 1; iLong++)
			{
				indices.push_back(calcIdx(iLat, iLong));
				indices.push_back(calcIdx(iLat + 1, iLong));
				indices.push_back(calcIdx(iLat, iLong + 1));
				indices.push_back(calcIdx(iLat, iLong + 1));
				indices.push_back(calcIdx(iLat + 1, iLong));
				indices.push_back(calcIdx(iLat + 1, iLong + 1));
			}
			// wrap band
			indices.push_back(calcIdx(iLat, longDiv - 1));
			indices.push_back(calcIdx(iLat + 1, longDiv - 1));
			indices.push_back(calcIdx(iLat, 0));
			indices.push_back(calcIdx(iLat, 0));
			indices.push_back(calcIdx(iLat + 1, longDiv - 1));
			indices.push_back(calcIdx(iLat + 1, 0));
		}

		// cap fans
		for (unsigned short iLong = 0; iLong < longDiv - 1; iLong++)
		{
			// north
			indices.push_back(iNorthPole);
			indices.push_back(calcIdx(0, iLong));
			indices.push_back(calcIdx(0, iLong + 1));
			// south
			indices.push_back(calcIdx(latDiv - 2, iLong + 1));
			indices.push_back(calcIdx(latDiv - 2, iLong));
			indices.push_back(iSouthPole);
		}
		// wrap triangles
		// north
		indices.push_back(iNorthPole);
		indices.push_back(calcIdx(0, longDiv - 1));
		indices.push_back(calcIdx(0, 0));
		// south
		indices.push_back(calcIdx(latDiv - 2, 0));
		indices.push_back(calcIdx(latDiv - 2, longDiv - 1));
		indices.push_back(iSouthPole);

		return { std::move(vb),std::move(indices) };
	}

	static IndexedTriangleList Make(std::optional<ver::dv::VertexLayout> layout = std::nullopt)
	{
		using Element = ver::dv::VertexLayout::ElementType;
		if (!layout)
		{
			layout = ver::dv::VertexLayout
			{
				{Element::Position3D}
			};
		}
		return MakeTesselated(std::move(*layout), 12, 24);
	}
};