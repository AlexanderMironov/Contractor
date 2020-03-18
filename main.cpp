#include "mainwindow.h"
#include <QApplication>
//
#include "config/configuration.h"
#include "dbsupport/dbconnectionmanager.h"
#include "processor/agencyprocessor.h"
#include "processor/agentprocessor.h"
#include "processor/countryprocessor.h"
#include "processor/townprocessor.h"
#include "processor/offerprocessor.h"
#include "processor/offerskillprocesor.h"
#include "processor/skillprocessor.h"
#include "processor/statusprocessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //init configuration
    if (Configuration::getInstance().init() == false)
    {
        return -1;
    };
    //
    const bool b_init_pool = DbConnectionManager::getInstance().init(2,
                                                                     Configuration::getInstance().getDBDatabaseType(),
                                                                     Configuration::getInstance().getDBHostName(),
                                                                     Configuration::getInstance().getDBName(),
                                                                     Configuration::getInstance().getDBUserName(),
                                                                     Configuration::getInstance().getDBUserPassword(),
                                                                     Configuration::getInstance().getDBPort());
    if (false == b_init_pool){
        return -1;
    };
    //
    if (AgencyProcessor::getInstance().init() == false) {
        return -1;
    };
    //
    if (AgentProcessor::getInstance().init() == false) {
        return -1;
    };
    //
    if (CountryProcessor::getInstance().init() == false) {
        return -1;
    };
    //
    if (OfferSkillProcesor::getInstance().init() == false) {
        return -1;
    };
    //
    if (SkillProcessor::getInstance().init() == false) {
        return -1;
    };
    //
    if (TownProcessor::getInstance().init() == false) {
        return -1;
    };
    //
    if (StatusProcessor::getInstance().init() == false) {
        return -1;
    };
    //
    if (OfferProcessor::getInstance().init() == false) {
        return -1;
    };
    //
    MainWindow w;
    w.show();

    return a.exec();
}
