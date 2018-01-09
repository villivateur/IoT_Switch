/*
   2018/1/5
   @Villivateur Von
   基于ESP8266和Arduino的Socket内网穿透控制客户端
*/
#include <Servo.h>

#define ErrorLED 12 //错误指示灯
Servo myservo;//控制舵机

void setup() {
  Serial.begin(115200);

  myservo.attach(9);

  pinMode(ErrorLED, OUTPUT);

  digitalWrite(ErrorLED, 0);//错误指示灯置0
  delay(6000);//ESP8266启动预留时间

  Serial.print("ATE0\r\n");//关闭回显
  delay(300);
}

char msg[64];//用于存放ESP8266回传信息

void loop() {
  int msglen = 0;//用于存放回传信息长度

  Serial.print("AT+CIPCLOSE\r\n");//为防止前一个TCP连接仍存在而导致错误，先清空链连接
  delay(100);
  recvmsg();//清空缓冲区

  Serial.print("AT+CIPSTART=\"TCP\",\"192.168.27.2\",10081\r\n");//建立TCP连接
  delay(300);
  msglen = recvmsg();
  if (msg[0] == 'C' && msg[4] == 'E' && msg[msglen - 3] == 'K') {//比较回传信息（基于ESP8266回传信息特性），是否已经成功建立连接，若否，错误指示灯亮
    digitalWrite(ErrorLED, 0);
    while (1) {
      Serial.print("AT+CIPSEND=1\r\n");//发送数据
      delay(100);
      msglen = recvmsg();
      if (msg[2] == 'O' && msg[3] == 'K') {//同上比较
        digitalWrite(ErrorLED, 0);
        Serial.print("6");//发送一个“6”（测试用）
        delay(300);
        msglen = recvmsg();

        if (msg[2] == 'R' && msg[7] == '1' && msg[18] == 'S' && msg[23] == 'O' && msg[34] == '1') {//同上比较
          digitalWrite(ErrorLED, 0);
          if (msg[msglen - 1] == '1') myservo.write(0);
          if (msg[msglen - 1] == '0') myservo.write(140); //根据回传数据控制
        }
        else {
          digitalWrite(ErrorLED, 1);
          break;
        }

      }
      else {
        digitalWrite(ErrorLED, 1);
        break;
      }
    }
  }
  else digitalWrite(ErrorLED, 1);
}

//接收ESP8266数据的函数，返回值为数据长度
int recvmsg() {
  int i = 0;
  while (Serial.available()) {
    msg[i] = (char)Serial.read();
    i++;
  }
  return i;
}
