#ifndef CONFIGDEF_H
#define CONFIGDEF_H
    static const char DB_SECTION_NAME[] = "DB";
    static const char DB_HOST [] ="db_host";
    static const char DB_PORT [] = "db_port";
    static const char DB_NAME [] = "db_name";
    static const char DB_USER [] = "db_user";
    static const char DB_PASSWORD[] = "db_password";
    static const char DB_CONNECTIONAME[] = "db_connectioname";
    static const char DB_DATABASETYPE[] = "db_databasetype";
    //
    static const char ATTRACTIVITY_SECTION_NAME[]   = "ATTRACTIVITY";
    static const char AT_ATTRACTIVITY_UNKNOWN[]     = "attractivity_unknown";
    static const char AT_ATTRACTIVITY_LOW[]         = "attractivity_low";
    static const char AT_ATTRACTIVITY_STANDARD[]    = "attractivity_standard";
    static const char AT_ATTRACTIVITY_HIGH[]        = "attractivity_high";
    static const char AT_ATTRACTIVITY_VERY_HIGH[]   = "attractivity_very_high";
    //
    static const char RANK_SECTION_NAME[]       = "AGENT_RANK";
    static const char RANK_UNKNOWN[]            = "rank_unknown";
    static const char RANK_VERY_BAD[]           = "rank_very_bad";
    static const char RANK_BAD[]                = "rank_bad";
    static const char RANK_NEUTRAL[]            = "rank_neutral";
    static const char RANK_GOOD[]               = "rank_good";
    static const char RANK_VERY_GOOD[]          = "rank_very_good";
    //
    static const char PATHS_SECTION_NAME[]      = "PATHS";
    static const char DEFAULT_EXPORT_PATH[]     = "default_export_path";
    static const char DEFAULT_IMPORT_PATH[]     = "default_import_path";
    //
    static const char LOG_WRITER_NAME[] = "LOG";
    //
    static const char LOG_SECTION_NAME[]  = "LOG";
    static const char LOG_FILE_LOCATION[] = "log_file_location";
    static const char LOG_MODE[] = "log_mode";
    //
    static const int LOG_MODE_MIN = 0;
    static const int LOG_MODE_NORMAL = 1;
    static const int LOG_MODE_VERBOSE = 2;


#endif // CONFIGDEF_H
