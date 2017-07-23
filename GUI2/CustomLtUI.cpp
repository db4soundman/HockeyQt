#include "CustomLtUI.h"
#include <QPainter>

CustomLtUI::CustomLtUI(LowerThird *lt, LowerThird* previewLt):
    LowerThirdCreator(lt, false)
{
    this->previewLt=previewLt;
    connect(&previewButton, SIGNAL(clicked(bool)), this, SLOT(updatePreview()));
    QVBoxLayout* myLayout = new QVBoxLayout();
    myLayout->addLayout(getLayout(false));
    myLayout->addWidget(&preview);
    previewPixmap=QPixmap(previewLt->getWidth(),previewLt->getHeight());
    setLayout(myLayout);
}

void CustomLtUI::updatePreview()
{
    QList<QString> headerText, statText;
    headerText.append(header.text());
    statText.append(text.toPlainText());
    previewLt->prepareForCustomLt(name.text(), num.text(), yr.text(), headerText, statText,
                      home.isChecked(),false);
    QPainter painter(&previewPixmap);
    previewLt->paintPreview(&painter);
    preview.setPixmap(previewPixmap.scaled(previewLt->getWidth()/2, previewLt->getHeight()/2));
}
