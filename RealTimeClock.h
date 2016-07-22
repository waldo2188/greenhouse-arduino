/**********
   Talk with Tiny RTC(Real Time Clock) (DS1307)

  Usefull for generating log
*/

#include <Arduino.h>

class RealTimeClock {

  public:
    RealTimeClock();

    /**
     * Initialise communication with RTC module
     */
    void init();

   /**
    * Return Log
    * 
    * exemple : [2016-07-13 15:16:57] capteur.INFO: {temperature:10.87} [capteur, inside]
    */
     String getLog(String channel, String levelName, String Message, String Context);

    /**
     * Add leading zero to have a two-digit number
     * 
     * @param int value
     * @return String
     */
     static String leadingZeros(byte value);
};

