/*
 * MIT License
 *
 * Copyright (c) 2018 TheRock
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>


#ifndef MAIN_H
#define MAIN_H

class BitcoinCore : public QObject {

    Q_OBJECT

public:

    BitcoinCore(const QString rpcUser, const QString rpcPassword)
        : mRpcUser(rpcUser),
          mRpcPassword(rpcPassword)
    {
        m_WebRequest.setRawHeader("Content-Type", "text/plain");
        m_WebRequest.setUrl(QUrl(QString("http://127.0.0.1:22555")));
        m_WebRequest.setRawHeader("Authorization", "Basic " + QString("%1:%2").arg(mRpcUser).arg(mRpcPassword).toLocal8Bit().toBase64());

        connect(&m_WebCtrl, &QNetworkAccessManager::finished, [](QNetworkReply *reply) {
            QByteArray ret = reply->readAll();

            qint32 statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if(statusCode == HTTP_UNAUTHORIZED) {
                qDebug() << "Credentials are not valid.";
            }
            else if(statusCode == HTTP_SUCCESS) {
                qDebug() << ret;
            }
            else {
                qDebug() << "Error: " << ret;
            }
        });
    }

    void getbalance( const QString username = {} ) {
        if(username.isNull() || username.isEmpty())
            makeRequest("getbalance");
        else
            makeRequest("getbalance", QJsonArray() << username);
    }

     void getnewaddress( const QString account = { }) {
        if(account.isNull() || account.isEmpty())
            makeRequest ( "getnewaddress" );
        else
            makeRequest( "getnewaddress", QJsonArray() << account );
    }

    bool gettransaction ( const QString account = {} ) {
        if(account.length() != 64)
            return false;
        else
            makeRequest( "gettransaction", QJsonArray() << account );

        return true;
    }

    bool sendfrom( const QString username, const QString walletAddress, const qint32 amount
                                                                /* amount should be a double, but I left it
                                                                 * on purpose an unsigned integer, since I use this
                                                                 * class with Dogecoins and 1 Dogecoin is $ 0.003
                                                                 */ ) {
        if(username.isEmpty() || username.isNull() || walletAddress.isEmpty() || walletAddress.isNull() || amount < 2)
           return false;

        makeRequest( "sendfrom", QJsonArray{ username, walletAddress, amount } );
        return true;
    }

private:
    QNetworkAccessManager m_WebCtrl;
    QNetworkRequest m_WebRequest;

    void makeRequest( const QString method, const QJsonArray array = {} ) {

        QJsonObject header = {
            qMakePair( QString("jsonrpc"), QJsonValue("1.0") ),
            qMakePair( QString("id"),      QJsonValue("jsonrpc") ),
            qMakePair( QString("method"),  QJsonValue(method) ),
            qMakePair( QString("params"),  QJsonValue(array) )
        };

        qDebug() << header;
       m_WebCtrl.post( m_WebRequest, QJsonDocument(header).toJson() );
    }

    QString mRpcUser;
    QString mRpcPassword;

    enum {
        HTTP_SUCCESS = 200,
        HTTP_UNAUTHORIZED = 401
    };
};

#endif // MAIN_H
