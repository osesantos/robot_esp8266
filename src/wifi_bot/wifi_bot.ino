#include <ESP8266WiFi.h>

const char* ssid = "Net Loading...";
const char* password = "Olivia.Serafim.1001";

int IN1 = 0;          // D3
int IN2 = 2;          // D4
int IN3 = 14;         // D5
int IN4 = 12;         // D6
int ENA = 4;          // D2
int ENB = 13;         // D7
int duty_a = 200;     // Speed of right motor range(0-255)
int duty_b = 200;     // Speed of left motor range(0-255)
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  /*-------- server started ---------*/
  server.begin();
  Serial.println("Server started");

  /*------ printing ip address --------*/
  Serial.print("IP Address of network: ");
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();    
  if (!client) {
    return;
  }

  Serial.println("Waiting for new client...");
  while(!client.available()) {
    delay(100);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  String value = "stop";
  if (request.indexOf("/foward") != -1)  {
    forward();
    value = "forward";
  }
  if (request.indexOf("/stop") != -1)  {
    halt();
    value ="stop" ;
  }
  if (request.indexOf("/right") != -1)  {
    right();
    value ="right" ;
  }
  if (request.indexOf("/left") != -1)  {
    left();
    value ="left" ;
  }
  if (request.indexOf("/reverse") != -1)  {
    reverse();
    value ="reverse" ;
  }

  /*------------------ Creating html page ---------------------*/

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println(" <meta charset=\"utf-8\"> ");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<title>");
  client.println("ROBOT CONTROL");
  client.println("</title>");
  client.println("<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD\" crossorigin=\"anonymous\">");


  client.println("</head>");
  client.println("<body>");
  client.println(" <script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN\" crossorigin=\"anonymous\">  </script>");
  client.println("");
  client.println("<div class=\"d-flex justify-content-center\">");
  client.println("<div style=\"margin-top:5px\">");
  client.println("<h2>ROBOT IS MOVING: </h2>");
  client.print("<h2 style=\"color:blue\">");
  client.print(value);
  client.print("</h2>");
  client.println("<br><br><br><br></div>");
  client.println("</div>");

  client.println("<div class=\"d-flex justify-content-center\">");
  client.println("<br><br>");
  client.println("<table>");
  client.println("<tr><th></th>");
  client.println("<th class=\"text-center\"> <a href=\"/foward\"><button class=\"btn btn-primary\" type=\"button\">FORWARD</button></a></th>");
  client.println("<th></th></tr><tr></tr><tr>");
  client.println("<th class=\"text-center\"><a href=\"/left\"><button class=\"btn btn-primary\" type=\"button\">LEFT</button></a></th>");
  client.println("<th class=\"text-center\"><a href=\"/stop\"><button class=\"btn btn-primary\" type=\"button\">STOP</button></a></th>");
  client.println("<th class=\"text-center\"><a href=\"/right\"><button class=\"btn btn-primary\" type=\"button\">RIGHT</button></a></th></tr>");
  client.println("<tr><th></th>");
  client.println("<th class=\"text-center\"><a href=\"/reverse\"><button class=\"btn btn-primary\" type=\"button\">REVERSE</button></a></th>");
  client.println("<th></th></tr><tr></tr></table>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  delay(100);
  Serial.println("Client disonnected...");
}

void reverse(void) {
  analogWrite(ENA, duty_a);
  analogWrite(ENB, duty_b);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void forward(void) {
  analogWrite(ENA, duty_a);
  analogWrite(ENB, duty_b);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left(void) {
  analogWrite(ENA, duty_a);
  analogWrite(ENB, duty_b);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right(void) {
  analogWrite(ENA, duty_a);
  analogWrite(ENB, duty_b);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void halt(void) {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
