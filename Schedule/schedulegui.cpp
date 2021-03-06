#include "schedulegui.h"
#include <QTextStream>
#include <QFile>
#include "MiamiAllAccessHockey.h"
#include <algorithm>
#include <QDate>
#include <QVBoxLayout>

void ScheduleGUI::loadSchedule()
{
    schedule.clear();
    QFile csv(MiamiAllAccessHockey::getAppDirPath() + "/schedule.csv");
    csv.open(QIODevice::ReadOnly);
    QTextStream stream(&csv);
    stream.readLine();
    int month = QDate::currentDate().month();
    int date = QDate::currentDate().day();
    bool preNye = month > 4;
    while (!stream.atEnd()) {
        QStringList data = stream.readLine().split(',');
        QString tMonth = data[0].split('/')[0];
        int schedMonth = QDate::fromString(tMonth, "MMM").month();
        int day1 = data[2].split('/')[0].toInt();
        int day2 = data[2].contains("/") ? data[2].split('/')[1].toInt():
                -1;
        // Same month, look at days
        if (schedMonth == month) {
            if (date < day1) {
                ScheduleEntry entry(data[0],data[1].toInt(),QString::number(day1),data[3],
                        data[4], data[5], data[7], QString::number(day2), data[6], data[8]);
                schedule.append(entry);
            } else if ( date < day2) {
                ScheduleEntry entry(data[0],1,QString::number(day2),data[3],
                        data[4], data[6], data[8]);
                schedule.append(entry);
            }
        }
        // Pre NYE, schedMonth in future, or game after NYE
        else if (preNye && ( month < schedMonth || schedMonth - 4 <= 0)) {
            ScheduleEntry entry(data[0],data[1].toInt(),QString::number(day1),data[3],
                    data[4], data[5], data[7], QString::number(day2), data[6], data[8]);
            schedule.append(entry);
        }
        // Post NYE, only months 1-4 accepted
        else if (schedMonth - 4 <= 0) {
            ScheduleEntry entry(data[0],data[1].toInt(),QString::number(day1),data[3],
                    data[4], data[5], data[7], QString::number(day2), data[6], data[8]);
            schedule.append(entry);
        }
    }
}

ScheduleGUI::ScheduleGUI()
{
    series.setText("Series View");
    series.setChecked(true);
    game.setText("Game View");
    game.setChecked(false);
    group.addButton(&series);
    group.addButton(&game);
    showButton.setText("Show");
    reloadButton.setText("Reload Schedule");
    QVBoxLayout* manager = new QVBoxLayout();
    manager->addWidget(&numToShow);
    manager->addWidget(&series);
    manager->addWidget(&game);
    manager->addWidget(&reloadButton);
    manager->addWidget(&showButton);

    loadSchedule();
    numToShow.setValue(std::min(2, schedule.length()));
    numToShow.setMaximum(std::min(8, schedule.length()));
    numToShow.setMinimum(1);

    connect(&showButton, SIGNAL(clicked()), this, SLOT(prepareToShow()));
    connect(&reloadButton, SIGNAL(clicked(bool)), this, SLOT(loadSchedule()));
    //connect(&showButton, SIGNAL(clicked()), this, SLOT(close()));
    setLayout(manager);
}

void ScheduleGUI::prepareToShow()
{
    int num = numToShow.value();
    QList<ScheduleEntry> toShow;
    for (int i = 0; toShow.size() <  num; i++) {
        if (series.isChecked()) {
            toShow.append(schedule[i]);
        }
        else {
            ScheduleEntry temp = schedule[i];
            toShow.append(temp);
            if (temp.getNumGames() == 2 && (i + 1) < num) {
                ScheduleEntry part2(temp.getMonth2().isEmpty() ? temp.getMonth1() : temp.getMonth2(),
                                    1,temp.getDate2(), temp.getVsAt(), temp.getOpp(),
                                    temp.getTime2(),temp.getMedia2());
                toShow.append(part2);
            //    i++;
            }
        }
    }
    emit show(toShow, series.isChecked());
}
