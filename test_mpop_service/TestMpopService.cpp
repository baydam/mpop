#include "TestMpopService.h"
#include "mpopservice.h"
#include "response.h"
#include "request.h"
#include <QDebug>


// called before the first test function is executed
void TestMpopService::init_TestCase()
{
    Config config;
    MPopService::load_config_from_env_vars(config);
    // FIXME: Will attempt to connect to a MySQL database
    // Relies on it.
    this->facade = QSharedPointer<Facade>(new Facade(config));

    this->is_mysql_supported = this->facade->isDatabaseReady();

    if (this->is_mysql_supported) {
        this->facade->deleteAllFromDatabase();
    }
    // TODO: Perhaps clean all users that we've created in previous tests, as well as all their answers
}


// called after the last test function was executed
void TestMpopService::cleanupTestCase()
{
    if (this->is_mysql_supported) {
        this->facade->deleteAllFromDatabase();
    }
    // No need to delete the MPopService
    // Though, once the destructor is called, the MySQL connection will close.
}


void TestMpopService::test_toBoolean()
{
    // Expected to be true:
    QCOMPARE(MPopService::toBoolean("TRUE"), true);
    QCOMPARE(MPopService::toBoolean("true"), true);
    QCOMPARE(MPopService::toBoolean("True"), true);
    QCOMPARE(MPopService::toBoolean("1"), true);

    // Expected to be false:
    QCOMPARE(MPopService::toBoolean("FALSE"), false);
    QCOMPARE(MPopService::toBoolean("false"), false);
    QCOMPARE(MPopService::toBoolean("False"), false);
    QCOMPARE(MPopService::toBoolean("0"), false);

    // Invalid values should return false:
    QCOMPARE(MPopService::toBoolean("qweqweqwe"), false);
    QCOMPARE(MPopService::toBoolean("????"), false);
    QCOMPARE(MPopService::toBoolean("987"), false);
    QCOMPARE(MPopService::toBoolean("!!!!!!"), false);
}

void TestMpopService::test_getOrCreateUser() {
    if (! this->is_mysql_supported) {
        QSKIP("This test requires MySQL");
    }
    static const QString TEST_RFID_TAG = "test_RFID_tag_0000";
    int userId = this->facade->getOrCreateUser(TEST_RFID_TAG);

    // Check that our user has the same ID as before:
    int userIdAgain = this->facade->getOrCreateUser(TEST_RFID_TAG);
    QCOMPARE(userIdAgain, userId);
}


void TestMpopService::test_getUserAnswers() {
    if (! this->is_mysql_supported) {
        QSKIP("This test requires MySQL");
    }
    static const QString TEST_RFID_TAG = "test_RFID_tag_0001";
    static const QString TEST_QUESTION_ID = "confiance_systeme";
    int userId = this->facade->getOrCreateUser(TEST_RFID_TAG);

    // Set an answer, and get it:
    int value = 99;
    this->facade->setUserAnswer(userId, TEST_QUESTION_ID, value);
    QMap<QString, QVariant> answers = this->facade->getUserAnswers(userId);
    QVariant actual = answers[TEST_QUESTION_ID];
    QCOMPARE(actual, value);
}

void TestMpopService::test_getUserLanguage() {
    if (! this->is_mysql_supported) {
        QSKIP("This test requires MySQL");
    }
    static const QString TEST_RFID_TAG = "test_RFID_tag_0002";
    static const QString TEST_LANGUAGE = "fr";
    int userId = this->facade->getOrCreateUser(TEST_RFID_TAG);

    this->facade->setUserLanguage(userId, TEST_LANGUAGE);
    QString language = this->facade->getUserLanguage(userId);

    QCOMPARE(TEST_LANGUAGE, language);
}


void TestMpopService::test_getUserGender() {
    if (! this->is_mysql_supported) {
        QSKIP("This test requires MySQL");
    }
    static const QString TEST_RFID_TAG = "test_RFID_tag_0003";
    static const QString TEST_USER_GENDER = "male";
    int userId = this->facade->getOrCreateUser(TEST_RFID_TAG);

    this->facade->setUserGender(userId, TEST_USER_GENDER);
    QString gender = this->facade->getUserGender(userId);

    QCOMPARE(TEST_USER_GENDER, gender);
}

void TestMpopService::test_getUserNation() {
    if (! this->is_mysql_supported) {
        QSKIP("This test requires MySQL");
    }
    static const QString TEST_RFID_TAG = "test_RFID_tag_0004";
    static const QString TEST_USER_NATION = "quebecer";
    int userId = this->facade->getOrCreateUser(TEST_RFID_TAG);

    // get an ethenicity.
    static const QString value="ethnicity";
    this->facade->setUserNation(userId, TEST_USER_NATION);
    QMap<QString, QVariant> userInfo = this->facade->getUserInfo(userId);
    QVariant userNation = userInfo[value];
    QCOMPARE(TEST_USER_NATION, userNation);
}

void TestMpopService::test_requestParams() {
    static const QString EXPECTED_RFID_TAG = "test_RFID_tag_doesntexist";
    static const int EXPECTED_REQUEST_ID = 9999;
    static const QString request_getOrCreateUser_01 =
        "{"
            "\"id\": 9999, "
            "\"method\":\"getOrCreateUser\", "
            "\"params\": ["
                "\"test_RFID_tag_doesntexist\""
            "]"
        "}";
     Request request = Request::fromString(request_getOrCreateUser_01);
     QString requestToString = request.toString();
     qDebug() << "request_getOrCreateUser_01:" << request_getOrCreateUser_01;
     qDebug() << "requestToString:" << requestToString;
     QString method = request.method;
     //QString param_1 = request.getParamByPosition(0).toString();
     //QCOMPARE(EXPECTED_RFID_TAG, param_1);
     int request_id = request.intId;
     QCOMPARE(EXPECTED_REQUEST_ID, request_id);
}
