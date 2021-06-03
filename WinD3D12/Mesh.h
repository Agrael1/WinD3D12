#pragma once
#include "Material.h"
#include "Drawable.h"
#include "TransformCBuf.h"

namespace ver
{
	class Mesh : public Drawable
	{
	public:
		Mesh(Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale = 1.0f);
		DirectX::XMMATRIX GetTransformXM() const noexcept;
		void Submit(DirectX::FXMMATRIX accumulatedTranform) const;
	private:
		mutable DirectX::XMFLOAT4X4 transform;
		TransformCbuf cbuf;
	};
}