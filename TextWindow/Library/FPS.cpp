#include "FPS.h"

int EvoLib::FPS::GetFPS_EvoLib()
{
    // Œ»İ‚ÌFPS‚ğæ“¾‚·‚é
    const float fps = GetFPS();

    // æ“¾‚µ‚½FPS‚ğ•Ô‚·
    return static_cast<int>(fps);
}
