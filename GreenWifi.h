
#include <Arduino.h>

// See : https://github.com/sleemanj/ESP8266_Simple/blob/3df46601ca075762742a62770392f39b9af5155a/ESP8266_Simple.h
struct HttpServerHandler
{
    const char     *requestMatches;
    void (* handlerFunction)(String query);
};


struct LogsContainer
{
    const char     *libelle;
    const char     *value;
};


class GreenWifi
{

  public:

    GreenWifi();

    void init(Stream *espSerial, char *ssid, char *password, HttpServerHandler *httpServerHandlers, String apiThingsSpeak);
    
    void handleRequest();
    
    void GreenWifi::logData(
      double outsideTemp,
      double insideTemp,
      double insideHumidity,
      byte fanSpeed,
      int ambientLight,
      byte additionnalLight  
    );

  protected:

    HttpServerHandler *httpServerHandlers;

  private:
  
    String readQueryParams(String query, String ref);

    String _apiThingsSpeak;
  
};

