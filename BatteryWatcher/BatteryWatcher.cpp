 #include <QApplication>
 #include <QDesktopWidget>
 #include <QLabel>
 #include <QDir>
 #include <QSettings>
 #include <QMessageBox>
 #include <QObject>
 #include <unistd.h>
 #include <cerrno>
 #include <fstream>
 #include <string>
 #include <stdexcept>
 #include <functional>

 class BatteryWatcher
 {
 public:
     BatteryWatcher();

     void watch_battery(void);

 private:
     QMessageBox *chargeWarning, *dischargeWarning;

     std::string read_status(std::ifstream& ifs, const std::string& fileName);
     int read_capacity(std::ifstream& ifs, const std::string& fileName);
     void charger_check(std::ifstream& ifs,
                        const std::string& status,
                        int capacity,
                        std::function<bool(int,int)> comp,
                        QMessageBox* warningBox);
 };

 BatteryWatcher::BatteryWatcher()
 {
     qApp->setQuitOnLastWindowClosed(false);

     chargeWarning = new QMessageBox(QMessageBox::Warning, QObject::tr("Battery Watcher"),
                           QObject::tr("The battery is running under 40\% capacity.\n"
                                       "Please plug in your charger!"),
                           QMessageBox::Ok | QMessageBox::Close);
     chargeWarning->setDefaultButton(QMessageBox::Close);
     chargeWarning->setMinimumSize(chargeWarning->sizeHint());
     chargeWarning->setWindowFlags(Qt::WindowStaysOnTopHint);  

     dischargeWarning = new QMessageBox(QMessageBox::Warning, QObject::tr("Battery Watcher"),
                            QObject::tr("The battery is running over 80\% capacity.\n"
                                       "Please plug out your charger!"),
                            QMessageBox::Ok | QMessageBox::Close);

     dischargeWarning->setDefaultButton(QMessageBox::Close);
     dischargeWarning->setMinimumSize(dischargeWarning->sizeHint());
     dischargeWarning->setWindowFlags(Qt::WindowStaysOnTopHint);
 }

 std::string BatteryWatcher::read_status(std::ifstream& ifs, const std::string& fileName)
 {
    ifs.open(fileName);
    if(!ifs)
        throw std::runtime_error("Cannot open input file '" + fileName + "' : " + strerror(errno));

    std::string status;
    ifs >> status;
    ifs.close();

    if(ifs.fail() && !ifs.eof())
        throw std::runtime_error("Error while reading from input file '" + fileName + "'");

    return status;
 }

 int BatteryWatcher::read_capacity(std::ifstream& ifs, const std::string& fileName)
 {
    ifs.open(fileName);
    if(!ifs)
        throw std::runtime_error("Cannot open input file '" + fileName + "' : " + strerror(errno));

    int capacity;
    ifs >> capacity;
    ifs.close();

    if(ifs.fail() && !ifs.eof())
        throw std::runtime_error("Error while reading from input file '" + fileName + "'");

    if(capacity < 0 || capacity > 100)
        throw std::runtime_error("Something unexpected has occurred (capacity NOT IN [0,100])");

    return capacity;
 }

 void BatteryWatcher::charger_check(std::ifstream& ifs,
                            const std::string& status,
                            int capacity,
                            std::function<bool(int,int)> comp,
                            QMessageBox* warningBox)
 {
    std::string current_status;
    int current_capacity = read_capacity(ifs, "/sys/class/power_supply/BAT0/capacity");

    if(comp(current_capacity, capacity)){
        do
            current_status = read_status(ifs, "/sys/class/power_supply/BAT0/status");
        while(current_status != status && warningBox->exec() != QMessageBox::Ok);    
    }
 }

 void BatteryWatcher::watch_battery(void)
 {
    std::ifstream ifs;
    std::string status = read_status(ifs, "/sys/class/power_supply/BAT0/status");

    if(status == "Discharging")
        charger_check(ifs, "Charging", 40, std::less_equal<int>(), chargeWarning);
    else
        charger_check(ifs, "Discharging", 80, std::greater_equal<int>(), dischargeWarning);
 }

 int main(int argc, char **argv)
 {
    QApplication app(argc, argv);

    BatteryWatcher bwt;
    while(!sleep(60))
        bwt.watch_battery(); 

    return app.exec();
 }