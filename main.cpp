#include "mainwindow.h"
#include <QApplication>
#include <QTextStream>
//
#include "config/configuration.h"
#include "config/configdef.h"
//
#include "logger/logwriter.h"
#include "logger/loggermanager.h"
//
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
    str<<"configuration initialized"<<endl;
    //
    if (LoggerManager::getInstance().createLogger(LOG_WRITER_NAME, Configuration::getInstance().getLogFileName()) == false){
        str<<"can not create log-file "<<LOG_FILE_LOCATION<<" Stop\n";
        return -1;
    };
    //
    LogWriter* ptr_log = LoggerManager::getInstance().getWriter(LOG_WRITER_NAME);
    //
    (*ptr_log)<<"Logger initialized"<<"\n";
    //
    const bool b_init_pool = DbConnectionManager::getInstance().init(2,
                                                                     Configuration::getInstance().getDBDatabaseType(),
                                                                     Configuration::getInstance().getDBHostName(),
                                                                     Configuration::getInstance().getDBName(),
                                                                     Configuration::getInstance().getDBUserName(),
                                                                     Configuration::getInstance().getDBUserPassword(),
                                                                     Configuration::getInstance().getDBPort());
    if (false == b_init_pool){
        (*ptr_log)<<"Can not initialize DB connection pool"<<"\n";
        return -1;
    };
    (*ptr_log)<<"DB connection pool initialized"<<"\n";
    //
    if (AgencyProcessor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize agency processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"agency processor initialized"<<"\n";
    //
    if (AgentProcessor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize agent processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"agent processor initialized"<<"\n";
    //
    if (CountryProcessor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize country processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"country processor initialized"<<"\n";
    //
    if (OfferSkillProcesor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize offer&skill processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"offer&skill processor initialized"<<"\n";
    //
    if (SkillProcessor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize skill processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"skill processor initialized"<<"\n";
    //
    if (TownProcessor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize town processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"town processor initialized"<<"\n";
    //
    if (StatusProcessor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize status processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"status processor initialized"<<"\n";
    //
    if (OfferProcessor::getInstance().init() == false) {
        (*ptr_log)<<"Can not initialize offer processor"<<"\n";
        return -1;
    };
    (*ptr_log)<<"offer processor initialized"<<"\n";
    //
    MainWindow w;
    w.show();
    int i_res = a.exec();
    return i_res;
}
