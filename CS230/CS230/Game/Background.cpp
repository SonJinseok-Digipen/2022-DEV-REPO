#include"Background.h"
#include"..\Engine\Camera.h"
void Background::Add(const std::filesystem::path& filepath,int level)
{
	backgrounds.push_back(ParallaxInfo{ filepath,level });
}

void Background::Unload()
{
	backgrounds.clear();
}

void Background::Draw(const CS230::Camera& camera)
{
	auto size = backgrounds.size()-1;
	for (int i = size; i >=0; i--)
	{
		backgrounds[i].texture.Draw(-camera.GetPosition() / backgrounds[i].level);
	}
	
}

math::ivec2 Background::Size()
{
	return backgrounds[0].texture.GetSize();
}
