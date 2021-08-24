#pragma once

#include <vector>
#include <memory>

#include "utilities/generics.hpp"
#include "utilities/exceptions.hpp"

namespace engine
{
    class node
    {
    public:
        register_exception(node_not_found, "cannot find node with requested name");
        register_exception(repeated_name_error, "cannot append child with name already in used");

    public:
        node(const std::string &name): name(name) {}

        void appendChild(node* child)
        {
            try
            {
                getChild<node>(child->getName());
                throw_exception_with_msg(repeated_name_error, "cannot append child \"" + child->getName() + "\": name already in used");
            }
            catch(...)
            { }
            
            child->setParent(this);
            children.push_back(child);
        }

        template<typename type>
        inline void appendChild(const std::shared_ptr<type> &child)
        { appendChild(child.get()); }

        inline void removeChild(size_t index)
        {
            getChild<node>(index);
            children.erase(children.begin() + index);
        }
        inline size_t getChildrenCount() const
        {
            return children.size();
        }
        
        template<typename type>
        const type* getChild(size_t index) const
        {
            if(children.size() <= index)
                throw_exception_with_msg(utilities::index_out_of_bounds_error, "cannot find index of size " + std::to_string(index));

            return children.at(index)->cast<type>();
        }

        template<typename type>
        type* getChild(const std::string &name) const
        {
            for(size_t i = 0; i < children.size(); i++)
            {
                if(children.at(i)->getName() == name)
                    return children.at(i)->cast<type>();
            }

            throw_exception_with_msg(node_not_found, "cannot find node \"" + name + "\" on \"" + this->name + "\"");
            return nullptr;
        }

        node* getRoot() const
        {
            node* root = (node*)this;
            
            while(root->parent != nullptr)
                root = root->parent;
            
            return root;
        }

        std::string getName() const
        {
            return name;
        }

        template<typename type>
        type* cast()
        {
            return static_cast<type*>(this);
        }

    protected:
        inline void setParent(node* parent)
        {
            this->parent = parent;
        }

    private:
        std::vector<node*> children;
        node* parent = nullptr;

        const std::string name;
    };
}