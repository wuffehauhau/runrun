/*
 * Copyright (C) Jani Salo 2013 -
 * All rights reserved unless otherwise stated.
 *
 * Kukkaruukku framework.
 *
 * File:    vertexattributeinfo.hpp
 * Created: 2013-02-02
 * Authors: Jani Salo
 */

/*
 * A container for vertex attribute properties.
 */

#ifndef RUUKKU_VERTEXATTRIBUTEINFO_HPP
#define RUUKKU_VERTEXATTRIBUTEINFO_HPP

#include <string>
#include <GL/glew.h>

#include "../opengl/glutil.hpp"

namespace ruukku {
    class VertexAttributeInfo {
        public:
            // Constructs a new vertex attribute info with size in components,
            // component type, attribute index and attribute name in shader.
            VertexAttributeInfo (
                const std::size_t size,
                const GLenum      type,
                const GLuint      index,
                const std::string name
            ) : size_(size), type_(type), index_(index), name_(name) {}

        public:
            std::size_t        getSize()  const { return size_; }
            GLenum             getType()  const { return type_; }
            GLuint             getIndex() const { return index_; }
            const std::string& getName()  const { return name_; }

        public:
            std::size_t getByteSize() const { return size_ * GLUtil::getByteSizefromEnum(type_); }

        public:
            bool operator ==(const VertexAttributeInfo& info) const { return size_ == info.size_ && type_ == info.type_ && index_ == info.index_ && name_ == info.name_; }
            bool operator !=(const VertexAttributeInfo& info) const { return !(*this == info); }

        private:
            std::size_t size_;
            GLenum      type_;
            GLuint      index_;
            std::string name_;
    };
};

#endif /* RUUKKU_VERTEXATTRIBUTEINFO_HPP */

