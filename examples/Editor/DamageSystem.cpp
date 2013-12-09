#include "DamageSystem"
#include "ShapeSystem"

#include <QtEntity/EntityManager>

IMPLEMENT_COMPONENT_TYPE(Damage)

DamageSystem::DamageSystem(QtEntity::EntityManager* em)
    : BaseClass(em)
{
}


QVariantMap DamageSystem::toVariantMap(QtEntity::EntityId eid, int)
{
    QVariantMap m;
    Damage* d;
    if(component(eid, d))
    {
        m["energy"] = d->energy();
    }
    return m;    
}


void DamageSystem::fromVariantMap(QtEntity::EntityId eid, const QVariantMap& m, int)
{
    Damage* d;
    if(component(eid, d))
    {
        if(m.contains("energy")) d->setEnergy(m["energy"].toInt());
    }
}


void DamageSystem::step(int frameNumber, int totalTime, int delta)
{
    for(auto i = begin(); i != end(); ++i)
    {
        Shape* shape;
        entityManager()->component(i->first, shape);
    }
}


