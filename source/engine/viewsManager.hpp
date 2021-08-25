#pragma once

#include <vector>

#include "utilities/logger.hpp"
#include "graphics/view.hpp"

namespace engine
{
    class viewsManager: public engine::node 
    {
    public:
        viewsManager(const std::string &name): node(name) {}
        
        void registerView(graphics::view* request);

        inline void setActiveView(const std::string &name)
        { activeView = getChild<graphics::view>(name); }
        inline graphics::view* getActiveView() const
        { return activeView; }
    
    private:
        std::vector<std::shared_ptr<graphics::view>> views;

        graphics::view* activeView = nullptr;
    };
}