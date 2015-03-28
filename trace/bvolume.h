#pragma once

#include <vector>
#include "vector3.h"
#include "sceneobject.h"
#include "ray.h"
#include <utility>
#include <queue>

#define INFINITY 

class BVNode : public SceneObject
{
    public:
        BVNode();
        BVNode(std::vector<SceneObject *> & objs, std::pair<Vector3, Vector3> & b, int d);
        bool intersect(Ray *ray);

        std::vector<SceneObject *> objects;
        BVNode * lchild;
        BVNode * rchild;
        std::pair<Vector3, Vector3> bounds;
        int dim;

};

class BVolume
{
    public:
        BVolume();
        BVolume(std::vector<SceneObject *> objs);
        BVolume(BVolume const & other);
        BVolume const & operator=(BVolume const & other);
        ~BVolume();
        BVNode * root;
        std::vector<SceneObject *> candidates;
        void buildTree();

        bool intersect(Ray * ray);
    
    private:
        void buildTree(BVNode * croot) const;
        void _clear(BVNode *& croot);
        BVNode * _copy(BVNode * croot);
        
};

std::pair<Vector3, Vector3> getBounds(std::vector<SceneObject *> objects);