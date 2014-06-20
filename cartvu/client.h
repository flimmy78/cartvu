#ifndef CLIENT_H
#define CLIENT_H

#include <QtNetwork>
#include <QString>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QTimer>
#include <QTime>
#include <QDebug>

//#define TIME_OUT_SEC   5
#define TEST_TIME_OUT       5
#define TEST_TIME_COUNT      5



//#define TEST_START_TIME_COUNT      10
#define TEST_START_TIME_COUNT      30


class client : public QObject{
    Q_OBJECT
public:
    client();
    //client(QString serverip, int port, QString cmd, QString *rec_string);
    ~client();
    
    void init();
    void new_tcp_connection();
    //测试服务器连通性    
    void test_server_port(QString serverip, int port, int sig_sec, int num);
    //单次连接
    void try_connect();
    //发送post或者get请求
    void transmit_info(QString serverip, int port, QString cmd, QString *rec_string);
public:
    QString serverip;
    int port;
    QString cmd;
    bool error_flag;
    QString *parent_string;
    QTimer connect_timeout;
    bool connect_state;
    int time_out;
    int time_out_count;
    int now_time_out_count;
    bool error_timeout;
private:
    QTcpSocket *tcp_socket;
    QString datas;
private slots:
    //socket 写
    void cmd_write();
    // socket 读
    void rec_data();
    //连接错误
    void display_error(QAbstractSocket::SocketError);
    // 连接错误
    void test_display_error(QAbstractSocket::SocketError);
    //超时
    void connect_to_host_timeout();
    //测试服务器连通性超时
    void test_connect_to_host_timeout();
    //发送连通性是超时还是连上，并将数据发出
    void emit_connect_state();
signals:
    //发送接收信号
    void emit_receive();
    //发送当前连接状态
    void now_sate();
};

#endif // CLIENT_H
