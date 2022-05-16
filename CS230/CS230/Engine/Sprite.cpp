#include"Sprite.h"
CS230::Sprite::Sprite()
{

}

void CS230::Sprite::Load(const std::filesystem::path& texturePath)
{
	texture.Load(texturePath);
		
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, math::ivec2 hotSpotPosition)
{
	texture.Load(texturePath);
	hotSpotList.push_back( hotSpotPosition);
}

void CS230::Sprite::Load(const std::filesystem::path& texturePath, std::initializer_list<math::ivec2> hotspots)
{
	texture.Load(texturePath);
	for (const math::ivec2& hotstpot : hotspots)
	{
		hotSpotList.push_back(hotstpot);
	}
}

void CS230::Sprite::Draw(math::TransformMatrix displayMatrix)
{
	texture.Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)));
	
}

math::ivec2 CS230::Sprite::GetTextureSize()
{
	return texture.GetSize();
}

math::ivec2 CS230::Sprite::GetHotSpot(int index) 
{
	return hotSpotList[index];
}