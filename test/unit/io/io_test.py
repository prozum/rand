from pysimavr.avr import Avr
from pysimavr.firmware import Firmware
from pysimavr.sim import ArduinoSim
import unittest

class IODigitalWrite(unittest.TestCase):
    def write1_expect1(self):
        return 1