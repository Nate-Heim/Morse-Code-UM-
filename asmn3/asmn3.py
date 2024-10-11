# Nate Heim

import smbus
import time

# Set up I2C
bus = smbus.SMBus(1)  # Raspberry Pi uses I2C bus 1 by default
I2C_SLAVE_ADDRESS = 0x11  # Address of the Pico

# Morse code for "U" and "M"
morse_code = {"U": ".._", "M": "__"}


# Function to send a Morse character (dot, dash, or character break)
def send_morse_letter(letter):
    morse = morse_code[letter]
    for symbol in morse:
        try:
            if symbol == ".":
                bus.write_byte(I2C_SLAVE_ADDRESS, ord("."))  # Send dot
            elif symbol == "_":
                bus.write_byte(I2C_SLAVE_ADDRESS, ord("_"))  # Send dash
            time.sleep(2.5)  # Wait after each symbol (LED on + off duration)
        except OSError as e:
            print(f"Error communicating with I2C device: {e}")
            return  # Exit function on error

    # Signal the end of the letter with a blue LED blink (character break)
    try:
        bus.write_byte(
            I2C_SLAVE_ADDRESS, ord(" ")
        )  # Send character break (space for blue LED)
        time.sleep(3.0)  # 3-second delay between letters
    except OSError as e:
        print(f"Error communicating with I2C device: {e}")


# Main loop to send "UM" in Morse code
try:
    while True:
        for char in "UM":
            send_morse_letter(char)  # Corrected function call here
except KeyboardInterrupt:
    pass  # Exit the loop on keyboard interrupt
