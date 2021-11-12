#include "TextualRosterInput.h"
#include <QVBoxLayout>
#include <QRegularExpressionMatchIterator>
#include "SeasonXMLHandler.h"

TextualRosterInput::TextualRosterInput(HockeyTeam *myTeam, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *myLayout = new QVBoxLayout();
    submit.setText("Submit");
    convert.setText("Convert");
    myLayout->addWidget(&rosterInput);
    myLayout->addWidget(&submit);
    //myLayout->addWidget(&convert);
    setLayout(myLayout);

    numberName = QRegularExpression("\\(?<num>\\d+)\\s*(?<name>.+)\n");
    numberName.setPatternOptions(QRegularExpression::MultilineOption);
//    nameNumber = QRegularExpression("\\s*(?<name>[\\w+-]+,?\\s*[\\w+-]+)\\s*(?<num>\\d+)[^\n]*\n");
//    nameNumber.setPatternOptions(QRegularExpression::MultilineOption);
    team=myTeam;

    connect(&submit, SIGNAL(clicked(bool)), this, SLOT(parseRoster()));
    connect(&convert, SIGNAL(clicked(bool)), this, SLOT(convertText()));
}

void TextualRosterInput::parseRoster()
{
//    QString es = numberName.errorString();
//    int eo = numberName.patternErrorOffset();

    QString roster = rosterInput.toPlainText();
    QStringList players = roster.split("\n");
    for(int i = 0; i < players.size(); i++) {
        HockeyPlayer p;
        p.setUni(players[i].split(" ")[0]);
        p.setName(players[i].mid(players[i].indexOf(" ")).trimmed());
        team->addPlayer(p);
        emit team->rosterChanged();

//    if (numberName.match(rosterInput.toPlainText()).hasMatch()) {
//        QRegularExpressionMatchIterator i = numberName.globalMatch(rosterInput.toPlainText());
//        team->clearRoster();
//        while (i.hasNext()) {
//            QRegularExpressionMatch match = i.next();
//            HockeyPlayer p;
//            p.setUni(match.captured("num"));
//            p.setName(SeasonXMLHandler::correctName(match.captured("name")));
//            team->addPlayer(p);
//            this->close();
//            emit team->rosterChanged();
//        }
    }
   /* HockeyPlayer empty;
    empty.setName("No Name");
    team->addPlayer(empty);
    emit team->rosterChanged();*/
    this->close();
}

void TextualRosterInput::convertText()
{
    rosterInput.setText(rosterInput.toPlainText());
}
