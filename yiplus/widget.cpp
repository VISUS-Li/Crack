#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("yiPlus");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pB_signUp_clicked()
{
    this->close();
}

void Widget::on_pB_signIn_clicked()
{
    QString ID = ui->lE_ID->text();
    QString passWord = ui->lE_passWord->text();

    if( ID.isEmpty() || passWord.isEmpty()) {
        ui->lb_conInfo->setStyleSheet("color:red;");
        ui->lb_conInfo->setText("请输入ID和密码!");
        return;
    }

    ui->lb_conInfo->setStyleSheet("color:green;");

    /* create url */
    logInURL = logInURL + "phoneNumber=" + ID + "&";
    logInURL = logInURL + "password=" + "GCN0kn9VEM5pc7zPakk2YA==";

    qDebug() << "logInURL" << logInURL;

    //create url request
    QNetworkRequest request(logInURL);
    QHttpMultiPart *multi_part = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart *formdata = new QHttpPart;
    formdata->setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant(QString("form-data; phoneNumber=\"15002326234\";password=\"GCN0kn9VEM5pc7zPakk2YA==\";")));
    multi_part->append(*formdata);
    QNetworkAccessManager *netWorkManager = new QNetworkAccessManager;

    QNetworkReply *reply = netWorkManager->post(request, multi_part);

    //连接请求结束信号
    connect(netWorkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    //连接响应时返回数据信号
    connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
}

void Widget::replyFinished(QNetworkReply *reply)
{
    QByteArray data = reply->readAll();

    QJsonParseError json_error;
    QJsonDocument document = QJsonDocument::fromJson(data, &json_error);

    if(json_error.error == QJsonParseError::NoError)
    {
        qDebug() << document;
        if(document.isObject())
        {
            QJsonObject obj = document.object();
            //解析反馈请求结果
            if(obj.contains("flag"))
            {
                 bool flag = obj.take("flag").toBool();
                 qDebug() << "登录请求返回结果：" << flag;
                 if ( true != flag) {
                     ui->lb_conInfo->setStyleSheet("color:red;");
                     ui->lb_conInfo->setText("请求失败！");
                     return;
                 } else  {
                     Form *mainWidget = new Form(document, this);
                     this->hide();
                     mainWidget->show();
                 }
            }
        }
    }
}

void Widget::on_readyRead()
{

}
