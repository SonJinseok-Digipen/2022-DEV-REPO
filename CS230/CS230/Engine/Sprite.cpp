#include"Sprite.h"
#include<fstream>

#include "Engine.h"

CS230::Sprite::Sprite()
{

}

void CS230::Sprite::Load(const std::filesystem::path& spriteInfoFile) {
	hotSpotList.clear();
	frameTexel.clear();

	if (spriteInfoFile.extension() != ".spt") {
		throw std::runtime_error("Bad Filetype.  " + spriteInfoFile.generic_string() + " not a sprite info file (.spt)");
	}
	std::ifstream inFile(spriteInfoFile);

	if (inFile.is_open() == false) {
		throw std::runtime_error("Failed to load " + spriteInfoFile.generic_string());
	}

	std::string text;
	inFile >> text;
	texture.Load(text);
	frameSize = texture.GetSize();

	inFile >> text;
	while (inFile.eof() == false) {
		if (text == "FrameSize") {
			inFile >> frameSize.x;
			inFile >> frameSize.y;
		}
		else if (text == "NumFrames") {
			int numFrames;
			inFile >> numFrames;
			for (int i = 0; i < numFrames; i++) {
				frameTexel.push_back({ frameSize.x * i, 0 });
			}
		}
		else if (text == "Frame") {
			int frameLocationX, frameLocationY;
			inFile >> frameLocationX;
			inFile >> frameLocationY;
			frameTexel.push_back({ frameLocationX, frameLocationY });
		}
		else if (text == "HotSpot") {
			int hotSpotX, hotSpotY;
			inFile >> hotSpotX;
			inFile >> hotSpotY;
			hotSpotList.push_back({ hotSpotX, hotSpotY });
		}
		else {
			Engine::GetLogger().LogError("Unknown spt command " + text);
		}
		inFile >> text;
	}
	if (frameTexel.empty() == true) {
		frameTexel.push_back({ 0,0 });
	}
}





void CS230::Sprite::ShowFrame(int index)
{
	currFrame = index;
}



void CS230::Sprite::Draw(math::TransformMatrix displayMatrix)
{
	texture.Draw(displayMatrix * math::TranslateMatrix(-GetHotSpot(0)),frameTexel[currFrame],GetFrameSize());
	
}

math::ivec2 CS230::Sprite::GetHotSpot(int index) 
{
	return hotSpotList[index];
}

math::ivec2 CS230::Sprite::GetFrameSize() const
{
	return frameSize;
}

math::ivec2 CS230::Sprite::GetFrameTexel(int frameNum) const
{
	if(currFrame >= 0 && currFrame <= frameTexel.size())
	{
		throw std::runtime_error("You try to access wrong frame");
	}
	return frameTexel[frameNum];
}

	
	
