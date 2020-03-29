#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>
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
    QTextStream str(stdout);
    QApplication a(argc, argv);
    //init configuration
    if (Configuration::getInstance().init() == false)
    {
        str<<"Can not initialize configuration"<<endl;
        return -1;
    };
    str<<"agency processor initialized"<<endl;
    //
    const bool b_init_pool = DbConnectionManager::getInstance().init(2,
                                                                     Configuration::getInstance().getDBDatabaseType(),
                                                                     Configuration::getInstance().getDBHostName(),
                                                                     Configuration::getInstance().getDBName(),
                                                                     Configuration::getInstance().getDBUserName(),
                                                                     Configuration::getInstance().getDBUserPassword(),
                                                                     Configuration::getInstance().getDBPort());
    if (false == b_init_pool){
        str<<"Can not initialize DB connection pool"<<endl;
        return -1;
    };
    str<<"DB connection pool initialized"<<endl;
    //
    if (AgencyProcessor::getInstance().init() == false) {
        str<<"Can not initialize agency processor"<<endl;
        return -1;
    };
    str<<"agency processor initialized"<<endl;
    //
    if (AgentProcessor::getInstance().init() == false) {
        str<<"Can not initialize agent processor"<<endl;
        return -1;
    };
    str<<"agent processor initialized"<<endl;
    //
    if (CountryProcessor::getInstance().init() == false) {
        str<<"Can not initialize country processor"<<endl;
        return -1;
    };
    str<<"country processor initialized"<<endl;
    //
    if (OfferSkillProcesor::getInstance().init() == false) {
        str<<"Can not initialize offer&skill processor"<<endl;
        return -1;
    };
    str<<"offer&skill processor initialized"<<endl;
    //
    if (SkillProcessor::getInstance().init() == false) {
        str<<"Can not initialize skill processor"<<endl;
        return -1;
    };
    str<<"skill processor initialized"<<endl;
    //
    if (TownProcessor::getInstance().init() == false) {
        str<<"Can not initialize town processor"<<endl;
        return -1;
    };
    str<<"town processor initialized"<<endl;
    //
    if (StatusProcessor::getInstance().init() == false) {
        str<<"Can not initialize status processor"<<endl;
        return -1;
    };
    str<<"status processor initialized"<<endl;
    //
    if (OfferProcessor::getInstance().init() == false) {
        str<<"Can not initialize offer processor"<<endl;
        return -1;
    };
    str<<"offer processor initialized"<<endl;
    //
    MainWindow w;
    w.show();

    return a.exec();
}
