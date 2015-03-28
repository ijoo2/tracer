#include "bvolume.h"

using namespace std;

BVNode::BVNode()
{
    objects = vector<SceneObject *>();
    bounds = pair<Vector3, Vector3>();
    dim = 0;
    lchild = NULL;
    rchild = NULL;
}

BVNode::BVNode(vector<SceneObject *> & objs, pair<Vector3, Vector3> & b, int d)
{
    objects = objs;
    bounds = b;
    dim = d;
    lchild = NULL;
    rchild = NULL;
}

bool BVNode::intersect(Ray * ray)
{
    bool xcond, ycond, zcond;
    double xp, yp, zp;
    
    xp = ray->anchor.x;
    yp = ray->anchor.y;
    zp = ray->anchor.z;

    double tx0, ty0, tz0, tx1, ty1, tz1;
    
    if (ray->dir.x != 0)
    {
        tx0 = (bounds.first.x-xp)/ray->dir.x;    
        tx1 = (bounds.second.x-xp)/ray->dir.x;
    }
    else
    {
        if (ray->dir.x >= bounds.first.x && ray->dir.x <= bounds.second.x)
        {
            tx0 = 1.0;
            tx1 = 1.0;
        }
    }
    
    if (ray->dir.y != 0)
    {
        ty0 = (bounds.first.y-yp)/ray->dir.y;
        ty1 = (bounds.second.y-yp)/ray->dir.y;
    }
    else
    {
        if (ray->dir.y >= bounds.first.y && ray->dir.y <= bounds.second.y)
        {
            ty0 = 1.0;
            ty1 = 1.0;
        }
    }

    if (ray->dir.z != 0)
    {
        tz0 = (bounds.first.z-zp)/ray->dir.z;
        tz1 = (bounds.second.z-zp)/ray->dir.z;
    }
    else
    {
        if (ray->dir.z >= bounds.first.z && ray->dir.z <= bounds.second.z)
        {
            tz0 = 1.0;
            tz1 = 1.0;
        }
    }

    xcond = ((tx0 > 0) && (tx0 < ray->t)) || ((tx1 > 0) && (tx1 < ray->t));
    ycond = ((ty0 > 0) && (ty0 < ray->t)) || ((ty1 > 0) && (ty1 < ray->t));
    zcond = ((tz0 > 0) && (tz0 < ray->t)) || ((tz1 > 0) && (tz1 < ray->t));

    //cout << xcond << ycond << zcond << endl;

    return (xcond && ycond && zcond);
}

BVolume::BVolume()
{
    root = NULL;
}


BVolume::BVolume(vector<SceneObject *> objs)
{
    pair<Vector3, Vector3> b = getBounds(objs);
    root = new BVNode(objs, b, 0);
    buildTree(root);
}

BVolume::BVolume(BVolume const & other)
{
    root = _copy(other.root);
}

BVolume const & BVolume::operator=(BVolume const & other)
{
    if (this != &other)
    {
        _clear(root);
        root = _copy(other.root);
    }

    return *this;
}

BVolume::~BVolume()
{
    _clear(root);
}

BVNode * BVolume::_copy(BVNode * croot)
{
    BVNode * temp;
    if (croot != NULL)
    {
        temp = new BVNode(croot->objects, croot->bounds, croot->dim);
        temp->lchild = _copy(croot->lchild);
        temp->rchild = _copy(croot->rchild);
    }
    else
        temp = NULL;
    return temp;

}

void BVolume::_clear(BVNode *& croot)
{
    if (croot != NULL)
    {
        _clear(croot->lchild);
        _clear(croot->rchild);
        
        delete croot;
        croot = NULL;
    }
}

pair<Vector3, Vector3> getBounds(vector<SceneObject *> objects)
{
    Vector3 pMin, pMax;
    double gMinX, gMinY, gMinZ, gMaxX, gMaxY, gMaxZ;
    gMinX = gMinY = gMinZ = INT_MAX;
    gMaxX = gMaxY = gMaxZ = -INT_MAX;

    for each(auto object in objects)
    {
        if (object->str() == "Plane")
            continue;

        if (object->minX <= gMinX)
            gMinX = object->minX;
        else if (object->maxX > gMaxX)
            gMaxX = object->maxX;
        else {}

        if (object->minY <= gMinY)
            gMinY = object->minY;
        else if (object->maxY > gMaxY)
            gMaxY = object->maxY;
        else {}

        if (object->minZ <= gMinZ)
            gMinZ = object->minZ;
        else if (object->maxZ > gMaxZ)
            gMaxZ = object->maxZ;
        else {}

    }
    pMin = Vector3(gMinX, gMinY, gMinZ);
    pMax = Vector3(gMaxX, gMaxY, gMaxZ);
    pair<Vector3, Vector3> p = pair<Vector3, Vector3>(pMin, pMax);
    return p;
}

void BVolume::buildTree(BVNode * croot) const
{
    vector<SceneObject *> objs = croot->objects;
    if (objs.size() <= 1)
        return;
    
    int dim = croot->dim;
    pair<Vector3, Vector3> bounds = croot->bounds;
    double split = (bounds.second[dim] + bounds.first[dim])/2.0;

    //cout << "Splitting on dimension " << dim << " at " << split << endl;
    vector<SceneObject *> left, right;
    for each (auto object in objs)
    {
        if (object->str() == "Plane")
        {
            left.push_back(object);
            right.push_back(object);
            continue;
        }

        if (object->operator[](dim) < split)
            left.push_back(object);
        else
            right.push_back(object);
    }

    pair<Vector3, Vector3> lbounds = getBounds(left);
    pair<Vector3, Vector3> rbounds = getBounds(right);
    croot->lchild = new BVNode(left, lbounds, (dim+1) % 3);
    croot->rchild = new BVNode(right, rbounds, (dim+1) % 3);

    //cout << "left child contains " << left.size() << " objects.\n";
    //cout << "right child contains " << right.size() << " objects.\n\n";
    //system("pause");
    if (objs.size() != left.size())
        buildTree(croot->lchild);
    if (objs.size() != right.size())
        buildTree(croot->rchild);
}

bool BVolume::intersect(Ray * ray)
{
    queue<BVNode *> q;
    q.push(root);
    while (!q.empty())
    {
        BVNode * croot = q.front();
        q.pop();
        if (croot == NULL)
            continue;

        if (croot->intersect(ray))
        {
            candidates = croot->objects;
            q.push(croot->lchild);
            q.push(croot->rchild);
        }

    }
    return (candidates.size() != 0);
}


