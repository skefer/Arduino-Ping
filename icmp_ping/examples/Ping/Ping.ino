/*
  Ping Example
 
 This example sends an ICMP pings every 500 milliseconds, sends the human-readable
 result over the serial port. 

 Circuit:
 *w5500 connect to Mega2560 50,51,52,53
 
 created 30 Sep 2010
 by Blake Foster
 
 */

#include <SPI.h>         
#include <Ethernet.h>
#include <ICMPPing.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // max address for ethernet shield
byte ip[] = {192,168,0,177}; // ip address for ethernet shield
IPAddress pingAddr(192,168,0,19); // ip address to ping


char buffer [256];
ICMPPing ping;

void setup() 
{
  pinMode(53, OUTPUT);
  SPI.begin();
  digitalWrite(53, LOW); // enable Ethernet
  // start Ethernet
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
   Serial.println(Ethernet.localIP());
  Serial.println("Init ok");
}

void loop()
{
  Serial.println("Begin Ping...");
  ICMPEchoReply echoReply = ping.Ping(pingAddr);
  Serial.println("GotData");
  if (echoReply.status == SUCCESS)
  {
    sprintf(buffer,
            "Reply[%d] from: %d.%d.%d.%d: bytes=%d time=%ldms TTL=%d",
            echoReply.data.seq,
            echoReply.addr[0],
            echoReply.addr[1],
            echoReply.addr[2],
            echoReply.addr[3],
            REQ_DATASIZE,
            millis() - echoReply.data.time,
            echoReply.ttl);
  }
  else
  {
    sprintf(buffer, "Echo request failed; %d", echoReply.status);
  }
  Serial.println(buffer);
  delay(500);
}










