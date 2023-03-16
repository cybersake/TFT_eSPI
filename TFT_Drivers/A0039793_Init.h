
// This is the command sequence that initialises the A0039793 driver (Project Otto)
//
// This setup information uses simple 8 bit SPI writecommand() and writedata() functions
//

// A0039793 Display Project Otto
{
/*   writecommand(ST7789_SLPOUT);   // Sleep out
  delay(120);

  writecommand(ST7789_NORON);    // Normal display mode on

  //------------------------------display and color format setting--------------------------------//
  writecommand(ST7789_MADCTL);
  writedata(TFT_MAD_COLOR_ORDER);

  writecommand(ST7789_COLMOD);
  writedata(0x55);
  delay(10);

  //--------------------------------ST7789V Frame rate setting----------------------------------//
  writecommand(ST7789_PORCTRL);
  writedata(0x0b);
  writedata(0x0b);
  writedata(0x00);
  writedata(0x33);
  writedata(0x33);

  writecommand(ST7789_GCTRL);      // Voltages: VGH / VGL
  writedata(0x75);

  //---------------------------------ST7789V Power setting--------------------------------------//
  writecommand(ST7789_VCOMS);
  writedata(0x28);		// JLX240 display datasheet

  writecommand(ST7789_LCMCTRL);
  writedata(0x2C);

  writecommand(ST7789_VDVVRHEN);
  writedata(0x01);

  writecommand(ST7789_VRHS);       // voltage VRHS
  writedata(0x1F);

  writecommand(ST7789_FRCTR2);
  writedata(0x13);

  writecommand(ST7789_PWCTRL1);
  writedata(0xa7);

  writecommand(ST7789_PWCTRL1);
  writedata(0xa4);
  writedata(0xa1);

  writecommand(0xD6);
  writedata(0xa1);

  //--------------------------------ST7789V gamma setting---------------------------------------//
  writecommand(ST7789_PVGAMCTRL);
  writedata(0xf0);
  writedata(0x05);
  writedata(0x0a);
  writedata(0x06);
  writedata(0x06);
  writedata(0x03);
  writedata(0x2b);
  writedata(0x32);
  writedata(0x43);
  writedata(0x36);
  writedata(0x11);
  writedata(0x10);
  writedata(0x2b);
  writedata(0x32);

  writecommand(ST7789_NVGAMCTRL);
  writedata(0xf0);
  writedata(0x08);
  writedata(0x0c);
  writedata(0x0b);
  writedata(0x09);
  writedata(0x24);
  writedata(0x2b);
  writedata(0x22);
  writedata(0x43);
  writedata(0x38);
  writedata(0x15);
  writedata(0x16);
  writedata(0x2f);
  writedata(0x37);
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  end_tft_write();
  delay(120);
  begin_tft_write();

  //writecommand(ST7789_DISPON);    //Display on
  delay(120);
  //28][E][esp32-hal-gpio.c:102] __pinMode(): Invalid pin selected
  
  // A0039793 back-light full power
  pinMode(PIN_HSPI_RS, OUTPUT); //MEM CPLD or 1=TOUCH/KEYS/BackLight
  digitalWrite(PIN_HSPI_RS, HIGH); //Select Control TOUCH/KEYS/BackLight  
  CS_L; //digitalWrite(TFT_CS, LOW);  //CS active
  A0039793_ControlReg_t ControlReg;
  ControlReg.all = 0;
  ControlReg.LedDuty = 15;  //Full power
  ControlReg.TftEn   = 1;   //Screen ON
  ControlReg.TscPoff = 0;   //Touch screen power ON
  ControlReg.TftReverseScan = 0; //Normal Scan
  
  spi.transfer(ControlReg.all);
  CS_H; //digitalWrite(TFT_CS, HIGH); //release CS
  digitalWrite(PIN_HSPI_RS, LOW); //Select MEM 
}
