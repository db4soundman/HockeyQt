#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QColor>
class Profile
{
public:
    Profile(QString title, QString fullName, QString shortName, QColor color, QString logoPath);
    ~Profile();


    QString getTitle() const;
    void setTitle(const QString &value);

    QString getFullName() const;
    void setFullName(const QString &value);

    QString getShortName() const;
    void setShortName(const QString &value);

    QString getLogoPath() const;
    void setLogoPath(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

    QString toString();

private:
    QString title, fullName, shortName, logoPath;
    QColor color;
};

#endif // PROFILE_H
