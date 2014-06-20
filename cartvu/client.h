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
    //���Է�������ͨ��    
    void test_server_port(QString serverip, int port, int sig_sec, int num);
    //��������
    void try_connect();
    //����post����get����
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
    //socket д
    void cmd_write();
    // socket ��
    void rec_data();
    //���Ӵ���
    void display_error(QAbstractSocket::SocketError);
    // ���Ӵ���
    void test_display_error(QAbstractSocket::SocketError);
    //��ʱ
    void connect_to_host_timeout();
    //���Է�������ͨ�Գ�ʱ
    void test_connect_to_host_timeout();
    //������ͨ���ǳ�ʱ�������ϣ��������ݷ���
    void emit_connect_state();
signals:
    //���ͽ����ź�
    void emit_receive();
    //���͵�ǰ����״̬
    void now_sate();
};

#endif // CLIENT_H
