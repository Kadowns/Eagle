//
// Created by Novak on 05/06/2019.
//

#include <algorithm>

#include "eagle/core/LayerStack.h"
#include <eagle/core/Log.h>

_EAGLE_BEGIN

void LayerStack::emplace_back(std::shared_ptr<Layer> layer) {
    EG_CORE_TRACE("Emplacing back a new layer!");
    m_layers.emplace_back(layer);

    if (!m_initialized)
        return;

    layer->handle_attach();
}

void LayerStack::pop_layer(std::shared_ptr<Layer> layer) {
    EG_CORE_TRACE("Popping a layer!");
    auto it = std::find(m_layers.begin(), m_layers.end(), layer);
    if (it != m_layers.end()){
        m_layers.erase(it);

        if (!m_initialized)
            return;

        layer->handle_deattach();
        EG_CORE_TRACE("Layer popped!");
    } else {
        EG_CORE_TRACE("Layer not found!");
    }
}

LayerStack::LayerStack(const std::vector<std::shared_ptr<Layer>>& layers) {
    emplace(layers);
}

void LayerStack::emplace_front(std::shared_ptr<Layer> layer) {
    EG_CORE_TRACE("Emplacing front a new layer!");
    m_layers.emplace(m_layers.begin(), layer);

    if (!m_initialized)
        return;

    layer->handle_attach();
}

void LayerStack::emplace(const std::vector<std::shared_ptr<Layer>>& layers) {
    for (auto& it :layers){
        emplace_back(it);
    }
}

void LayerStack::init() {

    if (m_initialized) return;

    m_initialized = true;
    for (auto& layer : m_layers){
        layer->handle_attach();
    }
}

void LayerStack::deinit() {
    if (!m_initialized) return;

    for (auto& layer : m_layers){
        pop_layer(layer);
    }

    m_initialized = false;
}


_EAGLE_END

