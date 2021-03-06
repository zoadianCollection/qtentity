#include <QtTest/QtTest>
#include <QtCore/QObject>
#include <QtEntity/EntityManager>
#include <QtEntity/SimpleEntitySystem>
#include "common.h"

using namespace QtEntity;

class EntitySystemTest: public QObject
{
    Q_OBJECT
private slots:

  
    void createAndFetch()
    {
        EntityManager em;
        TestingSystem* ts = new TestingSystem(&em);

		QVariantMap m;
		m["myint"] = 666;

        void* c = ts->createComponent(1, m);

        void* c2 = ts->component(1);
        QVERIFY(c == c2);
        QVERIFY(ts->component(1) != nullptr);

        void* c3 = ts->component(2);
        QVERIFY(c3 == nullptr);

        Testing* tr = static_cast<Testing*>(c);
        QVERIFY(tr != nullptr);
        QCOMPARE(tr->myInt(), 666);

    }

    void destruct()
    {
        EntityManager em;
        TestingSystem* ts = new TestingSystem(&em);
        void* c = ts->createComponent(1);
        void* c2 = ts->component(1);
        QVERIFY(c == c2);
        QVERIFY(ts->component(1) != nullptr);
        ts->destroyComponent(1);
        QVERIFY(ts->component(1) == nullptr);
        void* c3 = ts->component(1);
        QVERIFY(c3 == nullptr);
    }

    void erase()
    {
        EntityManager em;
        TestingSystem* ts = new TestingSystem(&em);
        QVariantMap m;
		m["myint"] = 1;
        ts->createComponent(1, m);
        m["myint"] = 2;
        ts->createComponent(2, m);
        m["myint"] = 3;
        ts->createComponent(3, m);
        for(auto i = ts->begin(); i != ts->end(); ++i)
        {
            if(i->second->myInt() == 2)
            {
                ts->erase(i);
                break;
            }
        }
        int sum = 0;
        for(auto i = ts->begin(); i != ts->end(); ++i)
        {
            sum += i->second->myInt();
        }
        QCOMPARE(sum, 4);

        QCOMPARE(ts->count(), (size_t)2);
        QVERIFY(ts->component(2) == nullptr);
    }

    void clear()
    {
        EntityManager em;
        TestingSystem* ts = new TestingSystem(&em);
        ts->createComponent(1);
        ts->createComponent(2);        
        ts->createComponent(3);
        ts->clear();
        QCOMPARE(ts->count(), (size_t)0);
        ts->createComponent(1);
        QCOMPARE(ts->count(), (size_t)1);
    }

    void iteratorTest1()
    {
        EntityManager em;
        TestingSystem* ts = new TestingSystem(&em);
        ts->createComponent(1);
        auto i = ts->pbegin();
        void* o = *i;
        void* o2 = ts->component(1);
        QCOMPARE(o, o2);

    }

    void iteratorTest2()
    {
        EntityManager em;
        TestingSystem* ts = new TestingSystem(&em);
        QVariantMap m;
        for(int i = 1; i <= 5; ++i)
        {
            m["myint"] = i;
            ts->createComponent(i, m);
        }
        int sum = 0;
        auto end = ts->pend();
        for(auto i = ts->pbegin(); i != end; ++i)
        {
            void* o = *i;
            Testing* t = static_cast<Testing*>(o);
            sum += t->myInt();
        }

        QCOMPARE(sum, 15);
    }
};
