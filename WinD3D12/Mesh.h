#pragma once
#include "Drawable.h"
#include "TransformCBuf.h"
#include "ConstantBufferEx.h"
#include <pplawait.h>

namespace ver
{
	class Material;
	class Mesh : public Drawable
	{
		friend class Panel;
	public:
		Mesh(const Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale = 1.0f);
		static concurrency::task<std::shared_ptr<Mesh>>
			MakeAsync(const Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale = 1.0f);
	public:
		DirectX::XMMATRIX GetTransformXM() const noexcept;
		void Step(const Graphics& gfx, float dt, DirectX::FXMMATRIX accumulatedTranform);
	private:
		mutable DirectX::XMFLOAT4X4 transform;
		TransformCbuf cbuf;
		PixelConstantBufferEx pixbuf;
	};
}