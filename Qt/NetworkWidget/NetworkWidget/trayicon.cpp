#include "trayicon.h"
#include "ui_trayicon.h"
#include <qdebug.h>
#include <QTimer>
#include <QSettings>
#include <QStringList>
#include <QString>
#include <QVariant>
#include <QTextDocumentFragment>


TrayIcon::TrayIcon()
    : QSystemTrayIcon(), retryDelaySec{1}{
    setIcon(QIcon("/usr/share/icons/Mint-X-Dark/places/22/start-here.png"));
    createContextMenu();
    networkXmlAccess = new QNetworkAccessManager(this);
    networkIconAccess = new QNetworkAccessManager(this);
    connect(networkXmlAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(readXml(QNetworkReply*)));
    connect(networkIconAccess, SIGNAL(finished(QNetworkReply*)), this, SLOT(readIcon(QNetworkReply*)));
    QTimer::singleShot(0, this, SLOT(requestXml()));
}

TrayIcon::~TrayIcon()
{
    delete ui;
}

void TrayIcon::createContextMenu(){
    QStringList airports;
    airports << "Austin-Gergstrom (KAUS)"
             << "Chicago-O'Hare (KORD)"
             << "Dallas Fort Worth (KDFW)"
             << "Coleman (KDET)"
             << "Houston (KIAH)"
             << "Los Angeles (KLAX)";

    QSettings settings;
    airport = settings.value("airport", QVariant(airports.at(0))).toString();
    QActionGroup *group = new QActionGroup(this);
    foreach(const QString &anAirport, airports){
        QAction *action = menu.addAction(anAirport);
        group->addAction(action);
        action->setCheckable(true);
        action->setChecked(anAirport == airport);
        action->setData(anAirport);
    }
    connect(group, SIGNAL(triggered(QAction*)), this, SLOT(setAirport(QAction*)));
    menu.addSeparator();
    menu.addAction(QIcon(":/exit.png"), tr("Wyjście"), qApp, SLOT(quit()));
    //AQP::accelerateMenu(&menu);
    setContextMenu(&menu);
}


void TrayIcon::requestXml(){
    QString airportID {airport.right(6)};
    if(airportID.startsWith("(") && airportID.endsWith(")")){
        QString url {QString("http://w1.weather.gov/xml/current_obs/%1.xml").arg(airportID.mid(1,4))};
        qDebug() << url;
        networkXmlAccess->get(QNetworkRequest(QUrl(url)));
    }
}


void TrayIcon::readXml(QNetworkReply *reply){
    if(reply->error() != QNetworkReply::NoError){
        setToolTip(tr("Błąd pobierania danych pogodowych:\n%1")
                   .arg(reply->errorString()));
        QTimer::singleShot(retryDelaySec * 1000, this,  SLOT(requestXml()));
        retryDelaySec <<= 1;
        if(retryDelaySec > 60*60)
            retryDelaySec = 1;
    }
    retryDelaySec = 1;
    QDomDocument document;
    if(document.setContent(reply))
            populateToolTip(&document);
    qDebug() << document.toString();
    QTimer::singleShot(60 * 60 * 1000, this, SLOT(requestXml()));
}


void TrayIcon::populateToolTip(QDomDocument *document){
    QString toolTipText = tr("<font color=darkblue>%1</font><br>").arg(airport);
    QString weather = textForTag("weather", document);
    if(!weather.isEmpty())
        toolTipText += toolTipField("Weather", "green", weather);
    QString temp = textForTag("temp", document);
    if(!weather.isEmpty())
        toolTipText += toolTipField("Temp.", "green", temp);

    QString iconUrl {textForTag("icon_url_base", document)};
    if(!iconUrl.isEmpty()){
        QString name {textForTag("icon_url_name", document)};
        if(!name.isEmpty()){
            iconUrl += name;
            QUrl url(iconUrl);
            QIcon *icon {iconCache.object(url)};
            if(icon && !icon->isNull())
                setIcon(*icon);
            else
                networkIconAccess->get(QNetworkRequest(url));
        }
    }

#ifdef Q_WS_X11
    toolTipText = QtextDocumentFragment::fromHtml(toolTipText).toPlainText();
#endif
    setToolTip(toolTipText);
}


QString TrayIcon::textForTag(const QString &tag, QDomDocument *document){
    QString result{};
    QDomNodeList nodes {document->elementsByTagName(tag)};
    if(!nodes.isEmpty()){
        const QDomNode &node = nodes.item(0);
        if(!node.isNull() && node.hasChildNodes())
            result = node.firstChild().nodeValue();
    }
    return result;
}


QString TrayIcon::toolTipField(const QString &name, const QString &htmlColor, const QString &value, bool appendBr){
    return QString("<i>%1:</i>&nbsp;<font color=\"%2\">%3</font>%4")
            .arg(name).arg(htmlColor).arg(value).arg(appendBr ? "<br>" : "");
}


void TrayIcon::readIcon(QNetworkReply *reply){
    QUrl redirect {reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl()};
    if(redirect.isValid())
        networkIconAccess->get(QNetworkRequest(redirect));
    else{
        QByteArray ba(reply->readAll());
        QPixmap pixmap;
        if(pixmap.loadFromData(ba)){
            QIcon *icon = new QIcon(pixmap);
            setIcon(*icon);
            iconCache.insert(reply->request().url(), icon);
        }
    }
}


void TrayIcon::setAirport(QAction *action){
    airport = action->data().toString();
    QSettings settings;
    settings.setValue("airport", airport);
    requestXml();
}

