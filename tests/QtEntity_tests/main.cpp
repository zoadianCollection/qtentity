#include <QtTest/QtTest>

#include "test_entitymanager.h"
#include "test_entitysystem.h"
#include "test_pooledentitysystem.h"
#include "test_prefabsystem.h"
#include "test_scripting.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setAttribute(Qt::AA_Use96Dpi, true);

    { EntitySystemTest t; if(0 != QTest::qExec(&t, argc, argv)) return 1; }
    { EntityManagerTest t; if(0 != QTest::qExec(&t, argc, argv)) return 1; }
    { PooledEntitySystemTest t; if(0 != QTest::qExec(&t, argc, argv)) return 1; }
    { PrefabSystemTest t; if(0 != QTest::qExec(&t, argc, argv)) return 1; }
    { ScriptingTest t; if(0 != QTest::qExec(&t, argc, argv)) return 1; }

    return 0;
}
