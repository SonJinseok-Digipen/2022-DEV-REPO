#pragma once
/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Project: CS230
Author: Kevin Wright
Creation date: 2/11/2021
-----------------------------------------------------------------*/
#pragma once
#include <string>
#include "Vec2.h"
#include "Texture.h"
#include"TransformMatrix.h"
namespace CS230 {
    class Sprite {
    public:
        Sprite();
        void Load(const std::filesystem::path& spriteInfoFile);
    	void Draw(math::TransformMatrix displayMatrix);
        
        void ShowFrame(int index);
        math::ivec2 GetHotSpot(int index);
        math::ivec2 GetFrameSize() const;
    private:
        Texture texture;
        int currFrame;
        math::ivec2 frameSize;
        math::ivec2 GetFrameTexel(int frameNum) const;
        std::vector<math::ivec2>frameTexel;
        std::vector<math::ivec2> hotSpotList;
    };
}