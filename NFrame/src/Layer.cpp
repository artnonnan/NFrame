#include "NFrame/nfpch.h"
#include "NFrame/Core/Layer.h"
namespace NFrame
{

    Layer::Layer(const std::string& name)
        : m_DebugName(name)
    {
    }

    Layer::~Layer()
    {
    }

} // namespace NFrame