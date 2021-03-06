#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::TextureSetup
    @ingroup Gfx
    @brief setup object for textures and render targets
*/
#include "Resource/Locator.h"
#include "Resource/Id.h"
#include "Gfx/Core/Enums.h"
#include "Gfx/Core/GfxConfig.h"
#include "Gfx/Core/SamplerState.h"
#include "Gfx/Core/ClearState.h"
#include "Gfx/Attrs/ImageDataAttrs.h"

namespace Oryol {
    
class TextureSetup {
public:
    /// asynchronously load from file
    static TextureSetup FromFile(const Locator& loc, Id placeholder=Id::InvalidId());
    /// asynchronously load from file
    static TextureSetup FromFile(const Locator& loc, const TextureSetup& blueprint=TextureSetup(), Id placeholder=Id::InvalidId());
    /// setup texture from raw pixel data
    static TextureSetup FromPixelData(int w, int h, int numMipMaps, TextureType::Code type, PixelFormat::Code fmt, const TextureSetup& blueprint=TextureSetup());
    /// setup empty texture (usually for dynamic streaming of CPU generated texture data)
    static TextureSetup Empty(int w, int h, int numMipMaps, TextureType::Code type, PixelFormat::Code fmt, Usage::Code Usage);
    /// setup as absolute-size render target
    static TextureSetup RenderTarget(int w, int h);
    /// setup as render target with size relative to current display size
    static TextureSetup RelSizeRenderTarget(float relWidth, float relHeight);
    /// create render target with shared depth buffer
    static TextureSetup SharedDepthRenderTarget(const Id& depthRenderTarget);

    /// default constructor
    TextureSetup();
    /// return true if texture should be setup from a file
    bool ShouldSetupFromFile() const;
    /// return true if texture should be setup from raw pixel data
    bool ShouldSetupFromPixelData() const;
    /// return true if texture should be created empty
    bool ShouldSetupEmpty() const;
    /// return true if texture should be setup as render target
    bool ShouldSetupAsRenderTarget() const;
    /// return true if rel-size render target
    bool IsRelSizeRenderTarget() const;
    /// return true if render target has depth (shared or non-shared)
    bool HasDepth() const;
    /// return true if render target with shared depth buffer
    bool HasSharedDepth() const;

    /// intended usage
    Usage::Code TextureUsage;
    /// texture type (default is Texture2D)
    TextureType::Code Type;
    /// the width in pixels (only if absolute-size render target)
    int Width;
    /// the height in pixels (only if absolute-size render target)
    int Height;
    /// display-relative width (only if screen render target)
    float RelWidth;
    /// display-relative height (only if screen render target)
    float RelHeight;
    /// number of mipmaps (default is 1, only for FromPixelData)
    int NumMipMaps;
    /// the color pixel format (only if render target)
    PixelFormat::Code ColorFormat;
    /// the depth pixel format (only if render target, InvalidPixelFormat if render target should not have depth buffer)
    PixelFormat::Code DepthFormat;
    /// resource id of render target which owns the depth buffer (only if render target with shared depth buffer)
    Id DepthRenderTarget;

    /// sampler state
    SamplerState Sampler;
    /// optional clear hint for render targets, this is used as hint by D3D12 to optimize clears
    ClearState ClearHint;

    /// resource locator
    class Locator Locator;
    /// resource placeholder
    Id Placeholder;

    /// optional image surface offsets and sizes
    ImageDataAttrs ImageData;

private:
    bool setupFromFile : 1;
    bool setupFromPixelData : 1;
    bool setupEmpty : 1;
    bool setupAsRenderTarget : 1;
    bool isRelSizeRenderTarget : 1;
    bool hasSharedDepth : 1;
    bool hasMipMaps : 1;
};
    
} // namespace Oryol
