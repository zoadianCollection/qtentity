#include <QtTest/QtTest>
#include <QtCore/QObject>
#include <QtEntity/PrefabSystem>
#include <QtEntity/EntityManager>
#include "common.h"

using namespace QtEntity;


class PrefabSystemTest: public QObject
{
    Q_OBJECT

private slots:

    void create()
    {
        EntityManager em;
        PrefabSystem* ps = new PrefabSystem(&em);
        
        TestingSystem* ts = new TestingSystem(&em);
        
        QVariantMap mycomponent;
        mycomponent["myint"] = 12345;

        QVariantMap components;
        QString cn = "Testing";
        components[cn] = mycomponent;
        ps->addPrefab("bla.prefab", components);

        PrefabInstance* instance;

        QVariantMap props;
        props["path"] = "bla.prefab";
        em.createComponent(1, instance, props);

        auto test = em.component<Testing>(1);
        QVERIFY(test != nullptr);
        QCOMPARE(12345, test->myInt());

    }



    void update()
    {
        EntityManager em;
        PrefabSystem* ps = new PrefabSystem(&em);
        
        TestingSystem* ts = new TestingSystem(&em);
       
        QVariantMap mycomponent;
        mycomponent["myint"] = 12345;

        QVariantMap components;
        QString cn = "Testing";
        components[cn] = mycomponent;
        ps->addPrefab("bla.prefab", components);

        PrefabInstance* instance;

        QVariantMap props;
        props["path"] = "bla.prefab";
        em.createComponent(1, instance, props);

        auto test = em.component<Testing>(1);
        QVERIFY(test != nullptr);
        QCOMPARE(12345, test->myInt());

        mycomponent["myint"] = 6789;
        components[cn] = mycomponent;
        ps->updatePrefab("bla.prefab", components, true);
        QCOMPARE(6789, test->myInt());
    }

    void destroyComponent()
    {
        EntityManager em;
        PrefabSystem* ps = new PrefabSystem(&em);
        
        TestingSystem* ts = new TestingSystem(&em);
        
        QVariantMap mycomponent;
        mycomponent["myint"] = 12345;

        QVariantMap components;
        QString cn = "Testing";
        components[cn] = mycomponent;
        ps->addPrefab("bla.prefab", components);

        PrefabInstance* instance;

        QVariantMap props;
        props["path"] = "bla.prefab";
        em.createComponent(1, instance, props);

        auto test = em.component<Testing>(1);
        QVERIFY(test != nullptr);
        QCOMPARE(12345, test->myInt());
        auto x = em.component<Testing>(1);
        QVERIFY(x);
        components.clear();
        ps->updatePrefab("bla.prefab", components, true);

        auto y = em.component<Testing>(1);
        QVERIFY(y == nullptr);
    }


    void add()
    {
        EntityManager em;
        PrefabSystem* ps = new PrefabSystem(&em);
        
        TestingSystem* ts = new TestingSystem(&em);
        
        QVariantMap mycomponent;
        mycomponent["myint"] = 12345;

        QVariantMap components;
        QString cn = "Testing";

        ps->addPrefab("bla.prefab", components);

        PrefabInstance* instance;

        QVariantMap props;
        props["path"] = "bla.prefab";
        em.createComponent(1, instance, props);

        auto test = em.component<Testing>(1);
        QVERIFY(test == nullptr);

        mycomponent["myint"] = 6789;
        components[cn] = mycomponent;
        components[cn] = mycomponent;
        ps->updatePrefab("bla.prefab", components, true);
        test = em.component<Testing>(1);
        QVERIFY(test != nullptr);
        QCOMPARE(6789, test->myInt());
    }

};
