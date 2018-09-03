#include "Settings.h"

Settings::Settings() {}

void Settings::load() {
  if (debug) Serial.println("\n[E] Load Settings");

  ssidLen = EEPROM.read(ssidLenAdr);
  if (ssidLen < 0 || ssidLen > 32) {
    Settings::reset();
    return;
  }
  passwordLen = EEPROM.read(passwordLenAdr);
  if (passwordLen < 0 || passwordLen > 32) {
    Settings::reset();
    return;
  }
  autostartLen = EEPROM.read(autostartLenAdr);
  if (autostartLen < 1 || autostartLen > 32) {
    Settings::reset();
    return;
  }
  channel = EEPROM.read(channelAdr);
  if (channel < 1 || channel > 14) {
    Settings::reset();
    return;
  }
  hidden = (bool)EEPROM.read(hiddenAdr);
  autoExec = (bool)EEPROM.read(autoExecAdr);

  for (int i = 0; i < ssidLen; i++) ssid[i] = EEPROM.read(ssidAdr + i);
  for (int i = 0; i < passwordLen; i++)
    password[i] = EEPROM.read(passwordAdr + i);
  for (int i = 0; i < autostartLen; i++)
    autostart[i] = EEPROM.read(autostartAdr + i);
}

void Settings::save() {
  if (debug) Serial.println("[E] Save Settings");

  EEPROM.write(ssidLenAdr, ssidLen);
  for (int i = 0; i < ssidLen; i++) {
    EEPROM.write(ssidAdr + i, ssid[i]);
  }
  EEPROM.write(passwordLenAdr, passwordLen);
  for (int i = 0; i < passwordLen; i++) {
    EEPROM.write(passwordAdr + i, password[i]);
  }
  EEPROM.write(autostartLenAdr, autostartLen);
  for (int i = 0; i < autostartLen; i++) {
    EEPROM.write(autostartAdr + i, autostart[i]);
  }
  EEPROM.write(channelAdr, channel);
  EEPROM.write(hiddenAdr, hidden);
  EEPROM.write(autoExecAdr, autoExec);

  EEPROM.commit();
}

void Settings::reset() {
  if (debug) Serial.println("[E] Reset Settings");

  String _ssid = "WiFi Duck";
  _ssid.toCharArray(ssid, 32);
  ssidLen = _ssid.length();

  String _pswd = "quackquack";
  _pswd.toCharArray(password, 32);
  passwordLen = _pswd.length();

  String _autostart = "autostart.txt";
  _autostart.toCharArray(autostart, 32);
  autostartLen = _autostart.length();

  channel = 1;
  hidden = false;
  autoExec = false;

  save();
}

void Settings::print() {
  Serial.println("\n[E] Settings:");
  Serial.println("[E] SSID = " + (String)ssid);
  Serial.println("[E] Password = " + (String)password);
  Serial.println("[E] Channel = " + (String)channel);
  Serial.println("[E] Hidden SSID = " + (String)hidden);
  Serial.println("[E] auto. Execute = " + (String)autoExec);
  Serial.println("[E] Autoscript = '" + (String)autostart + "'");
}
