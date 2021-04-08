#include "ScreenRecord.h"

void ScreenRecord::init()
{
	mask.Load(L"Data/Sprite/mask.dds");
	mask_ps.LoadPixelShader("Data/shader/mask_ps.cso");
	ScreenSize = AliceLib::GetWindowSize();
	buffer.init(static_cast<int>(ScreenSize.x), static_cast<int>(ScreenSize.y));
}

void ScreenRecord::save(int num)
{
	framebuffer _save;
	_save.init(static_cast<int>(ScreenSize.x), static_cast<int>(ScreenSize.y));
	//テクスチャバインドによるエラー回避用
	ID3D11ShaderResourceView* null_srv[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
	context->VSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, null_srv);
	context->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, null_srv);
	_save.begin();
	//Todo
	buffer.SetShaderResource(0, 0, 1);
	mask.Set(1, 0, 1);
	SampleState->Active(SampleType::S_CLAMP);
	mask_ps.SetPSSharders();
	FullScreenQuadBlit();
	_save.end();
	records[0].load(_save.render_target_shader_resource_view.Get());
	test = _save.render_target_shader_resource_view.Get();
	test->AddRef();
}

void ScreenRecord::begin()
{
	//テクスチャバインドによるエラー回避用
	ID3D11ShaderResourceView* null_srv[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };
	context->VSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, null_srv);
	context->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, null_srv);
	buffer.begin();
}

void ScreenRecord::end()
{
	buffer.end();
	FrameBufferRender(buffer, {});
}

void ScreenRecord::demoPlay()
{
	ImGuiNewFrame();
	ImGui::Begin("test");
	if(test)
	ImGui::Image(test, { ScreenSize.x/5.0f,ScreenSize.y / 5.0f });
	ImGui::End();
	ImGuiRender();
}
