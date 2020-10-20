#pragma once
#include "Bindable.h"

namespace ver
{
	class Pipeline : public Bindable
	{
	public:
		Pipeline()
		{
		}
	private:
		wgpu::RenderPipelineDescriptor desc = {};
		wgpu::RenderPipeline pipe;
	};
}
