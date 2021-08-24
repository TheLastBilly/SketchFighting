#pragma once

#include <vector>
#include <memory>

#include "utilities/utilities.hpp"
#include "utilities/exceptions.hpp"

namespace engine
{
    class node
    {
    public:
        register_exception(node_not_found, "cannot find node with requested name");

    public:
        node(const std::string &name): name(name) {}

        inline void append_child(std::shared_ptr<node> &child)
        {
            child->set_parent(std::shared_ptr<node>(this));
            children.push_back(child);
        }
        inline void remove_child(size_t index)
        {
            get_child(index);
            children.erase(children.begin() + index);
        }
        inline void set_parent(const std::shared_ptr<node> &parent)
        {
            this->parent = parent;
        }
        inline size_t get_children_count() const
        {
            return children.size();
        }
        
        const std::shared_ptr<node> get_child(size_t index) const
        {
            if(children.size() <= index)
                throw_exception_with_msg(utilities::index_out_of_bounds_error, "cannot find index of size " + std::to_string(index));

            return children.at(index);
        }

        const std::shared_ptr<node> get_child(const std::string &name) const
        {
            for(size_t i = 0; i < children.size(); i++)
            {
                if(children.at(i)->get_name() == name)
                    return children.at(i);
            }

            throw_exception_with_msg(node_not_found, "cannot find node \"" + name + "\" on \"" + this->name + "\"");
            return nullptr;
        }

        template<typename type>
        const std::shared_ptr<type> cast()
        {
            return std::shared_ptr<type>(static_cast<type*>(this));
        }

        std::string get_name() const
        {
            return name;
        }

    private:
        std::vector<std::shared_ptr<node>> children;
        std::shared_ptr<node> parent;

        const std::string name;
    };
}