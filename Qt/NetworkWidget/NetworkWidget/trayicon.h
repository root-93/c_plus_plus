#ifndef TRAYICON_H
#define TRAYICON_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QNetworkReply>
#include <QMenu>
#include <QUrl>
#include <QIcon>
#include <QCache>
#include <QDomDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class TrayIcon; }
QT_END_NAMESPACE

class TrayIcon : public QSystemTrayIcon
{
        Q_OBJECT

    public:
        explicit TrayIcon();
        ~TrayIcon();
    private slots:
        void requestXml();
        void readXml(QNetworkReply *reply);
        void readIcon(QNetworkReply *reply);
        void setAirport(QAction *action);
    private:
        void createContextMenu();
        void populateToolTip(QDomDocument *document);
        QString textForTag(const QString &tag, QDomDocument *document);
        QString toolTipField(const QString &name, const QString &htmlColor, const QString &value, bool appendBr = false);

        QMenu menu;
        QNetworkAccessManager *networkXmlAccess;
        QNetworkAccessManager *networkIconAccess;
        QString airport;
        QCache<QUrl, QIcon> iconCache;
        int retryDelaySec;
        Ui::TrayIcon *ui;
};
#endif // TRAYICON_H
