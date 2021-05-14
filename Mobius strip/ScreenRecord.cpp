#include "ScreenRecord.h"

void ScreenRecord::init()
{
	mask.Load(L"Data/Sprite/mask.dds");
	brightness_ps.LoadPixelShader("Data/shader/Increase_brightness_ps.cso");
	mask_ps.LoadPixelShader("Data/shader/mask_ps.cso");
	ScreenSize = AliceLib::GetWindowSize();
	buffer.init(static_cast<int>(ScreenSize.x), static_cast<int>(ScreenSize.y));
	cbuff.CreateConstantBuffer();
	cbuff2.CreateConstantBuffer();
}

bool ScreenRecord::save(int num)
{
	if (0 > num || num >= max_racord)return false;
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
	cbuff.Active(0, 0, 1);
	SampleState->Active(SampleType::S_CLAMP);
	mask_ps.SetPSSharders();
	FullScreenQuadBlit();
	_save.end();
	records[num].load(_save.render_target_shader_resource_view.Get());
	//test = _save.render_target_shader_resource_view.Get();
	//test->AddRef();
	return true;
}

bool ScreenRecord::erasure(int num)
{
	if (0 > num || num >= max_racord)return false;
	if (records[num])
	{
		records[num].unload();
		return true;
	}
	return false;
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
	brightness_ps.SetPSSharders();
#if _DEBUG
	_edit();
#endif // 
	cbuff2.Active(1, 0, 1);
	SampleState->Active(0, 0, 1);
	buffer.SetShaderResource(0, 0, 1);
	FullScreenQuadBlit();
	//FrameBufferRender(buffer, {});
}

void ScreenRecord::_edit()
{
	ImGui::Begin(u8"オプション");
	ImGui::InputFloat(u8"コントラスト", &cbuff2->ContrastWeight, 0.25, -0.25);
	ImGui::InputFloat(u8"明度", &cbuff2->Bright, 0.25, -0.25);
	ImGui::InputFloat(u8"閾値", &cbuff2->threshold, 0.025, -0.025);
	ImGui::End();
}

//void ScreenRecord::demoPlay()
//{
//	ImGuiNewFrame();
//	ImGui::Begin("test");
//	//if(test)ImGui::Image(test, { ScreenSize.x/5.0f,ScreenSize.y / 5.0f });
//	ImGui::End();
//	ImGuiRender();
//}
