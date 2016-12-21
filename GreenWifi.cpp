
#include "GreenWifi.h"
#include "WiFiEsp.h"


// TODO Dosen't work for now
// Initialize the Server client object
//WiFiEspServer server(80);

// Initialize the Ethernet client object
WiFiEspClient httpClient;


int _status = WL_IDLE_STATUS;     // the Wifi radio's status
char *_ssid;
char *_password;

GreenWifi::GreenWifi() {
}

void GreenWifi::init(Stream *espSerial, char *ssid, char *password, HttpServerHandler *httpServerHandlers, String apiThingsSpeak) {

  _apiThingsSpeak = apiThingsSpeak;
  _ssid = ssid;
  _password = password;

  //this->httpServerHandlers = httpServerHandlers;

  // initialize ESP module
  WiFi.init(espSerial);

  // get your MAC address
  byte mac[6];
  WiFi.macAddress(mac);

  // print MAC address
  char buf[20];
  sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  Serial.print("MAC address: ");
  Serial.println(buf);



  this->connection();

  /*
  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print where to go in the browser
  Serial.println();
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  Serial.println(); */

  // TODO Don't work for now
  //server.begin();
}

void GreenWifi::connection() {

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    return;
  }

  long timeOut = millis();

  // attempt to connect to WiFi network
  while ( _status != WL_CONNECTED && (millis() - timeOut < 500)) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(_ssid);
    // Connect to WPA/WPA2 network
    _status = WiFi.begin(_ssid, _password);
  }
  
}

void GreenWifi::handleRequest() {
  /*
    // listen for incoming clients
    WiFiEspClient client = server.available();

    if (client) {
    Serial.println("New client");

    String request = "";

    boolean isCR = false;

    long _startMillis = millis();

    // Some time Wifi Library get a TIMEOUT and dont close the connection
    while (client.connected() && (millis() - _startMillis < 500)) {
      if (client.available()) {

        char c = client.read();

        request += (char)c;

        // If it's the end of HTTP Request
        if (c == '\n' && isCR) {
          // End of HTTP request
          break;
        }

        isCR = (c == "\r");
      }
    }


    int contRequest = sizeof(this->httpServerHandlers);

    for(byte x = 0;x < contRequest; x++)
    {
      if(request.indexOf(this->httpServerHandlers[x].requestMatches) > -1)
      {
        String requestParam = readQueryParams(request, this->httpServerHandlers[x].requestMatches);

        this->httpServerHandlers[x].handlerFunction(requestParam);
      }
    }

    //client.flush();

    if(request != "") {
      Serial.println("Sending response");

      // send a standard http response header
      // use \r\n instead of many println statements to speedup data send
      client.print(
      "HTTP/1.1 200 OK\r\n"
      "Content-Type: text/html\r\n"
      "Connection: close\r\n"  // the connection will be closed after completion of the response
      "\r\nok\r\n");
    }

    // We clear the request
    request = "";

    // give the web browser time to receive the data
    delay(10);

    Serial.println("Client disconnected");
    }

    // close the connection:
    client.stop();*/
}

String GreenWifi::readQueryParams(String query, String ref)
{
  int start = query.indexOf(ref) + ref.length() + 1;

  return query.substring(
           start,
           query.indexOf(" ", start)
         );
}

void GreenWifi::logData(
  double outsideTemp,
  double insideTemp,
  double insideHumidity,
  byte fanSpeed,
  int ambientLight,
  byte additionnalLight,
  int moiste,
  int hasBeenWatering
) {
    // close any connection before send a new request
    // this will free the socket on the WiFi shield
    httpClient.stop();

  if (httpClient.connect("api.thingspeak.com", 80)) {

    String cmd = "GET /update?api_key=" + _apiThingsSpeak + "&field1=";
    cmd += outsideTemp;
    cmd += "&field2=";
    cmd += insideTemp;
    cmd += "&field3=";
    cmd += insideHumidity;
    cmd += "&field4=";
    cmd += fanSpeed;
    cmd += "&field5=";
    cmd += ambientLight;
    cmd += "&field6=";
    cmd += additionnalLight;
    cmd += "&field7=";
    cmd += moiste;
    cmd += "&field8=";
    cmd += hasBeenWatering;

    cmd += "\r\n\r\n";

    Serial.println("Connected to server");
    Serial.println("Send request : ");
    Serial.print(cmd);

    // Make a HTTP request
    httpClient.print(cmd);

    delay(1000);
    while (httpClient.available()) {
      char c = httpClient.read();
      Serial.write(c);
    }
    delay(3000);
  }
}

void GreenWifi::reset() {

  Serial.println("\nReset the Wifi");

  WiFi.reset();

  WiFi.disconnect();

  _status = WL_IDLE_STATUS;

  this->connection();
}

