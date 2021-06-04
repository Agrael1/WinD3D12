#pragma once

namespace ver
{
	class Model;
	class Mesh;
	class Graphics;
	//class TechniqueProbe;
	//class ModelProbe;

	class Node
	{
		friend Model;
	public:
		Node(int id, std::string_view, std::vector<Mesh*> meshPtrs, const DirectX::XMMATRIX& transform);
	public:
		void Step(const Graphics& gfx, float dt, DirectX::FXMMATRIX accumulatedTransform) const;
		void SetAppliedTransform(DirectX::FXMMATRIX transform) noexcept;
		const DirectX::XMFLOAT4X4& GetAppliedTransform() const noexcept;
		int GetId() const noexcept;
		bool HasChildren() const noexcept
		{
			return childPtrs.size() > 0;
		}
		//void Accept(ModelProbe& probe);
		//void Accept(TechniqueProbe& probe);
		std::string_view GetName() const
		{
			return name;
		}
	private:
		void AddChild(std::unique_ptr<Node> pChild)noexcept;
	private:
		std::string name;
		int id;
		std::vector<std::unique_ptr<Node>> childPtrs;
		std::vector<Mesh*> meshPtrs;
		DirectX::XMFLOAT4X4 transform;
		DirectX::XMFLOAT4X4 appliedTransform;
	};
}