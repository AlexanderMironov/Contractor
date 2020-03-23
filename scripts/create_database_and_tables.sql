#
#       execute this script in terminal using the following command:
#       mysql -u cynic -porient < create_database_and_tables.sql
#
CREATE DATABASE IF NOT EXISTS contractor CHARACTER SET utf8 COLLATE utf8_general_ci;
#
USE contractor;
#
CREATE TABLE IF NOT EXISTS `agents_tbl`(`id` int(11) NOT NULL AUTO_INCREMENT,
                                        `name` varchar(255) NOT NULL,
                                        `e_mail` varchar(255) NOT NULL,
                                        `phone_1` varchar(100) NOT NULL,
                                        `phone_2` varchar(100),
                                        `description` varchar(2000),
                                        `web_profile` varchar(400),
                                        `id_agency` int(11)  NOT NULL,
                                        `level` int(11) NOT NULL DEFAULT -1,
                                        CONSTRAINT e_mail_unique UNIQUE (e_mail),
                                        PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
CREATE TABLE IF NOT EXISTS `countries_tbl`(`id`   int(11)      NOT NULL AUTO_INCREMENT,
                                           `name` varchar(255) NOT NULL,
                                           CONSTRAINT name_unique UNIQUE (name),
                                           PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
CREATE TABLE IF NOT EXISTS `agencies_tbl`(`id`   int(11)      NOT NULL AUTO_INCREMENT,
                                          `name` varchar(255) NOT NULL,
                                          `description` varchar(2000),
                                          CONSTRAINT name_unique UNIQUE (name),
                                          PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
CREATE TABLE IF NOT EXISTS `towns_tbl`(`id`   int(11)      NOT NULL AUTO_INCREMENT,
                                        `name` varchar(255) NOT NULL,
                                        CONSTRAINT name_unique UNIQUE (name),
                                        PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
CREATE TABLE IF NOT EXISTS `skills_tbl`(`id`   int(11)   NOT NULL AUTO_INCREMENT,
                                       `name` varchar(255) NOT NULL,
                                       CONSTRAINT name_unique UNIQUE (name),
                                       PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
CREATE TABLE IF NOT EXISTS `offers_tbl`(`id`   int(11)   NOT NULL AUTO_INCREMENT,
                                        `creation_date`     date            NOT NULL,
                                        `pos_title`         varchar(255)    NOT NULL,
                                        `description`       varchar(2000)   NOT NULL,
                                        `comments`          varchar(2000),
                                        `id_country`        int(11)         NOT NULL,
                                        `id_town`           int(11)         NOT NULL DEFAULT -1,
                                        `id_agent`          int(11)         NOT NULL,
                                        `id_status`         int(11)         NOT NULL DEFAULT -1,
                                        `attractivity`      int(11)         NOT NULL DEFAULT -1,
                                        `rate`              int(11)         NOT NULL DEFAULT 0,
                                        PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
CREATE TABLE IF NOT EXISTS `offers_skills_tbl`(`id`   int(11)   NOT NULL AUTO_INCREMENT,
                                        `id_offer`          int(11)         NOT NULL,
                                        `id_skill`          int(11)         NOT NULL,
                                        CONSTRAINT offer_skill_unique UNIQUE (id_offer, id_skill),
                                        PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
CREATE TABLE IF NOT EXISTS `statuses_tbl`(`id`   int(11)      NOT NULL AUTO_INCREMENT,
                                       `name` varchar(255) NOT NULL,
                                        CONSTRAINT name_unique UNIQUE (name),
                                        PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
#
# just example
#
INSERT INTO statuses_tbl (name) values ("no CV");
INSERT INTO statuses_tbl (name) values ("CV sended");
INSERT INTO statuses_tbl (name) values ("Spoke with agent");
INSERT INTO statuses_tbl (name) values ("Interview assigned");
INSERT INTO statuses_tbl (name) values ("Rejected");
INSERT INTO statuses_tbl (name) values ("Expired");
INSERT INTO statuses_tbl (name) values ("Waiting contract");
#
CREATE TABLE IF NOT EXISTS `colleagues_tbl`(`id` int(11) NOT NULL AUTO_INCREMENT,
                                        `name` varchar(255) NOT NULL,
                                        `e_mail` varchar(255) NOT NULL,
                                        CONSTRAINT e_mail_unique UNIQUE (e_mail),
                                        PRIMARY KEY (`id`)) ENGINE=InnoDB DEFAULT CHARSET=utf8;
