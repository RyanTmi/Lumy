#pragma once

namespace Lumy
{
    enum class AssetType
    {
        None,
        Audio,
        Mesh,
        Scene,
        Texture,
    };

    class Asset
    {
    private:
        AssetType m_Type;
    };
}
