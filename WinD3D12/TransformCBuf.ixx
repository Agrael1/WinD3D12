module;
#include <cstdint>
export module TransformCBuf;
import ConstantBuffers;

export namespace ver
{
	class TransformCbuf : public ConstantBuffer
	{
	protected:
		struct Transforms
		{
			DirectX::XMMATRIX modelView;
			DirectX::XMMATRIX modelViewProj;
		}tr;
	public:
		TransformCbuf(const Graphics& gfx, uint32_t slot = 0u);
	public:
		void Update(const Graphics& gfx, DirectX::XMMATRIX transform) noexcept;
	};
}
