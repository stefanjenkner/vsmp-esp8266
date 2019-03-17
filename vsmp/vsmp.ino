
#define ENABLE_GxEPD2_GFX 0

#include <FS.h>
#include <GxEPD2_BW.h>

// ESP8266 ePaper board
GxEPD2_BW < GxEPD2_750, GxEPD2_750::HEIGHT / 2 > display(GxEPD2_750(/*CS=15*/ SS, /*DC=4*/ 4, /*RST=5*/ 5, /*BUSY=16*/ 16));

// initial image in SPIFFS
String imageName = String("000.dat");

void setup()
{
  SPIFFS.begin();

  Serial.begin(115200);
  //while(!Serial) {
  //  ; // wait
  //}
  delay(2000);

  Serial.println("Init display");
  display.init(115200);
}

void displayImage(String filename, uint16_t width, uint16_t height) {

  fs::File file;
  Serial.print(String("Loading image: ") + filename);
  file = SPIFFS.open(String("/") + filename, "r");
  if (!file) {
    Serial.print("File not found");
    return;
  }
  uint8_t data[width];
  for (uint16_t y = 0; y < height ; y += 8) {
    file.read(data, width /* multiply by 8 rows divide by 8 bits */ );
    // void writeImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    display.writeImage(data, 0, y, width, 8);
  }
  display.refresh();
  file.close();
}

String findNextFile(String prevFile) {

  String nextFile = String("");
  fs::Dir dir = SPIFFS.openDir("");

  while (dir.next()) {
    String fileName = dir.fileName();
    fileName = fileName.substring(1); // strip '/'

    // skip non-supported files
    if (!fileName.endsWith(".dat")) {
      continue;
    }

    if (prevFile.compareTo(fileName) < 0) {
      // first valid match OR found better match
      if ((nextFile == "") || (fileName.compareTo(nextFile) < 0)) {
        nextFile = fileName;
      }
    }
  }
  return nextFile;
}


void loop()
{
  imageName = findNextFile(imageName);

  // nothing to show?
  if (imageName == "") {
    display.firstPage();
    display.fillScreen(GxEPD_WHITE);
    display.nextPage();
    display.powerOff();
    Serial.println("Good night");
    ESP.restart();
  }

  displayImage(imageName, 640, 384);
  delay(60000);

}
