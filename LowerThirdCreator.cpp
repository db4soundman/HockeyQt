#include "LowerThirdCreator.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>

LowerThirdCreator::LowerThirdCreator(LowerThird* lt, bool standAlone) {
    if (standAlone){
        setLayout(getLayout(standAlone));
    }
    connect(this, SIGNAL(makeCustomLt(QString,QString,QString,QList<QString>,QList<QString>,bool)),
            lt, SLOT(prepareForCustomLt(QString,QString,QString,QList<QString>,QList<QString>,bool)));
    connect(&show, SIGNAL(clicked()), this, SLOT(submitLt()));
    if (standAlone) {
        connect(&show, SIGNAL(clicked()), this, SLOT(hide()));
    }
    connect(&clear, SIGNAL(clicked()), this, SLOT(clearFields()));
}

QVBoxLayout * LowerThirdCreator::getLayout(bool standAlone)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    home.setText("Home Team");
    mainLayout->addWidget(&home);
    QFormLayout* details = new QFormLayout();

    details->addRow("Name", &name);
    details->addRow("Number", &num);
    details->addRow("Year", &yr);
    details->addRow("Header", &header);
    details->addRow("Text", &text);

    mainLayout->addLayout(details);

    QHBoxLayout* buttons = new QHBoxLayout();

    clear.setText("Clear Fields");

    buttons->addWidget(&clear);

    previewButton.setText("Preview");
    if (!standAlone) {
        buttons->addWidget(&previewButton);
    }

    show.setText("Show");

    buttons->addWidget(&show);

    mainLayout->addLayout(buttons);

    return mainLayout;
}

void LowerThirdCreator::clearFields()
{
    name.setText("");
    num.setText("");
    yr.setText("");
    header.setText("");
    text.clear();
}

void LowerThirdCreator::submitLt()
{
    QList<QString> headerText, statText;
    headerText.append(header.text());
    statText.append(text.toPlainText());
    emit makeCustomLt(name.text(), num.text(), yr.text(), headerText, statText,
                      home.isChecked());
}
